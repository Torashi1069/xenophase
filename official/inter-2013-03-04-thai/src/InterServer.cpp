#include "CEntryQueueMgr.h"
#include "CGVar.h"
#include "CIsvrSchedulerIdentity.h"
#include "CMakerRankMgr.h"
#include "ExpParameter.h"
#include "FriendDB.h"
#include "IGuildInfoDB.h"
#include "IGuildMgr.h"
#include "InterServer.h"
#include "MServer.h"
#include "MServerLog.h"
#include "PartyMgr.h"
#include "ProcessThread.h"
#include "ServerExpInfoMgr.h"
#include "TestButton.h"
#include "UserLogDB.h"
#include "UserLogMgr.h"
#include "UserMgr.h"
#include "Common/ServerIdentity.h"
#include "Instant Map/InstantMapMgr.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "NetLib/Acceptor.h"
#include "NetLib/AsyncStream.h"
#include "ServerManager/CMsvrAcceptHandler.h"
#include "ServerManager/CMsvrAcceptThread.h"
#include "ServerManager/CMsvrMgr.h"
#include "Statistics/StatisticsMgr.h"
#include "Zsvr/CZsvrAcceptHandler.h"
#include "Zsvr/CZsvrAcceptThread.h"
#include "Zsvr/CZsvrMgr.h"
#include "shared/CProgrammerSupportLog.h"
#include "shared/CMapInfoMgr.h"
#include "shared/MyMiniDumpUnhandledExceptionHandler.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/NTraceLog.h"
#include "shared/ServerInfo.h"
#include "shared/shared.h"
#include "shared/NSystem/NIPAddr.h"
#include "shared/N2System/N2IDGenerator36.h"
#include "shared/N2System/N2SystemMgr.h"
#include "shared/N2System/DBLog/N2DBLogMgr.h"
#include "shared/N3System/N3DataTransferMgr.h"
#include "shared/N3System/N3MessageMgr.h"


/// globals
CIGuildInfoDB& g_IGuildDB = VTOR<CIGuildInfoDB>(DetourFindFunction(EXEPATH(), "g_IGuildDB"));
CIGuildSkillDB& g_IGuildSkillDB = VTOR<CIGuildSkillDB>(DetourFindFunction(EXEPATH(), "g_IGuildSkillDB"));
CExpParameter& g_expParameter = VTOR<CExpParameter>(DetourFindFunction(EXEPATH(), "g_expParameter"));
CPartyMgr& g_groupMgr = VTOR<CPartyMgr>(DetourFindFunction(EXEPATH(), "g_groupMgr"));
CServerInfo& g_serverInfo = VTOR<CServerInfo>(DetourFindFunction(EXEPATH(), "g_serverInfo"));
CUserMgr& g_userMgr = VTOR<CUserMgr>(DetourFindFunction(EXEPATH(), "g_userMgr"));
CMClient& g_mServer = VTOR<CMClient>(DetourFindFunction(EXEPATH(), "g_mServer"));
CUserLogMgr& g_UserLogMgr = VTOR<CUserLogMgr>(DetourFindFunction(EXEPATH(), "g_UserLogMgr"));
CUserLogDB& g_UserLogDB = VTOR<CUserLogDB>(DetourFindFunction(EXEPATH(), "g_UserLogDB"));
CFriendDB& g_FriendDB = VTOR<CFriendDB>(DetourFindFunction(EXEPATH(), "g_FriendDB"));
CMakerRankMgr& g_MakerRankMgr = VTOR<CMakerRankMgr>(DetourFindFunction(EXEPATH(), "g_MakerRankMgr"));
BOOL& g_SendChkProrcessTime = VTOR<int>(DetourFindFunction(EXEPATH(), "g_SendChkProrcessTime"));
DWORD& g_sleep = VTOR<DWORD>(DetourFindFunction(EXEPATH(), "g_sleep"));
BOOL& g_isGuildAllSend = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isGuildAllSend"));
BOOL& g_bSetUserCounter = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_bSetUserCounter"));
BOOL& g_isPacketLog = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isPacketLog"));
BOOL& g_isBroadCastLog = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isBroadCastLog"));
int& g_FunctionUniqueCnt = VTOR<int>(DetourFindFunction(EXEPATH(), "g_FunctionUniqueCnt"));
const char* const g_infFile = ".\\Inter.inf";
const char CHARACTER_DSN_FILE[] = "character.dsn";
const char LOG_DSN_FILE[] = "log.dsn";
const char GLOBALINFO_DSN_FILE[] = "globalinfo.dsn";
const char SCRIPT_DSN_FILE[] = "script.dsn";
const char IPINFO_DSN_FILE[] = "ipinfo.dsn";

/// locals
static HWND& ghWnd = VTOR<HWND>(DetourFindFunction(EXEPATH(), "ghWnd"));
static BOOL& g_isGUILDWAR = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isGUILDWAR")); // = TRUE;
static int& g_MaxUser = VTOR<int>(DetourFindFunction(EXEPATH(), "g_MaxUser"));
static int& g_MaxParty = VTOR<int>(DetourFindFunction(EXEPATH(), "g_MaxParty"));
static int& g_MaxGuild = VTOR<int>(DetourFindFunction(EXEPATH(), "g_MaxGuild"));
static bool& g_bOutput = VTOR<bool>(DetourFindFunction(EXEPATH(), "g_bOutput"));
static BOOL& g_bInterServerClose = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_bInterServerClose"));
static BOOL& g_isExtendDB = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isExtendDB"));
static int& MaxOutputLineCnt = VTOR<int>(DetourFindFunction(EXEPATH(), "MaxOutputLineCnt")); // = -1;
static CTestButton& ToggleButtonCriticalLog = VTOR<CTestButton>(DetourFindFunction(EXEPATH(), "ToggleButtonCriticalLog")); // ToggleButtonCriticalLog((HMENU)20); // 225
static CTestButton& ToggleButtonTraceLog = VTOR<CTestButton>(DetourFindFunction(EXEPATH(), "ToggleButtonTraceLog")); // ToggleButtonTraceLog((HMENU)21); // 226
static int& gViewMode = VTOR<int>(DetourFindFunction(EXEPATH(), "gViewMode"));


/// forward declarations
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
std::pair<bool,std::string> Startup();
void CleanUp();


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEXA wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_CLASSDC | CS_DBLCLKS;
	wc.lpfnWndProc = &WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandleA(NULL);
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Ragnarok";
	wc.hIconSm = NULL;
	RegisterClassExA(&wc);

	char WindowsName[MAX_PATH] = "INTER";
	_snprintf(WindowsName, countof(WindowsName), "INTER - INTERNATIONAL Ep%d.%d.X (%s)", 14, 2, __DATE__);

	HWND hWnd = CreateWindowExA(0, "Ragnarok", WindowsName, WS_OVERLAPPEDWINDOW, 100, 100, 600, 400, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	if( hWnd == NULL )
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetTimer(hWnd, NULL, 1000, NULL);
	ghWnd = hWnd;

	return TRUE;
}


void OnWM_PAINT(HWND in_hWnd)
{
	PAINTSTRUCT ps;
	BeginPaint(in_hWnd, &ps);

	RECT rect;
	GetClientRect(in_hWnd, &rect);

	FillRect(ps.hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	if( NOutputTextMgr::GetObj() != NULL )
	{
		MaxOutputLineCnt = NOutputTextMgr::GetObj()->NOutputTextMgr::GetMaxLineCnt();
		for( int Cnt = 0, y = 300; y >= 60; ++Cnt, y -= 16 )
		{
			std::string msg = NOutputTextMgr::GetObj()->NOutputTextMgr::GetText(MaxOutputLineCnt - Cnt);
			if( msg.size() == 0 )
				break;

			TextOutA(ps.hdc, 10, y, msg.c_str(), msg.size());
		}
	}

	char buf[1024] = {};

	sprintf_s(buf, countof(buf), "ZSVR : %d", CZsvrMgr::GetObj()->CZServerMgr::GetZoneNumber());
	TextOutA(ps.hdc, 10, 316, buf, strlen(buf));

	sprintf_s(buf, countof(buf), "SVRMGR : %d", CMsvrMgr::GetObj()->CMsvrMgr::GetClientNumber());
	TextOutA(ps.hdc, 10, 332, buf, strlen(buf));

	sprintf_s(buf, countof(buf), "no");
	if( NCriticalErrorLog::GetObj()->NFileLog::GetOutput() )
		sprintf_s(buf, countof(buf), "yes");
	TextOutA(ps.hdc, ToggleButtonCriticalLog.CTestButton::GetX() + ToggleButtonCriticalLog.CTestButton::GetWidth() + 5, ToggleButtonCriticalLog.CTestButton::GetY(), buf, strlen(buf));

	sprintf_s(buf, countof(buf), "no");
	if( Trace == &TraceF )
		sprintf_s(buf, countof(buf), "yes");
	TextOutA(ps.hdc, ToggleButtonTraceLog.CTestButton::GetX() + ToggleButtonTraceLog.CTestButton::GetWidth() + 5, ToggleButtonTraceLog.CTestButton::GetY(), buf, strlen(buf));

	EndPaint(in_hWnd, &ps);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_CREATE:
	{
		CREATESTRUCTA* cs = reinterpret_cast<CREATESTRUCTA*>(lParam);
		int x = LOWORD(GetDialogBaseUnits());
		int y = HIWORD(GetDialogBaseUnits());
		x += 400;
		ToggleButtonCriticalLog.CTestButton::OnCreate(hWnd, cs->hInstance, x, y, 80, 21, "critical log");
		ToggleButtonTraceLog.CTestButton::OnCreate(hWnd, cs->hInstance, x, y + 22, 80, 21, "trace log");
	}
	break;
	case WM_COMMAND:
		switch( wParam )
		{
		case 20: // ToggleButtonCriticalLog
			NCriticalErrorLog::GetObj()->NFileLog::SetOutput(!NCriticalErrorLog::GetObj()->NFileLog::GetOutput());
			InvalidateRect(hWnd, NULL, FALSE);
		break;
		case 21: // ToggleButtonTraceLog
			Trace = ( Trace == &TraceF ) ? &TraceN : &TraceF;
			InvalidateRect(hWnd, NULL, FALSE);
		break;
		};
	break;
	case WM_CHAR:
		++gViewMode;
		if( gViewMode > 1 )
			gViewMode = 0;
	break;
	case WM_TIMER:
		if( MaxOutputLineCnt != NOutputTextMgr::GetObj()->NOutputTextMgr::GetMaxLineCnt() )
			InvalidateRect(hWnd, NULL, TRUE);
	break;
	case WM_RBUTTONDBLCLK:
		g_SendChkProrcessTime = TRUE;
	break;
	case WM_PAINT:
		OnWM_PAINT(hWnd);
	break;
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
	break;
	case WM_MBUTTONDOWN:
		if( CIGuildMgr::GetObj() != NULL )
		{
			unsigned long GDID = GetPrivateProfileIntA("DEBUG", "OUTGUILDINFO", 0, g_infFile);
			if( GDID == 0 )
				return 0;
			CIGuildMgr::GetObj()->CIGuildMgr::OutPutGuildInfo(GDID);
		}
	break;
	case WM_RBUTTONDOWN:
		InvalidateRect(hWnd, NULL, TRUE);
	break;
	};

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if( !CMyMiniDumpUnhandledExceptionHandler::CreateInstance(NULL) )
		return 0;

	if( !NCriticalErrorLog::CreateInstance() )
		return 0;

	if( !NTraceLog::CreateInstance() )
		return 0;

	NTraceLog::GetObj()->NFileLog::SetOutput(true);

	HANDLE hMutex = CreateMutexA(NULL, FALSE, "Global\\Ragnarok Inter Server");
	if( WaitForSingleObject(hMutex, 0) != WAIT_OBJECT_0 )
	{
		MessageBoxA(NULL, "Another Inter Server is Still Executing", NULL, MB_OK);
		return 0;
	}

	if( !InitInstance(hInstance, nCmdShow) )
		return 0;

	std::pair<bool,std::string> ret = Startup();
	if( !ret.first )
	{
		MessageBoxA(NULL, ret.second.c_str(), "Startup()", MB_OK);
		return 0;
	}

	_ACCEPT_PARM ap;
	ap.ip = (DWORD)g_serverInfo.CServerInfo::GetServerPrivateIPAddr(g_serverInfo.CServerInfo::GetLocalServerID());
	if( ap.ip == INADDR_ANY )
		g_isExtendDB = FALSE;

	if( g_isExtendDB )
	{
		ap.port = (short)g_serverInfo.CServerInfo::GetServerPrivatePort(g_serverInfo.CServerInfo::GetLocalServerID());
	}
	else
	{
		ap.ip = (DWORD)g_serverInfo.CServerInfo::GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS);
		ap.port = (short)g_serverInfo.CServerInfo::GetLocalPort();
	}

	char buffer[256];
	GetPrivateProfileStringA("ETC", "DB", "", buffer, 64, g_infFile);

	char dbPWD[256] = {};
	Decrypt(buffer, (unsigned char*)dbPWD);

	std::string logDBconnectionStr = std::string("FILEDSN=.\\") + std::string(LOG_DSN_FILE) + std::string(";PWD=") + std::string(dbPWD);
	int WorkThreadNum = GetPrivateProfileIntA("SETTING", "database log work thread number", 2, g_infFile);

	if( !N2DBLogMgr::CreateInstance(WorkThreadNum, logDBconnectionStr) )
	{
		MessageBoxA(NULL, "DB Log Manager Error", "N2DBLogMgr", MB_OK);
		return 0;
	}

	if( !CInstantMapMgr::CreateInstance() )
	{
		MessageBoxA(NULL, "Create Instance Error", "InstantMapMgr", MB_OK);
		return 0;
	}

	if( !CMemorialDungeonMgr::CreateInstance() )
	{
		MessageBoxA(NULL, "Create Instance Error", "MemorialDungeonMgr", MB_OK);
		return 0;
	}

	if( !CProcessThread::CreateInstance() )
	{
		MessageBoxA(NULL, "Create Instance Error", "ProcessThread", MB_OK);
		return 0;
	}

	if( !CStatisticsMgr::CreateInstance() )
	{
		MessageBoxA(NULL, "Create Instance Error", "StatisticsMgr", MB_OK);
		return 0;
	}

	if( !CZsvrAcceptHandler::CreateInstance() )
	{
		MessageBoxA(NULL, "Create Instance Error", "CZsvrAcceptHandler", MB_OK);
		return 0;
	}

	CZsvrAcceptHandler::GetObj()->CZsvrAcceptHandler::Init(( g_isExtendDB != FALSE ), 40);

	if( !CZsvrAcceptThread::CreateInstance(ap.ip, ap.port) )
	{
		MessageBoxA(NULL, "Create Instance Error", "CZsvrAcceptThread", MB_OK);
		return 0;
	}

	if( !CMsvrAcceptHandler::CreateInstance() )
	{
		MessageBoxA(NULL, "Create Instance Error", "CMsvrAcceptHandler", MB_OK);
		return 0;
	}

	CMsvrAcceptHandler::GetObj()->CMsvrAcceptHandler::Init(40);

	{// scope
	char buffer[260] = "127.0.0.1";
	GetPrivateProfileStringA("Server Manager", "ip", "127.0.0.1", buffer, countof(buffer), g_infFile);
	NIPAddr ManagerAcceptIPAddr(buffer);

	int ManagerAcceptPort = GetPrivateProfileIntA("Server Manager", "port", 4000, g_infFile);

	if( ManagerAcceptIPAddr == NIPAddr("127.0.0.1") )
	{
		ManagerAcceptIPAddr = NIPAddr(g_serverInfo.CServerInfo::GetServerIPAddr(g_serverInfo.CServerInfo::GetLocalServerID()));
		ManagerAcceptPort = g_serverInfo.CServerInfo::GetServerPort(g_serverInfo.CServerInfo::GetLocalServerID());
	}

	if( ManagerAcceptIPAddr == CZsvrAcceptThread::GetObj()->CZsvrAcceptThread::GetIPAddr() && ManagerAcceptPort == CZsvrAcceptThread::GetObj()->CZsvrAcceptThread::GetPort() )
	{
		char buffer[1024] = {};
		_snprintf_s(buffer, countof(buffer), _TRUNCATE, "duplicate accept ip/port found\nZSVR %s(%d)\nMGR %s(%d)", NIPAddapter(CZsvrAcceptThread::GetObj()->CZsvrAcceptThread::GetIPAddr()), CZsvrAcceptThread::GetObj()->CZsvrAcceptThread::GetPort(), NIPAddapter(ManagerAcceptIPAddr), ManagerAcceptPort);
		MessageBoxA(NULL, buffer, "MGR Accept Thread", MB_OK);
		ExitProcess(EXIT_SUCCESS);
	}

	if( !CMsvrAcceptThread::CreateInstance(ManagerAcceptIPAddr, ManagerAcceptPort) )
	{
		MessageBoxA(NULL, "Create Instance Error", "CMsvrAcceptThread", MB_OK);
		ExitProcess(EXIT_SUCCESS);
	}
	}// scope

	if( !N2DBLogMgr::GetObj()->N2DBLogMgr::Start() )
	{
		MessageBoxA(NULL, "Start() Error", "N2DBLogMgr", MB_OK);
		return 0;
	}

	if( !CProcessThread::GetObj()->CProcessThread::Start() )
	{
		MessageBoxA(NULL, "Start() Error", "ProcessThread", MB_OK);
		return 0;
	}

	if( !CZsvrAcceptThread::GetObj()->CZsvrAcceptThread::Start() )
	{
		MessageBoxA(NULL, "Start() Error", "InstanceCZsvrAcceptThread", MB_OK);
		return 0;
	}

	if( !CMsvrAcceptThread::GetObj()->CMsvrAcceptThread::Start() )
	{
		MessageBoxA(NULL, "Start() Error", "CMsvrAcceptThread", MB_OK);
		return 0;
	}

	g_bOutput = true;

	MSG msg = {};
	int SleepCounter = 0;

	while( msg.message != WM_QUIT )
	{
		if( PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else
		{
			if( SleepCounter++ > 100 )
			{
				Sleep(1);
				SleepCounter = 0;
			}

			if( g_bInterServerClose == 1 && g_userMgr.CUserMgr::GetUserCount() == 0 )
				DestroyWindow(ghWnd);
		}
	}

	CZsvrAcceptThread::GetObj()->CZsvrAcceptThread::Stop();
	CZsvrAcceptThread::DestroyInstance();
	CZsvrAcceptHandler::DestroyInstance();
	CMsvrAcceptThread::GetObj()->CMsvrAcceptThread::Stop();
	CMsvrAcceptThread::DestroyInstance();
	CMsvrAcceptHandler::DestroyInstance();
	CProcessThread::GetObj()->CProcessThread::Stop();
	N2DBLogMgr::GetObj()->N2DBLogMgr::Stop();
	CIGuildMgr::GetObj()->CIGuildMgr::GuildAllSave();
	CStatisticsMgr::DestroyInstance();
	CProcessThread::DestoryInstance();
	CMemorialDungeonMgr::DestroyInstance();
	CInstantMapMgr::DestroyInstance();
	N2DBLogMgr::DestroyInstance();
	CServerExpInfoMgr::DestroyInstance();
	CleanUp();
	NTraceLog::DestroyInstance();
	NCriticalErrorLog::DestroyInstance();
	CMyMiniDumpUnhandledExceptionHandler::DestroyInstance();

	ExitProcess(EXIT_SUCCESS);
}


static void OutputServerIdentity(const char in_pStr[])
{
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", in_pStr);
}


void InterServerIdentity()
{
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "========== server identity check start ...");
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "build version : %s", __DATE__ " " __TIME__);

	ServerIdentity(&OutputServerIdentity);

	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "========== server identity check end ...");
}


BOOL IsSetting(unsigned int setting)
{
	switch( setting )
	{
	case SETTING_GUILDWAR:
		return g_isGUILDWAR;
	break;
	default:
		return 0;
	break;
	};
}


void CleanUp()
{
	CMServerLog::DestroyInstance();
	CIGuildMgr::DestroyInstance();
	N2SystemMgr::DestoryInstance();
	WSACleanup();
	CMapInfoMgr::DestroyInstance();
	CEntryQueueMgr::DestroyInstance();
	NOutputTextMgr::DestroyInstance();
	CMsvrMgr::DestroyInstance();
	CZsvrMgr::DestroyInstance();
	N2IDGenerator36::DestroyInstance();
	N3DataTransferMgr::DestroyInstance();
	N3MessageMgr::DestroyInstance();
	CIsvrSchedulerIdentity::DestroyInstance();
	CProgrammerSupportLog::DestroyInstance();
	CGVar::DestroyInstance();
}


BOOL DB_Init_FileDsn()
{
	char encBuf[256];
	char encBuf2[256];
	char dbPWD[256];
	char GlobaldbPWD[256];
	GetPrivateProfileStringA("ETC", "DB", "", encBuf, 64, g_infFile);
	GetPrivateProfileStringA("ETC", "GLOBAL_DB", encBuf, encBuf2, 64, g_infFile);
	Decrypt(encBuf, (unsigned char*)dbPWD);
	Decrypt(encBuf2, (unsigned char*)GlobaldbPWD);

	CGVar::GetObj()->CGVar::SetGlobalDBPwd(GlobaldbPWD);
	CGVar::GetObj()->CGVar::SetCharacterDBPwd(dbPWD);

	InterServerIdentity();

	g_expParameter.CExpParameter::Init(SCRIPT_DSN_FILE, GlobaldbPWD);

	if( !g_IGuildDB.CGuildDB::Init(CHARACTER_DSN_FILE, dbPWD)
	 || !g_IGuildSkillDB.CGuildDB::Init(CHARACTER_DSN_FILE, dbPWD) )
		return FALSE;

	if( !N2SystemMgr::CreateInstance() )
	{
		MessageBoxA(NULL, "Create Instance Error", "Nsystem", MB_OK);
		return FALSE;
	}

	if( !CIGuildMgr::CreateInstance() )
	{
		MessageBoxA(NULL, "Create Instance Error", "CIGuildMgr", MB_OK);
		return FALSE;
	}

	CIGuildMgr::GetObj()->Init(g_MaxGuild);

	if( !g_FriendDB.CODBC::Init(CHARACTER_DSN_FILE, dbPWD) )
		return FALSE;

	if( !g_MakerRankMgr.CMakerRankMgr::Init(CHARACTER_DSN_FILE, dbPWD) )
		return FALSE;

	if( IsSetting(0) )
		CIGuildMgr::GetObj()->CIGuildMgr::GetGuildAgitDB();

	g_isExtendDB = g_serverInfo.CServerInfo::Init(GLOBALINFO_DSN_FILE, GlobaldbPWD, INTERPROCESSTYPE, -1);

	g_groupMgr.CPartyMgr::Init(g_MaxParty, CHARACTER_DSN_FILE, dbPWD);

	return TRUE;
}


std::pair<bool,std::string> Startup()
{
	if( !CGVar::CreateInstance() )
		return std::pair<bool,std::string>(false, "CGVar::CreateInstance()");

	if( !CProgrammerSupportLog::CreateInstance() )
		return std::pair<bool,std::string>(false, "CProgrammerSupportLog::CreateInstance()");

	if( !CIsvrSchedulerIdentity::CreateInstance() )
		return std::pair<bool,std::string>(false, "CIsvrSchedulerIdentity::CreateInstance()");

	if( !N3MessageMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "N3MessageMgr::CreateInstance()");

	if( !N3DataTransferMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "N3DataTransferMgr::CreateInstance()");

	if( !CServerExpInfoMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "Create Instance Error");

	if( !CServerExpInfoMgr::GetObj()->CServerExpInfoMgr::Init() )
		return std::pair<bool,std::string>(false, "Init InstanceCServerExpInfoMgr");

	if( !NOutputTextMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "NOutputTextMgr::CreateInstance()");

	if( !CEntryQueueMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "CEntryQueueMgr::CreateInstance()");

	if( !N2IDGenerator36::CreateInstance() )
		return std::pair<bool,std::string>(false, "N2IDGenerator36::CreateInstance()");

	WSADATA wsaData;
	if( WSAStartup(MAKEWORD(2,2), &wsaData) == SOCKET_ERROR )
		return std::pair<bool,std::string>(false, "WSAStartup()");

	int LogOption = GetPrivateProfileIntA("ETC", "LOG", 0, g_infFile);
	InitializeSharedLib(FALSE, LogOption);

	StartCompletionProactor();

	if( !GetPrivateProfileIntA("SETTING", "GUILDWAR", 1, g_infFile) )
		g_isGUILDWAR = FALSE;

	g_sleep = GetPrivateProfileIntA("SETTING", "SLEEP", 0, g_infFile) + 1;
	if( g_sleep > 1 )
		g_sleep = 1;

	g_MaxUser = GetPrivateProfileIntA("MAXVALUE", "MAXUSER", 20000, g_infFile);
	if( g_MaxUser == 0 || g_MaxUser < 20000 )
		g_MaxUser = 20000;

	g_MaxParty = GetPrivateProfileIntA("MAXVALUE", "MAXPARTY", 10000, g_infFile);
	if( g_MaxParty == 0 )
		g_MaxParty = 10000;

	g_MaxGuild = GetPrivateProfileIntA("MAXVALUE", "MAXGUILD", 0, g_infFile);
	if( g_MaxGuild == 0 || g_MaxGuild < 15000 )
		g_MaxGuild = 15000;
	g_MaxGuild += 5000;

	GetPrivateProfileIntA("ETC", "ALLGUILDSEND", 0, g_infFile);
	g_isGuildAllSend = FALSE;

	g_bSetUserCounter = GetPrivateProfileIntA("ETC", "USERCOUNTER", 0, g_infFile);

	BOOL bCriticalLog = GetPrivateProfileIntA("ETC", "CRITICAL_LOG", 0, g_infFile);
	NCriticalErrorLog::GetObj()->NFileLog::SetOutput(bCriticalLog != FALSE);

	g_isPacketLog = GetPrivateProfileIntA("ETC", "PACKET_LOG", 0, g_infFile);

	g_isBroadCastLog = GetPrivateProfileIntA("ETC", "BROADCAST_LOG", 0, g_infFile);

	char encBuf[256] = {};
	GetPrivateProfileStringA("ETC", "DB", "", encBuf, 64, g_infFile);

	char dbPWD[256] = {};
	Decrypt(encBuf, (unsigned char*)dbPWD);

	std::string ConnectionString = std::string("FILEDSN=.\\") + std::string(IPINFO_DSN_FILE) + std::string(";PWD=") + std::string(dbPWD);
	if( !CMapInfoMgr::CreateInstance(ConnectionString) )
		return std::pair<bool,std::string>(false, "CMapInfoMgr::CreateInstance()");

	if( !DB_Init_FileDsn() )
		return std::pair<bool,std::string>(false, "DB_Init_FileDsn()");

	g_userMgr.CUserMgr::Init(g_MaxUser);

	if( !CMsvrMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "CMsvrMgr::CreateInstance()");

	CMsvrMgr::GetObj()->CMClientMgr::Init(40);

	if( !CZsvrMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "CZsvrMgr::CreateInstance()");

	CZsvrMgr::GetObj()->CZServerMgr::Init(40);

	if( !CMServerLog::CreateInstance() )
		return std::pair<bool,std::string>(false, "CMServerLog::CreateInstance()");

	return std::pair<bool,std::string>(true, "good");
}
