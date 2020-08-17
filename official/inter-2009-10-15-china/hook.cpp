#include "src/InterServer.h"


void Hook()
{
	extern void Test(void);
	Test();

	extern void Hook_Alloc(void* pfnNew, void* pfnDelete, void* pfnInit);
	Hook_Alloc(DetourFindFunction(SERVER, "??2@YAPAXI@Z"), DetourFindFunction(SERVER, "??3@YAXPAX@Z"), DetourFindFunction(SERVER, "_cinit"));

//	hookdb.Hook("WinMain", DetourFindFunction(SERVER, "WinMain"), DetourFindFunction("inter.dll", "WinMain"));
}


void UnHook()
{
}


void SymDBInitCallback()
{
}
