#pragma once


class CInstantVar
{
public:
	enum enumVAR
	{
		PassivePreLV_AB_EUCHARISTICA              = 0,
		RK_MAKE_RAWRUNESTONEID                    = 1,
		SC_AUTOSHADOWSPELL_REQUEST_TIME           = 2,
		SC_AUTOSHADOWSPELL_LEVEL                  = 3,
		ITEMUSEBLOCK                              = 4,
		MOVEBLOCK                                 = 5,
		SKILLUSEBLOCK                             = 6,
		MELEEATKBLOCK                             = 7,
		SR_RAISINGDRAGON_MAX_NUM_SPIRITS          = 8,
		SC_MANHOLE_CNT                            = 9,
		JT_MANHOLE_DISABLE                        = 10,
		PassivePreLV_WL_RADIUS                    = 11,
		BODYSTATE_IMPRISON_SpellActorAID          = 12,
		RA_RESEARCHTRAP_PLUSATK                   = 13,
		SC_DIMENSIONDOOR_CNT                      = 14,
		SC_CHAOSPANIC_CNT                         = 15,
		SC_MAELSTROM_SKILL_AID                    = 16,
		SC_BLOODYLUST_SKILL_AID                   = 17,
		USED_TRAP_ITEMID                          = 18,
		PassivePreLV_WM_LESSON                    = 19,
	    //                                        = 20,
		HOMUN_LEVEL_STATWEIGHT_VALUE              = 21,
		JT_SEVERE_RAINSTORM_ATK_MAXCNT            = 22,
		JT_SEVERE_RAINSTORM_ATK_CNT               = 23,
		JT_SEVERE_RAINSTORM_ATK_PERCENT           = 24,
		WM_POEMOFNETHERWORLD_INSTALL_CNT          = 25,
		CHATBLOCK                                 = 26,
		GN_WALLOFTHORN_CNT                        = 27,
		GC_POISONSMOKE_CNT                        = 28,
		PassivePreLV_NC_MAINFRAME                 = 29,
		SO_XXXWALK_CNT                            = 30,
		SO_PSYCHIC_WAVE_FireTM                    = 31,
		SO_CLOUD_KILL_FireTM                      = 32,
		SO_CLOUD_KILL_InstalledSkillAID           = 33,
		PassivePreLV_WL_FREEZE_SP                 = 34,
		SC_MAELSTROM_Suction_SKGroupUniqueID      = 35,
		GN_BLOOD_SUCKER_CNT                       = 36,
		GN_WALLOFTHORN_INSTALL_ORIGIN_POS         = 37,
		GN_WALLOFTHORN_FIRE                       = 38,
		GN_DEMONIC_FIRE_MATKPERCENT_ADD           = 39,
		WZ_WATERBALL_IGNORE_WATER_CNT             = 40,
		GN_HELLS_PLANT_INSTALL_CNT                = 41,
		RA_ELECTRICSHOCKER_INSTALL_CNT            = 42,
		RA_MAGENTATRAP_INSTALL_CNT                = 43,
		RA_COBALTTRAP_INSTALL_CNT                 = 44,
		RA_MAIZETRAP_INSTALL_CNT                  = 45,
		RA_VERDURETRAP_INSTALL_CNT                = 46,
		RA_FIRINGTRAP_INSTALL_CNT                 = 47,
		RA_ICEBOUNDTRAP_INSTALL_CNT               = 48,
		SR_GENTLETOUCH_CHANGE_INC_ITEMATK_AMOUNT  = 49,
		SR_GENTLETOUCH_CHANGE_DEC_ITEMMDEF_AMOUNT = 50,
		GN_CHANGEMATERIAL_WAIT_CNT                = 51,
		GN_MIX_COOKING_SPELL_LEVEL                = 52,
		GN_MAKEBOMB_SPELL_LEVEL                   = 53,
		GN_S_PHARMACY_SPELL_LEVEL                 = 54,
		SO_VACUUM_EXTREME_FIRE_TM                 = 55,
		SO_VACUUM_EXTREME_TARGET_MOVED            = 56,
		GN_THORNS_TRAP_INSTALL_CNT                = 57,
		GN_DEMONIC_FIRE_LIFETIME_ADD_VALUE        = 58,
		WL_WHITEIMPRISON_SPELL_LEVEL              = 59,
		WL_WHITEIMPRISON_SPELL_SPELL_ACTORAID     = 60,
		SO_EL_ANALYSIS_DISASSEMBLY_WAIT_CNT       = 61,
		SO_EL_ANALYSIS_COMBINATION_WAIT_CNT       = 62,
		MH_POISON_MIST_CNT                        = 63,
		NPC_SPECIAL_ASPD                          = 64,
		BA_DISSONANCE_CNT                         = 65,
		MH_STEINWAND_CNT                          = 66,
		MH_STEINWAND_IGNORE_DAMAGE_CNT            = 67,
		MH_LAVA_SLIDE_CNT                         = 68,
		MH_VOLCANIC_ASH_CNT                       = 69,
		ONE_KILL_MONSTER                          = 70,
		MACRO_RECV_INVALID_PACKET_CNT             = 71,
		STORE_MAX_NUM                             = 72,
		REFLECTDAMGE_COUNT                        = 73,
		USED_SKILL_LEVEL_GC_POISONINGWEAPON       = 74,
		USED_SKILL_LEVEL_SC_SHADOWFORM            = 75,
		KO_ZANZOU_SUMMON_CNT                      = 76,
		SIMPLE_CASHITEM_SEND                      = 77,
		OPEN_MERGE_ITEM                           = 78,
		ZC_SELECTCART_IDENTITY                    = 79,
		USED_SKILL_LEVEL_MC_CARTDECORATE          = 80,
		INSTALL_AID__SC_CHAOSPANIC                = 81,
		GN_WALLOFTHORN_TOUCHCNT                   = 82,
		NPC_HELLBURNING_FireTM                    = 83,
		MAGMA_ERUPTION_FIRE_TIME                  = 84,
		MAGMA_INSTALL_CNT                         = 85,
		APPLY_BURNT_CNT                           = 86,
		FULL_THROTTLE_STR_AMOUNT                  = 87,
		FULL_THROTTLE_INT_AMOUNT                  = 88,
		FULL_THROTTLE_DEX_AMOUNT                  = 89,
		FULL_THROTTLE_AGI_AMOUNT                  = 90,
		FULL_THROTTLE_LUK_AMOUNT                  = 91,
		FULL_THROTTLE_VIT_AMOUNT                  = 92,
		GLITTERING_GREED_INSTALL_CNT              = 93,
		B_TRAP_INSTALL_CNT                        = 94,
		RL_H_MINE_SK_LEVEL                        = 95,
		RL_P_ALTER_INC_ITEMATK_AMOUNT             = 96,
		RL_C_MARKER_SET_CNT                       = 97,
		USE_SKILL_ITEM_IDENTIFY                   = 98,
		ACTIVATE_KO_YAMIKUMO                      = 99,
		DESTROY_SKILL_OBJ_BY_RL_FIRERAIN          = 100,
		NPC_TRADE_GROUP_NUM                       = 101,
	};

private:
	/* this+0 */ //const CInstantVar::`vftable';
	typedef std::map<enumVAR,int> INSTANTVAR_CONTAINER;
	/* this+4 */ INSTANTVAR_CONTAINER m_Variables;

public:
	void Init()
	{
		m_Variables.clear();
	}

	void operator()(const enumVAR in_Var, const int in_Data)
	{
		m_Variables[in_Var] = in_Data;
	}

	int operator()(const enumVAR in_Var) const
	{
		INSTANTVAR_CONTAINER::const_iterator iter = m_Variables.find(in_Var);
		return ( iter != m_Variables.end() ) ? iter->second : 0;
	}

public:
	CInstantVar()
	{
	}

	virtual ~CInstantVar()
	{
	}
};
