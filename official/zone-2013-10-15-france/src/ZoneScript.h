#pragma once


enum MYCHECK_TYPE
{
	CHECK_LOCALBROADCAST    = 0,
	CHECK_BROADCAST         = 1,
	CHECK_DISCONNECTCHAR    = 2,
	CHECK_DISCONNECTALLCHAR = 3,
	CHECK_ITEMCREATE        = 4,
	CHECK_ITEMCREATE2       = 5,
	CHECK_ADMINMAPMOVE      = 6,
	CHECK_RESETPARAMETER    = 7,
	CHECK_CHANGEMAPTYPE     = 8,
	CHECK_CHANGEEFFECTSTATE = 9,
	CHECK_GIVEMANNERPOINT   = 10,
	CHECK_MOVEAID           = 11,
	CHECK_CALLAID           = 12,
	CHECK_CALLGID           = 13,
	CHECK_SHIFT             = 14,
	CHECK_ADMINISTRATOR     = 15,
	CHECK_ITEM_RESTRICT     = 16,
	CHECK_REQ_STATUS        = 17,
	CHECK_FORCEWHISPER      = 18,
	CHECK_GMDEFANS          = 19,
	CHECK_MAX_NUM           = 20,
};


enum
{
	ITMGROUP_ORE            = 1,
	ITMGROUP_GEM            = 2,
	ITMGROUP_HEAL           = 3,
	ITMGROUP_FOOD           = 4,
	ITMGROUP_GEM_KINGPORING = 5,
	ITMGROUP_LAST           = 6,
};


struct extraITMInfo
{
	/* this+0 */ unsigned short id;
	/* this+2 */ unsigned short num;
};


struct SummonMobList
{
	/* this+0 */ int num;
	/* this+4 */ std::list<unsigned long> summonMob;
};


struct MIN_MAX
{
	/* this+0 */ short min;
	/* this+2 */ short max;
};


struct STAT_PLUSTABLE
{
	/* this+ 0 */ struct MIN_MAX maxHP;
	/* this+ 4 */ struct MIN_MAX maxSP;
	/* this+ 8 */ struct MIN_MAX Str;
	/* this+12 */ struct MIN_MAX Int;
	/* this+16 */ struct MIN_MAX Vit;
	/* this+20 */ struct MIN_MAX Dex;
	/* this+24 */ struct MIN_MAX Agi;
	/* this+28 */ struct MIN_MAX Luk;
};


struct AttrAttackInfo
{
	/* this+0 */ int val[10][10];
};


class CAttackPlusPowerInfo
{
public:
	CAttackPlusPowerInfo();
	virtual ~CAttackPlusPowerInfo();

public:
	void Init(const char* filename);
	void LoadScript(const char* filename, int verDate);
	int GetAttackPlusPowerByProperty(int defState, int atkState);
	void GetAttackPlusPowerByProperty(int defState, int atkState, int& result);
	int GetAttackPlusPowerByProperty_Variation(int defState, int atkState, int in_damage);
	int GetpropertyID(char* name);
	void Reset();

private:
	/* this+   4 */ AttrAttackInfo m_info[5];
	/* this+2004 */ std::map<std::string,int> m_propertyName;
};


class CZoneScript
{
public:
	CZoneScript();
	~CZoneScript();

public:
	void Init();
	void Reset();
	std::map<unsigned short,std::vector<extraITMInfo>> GetMakingArrowItemInfo();
	std::map<unsigned short,std::vector<extraITMInfo>> GetMakingElementalInfo();
	std::map<unsigned short,std::vector<extraITMInfo>> GetMakingCookInfo(short level);
	BOOL SearchID(char* id, MYCHECK_TYPE func);
	int GetAtkPlusPWByProperty(int defState, int atkState);
	void GetAtkPlusPWByProperty(int defState, int atkState, int& result);
	int GetAtkPlusPWByProperty_Variation(int defState, int atkState, int in_damage);
	void LoadMetamorphosisInfo();
	SummonMobList* GetMetamorphosis(unsigned long spriteType);
	void LoadSummonSlaveInfo();
	SummonMobList* GetSummonSlaveList(unsigned long spriteType);
	void LoadSummonMobInfo(const char* filename, std::map<unsigned long,SummonMobList>& summonMobInfo);
	void LoadMobEmotionInfo();
	int GetMobEmotion(unsigned long spriteType);
	void LoadAbracadabraInfo();
	unsigned short GetSkillByAbracadabra(short level);
	unsigned long GetITMFromGroupID(int groupID);
	unsigned long GetCatchAID();
	unsigned long GetRemoveCatchAID();
	BOOL CheckAID(unsigned long AID);

private:
	typedef std::map<short,STAT_PLUSTABLE> HOMUN_STAT_CONTAINER;
	bool LoadHomunStatTable(lua_State* L, const char* in_TblName, const short in_Job, HOMUN_STAT_CONTAINER& io_Tbl);

private:
	/* this+ 0 */ HOMUN_STAT_CONTAINER m_HomunLevelUpTbl;
	/* this+16 */ HOMUN_STAT_CONTAINER m_HomunEvolutionTbl;
	/* this+32 */ HOMUN_STAT_CONTAINER m_HomunMutationTbl;

public:
	const STAT_PLUSTABLE* GetHomunLevelUpStatTable(const int in_Job);
	const STAT_PLUSTABLE* GetHomunEvolutionStatTable(const int in_Job);
	const STAT_PLUSTABLE* GetHomunMutationStatTable(const int in_Job);

private:
	BOOL LoadMakingArrowInfo();
	BOOL Load_MK_ElementalInfo();
	BOOL Load_MK_CookInfo();
	BOOL LoadItemGroupInfo(const char* fileName);
	BOOL LoadHomunInfo(const char* fName);
	BOOL CheckAvaibleID(char* id, MYCHECK_TYPE func);
	void LoadIDTable();
	void ClearIDTable();
	void LoadAIDTable();
	int GetITMGroupID(char* itmName);
	int GetField(lua_State* L, const char* key);

private:
	/* this+ 48 */ std::map<unsigned short,std::vector<extraITMInfo>> m_makingArrowInfo;
	/* this+ 64 */ std::map<unsigned short,std::vector<extraITMInfo>> m_makeElemental;
	/* this+ 80 */ std::map<unsigned short,std::vector<extraITMInfo>> m_makeCook[10];
	/* this+240 */ std::list<std::string> m_idTable[CHECK_MAX_NUM];
	/* this+480 */ std::list<unsigned long> m_aidTable;
	/* this+492 */ CAttackPlusPowerInfo* m_attackPlusPowerInfo;
	/* this+496 */ std::map<unsigned long,SummonMobList> m_metamorphosisInfo;
	/* this+512 */ std::map<unsigned long,SummonMobList> m_summonSlaveInfo;
	/* this+528 */ std::map<unsigned long,int> m_mobEmotionInfo;
	/* this+544 */ std::map<short,std::map<unsigned short,short>> m_abracadabraInfo;
	/* this+560 */ std::map<std::string,int> m_itmGroupName;
	/* this+576 */ std::map<int,std::vector<extraITMInfo>> m_itmGroupInfo;
};
