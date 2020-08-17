#include "Character.h"
#include "CharacterConfig.h"
#include "CharacterDB.h"
#include "CharacterLogDB.h"
#include "CHsvrSchedulerIdentity.h"
#include "DES.h"
#include "ForbiddenName.h"
#include "MsgInfo.h"
#include "PremiumServiceDB.h"
#include "PremiumServiceInfo.h"
#include "StartMap.h"
#include "UserAuthenticate.h"
#include "UserList.h"
#include "UserVerify.h"
#include "ZoneServerInfoList.h"
#include "CUserStreamMgr.h"
#include "CZsvrStreamMgr.h"
#include "AccountProcess.h"
#include "UserProcess.h"
#include "ZoneSvrProcess.h"
#include "Common/DBProxy.h"
#include "Common/EnterTraceLog.h"
#include "Common/GlobalInfoDB.h"
#include "Common/IPInfoDB.h"
#include "Common/IPMap.h"
#include "Common/MyMiniDumpUnhandledExceptionHandler.h"
#include "Common/Network.h"
#include "Common/NOutputTextMgr.h"
#include "Common/Packet.h"
#include "Common/ServerIdentity.h"
#include "Common/ServerInfoList.h"
#include "Common/Thread.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/CompletionPort.h"
#include "Network3/ProcessFactory.h"
#include "Network3/StreamManager.h"
#include "Enums.h"


/// globals
CZsvrStreamMgr g_ZoneSvrStreamMgr;
CStreamManager g_AccountStreamMgr;
CUserStreamMgr g_UserStreamMgr;
CAsyncProcessMgr g_AsyncProcessMgr;
CCharacterConfig g_characterConfig;
CUserList g_UserList;
CUserAuthenticate g_UserAuthenticate;
SSERVERINFO gLocalServerInfo;
DWORD g_dwLocalIP;
bool g_bProcessPermit = true;
bool g_bUsingCharacterPassword;
bool g_bAccountConnected;
bool g_bEnableDelChar;
bool g_bEnableMakeChar;
int g_bEnableAdultCheck;
DWORD g_dwUSERKEEP_BY_CH_PING;
sConfig gconfig;

/// locals
static CCompletionPort g_compltport;
static CProcessFactory<CZoneSvrProcess> g_ZoneSvrProcessFactory;
static CProcessFactory<CAccountProcess> g_AccountProcessFactory;
static CProcessFactory<CUserProcess> g_UserProcessFactory;
static CMsgInfo gMsgInfo;
static IPMap gGameRoomIPMap;
static int g_nLocalSID;
static DWORD g_dwLogUser;
static HANDLE g_hStopEvent = INVALID_HANDLE_VALUE;
static DWORD g_dwMyPublicIP;
static DWORD g_dwMyPrivateIP;
static DWORD g_dwGravityPublicIP = 0xCB92C077; // inet_addr("119.192.146.203")
static HINSTANCE hInst;
static HWND gHwnd;
static MMRESULT g_mmResult;
static int gPcbangDBReloadStartTM;
static int gPcBangDBReloadEndTM;
static int gPcbangDBReloadTimeIntervalPerMin;
static char g_szTime[1024];
static int MaxOutputLineCnt = -1;


/// forward declarations
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
std::pair<bool,std::string> StartUp1();
std::pair<bool,std::string> StartUp2();
void Destroy();
void __cdecl UpdateInfoThread(void* lpVoid);
void __cdecl PcbangDBReload(void* lpParam);


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


void PutText(HDC hdc, int x, int y, const char* msg, ...)
{
	va_list va;
	va_start(va, msg);

	char szMessage[1024] = {};
	_vsnprintf_s(szMessage, sizeof(szMessage), _TRUNCATE, msg, va);

	TextOutA(hdc, x, y, szMessage, strlen(szMessage));
}


/// @custom
void DisplayStatusMessage(const char* msg)
{
	HDC dc = GetDC(gHwnd);
	SetTextColor(dc, 0x0000FF);
	PutText(dc, 10, 480, msg);
	ReleaseDC(gHwnd, dc);
}


void OutputServerIdentity(const char in_pStr[])
{
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, in_pStr);
}


void __cdecl AccountServerIdentity()
{
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "start---------- server identity -----------------------------\n");
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "BULID DATE [%s %s] \n", __DATE__, __TIME__);
	//NOTE: 5 lines missing here
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[EPISODE_VER][MAJOR_VER] %d.%d\n", 14, 2);
	//NOTE: 20 lines missing here
	ServerIdentity(&OutputServerIdentity);
	//NOTE: 2 lines missing here
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "end----------------------------------------------------------\n");
}


namespace {
void mySetWindowTitle()
{
	char buffer[260] = {};
	_snprintf(buffer, sizeof(buffer), "CHR - INTERNATIONAL Ep%d.%d", 14, 2);

	std::string Title = buffer;

	std::string ServerType = "NORMAL";
	if( gconfig.nServerType == 0 )
		ServerType = "FREE";
	else
	if( gconfig.nServerType == 1 )
		ServerType = "BILL";
	else
	if( gconfig.nServerType == 2 )
		ServerType = "PREMIUM";
	else
	if( gconfig.nServerType == 3 )
		ServerType = "UNION";

	char myServerName[26] = {};
	memcpy_s(myServerName, sizeof(myServerName), gLocalServerInfo.m_szName, sizeof(myServerName)-1);

	std::string HSvrName = myServerName;
	std::string configuration; // unused?

	Title += " " + ServerType;

	if( HSvrName.size() != 0 )
		Title += " " + HSvrName;

	Title += std::string(" (") + std::string(__DATE__" "__TIME__) + std::string(")");

	SetWindowTextA(gHwnd, Title.c_str());
}
}; // namespace


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = &WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIconA(hInstance, NULL);
	wcex.hCursor = LoadCursorA(NULL, MAKEINTRESOURCEA(IDC_ARROW));
	wcex.hbrBackground = HBRUSH(COLOR_WINDOWFRAME);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "CHARACTER SERVER";
	wcex.hIconSm = LoadIconA(hInstance, NULL);
	RegisterClassExA(&wcex);

	std::pair<bool,std::string> ok1 = StartUp1();
	if( ok1.first == false )
	{
		MessageBoxA(NULL, ok1.second.c_str(), "StartUp1", MB_OK);
		return 0;
	}

	if( InitInstance(hInstance, nCmdShow) == FALSE )
		return 0;

	std::pair<bool,std::string> ok2 = StartUp2();
	if( ok2.first == false )
	{
		Destroy();
		MessageBoxA(NULL, ok2.second.c_str(), "StartUp2", MB_OK);
		return 0;
	}

	mySetWindowTitle();

	MSG msg;
	while( GetMessageA(&msg, NULL, 0, 0) )
	{
		if( !TranslateAcceleratorA(msg.hwnd, NULL, &msg) )
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	Destroy();
	return msg.wParam;
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowExA(0, "CHARACTER SERVER", "CHARACTER SERVER - ("__DATE__ __TIME__")", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 700, 450, NULL, NULL, hInstance, NULL);
	if( hWnd == NULL )
		return FALSE;

	gHwnd = hWnd;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_CREATE:
	break;
	case WM_CLOSE:
		PostQuitMessage(EXIT_SUCCESS);
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);

		RECT rect;
		GetClientRect(hWnd, &rect);

		FillRect(ps.hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

		if( NOutputTextMgr::GetObj() != NULL )
		{
			MaxOutputLineCnt = NOutputTextMgr::GetObj()->NOutputTextMgr::GetMaxLineCnt();
			for( unsigned int Cnt = 0, y = 300; y > 60; Cnt += 1, y -= 16 )
			{
				std::string msg = NOutputTextMgr::GetObj()->NOutputTextMgr::GetText(MaxOutputLineCnt - Cnt);
				if( msg.size() == 0 )
					break;

				TextOutA(ps.hdc, 10, y, msg.c_str(), msg.size());
			}
		}

		char szMsg[256];
		sprintf(szMsg, "[User Count: %d ][ User Connected: %d / %d ]  [ Acc Connected: %d ]  [ Zone Connected: %d ]", g_UserList.CUserList::GetCount(), g_UserStreamMgr.CStreamManager::GetConnectionCount(), g_UserStreamMgr.CStreamManager::GetFreeStreamNum(), g_AccountStreamMgr.CStreamManager::GetConnectionCount(), g_ZoneSvrStreamMgr.CStreamManager::GetConnectionCount());
		TextOutA(ps.hdc, 10, 366, szMsg, strlen(szMsg));

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_COMMAND:
	break;
	case WM_TIMER:
		if( MaxOutputLineCnt != NOutputTextMgr::GetObj()->NOutputTextMgr::GetMaxLineCnt() )
			InvalidateRect(hWnd, NULL, TRUE);
	break;
	case WM_RBUTTONDOWN:
		InvalidateRect(hWnd, NULL, TRUE);
	break;
	default:
		return DefWindowProcA(hWnd, message, wParam, lParam);
	break;
	};

	return 0;
}


std::pair<bool,std::string> StartUp1()
{
	if( !CMyMiniDumpUnhandledExceptionHandler::CreateInstance() )
		return std::pair<bool,std::string>(false, "CMyMiniDumpUnhandledExceptionHandler::CreateInstance()");

	if( !CEnterTraceLog::CreateInstance() )
		return std::pair<bool,std::string>(false, "CEnterTraceLog::CreateInstance()");

	if( !NOutputTextMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "NOutputTextMgr::CreateInstnace()");

	return std::pair<bool,std::string>(true, "good");
}


std::pair<bool,std::string> StartUp2()
{
	AccountServerIdentity();

	if( !CHsvrSchedulerIdentity::CreateInstance() )
		return std::pair<bool,std::string>(false, "CHsvrSchedulerIdentity::CreateInstance()");

	if( !CNetwork::CreateInstance() )
		return std::pair<bool,std::string>(false, "CNetwork::CreateInstance()");

	SetTimer(gHwnd, NULL, 1000, NULL);

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "==================================================");
	printf("MAX_CHARINFO_SLOT_COUNT %d", MAX_CHARINFO_SLOT_COUNT);

	char szModuleFileName[MAX_PATH] = {};
	GetModuleFileNameA(NULL, szModuleFileName, sizeof(szModuleFileName)-1);

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "build date(%s %s) \nModuleFileName - %s \n", __DATE__, __TIME__, szModuleFileName);

	CUserVerify* pUserVerify = CSingleton<CUserVerify>::getSingletonPtr();
	pUserVerify->CUserVerify::StartThread();

	g_mmResult = timeBeginPeriod(1);
	if( g_mmResult != TIMERR_NOERROR )
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "timeBeginPeriod failed, ret %u\n", g_mmResult);

	CNetwork* pNetwork = CNetwork::GetObj();
	pNetwork->CNetwork::InitializeNetwork();

	g_hStopEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
	if( g_hStopEvent == NULL )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "Create Stop Event fail! gle - %d", WSAGetLastError());

	gMsgInfo.CMsgInfo::AddString(0x000000, "bulid date [%s %s]  ", __DATE__, __TIME__);
	gMsgInfo.CMsgInfo::AddString(0x000000, "ModuleFileName - %s", szModuleFileName);

	g_characterConfig.CCharacterConfig::Open("character.config.txt");

	const char* szLOGAID = g_characterConfig.CInfoScript::GetInfo("LOGAID");
	g_dwLogUser = ( szLOGAID != NULL ) ? atoi(szLOGAID) : 0;

	const char* szADULTCHECK = g_characterConfig.CInfoScript::GetInfo("ADULT_CHECK");
	g_bEnableAdultCheck = ( szADULTCHECK != NULL ) ? atoi(szADULTCHECK) : 0;

	gMsgInfo.CMsgInfo::AddString(0x000000, "ADULT_CHECK %s", ( g_bEnableAdultCheck ) ? "(On)" : "(Off)");
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ADULT_CHECK %s\n", ( g_bEnableAdultCheck ) ? "(On)" : "(Off)");

	const char* szKEEPALIVE = g_characterConfig.CInfoScript::GetInfo("USERKEEP_BY_CH_PING");
	g_dwUSERKEEP_BY_CH_PING = ( szKEEPALIVE != NULL ) ? 60000 * atoi(szKEEPALIVE) : 60000 * 10;
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "USERKEEP_BY_CH_PING  %d min\n", g_dwUSERKEEP_BY_CH_PING / 60000);

	memset(&gconfig, 0, sizeof(gconfig));

	const char* sz3THJOB = g_characterConfig.CInfoScript::GetInfo("3TH_JOB");
	gconfig.b_IsThirdJob = ( sz3THJOB != NULL ) ? ( atoi(sz3THJOB) != 0 ) : false;
	gMsgInfo.CMsgInfo::AddString(0x0C0000, "3TH_JOB %s", ( gconfig.b_IsThirdJob ) ? "(On)" : "(Off)");

	const char* szSERVERTYPE = g_characterConfig.CInfoScript::GetInfo("SERVER_TYPE");
	if( szSERVERTYPE == NULL )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "failed! - Read [ SERVER_TYPE ] Field(character.config.txt)");
	gconfig.nServerType = atoi(szSERVERTYPE);

	const char* szMAXSLOT = g_characterConfig.CInfoScript::GetInfo("MAX_USER_SLOT");
	gconfig.nMax_User_Slot = ( szMAXSLOT != NULL ) ? atoi(szMAXSLOT) : MAX_CHARINFO_SLOT_COUNT;

	const char* szNORMALSLOT = g_characterConfig.CInfoScript::GetInfo("NORMAL_USER_SLOT");
	gconfig.nNoraml_User_Slot = ( szNORMALSLOT != NULL ) ? atoi(szNORMALSLOT) : MAX_CHARINFO_SLOT_COUNT;

	const char* szPREMIUMSLOT = g_characterConfig.CInfoScript::GetInfo("PREMIUM_USER_SLOT");
	gconfig.nPremium_User_Slot = ( szPREMIUMSLOT != NULL ) ? atoi(szPREMIUMSLOT) : MAX_CHARINFO_SLOT_COUNT;

	const char* szBILLSLOT = g_characterConfig.CInfoScript::GetInfo("BILL_USER_SLOT");
	gconfig.nBillUser_Slot = ( szBILLSLOT != NULL ) ? atoi(szBILLSLOT) : MAX_CHARINFO_SLOT_COUNT;

	const char* szPRODUCIBLESLOT = g_characterConfig.CInfoScript::GetInfo("DEFAULT_PRODUCIBLE_SLOT");
	gconfig.nProducibleSlot = ( szPRODUCIBLESLOT != NULL ) ? atoi(szPRODUCIBLESLOT) : MAX_CHARINFO_SLOT_COUNT;

	gMsgInfo.CMsgInfo::AddString(0x200000, "USER SLOT (Max: %d) (Normal: %d) (Bill: %d) (Premium: %d) (Producible: %d)", gconfig.nMax_User_Slot, gconfig.nNoraml_User_Slot, gconfig.nBillUser_Slot, gconfig.nPremium_User_Slot, gconfig.nProducibleSlot);
///
	const char* szPREMIUMSERVICE = g_characterConfig.CInfoScript::GetInfo("PREMIUM_SERVICE_TYPE");
	gconfig.nEnable_PremiumService = ( szPREMIUMSERVICE != NULL ) ? atoi(szPREMIUMSERVICE) : 0;

	if( !CPremiumServiceInfo::CreateInstance() )
		return std::pair<bool,std::string>(false, "CPremiumServiceInfo::CreateInstance()");

	if( !CPremiumServiceInfo::GetObj()->CPremiumServiceInfo::Init() )
		return std::pair<bool,std::string>(false, "InstanceCPremiumServiceInfo()->Init()");
///
	if( !CSingleton<CStartMap>::getSingletonPtr()->CStartMap::Initialize() )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "character.startmap.txt is not valid format. Please check it.");
///
	gPcbangDBReloadStartTM = timeGetTime();
	const char* szPCBANGRELOADINTERVAL = g_characterConfig.CInfoScript::GetInfo("PCBANGDB_RELOAD_TIME_INTERVAL_PER_MINUTES");
	gPcbangDBReloadTimeIntervalPerMin = ( szPCBANGRELOADINTERVAL ) ? 60000 * atoi(szPCBANGRELOADINTERVAL) : 0;

	CEnterTraceLog::GetObj()->CEnterTraceLog::MessagePrint("pcbonus DB Connect success. reload time %d\n", gPcbangDBReloadTimeIntervalPerMin);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "pcbonus DB Connect success. reload time %d\n", gPcbangDBReloadTimeIntervalPerMin);
///
	const char* szPREMIUMDBPW = g_characterConfig.CInfoScript::GetInfo("PREMIUM_SVC_DB_PW");
	if( szPREMIUMDBPW == NULL )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "failed!  -Read [ PREMIUM_SVC_DB_PW ] Field(character.config.txt)");

	char szDBPW[256] = {};
	Decrypt(szPREMIUMDBPW, (unsigned char*)szDBPW);

	if( !CSingleton<CPremiumServiceDB>::getSingletonPtr()->CDatabase::Connect("premiumservice.dsn", szDBPW) )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "connect failed :premiumservice.dsn");

	std::pair<bool,std::string> ipbonusRet = CSingleton<CPremiumServiceDB>::getSingletonPtr()->CPremiumServiceDB::InitIPBonusList();
	if( !ipbonusRet.first )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, ipbonusRet.second.c_str());

	if( !CSingleton<CPremiumServiceDB>::getSingletonPtr()->CPremiumServiceDB::InitPCBonusInit() )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "PCBonus DB Init failed with premiumservice.dsn");
///
	if( !CSingleton<CForbiddenName>::getSingletonPtr()->CForbiddenName::readForbiddenWordFile("character.preventName.txt") )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "cannot read character.preventName.txt or invalid format");

	if( !CSingleton<CForbiddenName>::getSingletonPtr()->CForbiddenName::readAsciiTableFile("character.preventAscii.txt") )
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "FORBIDDEN_NAME disabled\n");
///
	const char* szGLOBALDBPW = g_characterConfig.CInfoScript::GetInfo("GLOBAL_DBPW");
	if( szGLOBALDBPW == NULL )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "Set Database Password! - GLOBAL_DBPW Field(character.config.txt)");

	char global_dbpw[256] = {};
	Decrypt(szGLOBALDBPW, (unsigned char*)global_dbpw);
///
	const char* szGAMEDBPW = g_characterConfig.CInfoScript::GetInfo("GAME_DBPW");
	if( szGAMEDBPW == NULL )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "Set Database Password! - GAME_DBPW Field(character.config.txt)");

	char game_dbpw[256] = {};
	Decrypt(szGAMEDBPW, (unsigned char*)game_dbpw);
///
	g_dwMyPublicIP = pNetwork->CNetwork::GetLocalIP(true);
	g_dwMyPrivateIP = pNetwork->CNetwork::GetLocalIP(false);
	g_dwLocalIP = ( g_dwMyPublicIP != INADDR_ANY ) ? g_dwMyPublicIP : g_dwMyPrivateIP;
	if( g_dwLocalIP == INADDR_ANY )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "there's no IP address in this machine\n");

	char szIP[100] = {};
	pNetwork->CNetwork::GetTextIP(g_dwLocalIP, szIP);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CHARACTER SERVER LOCAL IP : %s", szIP);
///
	CIPInfoDB* pIPInfoDB = CSingleton<CIPInfoDB>::getSingletonPtr();
	pIPInfoDB->CIPInfoDB::SetPwd(game_dbpw);
	if( !pIPInfoDB->CIPInfoDB::Connect() )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "IpInfo DB connect failed.");
	gMsgInfo.CMsgInfo::AddString(0x143232, "IPINFO           DB CONNECT  OK!");
	pIPInfoDB->CIPInfoDB::InitMapInfoList();
///
	if( DBProxy<CGlobalInfoDB,4>::connect("global.dsn", global_dbpw) == FALSE )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "GlobalInfo DB connect failed.");

	gMsgInfo.CMsgInfo::AddString(0x141414, "GLOBALINFO DB CONNECT  OK!");
	DBProxy<CGlobalInfoDB,4>::instance(0)->CGlobalInfoDB::InitServerInfoList(false);
///
	CServerInfoList* pServerInfoList = CSingleton<CServerInfoList>::getSingletonPtr();
	g_nLocalSID = pServerInfoList->CServerInfoList::GetSID(g_dwLocalIP, SERVERTYPE_CHARACTER);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CHARACTER SERVER Local SID : %d", g_nLocalSID);

	if( !pServerInfoList->CServerInfoList::GetServerInfo(&gLocalServerInfo, g_nLocalSID) )
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Cannot read local server information\n");

	int nSID[30];
	int nCount = pServerInfoList->CServerInfoList::GetSID(g_nLocalSID, nSID);

	SSERVERINFO serverInfo[30] = {};

	for( int i = 0; i < nCount; ++i )
		pServerInfoList->CServerInfoList::GetServerInfo(&serverInfo[i], nSID[i]);

	CZoneServerInfoList* pZoneServerInfoList = CSingleton<CZoneServerInfoList>::getSingletonPtr();
	for( int i = 0; i < nCount; ++i )
	{
		pZoneServerInfoList->CZoneServerInfoList::AddZoneServerInfo(&serverInfo[i]);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Zone[%d] %s\n", i, serverInfo[i].m_szIP);
	}
///
	CCharacterDB* pCharacterDB = CSingleton<CCharacterDB>::getSingletonPtr();
	pCharacterDB->CCharacterDBBase::SetPwd(game_dbpw);
	if( !pCharacterDB->CCharacterDBBase::Connect() )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "Character DB connect failed.");

	gMsgInfo.CMsgInfo::AddString(0x000000, "CHARACTER  DB CONNECT  OK!");

	pCharacterDB->CCharacterDBBase::VeryfyConnection();
	g_bUsingCharacterPassword = pCharacterDB->CCharacterDB::IsUsingCharacterPassword();
	gMsgInfo.CMsgInfo::AddString(0x000000, "USING CHARACTER PASSWORD (%s)", ( g_bUsingCharacterPassword ) ? "ENABLE" : "DISALBE");
///
	if( g_characterConfig.CInfoScript::GetInfo("MODEPVP") )
	{
		CSingleton<CPVPCharacterDB>::getSingletonPtr()->CCharacterDBBase::SetPwd(game_dbpw);
		CSingleton<CPVPCharacterDB>::getSingletonPtr()->CCharacterDBBase::Connect();

		CSingleton<CPvPPointDB>::getSingletonPtr()->CPvPPointDB::SetPwd(game_dbpw);
		CSingleton<CPvPPointDB>::getSingletonPtr()->CPvPPointDB::Connect();

		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "MODE : MOVE TO PVP");
	}
///
	CSingleton<CCharacterLogDB>::getSingletonPtr()->CCharacterLogDB::SetPwd(game_dbpw);
	if( !CSingleton<CCharacterLogDB>::getSingletonPtr()->CCharacterLogDB::Connect() )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "CharacterLog DB connect failed.");

	const char* szGRAVITYIP = g_characterConfig.CInfoScript::GetInfo("GRAVITY_PUBLIC_IP");
	if( szGRAVITYIP != NULL )
	{
		g_dwGravityPublicIP = pNetwork->CNetwork::GetDWORDIP(szGRAVITYIP);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Gravity Public IP: %s (%d)", szGRAVITYIP, g_dwGravityPublicIP);
	}
	else
	{
		g_dwGravityPublicIP = pNetwork->CNetwork::GetDWORDIP("119.192.146.203");
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Gravity Public IP: 119.192.146.203 (%d)", g_dwGravityPublicIP);
	}

	const char* szENABLEDELETECHAR = g_characterConfig.CInfoScript::GetInfo("ENABLE_DELETE_CHARACTER");
	g_bEnableDelChar = ( szENABLEDELETECHAR != NULL ) ? ( atoi(szENABLEDELETECHAR) != 0 ) : true;

	const char* szENABLEMAKECHAR = g_characterConfig.CInfoScript::GetInfo("ENABLE_MAKE_CHARACTER");
	g_bEnableMakeChar = ( szENABLEMAKECHAR != NULL ) ? ( atoi(szENABLEMAKECHAR) != 0 ) : true;

	const char* szIsEnableDelChar = ( g_bEnableDelChar ) ? "ENBALE" : "DISABLE";
	const char* szIsEnableMakeChar = ( g_bEnableMakeChar ) ? "ENBALE" : "DISABLE";
	gMsgInfo.CMsgInfo::AddString(0x000000, "%s_DELETE_CHARACTER , %s_MAKE_CHARACTER", szIsEnableDelChar, szIsEnableMakeChar);

	/////////////////////////////////////////////////////////////////////////////
	const int ASYNCPROCESS_THREADS = 5;
	const int ASYNCPROCESS_POOL_COUNT = 100000;

	g_AsyncProcessMgr.CAsyncProcessMgr::Create(ASYNCPROCESS_THREADS, ASYNCPROCESS_POOL_COUNT);

	SYSTEM_INFO si;
	GetSystemInfo(&si);
	const int COMPLETIONPORT_THREADS = min(8 * si.dwNumberOfProcessors, 64);

	g_compltport.CCompletionPort::Create(COMPLETIONPORT_THREADS);
	/////////////////////////////////////////////////////////////////////////////
	std::list<CProcess*> process_list;
	/////////////////////////////////////////////////////////////////////////////
	const int ZONE_NETWORK_BUFSIZE = 3000000;
	const int ZONE_PROCESS_OBJ_NUM = 30;

	g_ZoneSvrProcessFactory.CProcessFactory<CZoneSvrProcess>::CreateProcessList(&process_list, ZONE_PROCESS_OBJ_NUM);
	g_ZoneSvrStreamMgr.CStreamManager::Create(process_list, ZONE_NETWORK_BUFSIZE, ZONE_NETWORK_BUFSIZE, &g_compltport, false);

	const DWORD ZONE_IP = ( DBProxy<CGlobalInfoDB,4>::instance(0)->CGlobalInfoDB::IsColumnPrivateAdded() ) ? gLocalServerInfo.m_dwPrivateIP : inet_addr("0.0.0.0");
	const WORD ZONE_PORT = ( DBProxy<CGlobalInfoDB,4>::instance(0)->CGlobalInfoDB::IsColumnPrivateAdded() ) ? (WORD)gLocalServerInfo.m_nPrivatePort : 7000;

	if( !g_ZoneSvrStreamMgr.CZsvrStreamMgr::Listen(ZONE_PORT, 5, 1800000, ZONE_IP) )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "ZSVR listen Error %s:%d", NIPAddapter(g_ZoneSvrStreamMgr.CZsvrStreamMgr::GetListenIPAddr()), g_ZoneSvrStreamMgr.CZsvrStreamMgr::GetListenPortNum());

	gMsgInfo.CMsgInfo::AddString(0x646400, " Zone Listener : %d port open", ZONE_PORT);
	/////////////////////////////////////////////////////////////////////////////
	process_list.clear();
	/////////////////////////////////////////////////////////////////////////////
	const int ACC_NETWORK_BUFSIZE = 30000000;
	const int ACC_PROCESS_OBJ_NUM = 1;

	g_AccountProcessFactory.CProcessFactory<CAccountProcess>::CreateProcessList(&process_list, ACC_PROCESS_OBJ_NUM);
	g_AccountStreamMgr.CStreamManager::Create(process_list, ACC_NETWORK_BUFSIZE, ACC_NETWORK_BUFSIZE, &g_compltport, true);

	SSERVERINFO account_server_info;
	pServerInfoList->CServerInfoList::GetServerInfo(&account_server_info, pServerInfoList->CServerInfoList::GetSID(g_dwLocalIP, SERVERTYPE_CHARACTER));
	pServerInfoList->CServerInfoList::GetServerInfo(&account_server_info, account_server_info.m_nPrimaryDestnation);
	const char* szACC_IP = ( DBProxy<CGlobalInfoDB,4>::instance(0)->CGlobalInfoDB::IsColumnPrivateAdded() ) ? account_server_info.m_szPrivateIP : account_server_info.m_szIP;
	const WORD ACC_PORT = ( DBProxy<CGlobalInfoDB,4>::instance(0)->CGlobalInfoDB::IsColumnPrivateAdded() ) ? (WORD)account_server_info.m_nPrivatePort : account_server_info.m_nPort;

	g_AccountStreamMgr.CStreamManager::Connect(szACC_IP, ACC_PORT, 3600000);

	gMsgInfo.CMsgInfo::AddString(0x646400, "Account Connect to %d port", ACC_PORT);
	/////////////////////////////////////////////////////////////////////////////
	process_list.clear();
	/////////////////////////////////////////////////////////////////////////////
	const int USER_NETWORK_BUFSIZE = 10000;
	const int USER_PROCESS_OBJ_NUM = 5000;

	g_UserProcessFactory.CProcessFactory<CUserProcess>::CreateProcessList(&process_list, USER_PROCESS_OBJ_NUM);
	g_UserStreamMgr.CStreamManager::Create(process_list, USER_NETWORK_BUFSIZE, USER_NETWORK_BUFSIZE, &g_compltport, false);

	const DWORD USER_IP  = ( DBProxy<CGlobalInfoDB,4>::instance(0)->CGlobalInfoDB::IsColumnPrivateAdded() ) ? gLocalServerInfo.m_dwIP : inet_addr("0.0.0.0");
	const WORD USER_PORT = (WORD)gLocalServerInfo.m_nPort;

	if( !g_UserStreamMgr.CUserStreamMgr::Listen(USER_PORT, 100, 60000, USER_IP) )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "ZSVR listen Error %s:%d", NIPAddapter(g_UserStreamMgr.CUserStreamMgr::GetListenIPAddr()), g_UserStreamMgr.CUserStreamMgr::GetListenPortNum());

	gMsgInfo.CMsgInfo::AddString(0x646400, "User Listener : %d port open", USER_PORT);
	/////////////////////////////////////////////////////////////////////////////
	process_list.clear();
	/////////////////////////////////////////////////////////////////////////////

	gMsgInfo.CMsgInfo::AddString(0x8080FF, "#ACCEPT_ENTER:%3d #CHARACTER_INFO:%3d", 7, 116);
	gMsgInfo.CMsgInfo::AddString(0x46461E, "######## ready to accept clients ########");

	InvalidateRect(gHwnd, NULL, FALSE);
	_beginthread(&UpdateInfoThread, 0, NULL);
	_beginthread(&PcbangDBReload, 0, NULL);

	return std::pair<bool,std::string>(true, "good");
}


void Destroy()
{
	CSingleton<CUserVerify>::getSingletonPtr()->CUserVerify::EndThread();

	DisplayStatusMessage("Waiting for all objects to be destroyed...UserStreamMgr.Destory()");
	g_bProcessPermit = false;
	g_ZoneSvrStreamMgr.CStreamManager::Destroy();
	DisplayStatusMessage("Waiting for all objects to be destroyed......");

	Sleep(10);

	DisplayStatusMessage("Waiting for all objects to be destroyed.........AccountStreamMgr.Destroy()");
	g_AccountStreamMgr.CStreamManager::Destroy();
	DisplayStatusMessage("Waiting for all objects to be destroyed............");

	DisplayStatusMessage("Waiting for all objects to be destroyed..............ZoneSvrStreamMgr.Destroy()");
	g_ZoneSvrStreamMgr.CStreamManager::Destroy();
	DisplayStatusMessage("Waiting for all objects to be destroyed..........................................");

	Sleep(10);

	g_compltport.CCompletionPort::Destroy();
	g_AsyncProcessMgr.CAsyncProcessMgr::Destroy();
	CNetwork::GetObj()->CNetwork::CleanupNetwork();

	g_mmResult = timeEndPeriod(1);
	if( g_mmResult != TIMERR_NOERROR )
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "timeEndPeriod failed, ret %u\n", g_mmResult);

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "server terminated -------------------");

	CNetwork::DestroyInstance();
	CEnterTraceLog::DestroyInstance();
	CHsvrSchedulerIdentity::DestroyInstance();
	NOutputTextMgr::DestroyInstance();
	CMyMiniDumpUnhandledExceptionHandler::DestroyInstance();
}


void __cdecl UpdateInfoThread(void* lpVoid)
{
	timeGetTime();
	timeGetTime();

	//NOTE: 45 line gap here

	DWORD dwBeginTime = timeGetTime();

	while( g_bProcessPermit )
	{
		DWORD loopstart = timeGetTime();

		time_t currentTime;
		time(&currentTime);
		strftime(g_szTime, sizeof(g_szTime), "%Y-%m-%d %H:%M:%S", localtime(&currentTime));

		timeGetTime();

		//NOTE: 80 line gap here

		if( gPcbangDBReloadTimeIntervalPerMin != 0 && gPcbangDBReloadTimeIntervalPerMin < int(timeGetTime() - dwBeginTime) )
		{
			dwBeginTime = timeGetTime();

			CPremiumServiceDB::getSingletonPtr()->CPremiumServiceDB::ReloadIPBonusList();
		}

		//NOTE: 30 line gap here

		timeGetTime();

		DWORD loopend = timeGetTime();
		DWORD delta = loopstart - loopend; //FIXME: wrong order, value is negative

		if( delta < 10 )
			Sleep(10 - delta);
	}
}


void __cdecl PcbangDBReload(void* lpParam)
{
	if( gPcbangDBReloadTimeIntervalPerMin <= 0 )
		return;

	while( 1 )
	{
		do
			gPcBangDBReloadEndTM = timeGetTime();
		while( gPcBangDBReloadEndTM - gPcbangDBReloadStartTM <= gPcbangDBReloadTimeIntervalPerMin );

		static CPremiumServiceDB* pPremiumServiceDB = CSingleton<CPremiumServiceDB>::getSingletonPtr();
		pPremiumServiceDB->CPremiumServiceDB::ReloadPCBangIPList();

		gPcbangDBReloadStartTM = timeGetTime();
	}
}


void MakeCHARACTER_INFO(const SCHARINFO* pCharInfo, CHARACTER_INFO* pCharacter_Info_target)
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
	pCharacter_Info_target->hp = pCharInfo->m_nHp;
	pCharacter_Info_target->maxsp = static_cast<short>(pCharInfo->m_nMaxSp) + pCharInfo->m_nMaxSp * pCharacter_Info_target->Int / 100;
	pCharacter_Info_target->maxhp = pCharInfo->m_nMaxHp + pCharInfo->m_nMaxHp * pCharacter_Info_target->Vit / 100;

	if( pCharacter_Info_target->sp > pCharacter_Info_target->maxsp )
		pCharacter_Info_target->sp = pCharacter_Info_target->maxsp;

	if( pCharacter_Info_target->hp > pCharacter_Info_target->maxhp )
		pCharacter_Info_target->hp = pCharacter_Info_target->maxhp;

//	pCharacter_Info_target->haircolor = static_cast<unsigned char>(pCharInfo->m_nHairColor); //FIXME
	pCharacter_Info_target->bIsChangedCharName = static_cast<short>(pCharInfo->m_bIsChangedCharName);
	pCharacter_Info_target->nRobe = pCharInfo->m_nRobe;
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
