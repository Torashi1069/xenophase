#pragma once
#include "mss.h"


bool __cdecl InitMSS(void);
void __cdecl UnInitMSS(void);
void __cdecl CloseStream(void);
int __cdecl GetStreamVolume(void);
void __cdecl SetStreamVolume(int volume);
int __cdecl Get2DVolume(void);
void __cdecl Set2DVolume(int volume);
int __cdecl Get3DVolume(void);
void __cdecl Set3DVolume(int volume);
void __cdecl PauseStream(int bgmIsPaused);
void __cdecl PlayStream(const char* streamFileName);
void __cdecl EndDigitalSound(void);
bool __cdecl PlayDigital(BYTE* fileImage, float& x, float& y, float& z, int volumeMaxDist, int volumeMinDist, float vFactor);
bool __cdecl Play3DDigital(BYTE* fileImage, float& x, float& y, float& z, int volumeMaxDist, int volumeMinDist, float vFactor);
void __cdecl SetRoomEffect(int val);
void __cdecl SetListenerOrient(float roty);


class CMssVariables
{
	/* this+   0 */ public: HDIGDRIVER hDigital;
	/* this+   4 */ public: HSTREAM hDigitalStream;
	/* this+   8 */ public: HSAMPLE hSamples[48];
	/* this+ 200 */ public: int streamVolume;
	/* this+ 204 */ public: int digital2DVolume;
	/* this+ 208 */ public: int digital3DVolume;
	/* this+ 212 */ public: char streamFileName[256];
	/* this+ 468 */ public: int volumeMaxDist;
	/* this+ 472 */ public: int volumeMinDist;
	/* this+ 476 */ public: int digitalrate;
	/* this+ 480 */ public: int digitalbits;
	/* this+ 484 */ public: int digitalchannels;
	/* this+ 488 */ public: int numSamples;
	/* this+ 492 */ public: char* provider_names[64];
	/* this+ 748 */ public: unsigned long provider_handles[64];
	/* this+1004 */ public: unsigned long provider_default;
	/* this+1008 */ public: unsigned long enum3D;
	/* this+1012 */ public: H3DPOBJECT h3DSamples[48];
	/* this+1204 */ public: H3DPOBJECT hListener;
	/* this+1208 */ public: int usingEAX;
	/* this+1212 */ public: int roomType;
	/* this+1216 */ public: int num3DSamples;

	public: CMssVariables::CMssVariables(void);
};
