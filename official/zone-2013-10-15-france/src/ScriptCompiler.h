#pragma once


enum SCRIPT_FILE_TYPE
{
	DEF_ITEM         = 0,
	DEF_MOBNAME      = 1,
	DEF_NPCSPR       = 2,
	DEF_SKILL        = 3,
	BIN_COMMON       = 4,
	BIN_ITEM         = 5,
	BIN_NPC          = 6,
	BIN_SKILL        = 7,
	BIN_BUFF         = 8,
	ASM_COMMON       = 9,
	ASM_ITEM         = 10,
	ASM_NPC          = 11,
	ASM_SKILL        = 12,
	ASM_BUFF         = 13,
	SC_ENUM_V2       = 14,
	SC_STD_V2        = 15,
	SC_ITEM_SPECIAL  = 16,
	SC_NPC_MOBDEF    = 17,
	SC_SKILL_SPECIAL = 18,
	SC_BUFF_SPECIAL  = 19,
	NPC_LIST         = 20,
	DUNGEON_NPC_LIST = 21,
	HIS_NPC_LIST     = 22,
	SCRIPT_FILE_LAST = 23,
};


char* GetScriptFileName(SCRIPT_FILE_TYPE file);
