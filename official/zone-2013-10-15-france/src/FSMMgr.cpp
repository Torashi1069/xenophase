#include "FSMMgr.h"
#include "NPC.h"


CFSMMgr::CFSMMgr()
{
}


CFSMMgr::~CFSMMgr()
{
}


void CFSMMgr::Init()
{
	m_scriptKeyword["NONE_IN"] = NONE_IN;
	m_scriptKeyword["WARP_SIGHT_IN"] = WARP_SIGHT_IN;
	m_scriptKeyword["TOUCHED_IN"] = TOUCHED_IN;
	m_scriptKeyword["CLICK_IN"] = CLICK_IN;
	m_scriptKeyword["WAIT_END_IN"] = WAIT_END_IN;
	m_scriptKeyword["MOVE_RANDOM_END_IN"] = MOVE_RANDOM_END_IN;
	m_scriptKeyword["ATTACKED_IN"] = ATTACKED_IN;
	m_scriptKeyword["MILLI_ATTACKED_IN"] = MILLI_ATTACKED_IN;
	m_scriptKeyword["ENEMY_OUTSIGHT_IN"] = ENEMY_OUTSIGHT_IN;
	m_scriptKeyword["MYOWNER_OUTSIGNT_IN"] = MYOWNER_OUTSIGNT_IN;
	m_scriptKeyword["ENEMY_DEAD_IN"] = ENEMY_DEAD_IN;
	m_scriptKeyword["ENEMY_INATTACKSIGHT_IN"] = ENEMY_INATTACKSIGHT_IN;
	m_scriptKeyword["NEAREST_CHARACTER_IN"] = NEAREST_CHARACTER_IN;
	m_scriptKeyword["ENEMY_OUTATTACKSIGHT_IN"] = ENEMY_OUTATTACKSIGHT_IN;
	m_scriptKeyword["DESTINATION_ARRIVED_IN"] = DESTINATION_ARRIVED_IN;
	m_scriptKeyword["ENERGY_RECHARGED_IN"] = ENERGY_RECHARGED_IN;
	m_scriptKeyword["DEADSTATE_TIMEOUT_IN"] = DEADSTATE_TIMEOUT_IN;
	m_scriptKeyword["ITEM_INSIGHT_IN"] = ITEM_INSIGHT_IN;
	m_scriptKeyword["ARRIVEDAT_ITEM_IN"] = ARRIVEDAT_ITEM_IN;
	m_scriptKeyword["TARGET_ITEM_DISAPPEAR_IN"] = TARGET_ITEM_DISAPPEAR_IN;
	m_scriptKeyword["CHARACTER_INSIGHT_IN"] = CHARACTER_INSIGHT_IN;
	m_scriptKeyword["FRIEND_ATTACKED_IN"] = FRIEND_ATTACKED_IN;
	m_scriptKeyword["ENEMY_FAR_INATTACKSIGHT_IN"] = ENEMY_FAR_INATTACKSIGHT_IN;
	m_scriptKeyword["CHANGE_NORMALST_IN"] = CHANGE_NORMALST_IN;
	m_scriptKeyword["CHARACTER_ATTACKSIGHT_IN"] = CHARACTER_ATTACKSIGHT_IN;
	m_scriptKeyword["G_CHARACTER_ATTACKSIGHT_IN"] = G_CHARACTER_ATTACKSIGHT_IN;
	m_scriptKeyword["ARENASTART_IN"] = ARENASTART_IN;
	m_scriptKeyword["MYOWNER_ATTACKED_IN"] = MYOWNER_ATTACKED_IN;
	m_scriptKeyword["LOWERLEVEL_INSIGHT_IN"] = LOWERLEVEL_INSIGHT_IN;
	m_scriptKeyword["MAGIC_LOCKON_IN"] = MAGIC_LOCKON_IN;
	m_scriptKeyword["CHARACTER_INATTACKSIGHT_IN"] = CHARACTER_INATTACKSIGHT_IN;
	m_scriptKeyword["G_CHARACTER_INSIGHT_IN"] = G_CHARACTER_INSIGHT_IN;
	m_scriptKeyword["TOUCHEDNPC_IN"] = TOUCHEDNPC_IN;
	m_scriptKeyword["TOUCHED2_IN"] = TOUCHED2_IN;
	m_scriptKeyword["MOVE_START_IN"] = MOVE_START_IN;
	m_scriptKeyword["MOVE_END_POS_IN"] = MOVE_END_POS_IN;

	m_scriptKeyword["NONE_OUT"] = NONE_OUT;
	m_scriptKeyword["CALL_CLICKEVENT_OUT"] = CALL_CLICKEVENT_OUT;
	m_scriptKeyword["CALL_TOUCHEVENT_OUT"] = CALL_TOUCHEVENT_OUT;
	m_scriptKeyword["CALL_ARENASTART_OUT"] = CALL_ARENASTART_OUT;
	m_scriptKeyword["TRADE_START_OUT"] = TRADE_START_OUT;
	m_scriptKeyword["CHANGE_ENEMY_OUT"] = CHANGE_ENEMY_OUT;
	m_scriptKeyword["MOVE_RANDOM_START_OUT"] = MOVE_RANDOM_START_OUT;
	m_scriptKeyword["WAIT_START_OUT"] = WAIT_START_OUT;
	m_scriptKeyword["EXPEL_OUT"] = EXPEL_OUT;
	m_scriptKeyword["NONE_OUT"] = NONE_OUT; //NOTE: duplicate
	m_scriptKeyword["ATTACK_ENEMY_OUT"] = ATTACK_ENEMY_OUT;
	m_scriptKeyword["MOVETO_ENEMY_OUT"] = MOVETO_ENEMY_OUT;
	m_scriptKeyword["MOVETO_FRIEND_OUT"] = MOVETO_FRIEND_OUT;
	m_scriptKeyword["REVENGE_ENEMY_OUT"] = REVENGE_ENEMY_OUT;
	m_scriptKeyword["SEARCH_OUT"] = SEARCH_OUT;
	m_scriptKeyword["TRY_REVIVAL_OUT"] = TRY_REVIVAL_OUT;
	m_scriptKeyword["MOVETO_ITEM_OUT"] = MOVETO_ITEM_OUT;
	m_scriptKeyword["PICKUP_ITEM_OUT"] = PICKUP_ITEM_OUT;
	m_scriptKeyword["STOP_MOVE_OUT"] = STOP_MOVE_OUT;
	m_scriptKeyword["CHANGE_NORMALST_OUT"] = CHANGE_NORMALST_OUT;
	m_scriptKeyword["MOVETO_MYOWNER_OUT"] = MOVETO_MYOWNER_OUT;
	m_scriptKeyword["REVENGE_RANDOM_OUT"] = REVENGE_RANDOM_OUT;
	m_scriptKeyword["CALL_TOUCHNPCEVENT_OUT"] = CALL_TOUCHNPCEVENT_OUT;
	m_scriptKeyword["CALL_TOUCHEVENT2_OUT"] = CALL_TOUCHEVENT2_OUT;
	m_scriptKeyword["MOVE_START_OUT"] = MOVE_START_OUT;
	m_scriptKeyword["STOP_AND_CLICKEVENT_OUT"] = STOP_AND_CLICKEVENT_OUT;
	m_scriptKeyword["STOP_MOVE_OUT"] = STOP_MOVE_OUT;
	m_scriptKeyword["STOP_AND_TRADER_OUT"] = STOP_AND_TRADER_OUT;

	m_scriptKeyword["ARENA_GUIDE_NPC"] = ARENA_GUIDE_NPC;
	m_scriptKeyword["WARP_NPC"] = WARP_NPC;
	m_scriptKeyword["HIDDEN_WARP_NPC"] = HIDDEN_WARP_NPC;
	m_scriptKeyword["GUIDE_NPC"] = GUIDE_NPC;
	m_scriptKeyword["TALK_NPC"] = TALK_NPC;
	m_scriptKeyword["TRADER_NPC"] = TRADER_NPC;
	m_scriptKeyword["EFFECT_NPC"] = EFFECT_NPC;
	m_scriptKeyword["MONSTER_TYPE_01"] = MONSTER_TYPE_01;
	m_scriptKeyword["MONSTER_TYPE_02"] = MONSTER_TYPE_02;
	m_scriptKeyword["MONSTER_TYPE_03"] = MONSTER_TYPE_03;
	m_scriptKeyword["MONSTER_TYPE_04"] = MONSTER_TYPE_04;
	m_scriptKeyword["MONSTER_TYPE_05"] = MONSTER_TYPE_05;
	m_scriptKeyword["MONSTER_TYPE_06"] = MONSTER_TYPE_06;
	m_scriptKeyword["MONSTER_TYPE_07"] = MONSTER_TYPE_07;
	m_scriptKeyword["MONSTER_TYPE_08"] = MONSTER_TYPE_08;
	m_scriptKeyword["MONSTER_TYPE_09"] = MONSTER_TYPE_09;
	m_scriptKeyword["MONSTER_TYPE_10"] = MONSTER_TYPE_10;
	m_scriptKeyword["MONSTER_TYPE_11"] = MONSTER_TYPE_11;
	m_scriptKeyword["MONSTER_TYPE_12"] = MONSTER_TYPE_12;
	m_scriptKeyword["MONSTER_TYPE_13"] = MONSTER_TYPE_13;
	m_scriptKeyword["MONSTER_TYPE_14"] = MONSTER_TYPE_14;
	m_scriptKeyword["MONSTER_TYPE_15"] = MONSTER_TYPE_15;
	m_scriptKeyword["MONSTER_TYPE_16"] = MONSTER_TYPE_16;
	m_scriptKeyword["MONSTER_TYPE_17"] = MONSTER_TYPE_17;
	m_scriptKeyword["MONSTER_TYPE_18"] = MONSTER_TYPE_18;
	m_scriptKeyword["MONSTER_TYPE_19"] = MONSTER_TYPE_19;
	m_scriptKeyword["MONSTER_TYPE_20"] = MONSTER_TYPE_20;
	m_scriptKeyword["MONSTER_TYPE_21"] = MONSTER_TYPE_21;
	m_scriptKeyword["MONSTER_TYPE_22"] = MONSTER_TYPE_22;
	m_scriptKeyword["MONSTER_TYPE_23"] = MONSTER_TYPE_23;
	m_scriptKeyword["MONSTER_TYPE_24"] = MONSTER_TYPE_24;
	m_scriptKeyword["MONSTER_TYPE_25"] = MONSTER_TYPE_25;
	m_scriptKeyword["MONSTER_TYPE_26"] = MONSTER_TYPE_26;
	m_scriptKeyword["MONSTER_TYPE_27"] = MONSTER_TYPE_27;
	m_scriptKeyword["MONSTER_TYPE_28"] = MONSTER_TYPE_28;
	m_scriptKeyword["MERCENARY_TYPE_01"] = MERCENARY_TYPE_01;
	m_scriptKeyword["MERCENARY_TYPE_02"] = MERCENARY_TYPE_02;
	m_scriptKeyword["CASHTRADER_NPC"] = CASHTRADER_NPC;
	m_scriptKeyword["MOVE_NPC_TYPE01"] = MOVE_NPC_TYPE01;
	m_scriptKeyword["MOVE_NPC_TRADER"] = MOVE_NPC_TRADER;
	m_scriptKeyword["LUA_AI_TYPE"] = LUA_AI_TYPE;
	m_scriptKeyword["LUA_ELEMENTAL_TYPE"] = LUA_ELEMENTAL_TYPE;
	m_scriptKeyword["ELEMENTAL_TYPE_WAIT"] = ELEMENTAL_TYPE_WAIT;
	m_scriptKeyword["ELEMENTAL_TYPE_PASSIVE"] = ELEMENTAL_TYPE_PASSIVE;
	m_scriptKeyword["ELEMENTAL_TYPE_DEFENSIVE"] = ELEMENTAL_TYPE_DEFENSIVE;
	m_scriptKeyword["ELEMENTAL_TYPE_OFFENSIVE"] = ELEMENTAL_TYPE_OFFENSIVE;

	m_scriptKeyword["IDLE_ST"] = IDLE_ST;
	m_scriptKeyword["RMOVE_ST"] = RMOVE_ST;
	m_scriptKeyword["FOLLOW_ST"] = FOLLOW_ST;
	m_scriptKeyword["ANGRY_ST"] = ANGRY_ST;
	m_scriptKeyword["RUSH_ST"] = RUSH_ST;
	m_scriptKeyword["BERSERK_ST"] = BERSERK_ST;
	m_scriptKeyword["FIGHT_ST"] = FIGHT_ST;
	m_scriptKeyword["MOVEENEMY_ST"] = MOVEENEMY_ST;
	m_scriptKeyword["MOVEHELP_ST"] = MOVEHELP_ST;
	m_scriptKeyword["SEARCH_ST"] = SEARCH_ST;
	m_scriptKeyword["FOLLOW_SEARCH_ST"] = FOLLOW_SEARCH_ST;
	m_scriptKeyword["DEAD_ST"] = DEAD_ST;
	m_scriptKeyword["MOVEITEM_ST"] = MOVEITEM_ST;	
	m_scriptKeyword["ABNORMAL_ST"] = ABNORMAL_ST;

	m_scriptKeyword["MOB_TOMB_NPC"] = MOB_TOMB_NPC;
	m_scriptKeyword["CLICK_EVENT_MOB_TOMB_OUT"] = CLICK_EVENT_MOB_TOMB_OUT;
	m_scriptKeyword["MONSTER_TYPE_29"] = MONSTER_TYPE_29;
	m_scriptKeyword["FIXED_MOB_TYPE__CHARACTER_ATTACKSIGHT_IN"] = FIXED_MOB_TYPE__CHARACTER_ATTACKSIGHT_IN;

	int err = this->CFSMMgr::Load_FSM_NpcScript();
	if( err > 0 )
	{
		char errMsg[256] = {};
		sprintf_s(errMsg, countof(errMsg), "FSM Load_FSM_NpcScript() Fail ERRCODE = %d", err);
		MessageBoxA(NULL, errMsg, NULL, MB_OK);
		return;
	}
}


CFSM* CFSMMgr::GetFSM(unsigned long fsmID)
{
	std::map<unsigned long,CFSM*>::iterator iter = m_fsm.find(fsmID);
	if( iter == m_fsm.end() )
		return NULL;

	return iter->second;
}


void CFSMMgr::Destroy()
{
}


void CFSMMgr::AddFSM(SCRIPT_INPUT* inputData)
{
	std::map<unsigned long,CFSM*>::iterator iter = m_fsm.find(inputData->npcTypeID);
	if( iter == m_fsm.end() )
	{
		CFSM* fsm = new CFSM();
		fsm->CFSM::Init(inputData->npcTypeID);
		fsm->CFSM::AddFSMState(inputData->fsmStateID, inputData->inputType, inputData->outputType, inputData->outputState);
		m_fsm[inputData->npcTypeID] = fsm;
	}
	else
	{
		CFSM* fsm = iter->second;
		fsm->CFSM::AddFSMState(inputData->fsmStateID, inputData->inputType, inputData->outputType, inputData->outputState);
	}
}


void CFSMMgr::DeleteFSM(unsigned long npcTypeID)
{
}


void CFSMMgr::LoadScript(const char* filename, int verDate)
{
	FILE* fp = fopen(filename, "r");
	if( fp == NULL )
		return;

	int date;
	fscanf(fp, "%d\n", &date);

	if( date != verDate )
	{
		char line[512];
		sprintf(line, "%s old version?", filename);
		MessageBoxA(NULL, line, "error", MB_OK);
	}

	while( !feof(fp) )
	{
		char line[512];
		fgets(line, countof(line), fp);

		if( strstr(line, "//") != NULL || strlen(line) < 10 )
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


unsigned long CFSMMgr::GetKeyWord(const char* strKeyWord)
{
	std::map<std::string,unsigned long>::iterator iter = m_scriptKeyword.find(strKeyWord);
	if( iter == m_scriptKeyword.end() )
		return -1;

	return iter->second;
}


int CFSMMgr::Load_FSM_NpcScript()
{
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
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "IDLE_ST", "FIXED_MOB_TYPE__CHARACTER_ATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 166;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "NONE_OUT", "IDLE_ST") ) return 167;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "NONE_OUT", "IDLE_ST") ) return 168;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 169;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 170;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_10", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 171;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_11", "IDLE_ST", "ATTACKED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 172;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_11", "IDLE_ST", "G_CHARACTER_ATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 173;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_11", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "NONE_OUT", "IDLE_ST") ) return 174;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_11", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 175;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_11", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 176;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "IDLE_ST", "G_CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 177;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 178;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 179;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RMOVE_ST", "G_CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 180;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 181;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 182;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 183;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 184;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 185;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 186;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 187;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 188;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 189;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 190;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 191;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_12", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 192;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "IDLE_ST", "FRIEND_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 193;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 194;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 195;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 196;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RMOVE_ST", "FRIEND_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 197;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 198;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 199;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 200;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 201;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 202;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 203;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 204;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 205;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 206;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 207;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 208;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 209;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 210;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 211;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_13", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 212;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "IDLE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 213;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 214;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 215;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "RMOVE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 216;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 217;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 218;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 219;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 220;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 221;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 222;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 223;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 224;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 225;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 226;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 227;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_17", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 228;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "IDLE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 229;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 230;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 231;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 232;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RMOVE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 233;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 234;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 235;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 236;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 237;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 238;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 239;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 240;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 241;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 242;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 243;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 244;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 245;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 246;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 247;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_19", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 248;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "IDLE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 249;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 250;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 251;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 252;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RMOVE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 253;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 254;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 255;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 256;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 257;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RUSH_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 258;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 259;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 260;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 261;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 262;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 263;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 264;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 265;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 266;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 267;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 268;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_20", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 269;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "IDLE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 270;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 271;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 272;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 273;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RMOVE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 274;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 275;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 276;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 277;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 278;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RUSH_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 279;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 280;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RUSH_ST", "CHARACTER_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 281;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 282;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 283;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 284;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 285;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 286;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 287;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 288;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 289;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 290;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_21", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 291;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "IDLE_ST", "MYOWNER_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 292;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "RMOVE_ST") ) return 293;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 294;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "RMOVE_ST", "MYOWNER_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 295;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 296;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 297;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 298;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 299;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 300;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 301;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 302;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 303;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 304;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 305;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 306;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_24", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 307;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_25", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "FOLLOW_ST") ) return 308;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_25", "FOLLOW_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 309;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "IDLE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 310;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 311;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "IDLE_ST", "WAIT_END_IN", "MOVE_RANDOM_START_OUT", "RMOVE_ST") ) return 312;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 313;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RMOVE_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 314;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RMOVE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 315;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RMOVE_ST", "MOVE_RANDOM_END_IN", "WAIT_START_OUT", "IDLE_ST") ) return 316;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RMOVE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 317;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 318;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RUSH_ST", "MAGIC_LOCKON_IN", "EXPEL_OUT", "RUSH_ST") ) return 319;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 320;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RUSH_ST", "CHARACTER_INATTACKSIGHT_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 321;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RUSH_ST", "DESTINATION_ARRIVED_IN", "SEARCH_OUT", "SEARCH_ST") ) return 322;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "RUSH_ST", "ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 323;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "SEARCH_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 324;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "SEARCH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 325;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "SEARCH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 326;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 327;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 328;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 329;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "BERSERK_ST", "MILLI_ATTACKED_IN", "CHANGE_ENEMY_OUT", "SEARCH_ST") ) return 330;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_26", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 331;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "IDLE_ST", "ATTACKED_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 332;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "IDLE_ST", "CHARACTER_ATTACKSIGHT_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 333;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "NONE_OUT", "IDLE_ST") ) return 334;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_RANDOM_OUT", "BERSERK_ST") ) return 335;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 336;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_27", "DEAD_ST", "DEADSTATE_TIMEOUT_IN", "TRY_REVIVAL_OUT", "IDLE_ST") ) return 337;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "FOLLOW_ST") ) return 338;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "IDLE_ST", "MYOWNER_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 339;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 340;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 341;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "RUSH_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 342;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 343;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 344;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 345;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_01", "FOLLOW_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 346;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "FOLLOW_ST") ) return 347;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "IDLE_ST", "MYOWNER_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 348;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "IDLE_ST", "ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 349;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 350;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "RUSH_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 351;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "BERSERK_ST", "ENEMY_OUTSIGHT_IN", "WAIT_START_OUT", "IDLE_ST") ) return 352;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 353;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 354;
	if( !this->CFSMMgr::SetDefined("MERCENARY_TYPE_02", "FOLLOW_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 355;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "IDLE_ST", "NONE_IN", "NONE_OUT", "IDLE_ST") ) return 356;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "RMOVE_ST", "NONE_IN", "NONE_OUT", "RMOVE_ST") ) return 357;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "RUSH_ST", "NONE_IN", "NONE_OUT", "RUSH_ST") ) return 358;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "ABNORMAL_ST", "NONE_IN", "NONE_OUT", "ABNORMAL_ST") ) return 359;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "SEARCH_ST", "NONE_IN", "NONE_OUT", "SEARCH_ST") ) return 360;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "BERSERK_ST", "NONE_IN", "NONE_OUT", "BERSERK_ST") ) return 361;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "FOLLOW_ST", "NONE_IN", "NONE_OUT", "FOLLOW_ST") ) return 362;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "DEAD_ST", "NONE_IN", "NONE_OUT", "DEAD_ST") ) return 363;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "ANGRY_ST", "NONE_IN", "NONE_OUT", "ANGRY_ST") ) return 364;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "FOLLOW_SEARCH_ST", "NONE_IN", "NONE_OUT", "FOLLOW_SEARCH_ST") ) return 365;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "FIGHT_ST", "NONE_IN", "NONE_OUT", "FIGHT_ST") ) return 366;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "MOVEENEMY_ST", "NONE_IN", "NONE_OUT", "MOVEENEMY_ST") ) return 367;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "MOVEHELP_ST", "NONE_IN", "NONE_OUT", "MOVEHELP_ST") ) return 368;
	if( !this->CFSMMgr::SetDefined("LUA_AI_TYPE", "MOVEITEM_ST", "NONE_IN", "NONE_OUT", "MOVEITEM_ST") ) return 369;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "IDLE_ST", "MYOWNER_ATTACKED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 370;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "IDLE_ST", "ATTACKED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 371;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "IDLE_ST", "CHARACTER_ATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 372;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "NONE_OUT", "IDLE_ST") ) return 373;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 374;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_28", "ABNORMAL_ST", "CHANGE_NORMALST_IN", "CHANGE_NORMALST_OUT", "IDLE_ST") ) return 375;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "IDLE_ST", "NONE_IN", "NONE_OUT", "IDLE_ST") ) return 376;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "RMOVE_ST", "NONE_IN", "NONE_OUT", "RMOVE_ST") ) return 377;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "RUSH_ST", "NONE_IN", "NONE_OUT", "RUSH_ST") ) return 378;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "ABNORMAL_ST", "NONE_IN", "NONE_OUT", "ABNORMAL_ST") ) return 379;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "SEARCH_ST", "NONE_IN", "NONE_OUT", "SEARCH_ST") ) return 380;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "BERSERK_ST", "NONE_IN", "NONE_OUT", "BERSERK_ST") ) return 381;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "FOLLOW_ST", "NONE_IN", "NONE_OUT", "FOLLOW_ST") ) return 382;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "DEAD_ST", "NONE_IN", "NONE_OUT", "DEAD_ST") ) return 383;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "ANGRY_ST", "NONE_IN", "NONE_OUT", "ANGRY_ST") ) return 384;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "FOLLOW_SEARCH_ST", "NONE_IN", "NONE_OUT", "FOLLOW_SEARCH_ST") ) return 385;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "FIGHT_ST", "NONE_IN", "NONE_OUT", "FIGHT_ST") ) return 386;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "MOVEENEMY_ST", "NONE_IN", "NONE_OUT", "MOVEENEMY_ST") ) return 387;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "MOVEHELP_ST", "NONE_IN", "NONE_OUT", "MOVEHELP_ST") ) return 388;
	if( !this->CFSMMgr::SetDefined("LUA_ELEMENTAL_TYPE", "MOVEITEM_ST", "NONE_IN", "NONE_OUT", "MOVEITEM_ST") ) return 389;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_WAIT", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "FOLLOW_ST") ) return 390;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_WAIT", "FOLLOW_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 391;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_PASSIVE", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "FOLLOW_ST") ) return 392;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_PASSIVE", "FOLLOW_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 393;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_DEFENSIVE", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "FOLLOW_ST") ) return 394;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_DEFENSIVE", "FOLLOW_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 395;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_OFFENSIVE", "IDLE_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "FOLLOW_ST") ) return 396;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_OFFENSIVE", "IDLE_ST", "MYOWNER_ATTACKED_IN", "EXPEL_OUT", "RUSH_ST") ) return 397;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_OFFENSIVE", "IDLE_ST", "CHARACTER_INSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 398;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_OFFENSIVE", "FOLLOW_ST", "DESTINATION_ARRIVED_IN", "NONE_OUT", "IDLE_ST") ) return 399;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_OFFENSIVE", "RUSH_ST", "MYOWNER_OUTSIGNT_IN", "NONE_OUT", "IDLE_ST") ) return 400;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_OFFENSIVE", "RUSH_ST", "ENEMY_INATTACKSIGHT_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 401;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_OFFENSIVE", "RUSH_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 402;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_OFFENSIVE", "BERSERK_ST", "MYOWNER_OUTSIGNT_IN", "MOVETO_MYOWNER_OUT", "FOLLOW_ST") ) return 403;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_OFFENSIVE", "BERSERK_ST", "ENERGY_RECHARGED_IN", "REVENGE_ENEMY_OUT", "BERSERK_ST") ) return 404;
	if( !this->CFSMMgr::SetDefined("ELEMENTAL_TYPE_OFFENSIVE", "BERSERK_ST", "ENEMY_OUTATTACKSIGHT_IN", "EXPEL_OUT", "RUSH_ST") ) return 405;
	if( !this->CFSMMgr::SetDefined("MOB_TOMB_NPC", "IDLE_ST", "CLICK_IN", "CLICK_EVENT_MOB_TOMB_OUT", "IDLE_ST") ) return 406;
	if( !this->CFSMMgr::SetDefined("MONSTER_TYPE_29", "IDLE_ST", "NONE_IN", "NONE_OUT", "IDLE_ST") ) return 407;

	return 0;
}


bool CFSMMgr::SetDefined(const char* npcTypeID, const char* fsmStateID, const char* inputType, const char* outputType, const char* outputState)
{
	if( npcTypeID == 0 || fsmStateID == 0 || inputType == 0 || outputType == 0 || outputState == 0 )
		return false;

	unsigned long nKeyWord = this->CFSMMgr::GetKeyWord(npcTypeID);
	if( nKeyWord == -1 )
		return false;

	unsigned long sKeyWord = this->CFSMMgr::GetKeyWord(fsmStateID);
	if( sKeyWord == -1 )
		return false;

	unsigned long iKeyWord = this->CFSMMgr::GetKeyWord(inputType);
	if( iKeyWord == -1 )
		return false;

	unsigned long otKeyWord = this->CFSMMgr::GetKeyWord(outputType);
	if( otKeyWord == -1 )
		return false;

	unsigned long osKeyWord = this->CFSMMgr::GetKeyWord(outputState);
	if( osKeyWord == -1 )
		return false;

	SCRIPT_INPUT scriptInput;
	scriptInput.npcTypeID = nKeyWord;
	scriptInput.fsmStateID = sKeyWord;
	scriptInput.inputType = iKeyWord;
	scriptInput.outputType = otKeyWord;
	scriptInput.outputState = osKeyWord;
	this->CFSMMgr::AddFSM(&scriptInput);

	return true;
}
