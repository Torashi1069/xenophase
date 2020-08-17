#include "Timer.h"


hook_func<void (__cdecl *)(void)> _ResetTimer(SAKEXE, "ResetTimer");
void __cdecl ResetTimer(void) // line 12
{
	return (_ResetTimer)();

	//TODO
}


hook_func<void (__cdecl *)(unsigned long freq)> _InitTimer(SAKEXE, "InitTimer");
void __cdecl InitTimer(unsigned long freq) // line 16
{
	return (_InitTimer)(freq);

	//TODO
}


hook_func<int (__cdecl *)(void)> _SkipSceneRendering(SAKEXE, "SkipSceneRendering");
int __cdecl SkipSceneRendering(void) // line 23
{
	return (_SkipSceneRendering)();

	return 1;
}


hook_func<int (__cdecl *)(void)> _GetSkipFrameCount(SAKEXE, "GetSkipFrameCount");
int __cdecl GetSkipFrameCount(void) // line 27
{
	return (_GetSkipFrameCount)();

	//TODO
}
