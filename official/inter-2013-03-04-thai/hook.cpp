void Hook()
{
	C_ASSERT( sizeof std::string == 28 );
	C_ASSERT( sizeof std::vector<int> == 24 );
	C_ASSERT( sizeof std::list<int> == 28 );
	struct tmp { std::map<int,int> a; }; C_ASSERT( sizeof tmp == 32 );

	extern void Hook_Alloc(void* pfnNew, void* pfnDelete, void* pfnInit);
	Hook_Alloc(DetourFindFunction(EXEPATH(), "??2@YAPAXI@Z"), DetourFindFunction(EXEPATH(), "??3@YAXPAX@Z"), DetourFindFunction(EXEPATH(), "_cinit"));
}


void UnHook()
{
}


void SymDBInitCallback()
{
}


#ifndef NDEBUG
extern "C" void __cdecl _invalid_parameter(_In_opt_z_ const wchar_t *, _In_opt_z_ const wchar_t *, _In_opt_z_ const wchar_t *, unsigned int, uintptr_t);
extern "C" void __cdecl _invalid_parameter_noinfo(void)
{
    _invalid_parameter(NULL, NULL, NULL, 0, 0);
}
#endif
