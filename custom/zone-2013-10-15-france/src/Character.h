#pragma once
#include "FactorVAR.h"
#include "InstantVar.h"
#include "MSGPar.h"
#include "NeighborCache.h"
#include "shared/Client.h"
class CMapRes; //TODO
class CITZMsg;


/// see CCharacter::GetParameterValue()
enum enumCHARACTERVAR
{
	VAR_SPEED                            = 0,
	VAR_EXP                              = 1,
	VAR_JOBEXP                           = 2,
	VAR_VIRTUE                           = 3,
	VAR_HONOR                            = 4,
	VAR_HP                               = 5,
	VAR_MAXHP                            = 6,
	VAR_SP                               = 7,
	VAR_MAXSP                            = 8,
	VAR_POINT                            = 9,
	VAR_HAIRCOLOR                        = 10,
	VAR_CLEVEL                           = 11,
	VAR_SPPOINT                          = 12,
	VAR_STR                              = 13,
	VAR_AGI                              = 14,
	VAR_VIT                              = 15,
	VAR_INT                              = 16,
	VAR_DEX                              = 17,
	VAR_LUK                              = 18,
	VAR_JOB                              = 19,
	VAR_MONEY                            = 20,
	VAR_SEX                              = 21,
	VAR_MAXEXP                           = 22,
	VAR_MAXJOBEXP                        = 23,
	VAR_WEIGHT                           = 24,
	VAR_MAXWEIGHT                        = 25,
	VAR_POISON                           = 26,
	VAR_STONE                            = 27,
	VAR_CURSE                            = 28,
	VAR_FREEZING                         = 29,
	VAR_SILENCE                          = 30,
	VAR_CONFUSION                        = 31,
	VAR_STANDARD_STR                     = 32,
	VAR_STANDARD_AGI                     = 33,
	VAR_STANDARD_VIT                     = 34,
	VAR_STANDARD_INT                     = 35,
	VAR_STANDARD_DEX                     = 36,
	VAR_STANDARD_LUK                     = 37,
	VAR_ATTACKMT                         = 38,
	VAR_ATTACKEDMT                       = 39,
	VAR_NV_BASIC                         = 40,
	VAR_ATTPOWER                         = 41,
	VAR_REFININGPOWER                    = 42,
	VAR_MAX_MATTPOWER                    = 43,
	VAR_MIN_MATTPOWER                    = 44,
	VAR_ITEMDEFPOWER                     = 45,
	VAR_PLUSDEFPOWER                     = 46,
	VAR_MDEFPOWER                        = 47,
	VAR_PLUSMDEFPOWER                    = 48,
	VAR_HITSUCCESSVALUE                  = 49,
	VAR_AVOIDSUCCESSVALUE                = 50,
	VAR_PLUSAVOIDSUCCESSVALUE            = 51,
	VAR_CRITICALSUCCESSVALUE             = 52,
	VAR_ASPD                             = 53,
	VAR_PLUSASPD                         = 54,
	VAR_JOBLEVEL                         = 55,
	VAR_ACCESSORY2                       = 56,
	VAR_ACCESSORY3                       = 57,
	VAR_HEADPALETTE                      = 58,
	VAR_BODYPALETTE                      = 59,
	VAR_PKHONOR                          = 60,
	VAR_CURXPOS                          = 61,
	VAR_CURYPOS                          = 62,
	VAR_CURDIR                           = 63,
	VAR_CHARACTERID                      = 64,
	VAR_ACCOUNTID                        = 65,
	VAR_MAPID                            = 66,
	VAR_MAPNAME                          = 67,
	VAR_ACCOUNTNAME                      = 68,
	VAR_CHARACTERNAME                    = 69,
	VAR_ITEM_COUNT                       = 70,
	VAR_ITEM_ITID                        = 71,
	VAR_ITEM_SLOT1                       = 72,
	VAR_ITEM_SLOT2                       = 73,
	VAR_ITEM_SLOT3                       = 74,
	VAR_ITEM_SLOT4                       = 75,
	VAR_HEAD                             = 76,
	VAR_WEAPON                           = 77,
	VAR_ACCESSORY                        = 78,
	VAR_STATE                            = 79,
	VAR_MOVEREQTIME                      = 80,
	VAR_GROUPID                          = 81,
	VAR_ATTPOWERPLUSTIME                 = 82,
	VAR_ATTPOWERPLUSPERCENT              = 83,
	VAR_DEFPOWERPLUSTIME                 = 84,
	VAR_DEFPOWERPLUSPERCENT              = 85,
	VAR_DAMAGENOMOTIONTIME               = 86,
	VAR_BODYSTATE                        = 87,
	VAR_HEALTHSTATE                      = 88,
	VAR_RESETHEALTHSTATE                 = 89,
	VAR_CURRENTSTATE                     = 90,
	VAR_RESETEFFECTIVE                   = 91,
	VAR_GETEFFECTIVE                     = 92,
	VAR_EFFECTSTATE                      = 93,
	VAR_SIGHTABILITYEXPIREDTIME          = 94,
	VAR_SIGHTRANGE                       = 95,
	VAR_SIGHTPLUSATTPOWER                = 96,
	VAR_STREFFECTIVETIME                 = 97,
	VAR_AGIEFFECTIVETIME                 = 98,
	VAR_VITEFFECTIVETIME                 = 99,
	VAR_INTEFFECTIVETIME                 = 100,
	VAR_DEXEFFECTIVETIME                 = 101,
	VAR_LUKEFFECTIVETIME                 = 102,
	VAR_STRAMOUNT                        = 103,
	VAR_AGIAMOUNT                        = 104,
	VAR_VITAMOUNT                        = 105,
	VAR_INTAMOUNT                        = 106,
	VAR_DEXAMOUNT                        = 107,
	VAR_LUKAMOUNT                        = 108,
	VAR_MAXHPAMOUNT                      = 109,
	VAR_MAXSPAMOUNT                      = 110,
	VAR_MAXHPPERCENT                     = 111,
	VAR_MAXSPPERCENT                     = 112,
	VAR_HPACCELERATION                   = 113,
	VAR_SPACCELERATION                   = 114,
	VAR_SPEEDAMOUNT                      = 115,
	VAR_SPEEDDELTA                       = 116,
	VAR_SPEEDDELTA2                      = 117,
	VAR_PLUSATTRANGE                     = 118,
	VAR_DISCOUNTPERCENT                  = 119,
	VAR_AVOIDABLESUCCESSPERCENT          = 120,
	VAR_STATUSDEFPOWER                   = 121,
	VAR_PLUSDEFPOWERINACOLYTE            = 122,
	VAR_MAGICITEMDEFPOWER                = 123,
	VAR_MAGICSTATUSDEFPOWER              = 124,
	VAR_CLASS                            = 125,
	VAR_PLUSATTACKPOWEROFITEM            = 126,
	VAR_PLUSDEFPOWEROFITEM               = 127,
	VAR_PLUSMDEFPOWEROFITEM              = 128,
	VAR_PLUSARROWPOWEROFITEM             = 129,
	VAR_PLUSATTREFININGPOWEROFITEM       = 130,
	VAR_PLUSDEFREFININGPOWEROFITEM       = 131,
	VAR_IDENTIFYNUMBER                   = 132,
	VAR_ISDAMAGED                        = 133,
	VAR_ISIDENTIFIED                     = 134,
	VAR_REFININGLEVEL                    = 135,
	VAR_WEARSTATE                        = 136,
	VAR_ISLUCKY                          = 137,
	VAR_ATTACKPROPERTY                   = 138,
	VAR_STORMGUSTCNT                     = 139,
	VAR_MAGICATKPERCENT                  = 140,
	VAR_MYMOBCOUNT                       = 141,
	VAR_ISCARTON                         = 142,
	VAR_GDID                             = 143,
	VAR_NPCXSIZE                         = 144,
	VAR_NPCYSIZE                         = 145,
	VAR_RACE                             = 146,
	VAR_SCALE                            = 147,
	VAR_PROPERTY                         = 148,
	VAR_PLUSATTACKPOWEROFITEM_RHAND      = 149,
	VAR_PLUSATTACKPOWEROFITEM_LHAND      = 150,
	VAR_PLUSATTREFININGPOWEROFITEM_RHAND = 151,
	VAR_PLUSATTREFININGPOWEROFITEM_LHAND = 152,
	VAR_TOLERACE                         = 153,
	VAR_ARMORPROPERTY                    = 154,
	VAR_ISMAGICIMMUNE                    = 155,
	VAR_ISFALCON                         = 156,
	VAR_ISRIDING                         = 157,
	VAR_MODIFIED                         = 158,
	VAR_FULLNESS                         = 159,
	VAR_RELATIONSHIP                     = 160,
	VAR_ACCESSARY                        = 161,
	VAR_SIZETYPE                         = 162,
	VAR_SHOES                            = 163,
	VAR_STATUSATTACKPOWER                = 164,
	VAR_BASICAVOIDANCE                   = 165,
	VAR_BASICHIT                         = 166,
	VAR_PLUSASPDPERCENT                  = 167,
	VAR_CPARTY                           = 168,
	VAR_ISMARRIED                        = 169,
	VAR_ISGUILD                          = 170,
	VAR_ISFALCONON                       = 171,
	VAR_ISPECOON                         = 172,
	VAR_ISPARTYMASTER                    = 173,
	VAR_ISGUILDMASTER                    = 174,
	VAR_BODYSTATENORMAL                  = 175,
	VAR_HEALTHSTATENORMAL                = 176,
	VAR_STUN                             = 177,
	VAR_SLEEP                            = 178,
	VAR_UNDEAD                           = 179,
	VAR_BLIND                            = 180,
	VAR_BLOODING                         = 181,
	VAR_BSPOINT                          = 182,
	VAR_ACPOINT                          = 183,
	VAR_BSRANK                           = 184,
	VAR_ACRANK                           = 185,
	VAR_CHANGESPEED                      = 186,
	VAR_CHANGESPEEDTIME                  = 187,
	VAR_MAGICATKPOWER                    = 188,
	VAR_MER_KILLCOUNT                    = 189,
	VAR_MER_FAITH                        = 190,
	VAR_MDEFPERCENT                      = 191,
	VAR_CRITICAL_DEF                     = 192,
	VAR_ITEMPOWER                        = 193,
	VAR_MAGICDAMAGEREDUCE                = 194,
	VAR_STATUSMAGICPOWER                 = 195,
	VAR_PLUSMAGICPOWEROFITEM             = 196,
	VAR_ITEMMAGICPOWER                   = 197,
	VAR_NAME                             = 198,
	VAR_FSMSTATE                         = 199,
	VAR_ATTMPOWER                        = 200,
	VAR_CARTWEIGHT                       = 201,
	VAR_HP_SELF                          = 202,
	VAR_SP_SELF                          = 203,
	VAR_COSTUME_BODY                     = 204,
	VAR_RESET_COSTUMES                   = 205,
	VAR_ROBE                             = 206,
};


/// see CCharacter::GetScale()
enum enumCHARSCALE
{
	CHAR_SCALE_SMALL  = 0,
	CHAR_SCALE_MEDIUM = 1,
	CHAR_SCALE_LARGE  = 2,
	CHAR_SCALE_LAST   = 3,
};


struct COMMAND_QUEUE
{
	enum
	{
		ATK_USESKILL = 1,
		ATK_SPELL    = 2,
	};

	COMMAND_QUEUE()
	{
		par1 = 0;
		par2 = 0;
		par3 = 0;
		par4 = 0;
		par5 = 0;
		par6 = 0;
		par7 = 0;
	}

	void SetAtkUseSkill()
	{
		this->par3 |= ATK_USESKILL;
	}

	void SetAtkSpell(unsigned short skillPattern)
	{
		if( skillPattern == 2 )
			this->par3 |= ATK_SPELL;
	}

	/* this+ 0 */ unsigned long commandID;
	/* this+ 4 */ unsigned long executionTime;
	/* this+ 8 */ unsigned long sender;
	/* this+12 */ unsigned long par1;
	/* this+16 */ unsigned long par2;
	/* this+20 */ unsigned long par3;
	/* this+24 */ unsigned long par4;
	/* this+28 */ unsigned long par5;
	/* this+32 */ unsigned long par6;
	/* this+36 */ MSGpar::CVar par7;
};


class CCharacter : public CClient
{
public:
//	int GetNeighborPlayerNum();
	virtual void RecycleInit();

public:
	/* this+  0 */ //CClient baseclass_0;
	/* this+ 40 */ FactorVAR::BOOLvar mfvarb_RNG_Physics_ATKED_Cancel;
	/* this+ 64 */ FactorVAR::BOOLvar mfvarb_Skill_ATKED_Cancel;
	/* this+ 88 */ FactorVAR::MAXvar mfvarm_Melee_Physics_ATKED_Cancel_Percent;
	/* this+112 */ FactorVAR::MAXvar mfvarm_Magic_ATKED_Cancel_Percent;
	/* this+136 */ FactorVAR::MAXvar m_fvarm_Item_DEF_INC_Percent;
	/* this+160 */ FactorVAR::MAXvar m_fvarm_Item_DEF_DEC_Percent;
	/* this+184 */ FactorVAR::SUMvar m_fvars_Item_DEF_INC_Amount;
	/* this+208 */ FactorVAR::MAXvar m_fvarm_Status_DEF_INC_Percent;
	/* this+232 */ FactorVAR::SUMvar m_fvars_Status_DEF_INC_Amount;
	/* this+256 */ FactorVAR::BOOLvar m_fvarb_HEALTH_BLOODING_Cancel;
	/* this+280 */ FactorVAR::BOOLvar m_fvarb_BODYSTATE_STONECURSE_Cancel;
	/* this+304 */ FactorVAR::MAXvar m_fvarm_Move_Speed_DEC_Percent;
	/* this+328 */ FactorVAR::INDvar m_fvarind_Appoint_Skill_MATK_Percent;
	/* this+348 */ FactorVAR::INDHISTORYvar m_fvarindhistory_Appoint_Skill_Change_Property;
	/* this+368 */ FactorVAR::INDMAXHISTORYvar m_fvarindmaxhistory_UseSkill_ConsumItem_CancelPermil;
	/* this+388 */ FactorVAR::SUMHISTORYvar m_fvarshistory_ItemMATK_Amount;
	/* this+412 */ FactorVAR::INDSUMHISTORYvar m_fvarindsumhistory_GlobalPostDelay_Percent;
	/* this+432 */ FactorVAR::INDMINHISTORYvar m_fvarindminhistory_UseSkill_SPcost_Percent;
	/* this+452 */ FactorVAR::HISTORYvar m_fvarh_ATK_Property;
	/* this+476 */ FactorVAR::SUMHISTORYvar m_fvarshistory_INC_ItemATK_Percent;
	/* this+500 */ FactorVAR::SUMHISTORYvar m_fvarshistory_ItemATK_Amount;
	/* this+524 */ FactorVAR::SUMvar m_fvars_FinalDamage_DEC_Amount;
	/* this+548 */ FactorVAR::PassiveSKHPSPRecovery m_fvarPassiveSKHPRecovery;
	/* this+576 */ FactorVAR::PassiveSKHPSPRecovery m_fvarPassiveSKSPRecovery;
	/* this+604 */ FactorVAR::SUMHISTORYvar m_fvarshistory_NearPhysicsAtkPercent;
	/* this+628 */ FactorVAR::BOOLvar m_fvarb_WearTakeOff_Forbid;
	/* this+652 */ FactorVAR::BOOLvar m_fvarb_MoveBlock;
	/* this+676 */ FactorVAR::BOOLvar m_fvarb_SkillUseBlock;
	/* this+700 */ FactorVAR::BOOLvar m_fvarb_ItemUseBlock;
	/* this+724 */ FactorVAR::BOOLvar m_fvarb_MeleeAtkBlock;
private:
	/* this+748 */ std::vector<FactorVAR::Fvar*> m_fvars;
protected:
	/* this+764 */ CInstantVar m_InstantVar;

public:
//	int GetInstantVar(const CInstantVar::enumVAR );
//	void SetInstantVar(const CInstantVar::enumVAR , const int );
//	int SetInstantVarIncrement(const CInstantVar::enumVAR );
//	int SetInstantVarDecrease(const CInstantVar::enumVAR );

protected:
	struct CHARACTER_PROPERTY_INFO
	{
		/* this+ 0 */ int bodyState;
		/* this+ 4 */ int healthState;
		/* this+ 8 */ int armor;
		/* this+12 */ int currentProperty;
		/* this+16 */ int attack;
		/* this+20 */ int effectState;
	};

	/* this+784 */ CHARACTER_PROPERTY_INFO m_characterPInfo;

public:
	virtual int GetWeaponProperty(int position, BOOL isArrowProperty);
	virtual void AddErrorCnt(const char* in_SourceFileName, const int in_SourceLineNum, const DWORD in_Cnt, const DWORD in_TM);

public:
	CCharacter();
	virtual ~CCharacter();

public:
	virtual bool IsActor();
	virtual void Init();
	virtual int GetType();
	CMapRes* GetMapRes();
	virtual int IsItPossible(int property);
	virtual BOOL IsSiegeMode();
	virtual unsigned long GetAccountID() = 0;
	virtual int OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	virtual int GetParameterValue(unsigned short id, int& value);
	virtual int UpdateParameterValue(unsigned short id, int value);
	virtual void InsertCommand(COMMAND_QUEUE* command) = 0;
	virtual void CheckCommandQueue() = 0;
	virtual void DisableCommand(unsigned long commandID);
	virtual COMMAND_QUEUE* SearchCommand(unsigned long commandID);
	virtual BOOL IsMyArea(CCharacter* ch, int range) = 0;
	virtual unsigned long GetState();
	virtual int GetScale();
	virtual int IsTarget(CCharacter* ch, unsigned long flag) = 0;
	virtual BOOL IsDamageMotionPossible();
	virtual BOOL IsRightProperty(int property);
	virtual BOOL IsAvoidable(int race, int _class, int level);
	virtual BOOL IsInitingState();
	virtual BOOL IsLucky();
	virtual void OnShowEffect(int effect);
	virtual void OnShowEffect3(int effect, int numdata);
	virtual void OnShowScript(const char* In_Msg);
	void MultiCast(char* buf, int len);
	BOOL IsDirectPath(CCharacter* ch, BOOL isClose);
	virtual int GetEffectState();
	std::vector<CCharacter*>* GetSectionList();
	void SetSectionList(std::vector<CCharacter*>* sl);
	virtual void OnMsgFromItemServer(unsigned long AID, CITZMsg* reqMsg);
	virtual int GetEffective(int index, int enumVal);
	virtual int SetEffective(int index, int time, int val1, int val2, int val3, BOOL isSendClient);
	virtual void UpdateEffective(int index, int val, int enumVal);
	virtual void ResetEffective(int index, int val);
	virtual void GetModifiedHealAmount(int& healAmount);
	bool IsBattleFieldMode();
	virtual char GetCampID();
	virtual void SetCampID(char campID);
	bool IsTargetInBattleField(CCharacter* ch, unsigned long flag, BOOL& result);

protected:
	/* this+808 */ int m_type;
	/* this+812 */ std::list<COMMAND_QUEUE> m_commandQueue;
	/* this+824 */ CNeighborCache m_neighborCache;
	/* this+880 */ CMapRes* m_mapRes;
	/* this+884 */ std::vector<CCharacter*>* m_sectionList;
};
C_ASSERT( sizeof CCharacter == 888 );
