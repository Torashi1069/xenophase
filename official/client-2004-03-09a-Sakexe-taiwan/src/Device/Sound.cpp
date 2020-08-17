#include "Globals.h"
#include "Sound.h"
#include "mss.h"


hook_func<bool (__cdecl *)(void)> _InitMSS(SAKEXE, "InitMSS");
bool __cdecl InitMSS(void) // line 10-124
{
	return (_InitMSS)();

	//TODO
}


hook_func<void (__cdecl *)(void)> _UnInitMSS(SAKEXE, "UnInitMSS");
void __cdecl UnInitMSS(void) // line 127-155
{
	return (_UnInitMSS)();

	//TODO
}


hook_func<void (__cdecl *)(void)> _CloseStream(SAKEXE, "CloseStream");
void __cdecl CloseStream(void) // line 159-165
{
	return (_CloseStream)();

	//TODO
}


hook_func<int (__cdecl *)(void)> _GetStreamVolume(SAKEXE, "GetStreamVolume");
int __cdecl GetStreamVolume(void) // line 168-170
{
	return (_GetStreamVolume)();

	return g_mssVar.streamVolume;
}


hook_func<void (__cdecl *)(int volume)> _SetStreamVolume(SAKEXE, "SetStreamVolume");
void __cdecl SetStreamVolume(int volume) // line 173-181
{
	return (_SetStreamVolume)(volume);

	volume = ( volume < 0 ) ? 0 : ( volume > 127 ) ? 127 : volume;

	g_mssVar.streamVolume = volume;

	if( g_mssVar.hDigitalStream != NULL )
		AIL_set_stream_volume(g_mssVar.hDigitalStream, volume);
}


hook_func<int (__cdecl *)(void)> _Get2DVolume(SAKEXE, "Get2DVolume");
int __cdecl Get2DVolume(void) // line 184-186
{
	return (_Get2DVolume)();

	return g_mssVar.digital2DVolume;
}


hook_func<void (__cdecl *)(int volume)> _Set2DVolume(SAKEXE, "Set2DVolume");
void __cdecl Set2DVolume(int volume) // line 189-195
{
	return (_Set2DVolume)(volume);

	//TODO
}


hook_func<int (__cdecl *)(void)> _Get3DVolume(SAKEXE, "Get3DVolume");
int __cdecl Get3DVolume(void) // line 198-200
{
	return (_Get3DVolume)();

	//TODO
}


hook_func<void (__cdecl *)(int volume)> _Set3DVolume(SAKEXE, "Set3DVolume");
void __cdecl Set3DVolume(int volume) // line 203-209
{
	return (_Set3DVolume)(volume);

	//TODO
}


hook_func<void (__cdecl *)(int bgmIsPaused)> _PauseStream(SAKEXE, "PauseStream");
void __cdecl PauseStream(int bgmIsPaused) // line 212-216
{
	return (_PauseStream)(bgmIsPaused);

	//TODO
}


hook_func<void (__cdecl *)(const char* streamFileName)> _PlayStream(SAKEXE, "PlayStream");
void __cdecl PlayStream(const char* streamFileName) // line 219-234
{
	return (_PlayStream)(streamFileName);

	//TODO
}


hook_func<void (__cdecl *)(void)> _EndDigitalSound(SAKEXE, "EndDigitalSound");
void __cdecl EndDigitalSound(void) // line 237-250
{
	return (_EndDigitalSound)();

	//TODO
}


hook_func<bool (__cdecl *)(BYTE* fileImage, float& x, float& y, float& z, int volumeMaxDist, int volumeMinDist, float vFactor)> _PlayDigital(SAKEXE, "PlayDigital");
bool __cdecl PlayDigital(BYTE* fileImage, float& x, float& y, float& z, int volumeMaxDist, int volumeMinDist, float vFactor) // line 253-283
{
	return (_PlayDigital)(fileImage, x, y, z, volumeMaxDist, volumeMinDist, vFactor);

	//TODO
}


hook_func<bool (__cdecl *)(BYTE* fileImage, float& x, float& y, float& z, int volumeMaxDist, int volumeMinDist, float vFactor)> _Play3DDigital(SAKEXE, "Play3DDigital");
bool __cdecl Play3DDigital(BYTE* fileImage, float& x, float& y, float& z, int volumeMaxDist, int volumeMinDist, float vFactor) // line 286-315
{
	return (_Play3DDigital)(fileImage, x, y, z, volumeMaxDist, volumeMinDist, vFactor);

	//TODO
}


hook_func<void (__cdecl *)(int val)> _SetRoomEffect(SAKEXE, "SetRoomEffect");
void __cdecl SetRoomEffect(int val) // line 318-325
{
	return (_SetRoomEffect)(val);

	//TODO
}


hook_func<void (__cdecl *)(float roty)> _SetListenerOrient(SAKEXE, "SetListenerOrient");
void __cdecl SetListenerOrient(float roty) // line 328-335
{
	return (_SetListenerOrient)(roty);

	//TODO
}


////////////////////////////////////////


CMssVariables::CMssVariables(void) // inlined ($E15_1)
{
	numSamples = 48;
	num3DSamples = 48;
	memset(hSamples, 0, sizeof(hSamples));
	provider_default = 0;
	for( int i = 0; i < 64; ++i )
	{
		provider_names[i] = NULL;
		provider_handles[i] = 0;
	}
	enum3D = 0;
	memset(h3DSamples, 0, sizeof(h3DSamples));
	streamVolume = 100;
	digital2DVolume = 100;
	digital3DVolume = 100;
	hListener = 0;
	usingEAX = 0;
	roomType = 0;
	memset(streamFileName, 0, sizeof(streamFileName));
	volumeMaxDist = 250;
	volumeMinDist = 40;
	digitalrate = 22050;
	digitalbits = 16;
	digitalchannels = 2;
}
