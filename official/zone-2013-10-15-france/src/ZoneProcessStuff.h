#pragma once
struct EQUIPSLOTINFO; // #include "Struct.h"


/// @see IsSetting()
enum
{
	SETTING_NEWHPSP       = 0,
	SETTING_MANNER_POINT  = 1,
	SETTING_KILLER_SYSTEM = 2,
};


void shutdownlog();
int GetPureJob(int in_Job);
void InitRefinerySuccessPercent();
int GetRefinerySuccessPercent(int itemLv, int refiningLv, bool isAdvanced);
int GetLocalServerID();
int GetServerRandom(int in_Min, int in_Max);
int IsSetting(unsigned int setting);
void ZoneServerIdentity();
void CopyEquipItemSlotInfo(EQUIPSLOTINFO* des, EQUIPSLOTINFO* src);
time_t GetServerTime();
bool ScriptCompile();
const char* GetRootPath();
void OutputDebugLog(bool in_bDaemonServer);
int GetMaxCharacterLevel(short job); // (ZoneProcess.h)
int GetIndexFromBitFlag(int bitFlag); // (StdAfx.cpp)
void ModifyVar(int& var, int val, int max); // (StdAfx.cpp)
