#include "Character.h"
#include "CharacterDB.h"
#include "CharacterLogDB.h"
#include "DES.h"
#include "ForbiddenName.h"
#include "PremiumServiceDB.h"
#include "StartMap.h"
#include "UserAuthenticate.h"
#include "UserList.h"
#include "UserVerify.h"
#include "ZoneServerInfoList.h"
#include "AccountProcess.h"
#include "UserProcess.h"
#include "ZoneSvrProcess.h"
#include "Common/Exception.h"
#include "Common/GlobalInfoDB.h"
#include "Common/InfoScript.h"
#include "Common/IPInfoDB.h"
#include "Common/IPMap.h"
#include "Common/Network.h"
#include "Common/Packet.h"
#include "Common/Reporter.h"
#include "Common/ServerInfoList.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/CompletionPort.h"
#include "Network3/ProcessFactory.h"
#include "Network3/StreamManager.h"
#include "enum.hpp"


/// globals
CStreamManager g_ZoneSvrStreamMgr;
CStreamManager g_AccountStreamMgr;
CStreamManager g_UserStreamMgr;
CAsyncProcessMgr g_AsyncProcessMgr;
CInfoScript g_characterConfig;
CUserList g_UserList;
CUserAuthenticate g_UserAuthenticate;
SSERVERINFO gLocalServerInfo = {};
DWORD g_dwLocalIP = INADDR_ANY;
bool g_bProcessPermit = true;
bool g_bUsingCharacterPassword = false;
bool g_bAccountConnected = false;

/// locals
static CCompletionPort g_compltport;
static CProcessFactory<CZoneSvrProcess> g_ZoneSvrProcessFactory;
static CProcessFactory<CAccountProcess> g_AccountProcessFactory;
static CProcessFactory<CUserProcess> g_UserProcessFactory;
static IPMap gGameRoomIPMap;
static int g_nLocalSID = 0;
static DWORD g_dwLogUser = 0;
static HANDLE g_hStopEvent = INVALID_HANDLE_VALUE;
static DWORD g_dwMyPublicIP = INADDR_ANY;
static DWORD g_dwMyPrivateIP = INADDR_ANY;
static char g_szTime[1024] = {};


/// forward declarations
int __stdcall ConsoleHandler(DWORD dwConsoleEvent);
void __cdecl UpdateInfoThread(void* lpVoid);


void Decrypt(const char* encBuf, unsigned char* decBuf)
{
	unsigned char key[7] = { 0x78, 0x11, 0x23, 0x2A, 0xF1, 0xED, 0x07 };

	DES des(key);

	char szString[2+1] = {};

	size_t hexlen = strlen(encBuf) / 2;

	// unpack hex-string to binary
	for( size_t i = 0; i < hexlen; ++i )
	{
		szString[0] = encBuf[2*i+0];
		szString[1] = encBuf[2*i+1];
		sscanf(szString, "%02X", &decBuf[i]);
	}

	// decode data, block by block
	for( size_t i = 0; i < hexlen; i += 8 )
		des.DES::decrypt(&decBuf[i], 8);
}


int __cdecl main(int argc, const char** argv, const char** envp)
{
	MMRESULT mmresult;
	bool result;

	CSingleton<CUserVerify>::getSingletonPtr()->CUserVerify::StartThread(); //FIXME: no synchronization, will crash on shutdown

	srand((unsigned int)time(NULL));

	char szModuleFileName[260] = {};
	GetModuleFileNameA(0, szModuleFileName, sizeof(szModuleFileName)-1);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("build date(%s %s) \nModuleFileName - %s \n", __DATE__, __TIME__, szModuleFileName);

	SetUnhandledExceptionFilter(&ExceptionFilter);

	mmresult = timeBeginPeriod(1);
	if( mmresult != TIMERR_NOERROR )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("timeBeginPeriod failed, ret %u\n", mmresult);

	if( !CSingleton<CNetwork>::getSingletonPtr()->CNetwork::InitializeNetwork() )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("gNetwork.InitializeNetwork failed\n");

	g_hStopEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
	if( g_hStopEvent == NULL )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("Create Stop Event fail! gle - %d", GetLastError());

	SetConsoleCtrlHandler(ConsoleHandler, TRUE);

	InitPacketLen();

	g_characterConfig.CInfoScript::Open("character.config.txt");
	g_dwLogUser = atoi(g_characterConfig.CInfoScript::GetInfo("LOGAID"));

	if( !CSingleton<CStartMap>::getSingletonPtr()->CStartMap::Initialize() )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("character.startmap.txt is not valid format. Please check it.");

	if( !CSingleton<CForbiddenName>::getSingletonPtr()->CForbiddenName::readForbiddenWordFile("character.preventName.txt") )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("cannot read character.preventName.txt or invalid format");

	if( !CSingleton<CForbiddenName>::getSingletonPtr()->CForbiddenName::readAsciiTableFile("character.preventAscii.txt") )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("FORBIDDEN_NAME disabled\n");

	const char* szGLOBALDBPW = g_characterConfig.CInfoScript::GetInfo("GLOBAL_DBPW");
	if( szGLOBALDBPW == NULL )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("Set Database Password! - GLOBAL_DBPW Field(character.config.txt)");

	char global_dbpw[256] = {};
	Decrypt(szGLOBALDBPW, (unsigned char*)global_dbpw);

	const char* szGAMEDBPW = g_characterConfig.CInfoScript::GetInfo("GAME_DBPW");
	if( szGAMEDBPW == NULL )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("Set Database Password! - GAME_DBPW Field(character.config.txt)");

	char game_dbpw[256] = {};
	Decrypt(szGAMEDBPW, (unsigned char*)game_dbpw);

	CSingleton<CPremiumServiceDB>::getSingletonPtr()->CDatabase::Connect("pcpremium", global_dbpw, "pcpremium");

	g_dwMyPublicIP = CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetLocalIP(true);
	g_dwMyPrivateIP = CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetLocalIP(false);
	if( g_dwMyPublicIP == INADDR_ANY )
		g_dwMyPublicIP = g_dwMyPrivateIP;
	g_dwLocalIP = g_dwMyPublicIP;
	if( g_dwMyPublicIP == INADDR_ANY )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("there's no IP address in this machine\n");

	char szIP[100] = {};
	CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(g_dwMyPublicIP, szIP);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("local ip %s\n", szIP);

	CSingleton<CIPInfoDB>::getSingletonPtr()->CDatabase::Connect("ipinfo", game_dbpw, "ipinfo");
	CSingleton<CIPInfoDB>::getSingletonPtr()->CIPInfoDB::InitMapInfoList();

	CSingleton<CGlobalInfoDB>::getSingletonPtr()->CDatabase::Connect("globalinfo", global_dbpw, "GlobalInfo");
	CSingleton<CGlobalInfoDB>::getSingletonPtr()->CGlobalInfoDB::InitServerInfoList(false);

	g_nLocalSID = CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetSID(g_dwLocalIP, SERVERTYPE_CHARACTER);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("g_nLocalSID %d\n", g_nLocalSID);

	if( !CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetServerInfo(&gLocalServerInfo, g_nLocalSID) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Cannot read local server information\n");

	int nSID[30];
	int nCount = CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetSID(g_nLocalSID, nSID);

	SSERVERINFO serverInfo[30] = {};

	for( int i = 0; i < nCount; ++i )
		CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetServerInfo(&serverInfo[i], nSID[i]);

	for( int i = 0; i < nCount; ++i )
	{
		CSingleton<CZoneServerInfoList>::getSingletonPtr()->CZoneServerInfoList::AddZoneServerInfo(&serverInfo[i]);
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("Zone[%d] %s\n", i, serverInfo[i].m_szIP);
	}

	CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDBBase::InitProp("character", game_dbpw, "character");

	CSingleton<CCharacterDB>::getSingletonPtr()->CDatabase::Connect("character", game_dbpw, "character");
	CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDBBase::VeryfyConnection();

	g_bUsingCharacterPassword = CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDB::IsUsingCharacterPassword();

	if( g_characterConfig.CInfoScript::GetInfo("MODEPVP") )
	{
		CSingleton<CPVPCharacterDB>::getSingletonPtr()->CDatabase::Connect("character", game_dbpw, "pvpcharacter");
		CSingleton<CPvPPointDB>::getSingletonPtr()->CDatabase::Connect("point", game_dbpw, "PvPoint");
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("MODE : MOVE TO PVP");
	}

	CSingleton<CCharacterLogDB>::getSingletonPtr()->CDatabase::Connect("Loger", game_dbpw, "itemlog");

	/////////////////////////////////////////////////////////////////////////////
	const int ASYNCPROCESS_THREADS = 5;
	const int ASYNCPROCESS_POOL_COUNT = 100000;
	const int COMPLETIONPORT_THREADS = 3;

	g_AsyncProcessMgr.CAsyncProcessMgr::Create(ASYNCPROCESS_THREADS, ASYNCPROCESS_POOL_COUNT);
	g_compltport.CCompletionPort::Create(COMPLETIONPORT_THREADS);
	/////////////////////////////////////////////////////////////////////////////
	std::list<CProcess*> process_list;
	/////////////////////////////////////////////////////////////////////////////
	const DWORD ZONE_IP = inet_addr("0.0.0.0");
	const WORD ZONE_PORT = ( CSingleton<CGlobalInfoDB>::getSingletonPtr()->IsColumnPrivateAdded() ) ? (WORD)gLocalServerInfo.m_nPrivatePort : 7000;
	const int ZONE_NETWORK_BUFSIZE = 3000000;
	const int ZONE_PROCESS_OBJ_NUM = 20;

	result = g_ZoneSvrProcessFactory.CProcessFactory<CZoneSvrProcess>::CreateProcessList(&process_list, ZONE_PROCESS_OBJ_NUM);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("\t(%d) = g_ZoneSvrProcessFactory.CreateProcessList(&process_list, ZONE_PROCESS_OBJ_NUM); \n", result);

	result = g_ZoneSvrStreamMgr.CStreamManager::Create(process_list, ZONE_NETWORK_BUFSIZE, ZONE_NETWORK_BUFSIZE, &g_compltport, false);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("\t(%d) = g_ZoneSvrStreamMgr.Create(process_list, 3000000, 3000000, &g_compltport); \n", result);

	result = g_ZoneSvrStreamMgr.CStreamManager::Listen(ZONE_PORT, 5, 1800 * 1000, ZONE_IP);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("\t(%d) = g_ZoneSvrStreamMgr.Listen(gLocalServerInfo.m_nPrivatePort, ; \n", result);
	/////////////////////////////////////////////////////////////////////////////
	process_list.clear();
	/////////////////////////////////////////////////////////////////////////////
	SSERVERINFO account_server_info;
	CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetServerInfo(&account_server_info, CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetSID(g_dwLocalIP, SERVERTYPE_CHARACTER));
	CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetServerInfo(&account_server_info, account_server_info.m_nPrimaryDestnation);

	const char* szACC_IP = ( CSingleton<CGlobalInfoDB>::getSingletonPtr()->IsColumnPrivateAdded() ) ? account_server_info.m_szPrivateIP : account_server_info.m_szIP;
	const WORD ACC_PORT = ( CSingleton<CGlobalInfoDB>::getSingletonPtr()->IsColumnPrivateAdded() ) ? (WORD)account_server_info.m_nPrivatePort : (WORD)account_server_info.m_nPort;
	const int ACC_NETWORK_BUFSIZE = 30000000;
	const int ACC_PROCESS_OBJ_NUM = 1;

	result = g_AccountProcessFactory.CProcessFactory<CAccountProcess>::CreateProcessList(&process_list, ACC_PROCESS_OBJ_NUM);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("\t(%d) = g_AccountProcessFactory.CreateProcessList(&process_list, 1); \n", result);

	result = g_AccountStreamMgr.CStreamManager::Create(process_list, ACC_NETWORK_BUFSIZE, ACC_NETWORK_BUFSIZE, &g_compltport, true);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("\t(%d) = g_AccountStreamMgr.Create(process_list, 30000000, 30000000, &g_compltport, true); \n", result);

	result = g_AccountStreamMgr.CStreamManager::Connect(szACC_IP, ACC_PORT, 3600 * 1000);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("\t(%d) = g_AccountStreamMgr.Connect(account_server_info.m_szPrivateIP,; \n", result);
	/////////////////////////////////////////////////////////////////////////////
	process_list.clear();
	/////////////////////////////////////////////////////////////////////////////
	const DWORD USER_IP = inet_addr("0.0.0.0");
	const WORD USER_PORT = (WORD)gLocalServerInfo.m_nPort;
	const int USER_NETWORK_BUFSIZE = 10000;
	const int USER_PROCESS_OBJ_NUM = 5000;

	result = g_UserProcessFactory.CProcessFactory<CUserProcess>::CreateProcessList(&process_list, USER_PROCESS_OBJ_NUM);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("\t(%d) = g_UserProcessFactory.CreateProcessList(&process_list, USER_PROCESS_OBJ_NUM); \n", result);

	result = g_UserStreamMgr.CStreamManager::Create(process_list, USER_NETWORK_BUFSIZE, USER_NETWORK_BUFSIZE, &g_compltport, false);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("\t(%d) = g_UserStreamMgr.Create(process_list, 10000, 10000, &g_compltport); \n", result);

	result = g_UserStreamMgr.CStreamManager::Listen(USER_PORT, 100, 60 * 1000, USER_IP);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("\t(%d) = g_UserStreamMgr.Listen(gLocalServerInfo.m_nPort, 100, 1000 * 60); \n", result);
	/////////////////////////////////////////////////////////////////////////////
	process_list.clear();
	/////////////////////////////////////////////////////////////////////////////

	puts("## ready to accept clients ##");

	_beginthread(&UpdateInfoThread, 0, NULL);
	WaitForSingleObject(g_hStopEvent, INFINITE);
	CloseHandle(g_hStopEvent);

	CSingleton<CNetwork>::getSingletonPtr()->CNetwork::CleanupNetwork();

	mmresult = timeEndPeriod(1);
	if( mmresult != TIMERR_NOERROR )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("timeEndPeriod failed, ret %u\n", mmresult);

	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("server terminated -------------------");
	return 0;
}


int __stdcall ConsoleHandler(DWORD dwConsoleEvent)
{
	switch( dwConsoleEvent )
	{
	case CTRL_C_EVENT:
	case CTRL_BREAK_EVENT:
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		CSingleton<CReporter>::getSingletonPtr()->CReporter::MessagePrint("Waiting for all objects to be destroyed...\n");
		g_bProcessPermit = false;
		g_UserStreamMgr.CStreamManager::Destroy();
		Sleep(1000);
		g_AccountStreamMgr.CStreamManager::Destroy();
		Sleep(500);
		g_ZoneSvrStreamMgr.CStreamManager::Destroy();
		Sleep(500);
		g_compltport.CCompletionPort::Destroy();
		g_AsyncProcessMgr.CAsyncProcessMgr::Destroy();
	break;
	default:
	break;
	};

	SetEvent(g_hStopEvent);
	return 1;
}


void __cdecl UpdateInfoThread(void* lpVoid)
{
	DWORD dwBeginTime = timeGetTime();

	while( g_bProcessPermit )
	{
		time_t currentTime;
		time(&currentTime);
		strftime(g_szTime, sizeof(g_szTime), "%Y-%m-%d %H:%M:%S", localtime(&currentTime));

		DWORD uptime = timeGetTime() - dwBeginTime;
		DWORD hours = uptime / 3600000;
		uptime = uptime % 3600000;
		DWORD minutes = uptime / 60000;
		uptime = uptime % 60000;
		DWORD seconds = uptime / 1000;

		char szInfo[1024];
		sprintf(szInfo, "%d C%d,S%d A%d Z%d W%d p%d/%d %04d:%02d:%02d v(%s %s)",
			g_UserList.CUserList::GetCount(),
			g_UserStreamMgr.CStreamManager::GetConnectionCount(),
			g_UserStreamMgr.CStreamManager::GetFreeStreamNum(),
			g_AccountStreamMgr.CStreamManager::GetConnectionCount(),
			g_ZoneSvrStreamMgr.CStreamManager::GetConnectionCount(),
			0,
			g_AsyncProcessMgr.CAsyncProcessMgr::GetPoolAllocSize(),
			g_AsyncProcessMgr.CAsyncProcessMgr::GetPoolSize(),
			hours,
			minutes,
			seconds,
			__DATE__,
			__TIME__
			);

		SetConsoleTitleA(szInfo);
		CSingleton<CCharacterDB>::getSingletonPtr()->CCharacterDBBase::VeryfyConnection();
		Sleep(800);
	}
}


void MakeCHARACTER_INFO(SCHARINFO* pCharInfo, CHARACTER_INFO* pCharacter_Info_target)
{
	memset(pCharacter_Info_target, 0, sizeof(CHARACTER_INFO));

	memcpy(pCharacter_Info_target->name, pCharInfo->m_szName, sizeof(pCharacter_Info_target->name));
	pCharacter_Info_target->exp = pCharInfo->m_nExp;
	pCharacter_Info_target->jobexp = pCharInfo->m_nJobExp;
	pCharacter_Info_target->money = pCharInfo->m_nMoney;
	pCharacter_Info_target->Str = static_cast<unsigned char>(pCharInfo->m_nStr);
	pCharacter_Info_target->Agi = static_cast<unsigned char>(pCharInfo->m_nAgi);
	pCharacter_Info_target->Vit = static_cast<unsigned char>(pCharInfo->m_nVit);
	pCharacter_Info_target->Int = static_cast<unsigned char>(pCharInfo->m_nInt);
	pCharacter_Info_target->Dex = static_cast<unsigned char>(pCharInfo->m_nDex);
	pCharacter_Info_target->Luk = static_cast<unsigned char>(pCharInfo->m_nLuk);
	pCharacter_Info_target->job = static_cast<short>(pCharInfo->m_nJob);
	pCharacter_Info_target->sppoint = static_cast<short>(pCharInfo->m_nSpPoint);
	pCharacter_Info_target->jobpoint = static_cast<short>(pCharInfo->m_nJobPoint);
	pCharacter_Info_target->level = static_cast<short>(pCharInfo->m_nCLevel);
	pCharacter_Info_target->joblevel = pCharInfo->m_nJobLevel;
	pCharacter_Info_target->CharNum = static_cast<unsigned char>(pCharInfo->m_nSlotIndex);
	pCharacter_Info_target->GID = static_cast<unsigned long>(pCharInfo->m_nGID);
	pCharacter_Info_target->speed = static_cast<short>(pCharInfo->m_nSpeed);
	pCharacter_Info_target->head = static_cast<short>(pCharInfo->m_nHead);
	pCharacter_Info_target->weapon = static_cast<short>(pCharInfo->m_nWeapon);
	pCharacter_Info_target->accessory = static_cast<short>(pCharInfo->m_nAccessory);
	pCharacter_Info_target->bodystate = pCharInfo->m_nBodyState;
	pCharacter_Info_target->healthstate = pCharInfo->m_nHealthState;
	pCharacter_Info_target->effectstate = pCharInfo->m_nEffectState;
//	pCharacter_Info_target->virtue = pCharInfo->m_nVirtue; //FIXME
//	pCharacter_Info_target->honor = pCharInfo->m_nHonor; //FIXME
	pCharacter_Info_target->accessory2 = static_cast<short>(pCharInfo->m_nAccessory2);
	pCharacter_Info_target->accessory3 = static_cast<short>(pCharInfo->m_nAccessory3);
	pCharacter_Info_target->headpalette = static_cast<short>(pCharInfo->m_nHeadPalette);
	pCharacter_Info_target->bodypalette = static_cast<short>(pCharInfo->m_nBodyPalette);
	pCharacter_Info_target->shield = static_cast<short>(pCharInfo->m_nShield);
	pCharacter_Info_target->sp = static_cast<short>(pCharInfo->m_nSp);
	pCharacter_Info_target->hp = static_cast<short>(pCharInfo->m_nHp);
	pCharacter_Info_target->maxsp = static_cast<short>(pCharInfo->m_nMaxSp) + pCharInfo->m_nMaxSp * pCharacter_Info_target->Int / 100;
	pCharacter_Info_target->maxhp = static_cast<short>(pCharInfo->m_nMaxHp) + pCharInfo->m_nMaxHp * pCharacter_Info_target->Vit / 100;

	if( pCharacter_Info_target->sp > pCharacter_Info_target->maxsp )
		pCharacter_Info_target->sp = pCharacter_Info_target->maxsp;

	if( pCharacter_Info_target->hp > pCharacter_Info_target->maxhp )
		pCharacter_Info_target->hp = pCharacter_Info_target->maxhp;

//	pCharacter_Info_target->haircolor = static_cast<unsigned char>(pCharInfo->m_nHairColor); //FIXME
}


////////////////////////////////////////


/// locals
static std::map<int,std::map<int,AuthenticateConnectCharacter>> gHashMapConnectCharacter;


void PutConnectCharacter(int iAID, int iSlot)
{
	gHashMapConnectCharacter[iAID][iSlot] = CONNECT_CHARACTER;
}


enum AuthenticateConnectCharacter IsConnectCharacter(int iAID, int iSlot)
{
	std::map<int,std::map<int,AuthenticateConnectCharacter>>::const_iterator itAID = gHashMapConnectCharacter.find(iAID);
	if( itAID == gHashMapConnectCharacter.end() )
		return NOT_CONNECT_CHARACTER;

	std::map<int,AuthenticateConnectCharacter>::const_iterator itSlot = itAID->second.find(iSlot);
	if( itSlot == itAID->second.end() )
		return NOT_CONNECT_CHARACTER;

	return CONNECT_CHARACTER;
}


void DeleteConnectCharacter(int iAID)
{
	gHashMapConnectCharacter[iAID].clear();
}
