#pragma once
#include "MonParameterTable.h"
#include "shared/ODBC.h"


struct MONITEMINFO
{
	/* this+ 0 */ char name[24];
	/* this+24 */ int percent;
};


struct MONITEMPERCENT
{
	/* this+0 */ unsigned short ITID;
	/* this+4 */ int percent;
};


struct MONPARAMETER
{
	/* this+  0 */ int aRan;
	/* this+  4 */ int LV;
	/* this+  8 */ int HP;
	/* this+ 12 */ int SP;
	/* this+ 16 */ int str;
	/* this+ 20 */ int Int;
	/* this+ 24 */ int vit;
	/* this+ 28 */ int dex;
	/* this+ 32 */ int agi;
	/* this+ 36 */ int luk;
	/* this+ 40 */ int atk1;
	/* this+ 44 */ int atk2;
	/* this+ 48 */ int def;
	/* this+ 52 */ int exp;
	/* this+ 56 */ int jexp;
	/* this+ 60 */ int inc;
	/* this+ 64 */ int as;
	/* this+ 68 */ int es;
	/* this+ 72 */ int rechargeTime;
	/* this+ 76 */ int attackedMT;
	/* this+ 80 */ int mSpeed;
	/* this+ 84 */ int attackMT;
	/* this+ 88 */ int property;
	/* this+ 92 */ int scale;
	/* this+ 96 */ int _class;
	/* this+100 */ int race;
	/* this+104 */ int mdef;
	/* this+108 */ MONITEMPERCENT itemInfo[8];
	/* this+172 */ char name[24];
	/* this+196 */ int aiType;
	/* this+200 */ int attr;
};


struct MONSPAWN_SETINFO
{
	/* this+0 */ unsigned long spriteType;
	/* this+4 */ unsigned long npcType;
	/* this+8 */ int count;
};


class CMonParameterMgr : public CODBC, public CMonsterParameterTable
{
public:
	CMonParameterMgr();
	virtual ~CMonParameterMgr();

public:
	int GetJob(const char* in_szpMonName) const;
	unsigned long SearchKeyword(const char* keyword);
	void Init(const char* Script);
	MONPARAMETER* GetMonParameter(unsigned long spriteType);
	MONSPAWN_SETINFO* GetMonSpawnInfo(unsigned long spriteType);
	const char* GetMonsterName(unsigned long spriteType);
	int GetMonsterType(unsigned long spriteType);
	bool SetMonsterNameAndAIType(unsigned long spriteType, const char* name, int aiType);

private:
	void Load(const char* , const char* ); // not implemented
	void LoadSpawnInfo();
	void InsertMonParameter(char* , MONPARAMETER* ); // not implemented
	bool LoadMonParameter();
	void LoadMonMakingItem();
	void AddMonParameter(unsigned long spriteType, MONPARAMETER* parameter);
	void Destroy();
	void LoadEventMonParameter();
	void LoadEventMonMakingItem();

private:
	/* this+ 0 */ //CODBC baseclass_0;
	/* this+20 */ //CMonsterParameterTable baseclass_20;
	/* this+56 */ std::map<unsigned long,MONPARAMETER*> m_parameter;
	/* this+72 */ std::map<unsigned long,MONSPAWN_SETINFO> m_spawnSetData;
};
