#pragma once
#include "NPC.h"
#include "shared/PollTimer.h"


struct BOSS_INFO
{
	void Init(int xPos, int yPos)
	{
		this->isBossInMap = false;
		this->lastNotifyPositionX = xPos;
		this->lastNotifyPositionY = yPos;
		this->lastNotifyTime = 0;
		this->isDead = false;
		memset(&this->regenSystemTime, 0, sizeof(this->regenSystemTime));
		this->regenTime = 0;
//		this->regenTerm = 0;
		this->pcList.clear();
	}
	
	/* this+ 0 */ bool isBossInMap;
	/* this+ 4 */ int lastNotifyPositionX;
	/* this+ 8 */ int lastNotifyPositionY;
	/* this+12 */ unsigned long lastNotifyTime;
	/* this+16 */ bool isDead;
	/* this+18 */ SYSTEMTIME regenSystemTime;
	/* this+36 */ unsigned long regenTime;
	/* this+40 */ unsigned long regenTerm;
	/* this+44 */ std::list<int> pcList;
};


class CNpcMob : public CNPC
{
public:
	CNpcMob();
	virtual ~CNpcMob();

public:
	virtual void Reset();
	virtual void OnProcess();
	virtual int OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	int GetInvincibleTimeInfo(int skillID);
	int ChkGndSkillDurability();
	void SetEffectByGospel(CCharacter* ch);
	void ResetEffectByGospel(int value);
	void ResetEffectiveByDispel();
	int GetMonsterDBDef();
	int GetMonsterDBMdef();
	short CheckBossEnableRegen();
	enum
	{
		BOSSREGEN_NOT_BOSS = 0,
		BOSSREGEN_NOT_YET  = 1,
		BOSSREGEN_PERMIT   = 2,
	};
	void GetBossRegenSystemTime(unsigned long& hour, unsigned long& minute);
	bool IsBossInMap();
	void SetBossRegenTime(const unsigned long in_AfterTime);
	virtual int GetRevivalTerm();

protected:
	virtual void InitCore();

private:
	void OnHealHP(int par1);
	void OnDecreaseDef(CCharacter* sender, int par1);
	void OnSetBossInMap();
//	void OnRequestBossInfo(CCharacter* sender);
//	void OnReqAddBossPCList(CCharacter* sender);
//	void OnReqDelBossPCList(CCharacter* sender);
//	void OnBlessingFromAcolyte(CCharacter* sender, int par1, int par2, int par3);
//	void OnCureFromAcolyte();
//	void OnResurrection(int healPercent);
//	void SetInvincibleTimeInfo(unsigned long time, int skillID);
//	void SetBodyStateTimeInfo(unsigned long firstTime, unsigned long secondTime, int state);
	void UpdateBossInfo();
	char* GetBossInfo(bool isWithMsg);

private:
	/* this+   0 */ //CNPC baseclass_0;
	/* this+2104 */ CPollTimer m_stateTimer;
	/* this+2112 */ BOSS_INFO m_bossInfo;
	/* this+2168 */ int m_SvrScriptAppID;

public:
	void SetSvrScriptAppID(int in_SvrScriptAppID);
	int GetSvrScriptAppID();

private:
	void CreateMobTomb(const unsigned int in_KillerAID);
};
