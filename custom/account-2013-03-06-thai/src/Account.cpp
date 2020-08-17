#include "Account.h"
#include "AccountDB.h"
#include "BillingConnection.h"
#include "BillingDB.h"
#include "CAccountServerMgr.h"
#include "Certificate.h"
#include "CharacterServerInfo.h"
#include "PCBangBillingDB.h"
#include "PCBangList.h"
#include "SakrayAID.h"
#include "UserDB.h"
#include "UserDB_Sakray.h"
#include "UserList.h"
#include "Common/EnterTraceLog.h"
#include "Common/GlobalInfoDB.h"
#include "Common/InfoScript.h"
#include "Common/MyMiniDumpUnhandledExceptionHandler.h"
#include "Common/Network.h"
#include "Common/NOutputTextMgr.h"
#include "Common/ScriptParser.h"
#include "Common/NSystem/NMessageMgr.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/CompletionPort.h"
#include "Network3/StreamManager.h"


/// globals
CCompletionPort g_compltport;
CStreamManager g_UserStreamMgr;
CStreamManager g_CharSvrStreamMgr;
CAsyncProcessMgr g_AsyncProcessMgr;
CInfoScript g_xmlFileUser;
CInfoScript g_scrptConfig;
CInfoScript g_scriptRestriction;
CScriptParser CharServerInfo;
CUserList g_userList;
CCharacterServerInfo g_characterServerInfo[MAX_CLIENTTYPE];
CAccountDB g_AccountDB[5];
CUserDB g_UserDB;
CSakrayUserDB g_SakrayUserDB;
CCertificate g_certificate;
CBillingConnection g_Billing;
CBillingDB g_BillingDB;
CListedPCBangIPList gListedPCBangipLists;
//CSakrayAID g_SakrayAID; // do NOT want!
int GAME_ID = 1;
int g_nVersion[MAX_CLIENTTYPE];
char g_szModuleFileName[MAX_PATH];
int g_LocalSID;
bool g_bProcessPermit = true;
bool g_bXmlFileUserCheck;
bool gbUpdateThreadRun;
bool gbUpdateThreadEnd = true;

/// locals
static HINSTANCE g_hInst;
static HWND g_hWnd;
static char g_szTime[1024];
static int MaxOutputLineCnt = -1;


bool IsFreeServerSID(int nSID)
{
	bool result = false;

	for( size_t i = 0; i < CharServerInfo.CScriptParser::size() - 2; ++i )
	{
		char buf[5] = {};
		_snprintf_s(buf, sizeof(buf), _TRUNCATE, "SID%d", i);

		const char* szSID = CharServerInfo.CScriptParser::GetItem(buf, 1);
		if( szSID == NULL )
			continue;

		if( nSID != atoi(szSID) )
			continue;

		const char* szType = CharServerInfo.CScriptParser::GetItem(buf, 2);
		if( szType == NULL )
			continue;

		if( atoi(szType) != 0 )
			continue; // not free server

		result = true;
		break; // found.
	}

	return result;
}


void ConcurrentUserNumberLog(int user_num)
{
	static time_t LastTime;
	static char szDir[MAX_PATH];

	if( LastTime == 0 )
	{// initialize dir path
		for( size_t i = strlen(g_szModuleFileName) - 1; i > 0; --i )
		{
			if( g_szModuleFileName[i] == '\\' )
			{
				strncpy_s(szDir, sizeof(szDir), g_szModuleFileName, i + 1);
				strcat_s(szDir, sizeof(szDir), "ConULog");
				break;
			}
		}
	}

	time_t CurrentTime;
	time(&CurrentTime);
	if( difftime(CurrentTime, LastTime) < 60.0 )
		return; // too early for recalc

	time(&LastTime);

	if( _mkdir(szDir) != 0 )
	{
		if( errno == ENOENT )
			printf("Path was not found.\n");
		else
		if( errno != EEXIST )
			printf("unknown error!!!\n");
	}

	time_t ltime;
	time(&ltime);

	tm now;
	localtime_s(&now, &ltime);

	char szTime[1024] = {};
	strftime(szTime, sizeof(szTime), "%Y-%m-%d", &now);

	char szFileName[1024] = {};
	_snprintf_s(szFileName, sizeof(szFileName), _TRUNCATE, "%s\\%s.txt", szDir, szTime);

	FILE* fp = NULL;
	fopen_s(&fp, szFileName, "a");
	if( fp == NULL )
		return;

	strftime(szTime, sizeof(szTime), "%Y-%m-%d %H:%M:%S", &now);

	char szMessage[1024] = {};
	_snprintf_s(szMessage, sizeof(szMessage), _TRUNCATE, "%s - %d\n", szTime, user_num);

	fprintf(fp, szMessage);
	fclose(fp);
}


void __cdecl UpdateInfoThread(void* lpVoid)
{
	char szInfo[1024] = {};
	DWORD dwBeginTime = timeGetTime();

	while( gbUpdateThreadRun )
	{
		time_t currentTime;
		time(&currentTime);

		tm now;
		localtime_s(&now, &currentTime);
		strftime(g_szTime, sizeof(g_szTime), "%Y-%m-%d %H:%M:%S", &now);

		DWORD deltaTime = timeGetTime() - dwBeginTime;
		unsigned int nHour = deltaTime / 3600000;
		deltaTime -= nHour * 3600000;
		unsigned int nMin = deltaTime / 60000;
		deltaTime -= nMin * 60000;
		unsigned int nSecond = deltaTime / 1000;
		deltaTime -= nSecond * 1000;

		_snprintf_s(szInfo, sizeof(szInfo), _TRUNCATE, "[TestA] (%d,%d,%d) C(%d/%d) H(%d/%d) TH(%d/%d) P(%d/%d) B(%d,%d) (%03d:%02d:%02d) (%s) (PCBonus) v(%s %s)", // [patch] build date in window title
			g_userList.CUserList::GetCount(), g_userList.CUserList::GetCountAuth(), g_userList.CUserList::GetAllocCount(),
			g_UserStreamMgr.CStreamManager::GetConnectionCount(), g_UserStreamMgr.CStreamManager::GetFreeStreamNum(),
			g_CharSvrStreamMgr.CStreamManager::GetConnectionCount(), g_CharSvrStreamMgr.CStreamManager::GetFreeStreamNum(),
			g_compltport.CCompletionPort::GetRunningThreadNum(), g_compltport.CCompletionPort::GetWorkerThreadNum(),
			g_AsyncProcessMgr.CAsyncProcessMgr::GetPoolAllocSize(), g_AsyncProcessMgr.CAsyncProcessMgr::GetPoolSize(),
			g_Billing.m_bConnected, g_Billing.m_qSend.m_dwCount,
			nHour, nMin, nSecond,
			"NB", __DATE__, __TIME__);

		SendHeartBeatToBill(NOMAL_BILLINGSERVER);
		SendHeartBeatToBill(GAMEBANG_BILLNGSERVER);

		ConcurrentUserNumberLog(g_userList.CUserList::GetCountAuth());

		SetWindowTextA(g_hWnd, szInfo);
		Sleep(1000);
	}

	gbUpdateThreadEnd = true;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	case WM_DESTROY:
		Sleep(0);
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

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CLOSE:
	{
		NMessageMgr::GetObj()->NMessageMgr::Post(CAccountServerMgr::GetObj()->NObject::GetMyID(), CAccountServerMgr::MSG_THREAD_QUIT, 0, 0);
		return 0; // message processed.
	}
	break;
	case WM_TIMER:
		if( MaxOutputLineCnt != NOutputTextMgr::GetObj()->NOutputTextMgr::GetMaxLineCnt() )
			InvalidateRect(hWnd, NULL, FALSE);
	break;
	case WM_RBUTTONDOWN:
		InvalidateRect(hWnd, NULL, TRUE);
	break;
	default:
	break;
	}

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hInst = hInstance;

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

	std::string WindowName;
	WindowName = "AC";
	WindowName += " ("__DATE__" "__TIME__")";

	g_hWnd = CreateWindowExA(0, "Ragnarok", WindowName.c_str(), WS_OVERLAPPEDWINDOW, 100, 100, 700, 600, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	if( g_hWnd == NULL )
	{
		MessageBoxA(NULL, "failed window", "error", MB_OK);
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	return TRUE;
};


namespace {
std::pair<bool,std::string> Startup()
{
	if( !CEnterTraceLog::CreateInstance() )
		return std::pair<bool,std::string>(false, "CEnterTraceLog::CreateInstance()");

	if( !CMyMiniDumpUnhandledExceptionHandler::CreateInstance() )
		return std::pair<bool,std::string>(false, "CMyMiniDumpUnhandledExceptionHandler::CreateInstance()");

	if( !CNetwork::CreateInstance() )
		return std::pair<bool,std::string>(false, "CNetwork::CreateInstance()");

	if( !NOutputTextMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "NOutputTextMgr::CreateInstance()");

	if( !NMessageMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "NMessageMgr::CreateInstance()");

	if( !CAccountServerMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "CAccountServerMgr::CreateInstance()");

	if( !CPCBangBillingDB::CreateInstance() )
		return std::pair<bool,std::string>(false, "CPCBangBillingDB::CreateInstance()");

	if( !CGlobalInfoDB::CreateInstance() )
		return std::pair<bool,std::string>(false, "CGlobalInfoDB::CreateInstance()");

	memset(g_szModuleFileName, '\0', sizeof(g_szModuleFileName));
	GetModuleFileNameA(NULL, g_szModuleFileName, sizeof(g_szModuleFileName)-1);

	return std::pair<bool,std::string>(true, "good");
}


void Cleanup()
{
	CAccountServerMgr::DestroyInstance();
	NMessageMgr::DestroyInstance();
	NOutputTextMgr::DestroyInstance();
	CMyMiniDumpUnhandledExceptionHandler::DestroyInstance();
	CPCBangBillingDB::DestroyInstance();
	CNetwork::DestroyInstance();
	CEnterTraceLog::DestroyInstance();
	CGlobalInfoDB::DestroyInstance();
}
}; // namespace


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if( !InitInstance(hInstance, nCmdShow) )
	{
		MessageBoxA(NULL, "failed init window", NULL, MB_OK);
		return 0;
	}

	std::pair<bool,std::string> ret = Startup();
	if( !ret.first )
	{
		MessageBoxA(NULL, ret.second.c_str(), "Startup", MB_OK);
		return 0;
	}

	SetTimer(g_hWnd, 0, 1000, NULL);
	NOutputTextMgr::GetObj()->NOutputTextMgr::Insert("Server Start....");
	CAccountServerMgr::GetObj()->CAccountServerMgr::Start();

	while( 1 )
	{
		if( !CAccountServerMgr::GetObj()->NThread::isRun() && MaxOutputLineCnt == NOutputTextMgr::GetObj()->NOutputTextMgr::GetMaxLineCnt() )
			break;

		MSG msg;
		if( PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else
		{
			Sleep(100);
		}
	}

	CAccountServerMgr::GetObj()->CAccountServerMgr::Stop();
	Cleanup();

	return 0;
}
