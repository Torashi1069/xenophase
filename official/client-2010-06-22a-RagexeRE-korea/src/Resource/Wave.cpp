#include "Resource/Wave.h"


hook_func<void (__cdecl *)(const char* waveFileName, float x, float y, float z, int volumeMaxDist, int volumeMinDist, float vFactor)> _PlayWave("PlayWave");
void __cdecl PlayWave(const char* waveFileName, float x, float y, float z, int volumeMaxDist, int volumeMinDist, float vFactor)
{
	return (_PlayWave)(waveFileName, x, y, z, volumeMaxDist, volumeMinDist, vFactor);

	//TODO
}
