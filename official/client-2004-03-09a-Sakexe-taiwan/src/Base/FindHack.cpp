#include "FindHack.h"
#include "Globals.h"
#include "MsgStrings.h"
#include "Framework/Language.h"
#include "NPGameLib.h"
#include "NPKCrypt.h"
#include <shellapi.h> // ShellExecuteA()
#include <wincrypt.h>


int  (__cdecl*& MyInitialize)(void)             = VTOR<int(__cdecl*)(void)>(SymDB::Add("MyInitialize", SAKEXE, "MyInitialize")); // = ?;
int  (__cdecl*& MyStartEncryption)(void)        = VTOR<int(__cdecl*)(void)>(SymDB::Add("MyStartEncryption", SAKEXE, "MyStartEncryption")); // = ?;
int  (__cdecl*& MyStopEncryption)(void)         = VTOR<int(__cdecl*)(void)>(SymDB::Add("MyStopEncryption", SAKEXE, "MyStopEncryption")); // = ?;
int  (__cdecl*& MyCloseDriver)(void)            = VTOR<int(__cdecl*)(void)>(SymDB::Add("MyCloseDriver", SAKEXE, "MyCloseDriver")); // = ?;
int  (__cdecl*& MyGetCryptData)(unsigned char*) = VTOR<int(__cdecl*)(unsigned char*)>(SymDB::Add("MyGetCryptData", SAKEXE, "MyGetCryptData")); // = ?;
void (__cdecl*& MyRegisterHWNDForEdit)(unsigned long, void*) = VTOR<void(__cdecl*)(unsigned long, void*)>(SymDB::Add("MyRegisterHWNDForEdit", SAKEXE, "MyRegisterHWNDForEdit")); // = ?;
int  (__cdecl*& MyInitReg)(void)                = VTOR<int(__cdecl*)(void)> (SymDB::Add("MyInitReg", SAKEXE, "MyInitReg")); // = ?;
void (__cdecl*& MyInstallReg)(void)             = VTOR<void(__cdecl*)(void)>(SymDB::Add("MyInstallReg", SAKEXE, "MyInstallReg")); // = ?;
void (__cdecl*& MyUninstallReg)(void)           = VTOR<void(__cdecl*)(void)>(SymDB::Add("MyUninstallReg", SAKEXE, "MyUninstallReg")); // = ?;
int  (__cdecl*& MyCheckReg)(void)               = VTOR<int(__cdecl*)(void)> (SymDB::Add("MyCheckReg", SAKEXE, "MyCheckReg")); // = ?;
int  (__cdecl*& MyLoadKindDriver)(void)         = VTOR<int(__cdecl*)(void)> (SymDB::Add("MyLoadKindDriver", SAKEXE, "MyLoadKindDriver")); // = ?;
int  (__cdecl*& MyGetInitError)(void)           = VTOR<int(__cdecl*)(void)> (SymDB::Add("MyGetInitError", SAKEXE, "MyGetInitError")); // = ?;
int  (__cdecl*& MyGetAthKbdObject)(char*)       = VTOR<int(__cdecl*)(char*)>(SymDB::Add("MyGetAthKbdObject", SAKEXE, "MyGetAthKbdObject")); // = ?;
int  (__cdecl*& MyGetIMEHangulMode)(void*)      = VTOR<int(__cdecl*)(void*)>(SymDB::Add("MyGetIMEHangulMode", SAKEXE, "MyGetIMEHangulMode")); // = ?;
const unsigned long& NPGAMEMON_SUCCESS = VTOR<const unsigned long>(SymDB::Add("NPGAMEMON_SUCCESS", SAKEXE, "NPGAMEMON_SUCCESS")); // = 1877;
HMODULE& g_hDll = VTOR<HMODULE>(SymDB::Add("g_hDll", SAKEXE, "g_hDll")); // = ?;


struct tagNPKFuncTbl
{
	/* this+ 0 */ HKCRYPT (WINAPI* FNPKOpenDriver)(void);
	/* this+ 4 */ HKCRYPT (WINAPI* FNPKOpenDriverEx)(UINT nHookType);
	/* this+ 8 */ BOOL (WINAPI* FNPKCloseDriver)(BOOL);
	/* this+12 */ BOOL (WINAPI* FNPKRegCryptMsg)(HKCRYPT hKCrypt, HWND hWnd, UINT nCallBackMsg);
	/* this+16 */ BOOL (WINAPI* FNPKRegCryptFunc)(HKCRYPT hKCrypt, HWND hWnd, FCryptAction fnCryptAction, PVOID pUserData);
	/* this+20 */ BOOL (WINAPI* FNPKUnregCrypt)(HKCRYPT hKCrypt, HWND hWnd);
	/* this+24 */ BOOL (WINAPI* FNPKSetKeyMode)(DWORD dwMode);
	/* this+28 */ BOOL (WINAPI* FNPKSetKbdLock)(BOOL bLock);
	/* this+32 */ VOID (WINAPI* FNPKSetDrvPath)(PSTR szPath);
};


namespace FH
{
HMODULE& hDll = VTOR<HMODULE>(SymDB::Add("FH::hDll", SAKEXE, "FH::hDll")); // = ?;
tagNPKFuncTbl& npkfuncs = VTOR<tagNPKFuncTbl>(SymDB::Add("FH::npkfuncs", SAKEXE, "FH::npkfuncs")); // = ?;
int& hKCrypt = VTOR<int>(SymDB::Add("FH::hKCrypt", SAKEXE, "FH::hKCrypt")); // = ?;
};


hook_func<bool (__cdecl *)(void)> _IsEnableOldKeycrypt(SAKEXE, "IsEnableOldKeycrypt");
bool __cdecl IsEnableOldKeycrypt(void) // line 90-95
{
	return (_IsEnableOldKeycrypt)();

	return( g_serviceType == ServiceKorea && g_serverType == ServerPrimary );
}


hook_func<bool (__cdecl *)(void)> _IsEnableNewKeycrypt(SAKEXE, "IsEnableNewKeycrypt");
bool __cdecl IsEnableNewKeycrypt(void) // line 98-131
{
	return (_IsEnableNewKeycrypt)();

	bool bUseNewKeycrypt[ServiceLast][ServerLast] = {
	//    Primary    Sakray    Local  InstantEvent
		{  false  ,   true  ,   true  ,  false  }, // Korea
		{  false  ,  false  ,  false  ,  false  }, // America
		{  false  ,  false  ,  false  ,  false  }, // Japan
		{  false  ,  false  ,  false  ,  false  }, // China
		{  false  ,  false  ,  false  ,  false  }, // Taiwan
		{  false  ,  false  ,  false  ,  false  }, // Thai
		{  false  ,  false  ,   true  ,  false  }, // Indonesia
		{  false  ,  false  ,  false  ,  false  }, // Philippine
		{  false  ,  false  ,  false  ,  false  }, // Malaysia
		{  false  ,  false  ,  false  ,  false  }, // Singapore
		{  false  ,  false  ,  false  ,  false  }, // Germany
	};

	return bUseNewKeycrypt[g_serviceType][g_serverType];
}


hook_func<int (__cdecl *)(void)> _FindHack1(SAKEXE, "FindHack1");
int __cdecl FindHack1(void) // line 134-158
{
	return (_FindHack1)();

	FILE* fp = fopen("findhack.exe", "r");
	if( fp == NULL )
		return -1;

	if( fseek(fp, 0, SEEK_END) != 0 )
	{
		fclose(fp);
		return -2;
	}

	int filesize = ftell(fp);

	if( fseek(fp, -4, SEEK_END) != 0 )
	{
		fclose(fp);
		return -3;
	}

	int writtenFileSize;
	fread(&writtenFileSize, 4u, 1u, fp);

	fclose(fp);

	if( writtenFileSize != filesize )
		return -4;

	return _spawnl(_P_WAIT, "findhack.exe", "findhack.exe", NULL);
}


hook_func<int (__cdecl *)(void)> _FindHack2(SAKEXE, "FindHack2");
int __cdecl FindHack2(void) // line 161-164
{
	return (_FindHack2)();

	PreInitNPGameMonA("Ragnarok");
	int ret = InitNPGameMon(NULL);
	CloseNPGameMon();
	return ret;

}


hook_func<int (__cdecl *)(void)> _ProcessFindHack1(SAKEXE, "ProcessFindHack1");
int __cdecl ProcessFindHack1(void) // line 167-224
{
	return (_ProcessFindHack1)();

	int err = FindHack1(); //inlined

	char errorMsg[1024];
	switch( err )
	{
	case -4:
	case -3:
	case -2:
	case -1:
		sprintf(errorMsg, MsgStr(MSI_FINDHACK_NOTINSTALLED), err);
		if( MessageBoxA(g_hMainWnd, errorMsg, "Message", 4u) == 6 )
			ShellExecuteA(g_hMainWnd, "open", MsgStr(MSI_FINDHACK_PATH), 0, 0, 1);
		return 0;
	case 1024:
	case 1025:
		return 1;
	case 1026:
		sprintf(errorMsg, MsgStr(MSI_FINDHACK_HACKTOOLEXIST));
		MessageBoxA(g_hMainWnd, errorMsg, "Message", MB_OK);
		return 0;
	case 1027:
		sprintf(errorMsg, MsgStr(MSI_FINDHACK_CANTDOWNLOAD));
		if( MessageBoxA(g_hMainWnd, errorMsg, "Message", 4u) == 6 )
			ShellExecuteA(g_hMainWnd, "open", MsgStr(MSI_FINDHACK_PATH), 0, 0, 1);
		return 0;
	case 1028:
		sprintf(errorMsg, MsgStr(MSI_FINDHACK_NOFILE));
		if( MessageBoxA(g_hMainWnd, errorMsg, "Message", 4u) == 6 )
			ShellExecuteA(g_hMainWnd, "open", MsgStr(MSI_FINDHACK_PATH), 0, 0, 1);
		return 0;
	case 1030:
		sprintf(errorMsg, MsgStr(MSI_FINDHACK_EXITPRESSED));
		MessageBoxA(g_hMainWnd, errorMsg, "Message", MB_OK);
		return 0;
	case 1031:
		sprintf(errorMsg, MsgStr(MSI_FINDHACK_UPDATEFAILED));
		MessageBoxA(g_hMainWnd, errorMsg, "Message", MB_OK);
		return 0;
	default:
		sprintf(errorMsg, MsgStr(MSI_FINDHACK_EXCEPTION), err);
		MessageBoxA(g_hMainWnd, errorMsg, "Message", MB_OK);
		return 0;
	};
}


hook_func<int (__cdecl *)(void)> _ProcessFindHack2(SAKEXE, "ProcessFindHack2");
int __cdecl ProcessFindHack2(void) // line 227-273
{
	return (_ProcessFindHack2)();

	int err = FindHack2();
	if( err == NPGAMEMON_SUCCESS )
		return 1;

	char lpszMsg[1024];
	switch( err )
	{
	case 120:
	case 124:
	case 150:
	case 153: sprintf(lpszMsg, MsgStr(MSI_NPGAMEMON_ERROR_AUTH_GAMEGUARD)); break;
	case 155: sprintf(lpszMsg, MsgStr(MSI_NPGAMEMON_ERROR_CRYPTOAPI)); break;
	case 170: sprintf(lpszMsg, MsgStr(MSI_NPGAMEMON_ERROR_EXECUTE)); break;
	case 200: sprintf(lpszMsg, MsgStr(MSI_NPGAMEMON_ERROR_ILLEGAL_PRG)); break;
	case 350: sprintf(lpszMsg, MsgStr(MSI_NPGMUP_ERROR_ABORT)); break;
	case 340:
	case 380: sprintf(lpszMsg, MsgStr(MSI_NPGMUP_ERROR_CONNECT)); break;
	case 360: sprintf(lpszMsg, MsgStr(MSI_NPGMUP_ERROR_AUTH)); break;
	default : sprintf(lpszMsg, "GameGuard Error: %lu", err); break;
	};

	MessageBoxA(g_hMainWnd, lpszMsg, "Message", MB_OK);
	return 0;
}


hook_func<void (__cdecl *)(void)> _DeleteHack(SAKEXE, "DeleteHack");
void __cdecl DeleteHack(void) // line 288-296
{
	return (_DeleteHack)();

	if( !access("nconfig.ini", 6) )
		unlink("nconfig.ini");
	if( !access("removenp.exe", 6) )
		unlink("removenp.exe");
	if( !access("cfindhack.exe", 6) )
		unlink("cfindhack.exe");
	if( !access("ffindhack.exe", 6) )
		unlink("ffindhack.exe");
	if( !access("gfindhack.exe", 6) )
		unlink("gfindhack.exe");
}


hook_func<int (__cdecl *)(void)> _NpKeyMyLoadLibrary(SAKEXE, "NpKeyMyLoadLibrary");
int __cdecl NpKeyMyLoadLibrary(void) // line 299-337
{
	return (_NpKeyMyLoadLibrary)();

	g_hDll = NULL;

	g_hDll = LoadLibraryA("npkeysdk.dll");
	if( g_hDll == NULL )
	{
		MessageBoxA(NULL, "npkeysdk.dll Load Failed!", "npkeysdk", MB_OK);
		return 0;
	}

	if( NULL == (MyInitialize = (int(__cdecl*)(void))GetProcAddress(g_hDll, "Initialize"))
	||  NULL == (MyStartEncryption = (int(__cdecl*)(void))GetProcAddress(g_hDll, "StartEncryption"))
	||  NULL == (MyStopEncryption = (int(__cdecl*)(void))GetProcAddress(g_hDll, "StopEncryption"))
	||  NULL == (MyCloseDriver = (int(__cdecl*)(void))GetProcAddress(g_hDll, "CloseDriver"))
	||  NULL == (MyGetCryptData = (int(__cdecl*)(unsigned char*))GetProcAddress(g_hDll, "GetCryptData"))
	||  NULL == (MyRegisterHWNDForEdit = (void(__cdecl*)(unsigned long, void*))GetProcAddress(g_hDll, "RegisterHWNDForEdit"))
	||  NULL == (MyGetAthKbdObject = (int(__cdecl*)(char*))GetProcAddress(g_hDll, "GetAthKbdObject"))
	||  NULL == (MyInitReg = (int(__cdecl*)(void))GetProcAddress(g_hDll, "InitReg"))
	||  NULL == (MyInstallReg = (void(__cdecl*)(void))GetProcAddress(g_hDll, "InstallReg"))
	||  NULL == (MyUninstallReg = (void(__cdecl*)(void))GetProcAddress(g_hDll, "UninstallReg"))
	||  NULL == (MyCheckReg = (int(__cdecl*)(void))GetProcAddress(g_hDll, "CheckReg"))
	||  NULL == (MyLoadKindDriver = (int(__cdecl*)(void))GetProcAddress(g_hDll, "LoadKindDriver"))
	||  NULL == (MyGetInitError = (int(__cdecl*)(void))GetProcAddress(g_hDll, "GetInitError"))
	||  NULL == (MyGetIMEHangulMode = (int(__cdecl*)(void*))GetProcAddress(g_hDll, "GetIMEHangulMode")) )
	{
		MessageBoxA(NULL, "npkeysdk.dll Load Failed!", "npkeysdkc", MB_OK);
		return 0;
	}

	return 1;
}


hook_func<HMODULE (__stdcall *)(tagNPKFuncTbl* tbl)> _InitNPKCryptFuncTbl(SAKEXE, "InitNPKCryptFuncTbl");
HMODULE __stdcall InitNPKCryptFuncTbl(tagNPKFuncTbl* pTbl) // line 344-380
{
	return (_InitNPKCryptFuncTbl)(pTbl);

	memset(pTbl, 0, sizeof(*pTbl));

	HMODULE hDll = LoadLibraryA("npkcrypt.dll");
	if( hDll == NULL )
	{
		FreeLibrary(hDll);
		return NULL;
	}

	pTbl->FNPKOpenDriver = (HKCRYPT (WINAPI*)(void))GetProcAddress(hDll, "NPKOpenDriver");
	pTbl->FNPKOpenDriverEx = (HKCRYPT (WINAPI*)(UINT))GetProcAddress(hDll, "NPKOpenDriverEx");
	pTbl->FNPKCloseDriver = (BOOL (WINAPI*)(BOOL))GetProcAddress(hDll, "NPKCloseDriver");
	pTbl->FNPKRegCryptMsg = (BOOL (WINAPI*)(HKCRYPT,HWND,UINT))GetProcAddress(hDll, "NPKRegCryptMsg");
	pTbl->FNPKRegCryptFunc = (BOOL (WINAPI*)(HKCRYPT,HWND,FCryptAction,PVOID))GetProcAddress(hDll, "NPKRegCryptFunc");
	pTbl->FNPKUnregCrypt = (BOOL (WINAPI*)(HKCRYPT,HWND))GetProcAddress(hDll, "NPKUnregCrypt");
	pTbl->FNPKSetKeyMode = (BOOL (WINAPI*)(DWORD))GetProcAddress(hDll, "NPKSetKeyMode");
	pTbl->FNPKSetKbdLock = (BOOL (WINAPI*)(BOOL))GetProcAddress(hDll, "NPKSetKbdLock");
	pTbl->FNPKSetDrvPath = (VOID (WINAPI*)(PSTR))GetProcAddress(hDll, "NPKSetDrvPath");
	
	if( pTbl->FNPKOpenDriver == NULL
	||  pTbl->FNPKOpenDriverEx == NULL
	||  pTbl->FNPKCloseDriver == NULL
	||  pTbl->FNPKRegCryptMsg == NULL
	||  pTbl->FNPKRegCryptFunc == NULL
	||  pTbl->FNPKUnregCrypt == NULL
	||  pTbl->FNPKSetKeyMode == NULL
	||  pTbl->FNPKSetKbdLock == NULL
	||  pTbl->FNPKSetDrvPath == NULL )
	{
		FreeLibrary(hDll);
		return NULL;
	}

	return hDll;
};


hook_func<void (__cdecl *)(void)> _WinMainNpKeyStartEncryption(SAKEXE, "WinMainNpKeyStartEncryption");
void __cdecl WinMainNpKeyStartEncryption(void) // line 383-388
{
	return (_WinMainNpKeyStartEncryption)();

	if( IsEnableNewKeycrypt() )
		NKCStartKeycrypt();
	else
	if( g_serviceType == ServiceKorea && g_serverType == ServerPrimary )
		MyStartEncryption();
}


hook_func<void (__cdecl *)(void)> _WinMainNpKeyStopEncryption(SAKEXE, "WinMainNpKeyStopEncryption");
void __cdecl WinMainNpKeyStopEncryption(void) // line 391-397
{
	return (_WinMainNpKeyStopEncryption)();

	if( IsEnableNewKeycrypt() )
		CloseKeyCrypt(); //inlined
	else
	if( g_serviceType == ServiceKorea && g_serverType == ServerPrimary )
		MyStopEncryption();
}


hook_func<DWORD (__cdecl *)(BYTE* pbKey, DWORD dwKeySize, BYTE* pbCipherText, BYTE* pbPlaintext, DWORD dwHowMuch)> _Decrypt(SAKEXE, "Decrypt");
DWORD __cdecl Decrypt(BYTE* pbKey, DWORD dwKeySize, BYTE* pbCipherText, BYTE* pbPlaintext, DWORD dwHowMuch) // line 414-456
{
	return (_Decrypt)(pbKey, dwKeySize, pbCipherText, pbPlaintext, dwHowMuch);

	memcpy(pbPlaintext, pbCipherText, dwHowMuch);

	HCRYPTPROV hProv = NULL;
	if( CryptAcquireContextA(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) != TRUE )
		throw GetLastError();

	HCRYPTHASH hHash = NULL;
	if( CryptCreateHash(hProv, CALG_MD5, NULL, 0, &hHash) != TRUE )
		throw GetLastError();

	if( CryptHashData(hHash, pbKey, dwKeySize, 0) != TRUE )
		throw GetLastError();

	HCRYPTKEY hKey = NULL;
	if( !CryptDeriveKey(hProv, CALG_RC4, hHash, CRYPT_EXPORTABLE, &hKey) )
		throw GetLastError();

	DWORD dwBuff = dwHowMuch;
	if ( !CryptDecrypt(hKey, NULL, TRUE, 0, pbPlaintext, &dwBuff) )
		throw GetLastError();

	if( hKey != NULL )
		CryptDestroyKey(hKey);

	if( hHash != NULL )
		CryptDestroyHash(hHash);

	if( hProv != NULL )
		CryptReleaseContext(hProv, 0);

	return 0;
}


hook_func<void (__stdcall *)(void* pParam, BYTE* pbBuff, DWORD dwBuffSize)> _KeyData(SAKEXE, "KeyData");
void __stdcall KeyData(void* pParam, BYTE* pbBuff, DWORD dwBuffSize) // line 459-472
{
	return (_KeyData)(pParam, pbBuff, dwBuffSize);

	char passwd[256];
	sprintf(passwd, "%x", pParam);

	char buff[1024];
	Decrypt((BYTE*)passwd, strlen(passwd), pbBuff, (BYTE*)buff, dwBuffSize);

	for( DWORD i = 0; i != dwBuffSize - 1; ++i )
		g_language->CLanguage::OnChar(buff[i], 0);
}


hook_func<void (__cdecl *)(void)> _CloseKeyCrypt(SAKEXE, "CloseKeyCrypt");
void __cdecl CloseKeyCrypt(void) // line 476-486
{
	return (_CloseKeyCrypt)();

	if( FH::hDll != NULL )
	{
		if( FH::hKCrypt > 0 )
		{
			FH::npkfuncs.FNPKCloseDriver(FH::hKCrypt);
			FH::hKCrypt = 0;
		}

		FreeLibrary(FH::hDll);
		FH::hDll = NULL;
	}
}


hook_func<int (__cdecl *)(void)> _NKCStartKeycrypt(SAKEXE, "NKCStartKeycrypt");
int __cdecl NKCStartKeycrypt(void) // line 489-546
{
	return (_NKCStartKeycrypt)();

	FH::hDll = InitNPKCryptFuncTbl(&FH::npkfuncs);
	if( FH::hDll == NULL )
	{
		MessageBoxA(g_hMainWnd, "npkcrypt.dll not found", "Ragnarok", 0);
		return 0;
	}

	char szFileName[MAX_PATH];
	memset(szFileName, '\0', sizeof(szFileName));
	_getcwd(szFileName, sizeof(szFileName));
	strrchr(szFileName, '\\'); // ???
	FH::npkfuncs.FNPKSetDrvPath(szFileName);

	FH::hKCrypt = FH::npkfuncs.FNPKOpenDriver();
	if( FH::hKCrypt <= 0 )
	{
		char szErrMsg[1024]; // not used?
		DWORD err = GetLastError();
		if( (err & 0x20000000) == 0x20000000 )
		{
			strcpy(szErrMsg, "어드민으로만 실행됩니다."); // "Will only run as admin."
		}
		else
		{
			HLOCAL hlocal = NULL;
			if( FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, err, 	LANG_KOREAN, (LPSTR)&hlocal, 0, NULL) )
			{
				strcpy(szErrMsg, (char*)LocalLock(hlocal));
				LocalFree(hlocal);
			}
		}

		return 0;
	}

	FH::npkfuncs.FNPKRegCryptFunc(FH::hKCrypt, g_hMainWnd, &KeyData, g_hMainWnd);
	return 1;
}
