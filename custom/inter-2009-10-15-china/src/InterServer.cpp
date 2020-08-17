#include "AcceptThread.h"
#include "CMailCtrl.h"
#include "CMakerRankMgr.h"
#include "DBScriptInfo.h"
#include "ErrorLog.h"
#include "ExpParameter.h"
#include "FriendDB.h"
#include "GuildDB.h"
#include "IGuildInfoDB.h"
#include "IGuildMgr.h"
#include "InterServer.h"
#include "ISAcceptHandler.h"
#include "ISDatabaseAccountMgr.h"
#include "MapInfo.h"
#include "MGAcceptHandler.h"
#include "MServerMgr.h"
#include "PartyMgr.h"
#include "ProcessThread.h"
#include "ServerInfo.h"
#include "UserMgr.h"
#include "ZServerMgr.h"
#include "shared.h"
#include "Common/Packet.h"
#include "Instant Map/InstantMapMgr.h"
#include "Memorial Dungeon/MemorialDungeonMgr.h"
#include "N2System/N2SystemMgr.h"
#include "N2System/DBLog/N2DBLogMgr.h"
#include "Statistics/StatisticsMgr.h"
#include "enums.hpp"
#include "globals.hpp"
#include "std/string"


hook_func<int (__cdecl *)(HINSTANCE hInstance, int nCmdShow)> _InitInstance(SERVER, "InitInstance");
int __cdecl InitInstance(HINSTANCE hInstance, int nCmdShow) // line 159
{
	return (_InitInstance)(hInstance, nCmdShow);

	WNDCLASSEXA wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_CLASSDC|CS_DBLCLKS;
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

	char buf[256];
	sprintf(buf, "%s(%s)", "(vc9)INTER", "Oct 15 2009 14:37:22");

	HWND hWnd = CreateWindowExA(0, "Ragnarok", buf, WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_GROUP|WS_TABSTOP, 100, 100, 600, 300, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	if( hWnd == NULL )
		return 0;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	SetTimer(hWnd, NULL, 5000, NULL);
	ghWnd = hWnd;
	return 1;
}


hook_func<LRESULT (CALLBACK *)(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)> _WndProc(SERVER, "WndProc");
HOOKED LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // line 211
{
	///@patch unlock hidden third window mode
	///@patch redraw window after switching modes
	if( msg == WM_CHAR )
	{
		gViewMode = (gViewMode + 1) % 3;
		InvalidateRect(hWnd, NULL, FALSE);
		return DefWindowProcA(hWnd, msg, wParam, lParam);
	}

	///@patch 'killall' system menu item
	const int ID_MENUKILL = 42;
	if( msg == WM_CREATE )
	{
		HMENU hMenu = GetSystemMenu(hWnd, FALSE);
		InsertMenuA(hMenu, SC_CLOSE, MF_STRING, ID_MENUKILL, "Killall");
		ModifyMenuA(hMenu, SC_CLOSE, MF_BYCOMMAND, SC_CLOSE, "Shutdown");
	}
	else
	if( msg == WM_SYSCOMMAND && wParam == ID_MENUKILL )
	{
		PACKET_IZ_DISCONNECT_ALL outpacket;
		outpacket.PacketType = HEADER_IZ_DISCONNECT_ALL;
		g_zServerMgr.CZServerMgr::BroadCast(sizeof(outpacket), (char*)&outpacket);
	}

	return (_WndProc)(hWnd, msg, wParam, lParam);

	switch( msg )
	{
	case WM_DESTROY:
		PostQuitMessage(EXIT_SUCCESS);
	break;
	case WM_PAINT:
		switch( gViewMode )
		{
		case  0: OnPaintMode0(hWnd); break;
		case  1: OnPaintMode1(hWnd); break;
		case  2: OnPaintMode2(hWnd); break;
		default: OnPaintMode0(hWnd); break;
		}
	break;
	case WM_CHAR:
		gViewMode = (gViewMode + 1) % 2; //FIXME: mode 2 is inaccessible
	break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, FALSE);
	break;
	case WM_RBUTTONDBLCLK:
		g_SendChkProrcessTime = 1;
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
	}

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}


hook_func<int (__stdcall *)(HINSTANCE__ *hInstance, HINSTANCE__ *hPrevInstance, char *lpCmdLine, int nCmdShow)> _WinMain(SERVER, "WinMain");
int __stdcall WinMain(HINSTANCE__ *hInstance, HINSTANCE__ *hPrevInstance, char *lpCmdLine, int nCmdShow) // line 307
{
	return (_WinMain)(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	SYSTEMTIME st;
	GetLocalTime(&st);
	_snprintf(g_szCriticalLogFileName, 260, "criticalError(%04d%02d%02d).txt", st.wYear, st.wMonth, st.wDay);
	_snprintf(g_szTraceLogFileName, 260, "TraceLog(%04d%02d%02d).txt", st.wYear, st.wMonth, st.wDay);

	HANDLE hMutex = CreateMutexA(NULL, false, "Global\\Ragnarok Inter Server");
	if( WaitForSingleObject(hMutex, 0) != WAIT_OBJECT_0 )
	{
		MessageBoxA(NULL, "Another Inter Server is Still Executing", NULL, MB_OK);
		return 0;
	}

	if( !InitInstance(hInstance, nCmdShow) )
		return 0;

	if( !StartUp() )
	{
		MessageBoxA(NULL, "Server Init False!!!", NULL, MB_OK);
		return 0;
	}

	_g_isAcceptHandler.CISAcceptHandler::Init(40);

	if( g_isExtendDB != 0 )
		_g_isMGAcceptHandler.CMGAcceptHandler::Init(40);

	_ACCEPT_PARM ap;
	ap.ip = g_serverInfo.CServerInfo::GetServerPrivateIPAddr(g_serverInfo.CServerInfo::GetLocalServerID());

	_ACCEPT_PARM MGap;
	if( ap.ip != 0 && g_isExtendDB != 0 )
	{
		ap.port = g_serverInfo.CServerInfo::GetServerPrivatePort(g_serverInfo.CServerInfo::GetLocalServerID());
		MGap.ip = g_serverInfo.CServerInfo::GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS);
		MGap.port = g_serverInfo.CServerInfo::GetLocalPort();
		MGap.backlog = 20;
		MGap.ipLog = 0;
	}
	else
	{
		g_isExtendDB = 0;
		ap.ip = g_serverInfo.CServerInfo::GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS);
		ap.port = g_serverInfo.CServerInfo::GetLocalPort();
		MGap.ip = 0;
		MGap.port = 0;
	}

	Trace("Program Start Ok \n");

	if( g_isExtendDB != 0 && ap.ip == MGap.ip && ap.port == MGap.port )
	{
		g_isExtendDB = 0;
		g_errorLogs.CErrorLog::CriticalErrorLog("같은 아이피 설정", 450, ".\\InterServer.cpp");
	}

	char buffer[256];
	char dbPWD[256];
	memset(dbPWD, 0, sizeof(dbPWD));
	GetPrivateProfileStringA("ETC", "DB", "", buffer, 64, g_infFile);
	Decrypt(buffer, (unsigned char*)dbPWD);

	CDBScriptInfo dbScriptInfo;

	char Path[80];
	GetCurrentDirectoryA(sizeof(Path), Path);

	char FileName[80];
	sprintf(FileName, "%s\\%s", Path, "DBInfo.scp");
	if( dbScriptInfo.CDBScriptInfo::Load(FileName) == 0 )
	{
		char Message[80];
		sprintf(Message, "%s open error", FileName);
		MessageBoxA(NULL, Message, NULL, MB_OK);
		return 0;
	}

	if( dbScriptInfo.CDBScriptInfo::Search("log") == NULL )
	{
		MessageBoxA(NULL, "can't find LogDB DSN name from DBInfo.scp", "LogDB", MB_OK);
		return 0;
	}

	mystd::string logDBConnectionStr = "";
	logDBConnectionStr += "DSN=";
	logDBConnectionStr += dbScriptInfo.CDBScriptInfo::Search("log");
	logDBConnectionStr += ";";
	logDBConnectionStr += "UID=";
	logDBConnectionStr += "loger";
	logDBConnectionStr += ";";
	logDBConnectionStr += "PWD=";
	logDBConnectionStr += dbPWD;
	logDBConnectionStr += ";";
	
	//dbScriptInfo goes out of scope here

	int nLogThreads = GetPrivateProfileIntA("SETTING", "database log work thread number", 2, g_infFile);
	if( !N2DBLogMgr::CreateInstance(nLogThreads, logDBConnectionStr) )
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

	gcpAcceptThread = new CAcceptThread(&_g_isAcceptHandler, ap.ip, ap.port, 20, 0);
	if( gcpAcceptThread == NULL )
	{
		MessageBoxA(NULL, "new Error", "AcceptThread", MB_OK);
		return 0;
	}
	if( !gcpAcceptThread->isOK() )
	{
		MessageBoxA(NULL, "isOK() Error", "AcceptThread", MB_OK);
		if( gcpAcceptThread != NULL )
			delete gcpAcceptThread;
		gcpAcceptThread = NULL;
		return 0;
	}

	if( g_isExtendDB != 0 && !(ap.ip == MGap.ip && ap.port == MGap.port) )
	{
		gcpManagerAcceptThread = new CAcceptThread(&_g_isMGAcceptHandler, MGap.ip, MGap.port, MGap.backlog, MGap.ipLog);
		if( gcpManagerAcceptThread == NULL )
		{
			MessageBoxA(NULL, "new Error", "ManagerAcceptThread", MB_OK);
			return 0;
		}
		if( !gcpManagerAcceptThread->isOK() )
		{
			MessageBoxA(NULL, "isOK() Error", "ManagerAcceptThread", MB_OK);
			if( gcpManagerAcceptThread != NULL )
				delete gcpManagerAcceptThread;
			gcpManagerAcceptThread = NULL;
			return 0;
		}
	}

	if( !InstanceN2DBLogMgr()->N2DBLogMgr::Start() )
	{
		MessageBoxA(NULL, "Start() Error", "N2DBLogMgr", MB_OK);
		return 0;
	}

	if( !CProcessThread::GetObj()->CProcessThread::Start() )
	{
		MessageBoxA(NULL, "Start() Error", "ProcessThread", MB_OK);
		return 0;
	}

	if( !gcpAcceptThread->CAcceptThread::Start() )
	{
		MessageBoxA(NULL, "Start() Error", "AcceptThread", MB_OK);
		return 0;
	}

	if( gcpManagerAcceptThread && !gcpManagerAcceptThread->CAcceptThread::Start() )
	{
		MessageBoxA(NULL, "Start() Error", "ManagerAcceptThread", MB_OK);
		return 0;
	}

	g_bOutput = true;

	int SleepCounter = 0;

	MSG msg;
	memset(&msg, 0, sizeof(msg));

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

			if( g_bInterServerClose == 1 )
			{
				if( g_userMgr.CUserMgr::GetUserCount() == 0 )
					DestroyWindow(ghWnd);
			}
		}
	}

	if( gcpAcceptThread != NULL )
	{
		gcpAcceptThread->CAcceptThread::Stop();
		if( gcpAcceptThread != NULL )
			delete gcpAcceptThread;
		gcpAcceptThread = NULL;
	}

	if( gcpManagerAcceptThread != NULL )
	{
		gcpManagerAcceptThread->CAcceptThread::Stop();
		if( gcpManagerAcceptThread != NULL )
			delete gcpManagerAcceptThread;
		gcpManagerAcceptThread = NULL;
	}

	CProcessThread::GetObj()->CProcessThread::Stop();
	InstanceN2DBLogMgr()->N2DBLogMgr::Stop();
	CIGuildMgr::GetObj()->CIGuildMgr::GuildAllSave();

	CStatisticsMgr::DestroyInstance();
	CProcessThread::DestoryInstance();
	CMemorialDungeonMgr::DestroyInstance();
	CInstantMapMgr::DestroyInstance();
	N2DBLogMgr::DestroyInstance();
	CleanUp();

	return 0;
}


hook_func<int (__cdecl *)(unsigned int setting)> _IsSetting(SERVER, "IsSetting");
int __cdecl IsSetting(unsigned int setting) // line 617
{
	return (_IsSetting)(setting);

	return ( setting == 0 ) ? g_isGUILDWAR : 0;
}


hook_func<void (__cdecl *)(void)> _CleanUp(SERVER, "CleanUp");
void __cdecl CleanUp(void) // line 630
{
	return (_CleanUp)();

	//TODO
}


hook_func<bool (__cdecl *)(void)> _StartUp(SERVER, "StartUp");
bool __cdecl StartUp(void) // line 646
{
	return (_StartUp)();

	WSAData wsaData;
	if( WSAStartup(MAKEWORD(2,2), &wsaData) == -1 )
		return false;

	InitializeSharedLib(1, GetPrivateProfileIntA("ETC", "LOG", 0, g_infFile));

	StartCompletionProactor();

	if( GetPrivateProfileIntA("SETTING", "GUILDWAR", 1, g_infFile) == 0 )
		g_isGUILDWAR = 0;

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
	g_MaxGuild = g_MaxGuild + 5000;

	GetPrivateProfileIntA("ETC", "ALLGUILDSEND", 0, g_infFile); // FIXME: value not assigned
	g_isGuildAllSend = 0;

	g_bSetUserCounter = GetPrivateProfileIntA("ETC", "USERCOUNTER", 0, g_infFile);

	char encBuf[256];
	char encBuf2[256];
	GetPrivateProfileStringA("ETC", "DB", "", encBuf, 64, g_infFile);
	GetPrivateProfileStringA("ETC", "GLOBAL_DB", encBuf, encBuf2, 64, g_infFile);

	g_isCriticalLog = GetPrivateProfileIntA("ETC", "CRITICAL_LOG", 0, g_infFile);
	g_isPacketLog = GetPrivateProfileIntA("ETC", "PACKET_LOG", 0, g_infFile);
	g_isBroadCastLog = GetPrivateProfileIntA("ETC", "BROADCAST_LOG", 0, g_infFile);

	char Path[80];
	GetCurrentDirectoryA(sizeof(Path), Path);

	char FileName[80];
	sprintf(FileName, "%s\\%s", Path, "DBInfo.scp");

	CDBScriptInfo dbScriptInfo;
	if( !dbScriptInfo.CDBScriptInfo::Load(FileName) )
	{
		char Message[80];
		sprintf(Message, "%s open error", FileName);
		MessageBoxA(NULL, Message, NULL, MB_OK);
		return false;
	}

	const char* szGlobalInfoDB = dbScriptInfo.CDBScriptInfo::Search("globalinfo");
	const char* szCharacterDB = dbScriptInfo.CDBScriptInfo::Search("character");
	const char* szScriptDB = dbScriptInfo.CDBScriptInfo::Search("script");
	if( szGlobalInfoDB == NULL || szCharacterDB == NULL || szScriptDB == NULL )
	{
		MessageBoxA(NULL, "check DBIno.scp", NULL, MB_OK);
		return false;
	}

	char dbPWD[256];
	char GlobaldbPWD[256];
	Decrypt(encBuf, (unsigned char*)dbPWD);
	Decrypt(encBuf2, (unsigned char*)GlobaldbPWD);

	const char* szIpInfoDB = dbScriptInfo.CDBScriptInfo::Search("ipinfo");
	if( !g_mapInfo.CODBC::Init(szIpInfoDB, "ipinfo", dbPWD, szIpInfoDB, 0) )
	{
		MessageBoxA(NULL, "mapInfo initialize error", "InitServer()", MB_OK);
		return false;
	}

	g_mapInfo.CMapInfo::GetMapInfo();

	g_expParameter.CExpParameter::Init(szScriptDB, GlobaldbPWD);

	if( !g_IGuildDB.CGuildDB::Init(szCharacterDB, "character", dbPWD, szCharacterDB, 0)
	||  !g_IGuildSkillDB.CGuildDB::Init(szCharacterDB, "character", dbPWD, szCharacterDB, 0) )
		return false;

	if( !ISDatabaseAccountMgr::CreateInstance() )
	{
		MessageBoxA(NULL, "Create Instance Error", "ISDatabaseAccountMgr", MB_OK);
		return false;
	}

	if( !N2SystemMgr::CreateInstance() )
	{
		MessageBoxA(NULL, "Create Instance Error", "Nsystem", MB_OK);
		return false;
	}

	if( !CIGuildMgr::CreateInstance() )
	{
		MessageBoxA(NULL, "Create Instance Error", "CIGuildMgr", MB_OK);
		return false;
	}

	CIGuildMgr::GetObj()->Init(g_MaxGuild);

	if( !g_FriendDB.CODBC::Init(szCharacterDB, "character", dbPWD, szCharacterDB, 0)
	||  !g_MakerRankMgr.CMakerRankMgr::Init(szCharacterDB, "character", dbPWD, szCharacterDB, 0) )
		return false;

	g_MailCtrl.CMailCtrl::Init(szCharacterDB, "character", dbPWD, szCharacterDB, 0);

	if( IsSetting(0) )
	{
		CIGuildMgr::GetObj()->CIGuildMgr::GetGuildAgitDB();
		Trace("Agit Loaded\n");
	}

	g_isExtendDB = g_serverInfo.CServerInfo::Init("globalinfo", GlobaldbPWD, szGlobalInfoDB, 4);
	InstanceCPartyMgr()->CPartyMgr::Init(g_MaxParty, szCharacterDB, "character", dbPWD, szCharacterDB, 0);
	g_userMgr.CUserMgr::Init(g_MaxUser);
	g_mServerMgr.CMClientMgr::Init(40);
	g_zServerMgr.CZServerMgr::Init(40);

	return true;
}


hook_func<void (__cdecl *)(HWND hWnd)> _OnPaintMode0(SERVER, "OnPaintMode0");
void __cdecl OnPaintMode0(HWND hWnd) // line 875
{
	return (_OnPaintMode0)(hWnd);

	char buf[1024];
	memset(buf, 0, sizeof(buf));

	PAINTSTRUCT ps; //static
	BeginPaint(hWnd, &ps);

	RECT rect;
	GetClientRect(hWnd, &rect);

	FillRect(ps.hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	sprintf(buf, "CRITICAL LOG = %s", (g_isCriticalLog)?"yes":"no");
	TextOutA(ps.hdc, 0, 24, buf, strlen(buf));

	sprintf(buf, " - Gravity -");
	TextOutA(ps.hdc, 0, 56, buf, strlen(buf));

	sprintf(buf, "Inter Version %d", 4);
	TextOutA(ps.hdc, 0, 72, buf, strlen(buf));

	sprintf(buf, "FOREIGN_LANGUAGE");
	TextOutA(ps.hdc, 0, 88, buf, strlen(buf));

	sprintf(buf, "GROBAL_VERSION");
	TextOutA(ps.hdc, 0, 104, buf, strlen(buf));

	sprintf(buf, "_CASH_POINT_ITEM_SHOP");
	TextOutA(ps.hdc, 0, 120, buf, strlen(buf));

	sprintf(buf, "__MEMORIAL_DUNGEON");
	TextOutA(ps.hdc, 0, 136, buf, strlen(buf));

	sprintf(buf, "__PARTY_INVITE");
	TextOutA(ps.hdc, 0, 152, buf, strlen(buf));

	sprintf(buf, "MailSize =  %d", 40);
	int nY = 168;
	TextOutA(ps.hdc, 0, nY, buf, strlen(buf));

	if( g_isBroadCastLog == 1 )
	{
		sprintf(buf, "BroadCast Log : On");
		nY += 16;
		TextOutA(ps.hdc, 0, nY, buf, strlen(buf));
	}

	if( g_isGuildAllSend == 1 )
	{
		sprintf(buf, "GuildAllSend : On");
		nY += 16;
		TextOutA(ps.hdc, 0, nY, buf, strlen(buf));
	}

	sprintf(buf, "M Server = %d", g_MServerSize);
	nY += 16;
	TextOutA(ps.hdc, 0, nY, buf, strlen(buf));

	sprintf(buf, "User Count:%d Free Size:%d  OffSet : %d", g_userMgrUserCount, g_userMgrFreeSize, g_MaxUser - g_userMgrFreeSize - g_userMgrUserCount);
	nY += 32;
	TextOutA(ps.hdc, 0, nY, buf, strlen(buf));

	sprintf(buf, "Party Count:%d Free Size:%d  OffSet : %d", g_groupMgrGroupSize, g_groupMgrFreeSize, g_MaxParty - g_groupMgrFreeSize - g_groupMgrGroupSize);
	nY += 16;
	TextOutA(ps.hdc, 0, nY, buf, strlen(buf));

	sprintf(buf, "Guild Count:%d Free Size:%d  OffSet : %d", g_IGuildMgrGuildSize, g_IGuildMgrFreeSize, g_MaxGuild - g_IGuildMgrFreeSize - g_IGuildMgrGuildSize);
	nY += 16;
	TextOutA(ps.hdc, 0, nY, buf, strlen(buf));

	sprintf(buf, "Max Process Time : %d (ms)", g_MaxProcessTime);
	nY += 16;
	TextOutA(ps.hdc, 0, nY, buf, strlen(buf));

	if( g_SIDProcessTime != 0 )
	{
		sprintf(buf, "Server Process Time : Server %d  ", g_SIDProcessTime);
		nY += 16;
		TextOutA(ps.hdc, 0, nY, buf, strlen(buf));

		sprintf(buf, "                     Inter->Zone %d (s), Zone->Inter %d (s) ", (int)g_IZProcessTime, (int)g_ZIProcessTime);
		nY += 16;
		TextOutA(ps.hdc, 0, nY, buf, strlen(buf));
	}

	if( g_bSetUserCounter != 0 )
	{
		sprintf(buf, "UserCounter : ON");
		nY += 16;
		TextOutA(ps.hdc, 0, nY, buf, strlen(buf));
	}
	else
	{
		sprintf(buf, "UserCounter : OFF");
		nY += 16;
		TextOutA(ps.hdc, 0, nY, buf, strlen(buf));
	}

	EndPaint(hWnd, &ps);
}


hook_func<void (__cdecl *)(HWND hWnd)> _OnPaintMode1(SERVER, "OnPaintMode1");
void __cdecl OnPaintMode1(HWND hWnd) // line 1012
{
	return (_OnPaintMode1)(hWnd);

	char buf[1024];
	memset(buf, 0, sizeof(buf));

	PAINTSTRUCT ps; //static
	BeginPaint(hWnd, &ps);

	RECT rect;
	GetClientRect(hWnd, &rect);

	FillRect(ps.hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	int nY = 8;

	sprintf(buf, " - Gravity -");
	nY += 10;
	TextOutA(ps.hdc, 0, nY, buf, strlen(buf));

	sprintf(buf, "View Mode 1");
	nY += 16;
	TextOutA(ps.hdc, 0, nY, buf, strlen(buf));

	g_zServerMgr.CZServerMgr::OnPaintZoneServerInfo(ps.hdc, nY);

	sprintf(buf, "- Press Any Key -");
	nY = 200;
	TextOutA(ps.hdc, 0, 200, buf, strlen(buf));

	EndPaint(hWnd, &ps);
}


hook_func<void (__cdecl *)(HWND hWnd)> _OnPaintMode2(SERVER, "OnPaintMode2");
void __cdecl OnPaintMode2(HWND hWnd) // line 825
{
	return (_OnPaintMode2)(hWnd);

	PAINTSTRUCT ps; //static
	BeginPaint(hWnd, &ps);

	int nX = 20;
	int nY = 0;

	char buffer[1025];
	memset(buffer, 0, sizeof(buffer));

	tagRECT rect;
	GetClientRect(hWnd, &rect);

	FillRect(ps.hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	sprintf(buffer, " - Instant Map / Memorial Dungeon -");
	nY += 16;
	TextOutA(ps.hdc, 0, nY, buffer, strlen(buffer));

	_snprintf(buffer, 1024, "memorial dungeon : %d", CMemorialDungeonMgr::GetObj()->CMemorialDungeonMgr::GetNum());
	nY += 16;
	TextOutA(ps.hdc, nX, nY, buffer, strlen(buffer));

	_snprintf(buffer, 1024, "instant map : %d", CInstantMapMgr::GetObj()->CInstantMapMgr::GetNum());
	nY += 16;
	TextOutA(ps.hdc, nX, nY, buffer, strlen(buffer));

	g_zServerMgr.CZServerMgr::OutputZSvrInfo(ps.hdc, nX, nY);

	EndPaint(hWnd, &ps);
}
