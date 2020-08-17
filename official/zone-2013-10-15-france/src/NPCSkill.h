#pragma once
class CNPC;


struct NPCSKILLINFO
{
	/* this+ 0 */ int status;
	/* this+ 4 */ unsigned short SKID;
	/* this+ 8 */ int level;
	/* this+12 */ int percent;
	/* this+16 */ int casttime;
	/* this+20 */ unsigned long cooldowntime;
	/* this+24 */ int noDispel;
	/* this+28 */ int ai_type;
	/* this+32 */ int emoticon;
	/* this+36 */ int chatNo;
	/* this+40 */ int condition;
	/* this+44 */ int value;
};


class CNPCSkill
{
public:
	void ForceUseSkill(unsigned short SKID, int skLevel, int castTime, int chatNo);
	void ForceUseSkill(unsigned long in_TargetAID, unsigned short in_SKID, int in_skLevel, int in_castTime, int in_chatNo);

public:
	CNPCSkill();
	virtual ~CNPCSkill();

public:
//	void Init();
//	void SetMyOwner(CNPC* );
	int OnProcess();
//	void OnUseSkill(unsigned short , int , int , int , int );
//	void OnUseGroundSkill(int , MSG_TYPE1_TWODWORD* , int , int );
//	void StartUseSkill();
//	void EndUseSkill(unsigned short );
//	void CancelSkill(int );
//	int IsSkillUsable(unsigned long );
//	void SetNPCJob(int );
//	int GetSkillLevel(unsigned long );
//	void SetPostDelayTimer(unsigned long );
//	void ResetPostDelayTimer(unsigned long );
//	void SetFSMReleaseTime(unsigned long );
//	void ProcessFSMReleaseTime();
//	void SetInfoByCreatorPC(unsigned long , unsigned long );
//	unsigned long GetMyCreatorPCAID();
//	void SetEmoticon(short );
//	void SetAITypeAfter(short );
//	bool IsUsingPlayingSkill();
//	void SetPosPlayingSkill(const short , const short );
//	void AddPlayingSkill(const unsigned long , const int , int , int );
//	void DeletePlayingSkill(const int );
//	void DestroyPlayingSkill();

private:
//	void ResetAttackedState();
//	int IsCondition(CNPC* , int , int );
//	int IsComradeCondition(CNPC* , int , int );
//	void ProcessPostDelayTimer();
//	int GetPostDelayTime(unsigned long );
//	NPCSKILLINFO* GetNPCSkillInfo(unsigned long );
//	int IsAvailableSkill(const unsigned long , const int );
//	void ProcessSkillPreDelayTime(NPCSKILLINFO* );

private:
	/* this+  0 */ //const CNPCSkill::`vftable';
	/* this+  4 */ int m_isSkillUsing;
	/* this+  8 */ int m_isNoDispel;
	/* this+ 12 */ int m_npcJob;
	/* this+ 16 */ unsigned long m_lastSkillTime;
	/* this+ 20 */ unsigned long m_fsmReleaseTime;
	/* this+ 24 */ int m_reactRangeAttack;
	/* this+ 28 */ unsigned long m_rangeAttackEnemyID;
	/* this+ 32 */ int m_reactRudeAttack;
	/* this+ 36 */ unsigned long m_rudeAttackEnemyID;
	/* this+ 40 */ int m_isRebirth;
	/* this+ 44 */ unsigned long m_myFriendID;
	/* this+ 48 */ std::map<unsigned long,unsigned long> m_postDelayTimer;
	/* this+ 64 */ CNPC* m_npc;
	/* this+ 68 */ int m_sanctuaryCnt;
	/* this+ 72 */ int m_stormGustCnt;
	/* this+ 76 */ unsigned long m_lifeTime;
	/* this+ 80 */ unsigned long m_creatorPCAID;
	/* this+ 84 */ unsigned short m_spellCastingSKID;
	/* this+ 88 */ unsigned long m_trickSkillDelayTime;
	/* this+ 92 */ int m_emoticon;
	/* this+ 96 */ int m_aiType;
	/* this+100 */ int m_chatNo;

	struct PlayingSkillInfo
	{
		/* this+ 0 */ unsigned long AID;
		/* this+ 4 */ int SKID;
		/* this+ 8 */ int DeltaPosX;
		/* this+12 */ int DeltaPosY;

		PlayingSkillInfo(const unsigned long , const int , const int , const int ); //TODO
		PlayingSkillInfo(); //TODO
		bool operator==(const PlayingSkillInfo& ); //TODO
	};

private:
	/* this+104 */ std::vector<PlayingSkillInfo> m_PlayingSkillList;
};
