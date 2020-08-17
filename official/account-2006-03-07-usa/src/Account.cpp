#include "Account.h"
#include "AccountDB.h"
#include "BillingConnection.h"
#include "BillingDB.h"
#include "BlockIPManager.h"
#include "Certificate.h"
#include "CharacterServerInfo.h"
#include "CharSvrProcess.h"
#include "ConnectLogDB.h"
#include "UserCounter.h"
#include "UserList.h"
#include "UserDB.h"
#include "UserProcess.h"
#include "WUCSPacket.h"
#include "WUCSStreamManager.h"
#include "WUCSSvrProcess.h"
#include "Common/Database.h"
#include "Common/Exception.h"
#include "Common/GlobalInfoDB.h"
#include "Common/InfoScript.h"
#include "Common/Network.h"
#include "Common/Packet.h"
#include "Common/Reporter.h"
#include "Common/ScriptParser.h"
#include "Common/ServerInfoList.h"
#include "Network2/StreamManager.h"
#include "Enums.h"


/// globals
CWUCSStreamManager g_WUCSClient;
CStreamManager g_UserStreamMgr;
CStreamManager g_CharSvrStreamMgr;
CInfoScript g_xmlFileUser;
CInfoScript g_scrptConfig;
CInfoScript g_scriptRestriction;
CUserList g_userList;
CCharacterServerInfo g_characterServerInfo[MAX_CLIENTTYPE];
CAccountDB g_AccountDB[3];
CUserDB g_UserDB;
CCertificate g_certificate;
CBillingConnection g_Billing(0);
CBillingDB g_BillingDB(0);
int g_GameID[3] = { 1, 0, 0 };
int g_nVersion[MAX_CLIENTTYPE];
bool g_bProcessPermit = true;
bool g_bXmlFileUserCheck = false;

/// locals
std::list<CProcess*> g_WUCSProcessList;
std::list<CProcess*> g_UserProcessList;
std::list<CProcess*> g_CharSvrProcessList;
HANDLE g_hStopEvent = INVALID_HANDLE_VALUE;
int g_nUserCounterTimer;
char g_szTime[1024];


/// forward declarations
BOOL WINAPI ConsoleHandler(DWORD dwConsoleEvent);
void __cdecl UpdateInfoThread(void* lpVoid);


int __cdecl main(int argc, const char** argv, const char** envp)
{
	char szModuleFileName[260] = {};
	GetModuleFileNameA(NULL, szModuleFileName, sizeof(szModuleFileName) - 1);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("build date(%s %s) \nModuleFileName - %s \n", __DATE__, __TIME__, szModuleFileName);

	SetUnhandledExceptionFilter(ExceptionFilter);

	MMRESULT ret = timeBeginPeriod(1);
	if( ret != TIMERR_NOERROR )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("timeBeginPeriod failed, ret %u\n", ret);

	if( !CSingleton<CNetwork>::getSingletonPtr()->CNetwork::InitializeNetwork() )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("gNetwork.InitializeNetwork failed\n");

	g_hStopEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
	if( g_hStopEvent == NULL )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("Create Stop Event fail! gle - %d", GetLastError());

	if( !SetConsoleCtrlHandler(&ConsoleHandler, TRUE) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("SetConsoleCtrlHandler failed - gle %d\n", GetLastError());

	if( !CSingleton<CBlockIPManager>::getSingletonPtr()->CBlockIPManager::loadBlockIPListFile("BlockIPList.txt") )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("Can not load IP Block List File. %s is not exist?", "BlockIPList.txt");

	InitPacketLen();
	InitWUCSPacketLen();

	g_scrptConfig.CInfoScript::Open("account.config.txt");

	const char* szEngVersion = g_scrptConfig.CInfoScript::GetInfo("ENGLISH");
	if( szEngVersion == NULL )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("cannot read the version of %s", "ENGLISH");
	g_nVersion[CLIENTTYPE_ENGLISH] = atoi(szEngVersion);

	const char* szEngSakVersion = g_scrptConfig.CInfoScript::GetInfo("ENGLISH_SAKRAY");
	if( szEngSakVersion == NULL )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("cannot read the version of %s", "ENGLISH_SAKRAY");
	g_nVersion[CLIENTTYPE_ENGLISH_SAKRAY] = atoi(szEngSakVersion);

	const char* PASSWORD_LOG = ( false ) ? "Ekdzhdrhk_dhwlddj3" : "tai";
	CSingleton<CConnectLogDB>::getSingletonPtr()->CDatabase::Connect("loger", PASSWORD_LOG, "Log");

	for( int i = 0; i < countof(g_AccountDB); ++i )
	{
		const char* PASSWORD_NLOGIN = ( false ) ? "Ekdzhdrhk_dhwlddj3" : "tai";
		g_AccountDB[i].CDatabase::Connect("login", PASSWORD_NLOGIN, "nLogin");
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("account DB %d connected\n", i + 1);
	}

	const char* PASSWORD_GLOBALINFO = ( false ) ? "wleks" : "tai";
	CSingleton<CGlobalInfoDB>::getSingletonPtr()->CDatabase::Connect("globalinfo", PASSWORD_GLOBALINFO, "GlobalInfo");

	CSingleton<CGlobalInfoDB>::getSingletonPtr()->CGlobalInfoDB::InitServerInfoList(false);

	char szIP[100] = {};
	unsigned int dwPublicIP = CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetLocalIP(true);
	int SID = CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetSID(dwPublicIP, SERVERTYPE_ACCOUNT);
	CSingleton<CNetwork>::getSingletonPtr()->CNetwork::GetTextIP(dwPublicIP, szIP);
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("%s local SID - %d\n", szIP, SID);

	SSERVERINFO serverInfo[20] = {};

	CScriptParser scrptCharserverSet;
	if( !scrptCharserverSet.CScriptParser::LoadFile("account.charserverset.txt") )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("Can't load account.charserverset.txt");

	int nCount = atoi(scrptCharserverSet.CScriptParser::GetItem("ServerCount", 0));
	for( int i = 0; i < nCount; ++i )
	{
		char buf[5];
		sprintf(buf, "SID%d", i);

		int nSID = atoi(scrptCharserverSet.CScriptParser::GetItem(buf, 2)); //FIXME: NULL-unsafe
		int clienttype = atoi(scrptCharserverSet.CScriptParser::GetItem(buf, 0)); //FIXME: NULL-unsafe

		CSingleton<CServerInfoList>::getSingletonPtr()->CServerInfoList::GetServerInfo(&serverInfo[i], nSID);
		g_characterServerInfo[clienttype].CCharacterServerInfo::AddCharacterServerInfo(&serverInfo[i], 0);
	}

	const char* szServerName = g_scrptConfig.CInfoScript::GetInfo("SERVERNAME");
	if( szServerName == NULL )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("cannot read the SERVERNAME");

	const char* szServerNumber = g_scrptConfig.CInfoScript::GetInfo("SERVERNUMBER");
	if( szServerName == NULL ) //FIXME: szServerNumber
	{
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("cannot read the SERVERNUMBER");
		return 0;
	}

	const char* szUserCounterTimer = g_scrptConfig.CInfoScript::GetInfo("USERCOUNTERTIMER");
	g_nUserCounterTimer = ( szUserCounterTimer != NULL ) ? atoi(szUserCounterTimer) : 5;

	CSingleton<CUserCounter>::getSingletonPtr()->CUserCounter::InitServer(szServerName, atoi(szServerNumber));

	/////////////////////////////////////////////////////////////////////////////
	const char* szWUCS_IP = g_scrptConfig.CInfoScript::GetInfo("WUCS_IP");
	const char* szWUCS_IP_SEC = g_scrptConfig.CInfoScript::GetInfo("WUCS_IP_SEC");
	const char* szWUCS_PORT = g_scrptConfig.CInfoScript::GetInfo("WUCS_PORT");
	const int WUCS_NETWORK_BUFSIZE = 3000000;
	const int WUCS_PROCESS_OBJ_NUM = 1;
	const int WUCS_PROCESS_THREADS = 1;
	const int WUCS_WORKER_THREADS  = 1;
	const int WUCS_SLEEP_RATIO = 3;

	if( szWUCS_IP == NULL && szWUCS_PORT == NULL )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("Set szWUCSIP Server IP or Port ! - WUCS_IP or WUCS_PORT Field(account.config.txt)");

	if( !CreateProcessList<CWUCSSvrClient>(&g_WUCSProcessList, WUCS_PROCESS_OBJ_NUM) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("CreateProcessList<CWUCSSvrClient> failed");

	if( !g_WUCSClient.CStreamManager::Create(g_WUCSProcessList, WUCS_NETWORK_BUFSIZE, WUCS_NETWORK_BUFSIZE, WUCS_NETWORK_BUFSIZE/3, false) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("WUCS stream mgr create failed");

	if( !g_WUCSClient.CStreamManager::StartProcessing(WUCS_PROCESS_THREADS, WUCS_SLEEP_RATIO, THREAD_PRIORITY_ABOVE_NORMAL) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("g_WUCSSvrStreamMgr.StartProcessing failed");

	if( !g_WUCSClient.CWUCSStreamManager::Connect(szWUCS_IP, szWUCS_IP_SEC, atoi(szWUCS_PORT), WUCS_WORKER_THREADS, 0) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("WUCS stream mgr listen failed");
	/////////////////////////////////////////////////////////////////////////////
	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("user stream ready\n");
	/////////////////////////////////////////////////////////////////////////////
	const DWORD CHAR_IP = inet_addr("0.0.0.0");
	const WORD CHAR_PORT = 6800;
	const int CHAR_NETWORK_BUFSIZE = 3000000;
	const int CHAR_PROCESS_OBJ_NUM = 6;
	const int CHAR_PROCESS_THREADS = 5;
	const int CHAR_WORKER_THREADS  = 3;
	const int CHAR_SLEEP_RATIO = 3;

	if( !CreateProcessList<CCharSvrProcess>(&g_CharSvrProcessList, CHAR_PROCESS_OBJ_NUM) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("CreateProcessList<CCharSvrProcess> failed");

	if( !g_CharSvrStreamMgr.CStreamManager::Create(g_CharSvrProcessList, CHAR_NETWORK_BUFSIZE, CHAR_NETWORK_BUFSIZE, CHAR_NETWORK_BUFSIZE/3, true) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("char stream mgr create failed");

	if( !g_CharSvrStreamMgr.CStreamManager::StartProcessing(CHAR_PROCESS_THREADS, CHAR_SLEEP_RATIO, THREAD_PRIORITY_ABOVE_NORMAL) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("g_CharSvrStreamMgr.StartProcessing failed");

	if( !g_CharSvrStreamMgr.CStreamManager::Listen(CHAR_PORT, 10, 3600000, CHAR_WORKER_THREADS, 4000, 4500, CHAR_IP) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("char stream mgr listen failed");
	/////////////////////////////////////////////////////////////////////////////
	Sleep(1000);
	/////////////////////////////////////////////////////////////////////////////
	const DWORD USER_IP = inet_addr("0.0.0.0");
	const WORD USER_PORT = 6900;
	const int USER_NETWORK_BUFSIZE = 10000;
	const int USER_PROCESS_OBJ_NUM = 5000;
	const int USER_PROCESS_THREADS = 10;
	const int USER_WORKER_THREADS  = 3;
	const int USER_SLEEP_RATIO = 1;

	if( !CreateProcessList<CUserProcess>(&g_UserProcessList, USER_PROCESS_OBJ_NUM) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("CreateProcessList<CUserProcess> failed");

	if( !g_UserStreamMgr.CStreamManager::Create(g_UserProcessList, USER_NETWORK_BUFSIZE, USER_NETWORK_BUFSIZE, USER_NETWORK_BUFSIZE, false) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("user stream mgr create error");

	if( !g_UserStreamMgr.CStreamManager::StartProcessing(USER_PROCESS_THREADS, USER_SLEEP_RATIO, THREAD_PRIORITY_NORMAL) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("g_UserStreamMgr.StartProcessing failed");

	if( !g_UserStreamMgr.CStreamManager::Listen(USER_PORT, 100, 60000, USER_WORKER_THREADS, 4000, 4500, USER_IP) )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::FatalError("user stream mgr listen error");
	/////////////////////////////////////////////////////////////////////////////

	puts("## ready to accept clients ##");

	_beginthread(&UpdateInfoThread, 0, NULL);
	WaitForSingleObject(g_hStopEvent, INFINITE);
	CloseHandle(g_hStopEvent);

	CSingleton<CNetwork>::getSingletonPtr()->CNetwork::CleanupNetwork();

	MMRESULT ret2 = timeEndPeriod(1);
	if( ret2 != TIMERR_NOERROR )
		CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("timeEndPeriod failed, ret %u\n", ret2);

	CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("server terminated -------------------");
	return 0;
}


BOOL WINAPI ConsoleHandler(DWORD dwConsoleEvent)
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
		g_CharSvrStreamMgr.CStreamManager::Destroy();
		Sleep(1000);
		DestroyProcessList(g_UserProcessList);
		DestroyProcessList(g_CharSvrProcessList);
	break;
	default:
	break;
	};

	SetEvent(g_hStopEvent);
	return TRUE;
}


void __cdecl UpdateInfoThread(void* lpVoid)
{
	char szInfo[1024] = {};

	DWORD dwBeginTime = timeGetTime();
	int lastMin = -1;

	while( 1 )
	{
		time_t currentTime;
		time(&currentTime);
		tm* t = localtime(&currentTime);
		strftime(g_szTime, sizeof(g_szTime), "%Y-%m-%d %H:%M:%S", t);

		int curMin = t->tm_min;
		if( curMin % g_nUserCounterTimer == 0 && curMin != lastMin )
		{
			lastMin = curMin;
			CSingleton<CUserCounter>::getSingletonPtr()->CUserCounter::WriteUserCount();
		}

		DWORD uptime = timeGetTime() - dwBeginTime;

		int hours = uptime / 3600000;
		uptime = uptime % 3600000;
		int minutes = uptime / 60000;
		uptime = uptime % 60000;
		int seconds = uptime / 1000;

		sprintf(szInfo, "(%d,%d)(C%d,%d)(%d/%d)(H%d)(%d/%d)(B%d,%d) %04d:%02d:%02d %s",
			g_userList.CUserList::GetCount(),
			g_userList.CUserList::GetCountAuth(),
			g_UserStreamMgr.CStreamManager::GetConnectionCount(),
			g_UserStreamMgr.CStreamManager::GetFreeStreamNum(),
			g_UserStreamMgr.CStreamManager::GetRunningWorkerThreadNum(),
			g_UserStreamMgr.CStreamManager::GetWorkerThreadNum(),
			g_CharSvrStreamMgr.CStreamManager::GetConnectionCount(),
			g_CharSvrStreamMgr.CStreamManager::GetRunningWorkerThreadNum(),
			g_CharSvrStreamMgr.CStreamManager::GetWorkerThreadNum(),
			g_Billing.m_bConnected,
			g_Billing.m_qSend.m_dwCount,
			hours,
			minutes,
			seconds,
			"NB");

		SetConsoleTitleA(szInfo);

		Sleep(500);
	}
}
