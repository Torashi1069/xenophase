#pragma once


enum inputList
{
	NONE_IN                                  = 0,
	WARP_SIGHT_IN                            = 1,
	TOUCHED_IN                               = 2,
	CLICK_IN                                 = 3,
	WAIT_END_IN                              = 4,
	MOVE_RANDOM_END_IN                       = 5,
	ATTACKED_IN                              = 6,
	MILLI_ATTACKED_IN                        = 7,
	ENEMY_OUTSIGHT_IN                        = 8,
	MYOWNER_OUTSIGNT_IN                      = 9,
	ENEMY_DEAD_IN                            = 10,
	ENEMY_INATTACKSIGHT_IN                   = 11,
	NEAREST_CHARACTER_IN                     = 12,
	ENEMY_OUTATTACKSIGHT_IN                  = 13,
	DESTINATION_ARRIVED_IN                   = 14,
	ENERGY_RECHARGED_IN                      = 15,
	DEADSTATE_TIMEOUT_IN                     = 16,
	ITEM_INSIGHT_IN                          = 17,
	ARRIVEDAT_ITEM_IN                        = 18,
	TARGET_ITEM_DISAPPEAR_IN                 = 19,
	CHARACTER_INSIGHT_IN                     = 20,
	FRIEND_ATTACKED_IN                       = 21,
	ENEMY_FAR_INATTACKSIGHT_IN               = 22,
	CHANGE_NORMALST_IN                       = 23,
	CHARACTER_ATTACKSIGHT_IN                 = 24,
	G_CHARACTER_ATTACKSIGHT_IN               = 25,
	ARENASTART_IN                            = 26,
	MYOWNER_ATTACKED_IN                      = 27,
	LOWERLEVEL_INSIGHT_IN                    = 28,
	MAGIC_LOCKON_IN                          = 29,
	CHARACTER_INATTACKSIGHT_IN               = 30,
	G_CHARACTER_INSIGHT_IN                   = 31,
	TOUCHEDNPC_IN                            = 32,
	TOUCHED2_IN                              = 33,
	MOVE_START_IN                            = 34,
	MOVE_END_POS_IN                          = 35,
	ATTACKED_MOTION_FINISHED_IN              = 36,
	MILLI_ATTACKED_MOTION_FINISHED_IN        = 37,
	MULTIPLE_ATTACKED_IN                     = 38,
	BODYSTATE_CHANGE_IN                      = 39,
	SPEED_CHANGE_IN                          = 40,
	PKMODE_OFF_IN                            = 41,
	HEALTHSTATE_CHANGE_IN                    = 42,
	HPPLUS_IN                                = 43,
	SPPLUS_IN                                = 44,
	USE_SKILL_IN                             = 45,
	USE_GROUNDSKILL_IN                       = 46,
	SPLASH_ATTACK_IN                         = 47,
	TELEPORT_IN                              = 48,
	KNUCKBACKED_IN                           = 49,
	ASYNC_DATABASE_WORK                      = 50,
	USE_AUTOSPELL_IN                         = 51,
	USE_AUTOSPELL_GROUND_IN                  = 52,
	REMEMBER_SKILL_USEINFO                   = 53,
	REQUEST_SIT_IN                           = 54,
	TRAP_TOUCHED_IN                          = 55,
	USE_EFST_IN                              = 56,
	IMPLICIT_ATTACKED_HP_IN                  = 57,
	IMPLICIT_ATTACKED_SP_IN                  = 58,
	IMPLICIT_SPLASH_ATTACK_HP_IN             = 59,
	IMPLICIT_SPLASH_ATTACK_SP_IN             = 60,
	USE_OB_OBOROGENSOU_TRANSITION_ATK        = 61,
	FIXED_MOB_TYPE__CHARACTER_ATTACKSIGHT_IN = 62,
};


enum outputList
{
	NONE_OUT                 = 0,
	TRADE_START_OUT          = 1,
	CALL_CLICKEVENT_OUT      = 2,
	CALL_TOUCHEVENT_OUT      = 3,
	MOVE_RANDOM_START_OUT    = 4,
	WAIT_START_OUT           = 5,
	EXPEL_OUT                = 6,
	SEARCH_OUT               = 7,
	ATTACK_ENEMY_OUT         = 8,
	MOVETO_ENEMY_OUT         = 9,
	MOVETO_FRIEND_OUT        = 10,
	REVENGE_ENEMY_OUT        = 11,
	TRY_REVIVAL_OUT          = 12,
	MOVETO_ITEM_OUT          = 13,
	PICKUP_ITEM_OUT          = 14,
	STOP_MOVE_OUT            = 15,
	CHANGE_ENEMY_OUT         = 16,
	CHANGE_NORMALST_OUT      = 17,
	CALL_ARENASTART_OUT      = 18,
	MOVETO_MYOWNER_OUT       = 19,
	REVENGE_RANDOM_OUT       = 20,
	CALL_TOUCHNPCEVENT_OUT   = 21,
	CALL_TOUCHEVENT2_OUT     = 22,
	MOVE_START_OUT           = 23,
	STOP_AND_CLICKEVENT_OUT  = 24,
	STOP_AND_TRADER_OUT      = 25,
	CLICK_EVENT_MOB_TOMB_OUT = 26,
};


enum stateList
{
	IDLE_ST          = 0,
	RMOVE_ST         = 1,
	FOLLOW_ST        = 2,
	ANGRY_ST         = 3,
	RUSH_ST          = 4,
	FOLLOW_SEARCH_ST = 5,
	SEARCH_ST        = 6,
	BERSERK_ST       = 7,
	FIGHT_ST         = 8,
	MOVEENEMY_ST     = 9,
	MOVEHELP_ST      = 10,
	DEAD_ST          = 11,
	MOVEITEM_ST      = 12,
	ABNORMAL_ST      = 13,
};


struct OUTPUT_DATA
{
	/* this+0 */ unsigned long outputType;
	/* this+4 */ unsigned long outputState;
};


class CFSMState
{
public:
	CFSMState();
	virtual ~CFSMState();

public:
	void AddTransition(unsigned long inputType, unsigned long outputType, unsigned long outputState);
	BOOL GetOutput(unsigned long inputType, unsigned long& outputType, unsigned long& outputState);
	void Init(unsigned long stateID);

private:
	void Destroy();

private:
	/* this+ 0 */ //const CFSMState::`vftable';
	/* this+ 4 */ int m_count;
	/* this+ 8 */ unsigned long m_transition[10];
	/* this+48 */ OUTPUT_DATA* m_table[64];
};
