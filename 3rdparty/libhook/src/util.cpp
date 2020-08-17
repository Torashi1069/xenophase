#include "util.hpp"
#include <windows.h>
#include <detours/detours.h> // DetourGetContainingModule()
#include <assert.h> // assert()


const char* EXEPATH(void)
{
	static char filename[MAX_PATH] = "";
	static bool bFirstRun = true;

	if( bFirstRun )
	{
		bFirstRun = false;
		::GetModuleFileNameA(NULL, filename, _countof(filename));
	}

	return filename;
}


const char* DLLPATH(void)
{
	static char filename[MAX_PATH] = "";
	static bool bFirstRun = true;

	if( bFirstRun )
	{
		bFirstRun = false;
		HMODULE hDllModule;
#if 1
		// same as below, but with additional integrity checks
		hDllModule = DetourGetContainingModule(&DLLPATH);
#elif 0
		// assume HMODULE == HINSTANCE == base load address
		MEMORY_BASIC_INFORMATION mbi = {0};
		::VirtualQuery((void*)&DLLPATH, &mbi, sizeof(mbi));
		hDllModule = reinterpret_cast<HMODULE>(mbi.AllocationBase);
#elif 0
		// same idea, different approach via MSVC-specific pseudovariable, from http://blogs.msdn.com/b/oldnewthing/archive/2004/10/25/247180.aspx
		extern IMAGE_DOS_HEADER __ImageBase;
		hDllModule = reinterpret_cast<HMODULE>(&__ImageBase);
#elif 0
		// get handle from syscall that crawls the loaded modules list (needs winXP or higher)
		::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCTSTR)&DLLPATH, &hDllModule);
#elif 0
		// get handle from DllMain's hinstDLL parameter (cleanest, but unavailable until DllMain runs)
		extern HMODULE hDllModule; // define this global var and fill it in DllMain
#endif
		::GetModuleFileNameA(hDllModule, filename, _countof(filename));
	}

	return filename;
}


/// Replaces memory contents at a specified location. Can be used on bytecode.
/// @param addr starting offset
/// @param size number of bytes to write
/// @param from data expected at 'addr' (optional, for verification purposes)
/// @param to data to write
/// @return true on success, false if data mismatch
bool Hex(void* addr, size_t size, const void* from, const void* to)
{
	// check if target happens to be correctly patched already
	if( memcmp(addr, to, size) == 0 )
		return true; // already done.
	
	// (optionally) verify that existing contents match
	if( from != NULL )
	{
		bool bMatch = ( memcmp(addr, from, size) == 0 );
		assert( bMatch );
		if( !bMatch )
			return false;
	}

	DWORD oldprotect;

	// make target memory writable
	VirtualProtect(addr, size, PAGE_READWRITE, &oldprotect);

	// write new data
	memcpy(addr, to, size);

	// restore original memory attributes
	VirtualProtect(addr, size, oldprotect, &oldprotect);

	return true;
}


bool Hex(unsigned long addr, size_t size, const void* from, const void* to)
{
	return Hex((void*)addr, size, from, to);
}

