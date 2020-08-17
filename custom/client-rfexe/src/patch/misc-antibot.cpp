#include <ntstatus.h> // STATUS_DLL_INIT_FAILED
#include <winternl.h> // struct UNICODE_STRING


namespace patch_misc_antibot
{


/// Equivalent to wcsicmp, except that str2 is split into individual stack arguments.
/// Helper function to obfuscate the presence of str2 (literal string).
static int obfuscated_wcsicmp(const wchar_t* str1, ...)
{
	int result;
	va_list ap;
	va_start(ap, str1);

	while( true )
	{
		wchar_t c1 = (wchar_t)towlower(*str1++);
		wchar_t c2 = (wchar_t)tolower(va_arg(ap, int));
		result = ( c1 == c2 ) ? 0 : ( c1 < c2 ) ? -1 : 1;

		if( result != 0 )
			break; // not equal.

		if( c1 == '\0' || c2 == '\0' )
			break; // end of string.
	}

	va_end(ap);
	return result;
}


hook_func<NTSTATUS (WINAPI *)(PWSTR DllPathEnv, PULONG DllCharacteristics, PUNICODE_STRING DllPath, PVOID* DllHandle)> _LdrLoadDll("LdrLoadDll");
NTSTATUS WINAPI my_LdrLoadDll(PWSTR DllPathEnv, PULONG DllCharacteristics, PUNICODE_STRING DllPath, PVOID* DllHandle)
{
	LPCWSTR DllName = wcsrchr(DllPath->Buffer, '\\');
	DllName = ( DllName != NULL ) ? DllName + 1 : DllPath->Buffer;

	if( 0 == obfuscated_wcsicmp(DllName, 'r','a','g','m','e','d','i','c'            ,'.','d','l','l','\0') // ragmedic.dll (RagMedic)
	||  0 == obfuscated_wcsicmp(DllName, 'w','p','e','s','p','y'                    ,'.','d','l','l','\0') // wpespy.dll (WPE Pro)
	||  0 == obfuscated_wcsicmp(DllName, 'r','p','e'                                ,'.','d','l','l','\0') // rPE.dll (rEdoX Packet Editor)
	||  0 == obfuscated_wcsicmp(DllName, 'n','e','t','r','e','d','i','r','e','c','t','.','d','l','l','\0') // netredirect.dll (OpenKore/XKore1)
	) {
		*DllHandle = NULL;
		return STATUS_DLL_INIT_FAILED;
	}

	return _LdrLoadDll(DllPathEnv, DllCharacteristics, DllPath, DllHandle);
}


};


using namespace patch_misc_antibot;
void Apply_misc_antibot()
{
	HookDB::DB().Hook("LdrLoadDll", _LdrLoadDll, &my_LdrLoadDll);
}
