#include <windows.h>


extern void Hook();
extern void UnHook();


extern "C" /// dummy export, required for Detours
__declspec(dllexport) void dummy(void) { };


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch( fdwReason )
	{
	case DLL_PROCESS_ATTACH:
		Hook();
	break;
	case DLL_THREAD_ATTACH:
	break;
	case DLL_THREAD_DETACH:
	break;
	case DLL_PROCESS_DETACH:
		UnHook();
	break;
	}

	return TRUE;
}
