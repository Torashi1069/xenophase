#include "FSMMgr.h"


CFSMMgr::CFSMMgr(void) // line 9
{
}


CFSMMgr::~CFSMMgr(void) // line 13
{
}


hook_method<void (CFSMMgr::*)(void)> CFSMMgr::_Init(SERVER, "CFSMMgr::Init");
void CFSMMgr::Init(void) // line 17
{
	return (this->*_Init)();

	m_scriptKeyword["NONE_IN"] = 0;
	m_scriptKeyword["WARP_SIGHT_IN"] = 1;
	m_scriptKeyword["TOUCHED_IN"] = 2;
	m_scriptKeyword["CLICK_IN"] = 3;
	m_scriptKeyword["WAIT_END_IN"] = 4;
	m_scriptKeyword["MOVE_RANDOM_END_IN"] = 5;
	m_scriptKeyword["ATTACKED_IN"] = 6;
	m_scriptKeyword["MILLI_ATTACKED_IN"] = 7;
	m_scriptKeyword["ENEMY_OUTSIGHT_IN"] = 8;
	m_scriptKeyword["MYOWNER_OUTSIGNT_IN"] = 9;
	m_scriptKeyword["ENEMY_DEAD_IN"] = 10;
	m_scriptKeyword["ENEMY_INATTACKSIGHT_IN"] = 11;
	m_scriptKeyword["NEAREST_CHARACTER_IN"] = 12;
	m_scriptKeyword["ENEMY_OUTATTACKSIGHT_IN"] = 13;
	m_scriptKeyword["DESTINATION_ARRIVED_IN"] = 14;
	m_scriptKeyword["ENERGY_RECHARGED_IN"] = 15;
	m_scriptKeyword["DEADSTATE_TIMEOUT_IN"] = 16;
	m_scriptKeyword["ITEM_INSIGHT_IN"] = 17;
	m_scriptKeyword["ARRIVEDAT_ITEM_IN"] = 18;
	m_scriptKeyword["TARGET_ITEM_DISAPPEAR_IN"] = 19;
	m_scriptKeyword["CHARACTER_INSIGHT_IN"] = 20;
	m_scriptKeyword["FRIEND_ATTACKED_IN"] = 21;
	m_scriptKeyword["ENEMY_FAR_INATTACKSIGHT_IN"] = 22;
	m_scriptKeyword["CHANGE_NORMALST_IN"] = 23;
	m_scriptKeyword["CHARACTER_ATTACKSIGHT_IN"] = 24;
	m_scriptKeyword["G_CHARACTER_ATTACKSIGHT_IN"] = 25;
	m_scriptKeyword["ARENASTART_IN"] = 26;
	m_scriptKeyword["MYOWNER_ATTACKED_IN"] = 27;
	m_scriptKeyword["LOWERLEVEL_INSIGHT_IN"] = 28;
	m_scriptKeyword["MAGIC_LOCKON_IN"] = 29;
	m_scriptKeyword["CHARACTER_INATTACKSIGHT_IN"] = 30;
	m_scriptKeyword["G_CHARACTER_INSIGHT_IN"] = 31;
	m_scriptKeyword["TOUCHEDNPC_IN"] = 32;
	m_scriptKeyword["TOUCHED2_IN"] = 33;
	m_scriptKeyword["MOVE_START_IN"] = 34;
	m_scriptKeyword["MOVE_END_POS_IN"] = 35;
	m_scriptKeyword["NONE_OUT"] = 0;
	m_scriptKeyword["CALL_CLICKEVENT_OUT"] = 2;
	m_scriptKeyword["CALL_TOUCHEVENT_OUT"] = 3;
	m_scriptKeyword["CALL_ARENASTART_OUT"] = 18;
	m_scriptKeyword["TRADE_START_OUT"] = 1;
	m_scriptKeyword["CHANGE_ENEMY_OUT"] = 16;
	m_scriptKeyword["MOVE_RANDOM_START_OUT"] = 4;
	m_scriptKeyword["WAIT_START_OUT"] = 5;
	m_scriptKeyword["EXPEL_OUT"] = 6;
	m_scriptKeyword["NONE_OUT"] = 0;
	m_scriptKeyword["ATTACK_ENEMY_OUT"] = 8;
	m_scriptKeyword["MOVETO_ENEMY_OUT"] = 9;
	m_scriptKeyword["MOVETO_FRIEND_OUT"] = 10;
	m_scriptKeyword["REVENGE_ENEMY_OUT"] = 11;
	m_scriptKeyword["SEARCH_OUT"] = 7;
	m_scriptKeyword["TRY_REVIVAL_OUT"] = 12;
	m_scriptKeyword["MOVETO_ITEM_OUT"] = 13;
	m_scriptKeyword["PICKUP_ITEM_OUT"] = 14;
	m_scriptKeyword["STOP_MOVE_OUT"] = 15;
	m_scriptKeyword["CHANGE_NORMALST_OUT"] = 17;
	m_scriptKeyword["MOVETO_MYOWNER_OUT"] = 19;
	m_scriptKeyword["REVENGE_RANDOM_OUT"] = 20;
	m_scriptKeyword["CALL_TOUCHNPCEVENT_OUT"] = 21;
	m_scriptKeyword["CALL_TOUCHEVENT2_OUT"] = 22;
	m_scriptKeyword["MOVE_START_OUT"] = 23;
	m_scriptKeyword["STOP_AND_CLICKEVENT_OUT"] = 24;
	m_scriptKeyword["STOP_MOVE_OUT"] = 15;
	m_scriptKeyword["STOP_AND_TRADER_OUT"] = 25;
	m_scriptKeyword["ARENA_GUIDE_NPC"] = 5;
	m_scriptKeyword["WARP_NPC"] = 0;
	m_scriptKeyword["HIDDEN_WARP_NPC"] = 33;
	m_scriptKeyword["GUIDE_NPC"] = 1;
	m_scriptKeyword["TALK_NPC"] = 2;
	m_scriptKeyword["TRADER_NPC"] = 3;
	m_scriptKeyword["EFFECT_NPC"] = 4;
	m_scriptKeyword["MONSTER_TYPE_01"] = 6;
	m_scriptKeyword["MONSTER_TYPE_02"] = 7;
	m_scriptKeyword["MONSTER_TYPE_03"] = 8;
	m_scriptKeyword["MONSTER_TYPE_04"] = 9;
	m_scriptKeyword["MONSTER_TYPE_05"] = 10;
	m_scriptKeyword["MONSTER_TYPE_06"] = 11;
	m_scriptKeyword["MONSTER_TYPE_07"] = 12;
	m_scriptKeyword["MONSTER_TYPE_08"] = 13;
	m_scriptKeyword["MONSTER_TYPE_09"] = 14;
	m_scriptKeyword["MONSTER_TYPE_10"] = 15;
	m_scriptKeyword["MONSTER_TYPE_11"] = 16;
	m_scriptKeyword["MONSTER_TYPE_12"] = 17;
	m_scriptKeyword["MONSTER_TYPE_13"] = 18;
	m_scriptKeyword["MONSTER_TYPE_14"] = 19;
	m_scriptKeyword["MONSTER_TYPE_15"] = 20;
	m_scriptKeyword["MONSTER_TYPE_16"] = 21;
	m_scriptKeyword["MONSTER_TYPE_17"] = 22;
	m_scriptKeyword["MONSTER_TYPE_18"] = 23;
	m_scriptKeyword["MONSTER_TYPE_19"] = 24;
	m_scriptKeyword["MONSTER_TYPE_20"] = 25;
	m_scriptKeyword["MONSTER_TYPE_21"] = 26;
	m_scriptKeyword["MONSTER_TYPE_22"] = 27;
	m_scriptKeyword["MONSTER_TYPE_23"] = 28;
	m_scriptKeyword["MONSTER_TYPE_24"] = 29;
	m_scriptKeyword["MONSTER_TYPE_25"] = 30;
	m_scriptKeyword["MONSTER_TYPE_26"] = 31;
	m_scriptKeyword["MONSTER_TYPE_27"] = 32;
	m_scriptKeyword["MONSTER_TYPE_28"] = 40;
	m_scriptKeyword["MERCENARY_TYPE_01"] = 34;
	m_scriptKeyword["MERCENARY_TYPE_02"] = 35;
	m_scriptKeyword["CASHTRADER_NPC"] = 36;
	m_scriptKeyword["MOVE_NPC_TYPE01"] = 37;
	m_scriptKeyword["MOVE_NPC_TRADER"] = 38;
	m_scriptKeyword["LUA_AI_TYPE"] = 39;
	m_scriptKeyword["IDLE_ST"] = 0;
	m_scriptKeyword["RMOVE_ST"] = 1;
	m_scriptKeyword["FOLLOW_ST"] = 2;
	m_scriptKeyword["ANGRY_ST"] = 3;
	m_scriptKeyword["RUSH_ST"] = 4;
	m_scriptKeyword["BERSERK_ST"] = 7;
	m_scriptKeyword["FIGHT_ST"] = 8;
	m_scriptKeyword["MOVEENEMY_ST"] = 9;
	m_scriptKeyword["MOVEHELP_ST"] = 10;
	m_scriptKeyword["SEARCH_ST"] = 6;
	m_scriptKeyword["FOLLOW_SEARCH_ST"] = 5;
	m_scriptKeyword["DEAD_ST"] = 11;
	m_scriptKeyword["MOVEITEM_ST"] = 12;
	m_scriptKeyword["ABNORMAL_ST"] = 13;

	int errcode = this->CFSMMgr::Load_FSM_NpcScript();
	if( errcode > 0 )
	{
		char errMsg[256];
		memset(errMsg, 0, sizeof(errMsg));
		sprintf(errMsg, "FSM Load_FSM_NpcScript() Fail ERRCODE = %d", errcode);
		MessageBoxA(NULL, errMsg, NULL, MB_OK);
	}
}


//hook_method<void (CFSMMgr::*)(const char* filename, int verDate)> CFSMMgr::_LoadScript(SERVER, "CFSMMgr::LoadScript");
void CFSMMgr::LoadScript(const char* filename, int verDate) // line ???
{
//	return (this->*_LoadScript)(filename, verDate);

	char line[512];

	FILE* fp = fopen(filename, "r");
	if( fp == NULL )
		return;

	int date;
	fscanf(fp, "%d\n", &date);
	if( date != verDate )
	{
		sprintf(line, "%s old version?", filename);
		MessageBoxA(NULL, line, "error", MB_OK);
	}

	while( !feof(fp) )
	{
		fgets(line, sizeof(line), fp);

		if( strstr(line, "//") != NULL )
			continue;

		if( strlen(line) < 10 )
			continue;

		char npcTypeKeyWord[50];
		char stateKeyWord[50];
		char inputKeyWord[50];
		char outputKeyWord[50];
		char outputState[50];

		sscanf(line, "%s%s%s%s%s", npcTypeKeyWord, stateKeyWord, inputKeyWord, outputKeyWord, outputState);

		SCRIPT_INPUT scriptInput;
		scriptInput.npcTypeID = this->CFSMMgr::GetKeyWord(npcTypeKeyWord);
		scriptInput.fsmStateID = this->CFSMMgr::GetKeyWord(stateKeyWord);
		scriptInput.inputType = this->CFSMMgr::GetKeyWord(inputKeyWord);
		scriptInput.outputType = this->CFSMMgr::GetKeyWord(outputKeyWord);
		scriptInput.outputState = this->CFSMMgr::GetKeyWord(outputState);
		this->CFSMMgr::AddFSM(&scriptInput);
	}

	fclose(fp);
}


hook_method<CFSM* (CFSMMgr::*)(unsigned long fsmID)> CFSMMgr::_GetFSM(SERVER, "CFSMMgr::GetFSM");
CFSM* CFSMMgr::GetFSM(unsigned long fsmID) // line 174
{
	return (this->*_GetFSM)(fsmID);

	mystd::map<unsigned long,CFSM*>::iterator it = m_fsm.find(fsmID);
	return ( it != m_fsm.end() ) ? it->second : NULL;
}


//hook_method<void (CFSMMgr::*)(void)> CFSMMgr::_Destroy(SERVER, "CFSMMgr::Destroy");
void CFSMMgr::Destroy(void) // line ???
{
//	return (this->*_Destroy)();

	;
}


hook_method<unsigned long (CFSMMgr::*)(const char* strKeyWord)> CFSMMgr::_GetKeyWord(SERVER, "CFSMMgr::GetKeyWord");
unsigned long CFSMMgr::GetKeyWord(const char* strKeyWord) // line 262
{
	return (this->*_GetKeyWord)(strKeyWord);

	mystd::map<mystd::string,unsigned long>::iterator it = m_scriptKeyword.find(strKeyWord);
	return( it != m_scriptKeyword.end() ) ? it->second : -1;
}


hook_method<int (CFSMMgr::*)(void)> CFSMMgr::_Load_FSM_NpcScript(SERVER, "CFSMMgr::Load_FSM_NpcScript");
int CFSMMgr::Load_FSM_NpcScript(void) // line 273
{
	return (this->*_Load_FSM_NpcScript)();

	if( !this->CFSMMgr::SetDefined("ARENA_GUIDE_NPC", "IDLE_ST", "ARENASTART_IN", "CALL_ARENASTART_OUT", "IDLE_ST") ) return 1;
	if( !this->CFSMMgr::SetDefined("WARP_NPC", "IDLE_ST", "TOUCHED_IN", "CALL_TOUCHEVENT_OUT", "IDLE_ST") ) return 2;
	if( !this->CFSMMgr::SetDefined("WARP_NPC", "IDLE_ST", "TOUCHEDNPC_IN", "CALL_TOUCHNPCEVENT_OUT", "IDLE_ST") ) return 3;
	if( !this->CFSMMgr::SetDefined("WARP_NPC", "IDLE_ST", "TOUCHED2_IN", "CALL_TOUCHEVENT2_OUT", "IDLE_ST") ) return 4;
	if( !this->CFSMMgr::SetDefined("HIDDEN_WARP_NPC", "IDLE_ST", "TOUCHED_IN", "CALL_TOUCHEVENT_OUT", "IDLE_ST") ) return 5;
	if( !this->CFSMMgr::SetDefined("HIDDEN_WARP_NPC", "IDLE_ST", "TOUCHEDNPC_IN", "CALL_TOUCHNPCEVENT_OUT", "IDLE_ST") ) return 6;
	if( !this->CFSMMgr::SetDefined("HIDDEN_WARP_NPC", "IDLE_ST", "TOUCHED2_IN", "CALL_TOUCHEVENT2_OUT", "IDLE_ST") ) return 7;
	if( !this->CFSMMgr::SetDefined("TALK_NPC", "IDLE_ST", "CLICK_IN", "CALL_CLICKEVENT_OUT", "IDLE_ST") ) return 8;
	if( !this->CFSMMgr::SetDefined("TALK_NPC", "IDLE_ST", "TOUCHED_IN", "CALL_TOUCHEVENT_OUT", "IDLE_ST") ) return 9;
	if( !this->CFSMMgr::SetDefined("TALK_NPC", "IDLE_ST", "TOUCHEDNPC_IN", "CALL_TOUCHNPCEVENT_OUT", "IDLE_ST") ) return 10;
	if( !this->CFSMMgr::SetDefined("TALK_NPC", "IDLE_ST", "TOUCHED2_IN", "CALL_TOUCHEVENT2_OUT", "IDLE_ST") ) return 11;
	if( !this->CFSMMgr::SetDefined("GUIDE_NPC", "IDLE_ST", "CLICK_IN", "CALL_CLICKEVENT_OUT", "IDLE_ST") ) return 12;
	if( !this->CFSMMgr::SetDefined("TRADER_NPC", "IDLE_ST", "CLICK_IN", "TRADE_START_OUT", "IDLE_ST") ) return 13;
	if( !this->CFSMMgr::SetDefined("EFFECT_NPC", "IDLE_ST", "CLICK_IN", "CALL_CLICKEVENT_OUT", "IDLE_ST") ) return 14;
	if( !this->CFSMMgr::SetDefined("CASHTRADER_NPC", "IDLE_ST", "CLICK_IN", "TRADE_START_OUT", "IDLE_ST") ) return 15;
	if( !this->CFSMMgr::SetDefined("MOVE_NPC_TYPE01", "IDLE_ST", "MOVE_START_IN", "MOVE_START_OUT", "RMOVE_ST") ) return 16;
	if( !this->CFSMMgr::SetDefined("MOVE_NPC_TYPE01", "IDLE_ST", "CLICK_IN", "CALL_CLICKEVENT_OUT", "IDLE_ST") ) return 17;
	if( !this->CFSMMgr::SetDefined("MOVE_NPC_TYPE01", "RMOVE_ST", "CLICK_IN", "STOP_AND_CLICKEVENT_OUT", "IDLE_ST") ) return 18;
	if( !this->CFSMMgr::SetDefined("MOVE_NPC_TYPE01", "RMOVE_ST", "MOVE_END_POS_IN", "WAIT_START_OUT", "IDLE_ST") ) return 19;
	if( !this->CFSMMgr::SetDefined("MOVE_NPC_TRADER", "IDLE_ST", "MOVE_START_IN", "MOVE_START_OUT", "RMOVE_ST") ) return 20;
	if( !this->CFSMMgr::SetDefined("MOVE_NPC_TRADER", "IDLE_ST", "CLICK_IN", "TRADE_START_OUT", "IDLE_ST") ) return 21;
	if( !this->CFSMMgr::SetDefined("MOVE_NPC_TRADER", "RMOVE_ST", "CLICK_IN", "STOP_AND_TRADER_OUT", "IDLE_ST") ) return 22;
	if( !this->CFSMMgr::SetDefined("MOVE_NPC_TRADER", "RMOVE_ST", "MOVE_END_POS_IN", "WAIT_START_OUT", "IDLE_ST") ) return 23;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 24;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 25;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 26;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 27;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 28;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 29;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 30;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 31;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 32;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 33;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 34;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 35;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 36;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_01", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 37;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "IDLE_ST", "ITEM_INSIGHT_IN", "MOVETO_ITEM_OUT", "MOVEITEM_ST") ) return 38;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 39;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 40;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 41;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "RMOVE_ST", "ITEM_INSIGHT_IN", "MOVETO_ITEM_OUT", "MOVEITEM_ST") ) return 42;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 43;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 44;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 45;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 46;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 47;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 48;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 49;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "MOVEITEM_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 50;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "MOVEITEM_ST", "TARGET_ITEM_DISAPPEAR_IN", "STOP_MOVE_OUT", "IDLE_ST") ) return 51;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "MOVEITEM_ST", "ARRIVEDAT_ITEM_IN", "PICKUP_ITEM_OUT", "IDLE_ST") ) return 52;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 53;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 54;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 55;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_02", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 56;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "IDLE_ST", "FRIEND_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 57;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 58;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 59;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "RMOVE_ST", "FRIEND_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 60;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 61;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 62;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 63;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 64;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 65;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 66;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 67;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 68;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 69;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 70;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 71;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 72;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_03", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 73;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "FOLLOW_ST") ) return 74;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 75;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 76;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "FOLLOW_ST") ) return 77;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 78;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 79;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 80;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "FOLLOW_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "ANGRY_ST") ) return 81;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "FOLLOW_ST", "NEAREST_CHARACTER_IN", "EXPEL_OUT", "FOLLOW_SEARCH_ST") ) return 82;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "FOLLOW_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "FOLLOW_SEARCH_ST") ) return 83;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "FOLLOW_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 84;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 85;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 86;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 87;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "FOLLOW_SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 88;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "FOLLOW_SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "ANGRY_ST") ) return 89;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "FOLLOW_SEARCH_ST", "NEAREST_CHARACTER_IN", "EXPEL_OUT", "FOLLOW_ST") ) return 90;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "FOLLOW_SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "FOLLOW_ST") ) return 91;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 92;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 93;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 94;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "ANGRY_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 95;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "ANGRY_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 96;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "ANGRY_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "FOLLOW_ST") ) return 97;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "ANGRY_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "ANGRY_ST") ) return 98;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "ANGRY_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 99;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 100;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 101;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 102;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 103;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_04", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 104;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 105;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 106;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 107;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 108;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 109;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 110;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 111;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 112;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 113;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 114;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 115;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 116;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 117;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 118;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 119;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 120;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_05", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 121;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_06", "IDLE_ST", "ATTACKED_IN", "NONE_OUT", "IDLE_ST") ) return 122;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_06", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 123;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_06", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 124;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "IDLE_ST", "ITEM_INSIGHT_IN", "MOVETO_ITEM_OUT", "MOVEITEM_ST") ) return 125;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "IDLE_ST", "FRIEND_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 126;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 127;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 128;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 129;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "RMOVE_ST", "ITEM_INSIGHT_IN", "MOVETO_ITEM_OUT", "MOVEITEM_ST") ) return 130;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "RMOVE_ST", "FRIEND_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 131;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 132;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 133;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 134;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 135;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 136;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 137;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 138;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "MOVEITEM_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 139;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "MOVEITEM_ST", "TARGET_ITEM_DISAPPEAR_IN", "STOP_MOVE_OUT", "IDLE_ST") ) return 140;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "MOVEITEM_ST", "ARRIVEDAT_ITEM_IN", "PICKUP_ITEM_OUT", "IDLE_ST") ) return 141;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 142;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 143;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 144;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 145;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_07", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 146;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "IDLE_ST", "LOWERLEVEL_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 147;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 148;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 149;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "RMOVE_ST", "LOWERLEVEL_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 150;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 151;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 152;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 153;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 154;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 155;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 156;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 157;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 158;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 159;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 160;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 161;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 162;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 163;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_08", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 164;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "IDLE_ST", "ATTACKED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 165;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "IDLE_ST", "CHARACTER_ATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 166;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "NONE_OUT", "IDLE_ST") ) return 167;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 168;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 169;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 170;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_11", "IDLE_ST", "ATTACKED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 171;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_11", "IDLE_ST", "G_CHARACTER_ATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 172;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_11", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "NONE_OUT", "IDLE_ST") ) return 173;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_11", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 174;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_11", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 175;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "IDLE_ST", "G_CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 176;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 177;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 178;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RMOVE_ST", "G_CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 179;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 180;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 181;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 182;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 183;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 184;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 185;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 186;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 187;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 188;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 189;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 190;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 191;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "IDLE_ST", "FRIEND_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 192;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 193;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 194;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 195;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RMOVE_ST", "FRIEND_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 196;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 197;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 198;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 199;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 200;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 201;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 202;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 203;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 204;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 205;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 206;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 207;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 208;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 209;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 210;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 211;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "IDLE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 212;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 213;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 214;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "RMOVE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 215;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 216;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 217;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 218;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 219;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 220;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 221;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 222;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 223;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 224;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 225;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 226;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 227;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "IDLE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 228;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 229;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 230;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 231;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RMOVE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 232;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 233;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 234;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 235;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 236;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 237;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 238;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 239;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 240;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 241;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 242;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 243;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 244;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 245;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 246;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 247;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "IDLE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 248;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 249;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 250;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 251;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RMOVE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 252;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 253;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 254;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 255;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 256;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RUSH_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 257;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 258;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 259;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 260;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 261;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 262;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 263;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 264;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 265;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 266;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 267;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 268;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "IDLE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 269;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 270;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 271;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 272;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RMOVE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 273;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 274;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 275;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 276;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 277;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RUSH_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 278;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 279;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RUSH_ST", "CHARACTER_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 280;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 281;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 282;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 283;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 284;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 285;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 286;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 287;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 288;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 289;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 290;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "IDLE_ST", "MYOWNER_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 291;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "RMOVE_ST") ) return 292;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 293;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "RMOVE_ST", "MYOWNER_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 294;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 295;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 296;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 297;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 298;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 299;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 300;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 301;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 302;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 303;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 304;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 305;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 306;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_25", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "FOLLOW_ST") ) return 307;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_25", "FOLLOW_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 308;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "IDLE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 309;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 310;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 311;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 312;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RMOVE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 313;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 314;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 315;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 316;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 317;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RUSH_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 318;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 319;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RUSH_ST", "CHARACTER_INATTACKSIGHT_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 320;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 321;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 322;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 323;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 324;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 325;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 326;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 327;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 328;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 329;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 330;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "IDLE_ST", "ATTACKED_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 331;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "IDLE_ST", "CHARACTER_ATTACKSIGHT_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 332;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "NONE_OUT", "IDLE_ST") ) return 333;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 334;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 335;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 336;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "FOLLOW_ST") ) return 337;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "IDLE_ST", "MYOWNER_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 338;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 339;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 340;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "RUSH_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 341;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 342;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 343;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 344;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "FOLLOW_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 345;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "FOLLOW_ST") ) return 346;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "IDLE_ST", "MYOWNER_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 347;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 348;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 349;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "RUSH_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 350;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 351;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 352;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 353;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "FOLLOW_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 354;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "IDLE_ST", "MYOWNER_ATTACKED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 355;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "IDLE_ST", "ATTACKED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 356;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "IDLE_ST", "CHARACTER_ATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 357;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "NONE_OUT", "IDLE_ST") ) return 358;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 359;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 360;
	
	return 0;
}


hook_method<bool (CFSMMgr::*)(const char* npcTypeID, const char* fsmStateID, const char* inputType, const char* outputType, const char* outputState)> CFSMMgr::_SetDefined(SERVER, "CFSMMgr::SetDefined");
bool CFSMMgr::SetDefined(const char* npcTypeID, const char* fsmStateID, const char* inputType, const char* outputType, const char* outputState) // line 814
{
	return (this->*_SetDefined)(npcTypeID, fsmStateID, inputType, outputType, outputState);

	if( npcTypeID == 0 || fsmStateID == 0 || inputType == 0 || outputType == 0 || outputState == 0 )
		return false;

	unsigned long nnpcTypeID, nfsmStateID, ninputType, noutputType, noutputState;
	if( (nnpcTypeID = this->CFSMMgr::GetKeyWord(npcTypeID), nnpcTypeID == -1 )
	||  (nfsmStateID = this->CFSMMgr::GetKeyWord(fsmStateID), nfsmStateID == -1)
	||  (ninputType = this->CFSMMgr::GetKeyWord(inputType), ninputType == -1)
	||  (noutputType = this->CFSMMgr::GetKeyWord(outputType), noutputType == -1)
	||  (noutputState = this->CFSMMgr::GetKeyWord(outputState), noutputState == -1) )
		return false;

	SCRIPT_INPUT scriptInput;
	scriptInput.outputState = noutputState;
	scriptInput.npcTypeID = nnpcTypeID;
	scriptInput.fsmStateID = nfsmStateID;
	scriptInput.inputType = ninputType;
	scriptInput.outputType = noutputType;
	this->CFSMMgr::AddFSM(&scriptInput);

	return true;
}


hook_method<void (CFSMMgr::*)(SCRIPT_INPUT* inputData)> CFSMMgr::_AddFSM(SERVER, "CFSMMgr::AddFSM");
void CFSMMgr::AddFSM(SCRIPT_INPUT* inputData) // line 188
{
	return (this->*_AddFSM)(inputData);

	mystd::map<unsigned long,CFSM*>::iterator it = m_fsm.find(inputData->npcTypeID);
	if( it == m_fsm.end() )
	{
		CFSM* fsm = new CFSM();
		fsm->CFSM::Init(inputData->npcTypeID);
		fsm->CFSM::AddFSMState(inputData->fsmStateID, inputData->inputType, inputData->outputType, inputData->outputState);
		m_fsm[inputData->npcTypeID] = fsm;
	}
	else
	{
		it->second->CFSM::AddFSMState(inputData->fsmStateID, inputData->inputType, inputData->outputType, inputData->outputState);
	}
}


//hook_method<void (CFSMMgr::*)(unsigned long npcTypeID)> CFSMMgr::_DeleteFSM(SERVER, "CFSMMgr::DeleteFSM");
void CFSMMgr::DeleteFSM(unsigned long npcTypeID) // line ???
{
//	return (this->*_DeleteFSM)(npcTypeID);

	;
}
