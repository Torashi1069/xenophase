#include "3dLib/Prim.h"


hook_func<void (__cdecl *)(void)> _CreateTrigonometricTable("CreateTrigonometricTable");
void __cdecl CreateTrigonometricTable(void)
{
	return (_CreateTrigonometricTable)();
}
