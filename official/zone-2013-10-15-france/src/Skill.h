#pragma once
#include "Character.h"
#include "Rect.h"
#include "Struct.h"


struct SKILL_TIME_INFO
{
	/* this+0 */ unsigned long lastHPMinusTime;
};


struct SKILL_INFO
{
	/* this+ 0 */ short xPos;
	/* this+ 2 */ short yPos;
	/* this+ 4 */ unsigned long operateTime;
	/* this+ 8 */ unsigned long expiredTime;
	/* this+12 */ unsigned long birthTime;
	/* this+16 */ unsigned long creatorAID;
	/* this+20 */ unsigned long state;
	/* this+24 */ unsigned long MoveReqLastTime;
	/* this+28 */ int hp;
	/* this+32 */ unsigned char job;
	/* this+36 */ int originalJob;
	/* this+40 */ short level;
	/* this+44 */ PosInfo creatorPos;
};


class CSkill : public CCharacter
{
public:
//	const char* GetNamePtr();
//	void ModifyDamage_ATKED(class CCharacter *, int &, int, int, int, int);
//	void ModifyDamage(int &, int, int, class CCharacter *, unsigned short);
//	unsigned int GetGroupUniqueID();

public:
//	CSkill();
//	virtual ~CSkill();

public:
//	void Init2(const unsigned int, short, short, class CMapRes *, unsigned char, unsigned long, unsigned long, short, unsigned short, int, int, const char);
//	int IsTarget(class CCharacter *, unsigned long);
//	unsigned long GetState();
	int OnProcess();
//	void CheckStateChange();
//	unsigned long GetAccountID();
//	void SetTargetAccountID(unsigned long);
//	unsigned long GetTargetAccountID();
//	void SetAccountID(unsigned long);
//	int OnMsg(class CCharacter *, class CCharacter *, unsigned long, int, int, int, class MSGpar::CVar);
//	void InsertCommand(struct COMMAND_QUEUE *);
//	void CheckCommandQueue();
//	void DisableCommand(unsigned long);
	bool IsMyArea(const int in_xPos, const int in_yPos);
//	int IsMyArea(class CCharacter *, int);
//	unsigned long GetCreatorAID();
//	void UpdateSkill(class std::vector<CCharacter *,std::allocator<CCharacter *> > *);
//	void NotifyUpdateInfo(class CPC *);
//	void NotifyUpdateSkillInfo();
	void OnDisappear();
//	void SetWarpMapName(char *);
	short GetxPos();
	short GetyPos();
//	int GetJob();
//	unsigned int GetRadiusRange();
//	int GetParameterValue(unsigned short, int &);
//	int UpdateParameterValue(unsigned short, int);
	unsigned short GetSKID();
//	void SetSKID(unsigned short);
//	void SetWarpXPos(short);
//	void SetWarpYPos(short);
//	void SetExpireTime(unsigned short);
//	int IsVisible();
	int GetSkillLevel();
//	int IsPossibleCreateSkill(const unsigned long, const unsigned short, const int, const short, const short, class CMapRes * const, unsigned long &);
//	int GetCreatorXPos();
//	int GetCreatorYPos();
//	void SetTalkBoxcontents(char *);
//	char* GetTalkBoxcontents();
//	void SetTrapState(int);
//	int GetTrapState();
//	int IsTrap();
//	CCharacter* GetMasterCharacter();
	unsigned long GetExpireTime();
//	static bool IsIgnoreLANDPROTECTOR(unsigned short);
//	void ProcessTrapTouched(const int, const int);
//	static bool IsAvailableReflectDamage(const unsigned short);

private:
//	void OnExpired();
//	void InitThePCCacheInfo(int);
//	void DispatchCommand(int);

private:
	/* this+   0 */ //CCharacter baseclass_0;
	/* this+ 888 */ char m_Name[24];
	/* this+ 912 */ unsigned long m_AID;
	/* this+ 916 */ int m_mapID;
	/* this+ 920 */ unsigned short m_SKID;
	/* this+ 922 */ unsigned short m_reactSKID;
	/* this+ 924 */ SKILL_INFO m_skillInfo;
	/* this+ 980 */ SKILL_TIME_INFO m_skillTimeInfo;
	/* this+ 984 */ int m_warpSize;
	/* this+ 988 */ int m_expiredCount;
	/* this+ 992 */ short m_warpXPos;
	/* this+ 994 */ short m_warpYPos;
	/* this+ 996 */ char m_warpMapName[16];
	/* this+1012 */ int m_property;
	/* this+1016 */ int m_trapState;
	/* this+1020 */ CCharacter* m_master;
	/* this+1024 */ unsigned long m_targetAID;
	/* this+1028 */ char m_talkBoxContents[80];
	/* this+1108 */ int m_fireWallIndex;
	/* this+1112 */ int m_visible;
	/* this+1116 */ unsigned int m_GroupUniqueID;
	/* this+1120 */ unsigned int m_RadiusRange;

private:
//	void UpdateNeighborhood();
//	void ProcessNeighborhood();
//	void ProcessCollision();
//	void ProcessWarpPortal();

private:
	struct tagPVAR_AB_EPICLESIS
	{
		enum enumStep
		{
			STEP_NONE         = 0,
			STEP_RESURRECTION = 1,
			STEP_DETECT       = 2,
			STEP_DETECT_NEXT  = 3,
		};

		/* this+0 */ enumStep step;
		/* this+4 */ unsigned long changeTM;
	};

	struct tagPVAR_GC_POISONSMOKE
	{
		/* this+0 */ int poisoningweaponType;
		/* this+4 */ unsigned long changeTM;
	};

	struct tagPVAR_WL_EARTHSTRAIN
	{
		/* this+ 0 */ int moveCnt;
		/* this+ 4 */ int movedx;
		/* this+ 8 */ int movedy;
		/* this+12 */ unsigned long CellReachTM;
		/* this+16 */ int CellMoveTM;
	};

private:
	union {
	/* this+1124 */ tagPVAR_AB_EPICLESIS m_PVAR_AB_EPICLESIS;
	/* this+1124 */ tagPVAR_GC_POISONSMOKE m_PVAR_GC_POISONSMOKE;
	/* this+1124 */ tagPVAR_WL_EARTHSTRAIN m_PVAR_WL_EARTHSTRAIN;
	};

private:
//	void OnProcess_AB_EPICLESIS();
//	void OnProcess_WL_EARTHSTRAIN();
public:
	CMyRect GetArea() const;
//	void GN_WALLOFTHORN_fire();
private:
//	void OnProcess_SC_FEINTBOMB();
//	void OnProcess_WM_SEVERE_RAINSTORM();
};
C_ASSERT( sizeof CSkill == 1144 );
