#include "ExceptionHandler.h" // ExceptionFilter()
#include "Globals.h" // ErrorMsg()
#include "ModeMgr.h"
#include "MsgStrings.h" // MsgStr()
#include "Struct.h"
#include "Base/FileMgr.h"
#include "Base/FindHack.h"
#include "Base/ResMgr.h" // g_resMgr()
#include "3dLib/Prim.h" // CreateTrigonometricTable()
#include "Device/Connection.h"
#include "Device/Control.h" // SetAcquire()
#include "Device/Sound.h" // InitMSS()
#include "Device/Timer.h" // ResetTimer()
#include "Framework/Locale.h" // InitClientInfo()
#include "Window/UIWindowMgr.h"
#include <sys/stat.h> //_S_IWRITE


hook_func<void (__cdecl *)(void)> _CheckSystemMessage(SAKEXE, "CheckSystemMessage");
void __cdecl CheckSystemMessage(void) // line 75
{
	return (_CheckSystemMessage)();

	MSG msg;
	while( PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) )
	{
		if( msg.message == WM_KEYDOWN && msg.wParam == VK_PROCESSKEY )
			g_language->SetKeyStroke(ImmGetVirtualKey(msg.hwnd));

		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}


hook_func<LRESULT (CALLBACK *)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)> _WindowProc(SAKEXE, "WindowProc");
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // line 106
{
	return (_WindowProc)(hWnd, message, wParam, lParam);

	bool hooked;
	LRESULT ret = g_language->ProcessImeMessage(hWnd, message, wParam, lParam, &hooked);

	if( hooked )
	{
		if( g_language->CLanguage::GetCandidateCount() != 0 )
		{
			mystd::string strCandidate[9];
			int intArray[4];

			int v14 = g_language->CLanguage::GetCandidateSelection() - g_language->CLanguage::GetCandidateSelection() % 9;
			int v13 = v14 + 9;
			if( v13 >= g_language->CLanguage::GetCandidateCount() )
				v13 = g_language->CLanguage::GetCandidateCount();

			intArray[0] = g_language->CLanguage::GetCandidateSelection() - v14;
			intArray[1] = (g_language->CLanguage::GetCandidateSelection() + 8) / 9;
			intArray[2] = (g_language->CLanguage::GetCandidateCount() + 8) / 9;
			intArray[3] = v13 - v14;

			for( int i = 0; i < v13 - v14; ++i )
				strCandidate[i] = g_language->CLanguage::GetCandidateString(v14 + i);

			UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_CANDIDATEWND);
			wnd->SendMsg(NULL, 65, (int)strCandidate, (int)intArray, 0);
		}
		else
		{
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_CANDIDATEWND);
		}

		if( g_language->GetKeyStrokeSize() != 0 )
		{
			UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_KEYSTROKEWND);
			wnd->Invalidate();
		}
		else
		{
			g_windowMgr.UIWindowMgr::DeleteWindow(WID_KEYSTROKEWND);
		}

		return ret;
	}

	switch( message )
	{
	case WM_CREATE:
	case WM_DESTROY:
		return 0;

	case WM_MOVE:
		if( g_isAppActive != 1 && !g_3dDevice.C3dDevice::IsFullscreen() )
			g_3dDevice.C3dDevice::ShowFrame(true);

		return 0;

	case WM_ACTIVATE:
		if( !g_3dDevice.C3dDevice::IsFullscreen() )
			return 1;

		if( g_isAppActive == 1 )
		{
			g_activatedNow = 1;
			ShowWindow(hWnd, SW_MAXIMIZE);
		}
		else
		{
			ShowWindow(hWnd, SW_MINIMIZE);
		}

		return 1;

	case WM_SETFOCUS:
		if( g_Bink.CBink::IsBinkPlaying() )
			g_Bink.CBink::Pause(0);

		break;

	case WM_KILLFOCUS:
		if( g_Bink.CBink::IsBinkPlaying() )
			g_Bink.CBink::Pause(1);

		if( IsEnableOldKeycrypt() )
			MyStopEncryption();

		break;

	case WM_PAINT:
		ValidateRect(hWnd, NULL);
		return 0;

	case WM_CLOSE:
		g_sysQuit = TRUE;

		if( IsEnableOldKeycrypt() )
			MyCloseDriver();

		if( IsEnableNewKeycrypt() )
			CloseKeyCrypt();

		return 0;

	case WM_ERASEBKGND:
		return 1;

	case WM_SETCURSOR:
		if( !g_3dDevice.C3dDevice::IsFullscreen() )
			SetCursor(NULL);
		return 0;

	case WM_NCACTIVATE:
		g_isAppActive = wParam;
		if( g_isAppActive )
		{
			SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
			SetAcquire(1);
		}
		else
		{
			SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
			SetAcquire(0);
		}

		if( g_isAppActive )
			ResetTimer();

		break;

	case WM_KEYDOWN:
		if( !g_Bink.CBink::Break(wParam) )
			return 0;

		if( g_windowMgr.UIWindowMgr::ProcessPushButton(wParam, ((unsigned int)~lParam >> 30) & 1) )
			return 0;

		if( g_windowMgr.UIWindowMgr::ExcuteMsgInBattleMode(wParam, lParam) )
			return 0;

		g_language->CLanguage::OnKeyDown(wParam, lParam);

		if( g_session.m_isBattle && !g_session.m_isBmChat )
			g_windowMgr.UIWindowMgr::SetTextAtBattleMode();

		return 0;

	case WM_KEYUP:
		if( wParam == VK_SNAPSHOT && g_windowMgr.UIWindowMgr::ProcessPushButton(VK_SNAPSHOT, 1) )
			return 0;
		return 0;

	case WM_CHAR:
		if( g_session.m_isBattle && !g_session.m_isBmChat )
			return 0;

		if( wParam == VK_SPACE && g_session.m_isStartBmChat )
		{
			g_windowMgr.UIWindowMgr::SetTextAtBattleMode();
			g_session.m_isStartBmChat = 0;
		}
		else
		{
			g_language->CLanguage::OnChar(wParam, lParam);
		}

		return 0;

	case WM_SYSKEYDOWN:
		if( !g_windowMgr.UIWindowMgr::ProcessPushButton(wParam, ((unsigned int)~lParam >> 30) & 1) )
			break;
		return 0;

	case WM_SYSCOMMAND:
		switch( wParam & 0xFFF0 )
		{
		case SC_CLOSE:
			break;

		case SC_KEYMENU:
			if( lParam != VK_SPACE )
				return 0;
			break;

		case SC_MOUSEMENU:
		case SC_MOVE:
		case SC_RESTORE:
		case SC_MINIMIZE:
		case SC_MONITORPOWER:
			if( g_3dDevice.C3dDevice::IsFullscreen() )
				return 0;
			break;

		default:
			return 0;
		}

		break;

	case WM_MOUSEMOVE:
		if( g_isAppActive != 1 && !g_3dDevice.C3dDevice::IsFullscreen() )
		{
			POINT Point;
			GetCursorPos(&Point);
			ScreenToClient(g_hMainWnd, &Point);
			g_mouse.CMouse::SetXPos(Point.x);
			g_mouse.CMouse::SetYPos(Point.y);
		}
		break;

	case WM_ENTERMENULOOP:
	case WM_ENTERSIZEMOVE:
		g_isAppActive = 0;
		SetPriorityClass(GetCurrentProcess(), 0x40u);
		SetAcquire(0);
		break;

	case WM_EXITMENULOOP:
	case WM_EXITSIZEMOVE:
		g_isAppActive = ( GetActiveWindow() == hWnd || !IsIconic(hWnd) );
		if( g_isAppActive )
		{
			SetPriorityClass(GetCurrentProcess(), 0x20u);
			SetAcquire(1);
		}
		else
		{
			SetPriorityClass(GetCurrentProcess(), 0x40u);
			SetAcquire(0);
		}
		break;

	case WM_IME_SETCONTEXT:
		return DefWindowProcA(hWnd, message, 1, 0);

	default:
		break;
	}

	return DefWindowProcA(hWnd, message, wParam, lParam);
}


hook_func<BOOL (__cdecl *)(HINSTANCE hInstance, int nCmdShow)> _InitApp(SAKEXE, "InitApp");
BOOL __cdecl InitApp(HINSTANCE hInstance, int nCmdShow) // line 303
{
	return (_InitApp)(hInstance, nCmdShow);

	g_hInstance = hInstance;

	if( strstr(GetCommandLineA(), "/multi") == NULL && FindWindowA(WINDOW_NAME, WINDOW_NAME) != NULL )
		return FALSE;

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
	AdjustWindowRect(&windowRect, WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_GROUP, FALSE);

	int nHeight = windowRect.bottom - windowRect.top;
	int nWidth = windowRect.right - windowRect.left;
	int Y = (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2;
	int X = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2;

	g_hMainWnd = CreateWindowExA(0, wc.lpszClassName, WINDOW_NAME, WS_CLIPCHILDREN|WS_CAPTION|WS_SYSMENU|WS_GROUP, X, Y, nWidth, nHeight, NULL, NULL, hInstance, NULL);
	if( g_hMainWnd == NULL )
	{
		MessageBoxA(NULL, "Window Creation Failed", "ERROR", MB_OK);
		return FALSE;
	}

	ShowWindow(g_hMainWnd, SW_SHOW);
	UpdateWindow(g_hMainWnd);

	if( IsEnableOldKeycrypt() && NpKeyMyLoadLibrary() )
	{
		if( MyInitialize() )
		{
			int err = MyGetInitError();
			if( err == 3 )
			{
				char temp[30];
				memset(temp, 0, sizeof(temp));

				if( MyGetAthKbdObject(temp) )
					MessageBoxA(NULL, temp, MsgStr(MSI_KEYCRYPT), MB_SYSTEMMODAL|MB_ICONASTERISK);

				if( MessageBoxA(NULL, MsgStr(MSI_KEYCRYPT_INSTALL_KEYDRIVER), MsgStr(MSI_KEYCRYPT), MB_SYSTEMMODAL|MB_ICONASTERISK|MB_YESNO) == IDYES )
				{
					if ( MyInstallReg != NULL )
					{
						MyInstallReg();
						MessageBoxA(NULL, MsgStr(MSI_KEYCRYPT_REBOOT), MsgStr(MSI_KEYCRYPT), MB_SYSTEMMODAL|MB_ICONASTERISK);
					}
					else
					{
						MessageBoxA(NULL, MsgStr(MSI_KEYCRYPT_INSTALLFAIL), MsgStr(MSI_KEYCRYPT), MB_HELP|MB_DEFBUTTON2|MB_ICONASTERISK|MB_ICONQUESTION);
					}
					return FALSE;
				}

				MessageBoxA(NULL, MsgStr(MSI_KEYCRYPT_SKIPKEYCRYPT), MsgStr(MSI_KEYCRYPT), MB_SYSTEMMODAL|MB_ICONASTERISK);
			}

			MyRegisterHWNDForEdit(0x10u, g_hMainWnd);
			MyStartEncryption();
		}
		else
		{
			int err = MyGetInitError();
			if( err == 1 )
			{
				MessageBoxA(0, MsgStr(MSI_KEYCRYPT_NOKEYCRYPTFILE), MsgStr(MSI_KEYCRYPT), MB_SYSTEMMODAL|MB_ICONASTERISK);
			}
			else
			if( err == 2 && GetKeyboardType(0) == 81 )
			{
				if( MessageBoxA(NULL, MsgStr(MSI_KEYCRYPT_USBKEYBOARD), MsgStr(MSI_KEYCRYPT), MB_HELP|MB_DEFBUTTON2|MB_ICONASTERISK|MB_ICONQUESTION|MB_YESNO) == IDYES )
				{
					if( MyInstallReg != NULL )
					{
						MyInstallReg();
						MessageBoxA(NULL, MsgStr(MSI_KEYCRYPT_REBOOT), MsgStr(MSI_KEYCRYPT), MB_SYSTEMMODAL|MB_ICONASTERISK);
					}
					else
					{
						MessageBoxA(NULL, MsgStr(MSI_KEYCRYPT_INSTALLFAIL), MsgStr(MSI_KEYCRYPT), MB_HELP|MB_DEFBUTTON2|MB_ICONASTERISK|MB_ICONQUESTION);
					}
					return FALSE;
				}

				MessageBoxA(NULL, MsgStr(MSI_KEYCRYPT_SKIPKEYCRYPT), MsgStr(MSI_KEYCRYPT), MB_SYSTEMMODAL|MB_ICONASTERISK);
			}
		}
	}

	GetCurrentDirectoryA(sizeof(g_baseDir3), g_baseDir3);
	return TRUE;
}


hook_func<void (__cdecl *)(void)> _ExitApp(SAKEXE, "ExitApp");
void __cdecl ExitApp(void) // line 430
{
	return (_ExitApp)();

	CheckSystemMessage(); // inlined
	CoUninitialize();
	DestroyWindow(g_hMainWnd);
}


BOOL __cdecl ReadRegistry(void) // line 439
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

		RegQueryValueExA(hKey, "ISFULLSCREENMODE", 0, &reg_Type, (LPBYTE)&g_registry.m_isFullScreenMode, &Datalength);

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
			g_isLightMap = 1;

		if( RegQueryValueExA(hKey, "TRILINEARFILTER", 0, &reg_Type, (LPBYTE)&g_registry.m_trilinearFilter, &Datalength) )
			g_registry.m_trilinearFilter = 0;

		if( g_isLightMap != 1 )
			g_Weather.CWeather::SetObjLight(false);

		if( RegQueryValueExA(hKey, "SPRITEMODE", 0, &reg_Type, (LPBYTE)&g_registry.m_spriteMode, &Datalength) )
			g_registry.m_spriteMode = 2;

		if( g_registry.m_spriteMode == 0 )
		{
			g_isXHalfSpr = 1;
			g_isYHalfSpr = 1;
		}

		if( g_registry.m_spriteMode == 1 )
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
		RegQueryValueExA(hKey, "DEVICENAME", 0, &reg_Type, (LPBYTE)&g_registry.m_deviceName, &Datalength);

		reg_Type = REG_BINARY;
		Datalength = sizeof(g_registry.m_guidDevice);
		RegQueryValueExA(hKey, "GUIDDEVICE", 0, &reg_Type, (LPBYTE)&g_registry.m_guidDevice, &Datalength);

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
		RegQueryValueExA(hKey, "PROVIDERNAME", 0, &reg_Type, (LPBYTE)&g_registry.m_providerName, &Datalength);

		RegCloseKey(hKey);
	}

	g_soundMode = g_registry.m_soundMode;
	return TRUE;
}


BOOL SetupDriver2() // line 551
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
		ErrorMsg("Cannot init d3d!");
		return FALSE;
	}

	return TRUE;
}


hook_func<HANDLE (__cdecl *)(const char* excutiveFile)> _ExcuteProgram(SAKEXE, "ExcuteProgram");
HANDLE __cdecl ExcuteProgram(const char* excutiveFile) // line 600
{
	return (_ExcuteProgram)(excutiveFile);

	char excutiveFileName[256];
	strcpy(excutiveFileName, excutiveFile);

	STARTUPINFOA StartupInfo = {};
	PROCESS_INFORMATION pi = {};

	StartupInfo.cb = sizeof(StartupInfo);
	StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
	StartupInfo.wShowWindow = SW_SHOWNORMAL;

	CreateProcessA(NULL, excutiveFileName, NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &pi);

	return pi.hProcess;
}


hook_func<bool (__cdecl *)(const char* patch, const char* pactchup)> _UpdatePatch(SAKEXE, "UpdatePatch");
bool __cdecl UpdatePatch(const char* patch, const char* pactchup) // line 579
{
	return (_UpdatePatch)(patch, pactchup);

	if( access(pactchup, 0) != 0 )
		return false;

	char buf[256];
	sprintf(buf, "%s is changed. Press ok to restart", patch);

	if( MessageBoxA(NULL, buf, "Alert", MB_ICONASTERISK|MB_OKCANCEL) != IDOK )
		return false;

	chmod(patch, _S_IWRITE);
	unlink(patch);
	if( rename(pactchup, patch) != 0 )
		return false;

	ExcuteProgram(patch); // inlined

	return true;
}


hook_func<int (__stdcall *)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)> _WinMain(SAKEXE, "WinMain");
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) // line 630
{
	return (_WinMain)(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	SetUnhandledExceptionFilter(&ExceptionFilter);

	if( strstr(lpCmdLine, "1rag1") == NULL )
	{
		ErrorMsg(PLEASE_EXCUTE_LAUNCHER);
		return 0;
	}

	g_fileMgr.CFileMgr::AddPak("data.grf");
	g_fileMgr.CFileMgr::AddPak("sdata.grf");

	char clientinfofile[64] = "sclientinfo.xml";
	char* account = strstr(lpCmdLine, "/account:");
	if( account != NULL )
		sscanf(account, "/account:%s", clientinfofile); // simplified

	InitClientInfo(clientinfofile);

	if( UpdatePatch(PATCH_CLIENT, PATCH_UP) ) // inlined
		return 0;

	g_session.CSession::Init();

	while( !ReadRegistry() )
		WaitForSingleObject(ExcuteProgram("setup.exe"), INFINITE); // inlined

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

	if( strstr(GetCommandLineA(), "/multi") == NULL )
	{
		HANDLE hMutex = CreateMutexA(NULL, FALSE, mutexKey);

		if( WaitForSingleObject(hMutex, 0) != WAIT_OBJECT_0 )
			return 1;

		if( mutexKey[0] + mutexKey[1] + mutexKey[2] + mutexKey[3] + mutexKey[4] + mutexKey[5] + mutexKey[6] != 713 )
			return 1;
	}

	if( g_serviceType == ServiceThai )
	{
		MoveFileA("65.mp3", "BGM\\65.mp3");
		MoveFileA("66.mp3", "BGM\\66.mp3");
		MoveFileA("67.mp3", "BGM\\67.mp3");
		MoveFileA("70.mp3", "BGM\\70.mp3");
		DeleteFileA("65.mp3");
		DeleteFileA("66.mp3");
		DeleteFileA("67.mp3");
		DeleteFileA("70.mp3");
	}

	g_session.CSession::Create();

	int bFindhackResult;
	if( IsEnableNewKeycrypt() )
		bFindhackResult = ProcessFindHack2();
	else
	if( IsEnableOldKeycrypt() )
		bFindhackResult = ProcessFindHack1();
	else
		bFindhackResult = wTimerRes; //NOTE: uninitialized variable stack reuse

	if( bFindhackResult == 0 )
		return 1;

	g_resMgr().CResMgr::ReadResNameTable("resNameTable.txt");

	if( !InitApp(hInstance, nCmdShow) )
		return 1;

	if( !SetupDriver2() ) // inlined
		return 1;

	g_renderer = g_3dDevice.C3dDevice::CreateRenderer();

	if( !CConnection::Startup() )
		return 1;

	InitTimer(60);
	SetFocus(g_hMainWnd);

	if( g_3dDevice.IsFullscreen() )
		ShowCursor(FALSE);

	g_mouse.CMouse::Init();
	g_windowMgr.UIWindowMgr::SetSize(g_renderer->GetWidth(), g_renderer->GetHeight());
	g_windowMgr.UIWindowMgr::InitUIRectInfoFromReg();
	g_GrannyBoneRes.C3dGrannyBoneRes::Init();
	g_skinMgr.CSkinMgr::Init();
	CreateTrigonometricTable();

	if( g_serviceType == ServiceTaiwan
	||  g_serviceType == ServiceChina
	||  g_serviceType == ServiceAmerica
	||  g_serviceType == ServiceMalaysia
	||  g_serviceType == ServiceSingapore )
	{
		g_loginStartMode = 1;
	}
	else if( g_serverType == ServerPrimary )
	{
		g_loginStartMode = 2;
	}
	else
	{
		g_loginStartMode = 0;
	}

	g_Bink.CBink::OpenningMain(1);

	g_modeMgr.CModeMgr::Run(MT_LOGIN, "login.rsw");

	UnInitMSS();
	g_windowMgr.UIWindowMgr::DestroyDC();
	g_connection.CConnection::Disconnect();
	CConnection::Cleanup();
	g_windowMgr.UIWindowMgr::RemoveAllWindows();
	g_windowMgr.UIWindowMgr::WriteUIRectInfoToReg();
	g_session.CSession::WriteOptionToRegistry();
	g_resMgr().CResMgr::Reset();
	g_texMgr.CTexMgr::DestroyAllTexture();
	g_3dDevice.C3dDevice::DestroyRenderer(g_renderer);
	g_3dDevice.C3dDevice::DestroyObjects();
	g_mouse.CMouse::Exit();
	ExitApp(); // inlined
	DeleteHack();
	CoUninitialize();

	if( wTimerRes!= 0 ) timeEndPeriod(wTimerRes);

	return 0;
}
