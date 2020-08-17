#include "Path.h"
#include "ScriptCompiler.h"
#include "ZoneProcess.h"


char* GetScriptFileName(SCRIPT_FILE_TYPE file) // 491-538
{
	const char* result;

	switch( file )
	{
	case DEF_ITEM:         result = ".\\scriptdata\\itp.def"; break;
	case DEF_MOBNAME:      result = ".\\scriptdata\\mobname.def"; break;
	case DEF_NPCSPR:       result = ".\\scriptdata\\npcspr.def"; break;
	case DEF_SKILL:        result = ".\\scriptdata\\skill.def"; break;
	case BIN_COMMON:       result = ".\\scriptbin\\common.bin"; break;
	case BIN_ITEM:         result = ".\\scriptbin\\item.bin"; break;
	case BIN_NPC:          result = ".\\scriptbin\\npc.bin"; break;
	case BIN_SKILL:        result = ".\\scriptbin\\skill.bin"; break;
	case BIN_BUFF:         result = ".\\scriptbin\\buff.bin"; break;
	case ASM_COMMON:       result = ".\\scriptbin\\common.asm"; break;
	case ASM_ITEM:         result = ".\\scriptbin\\item.asm"; break;
	case ASM_NPC:          result = ".\\scriptbin\\npc.asm"; break;
	case ASM_SKILL:        result = ".\\scriptbin\\skill.asm"; break;
	case ASM_BUFF:         result = ".\\scriptbin\\buff.asm"; break;
	case SC_ENUM_V2:       result = g_pathData.CPathData::SetFileName(".\\scriptdata\\enum.sc"); break;
	case SC_STD_V2:        result = g_pathData.CPathData::SetFileName(".\\scriptdata\\std_v2.sc"); break;
	case SC_ITEM_SPECIAL:  result = g_pathData.CPathData::SetFileName(".\\itemdata\\special.sc"); break;
	case SC_SKILL_SPECIAL: result = g_pathData.CPathData::SetFileName("SkillSpecial.sc"); break;
	case SC_BUFF_SPECIAL:  result = g_pathData.CPathData::SetFileName("BuffSpecial.sc");  break;
	case SC_NPC_MOBDEF:    result = g_pathData.CPathData::SetFileName(".\\scriptdata\\mobdef.sc"); break;
	case NPC_LIST:         result = g_pathDataNpc.CPathData::SetFileName(".\\npcdata\\list.txt"); break;
	case DUNGEON_NPC_LIST: result = g_pathDataNpc.CPathData::SetFileName(".\\npcdata\\dungeonList.txt"); break;
	case HIS_NPC_LIST:     result = ".\\npcScript_history.txt"; break;
	default:               result = ""; break;
	};

	if( result == NULL )
		result = "";

	return const_cast<char*>(result);
}
