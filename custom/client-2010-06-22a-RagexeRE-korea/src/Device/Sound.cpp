#include "Device/Sound.h"


hook_func<bool (__cdecl *)(void)> _InitMSS("InitMSS");
bool __cdecl InitMSS(void)
{
	return (_InitMSS)();
}


hook_func<void (__cdecl *)(void)> _UnInitMSS("UnInitMSS");
void __cdecl UnInitMSS(void)
{
	return (_UnInitMSS)();
}
