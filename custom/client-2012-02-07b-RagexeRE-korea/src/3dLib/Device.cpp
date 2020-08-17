#include "3dLib/Device.h"


hook_func<void (__cdecl *)()> _GDIFlip("GDIFlip");
void GDIFlip()
{
	return _GDIFlip();

	//TODO
}
