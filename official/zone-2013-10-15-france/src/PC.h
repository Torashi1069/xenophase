#pragma once
#include "Actor.h"
#include "AsyncMonopolyProcess.h"
#include "CHPAmount.h"
#include "CSPAmount.h"
#include "HostPathFinder.h"
#include "ITP.h"
#include "PCBattle.h"
#include "PCClientUpdater.h"
#include "PCElemental.h"
#include "PCHireItemCtrl.h"
#include "PCItem.h"
#include "PCItemInventoryMgr.h"
#include "PCPacketHandler.h"
class CPCProperty; // #include "PCProperty.h"
#include "PCQuestEvent.h"
#include "PCPacketHandler.h"
#include "PCSkill.h"
#include "Request.h"
#include "Struct.h"
#include "AsyncDBWork/Effect3rd.h"
#include "GameGuard/CSAuth2.h"
#include "Player/Inventory/CIVItItem.h"


struct CLASS_INFO
{
	/* this+0 */ int ignoreDEFCount;
	/* this+4 */ short plusMDamagePercent;
	/* this+6 */ short ignoreMDEFPercent;
	/* this+8 */ short ignoreDEFPercent;
};


struct USER_TARGET_INFO
{
	/* this+ 0 */ int destroySPProbability;
	/* this+ 4 */ int destroySPPercent;
	/* this+ 8 */ int plusDamageByClass[3];
	/* this+20 */ int SPAmount_Action;
};


struct CharacterInfo
{
	/* this+   0 */ unsigned long roomID;
	/* this+   4 */ int accountID;
	/* this+   8 */ int characterID;
	/* this+  12 */ int speed;
	/* this+  16 */ int plusCartspeed;
	/* this+  20 */ int AuthCode;
	/* this+  24 */ BOOL isSendable;
	/* this+  28 */ int mapID;
	/* this+  32 */ int GuildID;
	/* this+  36 */ int GroupID;
	/* this+  40 */ BOOL isGroupMaster;
	/* this+  44 */ short NotifyPositionX;
	/* this+  46 */ short NotifyPositionY;
	/* this+  48 */ unsigned long GroupExpOption;
	/* this+  52 */ int PartyItemPickupRule;
	/* this+  56 */ int PartyItemDivisionRule;
	/* this+  60 */ int exp;
	struct tagParty
	{
		union
		{
			struct tagConfig
			{
				/* this(bf)+0:0 len(1) */ unsigned char bRefuseJoinMsg : 1,
				/* this(bf)+0:1 len(7) */	            bReserved : 7;
			};

			/* this+0 */ tagConfig Bit;
			/* this+0 */ unsigned char Config;
		};
	};
	/* this+  64 */ tagParty Party;
	/* this+  65 */ bool bOpenEquipmentWin;
	/* this+  66 */ short font;
private:
	/* this+  68 */ int money;
public:
	int GetMoney()
	{
		return this->money;
	}

	int SetMoney(int Money)
	{
		this->money = ( Money >= 0 ) ? Money : 0;

		return this->money;
	}

	int AddMoney(int Money)
	{
		if( this->money < 0 )
			this->money = 0;

		if( Money < 0 )
			this->money = ( this->money + Money >= 0 ) ? this->money + Money : 0;
		else
			this->money = ( this->money + Money >= 0 ) ? this->money + Money : INT_MAX;

		return this->money;
	}

public:
	/* this+  72 */ int jobexp;
	/* this+  76 */ int joblevel;
	/* this+  80 */ BOOL isWhisperAcceptable;
	/* this+  84 */ int virtue;
	/* this+  88 */ int honor;
	/* this+  92 */ int PKhonor;
	/* this+  96 */ int plusMaxHP;
	/* this+ 100 */ int MHP_Percent;
	/* this+ 104 */ int plusMaxSP;
	/* this+ 108 */ int MSP_Percent;
	/* this+ 112 */ short jobpoint;
	/* this+ 114 */ short sxPos;
	/* this+ 116 */ short syPos;
	/* this+ 118 */ short targetxPos;
	/* this+ 120 */ short targetyPos;
	/* this+ 122 */ short StrAmount;
	/* this+ 124 */ short AgiAmount;
	/* this+ 126 */ short VitAmount;
	/* this+ 128 */ short IntAmount;
	/* this+ 130 */ short DexAmount;
	/* this+ 132 */ short LukAmount;
	/* this+ 136 */ int ATKPercent;
	/* this+ 140 */ int DEFPercent;
	/* this+ 144 */ short ArcherDex;
	/* this+ 148 */ int plusAttRange;
	/* this+ 152 */ int recvBytes;
	/* this+ 156 */ int sendBytes;
	/* this+ 160 */ BOOL IsLockOnMode;
	/* this+ 164 */ unsigned long targetAID;
	/* this+ 168 */ short job;
	/* this+ 170 */ short clevel;
	/* this+ 172 */ short sppoint;
	/* this+ 174 */ short head;
	/* this+ 176 */ int weapon;
	/* this+ 180 */ short accessory;
	/* this+ 184 */ int shoes;
	/* this+ 188 */ short headpalette;
	/* this+ 190 */ short bodypalette;
	/* this+ 192 */ short accessory2;
	/* this+ 194 */ short accessory3;
	/* this+ 196 */ short cookMastery;
	/* this+ 198 */ short headDir;
	/* this+ 200 */ unsigned char sex;
	/* this+ 201 */ char characterName[24];
	/* this+ 225 */ char accountName[24];
	/* this+ 249 */ char partyID[24];
	/* this+ 273 */ char mapName[16];
	/* this+ 289 */ char targetMapName[16];
	/* this+ 305 */ char restartMapName[16];
	/* this+ 321 */ char Str;
	/* this+ 322 */ char Agi;
	/* this+ 323 */ char Vit;
	/* this+ 324 */ char Int;
	/* this+ 325 */ char Dex;
	/* this+ 326 */ char Luk;
	/* this+ 327 */ char StrP;
	/* this+ 328 */ char AgiP;
	/* this+ 329 */ char VitP;
	/* this+ 330 */ char IntP;
	/* this+ 331 */ char DexP;
	/* this+ 332 */ char LukP;
	/* this+ 333 */ char xSize;
	/* this+ 334 */ char ySize;
	/* this+ 335 */ unsigned char haircolor;
	/* this+ 336 */ int extAttPower;
	/* this+ 340 */ int extItemDefPower;
	/* this+ 344 */ int extMagicAtkPercent;
	/* this+ 348 */ int extMagicDefPower;
	/* this+ 352 */ int extDodgePercent;
	/* this+ 356 */ int extDodgePercent2;
	/* this+ 360 */ int criPercent;
	/* this+ 364 */ int hitPercent;
	/* this+ 368 */ int extAttMPower;
	/* this+ 372 */ int isNeverBreakArmor;
	/* this+ 376 */ int isNeverBreakWeapon;
	/* this+ 380 */ int attackDamageWeapon[2];
	/* this+ 388 */ int attackDamageArmor[2];
	/* this+ 396 */ int resistHandicapState[41];
	/* this+ 560 */ int modifyDamge_RNGATK[2];
	/* this+ 568 */ BOOL noDispel;
	/* this+ 572 */ int HPdrain[2];
	/* this+ 580 */ int SPdrain[2];
	/* this+ 588 */ int magicImmune;
	/* this+ 592 */ BOOL noJamstone;
	/* this+ 596 */ int reflectPercent;
	/* this+ 600 */ int perfectDamage;
	/* this+ 604 */ int hasteAttack;
	/* this+ 608 */ int reinCarnation;
	/* this+ 612 */ int reduceSpellCastTime;
	/* this+ 616 */ int splashRange;
	/* this+ 620 */ int reducePercentSP;
	/* this+ 624 */ int reducePostDelay;
	/* this+ 628 */ CLASS_INFO classInfo[6];
	/* this+ 700 */ USER_TARGET_INFO userTarInfo[2];
	/* this+ 748 */ int plusAttackSpeed;
	/* this+ 752 */ int investigateCount;
	/* this+ 756 */ int guidedAttackPercent;
	/* this+ 760 */ int changeMonPercent;
	/* this+ 764 */ float extDEFPercent;
	/* this+ 768 */ float extMDEFPercent;
	/* this+ 772 */ int DEFFluctuation;
	/* this+ 776 */ int MDEFFluctuation;
	/* this+ 780 */ int neverDie;
	/* this+ 784 */ int MATKPercent;
	/* this+ 788 */ int MDEFPercent;
	/* this+ 792 */ int plusMakerPower;
	/* this+ 796 */ char LastOpenMailFromName[24];
	/* this+ 820 */ int isChangeShortCutKey;
	/* this+ 824 */ tagShortCutKey ShortCutKey[38];
	/* this+1092 */ int HPDrain_100;
	/* this+1096 */ short deadCount;
	/* this+1098 */ short m_Body;
	/* this+1100 */ short robe;
};
C_ASSERT( sizeof CharacterInfo == 1104 );


struct CharacterTimeInfo
{
	/* this+  0 */ unsigned long SpeedMount;
	/* this+  4 */ unsigned long connectedTime;
	/* this+  8 */ unsigned long clientLocalConnectTime;
	/* this+ 12 */ unsigned long TotalUsingTime;
	/* this+ 16 */ int HPAcceleration;
	/* this+ 20 */ int SPAcceleration;
	/* this+ 24 */ unsigned long lastPacketArrivedTime;
	/* this+ 28 */ unsigned long LastHPPlusTime;
	/* this+ 32 */ unsigned long LastSPPlusTime;
	/* this+ 36 */ unsigned long HPLastHealTime;
	/* this+ 40 */ unsigned long SPLastHealTime;
	/* this+ 44 */ unsigned long AttReqLastTime;
	/* this+ 48 */ unsigned long LastAttackedTime;
	/* this+ 52 */ unsigned long LastCharInfoSaveTime;
	/* this+ 56 */ unsigned long lastMannerTime;
	/* this+ 60 */ unsigned long lastPKMannerTime;
	/* this+ 64 */ unsigned long DamageNoMotionTime;
	/* this+ 68 */ unsigned long SightRange;
	/* this+ 72 */ unsigned long SightplusAttackPower;
	/* this+ 76 */ unsigned long PlusDefencePowerInAcolyte;
	/* this+ 80 */ unsigned long HPPartyNotifyTime;
	/* this+ 84 */ unsigned long LastNPCEventAnswerTime;
	/* this+ 88 */ unsigned long LastClientTime;
	/* this+ 92 */ int ChangeSpeed;
	/* this+ 96 */ int ChangeSpeedTime;
	/* this+100 */ unsigned long HSvrAliveTime;
};


struct PLUSSTATUS_BYJOB
{
	/* this+ 0 */ int Str;
	/* this+ 4 */ int Int;
	/* this+ 8 */ int Dex;
	/* this+12 */ int Agi;
	/* this+16 */ int Luk;
	/* this+20 */ int Vit;
};


struct PCBANG_INFO
{
	/* this+ 0 */ BOOL isPCBang;
	/* this+ 4 */ int PayType;
	/* this+ 8 */ int ConnectionArea;
	/* this+12 */ int ConnectionState;
	/* this+16 */ int EventNum;
	/* this+20 */ unsigned long ConnectionTime;
	/* this+24 */ float ExpFactor;
	/* this+28 */ float ExpFactor2;
	/* this+32 */ float DropFactor;
	/* this+36 */ int NotifyToClientCnt;
	/* this+40 */ int PremiumType;
	/* this+44 */ int PremiumType2;
};


struct EXCHANGEITEM_INFO
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ int isPermited;
	/* this+8 */ int isConcluded;
};


struct PARTNER_INFO
{
	/* this+0 */ BOOL bMarried;
	/* this+4 */ unsigned long partnerGID;
	/* this+8 */ char partnerName[24];
};


struct FAMILY_INFO
{
	/* this+ 0 */ int familyIndex;
	/* this+ 4 */ BOOL bMarried;
	/* this+ 8 */ short expOption;
	/* this+12 */ unsigned long father;
	/* this+16 */ char fatherName[24];
	/* this+40 */ unsigned long mother;
	/* this+44 */ char motherName[24];
	/* this+68 */ unsigned long baby;
	/* this+72 */ char babyName[24];
};


struct BATTLEFIELDINFO
{
	/* this+0 */ char campID;
	/* this+2 */ short xPos1;
	/* this+4 */ short yPos1;
	/* this+6 */ short xPos2;
	/* this+8 */ short yPos2;
};


struct PVPSCORE_INFO
{
	/* this+ 0 */ int GID;
	/* this+ 4 */ int AID;
	/* this+ 8 */ int WinTime;
	/* this+12 */ char MapName[16];
};


struct CollideInfo
{
	/* this+0 */ std::vector<CCharacter*>* sectionList;
	/* this+4 */ int count;
};


struct MannerPointData
{
	/* this+0 */ unsigned long otherGID;
	/* this+4 */ unsigned long type;
};


struct MannerPointInfo
{
public:
	void Init(CPC* pc);
	void Reset();
	unsigned long IsGivableMP(unsigned long otherGID);
	int LoadMPInfo();
	void InsertNewMP(unsigned long otherGID, int type);

private:
	BOOL SearchOtherCharacter(unsigned long otherGID);
	int GetSize();
	int DeleteFirstRecord();

private:
	/* this+ 0 */ int m_lastTimeGivingMP;
	/* this+ 4 */ std::list<MannerPointData> m_info;
	/* this+16 */ CPC* m_owner;
};


class CPC : public CActor
{
public:
	enum
	{
		MOVE_STOP_OPT_1 = 1,
		MOVE_STOP_OPT_2 = 2,
		MOVE_STOP_OPT_3 = 4,
		MOVE_STOP_OPT_4 = 8,
		MOVE_STOP_OPT_5 = 16,
	};

public:
	bool AsyncMonopolyProcess();
	AsyncMonopolyProcess::enumType GetAsyncMonopolyProcessType() const;
	bool SetAsyncMonopolyProcess(std::tr1::shared_ptr<CAsyncMonopolyProcess>& in_Amp);
	bool RemoveAsyncMonopolyProcess(const AsyncMonopolyProcess::enumType in_Type); //TODO
private:
	/* this+1276 */ std::tr1::shared_ptr<CAsyncMonopolyProcess> m_AsyncMonopolyProcessPtr;

public:
	const char* GetNamePtr() const;
	int SkillAttackExt(SKILLATTACK_MSG* , int , int , const bool ); //TODO
	const int GetMapID() const;
	const char* GetMapName(); //TODO
	void ForceMapMove_To_RestartMap();
	bool IsPartyJoinMSGRefuse() const;
	bool IsOpenEquipmentWin() const;

public:
	enum enumDisconnectStep
	{
		DISCONNECTSTEP_NONE                  = 0,
		DISCONNECTSTEP_ARRANGE               = 1,
		DISCONNECTSTEP_ASYNCDB_SAVE_REQUEST  = 2,
		DISCONNECTSTEP_ASYNCDB_SAVE_WAIT     = 3,
		DISCONNECTSTEP_ASYNCDB_SAVE_COMPLETE = 4,
		DISCONNECTSTEP_COMPLETE              = 5,
		DISCONNECTSTEP_REMOVE                = 6,
	};
private:
	/* this+1284 */ enumDisconnectStep m_DisconnectStep;
public:
	void SetDisconnectStep(const enumDisconnectStep in_Step);
	const enumDisconnectStep GetDisconnectStep() const;

public:
	CPCClientUpdater* GetClientUpdaterPtr();
	void AsyncSaveBodyItem();
	void AsyncSaveCart();
	void AsyncSaveCharacterInfo(const int in_callfunc);
	void AsyncLoadStore();
	void OnCM_NOTIFY_STOREDITEM();
	void AsyncSaveStore(const bool in_bCloseStore);
	void AsyncLoadCart(CCharacter* const in_pSender);
	void AsyncSaveALL_AFTER_ACTION_NONE();
	void AsyncSaveALL_AFTER_ACTION_ANYTIME();
	void AsyncSaveALL_AFTER_ACTION_XXX();
	void AsyncDBComplete_LoadCart(int in_SKLevel, const unsigned char* in_pData, int in_Length);
	int GetStoreItemDBFormat(unsigned char* out_pBuffer, const int in_MaxBytes);
	void StoreItemReset();
	int GetBodyItemSize(); //TODO

private:
	/* this+1288 */ CPCHireItemCtrl m_HireItemCtrl;

public:
	void GetDBInfo(const int in_callfunc, CHARINFO_TO_CHARACTERDB& io_DBInfo);
	IVItItem* SearchItemByUniqueIdentityNum(const enumInventoryType in_InventoryType, const __int64 in_UID);
	void HireItemCheckAdd(const enumInventoryType in_InventoryType, IVItItem* in_pItem);
	void TransferSKILLtoPARTYmember(CCharacter* const in_TransferCH, const int in_SKID, const int in_SKLevel, const int in_EFST, const int in_EFST_Time, const int in_EFST_Value);
	void MercenaryCall_Create_After(const int in_Job);
	void MercenaryCall_Delete_After(const int in_reason);

public:
	/* this+1312 */ CPCElemental m_Elemental;

public:
	virtual int GetAdditionalSkillSPCost(const int in_SkillID);
	void SendPVPPoint(); // not implemented
	int GetCountOfMyNameItem(int item);
	void SetBanTime(DWORD time);
	DWORD GetBanTime();

public:
	CPC();
	virtual ~CPC();
	void Init(CAsyncStream* stream, DWORD ip);
	void GameGuardInit();
	int OnProcess();
	virtual unsigned long GetAccountID();
	const char* GetAccountName() const;
	BOOL IsMapType(int MapType);
	virtual int OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	virtual int GetParameterValue(unsigned short id, int& value);
	virtual int UpdateParameterValue(unsigned short id, int value);
	virtual BOOL GetBodyItemCount(unsigned short id, int& value);
	virtual BOOL UpdateBodyItemCount(unsigned short id, int count, bool isidentified);
	virtual IVItItem* UpdateBodyItemCountByNPC(unsigned short id, int count, bool isidentified);
	virtual void InsertCommand(COMMAND_QUEUE* command);
	virtual void DisableCommand(unsigned long commandID);
	virtual void CheckCommandQueue();
	virtual COMMAND_QUEUE* SearchCommand(unsigned long commandID);
	virtual BOOL IsMyArea(CCharacter* ch, int range);
	virtual BOOL IsTarget(CCharacter* ch, unsigned long flag);
	virtual int GetScale();
	virtual void OnMsgFromItemServer(unsigned long AID, CITZMsg* reqMsg);
	void ProcessRegionSkill(int SKID, short range, CCharacter* exceptCH, int par1, int par2); // not implemented
	unsigned short GetItemCount(unsigned short id);
	BOOL GetJustBodyItemCount(unsigned short id, int& value);
	BOOL GetEquipItemCount(unsigned short id, int& value);
	BOOL IsDisconnectable();
	void GetAttackLastTime(time_t& time);
	void SetAttackLastTime(time_t time);
	void GetLastAttackedTime(time_t& time);
	void SetLastAttackedTime(time_t time);
	int GetErrorCount();
	BOOL AddExWhisperList(const char* name);
	BOOL DeleteExWhisperList(const char* name);
	void SettingWhisperState(BOOL flag);
	void GetWhisperList(int& out_StoreLen, char* buf, const int in_nMaxBufSize);
	BOOL SearchWhisperList(const char* name);
	void MulticastDestroyRoom();
	void RoomNewEntry(unsigned long roomID);
	void MulticastRoomNewEntry(unsigned long roomID);
	BOOL IsSendable();
	bool IsSendable2(const int in_Bytes);
	BOOL IsLockOnMode();
	void SetLockOnMode(BOOL flag);
	unsigned long GetTargetAID();
	void SetTargetAID(unsigned long AID);
	void CancelLockOnMode();
	CPacketHandler* GetPacketHandler();
	void Reset();
	virtual unsigned long GetState();
	void SetState(unsigned long state);
	unsigned long GetRoomID();
	void SetRoomID(unsigned long roomID);
	//...
	void NotifyParameter(unsigned long varID, int par1);
	unsigned long GetCharacterID();
	virtual void SkillUseAck(unsigned short SKID, unsigned short NUM, bool result, unsigned char cause);
	int GetJob();
	int GetPureJob();
	int GetCategoryFirstJob();
	static int GetCategorySecondJob(const int in_Job);
	int GetCategorySecondJob();
	int GetCategoryThirdJob();
	//...
	int GetSP();
	//...
	virtual short GetAttackSuccessPercent(CCharacter* other, const int in_SKATKPattern, BOOL isRangeAttack);
	//...
	virtual int GetWeaponProperty(int position, BOOL isArrowProperty);
	//...
	void ReqItemRepair(const REPAIRITEM_INFO& in_TargetItemInfo);
	void ReqWeaponRefine(short index);
	virtual BOOL IsDamageMotionPossible();
	virtual BOOL IsRightProperty(int property);
	//...
	virtual int IsAvoidable(int race, int _class, int level);
	bool IsAvoidableImpl(const int in_race, const int in_class, const bool in_bCheckSpecialHiding);
	//...
	BOOL IsSkillUsable(unsigned short SKID);
	BOOL IsSkillEnable(int SKID, int level, CCharacter* ch);
	//...
	virtual BOOL IsLucky();
	//...
	int GetPlusAttRange();
	virtual void SetEffectStateTimeInfo(DWORD time, int state);
	void SetBodyStateTimeInfo(unsigned long firstTime, unsigned long secondTime, int state);
	//...
	int GetAttackHasteValue1();
	int GetAttackHasteValue2();
	//...
	int GetBodyMaxItemWeight();
	//...
	int GetStoreMaxItemSize();
	int GetBodyItemWeight();
	//...
	BOOL IsMyPartyMember(unsigned long AID);
	BOOL IsPKModeON();
	BOOL IsRightForm(int SKID, int xPos, int yPos, int param);
	//...
	virtual void SetEffectState(int state);
	//...
	virtual void ResetHealthState(short state);
	//...
	virtual void ModifyAttackPowerByEffective(CCharacter* ch, int attackProperty, int& damage);
	void SetSpellCasting(unsigned short SKID, short skLevel);
	unsigned short GetSpellCasting();
	//...
	void NotifySpiritsInfo();
	//...
	void NotifyUseSkill(unsigned short SKID, unsigned long targetAID, unsigned long srcAID, short level, bool result);
	//...
	short GetDexValue();
	short GetStrValue();
	short GetIntValue();
	short GetLukValue();
	short GetAgiValue();
	short GetVitValue();
	//...
	BOOL IsValid();
	void SetValid(const BOOL flag);
	virtual int GetEffectState();
	//...
	void NotifyArrowEquiped(unsigned short index);
	CITP* GetITPEquipedWeapon();
	short GetEquipedWeaponType();
	BOOL ConsumeItem(unsigned short itmNum, int count, IVItItem* p, const short in_DeleteType);
	BOOL ConsumeItemForSkill(unsigned short itmNum, int count);
	//...
	int GetMaxHP();
	short GetMaxSP();
	int GetAttackMotionTime();
	int GetAttackedMotionTime();
	//...
	virtual void Send(int len, const char* buf);
	bool Send2(const unsigned char* , const int ); //TODO
	void ForceSend(int len, char* buf);
	void OnDispatchClientRequest(Request* request);
	//...
	void ParseDBFmtStoreItemData(const int in_Length, const unsigned char* in_pData);
	//...
	void AddMoney(int money);
	void DeleteMoney(int money);
	int GetMoney();
	//...
	double GetAttackDistance();
	void NotifyAttackRange();
	//...
	virtual void ResetEffectState(int state);
	void InitEnemyInfo();
	void InsertEnemyInfo(ENEMY_INFO* enemyInfo);
	void UpdateEnemyInfo();
	ENEMY_INFO* SearchEnemyInfo(unsigned long AID);
	//...
	virtual BOOL IsInitingState();
	//...
	CAsyncStream* GetStream();
	CharacterInfo* GetCharacterInfo();
	CPCBattle* GetPCBattle();
	//...
	int GetPVPWinPoint();
	void SetPVPWinPoint(int pvpWinPoint);
	void UpdatePVPWinPoint(int winpvpWinPoint);
	void SetPVPRanking(int ranking);
	int GetPVPRanking();
	void SetPVPTotal(int total);
	int GetPVPTotal();
	//...
	virtual BOOL IsSiegeMode();
	//...
	BOOL IsReadyToSave();
	BOOL ModifyMoney(int money);
	//...
	void SetEventNo(int n);
	int GetEventNo();
	//...
	void OnEnableItemMove(BOOL event);
	void OnDisableItemMove();
	//...
	void CheckWeaponState();
	char* GetCharacterName();
	//...
	char* GetGuildName();
	//...
	virtual void OnShowEffect(int effect);
	virtual void OnShowEffect3(int effect, int numdata);
	virtual void OnShowScript(const char* In_Msg);
	//...
	bool Divorce();
	void NotifyDivorce(unsigned long gid, char* partnerName);
	void DeleteMarriagering();
	PARTNER_INFO* GetMarriedInfo();
	//...
	void SetLastTargetAID(unsigned long aid);
	unsigned long GetLastTargetAID();
	//...
	void OnMakeFamily(unsigned long gid1, unsigned long gid2);
	//...
	PCBANG_INFO* GetPcBangInfo();
	BOOL IsPcBang();
	//...
	void SetLessEffect(BOOL bValue);
	BOOL GetLessEffect();
	//...
	char* GetRestartMapName();
	BOOL IsSkillEnableMapProperty(int SKID);
	//...
	BOOL PutInventoryBinaryItem(char* ItemBuffer, int ItemLen);
	//...
	BOOL isBodyAddMailItem(unsigned short ITID, unsigned long ItemType, int count, EQUIPSLOTINFO slotInfo, __int64 UniqueSerialNum);
	//...
	void SetLastOpenMailName(char* FromName);
	//...
	virtual void ReduceSPByUseSkill(int sp);
	virtual bool IsExistItem(int itemID, int count, bool isExternalEffect);
	virtual bool ConsumeItemByUseSkill(int itemID, int count, bool isExternalEffect);
private:
	int GetAttackFinalDamage(CCharacter* other, int position, int skillProperty, int plusATTPowerPercent, int plusATTSuccessPercent, int type, BOOL isRangeAttack, unsigned short SKID, short skLevel);
public:
	virtual int GetAttackFinalDamage(ATTACK_INFO* info);
	virtual int GetModifiedTargetItemDEF(CCharacter* target);
private:
	virtual int GetModifiedTargetItemMDEF2(CCharacter* in_cpTargetCH);
public:
	virtual int GetModifiedTargetItemMDEF(CCharacter* target);
	virtual void ApplyExtraDEF(int& def, CCharacter* in_cpAtkerCH);
	virtual void ApplyExtraMDEF(int& def);
	virtual int SetEffective(int index, int time, int val1, int val2, int val3, int isSendClient);
	virtual void ResetEffective(int index, int val);
	virtual bool IsGroundEffective(int index, int& SKID, bool& isPlaySolo);
	virtual void ProcessGroundEffective(int index, int SKID, bool isPlaySolo);
	virtual void SetOnShowEFST(int value);
	virtual void SetOffShowEFST(int value);
	virtual void OnChangeStatusAmount(int SKID, unsigned short type, unsigned long time, int amount);
	virtual void NotifyStatusAmount(unsigned short type, int amount);
	bool IsDeadState();
	//...
	virtual short GetHealthState();
	virtual short GetBodyState();
	short GetExtDodgePercent();
	short GetPerfectExtDodgePercent(); // not implemented
	short GetPlusHitPercent();
	//...
	virtual char GetCampID();
	virtual void SetCampID(char campID);
	//...
	void UpdateBattleFieldRespawnPoint2(short xPos, short yPos);
	void MoveToBattleFieldRespawnPoint(short RP_No, unsigned long npcID);
	//...
	void OnStopedProgress();
	//...
public:
	void SendQuestNotifyEffect(unsigned long npcID, short xPos, short yPos, short effect, short type);
	//...
private:
	//...
	void DispatchCommand(int par);
	void ResetCommandQueue();
	void DisableAllCommand();
	//...
	void MultiCastStateInfo();
	//...
	void DeleteCommand(unsigned long commandID);
	//...
	void OnUseSkill(int SKID, int target, int level, int spCost);
	void OnUseGroundSkill(int par1, int par2, int skLevel, int spCost);
	//...
private:
	//...
	void CancelCasting(BOOL flag);
	//...
	void AM_ReqMakingHomun();
	//...
	virtual int SkillAttack(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bSilenceSkill);
	//...
public:
	virtual short SplashAttack(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count);
private:
	virtual BOOL SplashAttack2(int in_plusATTPower, PosInfo in_dest, int in_type, int in_halfWidth, int in_height, MSG_TYPE1_TWODWORD* in_pMsgData, int in_count, int in_plusHitPercent, PosInfo* in_pspecialSrc);
	void SplashAttack3(int plusATTPower, PosInfo dest, int type, MSG_TYPE1_TWODWORD* msgData, int range, int count);
	void CollideSplashAttack(int plusATTPower, CCharacter* src, CCharacter* other, int destDir, int type, unsigned short SKID, int count, std::map<CCharacter*,CollideInfo>& collidedList);
	//...
	void OnStarPlaceRemember(int par1, int par2, int par3);
	//...
	void OnIncCarry(int amount);
	void OnIncCarry2(int par1, int par2, int par3);
	//...
public:
	void OpenSearchStoreInfo(const int OpenType, const int Count);
	void ClearSearchStoreInfo();
	void SetSSI_LimitSearchCnt(const int LimitSearchCnt);
	const int GetSSI_LimitSearchCnt();
	const int GetSSI_OpenType();
	//...
	IVItItem* OnAddItem(int ID, int type, int par, int Hour, bool isUniqueIdentityNumV2, const int in_TimeType);
	//...
public:
	//...
	short GetCurrentState();
	void SetBodyState(short state);
	virtual void SetHealthState(short state);
	void SetCurrentState(short state);
	void AddGroupMember(unsigned long AID);
	void DeleteGroupMember(unsigned long AID);
	void ResetGroupMember();
	virtual void DetectHidingCharacter(int range, SKILLATTACK_MSG* msg, int plusAttPower, int deltaX, int deltaY);
	//...
private:
	//...
	void GetSplashCells2(PosInfo src, PosInfo dest, int height, PosInfo* result);
	//...
	void NotifyDeleteItemFromBody(const unsigned short in_Index, const short in_Count, const short in_DeleteType);
	void InitTime();
	//...
	void MoveItem(unsigned char type, short index, int count);
	//...
public:
	void GetEfstListDBFmt_And_UpdateResetFlag(std::vector<Effect3rd::tagEffect3rdDBFmt>& io_List, const bool in_bKeepDeleteDBWhenResetFlag);
	//...
	virtual void SetSkillSinglePostDelay(unsigned short SKID, unsigned long delaytime);
	//...
	void NC_MAGICDECOY_operate(const int selectedItemID);
	//...
	int GetPhysicsFinalDamage(CCharacter* in_cpTarget, int in_WeaponPosition, int in_ATKProperty, int in_PlusATKPercent, int in_PlusHITPercent, int in_CalculateDamageType, BOOL in_IsRangeAttack, unsigned short in_SKID, short in_SKLevel);
	//...
	BOOL SkillAttack_Manual(SKILLATTACK_MSG* in_pMsg, const int in_PlusATKPercent, const int in_PlusHITPercent);
private:
	//...
	bool IsCancelCasting();
	//...
	void GC_POISONINGWEAPONoperation(const int in_itemID);
	//...
public:
	//...
	CNpcElemental* GetNpcElemental() const;
	//...
public:
	void WL_READING_SBoperation(const int in_itemID);
	//...
	virtual bool IsRightWeaponItemClass(short class1, short class2, short class3);
	//...
	void SetMapLoadingFlag(BOOL bFlag);
	void SetAuctionOpenFlag(BOOL bFlag); //TODO
	void SetMailOpenFlag(BOOL bFlag); //TODO
	BOOL isAuctionOpen();
	BOOL isMailOpen();
	void AuctionOpen();
	void MailOpen();
	//...

private:
	/* this+1320 */ bool m_bWorldEntrance;
	/* this+1321 */ unsigned char m_MaxItemCnt_BuyingStore;
	/* this+1324 */ int m_SSI_LimitSearchCnt;
	/* this+1328 */ int m_SSI_OpenType;
	/* this+1332 */ BYTE m_1332[588];
public:
	/* this+1920 */ std::list<int> m_captureItemList;
	/* this+1932 */ int m_useIncubator;
	/* this+1936 */ bool m_isPetOwner;
	/* this+1940 */ CharacterInfo m_characterInfo;
	/* this+3044 */ CharacterTimeInfo m_characterTimeInfo;
	/* this+3148 */ PLUSSTATUS_BYJOB m_plusStatusByJob;
	/* this+3172 */ CPollTimer m_emoticonTM;
	/* this+3180 */ BOOL m_isMapLoading;
	/* this+3184 */ unsigned long m_MapLoadingTick;
	/* this+3188 */ int m_invalidPacket;
private:
	/* this+3192 */ BOOL m_isValid;
	/* this+3196 */ PCBANG_INFO m_PCBangInfo;
public:
	/* this+3244 */ BOOL m_isPKModeON;
	/* this+3248 */ int m_index;
	/* this+3252 */ unsigned long m_ip;
	/* this+3256 */ unsigned long m_lastNPCAID;
	/* this+3260 */ short m_npcTouchCount;
	void SetLastCardIndex(short index);
	short GetLastCardIndex();
	/* this+3262 */ short m_lastCardIndex;
	/* this+3264 */ BOOL m_isItemMovable;
	/* this+3268 */ BOOL m_isAuctionOpen;
	/* this+3272 */ BOOL m_isMailOpen;
	/* this+3276 */ int m_isTraderOpen;
	/* this+3280 */ std::list<unsigned long> m_groupMember;
	/* this+3292 */ std::map<std::string,unsigned long> m_whisperExRegister;
	/* this+3308 */ CHostPathInfo m_pathInfo;
	/* this+3364 */ CPCClientUpdater m_pcClientUpdater;
	/* this+3376 */ CPCItem m_pcItem;
	/* this+3416 */ CPCItemInventoryMgr m_pcitemInventoryMgr;
	/* this+4280 */ CPCSkill m_pcSkill;
	/* this+4772 */ CPCPacketHandler m_packetHandler;
	/* this+4932 */ CPCBattle m_pcBattle;
	/* this+7652 */ EXCHANGEITEM_INFO m_exchangeItemInfo;
	/* this+7664 */ MannerPointInfo m_mannerPoint;
	/* this+7684 */ std::list<unsigned long> m_touchNPCList;
	/* this+7696 */ std::vector<ENEMY_INFO> m_enemyInfo;
	/* this+7712 */ CPCQuestEvent m_questEvent;
	/* this+7840 */ BYTE m_7840[32];
	/* this+7872 */ int m_skillUseRefCounter;
	/* this+7876 */ int m_lockCounter;
	/* this+7880 */ DWORD m_lastSendTime;
	/* this+7884 */ DWORD m_loadingCompleteTime;
	/* this+7888 */ DWORD m_DisconnetTime;
	/* this+7892 */ int m_pvpWinPoint;
	/* this+7896 */ int m_pvpRanking;
	/* this+7900 */ unsigned long m_pvpFGStratTime;
	/* this+7904 */ int m_pvpTotal;
	/* this+7908 */ int m_myPetID;
	void SetMyPetID(int ID);
	int GetMyPetID();
	/* this+7912 */ bool m_isProgress;
	/* this+7916 */ unsigned long m_gageRefreshTime;
	/* this+7920 */ int m_eventNo;
	/* this+7924 */ BOOL m_makingItemFlag;
	/* this+7928 */ std::list<unsigned long> m_devotionList;
	/* this+7940 */ unsigned long m_magicTargetAID;
	/* this+7944 */ PARTNER_INFO m_marriageInfo;
	/* this+7976 */ int m_specialSP;
	/* this+7980 */ BOOL m_specialDeath;
	/* this+7984 */ std::map<unsigned long,unsigned long> m_invincibleInfo;
	/* this+8000 */ unsigned long m_lastTargetAID;
	/* this+8004 */ BYTE m_8004[80];
	/* this+8084 */ FAMILY_INFO m_familyInfo;
	/* this+8180 */ BYTE m_8180[24];
	/* this+8204 */ int m_isLessEffect;
	/* this+8208 */ BYTE m_8208[84];
	/* this+8292 */ CCSAuth2 m_GameGuardAuth;
	/* this+8336 */ BOOL m_isSetGameGuard;
	/* this+8340 */ DWORD m_lastGameGuardCheckTime;
	/* this+8344 */ BYTE m_8344[76];
	/* this+8420 */ short m_cookSucc_Tool;
	/* this+8424 */ BYTE _padding[2]; BYTE m_8424[40];
	/* this+8464 */ CPCProperty* m_pcproperty;;
	/* this+8468 */ BATTLEFIELDINFO m_battleFieldInfo;
	/* this+8480 */ long m_clientVersion;
	/* this+8484 */ BOOL isInitSendGameGuard;
	/* this+8488 */ int m_CashPoint;
	/* this+8492 */ int m_itemScriptEventNo;
	/* this+8496 */ bool m_isSetEffectiveBySpecialItem;
	/* this+8500 */ unsigned long m_scrollItemIndex;
	/* this+8504 */ bool m_open_simpleCashShop;
	/* this+8508 */ BYTE m_8508[20];

public:
	void ScriptTimeClear();
	void SetScriptTime(int key);
	int GetScriptTime(int key);
private:
	/* this+8528 */ std::map<int,unsigned long> m_scriptTimeMap;

private:
	/* this+8544 */ int m_seCashPoint;
	/* this+8548 */ bool m_Open_SeSimpleCashShop;

private:
	/* this+8552 */ CHPAmount m_HPAmount;
	int HPAmountAdd(const int in_Amount); //TODO
	void HPAmountSetForce(const int in_Amount); //TODO
	void HPAmountSet(const int in_Amount); //TODO

private:
	/* this+8564 */ CSPAmount m_SPAmount;
	void SPAmountAdd(const int in_Amount); //TODO
	void SPAmountSetForce(const int in_Amount); //TODO
	void SPAmountSet(const int in_Amount); //TODO

public:
	int HPAmountGet(); //TODO
	int SPAmountGet(); //TODO

public:
	virtual int GetSPcostForSkill(const int in_SKID, const int in_SKLevel, const int in_SKType, CSkillTypeInfo* in_cpSKTypeInfo);

	friend class CPCClientUpdater; // SetIndex()
	friend class CPCFriendClass;
	friend class CPCPacketHandler; // DispatchPacket()
	friend class CPCSkill;
};
C_ASSERT( sizeof CPC == 8576 );
