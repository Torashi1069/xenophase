#include "Base/FindHack.h"


hook_func<void (__cdecl *)(void)> _DeleteHack("DeleteHack");
void __cdecl DeleteHack(void)
{
	return (_DeleteHack)();

	if( !access("nconfig.ini", 6) )
		unlink("nconfig.ini");
	if( !access("ffindhack.exe", 6) )
		unlink("ffindhack.exe");
	if( !access("gfindhack.exe", 6) )
		unlink("gfindhack.exe");
	if( !access("removenp.exe", 6) )
		unlink("removenp.exe");
	if( !access("cfindhack.exe", 6) )
		unlink("cfindhack.exe");
}
