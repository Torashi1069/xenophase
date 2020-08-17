#include "ExceptionHandler.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "Session.h"
#include "Skin.h"
#include "Struct.h"
#include "Weather.h"
#include "WinMain.h"
#include "3dLib/Device.h"
#include "3dLib/Prim.h"
#include "3dLib/Renderer.h"
#include "3dLib/Texture.h"
#include "Base/FileMgr.h"
#include "Base/FindHack.h"
#include "Base/Res.h"
#include "Base/Util.h"
#include "Device/Connection.h"
#include "Device/Control.h"
#include "Device/Sound.h"
#include "Device/Timer.h"
#include "Framework/Language.h"
#include "Framework/Locale.h"
#include "Movie/CBink.h"
#include "Resource/Model.h"
#include "Window/UIWindowMgr.h"
#include <Objbase.h> // CoInitialize(), CoUninitialize()
#include <TlHelp32.h>
#include <Psapi.h>
#include <float.h> // _controlfp()


/// globals
HINSTANCE& g_hInstance = VTOR<HINSTANCE>(SymDB::Find("g_hInstance")); // = ?;
char(& g_baseDir)[128] = VTOR<char[128]>(SymDB::Find("g_baseDir")); // = "data\\"
char(& g_baseDir3)[128] = VTOR<char[128]>(SymDB::Find("g_baseDir3")); // = ?
const char*& g_regPath = VTOR<const char*>(SymDB::Find("g_regPath")); // = "";
int& g_showTipsAtStartup = VTOR<int>(SymDB::Find("g_showTipsAtStartup")); // = 1;
int& g_isLightMap = VTOR<int>(SymDB::Find("g_isLightMap")); // = 1;
int& g_isXHalfSpr = VTOR<int>(SymDB::Find("g_isXHalfSpr")); // = ?;
int& g_isYHalfSpr = VTOR<int>(SymDB::Find("g_isYHalfSpr")); // = ?;
int& g_texLenDivFactor = VTOR<int>(SymDB::Find("g_texLenDivFactor")); // = 1;
int& g_isVoodoo = VTOR<int>(SymDB::Find("g_isVoodoo")); // = ?;
DWORD& g_soundMode = VTOR<DWORD>(SymDB::Find("g_soundMode")); // = 2;

/// locals
static int& WINDOW_WIDTH = VTOR<int>(SymDB::Find("WINDOW_WIDTH")); // = 640;
static int& WINDOW_HEIGHT = VTOR<int>(SymDB::Find("WINDOW_HEIGHT")); // = 480;


bool IsWin9X()
{
	OSVERSIONINFOEXA osi = {};
	osi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);

	// try extended structure
	if( GetVersionExA((LPOSVERSIONINFOA)&osi) == TRUE )
		return ( osi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS );

	// try basic structure
	osi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
	if( GetVersionExA((LPOSVERSIONINFOA)&osi) == TRUE )
		return ( osi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS );

	// unable to determine answer.
	return false;
};


bool SearchProcessIn9X()
{
	HMODULE hInstLib = LoadLibraryA("kernel32.dll");

	__try {
	///////

	if( hInstLib == NULL )
		return false;

	typedef HANDLE (WINAPI * CREATETOOLHELP32SNAPSHOTFUNC)(DWORD dwFlags, DWORD th32ProcessID);
	typedef BOOL (WINAPI * PROCESS32FIRSTFUNC)(HANDLE hSnapshot, tagPROCESSENTRY32* lppe);
	typedef BOOL (WINAPI * PROCESS32NEXTFUNC)(HANDLE hSnapshot, tagPROCESSENTRY32* lppe);
	CREATETOOLHELP32SNAPSHOTFUNC lpfCreateToolhelp32Snapshot = (CREATETOOLHELP32SNAPSHOTFUNC)GetProcAddress(hInstLib, "CreateToolhelp32Snapshot");
	PROCESS32FIRSTFUNC lpfProcess32First = (PROCESS32FIRSTFUNC)GetProcAddress(hInstLib, "Process32First");
	PROCESS32NEXTFUNC lpfProcess32Next = (PROCESS32NEXTFUNC)GetProcAddress(hInstLib, "Process32Next");

	if( lpfCreateToolhelp32Snapshot == NULL || lpfProcess32First == NULL || lpfProcess32Next == NULL )
		return false;

	HANDLE hSnapshot = lpfCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if( hSnapshot == INVALID_HANDLE_VALUE )
		return false;

	char szProcessName[MAX_PATH] = "unknown";

	tagPROCESSENTRY32 pe32;
	if( lpfProcess32First(hSnapshot, &pe32) )
	{
		while( 1 )
		{
			BOOL bContinue = lpfProcess32Next(hSnapshot, &pe32);

			int i;
			for( i = strlen(pe32.szExeFile) - 1; i > 0; --i )
			{
				if( pe32.szExeFile[i] == '\\' )
				{
					++i;
					break;
				}
			}

			strcpy(szProcessName, &pe32.szExeFile[i]);
			for( char* p = szProcessName; *p != '\0'; ++p )
				if( islower(*p) )
					*p -= 32;

			puts(szProcessName);

			if( strcmp(szProcessName, "RAGEXE.EXE") == 0
			 || strcmp(szProcessName, "SAKEXE.EXE") == 0
			 || strcmp(szProcessName, "RAGEXERE.EXE") == 0
			 || strcmp(szProcessName, "RAGTESTEXE.EXE") == 0
			 || strcmp(szProcessName, "SAKTESTEXE.EXE") == 0
			 || strcmp(szProcessName, "ADTESTEXE.EXE") == 0
			 || strcmp(szProcessName, "RAGEXE_M.EXE") == 0
			 || strcmp(szProcessName, "SAKEXE_M.EXE") == 0 )
				return true; //FIXME: handle leak

			if( !bContinue )
				break;
		}
	}

	CloseHandle(hSnapshot);
	return false;

	///////
	} __finally {
	///////
	if( hInstLib != NULL )
		FreeLibrary(hInstLib);
	///////
	}
}


bool SearchProcessInNT()
{
	HMODULE hInstLib = LoadLibraryA("psapi.dll");

	__try {
	///////

	if( hInstLib == NULL )
		return false;

	char szProcessName[MAX_PATH] = "unknown";

	typedef BOOL (WINAPI * ENUMPROCESSESFUNC)(DWORD* pProcessIds, DWORD cb, DWORD* pBytesReturned);
	typedef BOOL (WINAPI * ENUMPROCESSMODULESFUNC)(HANDLE hProcess, HMODULE* lphModule, DWORD cb, LPDWORD lpcbNeeded);
	typedef DWORD (WINAPI * GETMODULEBASENAMEAFUNC)(HANDLE hProcess, HMODULE hModule, LPSTR lpBaseName, DWORD nSize);
	ENUMPROCESSESFUNC lpfEnumProcesses = (ENUMPROCESSESFUNC)GetProcAddress(hInstLib, "EnumProcesses");
	ENUMPROCESSMODULESFUNC lpfEnumProcessModules = (ENUMPROCESSMODULESFUNC)GetProcAddress(hInstLib, "EnumProcessModules");
	GETMODULEBASENAMEAFUNC lpfGetModuleBaseName = (GETMODULEBASENAMEAFUNC)GetProcAddress(hInstLib, "GetModuleBaseNameA");

	if( lpfEnumProcesses == NULL || !lpfEnumProcessModules || lpfGetModuleBaseName == NULL )
		return false;

	DWORD dwProcessId[1024];
	DWORD cbNeeded;
	if( !lpfEnumProcesses(dwProcessId, sizeof(dwProcessId), &cbNeeded) )
		return false;

	DWORD cProcesses = cbNeeded / sizeof(DWORD);
	for( DWORD i = 0; i < cProcesses; ++i )
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessId[i]);
		HMODULE hMod[1];
		if( hProcess != NULL && lpfEnumProcessModules(hProcess, hMod, sizeof(hMod), &cbNeeded) )
		{
			lpfGetModuleBaseName(hProcess, hMod[0], szProcessName, sizeof(szProcessName));
			for( char* p = szProcessName; *p != '\0'; ++p )
				if( islower(*p) )
					*p -= 32;

			puts(szProcessName);

			if( !strcmp(szProcessName, "RAGEXE.EXE")
			 || !strcmp(szProcessName, "SAKEXE.EXE")
			 || !strcmp(szProcessName, "RAGEXERE.EXE") )
			 return true; //FIXME: handle leak
		}

		CloseHandle(hProcess);
	}

	return false;

	///////
	} __finally {
	///////
	if( hInstLib != NULL )
		FreeLibrary(hInstLib);
	///////
	}
}


void CheckSystemMessage()
{
	MSG msg;

	while( PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) )
	{
		if( msg.message == WM_KEYDOWN && msg.wParam == VK_PROCESSKEY )
			g_language->SetKeyStroke(ImmGetVirtualKey(msg.hwnd));

		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}


hook_func<LRESULT (CALLBACK *)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)> _WindowProc("WindowProc");
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return _WindowProc(hWnd, message, wParam, lParam);

	//TODO
}


BOOL InitApp(HINSTANCE hInstance, int nCmdShow)
{
	g_hInstance = hInstance;

	WNDCLASSA wc;
	wc.style = 0;
	wc.lpfnWndProc = &WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIconA(hInstance, MAKEINTRESOURCEA(119));
	wc.hCursor = LoadCursorA(NULL, MAKEINTRESOURCEA(IDC_ARROW));
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_NAME;
	RegisterClassA(&wc);

	RECT windowRect;
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = WINDOW_WIDTH;
	windowRect.bottom = WINDOW_HEIGHT;
	AdjustWindowRect(&windowRect, WS_CLIPCHILDREN|WS_CAPTION|WS_GROUP, FALSE);

	int X = g_session.CSession::GetOptionValue("Window_XPos", (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2);
	int Y = g_session.CSession::GetOptionValue("Window_YPos", (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2);
	if( X > GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH )
		X = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2;
	if( X < 0 )
		X = 0;
	if( Y > GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT )
		Y = (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2;
	if( Y < 0 )
		Y = 0;

	g_hMainWnd = CreateWindowExA(0, wc.lpszClassName, WINDOW_NAME, WS_CLIPCHILDREN|WS_CAPTION|WS_GROUP, X, Y, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, hInstance, NULL);
	if( g_hMainWnd == NULL )
	{
		MessageBoxA(NULL, "Window Creation Failed", "ERROR", MB_OK);
		return FALSE;
	}

	ShowWindow(g_hMainWnd, SW_SHOW);
	UpdateWindow(g_hMainWnd);

	GetCurrentDirectoryA(sizeof(g_baseDir3), g_baseDir3);
	return TRUE;
}


void ExitApp()
{
	CheckSystemMessage(); // inlined
	CoUninitialize();
	DestroyWindow(g_hMainWnd);
}


BOOL ReadRegistry()
{
	HKEY hResultKey;
	LSTATUS ret = RegOpenKeyExA(HKEY_LOCAL_MACHINE, g_regPath, 0, KEY_QUERY_VALUE, &hResultKey);
	RegCloseKey(hResultKey);
	if( ret != 0 )
		return FALSE;

	DWORD reg_Type;
	DWORD Datalength;

	HKEY hKey;
	if( !RegOpenKeyExA(HKEY_LOCAL_MACHINE, g_regPath, 0, KEY_QUERY_VALUE, &hKey) )
	{
		reg_Type = REG_DWORD;
		Datalength = sizeof(DWORD);

		if( g_serviceType != ServiceVietnam )
			RegQueryValueExA(hKey, "ISFULLSCREENMODE", 0, &reg_Type, (LPBYTE)&g_registry.m_isFullScreenMode, &Datalength);
		else
		if( RegQueryValueExA(hKey, "ISFULLSCREENMODE", 0, &reg_Type, (LPBYTE)&g_registry.m_isFullScreenMode, &Datalength) )
			return FALSE;

		RegQueryValueExA(hKey, "WIDTH", 0, &reg_Type, (LPBYTE)&g_registry.m_width, &Datalength);
		RegQueryValueExA(hKey, "HEIGHT", 0, &reg_Type, (LPBYTE)&g_registry.m_height, &Datalength);
		if( !g_registry.m_isFullScreenMode )
		{
			WINDOW_WIDTH = g_registry.m_width;
			WINDOW_HEIGHT = g_registry.m_height;
		}

		RegQueryValueExA(hKey, "BITPERPIXEL", 0, &reg_Type, (LPBYTE)&g_registry.m_bitPerPixel, &Datalength);
		RegQueryValueExA(hKey, "DEVICECNT", 0, &reg_Type, (LPBYTE)&g_registry.m_deviceCnt, &Datalength);
		RegQueryValueExA(hKey, "MODECNT", 0, &reg_Type, (LPBYTE)&g_registry.m_modeCnt, &Datalength);
		RegQueryValueExA(hKey, "ISVOODOO", 0, &reg_Type, (LPBYTE)&g_registry.m_isVoodoo, &Datalength);
		RegQueryValueExA(hKey, "SHOWTIPSATSTARTUP", 0, &reg_Type, (LPBYTE)&g_showTipsAtStartup, &Datalength);

		if( RegQueryValueExA(hKey, "ISLIGHTMAP", 0, &reg_Type, (LPBYTE)&g_isLightMap, &Datalength) )
		{
			g_Weather.CWeather::SetObjLight(true);
			g_isLightMap = 1;
		}
		else
		{
			if( g_isLightMap == 1 )
				g_Weather.CWeather::SetObjLight(true);
			else
				g_Weather.CWeather::SetObjLight(false);
		}

		if( RegQueryValueExA(hKey, "TRILINEARFILTER", 0, &reg_Type, (LPBYTE)&g_registry.m_trilinearFilter, &Datalength) )
			g_registry.m_trilinearFilter = 0;

		if( RegQueryValueExA(hKey, "SPRITEMODE", 0, &reg_Type, (LPBYTE)&g_registry.m_spriteMode, &Datalength) )
			g_registry.m_spriteMode = 2;

		if( g_registry.m_spriteMode == 0 )
		{
			g_isXHalfSpr = 1;
			g_isYHalfSpr = 1;
		}
		else
		if ( g_registry.m_spriteMode == 1 )
		{
			g_isYHalfSpr = 1;
		}
		else
		{
			g_isXHalfSpr = 0;
			g_isYHalfSpr = 0;
		}

		if( RegQueryValueExA(hKey, "TEXTUREMODE", 0, &reg_Type, (LPBYTE)&g_registry.m_textureMode, &Datalength) )
			g_registry.m_textureMode = 2;

		if( g_registry.m_textureMode == 0 )
			g_texLenDivFactor = 4;
		else
		if( g_registry.m_textureMode == 1 )
			g_texLenDivFactor = 2;
		else
			g_texLenDivFactor = 1;

		if( g_showTipsAtStartup != 1 && g_showTipsAtStartup != 0 )
			g_showTipsAtStartup = 1;

		reg_Type = REG_SZ;
		Datalength = sizeof(g_registry.m_deviceName);
		RegQueryValueExA(hKey, "DEVICENAME", 0, &reg_Type, (LPBYTE)g_registry.m_deviceName, &Datalength);

		reg_Type = REG_BINARY;
		Datalength = sizeof(g_registry.m_guidDevice);
		RegQueryValueExA(hKey, "GUIDDEVICE", 0, &reg_Type, (LPBYTE)&g_registry, &Datalength);

		reg_Type = REG_BINARY;
		Datalength = sizeof(g_registry.m_guidDriver);
		RegQueryValueExA(hKey, "GUIDDRIVER", 0, &reg_Type, (LPBYTE)&g_registry.m_guidDriver, &Datalength);

		RegCloseKey(hKey);
	}

	g_isVoodoo = g_registry.m_isVoodoo;

	if( !RegOpenKeyExA(HKEY_LOCAL_MACHINE, g_regPath, 0, KEY_QUERY_VALUE, &hKey) )
	{
		reg_Type = REG_DWORD;
		Datalength = sizeof(DWORD);

		RegQueryValueExA(hKey, "SOUNDMODE", 0, &reg_Type, (LPBYTE)&g_registry.m_soundMode, &Datalength);
		RegQueryValueExA(hKey, "SPEAKERTYPE", 0, &reg_Type, (LPBYTE)&g_registry.m_speakerType, &Datalength);
		RegQueryValueExA(hKey, "DIGITALRATETYPE", 0, &reg_Type, (LPBYTE)&g_registry.m_digitalrateType, &Datalength);
		RegQueryValueExA(hKey, "DIGITALBITSTYPE", 0, &reg_Type, (LPBYTE)&g_registry.m_digitalbitsType, &Datalength);

		if( RegQueryValueExA(hKey, "NUMSAMPLETYPE", 0, &reg_Type, (LPBYTE)&g_registry.m_numSampleType, &Datalength) )
			g_registry.m_numSampleType = 2;

		reg_Type = REG_SZ;
		Datalength = sizeof(g_registry.m_providerName);
		RegQueryValueExA(hKey, "PROVIDERNAME", 0, &reg_Type, (LPBYTE)g_registry.m_providerName, &Datalength);

		RegCloseKey(hKey);
	}

	g_soundMode = g_registry.m_soundMode;
	return TRUE;
}


BOOL SetupDriver2()
{
	if( g_registry.m_soundMode != 0 && !InitMSS() )
	{
		ErrorMsg("Audio System Init Failed");
		g_soundMode = 0;
		return FALSE;
	}

	DWORD dwFlags = 2|4;
	if( g_registry.m_isFullScreenMode != 0 )
		dwFlags |= 1;

	DDSURFACEDESC2 ddsd;
	ddsd.dwHeight = g_registry.m_height;
	ddsd.dwWidth = g_registry.m_width;
	ddsd.ddpfPixelFormat.dwRGBBitCount = g_registry.m_bitPerPixel;
	ddsd.dwMipMapCount = 0;

	if( FAILED(g_3dDevice.C3dDevice::Init(g_hMainWnd, &g_registry.m_guidDriver, &g_registry.m_guidDevice, &ddsd, dwFlags)) )
	{
		ErrorMsg("Cannot init d3d OR grf file has problem.");
		return FALSE;
	}

	return TRUE;
}


HANDLE ExcuteProgram(const char* excutiveFile)
{
	char excutiveFileName[256];
	strcpy(excutiveFileName, excutiveFile);

	STARTUPINFOA StartupInfo = {};
	PROCESS_INFORMATION ProcessInformation = {};

	StartupInfo.cb = sizeof(StartupInfo);
	StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
	StartupInfo.wShowWindow = SW_SHOWNORMAL;

	CreateProcessA(NULL, excutiveFileName, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInformation);

	return ProcessInformation.hProcess;
}


bool UpdatePatch(const char* patch, const char* pactchup)
{
	if( _access(pactchup, 0) != 0 )
		return false;

	char buf[256];
	if( g_serviceType != ServiceBrazil )
		sprintf(buf, "%s is changed. Press ok to restart", patch);
	else
		sprintf(buf, "%s foi modificada. Clique em Ok para continuar.", patch);

	if( MessageBoxA(NULL, buf, "Alert", MB_ICONASTERISK|MB_OKCANCEL) != IDOK )
		return false;

	chmod(patch, _S_IWRITE);
	unlink(patch);
	if( rename(pactchup, patch) != 0 )
		return false;

	ExcuteProgram(patch); // inlined
	return true;
}


hook_func<int (__cdecl *)(void)> _InitHShield("InitHShield");
int __cdecl InitHShield(void)
{
	return (_InitHShield)();

	//TODO
}


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SearchProcessInNT();
//	SetUnhandledExceptionFilter(&aossdkExceptionFilter); //NOTE: do not want
	SetUnhandledExceptionFilter(&ExceptionFilter);

	if( strstr(lpCmdLine, "1rag1") == NULL
	 && strstr(lpCmdLine, "1sak1") == NULL
	 && strstr(lpCmdLine, "1gld1") == NULL
	 && strstr(lpCmdLine, "2rag2") == NULL
	 && strstr(lpCmdLine, "1eve1") == NULL
	 && strstr(lpCmdLine, "1pk1" ) == NULL )
	{
		ErrorMsg(PLEASE_EXCUTE_LAUNCHER);
		return 0;
	}

	if( strstr(lpCmdLine, "2rag2") != NULL )
		g_EXE_way = 2;

	g_session.m_isCheckToPcbang = ( strstr(lpCmdLine, "pc") != NULL );

	g_fileMgr.CFileMgr::AddPak("data.grf");
	g_fileMgr.CFileMgr::AddPak("rdata.grf");

	char clientinfofile[64] = "clientinfo.xml";
	char* account = strstr(lpCmdLine, "/account:");
	if( account != NULL )
		sscanf(account, "/account:%s", clientinfofile); // simplified

	InitClientInfo(clientinfofile);

	if( g_serviceType == ServiceChina && strstr(clientinfofile, "clientinfo") != NULL )
		g_bUseCommand = false;

	if( UpdatePatch(PATCH_CLIENT, PATCH_UP) ) // inlined
		return 0;

	g_session.CSession::Init();

	char srcPath[20] = "Setup.exe";
	char dstPath[20] = "Setup\\Setup.exe";
	while( !ReadRegistry() )
		WaitForSingleObject(ExcuteProgram(srcPath), INFINITE); // inlined

	_controlfp(_PC_24, _MCW_PC);

	UINT wTimerRes = 0;
	TIMECAPS tc;
	if( !timeGetDevCaps(&tc, sizeof(tc)) )
	{
		wTimerRes = CAP_VALUE(tc.wPeriodMin, 1, tc.wPeriodMax);
		timeBeginPeriod(wTimerRes);
	}

	ResetTimer();

	CoInitialize(NULL);

    if( g_serviceType != ServiceKorea
	 && g_serviceType != ServiceChina
	 && g_serviceType != ServiceThai
	 && g_serviceType != ServiceAmerica
	 && g_serviceType != ServiceGermany
	 && g_serviceType != ServiceBrazil
	 && g_serviceType != ServiceFrance
	 && g_serviceType != ServiceRussia
	 && g_serviceType != ServiceVietnam
	 && g_serviceType != ServiceSingapore )
    {
		char mutexName[64] = {};
		sprintf(mutexName, "Global\\%s", mutexKey);

		HANDLE hMutex = CreateMutexA(NULL, FALSE, mutexKey);

		if( WaitForSingleObject(hMutex, 0) != WAIT_OBJECT_0 )
			return 1;

		if( mutexKey[0] + mutexKey[1] + mutexKey[2] + mutexKey[3] + mutexKey[4] + mutexKey[5] + mutexKey[6] != 713 )
			return 1;
	}

	g_session.CSession::Create();

	if( g_serviceType == ServiceKorea )
	{
		bool isFound = ( IsWin9X() ) ? SearchProcessIn9X() : SearchProcessInNT(); // inlined
		if( !isFound )
		{
			MessageBoxA(g_hMainWnd, "정상적인 라그나로크 클라이언트를 실행시켜 주시기 바랍니다.", NULL, 0); // "Please run the normal Ragnarok client."
			return 0;
		}
	}

	g_resMgr().CResMgr::ReadResNameTable("resNameTable.txt");

	if( !InitApp(hInstance, nCmdShow) )
		return 1;

	if( InitHShield() == 0 )
		return 1;

	if( !SetupDriver2() ) // inlined
		return 1;

	g_renderer = g_3dDevice.C3dDevice::CreateRenderer();

	if( !CConnection::Startup() )
		return 1;

	InitTimer(60);
	SetFocus(g_hMainWnd);

	if( g_3dDevice.C3dDevice::IsFullscreen() )
		ShowCursor(FALSE);

	g_mouse.CMouse::Init();
	g_windowMgr.UIWindowMgr::SetSize(g_renderer->CRenderer::GetWidth(), g_renderer->CRenderer::GetHeight());
	g_windowMgr.UIWindowMgr::InitUIRectInfoFromReg();
	g_GrannyBoneRes.C3dGrannyBoneRes::Init();
	g_GrannyBoneRes.C3dGrannyBoneRes::AddBone("model\\3dmob\\guildflag90_1.gr2", 5, 0);
	g_skinMgr.CSkinMgr::Init();
	CreateTrigonometricTable();

	switch( g_serviceType )
	{
	case ServiceKorea:
		g_loginStartMode = 0;
	break;
	case ServiceTaiwan:
	case ServiceMalaysia:
	case ServiceSingapore:
	case ServiceBrazil:
		g_loginStartMode = 1;
	break;
	case ServiceJapan:
	case ServiceChina:
	case ServiceArabic:
		g_loginStartMode = 2;
	break;
	case ServiceIndonesia:
		if( g_serverType == ServerPrimary )
			g_loginStartMode = 1;
		else
			g_loginStartMode = 0;
	break;
	default:
		if( g_serverType == ServerPrimary || g_serverType == ServerPK )
			g_loginStartMode = 2;
		else
			g_loginStartMode = 0;
	break;
	};

	g_Bink.CBink::OpenningMain(1);

	g_modeMgr.CModeMgr::Run(MT_LOGIN, "login.rsw");

	UnInitMSS();
	g_windowMgr.UIWindowMgr::DestroyDC();
	CRagConnection::instanceR().CConnection::Disconnect();
	CConnection::Cleanup();
	g_windowMgr.UIWindowMgr::RemoveAllWindows();
	g_windowMgr.UIWindowMgr::WriteUIRectInfoToReg();
	g_session.CSession::WriteOptionToLuaFile();
	g_resMgr().CResMgr::Reset();
	g_texMgr.CTexMgr::DestroyAllTexture();
	g_3dDevice.C3dDevice::DestroyRenderer(g_renderer);
	g_3dDevice.C3dDevice::DestroyObjects();
	g_mouse.CMouse::Exit();
	ExitApp(); // inlined
	DeleteHack();
	CScheduler::getInstance()->CScheduler::Clear();
	CoUninitialize();

	if( wTimerRes != 0 ) timeEndPeriod(wTimerRes);

	return 0;
}
