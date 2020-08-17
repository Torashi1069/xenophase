#ifndef __NPGAMELIB_H__
#define __NPGAMELIB_H__


/// Definitions
#ifdef NPGAMEDLL_EXPORTS
#define NPGAMEDLL_API __declspec(dllexport)
#else
#define NPGAMEDLL_API
#endif


#ifdef __cplusplus
extern "C" {
#endif

NPGAMEDLL_API DWORD __cdecl CheckNPGameMon();
NPGAMEDLL_API bool  __cdecl CloseNPGameMon();
NPGAMEDLL_API DWORD __cdecl InitNPGameMon(HWND hWnd);
NPGAMEDLL_API DWORD __cdecl PreInitNPGameMonA(const char* Source);

#ifdef __cplusplus
}
#endif


#endif // __NPGAMELIB_H__
