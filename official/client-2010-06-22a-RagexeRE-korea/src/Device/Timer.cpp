#include "Globals.h"
#include "Device/Timer.h"


unsigned int& frameTime = VTOR<unsigned int>(SymDB::Find("frameTime"));
unsigned int& frameFreq = VTOR<unsigned int>(SymDB::Find("frameFreq"));


hook_func<void (__cdecl *)(void)> _ResetTimer("ResetTimer");
void __cdecl ResetTimer(void)
{
	return (_ResetTimer)();

	frameTime = timeGetTime();
}


hook_func<void (__cdecl *)(unsigned long freq)> _InitTimer("InitTimer");
void __cdecl InitTimer(unsigned long freq)
{
	return (_InitTimer)(freq);

	frameTime = timeGetTime();
	frameFreq = 1000 / freq;
}


hook_func<int (__cdecl *)(void)> _SkipSceneRendering("SkipSceneRendering");
int __cdecl SkipSceneRendering(void)
{
	return (_SkipSceneRendering)();

	return 1;
}


hook_func<int (__cdecl *)(void)> _GetSkipFrameCount("GetSkipFrameCount");
int __cdecl GetSkipFrameCount(void)
{
	return (_GetSkipFrameCount)();

	unsigned int frameDelta = timeGetTime() - frameTime;
	int nFrames = frameDelta / frameFreq;
	frameTime += nFrames * frameFreq;

	if( g_frameskip == 0 )
		nFrames = 1;
	return nFrames;
}
