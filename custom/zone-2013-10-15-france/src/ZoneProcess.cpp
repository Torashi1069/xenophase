#include "CZoneProcessConfigMgr.h"
#include "CZoneProcessLocalConfigMgr.h"
#include "CZsvrSchedulerIdentity.h"
#include "GlobalVarDB.h"
#include "GVar.h"
#include "NNetworkMgr.h"
#include "ZoneProcess.h"
#include "ZSAcceptHandler.h"
#include "shared/MyMiniDumpUnhandledExceptionHandler.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/NOutputTextMgr.h"
#include "shared/NTraceLog.h"
#include "shared/ServerInfo.h"
#include "shared/N3System/N3DataTransferMgr.h"
#include "shared/N3System/N3MessageMgr.h"


/// globals
CZSAcceptHandler& g_zsAcceptHandler = VTOR<CZSAcceptHandler>(DetourFindFunction(EXEPATH(), "g_zsAcceptHandler")); // 272
CGlobalVarDB& g_globalVarDB = VTOR<CGlobalVarDB>(DetourFindFunction(EXEPATH(), "g_globalVarDB")); // 484
HINSTANCE& g_hInst = VTOR<HINSTANCE>(DetourFindFunction(EXEPATH(), "g_hInst"));
HWND& g_hWnd = VTOR<HWND>(DetourFindFunction(EXEPATH(), "g_hWnd"));
BOOL& g_isPacketLog = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_isPacketLog"));
DWORD& g_curTime = VTOR<DWORD>(DetourFindFunction(EXEPATH(), "g_curTime"));
BOOL& g_storePasswordCheck = VTOR<BOOL>(DetourFindFunction(EXEPATH(), "g_storePasswordCheck"));
const char g_infFile[] = ".\\RO.inf";


/// forward declarations
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) // 734-800
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

	char temp[256];
	sprintf_s(temp, countof(temp), "RO - INTERNATIONAL SC%d.%d.%d", 14, 2, 1);

	std::string windowName;
	windowName.append(temp, strlen(temp));

	char buf[256];
	sprintf_s(buf, countof(buf), "%s (%s)", windowName.c_str(), __DATE__" "__TIME__);

	g_hWnd = CreateWindowExA(0, "Ragnarok", buf, WS_OVERLAPPEDWINDOW, 100, 100, 700, 700, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	if( g_hWnd == NULL )
	{
		MessageBoxA(NULL, "failed window", "error", MB_OK);
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	SetTimer(g_hWnd, 0, 1000, NULL);

	return TRUE;
}


hook_func<LRESULT (CALLBACK *)(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)> _WndProc(EXEPATH(), "WndProc");
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // 1179-1219
{
	return _WndProc(hWnd, msg, wParam, lParam);

	//TODO
}


namespace {
////////////////////////////////////////
class lcApp
{
public:
	std::pair<bool,std::string> Startup();
	void Cleanup();

public:
	lcApp();
	virtual ~lcApp();

private:
	/* this+4 */ HANDLE m_hMutex;
	/* this+8 */ UINT m_wTimerRes;
};


lcApp::lcApp()
{
	m_hMutex = NULL;
	m_wTimerRes = 0;
}


lcApp::~lcApp()
{
}


std::pair<bool,std::string> lcApp::Startup() // 1721-1948
{
	if( !CZsvrSchedulerIdentity::CreateInstance() )
		return std::pair<bool,std::string>(false, "CZsvrSchedulerIdentity::CreateInstance()");

//	if( !CProgrammerSupportLog::CreateInstance() )
//		return std::pair<bool,std::string>(false, "CProgrammerSupportLog::CreateInstance()");

	TIMECAPS tc = {};
	if( !timeGetDevCaps(&tc, sizeof(tc)) )
	{
		m_wTimerRes = min(max(1, tc.wPeriodMin), tc.wPeriodMax);
		timeBeginPeriod(m_wTimerRes);
	}

//	if( !CThreadAffinityMgr::CreateInstance() )
//		return std::pair<bool,std::string>(false, "CThreadAffinityMgr::CreateInstance()");

//	if( !InitFromRoInf() )
//		return std::pair<bool,std::string>(false, "InitFromRoInf()");

	if( !CZoneProcessConfigMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "CZoneProcessConfigMgr::CreateInstance()");

	if( !CZoneProcessLocalConfigMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "CZoneProcessLocalConfigMgr::CreateInstance()");

	if( !CZoneProcessLocalConfigMgr::GetObj()->CZoneProcessLocalConfigMgr::Init() )
		return std::pair<bool,std::string>(false, "InstanceCZoneProcessLocalConfigMgr()->Init()");

	char modulePath[MAX_PATH] = {};
	GetModuleFileNameA(NULL, modulePath, countof(modulePath));

	for( size_t i = 0; i < strlen(modulePath); ++i )
		if( modulePath[i] == '\\' || modulePath[i] == ':' || modulePath[i] == '.' )
			modulePath[i] = ' ';

	m_hMutex = CreateMutexA(NULL, FALSE, modulePath);

	if( WaitForSingleObject(m_hMutex, 0) != WAIT_OBJECT_0 )
		return std::pair<bool,std::string>(false, "Another Zone Server is Still Executing");

	if( !CGVar::CreateInstance() )
		return std::pair<bool,std::string>(false, "CGvar Init faile zoneserver error");

	g_curTime = time(NULL);
//	g_serverInfo.CServerInfo::Init(GLOBALINFO_DSN_FILE, g_GlobaldbPWD, ZONEPROCESSSERVERTYPE, CZoneProcessLocalConfigMgr::GetObj()->CZoneProcessLocalConfigMgr::GetZSID());

	if( !NNetworkMgr::CreateInstance() )
		return std::pair<bool,std::string>(false, "NNetworkMgr::CreateInstance()");

	return std::pair<bool,std::string>(true, "good");
}


void lcApp::Cleanup() // 1951-2039
{
	NNetworkMgr::DestroyInstance();

	if( m_hMutex != NULL )
	{
		CloseHandle(m_hMutex);
		m_hMutex = NULL;
	}

	CZoneProcessLocalConfigMgr::DestroyInstance();
	CZoneProcessConfigMgr::DestroyInstance();
	CGVar::DestoryInstance();
//	CThreadAffinityMgr::DestroyInstance();
	if( m_wTimerRes != 0 ) timeEndPeriod(m_wTimerRes);
//	CProgrammerSupportLog::DestroyInstance();
	CZsvrSchedulerIdentity::DestroyInstance();
}
////////////////////////////////////////
}; // namespace


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) // 2062-2211
{
	if( !CMyMiniDumpUnhandledExceptionHandler::CreateInstance(NULL) )
		return 0;

	if( !NCriticalErrorLog::CreateInstance() )
		return 0;

	if( !NTraceLog::CreateInstance() )
		return 0;

	NTraceLog::GetObj()->NFileLog::SetOutput(true);

	if( !N3MessageMgr::CreateInstance() )
		return 0;

	if( !N3DataTransferMgr::CreateInstance() )
		return 0;

//	ZoneServerIdentity();

	if( !NOutputTextMgr::CreateInstance() )
		return 0;

//	if( !CProcessMgr::CreateInstance() )
//		return 0;

	if( !InitInstance(hInstance, nCmdShow) )
	{
		MessageBoxA(NULL, "failed init window", NULL, MB_OK);
		return 0;
	}

	lcApp* app = new(std::nothrow) lcApp();
	if( app == NULL )
		return 0;

	std::pair<bool,std::string> ret = app->lcApp::Startup();
	if( !ret.first )
	{
		MessageBoxA(NULL, ret.second.c_str(), "Startup()", MB_OK);
		return 0;
	}

//	if( !CProcessMgr::GetObj()->CProcessMgr::Start() )
//	{
//		MessageBoxA(NULL, "Start Fail", "InsanceCProcessMgr", MB_OK);
//		return 0;
//	}

	MSG msg = {};
	while( msg.message != WM_QUIT )
	{
		if( PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else
		{
			WaitMessage();
		}
	}

//	CProcessMgr::GetObj()->C2ClientWorkThread::Stop();
	app->lcApp::Cleanup();
	delete app;
//	CProcessMgr::DestroyInstance();
	NOutputTextMgr::DestroyInstance();
	N3MessageMgr::DestroyInstance();
	N3DataTransferMgr::DestroyInstance();
	NTraceLog::DestroyInstance();
	NCriticalErrorLog::DestroyInstance();
	CMyMiniDumpUnhandledExceptionHandler::DestroyInstance();

	ExitProcess(EXIT_SUCCESS);
}
