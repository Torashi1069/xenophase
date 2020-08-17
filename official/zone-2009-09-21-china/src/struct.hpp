#pragma once
#include "ScriptLib/TokenData.h"
#include "ScriptLib/TokenInfo.h"
#include "MSGpar.hpp"
#include "enum.hpp"
#include "globals.hpp"
#include "std/list"
#include "std/map"
#include "std/string"
#include "std/vector"


struct PC_INDEX_DATA
{
  /* this+0x0 */ int index;
  /* this+0x4 */ unsigned long connectionTime;
};


struct COMMAND_QUEUE
{
	enum
	{
		ATK_USESKILL = 0x1,
		ATK_SPELL    = 0x2,
	};

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

	public: COMMAND_QUEUE::COMMAND_QUEUE(const COMMAND_QUEUE& __that)
	{
		this->commandID = __that.commandID;
		this->executionTime = __that.executionTime;
		this->sender = __that.sender;
		this->par1 = __that.par1;
		this->par2 = __that.par2;
		this->par3 = __that.par3;
		this->par4 = __that.par4;
		this->par5 = __that.par5;
		this->par6 = __that.par6;
		this->par7.m_Var.m_INT.value = __that.par7.m_Var.m_INT.value;
	}

	public: COMMAND_QUEUE::COMMAND_QUEUE(void)
	{
		this->par1 = 0;
		this->par2 = 0;
		this->par3 = 0;
		this->par4 = 0;
		this->par5 = 0;
		this->par6 = 0;
		this->par7.m_Var.m_INT.value = 0;
	}

	public: COMMAND_QUEUE::~COMMAND_QUEUE(void)
	{
	}

	public: void COMMAND_QUEUE::SetAtkUseSkill(void)
	{
		this->par3 |= ATK_USESKILL;
	}

	public: void COMMAND_QUEUE::SetAtkSpell(unsigned short skillPattern)
	{
		if( skillPattern == 2 )
			this->par3 |= ATK_SPELL;
	}
};


struct AmountValue
{
	/* this+0x0 */ unsigned long time;
	/* this+0x4 */ int resetAmount;

	public: AmountValue::AmountValue(unsigned long _time, int _resetAmount)
	{
		this->time = _time;
		this->resetAmount = _resetAmount;
	}
};


struct ClientCache
{
	/* this+0x0 */ int AID;
	/* this+0x4 */ int Index;
	/* this+0x8 */ unsigned long MoveLastTime;
	/* this+0xC */ unsigned long ConnectedTime;
};


struct EFFECTIVE_INFO
{
	/* this+ 0 */ DWORD time;
	/* this+ 4 */ int val[3];
	/* this+16 */ int isSendClient;
};


struct PLUSSTATUS_BYJOB
{
	/* this+0x0  */ int Str;
	/* this+0x4  */ int Int;
	/* this+0x8  */ int Dex;
	/* this+0xC  */ int Agi;
	/* this+0x10 */ int Luk;
	/* this+0x14 */ int Vit;
};

struct BATTLEFIELDINFO
{
	/* this+0x0 */ char campID;
	/* this+0x2 */ short xPos1;
	/* this+0x4 */ short yPos1;
	/* this+0x6 */ short xPos2;
	/* this+0x8 */ short yPos2;
};


struct EXCHANGEITEM_INFO
{
	/* this+0x0 */ unsigned long AID;
	/* this+0x4 */ int isPermited;
	/* this+0x8 */ int isConcluded;
};


struct ENEMY_INFO
{
	/* this+0x0 */ unsigned long AID;
	/* this+0x4 */ unsigned long attackinglastTime;
};


struct MSG_TYPE1_TWODWORD
{
	/* this+0 */ int data1;
	/* this+4 */ int data2;
};


struct MSG_TYPE2_THREEDWORD
{
	/* this+0 */ int data1;
	/* this+4 */ int data2;
	/* this+8 */ int data3;
};


struct MSG_TYPE3_FOURDWORD
{
	/* this+ 0 */ int data1;
	/* this+ 4 */ int data2;
	/* this+ 8 */ int data3;
	/* this+12 */ int data4;
};


struct MSG_TYPE4_FIVEDWORD
{
	/* this+ 0 */ int data1;
	/* this+ 4 */ int data2;
	/* this+ 8 */ int data3;
	/* this+12 */ int data4;
	/* this+16 */ int data5;
};


struct MSG_TYPE5_SIXDWORD
{
	/* this+ 0 */ int data1;
	/* this+ 4 */ int data2;
	/* this+ 8 */ int data3;
	/* this+12 */ int data4;
	/* this+16 */ int data5;
	/* this+20 */ int data6;
};


struct MSG_TYPE7_EIGHTWORD
{
	/* this+ 0 */ int data1;
	/* this+ 4 */ int data2;
	/* this+ 8 */ int data3;
	/* this+12 */ int data4;
	/* this+16 */ int data5;
	/* this+20 */ int data6;
	/* this+24 */ int data7;
	/* this+28 */ int data8;
};


struct PARTNER_INFO
{
	/* this+0x0 */ int bMarried;
	/* this+0x4 */ unsigned long partnerGID;
	/* this+0x8 */ char partnerName[0x18];
};


struct FAMILY_INFO
{
	/* this+0x0  */ int familyIndex;
	/* this+0x4  */ int bMarried;
	/* this+0x8  */ short expOption;
	/* this+0xC  */ unsigned long father;
	/* this+0x10 */ char fatherName[0x18];
	/* this+0x28 */ unsigned long mother;
	/* this+0x2C */ char motherName[0x18];
	/* this+0x44 */ unsigned long baby;
	/* this+0x48 */ char babyName[0x18];
};


struct PalmStrikeInfo
{
	/* this+0x0 */ unsigned long AID;
	/* this+0x4 */ int level;        
};


struct PCBANG_INFO
{
	/* this+0x0  */ int isPCBang;
	/* this+0x4  */ int PayType;
	/* this+0x8  */ int ConnectionArea;
	/* this+0xC  */ int ConnectionState;
	/* this+0x10 */ int EventNum;
	/* this+0x14 */ unsigned long ConnectionTime;
	/* this+0x18 */ float ExpFactor;
	/* this+0x1C */ float ExpFactor2;
	/* this+0x20 */ float DropFactor;
	/* this+0x24 */ int NotifyToClientCnt;
	/* this+0x28 */ int PremiumType;
	/* this+0x2C */ int PremiumType2;
};


struct PVPINFO
{
	/* this+0x0 */ int WinPoint;
	/* this+0x4 */ int LosePoint;
	/* this+0x8 */ int Point;
};


struct PKInfo
{
	/* this+0x0  */ int winPoint;
	/* this+0x4  */ int losePoint;
	/* this+0x8  */ char killName[0x18];
	/* this+0x20 */ char killedName[0x18];
	/* this+0x38 */ FILETIME expireTime;
	/* this+0x40 */ unsigned long noPointTime;
	/* this+0x44 */ unsigned long expireTimeCheck;
	/* this+0x48 */ unsigned long lastCheckTime;
	/* this+0x4C */ int isCrazyKiller;
	/* this+0x50 */ int isKingCrazyKiller;
};


struct _LOTTO_NUMBERS
{
	/* this+0x0 */ bool isLoadedFromDB;
	/* this+0x4 */ int numbers[6];

	public: void _LOTTO_NUMBERS::Init(void)
	{
		this->isLoadedFromDB = false;
		this->numbers[0] = 0;
		this->numbers[1] = 0;
		this->numbers[2] = 0;
		this->numbers[3] = 0;
		this->numbers[4] = 0;
		this->numbers[5] = 0;
	}
};


struct Request
{
	/* this+ 0 */ public: int par1;
	/* this+ 4 */ public: int par2;
	/* this+ 8 */ public: int par3;
	/* this+12 */ protected: enum eRequestType m_requestID;

	public: void Request::SetID(int ID)
	{
		this->m_requestID = (eRequestType)ID;
	}

	public: int Request::GetID(void)
	{
		return this->m_requestID;
	}
};


struct NpcTimeInfo
{
	/* this+0x0  */ unsigned long StrEffectiveTime;
	/* this+0x4  */ unsigned long AgiEffectiveTime;
	/* this+0x8  */ unsigned long VitEffectiveTime;
	/* this+0xC  */ unsigned long IntEffectiveTime;
	/* this+0x10 */ unsigned long DexEffectiveTime;
	/* this+0x14 */ unsigned long LukEffectiveTime;
	/* this+0x18 */ unsigned long HPHealVelocity;
	/* this+0x1C */ unsigned long HPLastHealTime;
	/* this+0x20 */ unsigned long SPLastHealTime;
	/* this+0x24 */ unsigned long DamageNoMotionTime;
	/* this+0x28 */ unsigned long SightRange;
	/* this+0x2C */ unsigned long SightplusAttackPower;
	/* this+0x30 */ unsigned long SpeedMount;
	/* this+0x34 */ int ChangeSpeed;
	/* this+0x38 */ int ChangeSpeedTime;
};


struct EQUIPSLOTINFO
{
	/* this+0x0 */ unsigned short info[0x4];
};


struct EATING_ITEM_INVENTORY
{
	/* this+0x0  */ unsigned short ITID;
	/* this+0x2  */ unsigned short count;
	/* this+0x4  */ bool IsIdentified;
	/* this+0x8  */ __int64 unique_identity_numberV2;
	/* this+0x10 */ long hire_expire_date;
	/* this+0x14 */ bool IsDamaged;
	/* this+0x15 */ unsigned char RefiningLevel;
	/* this+0x16 */ EQUIPSLOTINFO slot;
};


struct MYMOBDATA
{
	/* this+0x0 */ unsigned long AID;
};


struct AMOUNT_INFO
{
	/* this+0x0 */ unsigned long time;
	/* this+0x4 */ int amount;
};


struct NpcInfo
{
	/* this+0x0   */ int accountID;
	/* this+0x4   */ short job;
	/* this+0x6   */ short clevel;
	/* this+0x8   */ short head;
	/* this+0xA   */ short weapon;
	/* this+0xC   */ short accessory;
	/* this+0xE   */ short headerDir;
	/* this+0x10  */ int speed;
	/* this+0x14  */ int isValid;
	/* this+0x18  */ int mapID;
	/* this+0x1C  */ unsigned long reChargeTime;
	/* this+0x20  */ int exp;
	/* this+0x24  */ int jexp;
	/* this+0x28  */ short inc;
	/* this+0x2C  */ int hp;
	/* this+0x30  */ int maxhp;
	/* this+0x34  */ int sp;
	/* this+0x38  */ int maxsp;
	/* this+0x3C  */ int jobpoint;
	/* this+0x40  */ char accountName[0x18];
	/* this+0x58  */ char mapName[0x10];
	/* this+0x68  */ unsigned char sex;
	/* this+0x6C  */ int Str;
	/* this+0x70  */ int Agi;
	/* this+0x74  */ int Vit;
	/* this+0x78  */ int Int;
	/* this+0x7C  */ int Dex;
	/* this+0x80  */ int Luk;
	/* this+0x84  */ int xSize;
	/* this+0x88  */ int ySize;
	/* this+0x8C  */ int virtue;
	/* this+0x90  */ short attackRange;
	/* this+0x92  */ short srcAttackSight;
	/* this+0x94  */ short attackSight;
	/* this+0x96  */ short srcExpelSight;
	/* this+0x98  */ short expelSight;
	/* this+0x9A  */ short atk1;
	/* this+0x9C  */ short atk2;
	/* this+0x9E  */ short def;
	/* this+0xA0  */ short attackedMT;
	/* this+0xA2  */ short attackMT;
	/* this+0xA4  */ short StrAmount;
	/* this+0xA6  */ short AgiAmount;
	/* this+0xA8  */ short VitAmount;
	/* this+0xAA  */ short IntAmount;
	/* this+0xAC  */ short DexAmount;
	/* this+0xAE  */ short LukAmount;
	/* this+0xB0  */ int ATKPercent;
	/* this+0xB4  */ int DEFPercent;
	/* this+0xB8  */ int property;
	/* this+0xBC  */ int scale;
	/* this+0xC0  */ int _class;
	/* this+0xC4  */ enum eRaceType race;
	/* this+0xC8  */ int mdef;
	/* this+0xCC  */ int roomID;
	/* this+0xD0  */ int IsRegen;
	/* this+0xD4  */ int revivalXPos;
	/* this+0xD8  */ int revivalYPos;
	/* this+0xDC  */ int revivalXRange;
	/* this+0xE0  */ int revivalYRange;
	/* this+0xE4  */ int RegenMinTime;
	/* this+0xE8  */ int RegenMaxTime;
	/* this+0xEC  */ int RegenType;
	/* this+0xF0  */ int GuildID;
	/* this+0xF4  */ short originalJob;
	/* this+0xF8  */ int MATKPercent;
	/* this+0xFC  */ int MDEFPercent;
	/* this+0x100 */ char cashShopName[0x33];
	/* this+0x133 */ char campID;
};


struct ATTACK_PC
{
	/* this+0x0  */ unsigned long AID;
	/* this+0x4  */ int damage;
	/* this+0x8  */ int attdamage;
	/* this+0xC  */ unsigned long GRID;
	/* this+0x10 */ unsigned long GID;
};


struct EXTInfo
{
	/* this+0x0 */ short DEF;
};


struct HO_SKINFO
{
	/* this+0x0 */ int level;
	/* this+0x4 */ int type;
	/* this+0x8 */ int count;

	public: HO_SKINFO::HO_SKINFO(void)
	{
		this->level = 0;
		this->count = 0;
	}
};


struct PET_INFO
{
	/* this+ 0 */ int iKind;
	/* this+ 4 */ int iCapturePercent;
	/* this+ 8 */ int iRIWF; // Relationship Increase When Fed
	/* this+12 */ int iRDWF; // Relationship Decrease When Fed (overfeeding)
	/* this+16 */ int iRD;   // Relationship Decrease (every 20s of starvation)
	/* this+20 */ int iRDWD; // Relationship Decrease When Dead
	/* this+24 */ int iSIWF; // Satedness Increase When Fed
	/* this+28 */ int iSD;   // Satedness Decrease (every 60 seconds)
	/* this+32 */ bool bSpecialON;
	/* this+34 */ unsigned short nAccID;
	/* this+36 */ unsigned short nFoodID;
	/* this+38 */ unsigned short nTrap;
	/* this+40 */ unsigned short nPetEgg;
};


struct HOMUN_DBINFO
{
	/* this+0x0  */ int homunID;
	/* this+0x4  */ int exp;
	/* this+0x8  */ int bodystate;
	/* this+0xC  */ int healthstate;
	/* this+0x10 */ int effectstate;
	/* this+0x14 */ int fullness;
	/* this+0x18 */ int modified;
	/* this+0x1C */ float relation;
	/* this+0x20 */ short clevel;
	/* this+0x22 */ short job;
	/* this+0x24 */ short SKPoint;
	/* this+0x26 */ short hp;
	/* this+0x28 */ short maxhp;
	/* this+0x2A */ short sp;
	/* this+0x2C */ short maxsp;
	/* this+0x2E */ short accessory;
	/* this+0x30 */ short property;
	/* this+0x32 */ char name[0x18];
	/* this+0x4A */ unsigned char Str;
	/* this+0x4B */ unsigned char Agi;
	/* this+0x4C */ unsigned char Vit;
	/* this+0x4D */ unsigned char Int;
	/* this+0x4E */ unsigned char Dex;
	/* this+0x4F */ unsigned char Luk;
};


struct MERSOL_DBINFO
{
	/* this+0x0  */ short faith;
	/* this+0x2  */ short job;
	/* this+0x4  */ short hp;
	/* this+0x6  */ short sp;
	/* this+0x8  */ short lifeTM;
	/* this+0xC  */ int exp;
	/* this+0x10 */ int property;
	/* this+0x14 */ int bodyState;
	/* this+0x18 */ int healthState;
	/* this+0x1C */ int effectState;
	/* this+0x20 */ int summonCount[0x3];
};


struct HEAL_REGULARLY_INFO
{
	/* this+0x0 */ unsigned long nextUpdateTime;
	/* this+0x4 */ unsigned long term;
	/* this+0x8 */ short amount;

	public: void Set(unsigned long _term, short _amount)
	{
		this->nextUpdateTime = _term + timeGetTime();
		this->term = _term;
		this->amount = _amount;
	}
};


struct PropTM_Info
{
	/* this+0x0 */ mystd::map<unsigned short,short> propAmount;
	/* this+0xC */ unsigned long time;
};


struct SKILL_ACTIVE
{
	/* this+0x0 */ unsigned long itemID;
	/* this+0x4 */ unsigned long SKID;
	/* this+0x8 */ unsigned long percent;
	/* this+0xC */ unsigned long time;
};


struct SKILL_ACTIVE_OPTION
{
	/* this+0x0 */ unsigned long itemID;
	/* this+0x4 */ unsigned long SKID;
	/* this+0x8 */ unsigned long time;
};


struct _SKILL_ACTIVE_INFO
{
	/* this+0x0  */ mystd::map<unsigned long,mystd::list<SKILL_ACTIVE> > skillActiveList;
	/* this+0xC  */ mystd::list<SKILL_ACTIVE_OPTION> skillDeactiveList;
	/* this+0x18 */ unsigned long lastActivatedSkill;
	/* this+0x1C */ unsigned long lastDeactivatedSkill;
};


struct SKILL_HANDICAP
{
	/* this+0x0 */ short who;
	/* this+0x2 */ short state;
	/* this+0x4 */ int percent;
};


struct SKILL_AUTOSPELL
{
	/* this+0x0 */ unsigned long percent;
	/* this+0x4 */ unsigned long SKID;
	/* this+0x8 */ short who;
	/* this+0xA */ short level;
};


struct AUTOSPELL_MAGIC
{
	/* this+0x0 */ unsigned long SKID;
	/* this+0x4 */ short level;
	/* this+0x6 */ short who;
	/* this+0x8 */ int percent;
};


struct TARGET_ATTACKED_BUFF
{
	/* this+0x0 */ unsigned long percent;
	/* this+0x4 */ short who;
	/* this+0x6 */ unsigned short buffType;
	/* this+0x8 */ unsigned long time;
	/* this+0xC */ unsigned long value;
};


struct AUTO_ACT_ITEMSCRIPT
{
	/* this+0x0 */ unsigned long itemID;
	/* this+0x4 */ unsigned long time;
	/* this+0x8 */ unsigned char type;
};


struct AUTO_ACT_ITEMINFO
{
	/* this+0x0 */ unsigned long itemID;
	/* this+0x4 */ short percent;
	/* this+0x6 */ short time;
};


struct OptionInfo
{
	/* this+0x0  */ MSG_TYPE2_THREEDWORD receiveZENYInfo;
	/* this+0xC  */ int plusCRI_RANGE;
	/* this+0x10 */ bool receiveITMGROUP_ID[0x6];
	/* this+0x18 */ int reflectMagic;
	/* this+0x1C */ int damagePercent_Scale[0x2][0x3];
	/* this+0x34 */ int damagePercent_CRI[0x2];
	/* this+0x3C */ int healHP_Kill;
	/* this+0x40 */ int healSP_Kill;
	/* this+0x44 */ int healHP_Kill_Magic;
	/* this+0x48 */ int healSP_Kill_Magic;
	/* this+0x4C */ short plusStatusDEF;
	/* this+0x4E */ short healSkillPercent;
	/* this+0x50 */ short neverKnockBack;
	/* this+0x54 */ int reservedArmorProperty;
	/* this+0x58 */ int receiveItem_Equip;
};


struct SORTED_PCLIST
{
	/* this+0x0 */ unsigned long AID;
	/* this+0x4 */ unsigned int limitTime;
	/* this+0x8 */ unsigned int val;
};


struct PICKUPABLE_PCLIST
{
	/* this+0x0 */ unsigned long AID;
	/* this+0x4 */ unsigned short limitTime;
};


struct extraITMInfo
{
	/* this+0x0 */ unsigned short id;
	/* this+0x2 */ unsigned short num;
};


struct SummonMobList
{
	/* this+0x0 */ int num;
	/* this+0x4 */ mystd::list<unsigned long> summonMob;
};


struct MIN_MAX
{
	/* this+0x0 */ short min;
	/* this+0x2 */ short max;
};


struct STAT_PLUSTABLE
{
	/* this+0x0  */ MIN_MAX maxHP;
	/* this+0x4  */ MIN_MAX maxSP;
	/* this+0x8  */ MIN_MAX Str;
	/* this+0xC  */ MIN_MAX Int;
	/* this+0x10 */ MIN_MAX Vit;
	/* this+0x14 */ MIN_MAX Dex;
	/* this+0x18 */ MIN_MAX Agi;
	/* this+0x1C */ MIN_MAX Luk;
};


struct MONITEMPERCENT
{
	/* this+0x0 */ unsigned short ITID;
	/* this+0x4 */ int percent;
};


struct MONPARAMETER
{
	/* this+0x0  */ int aRan;
	/* this+0x4  */ int LV;
	/* this+0x8  */ int HP;
	/* this+0xC  */ int SP;
	/* this+0x10 */ int str;
	/* this+0x14 */ int Int;
	/* this+0x18 */ int vit;
	/* this+0x1C */ int dex;
	/* this+0x20 */ int agi;
	/* this+0x24 */ int luk;
	/* this+0x28 */ int atk1;
	/* this+0x2C */ int atk2;
	/* this+0x30 */ int def;
	/* this+0x34 */ int exp;
	/* this+0x38 */ int jexp;
	/* this+0x3C */ int inc;
	/* this+0x40 */ int as;
	/* this+0x44 */ int es;
	/* this+0x48 */ int rechargeTime;
	/* this+0x4C */ int attackedMT;
	/* this+0x50 */ int mSpeed;
	/* this+0x54 */ int attackMT;
	/* this+0x58 */ int property;
	/* this+0x5C */ int scale;
	/* this+0x60 */ int _class;
	/* this+0x64 */ int race;
	/* this+0x68 */ int mdef;
	/* this+0x6C */ MONITEMPERCENT itemInfo[0x8];
	/* this+0xAC */ char name[24];
	/* this+0xC4 */ int aiType;
};


struct RACE_INFO
{
	/* this+0x0  */ int ignoreDefCount;
	/* this+0x4  */ int comaPercent;
	/* this+0x8  */ int SPAmount_Attack[0x2];
	/* this+0x10 */ int SPAmount_Kill;
	/* this+0x14 */ int plusDamageSelf;
	/* this+0x18 */ int plusEXPPercent;
	/* this+0x1C */ int plusCRIPercent;
	/* this+0x20 */ short plusMDamagePercent;
	/* this+0x22 */ short ignoreMDEFPercent;
	/* this+0x24 */ short ignoreDEFPercent;
};


struct CLASS_INFO
{
	/* this+0x0 */ int ignoreDEFCount;
	/* this+0x4 */ short plusMDamagePercent;
	/* this+0x6 */ short ignoreMDEFPercent;
	/* this+0x8 */ short ignoreDEFPercent;
};


struct USER_TARGET_INFO
{
	/* this+0x0  */ int destroySPProbability;
	/* this+0x4  */ int destroySPPercent;
	/* this+0x8  */ int plusDamageByClass[0x3];
	/* this+0x14 */ int SPAmount_Action;
};


#pragma pack(push,1)
struct ShortCutKey
{
	/* this+0x0 */ char isSkill;
	/* this+0x1 */ unsigned long ID;
	/* this+0x5 */ short count;
};
#pragma pack(pop)


struct CharacterInfo
{
	struct tagParty
	{
		union
		{
			struct tagConfig
			{
				/* this(bf)+0x0:0x0 len(0x1) */ unsigned char bRefuseJoinMsg : 1,
				/* this(bf)+0x0:0x1 len(0x7) */	              bReserved : 7;
			};

			/* this+0x0 */ tagConfig Bit;
			/* this+0x0 */ unsigned char Config;
		};
	};

	/* this+0x0   */ unsigned long roomID;
	/* this+0x4   */ int accountID;
	/* this+0x8   */ int characterID;
	/* this+0xC   */ int speed;
	/* this+0x10  */ int plusCartspeed;
	/* this+0x14  */ int AuthCode;
	/* this+0x18  */ int isSendable;
	/* this+0x1C  */ int mapID;
	/* this+0x20  */ int GuildID;
	/* this+0x24  */ int GroupID;
	/* this+0x28  */ int isGroupMaster;
	/* this+0x2C  */ short NotifyPositionX;
	/* this+0x2E  */ short NotifyPositionY;
	/* this+0x30  */ unsigned long GroupExpOption;
	/* this+0x34  */ int PartyItemPickupRule;
	/* this+0x38  */ int PartyItemDivisionRule;
	/* this+0x3C  */ int exp;
	/* this+0x40  */ CharacterInfo::tagParty Party;
	/* this+0x41  */ bool bOpenEquipmentWin;
	/* this+0x42  */ short font;
	/* this+0x44  */ int money;
	/* this+0x48  */ int jobexp;
	/* this+0x4C  */ int joblevel;
	/* this+0x50  */ int isWhisperAcceptable;
	/* this+0x54  */ int virtue;
	/* this+0x58  */ int honor;
	/* this+0x5C  */ int PKhonor;
	/* this+0x60  */ int hp;
	/* this+0x64  */ int plusMaxHP;
	/* this+0x68  */ int MHP_Percent;
	/* this+0x6C  */ int sp;
	/* this+0x70  */ int plusMaxSP;
	/* this+0x74  */ int MSP_Percent;
	/* this+0x78  */ short jobpoint;
	/* this+0x7A  */ short sxPos;
	/* this+0x7C  */ short syPos;
	/* this+0x7E  */ short targetxPos;
	/* this+0x80  */ short targetyPos;
	/* this+0x82  */ short StrAmount;
	/* this+0x84  */ short AgiAmount;
	/* this+0x86  */ short VitAmount;
	/* this+0x88  */ short IntAmount;
	/* this+0x8A  */ short DexAmount;
	/* this+0x8C  */ short LukAmount;
	/* this+0x90  */ int ATKPercent;
	/* this+0x94  */ int DEFPercent;
	/* this+0x98  */ short ArcherDex;
	/* this+0x9C  */ int plusAttRange;
	/* this+0xA0  */ int recvBytes;
	/* this+0xA4  */ int sendBytes;
	/* this+0xA8  */ int IsLockOnMode;
	/* this+0xAC  */ unsigned long targetAID;
	/* this+0xB0  */ short job;
	/* this+0xB2  */ short clevel;
	/* this+0xB4  */ short sppoint;
	/* this+0xB6  */ short head;
	/* this+0xB8  */ int weapon;
	/* this+0xBC  */ short accessory;
	/* this+0xC0  */ int shoes;
	/* this+0xC4  */ short headpalette;
	/* this+0xC6  */ short bodypalette;
	/* this+0xC8  */ short accessory2;
	/* this+0xCA  */ short accessory3;
	/* this+0xCC  */ short cookMastery;
	/* this+0xCE  */ short headDir;
	/* this+0xD0  */ unsigned char sex;
	/* this+0xD1  */ char characterName[0x18];
	/* this+0xE9  */ char accountName[0x18];
	/* this+0x101 */ char partyID[0x18];
	/* this+0x119 */ char mapName[0x10];
	/* this+0x129 */ char targetMapName[0x10];
	/* this+0x139 */ char restartMapName[0x10];
	/* this+0x149 */ char Str;
	/* this+0x14A */ char Agi;
	/* this+0x14B */ char Vit;
	/* this+0x14C */ char Int;
	/* this+0x14D */ char Dex;
	/* this+0x14E */ char Luk;
	/* this+0x14F */ char StrP;
	/* this+0x150 */ char AgiP;
	/* this+0x151 */ char VitP;
	/* this+0x152 */ char IntP;
	/* this+0x153 */ char DexP;
	/* this+0x154 */ char LukP;
	/* this+0x155 */ char xSize;
	/* this+0x156 */ char ySize;
	/* this+0x157 */ unsigned char haircolor;
	/* this+0x158 */ int extAttPower;
	/* this+0x15C */ int extItemDefPower;
	/* this+0x160 */ int extMagicAtkPercent;
	/* this+0x164 */ int extMagicDefPower;
	/* this+0x168 */ int extDodgePercent;
	/* this+0x16C */ int extDodgePercent2;
	/* this+0x170 */ int criPercent;
	/* this+0x174 */ int hitPercent;
	/* this+0x178 */ int extAttMPower;
	/* this+0x17C */ int resistByProperty[0xA];
	/* this+0x1A4 */ int plusByRace[0xA];
	/* this+0x1CC */ int resistByRace[0xA];
	/* this+0x1F4 */ int isNeverBreakArmor;
	/* this+0x1F8 */ int isNeverBreakWeapon;
	/* this+0x1FC */ int attackDamageWeapon[0x2];
	/* this+0x204 */ int attackDamageArmor[0x2];
	/* this+0x20C */ int resistHandicapState[0x20];
	/* this+0x28C */ int modifyDamge_RNGATK[0x2];
	/* this+0x294 */ int noDispel;
	/* this+0x298 */ int HPdrain[0x2];
	/* this+0x2A0 */ int SPdrain[0x2];
	/* this+0x2A8 */ int magicImmune;
	/* this+0x2AC */ int noJamstone;
	/* this+0x2B0 */ int reflectPercent;
	/* this+0x2B4 */ int perfectDamage;
	/* this+0x2B8 */ int hasteAttack;
	/* this+0x2BC */ int reinCarnation;
	/* this+0x2C0 */ int reduceSpellCastTime;
	/* this+0x2C4 */ int splashRange;
	/* this+0x2C8 */ int reducePercentSP;
	/* this+0x2CC */ int reducePostDelay;
	/* this+0x2D0 */ RACE_INFO raceInfo[0xA];
	/* this+0x460 */ CLASS_INFO classInfo[0x6];
	/* this+0x4A8 */ USER_TARGET_INFO userTarInfo[0x2];
	/* this+0x4D8 */ int plusAttackSpeed;
	/* this+0x4DC */ int investigateCount;
	/* this+0x4E0 */ int guidedAttackPercent;
	/* this+0x4E4 */ int changeMonPercent;
	/* this+0x4E8 */ float extDEFPercent;
	/* this+0x4EC */ int attackMotionTime;
	/* this+0x4F0 */ int statusAttPower;
	/* this+0x4F4 */ int basicAvoidance;
	/* this+0x4F8 */ int basicHit;
	/* this+0x4FC */ int neverDie;
	/* this+0x500 */ int MATKPercent;
	/* this+0x504 */ int MDEFPercent;
	/* this+0x508 */ int plusMakerPower;
	/* this+0x50C */ char LastOpenMailFromName[0x18];
	/* this+0x524 */ int isChangeShortCutKey;
	/* this+0x528 */ ShortCutKey ShortCutKey[0x1B];
	/* this+0x5E8 */ int HPDrain_100;
	/* this+0x5EC */ short deadCount;

	public: int CharacterInfo::GetMoney(void)
	{
		return this->money;
	}

	public: int CharacterInfo::SetMoney(int Money)
	{
		this->money = max(0, Money);
		return this->money;
	}

	public: int CharacterInfo::AddMoney(int Money)
	{
		if( this->money < 0 )
			this->money = 0;

		if( Money < 0 )
			this->money = max(0, this->money + Money);
		else if( this->money + Money < 0 )
			this->money = INT_MAX;
		else
			this->money = this->money + Money;

		return this->money;
	}
};
C_ASSERT(sizeof CharacterInfo == 0x5F0);


struct CharacterTimeInfo
{
	/* this+0x0  */ unsigned long SpeedMount;
	/* this+0x4  */ unsigned long connectedTime;
	/* this+0x8  */ unsigned long clientLocalConnectTime;
	/* this+0xC  */ unsigned long TotalUsingTime;
	/* this+0x10 */ int HPAcceleration;
	/* this+0x14 */ int SPAcceleration;
	/* this+0x18 */ unsigned long lastPacketArrivedTime;
	/* this+0x1C */ unsigned long HPPlusTime;
	/* this+0x20 */ int HPPlusValue;
	/* this+0x24 */ unsigned long LastHPPlusTime;
	/* this+0x28 */ unsigned long SPPlusTime;
	/* this+0x2C */ int SPPlusValue;
	/* this+0x30 */ unsigned long LastSPPlusTime;
	/* this+0x34 */ unsigned long HPLastHealTime;
	/* this+0x38 */ unsigned long SPLastHealTime;
	/* this+0x3C */ unsigned long AttReqLastTime;
	/* this+0x40 */ unsigned long LastAttackedTime;
	/* this+0x44 */ unsigned long LastCharInfoSaveTime;
	/* this+0x48 */ unsigned long lastMannerTime;
	/* this+0x4C */ unsigned long lastPKMannerTime;
	/* this+0x50 */ unsigned long DamageNoMotionTime;
	/* this+0x54 */ unsigned long SightRange;
	/* this+0x58 */ unsigned long SightplusAttackPower;
	/* this+0x5C */ unsigned long PlusDefencePowerInAcolyte;
	/* this+0x60 */ unsigned long HPPartyNotifyTime;
	/* this+0x64 */ unsigned long LastNPCEventAnswerTime;
	/* this+0x68 */ unsigned long LastClientTime;
	/* this+0x6C */ int ChangeSpeed;
	/* this+0x70 */ int ChangeSpeedTime;
	/* this+0x74 */ unsigned long HSvrAliveTime;
};
C_ASSERT(sizeof CharacterTimeInfo == 0x78);


struct MOVEINFO
{
	/* this+ 0 */ int xPos;
	/* this+ 4 */ int yPos;
	/* this+ 8 */ int dxPos;
	/* this+12 */ int dyPos;
	/* this+16 */ DWORD LastTime;
	/* this+20 */ char dir;
	/* this+24 */ int state; // enum
};


struct MONSPAWN_SETINFO
{
	/* this+0x0 */ unsigned long spriteType;
	/* this+0x4 */ unsigned long npcType;
	/* this+0x8 */ int count;
};


struct MONSTER_CREATED_BYSKILL
{
	/* this+0x0 */ unsigned short SKID;
	/* this+0x4 */ int monsterJob;
	/* this+0x8 */ short count;
};


struct PC_SKILL_INFO
{
	/* this+0x0  */ int level;
	/* this+0x4  */ int type;
	/* this+0x8  */ int typeBefore;
	/* this+0xC  */ int disposableLevel;
	/* this+0x10 */ int orgDispLevel;
	/* this+0x14 */ int imitationLevel;
	/* this+0x18 */ int count;
	/* this+0x1C */ short skillUseType;

	public: PC_SKILL_INFO::PC_SKILL_INFO(void)
	{
		this->level = 0;
		this->typeBefore = -1;
		this->disposableLevel = 0;
		this->orgDispLevel = 0;
		this->imitationLevel = 0;
		this->count = 0;
		this->skillUseType = -1;
	}
};


struct PosInfo
{
	/* this+0x0 */ int x;
	/* this+0x4 */ int y;
	/* this+0x8 */ int isCheckPos;
};


struct SKILLINFO
{
	/* this+ 0 */ unsigned short SKID;
	/* this+ 2 */ int type;
	/* this+ 6 */ short level;
	/* this+ 8 */ short spcost;
	/* this+10 */ short attackRange;
	/* this+12 */ char skillName[24];
	/* this+36 */ bool upgradable;
};


struct DYNAMIC_SKILLINFO
{
	/* this+0x0 */ unsigned short SKID;
	/* this+0x4 */ int orgDispLevel;
};


struct PLAY_SKILLINFO
{
	/* this+0x0 */ unsigned long skAID;
	/* this+0x4 */ PosInfo deltaPos;
};


struct WARP_POSITION
{
	/* this+0x0 */ short xPos;
	/* this+0x2 */ short yPos;
	/* this+0x4 */ char mapName[0x10];
};


struct PARAMETER
{
	/* this+0x0 */ int varType;
	/* this+0x4 */ int amount;
};


class CMapRes;
struct ITEM_INFO
{
	/* this+0x0  */ unsigned long MoveReqLastTime;
	/* this+0x4  */ unsigned long state;
	/* this+0x8  */ unsigned short ITID;
	/* this+0xA  */ unsigned short type;
	/* this+0xC  */ unsigned short count;
	/* this+0xE  */ bool IsIdentified;
	/* this+0x10 */ __int64 unique_identity_numberV2;
	/* this+0x18 */ long hire_expire_date;
	/* this+0x1C */ bool IsDamaged;
	/* this+0x1D */ unsigned char RefiningLevel;
	/* this+0x1E */ EQUIPSLOTINFO slot;
	/* this+0x28 */ int xPos;
	/* this+0x2C */ int yPos;
	/* this+0x30 */ unsigned char subX;
	/* this+0x31 */ unsigned char subY;
	/* this+0x34 */ CMapRes* mapRes;
	/* this+0x38 */ char name[24];

	public: ITEM_INFO::ITEM_INFO(void)
	{
		this->unique_identity_numberV2 = 0;
		this->hire_expire_date = 0;
	}
};


class CAsyncStream;
struct CAsyncOperation : public OVERLAPPED
{
	enum
	{
		RECV = 0x0,
		SEND = 0x1,
	};

	/* this+0x0    */ //OVERLAPPED
	/* this+0x14   */ WSABUF m_dataBuf;
	/* this+0x1C   */ char m_buffer[10240];
	/* this+0x281C */ int m_type;
	/* this+0x2820 */ SOCKET m_socket;
	/* this+0x2824 */ CAsyncStream* m_stream;
};


struct MVPINFO
{
	/* this+ 0 */ int expPercent;
	/* this+ 4 */ int itemPercent[3];
	/* this+16 */ char name[24];
	/* this+40 */ char itemName[3][24];
};


struct GUILDNOTICE
{
	/* this+0x0  */ int GDID;
	/* this+0x4  */ char Subject[0x3C];
	/* this+0x40 */ char Notice[0x78];
};


#pragma pack(push, 1)
struct GUILDMINFO
{
	/* this+  0 */ int GID;
	/* this+  4 */ char CharName[24];
	/* this+ 28 */ char AccountName[24];
	/* this+ 52 */ int Level;
	/* this+ 56 */ char Memo[50];
	/* this+106 */ int Service;
	/* this+110 */ int MemberExp;
	/* this+114 */ int GDID;
	/* this+118 */ int AID;
	/* this+122 */ int PositionID;
	/* this+126 */ short head;
	/* this+128 */ short headPalette;
	/* this+130 */ short sex;
	/* this+132 */ int job;
	/* this+136 */ int status;
};
#pragma pack(pop)


struct GUILDALLYINFO
{
	/* this+0x0  */ int GDID;
	/* this+0x4  */ int OpponentGDID;
	/* this+0x8  */ char GuildName[0x18];
	/* this+0x20 */ int Relation;
};


struct GUILDBANISHINFO
{
	/* this+0x0  */ int GDID;
	/* this+0x4  */ char MemberName[0x18];
	/* this+0x1C */ char MemberAccount[0x18];
	/* this+0x34 */ char Reason[0x32];
	/* this+0x66 */ int GID;
	/* this+0x6A */ int AID;
};


struct GUILDMPOSITION
{
	/* this+0x0  */ int GDID;
	/* this+0x4  */ int Grade;
	/* this+0x8  */ char PosName[0x18];
	/* this+0x20 */ int JoinRight;
	/* this+0x24 */ int PenaltyRight;
	/* this+0x28 */ int PositionID;
	/* this+0x2C */ int Service;
};


struct NpcSvrNpcInfo
{
	/* this+ 0 */ const char* zone;
	/* this+ 4 */ const char* name;
	/* this+ 8 */ int type;
	/* this+12 */ int x;
	/* this+16 */ int y;
	/* this+20 */ int dx;
	/* this+24 */ int dy;
	/* this+28 */ int w;
	/* this+32 */ int h;
	/* this+36 */ int sprite;
	/* this+40 */ int direction;
	/* this+44 */ int regenMin;
	/* this+48 */ int regenMax;
	/* this+52 */ int regenType;
	/* this+56 */ int npcType;

	public: void NpcSvrNpcInfo::SetDefault(void)
	{
		this->zone = 0;
		this->name = 0;
		this->type = 0;
		this->x = 0;
		this->y = 0;
		this->dx = 0;
		this->dy = 0;
		this->direction = 0;
		this->sprite = 32;
		this->w = 0;
		this->h = 0;
		this->regenMin = 1000;
		this->regenMax = 4000;
		this->regenType = 0;
		this->npcType = 0;
	}
};


struct MapInfo
{
	/* this+0x0  */ bool bPlayerEnter;
	/* this+0x4  */ int ZSID;
	/* this+0x8  */ int MapID;
	/* this+0xC  */ int type;
	/* this+0x10 */ char Name[0x18];

	public: MapInfo::MapInfo(void)
	{
		this->bPlayerEnter = true;
	}
};


struct _SERVERINFO
{
	/* this+0x0  */ int SID;
	/* this+0x4  */ int Type;
	/* this+0x8  */ unsigned long ip;
	/* this+0xC  */ mystd::string IPstr;
	/* this+0x28 */ int Port;
	/* this+0x2C */ int DestinationOneSID;
	/* this+0x30 */ int DestinationTwoSID;
	/* this+0x34 */ char Name[0x14];
	/* this+0x48 */ unsigned long PrivateIP;
	/* this+0x4C */ mystd::string PrivateIPstr;
	/* this+0x68 */ int PrivatePort;

	public: _SERVERINFO::_SERVERINFO(void)
	{
		memset(this, 0, sizeof(*this)); //FIXME: trashes state of IPstr and PrivateIPstr
	}
};


struct NPCSKILLINFO
{
	/* this+0x0  */ int status;
	/* this+0x4  */ unsigned short SKID;
	/* this+0x8  */ int level;
	/* this+0xC  */ int percent;
	/* this+0x10 */ int casttime;
	/* this+0x14 */ unsigned long cooldowntime;
	/* this+0x18 */ int noDispel;
	/* this+0x1C */ int ai_type;
	/* this+0x20 */ int emoticon;
	/* this+0x24 */ int chatNo;
	/* this+0x28 */ int condition;
	/* this+0x2C */ int value;
};


struct NPC_CHAT_INFO
{
	/* this+0x0 */ unsigned long color;
	/* this+0x4 */ char chat[0x100];

	public: NPC_CHAT_INFO::NPC_CHAT_INFO(void)
	{
		this->color = 0;
		memset(this->chat, 0, sizeof(this->chat));
	}
};


struct AUCTIONTIME
{
	/* this+0x0 */ short Year;
	/* this+0x2 */ short Month;
	/* this+0x4 */ short Day;
	/* this+0x6 */ short Hour;
};


struct DBAUCTIONINFO
{
	/* this+0x0  */ unsigned long AuctionID;
	/* this+0x4  */ unsigned long ZoneServerID;
	/* this+0x8  */ unsigned long AID;
	/* this+0xC  */ unsigned long GID;
	/* this+0x10 */ char SellerName[0x18];
	/* this+0x28 */ unsigned long BuyerAID;
	/* this+0x2C */ unsigned long BuyerGID;
	/* this+0x30 */ char BuyerName[0x18];
	/* this+0x48 */ unsigned long NowPrice;
	/* this+0x4C */ unsigned long MaxPrice;
	/* this+0x50 */ AUCTIONTIME EndTime;
	/* this+0x58 */ int AuctionType;
	/* this+0x5C */ char Item[0x28];
	/* this+0x84 */ unsigned long ItemLen;
};


struct AUCTIONINFO : public DBAUCTIONINFO
{
	/* this+0x0  */ //DBAUCTIONINFO
	/* this+0x88 */ int isBuyer;
	/* this+0x8C */ unsigned short ITID;
	/* this+0x8E */ unsigned short ItemType;
	/* this+0x90 */ int count;
	/* this+0x94 */ bool IsIdentified;
	/* this+0x95 */ bool IsDamaged;
	/* this+0x96 */ unsigned char refiningLevel;
	/* this+0x97 */ EQUIPSLOTINFO slot;
};


struct SKILL_INFO
{
	/* this+0x0  */ short xPos;
	/* this+0x2  */ short yPos;
	/* this+0x4  */ unsigned long operateTime;
	/* this+0x8  */ unsigned long expiredTime;
	/* this+0xC  */ unsigned long birthTime;
	/* this+0x10 */ unsigned long creatorAID;
	/* this+0x14 */ unsigned long state;
	/* this+0x18 */ unsigned long MoveReqLastTime;
	/* this+0x1C */ int hp;
	/* this+0x20 */ unsigned char job;
	/* this+0x21 */ unsigned char originalJob;
	/* this+0x22 */ short level;
	/* this+0x24 */ PosInfo creatorPos;
};
C_ASSERT(sizeof SKILL_INFO == 0x30);


struct SKILL_TIME_INFO
{
	/* this+0x0 */ unsigned long lastHPMinusTime;
};
C_ASSERT(sizeof SKILL_TIME_INFO == 0x4);


struct BOSS_INFO
{
	/* this+0x0  */ bool isBossInMap;
	/* this+0x4  */ int lastNotifyPositionX;
	/* this+0x8  */ int lastNotifyPositionY;
	/* this+0xC  */ unsigned long lastNotifyTime;
	/* this+0x10 */ bool isDead;
	/* this+0x12 */ SYSTEMTIME regenSystemTime;
	/* this+0x24 */ unsigned long regenTime;
	/* this+0x28 */ mystd::list<int> pcList;

	public: void BOSS_INFO::Init(int xPos, int yPos)
	{
		this->isBossInMap = 0;
		this->lastNotifyPositionX = xPos;
		this->lastNotifyPositionY = yPos;
		this->lastNotifyTime = 0;
		this->isDead = 0;
		memset(&this->regenSystemTime, 0, sizeof(this->regenSystemTime));
		this->regenTime = 0;
		this->pcList.clear();
	}
};


struct ARENA_ROOM_INFO
{
	/* this+0x0 */ int fee;
	/* this+0x4 */ int lowLevel;
	/* this+0x8 */ int highLevel;
	/* this+0xC */ mystd::list<int> m_exJob;
};


struct STATUS
{
	/* this+0x0  */ int Str;
	/* this+0x4  */ int Agi;
	/* this+0x8  */ int Vit;
	/* this+0xC  */ int Int;
	/* this+0x10 */ int Dex;
	/* this+0x14 */ int Luk;
};


struct AGIT_DBINFO
{
	/* this+ 0 */ char mapName[16];
	/* this+16 */ char agitName[24];
	/* this+40 */ int guildID;
	/* this+44 */ int economy;
	/* this+48 */ int defense;
	/* this+52 */ int triggerE;
	/* this+56 */ int triggerD;
	/* this+60 */ long nextTime;
	/* this+64 */ long payTime;
	/* this+68 */ long createTime;
	/* this+72 */ unsigned char visibleC;
	/* this+73 */ unsigned char visibleG[8];
};


struct BATTLEFIELD_MAPINFO
{
	/* this+0x0 */ short aX2;
	/* this+0x2 */ short aY2;
	/* this+0x4 */ short bX2;
	/* this+0x6 */ short bY2;
	/* this+0x8 */ bool isPointNotify;
	/* this+0x9 */ bool isPKPoint;
	/* this+0xA */ bool isAlivePCCheck;
	/* this+0xB */ bool isNpcNotify;
};


struct BATTLEFIELD_STATEINFO
{
	/* this+0x0 */ int a_point;
	/* this+0x4 */ int b_point;
};


struct MCSTORE_ITEMEXTRA_INFO
{
	/* this+0x0 */ int price;
};


struct WINPOINT
{
	/* this+0x0 */ unsigned long AID;
	/* this+0x4 */ int winpoint;
};


class CCharacter;
struct ATTACK_INFO
{
	/* this+0x0  */ CCharacter* target;
	/* this+0x4  */ int position;
	/* this+0x8  */ int skillProperty;
	/* this+0xC  */ int plusATTPowerPercent;
	/* this+0x10 */ int plusATTSuccessPercent;
	/* this+0x14 */ int calculateType;
	/* this+0x18 */ int isRangeAttack;
	/* this+0x1C */ unsigned short SKID;
	/* this+0x1E */ short skLevel;

	public: ATTACK_INFO::ATTACK_INFO(void)
	{
		this->plusATTPowerPercent = 100;
		this->plusATTSuccessPercent = 100;
		this->target = NULL;
		this->position = 2;
		this->skillProperty = 0;
		this->calculateType = 1;
		this->isRangeAttack = 0;
		this->SKID = 0;
		this->skLevel = 0;
	}
};


struct PASERRET
{
	enum enumError
	{
		ERROR_NONE                         = 0,
		ERROR_CRITICAL_MEMORY_ALLOC        = 1,
		ERROR_CRITICAL_UNKNOWN_VERSION     = 2,
		ERROR_CRITICAL_MISMATCH_TYPE       = 3,
		ERROR_CRITICAL_UNKNOWN_PASING_TYPE = 4,
		ERROR_CRITICAL_ZIP_UNCOMPRESS      = 5,
		ERROR_CRITICAL_NOTEXIST_TYPE       = 6,
		ERROR_CRITICAL_UNKNOWN             = 7,
		ERROR_ADD                          = 8,
	};

	/* this+0x0 */ enum PASERRET::enumError m_error;
	/* this+0x4 */ int m_used_bytes;

	public: PASERRET::PASERRET(const enum PASERRET::enumError in_error, const int in_used_bytes)
	{
		this->m_error = in_error;
		this->m_used_bytes = in_used_bytes;
	}

	public: PASERRET::PASERRET(void)
	{
		this->m_error = ERROR_NONE;
		this->m_used_bytes = 0;
	}
};


struct PET_PROPERTY
{
	/* this+0x0  */ int dbkey;
	/* this+0x4  */ char name[24];
	/* this+0x1C */ int modified;
	/* this+0x20 */ int spriteType;
	/* this+0x24 */ int level;
	/* this+0x28 */ int fullness;
	/* this+0x2C */ int relationship;
	/* this+0x30 */ int accessary;
};


struct SPETLOG
{
	/* this+0x0  */ unsigned long characterID;
	/* this+0x4  */ PET_PROPERTY property;
	/* this+0x38 */ char mapName[16];
	/* this+0x48 */ int logType;

	public: SPETLOG::SPETLOG(const unsigned long in_gid, const PET_PROPERTY in_property, const char* in_mapName, const int in_logType)
	{
		this->characterID = in_gid;
		memcpy(&this->property, &in_property, sizeof(this->property));
		memset(this->mapName, 0, sizeof(this->mapName));
		strncpy(this->mapName, in_mapName ? in_mapName : "none", sizeof(this->mapName));
		this->logType = in_logType;
	}
};


struct SKILLATTACK_MSG
{
	/* this+0x0  */ unsigned long targetAID;
	/* this+0x4  */ unsigned short SKID;
	/* this+0x8  */ unsigned long srcAID;
	/* this+0xC  */ short level;
	/* this+0xE  */ short count;
	/* this+0x10 */ short xPos;
	/* this+0x12 */ short yPos;
	/* this+0x14 */ short msgtype;
	/* this+0x18 */ int par1;
	/* this+0x1C */ unsigned char actionType;
	/* this+0x20 */ int isDivide;
	/* this+0x24 */ short skLevel;
	/* this+0x26 */ bool isEnableDirectPath;
	/* this+0x28 */ int finalDamage;

	public: SKILLATTACK_MSG::SKILLATTACK_MSG(void)
	{
		this->skLevel = 0;
		this->msgtype = 0;
		this->srcAID = 0;
		this->par1 = 0;
		this->isDivide = 0;
		this->count = 1;
		this->isEnableDirectPath = 1;
		this->finalDamage = 0;
	}

	public: short SKILLATTACK_MSG::GetType(void)
	{
		return this->msgtype;
	}

	public: void SKILLATTACK_MSG::SetType(short type)
	{
		this->msgtype = type;
	}
};


struct _BOTDATA
{
	/* this+0x0 */ short penalty;
	/* this+0x4 */ unsigned long penaltyTime;
	/* this+0x8 */ short warning;

	public: _BOTDATA::_BOTDATA(void)
	{
		this->penalty = 0;
		this->penaltyTime = 0;
		this->warning = 0;
	}

	public: _BOTDATA::~_BOTDATA(void)
	{
	}

	public: void _BOTDATA::Init(void)
	{
		this->penalty = 0;
		this->penaltyTime = 0;
		this->warning = 0;
	}
};


struct STRUCT_SK_EVENT
{
	/* this+0x0 */ mystd::map<unsigned long,void *> infoMap;
};


struct NEIGHBORHOOD_SECTION
{
	/* this+0x0 */ mystd::vector<CCharacter *>* section[4];
};


struct _MEventItemInfo
{
	/* this+0x0  */ int MNum;
	/* this+0x4  */ int AID;
	/* this+0x8  */ int money;
	/* this+0xC  */ int ItemID;
	/* this+0x10 */ short ItemCount;
	/* this+0x14 */ int couponNum;
	/* this+0x18 */ int remark;
	/* this+0x1C */ SYSTEMTIME expireTime;
	/* this+0x2C */ int hireTime;
};


#pragma pack(push,1)
struct REPAIRITEM_INFO
{
	/* this+0x0 */ short index;
	/* this+0x2 */ unsigned short ITID;
	/* this+0x4 */ unsigned char refiningLevel;
	/* this+0x5 */ EQUIPSLOTINFO slot;
};
#pragma pack(pop)


#pragma pack(push,1)
struct GUILD_MEMBER_INFO
{
	/* this+ 0 */ int AID;
	/* this+ 4 */ int GID;
	/* this+ 8 */ short head;
	/* this+10 */ short headPalette;
	/* this+12 */ short sex;
	/* this+14 */ short job;
	/* this+16 */ short level;
	/* this+18 */ int contributionExp;
	/* this+22 */ int currentState;
	/* this+26 */ int positionID;
	/* this+30 */ char intro[50];
	/* this+80 */ char charname[24];
};
#pragma pack(pop)
C_ASSERT(sizeof GUILD_MEMBER_INFO == 104);


struct CoupleInfo
{
	/* this+0x0 */ unsigned long maleGID;
	/* this+0x4 */ unsigned long femaleGID;
	/* this+0x8 */ SYSTEMTIME weddingTime;
};


struct FamilyInfo
{
	/* this+0x0  */ unsigned long index;
	/* this+0x4  */ unsigned long father;
	/* this+0x8  */ unsigned long mother;
	/* this+0xC  */ unsigned long baby;
	/* this+0x10 */ SYSTEMTIME Time;
};


struct ITEM_PLUSSTATUS_VALUE
{
	/* this+0x0 */ short dexValue;
	/* this+0x2 */ short strValue;
	/* this+0x4 */ short intValue;
	/* this+0x6 */ short lukValue;
	/* this+0x8 */ short agiValue;
	/* this+0xA */ short vitValue;
};


struct ITEM_PLUSPOWEROFITEM
{
	/* this+0x0  */ short rightAttackPower;
	/* this+0x2  */ short leftAttackPower;
	/* this+0x4  */ short defencePower;
	/* this+0x6  */ short magicDefPower;
	/* this+0x8  */ short equipedArrowAttPow;
	/* this+0xA  */ short rightrefiningAttPower;
	/* this+0xC  */ short leftrefiningAttPower;
	/* this+0xE  */ short refiningDefPower;
	/* this+0x10 */ short magicAttackPower;
};


struct CommonItemInfo
{
	/* this+0x0  */ unsigned short ITID;
	/* this+0x2  */ int count;
	/* this+0x6  */ unsigned short ServerItemType;
	/* this+0x8  */ unsigned short Type;
	/* this+0xA  */ bool IsIdentified;
	/* this+0xB  */ bool IsDamaged;
	/* this+0xC  */ unsigned char refiningLevel;
	/* this+0xD  */ EQUIPSLOTINFO slot;
	/* this+0x15 */ __int64 UniqueSerialNum;
	/* this+0x1D */ long HireExpireDate;
};


#pragma pack(push,1)
struct PURCHASE_ITEM
{
	/* this+0 */ int price;
	/* this+4 */ int discountprice;
	/* this+8 */ unsigned char type;
	/* this+9 */ unsigned short ITID;
};
#pragma pack(pop)


#pragma pack(push,1)
struct SELL_ITEM
{
	/* this+0 */ short index;
	/* this+2 */ int price;
	/* this+6 */ int overchargeprice;
};
#pragma pack(pop)


#pragma pack(push,1)
struct CZ_PURCHASE_ITEM
{
	/* this+0 */ short count;
	/* this+2 */ unsigned short ITID;
};
#pragma pack(pop)


#pragma pack(push,1)
struct CZ_SELL_ITEM
{
	/* this+0 */ short index;
	/* this+2 */ short count;
};
#pragma pack(pop)


#pragma pack(push,1)
struct CZ_PURCHASE_ITEM_FROMMC
{
	/* this+0 */ short count;
	/* this+2 */ short index;
};
#pragma pack(pop)


#pragma pack(push,1)
struct PURCHASE_ITEM_FROMMC
{
	/* this+ 0 */ int price;
	/* this+ 4 */ short count;
	/* this+ 6 */ short index;
	/* this+ 8 */ unsigned char type;
	/* this+ 9 */ unsigned short ITID;
	/* this+11 */ bool IsIdentified;
	/* this+12 */ bool IsDamaged;
	/* this+13 */ unsigned char refiningLevel;
	/* this+14 */ EQUIPSLOTINFO slot;
};
#pragma pack(pop)


struct AttrAttackInfo
{
	/* this+0x0 */ int val[10][10];
};


struct CHARINFO_TO_CHARACTERDB
{
	struct tagParty
	{
		/* this+0x0 */ unsigned char Config;
	};

	/* this+0x0  */ int exp;
	/* this+0x4  */ int GuildID;
	/* this+0x8  */ int money;
	/* this+0xC  */ int jobexp;
	/* this+0x10 */ int joblevel;
	/* this+0x14 */ int bodystate;
	/* this+0x18 */ int healthstate;
	/* this+0x1C */ int effectstate;
	/* this+0x20 */ int virtue;
	/* this+0x24 */ int honor;
	/* this+0x28 */ short hp;
	/* this+0x2A */ short maxhp;
	/* this+0x2C */ short sp;
	/* this+0x2E */ short maxsp;
	/* this+0x30 */ short xPos;
	/* this+0x32 */ short yPos;
	/* this+0x34 */ short speed;
	/* this+0x36 */ short jobpoint;
	/* this+0x38 */ short sxPos;
	/* this+0x3A */ short syPos;
	/* this+0x3C */ short job;
	/* this+0x3E */ short clevel;
	/* this+0x40 */ short sppoint;
	/* this+0x42 */ short head;
	/* this+0x44 */ short weapon;
	/* this+0x46 */ short accessory;
	/* this+0x48 */ short accessory2;
	/* this+0x4A */ short accessory3;
	/* this+0x4C */ short headpalette;
	/* this+0x4E */ short bodypalette;
	/* this+0x50 */ short cookMastery;
	/* this+0x52 */ char mapname[16];
	/* this+0x62 */ char restartMapName[16];
	/* this+0x72 */ unsigned char Str;
	/* this+0x73 */ unsigned char Agi;
	/* this+0x74 */ unsigned char Vit;
	/* this+0x75 */ unsigned char Int;
	/* this+0x76 */ unsigned char Dex;
	/* this+0x77 */ unsigned char Luk;
	/* this+0x78 */ unsigned char haircolor;
	/* this+0x79 */ CHARINFO_TO_CHARACTERDB::tagParty Party;
	/* this+0x7A */ bool bOpenEquipmentWin;
	/* this+0x7B */ short font;
	/* this+0x7D */ char ZenyCheckSum[4];
};


struct GUILDINFO
{
	/* this+0x0  */ int GDID;
	/* this+0x4  */ int Level;
	/* this+0x8  */ char Name[24];
	/* this+0x20 */ char MName[24];
	/* this+0x38 */ int MaxUserNum;
	/* this+0x3C */ int UserNum;
	/* this+0x40 */ int Honor;
	/* this+0x44 */ int Virtue;
	/* this+0x48 */ int Type;
	/* this+0x4C */ int Class;
	/* this+0x50 */ int Money;
	/* this+0x54 */ int ArenaWin;
	/* this+0x58 */ int ArenaLose;
	/* this+0x5C */ int ArenaDrawn;
	/* this+0x60 */ char ManageLand[24];
	/* this+0x78 */ int Exp;
	/* this+0x7C */ int EmblemVersion;
	/* this+0x80 */ int Point;
	/* this+0x84 */ char Desc[80];
};


struct CHARINFO_FROM_CHARACTERDB
{
	struct tagParty
	{
		/* this+0x0 */ unsigned char Config;
	};

	/* this+0x0  */ int GID;
	/* this+0x4  */ int exp;
	/* this+0x8  */ int AID;
	/* this+0xC  */ int GuildID;
	/* this+0x10 */ int money;
	/* this+0x14 */ int jobexp;
	/* this+0x18 */ int joblevel;
	/* this+0x1C */ int bodystate;
	/* this+0x20 */ int healthstate;
	/* this+0x24 */ int effectstate;
	/* this+0x28 */ int virtue;
	/* this+0x2C */ int honor;
	/* this+0x30 */ short hp;
	/* this+0x32 */ short maxhp;
	/* this+0x34 */ short sp;
	/* this+0x36 */ short maxsp;
	/* this+0x38 */ short xPos;
	/* this+0x3A */ short yPos;
	/* this+0x3C */ short speed;
	/* this+0x3E */ short jobpoint;
	/* this+0x40 */ short sxPos;
	/* this+0x42 */ short syPos;
	/* this+0x44 */ short head;
	/* this+0x46 */ short weapon;
	/* this+0x48 */ short accessory;
	/* this+0x4A */ short accessory2;
	/* this+0x4C */ short accessory3;
	/* this+0x4E */ short headpalette;
	/* this+0x50 */ short bodypalette;
	/* this+0x52 */ short cookMastery;
	/* this+0x54 */ char name[24];
	/* this+0x6C */ char mapname[16];
	/* this+0x7C */ char restartMapName[16];
	/* this+0x8C */ short job;
	/* this+0x8E */ short clevel;
	/* this+0x90 */ short sppoint;
	/* this+0x92 */ char Str;
	/* this+0x93 */ char Agi;
	/* this+0x94 */ char Vit;
	/* this+0x95 */ char Int;
	/* this+0x96 */ char Dex;
	/* this+0x97 */ char Luk;
	/* this+0x98 */ char CharNum;
	/* this+0x99 */ unsigned char haircolor;
	/* this+0x9A */ CHARINFO_FROM_CHARACTERDB::tagParty Party;
	/* this+0x9B */ bool bOpenEquipmentWin;
	/* this+0x9C */ short font;
	/* this+0x9E */ char ZenyCheckSum[4];
};


struct MAKERINFO
{
	/* this+0x0  */ int rank;
	/* this+0x4  */ char charname[24];
	/* this+0x1C */ int point;
};


struct MAKER_RANKING
{
	/* this+0x0  */ unsigned long GID;
	/* this+0x4  */ char charname[24];
	/* this+0x1C */ int point;
};


struct WARPPORTAL_INFO
{
	/* this+0x0  */ char mapName[3][16];
	/* this+0x30 */ short xPos[3];
	/* this+0x36 */ short yPos[3];
};


struct CollideInfo
{
  /* this+0x0 */ mystd::vector<CCharacter*>* sectionList;
  /* this+0x4 */ int count;
};


#pragma pack(push,1)
struct MAKABLEITEM_INFO
{
  /* this+0 */ unsigned short ITID;
  /* this+2 */ unsigned short material_ID[3];
};
#pragma pack(pop)


struct PACKET_MOB_HUNTING
{
	/* this+0 */ unsigned long questID;
	/* this+4 */ unsigned long mobGID;
	/* this+8 */ short count;
};


struct ZSERVER_ADDR
{
	/* this+0 */ DWORD ip;
	/* this+4 */ WORD port;
};


/// @see PACKET_ZC_MYGUILD_BASIC_INFO
/// @see CGuild::GetGuildAllyInfo()
struct RELATED_GUILD_INFO
{
	/* this+0 */ int relation;
	/* this+4 */ int GDID;
	/* this+8 */ char guildname[24];
};
