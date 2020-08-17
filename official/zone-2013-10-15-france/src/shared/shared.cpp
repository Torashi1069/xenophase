#include "Enum.h" // JT_*
#include "shared/DES.h"
#include "shared/NTraceLog.h"
#include "shared/shared.h"


/// globals
void(*& Trace)(const char* str, ...) = VTOR<void(*)(const char* str, ...)>(DetourFindFunction(EXEPATH(), "Trace")); // = &TraceO;


void Decrypt(const char* encBuf, unsigned char* decBuf)
{
	unsigned char key[7] = { 0x78, 0x11, 0x23, 0x2A, 0xF1, 0xED, 0x07 };
	DES des(key);

	char szString[2+1] = {};
	size_t hexlen = strlen(encBuf) / 2;

	// unpack hex-string to binary
	for( size_t i = 0; i < hexlen; ++i )
	{
		szString[0] = encBuf[2*i+0];
		szString[1] = encBuf[2*i+1];
		sscanf(szString, "%02X", &decBuf[i]);
	}

	// decode data, block by block
	for( size_t i = 0; i < hexlen; i += 8 )
		des.DES::decrypt(&decBuf[i], 8);
}


void TraceN(const char* str, ...)
{
}


void TraceO(const char* str, ...)
{
	va_list va;
	va_start(va, str);

	char szBuffer[1024+1] = {};
	_vsnprintf(szBuffer, countof(szBuffer)-1, str, va);

	OutputDebugStringA(szBuffer);
}


void TraceF(const char* str, ...)
{
	va_list va;
	va_start(va, str);

	char szBuffer[1024];
	_vsnprintf_s(szBuffer, countof(szBuffer), _TRUNCATE, str, va);

	NTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, szBuffer);
}


void InitializeSharedLib(BOOL isInstallFilter, int logOption)
{
	if     ( logOption == 0 ) Trace = &TraceN;
	else if( logOption == 1 ) Trace = &TraceF;
	else if( logOption == 2 ) Trace = &TraceO;
}


short GetThirdJobGroup(short job)
{
	switch( job )
	{
	case JT_RUNE_KNIGHT:
	case JT_RUNE_KNIGHT_H:
	case JT_RUNE_KNIGHT_B:
		return JT_RUNE_KNIGHT;

	case JT_ARCHBISHOP:
	case JT_ARCHBISHOP_H:
	case JT_ARCHBISHOP_B:
		return JT_ARCHBISHOP;

	case JT_WARLOCK:
	case JT_WARLOCK_H:
	case JT_WARLOCK_B:
		return JT_WARLOCK;

	case JT_MECHANIC:
	case JT_MECHANIC_H:
	case JT_MECHANIC_B:
		return JT_MECHANIC;

	case JT_RANGER:
	case JT_RANGER_H:
	case JT_RANGER_B:
		return JT_RANGER;

	case JT_GUILLOTINE_CROSS:
	case JT_GUILLOTINE_CROSS_H:
	case JT_GUILLOTINE_CROSS_B:
		return JT_GUILLOTINE_CROSS;

	case JT_ROYAL_GUARD:
	case JT_ROYAL_GUARD_H:
	case JT_ROYAL_GUARD_B:
		return JT_ROYAL_GUARD;

	case JT_SURA:
	case JT_SURA_H:
	case JT_SURA_B:
		return JT_SURA;

	case JT_SORCERER:
	case JT_SORCERER_H:
	case JT_SORCERER_B:
		return JT_SORCERER;

	case JT_SHADOW_CHASER:
	case JT_SHADOW_CHASER_H:
	case JT_SHADOW_CHASER_B:
		return JT_SHADOW_CHASER;

	case JT_GENETIC:
	case JT_GENETIC_H:
	case JT_GENETIC_B:
		return JT_GENETIC;

	case JT_MINSTREL:
	case JT_MINSTREL_H:
	case JT_MINSTREL_B:
		return JT_MINSTREL;

	case JT_WANDERER:
	case JT_WANDERER_H:
	case JT_WANDERER_B:
		return JT_WANDERER;

	default:
		return job;
	};
}
