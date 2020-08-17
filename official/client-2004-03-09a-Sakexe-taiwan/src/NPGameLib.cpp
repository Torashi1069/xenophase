#include "NPGameLib.h"


hook_func<DWORD (__cdecl *)(void)> _CheckNPGameMon(SAKEXE, "?CheckNPGameMon@@YAKXZ");
NPGAMEDLL_API DWORD __cdecl CheckNPGameMon(void)
{
	return (_CheckNPGameMon)();

	//TODO
}


hook_func<bool  (__cdecl *)(void)> _CloseNPGameMon(SAKEXE, "?CloseNPGameMon@@YA_NXZ");
NPGAMEDLL_API bool  __cdecl CloseNPGameMon(void)
{
	return (_CloseNPGameMon)();

	//TODO
}


hook_func<DWORD (__cdecl *)(HWND hWnd)> _InitNPGameMon(SAKEXE, "?InitNPGameMon@@YAKPAUHWND__@@@Z");
NPGAMEDLL_API DWORD __cdecl InitNPGameMon(HWND hWnd)
{
	return (_InitNPGameMon)(hWnd);

	//TODO
}


hook_func<DWORD (__cdecl *)(const char* Source)> _PreInitNPGameMonA(SAKEXE, "?PreInitNPGameMonA@@YAKPBD@Z");
NPGAMEDLL_API DWORD __cdecl PreInitNPGameMonA(const char* Source)
{
	return (_PreInitNPGameMonA)(Source);

	//TODO
}
