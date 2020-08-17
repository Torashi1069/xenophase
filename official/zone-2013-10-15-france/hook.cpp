void Hook()
{
	C_ASSERT( sizeof std::string == 28 );
	C_ASSERT( sizeof std::vector<int> == 16 );
	C_ASSERT( sizeof std::list<int> == 12 );
	struct tmp { std::map<int,int> a; }; C_ASSERT( sizeof tmp == 16 );

	extern void Hook_Alloc(void* pfnNew, void* pfnDelete, void* pfnInit);
	Hook_Alloc(DetourFindFunction(EXEPATH(), "??2@YAPAXI@Z"), DetourFindFunction(EXEPATH(), "??3@YAXPAX@Z"), DetourFindFunction(EXEPATH(), "_cinit"));

	#define HOOK(S) HookDB::DB().Hook(S, DetourFindFunction(EXEPATH(), S), DetourFindFunction(DLLPATH(), S))
	HOOK("WinMain");
}


void UnHook()
{
}


void SymDBInitCallback()
{
}
