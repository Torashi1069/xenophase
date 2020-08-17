#pragma once
#include "std/map"
class CNPC;
struct MSG_TYPE1_TWODWORD;
struct NPCSKILLINFO;


class CNPCSkill
{
public:
	/* this+0x0  */ //const CNPCSkill::`vftable'
	/* this+0x4  */ int m_isSkillUsing;
	/* this+0x8  */ int m_isNoDispel;
	/* this+0xC  */ int m_npcJob;
	/* this+0x10 */ unsigned long m_lastSkillTime;
	/* this+0x14 */ unsigned long m_fsmReleaseTime;
	/* this+0x18 */ int m_reactRangeAttack;
	/* this+0x1C */ unsigned long m_rangeAttackEnemyID;
	/* this+0x20 */ int m_reactRudeAttack;
	/* this+0x24 */ unsigned long m_rudeAttackEnemyID;
	/* this+0x28 */ int m_isRebirth;
	/* this+0x2C */ unsigned long m_myFriendID;
	/* this+0x30 */ mystd::map<unsigned long,unsigned long> m_postDelayTimer;
	/* this+0x3C */ CNPC* m_npc;
	/* this+0x40 */ int m_sanctuaryCnt;
	/* this+0x44 */ int m_stormGustCnt;
	/* this+0x48 */ unsigned short m_spellCastingSKID;
	/* this+0x4C */ unsigned long m_creatorPCAID;
	/* this+0x50 */ unsigned long m_trickSkillDelayTime;
	/* this+0x54 */ unsigned long m_lifeTime;
	/* this+0x58 */ int m_emoticon;
	/* this+0x5C */ int m_aiType;
	/* this+0x60 */ int m_chatNo;

	public: CNPCSkill::CNPCSkill(void);
	public: virtual CNPCSkill::~CNPCSkill(void);
	public: void CNPCSkill::Init(void);
	public: void CNPCSkill::SetMyOwner(CNPC* npc);
	public: int CNPCSkill::OnProcess(void);
	public: void CNPCSkill::OnUseSkill(unsigned short SKID, int skLevel, int targetAID, int xPos, int yPos);
	public: void CNPCSkill::OnUseGroundSkill(int SKID, MSG_TYPE1_TWODWORD* position, int skLevel, int spCost);
	public: void CNPCSkill::StartUseSkill(void);
	public: void CNPCSkill::EndUseSkill(unsigned short SKID);
	public: void CNPCSkill::CancelSkill(int flag);
	public: int CNPCSkill::IsSkillUsable(unsigned long FSMState);
	public: void CNPCSkill::SetNPCJob(int job);
	public: int CNPCSkill::GetSkillLevel(unsigned long SKID);
	public: void CNPCSkill::SetPostDelayTimer(unsigned long SKID);
	public: void CNPCSkill::ResetPostDelayTimer(unsigned long SKID);
	public: void CNPCSkill::SetFSMReleaseTime(unsigned long time);
	public: void CNPCSkill::ProcessFSMReleaseTime(void);
	public: void CNPCSkill::SetInfoByCreatorPC(unsigned long id, unsigned long lifeTime);
	public: unsigned long CNPCSkill::GetMyCreatorPCAID(void);
	public: void CNPCSkill::SetEmoticon(short par);
	public: void CNPCSkill::SetAITypeAfter(short par);
	public: void CNPCSkill::ForceUseSkill(unsigned short SKID, int skLevel, int castTime, int chatNo);
	private: void CNPCSkill::ResetAttackedState(void);
	private: int CNPCSkill::IsCondition(CNPC* npc, int condition, int value);
	private: int CNPCSkill::IsComradeCondition(CNPC* npc, int condition, int value);
	private: void CNPCSkill::ProcessPostDelayTimer(void);
	private: int CNPCSkill::GetPostDelayTime(unsigned long SKID);
	private: NPCSKILLINFO* CNPCSkill::GetNPCSkillInfo(unsigned long SKID);
	private: int CNPCSkill::IsAvailableSkill(unsigned long SKID);
	private: void CNPCSkill::ProcessSkillPreDelayTime(NPCSKILLINFO* skillInfo);

private:
	static hook_method<void (CNPCSkill::*)(void)> CNPCSkill::_Init;
	static hook_method<void (CNPCSkill::*)(CNPC* npc)> CNPCSkill::_SetMyOwner;
	static hook_method<int (CNPCSkill::*)(void)> CNPCSkill::_OnProcess;
	static hook_method<void (CNPCSkill::*)(unsigned short SKID, int skLevel, int targetAID, int xPos, int yPos)> CNPCSkill::_OnUseSkill;
	static hook_method<void (CNPCSkill::*)(int SKID, MSG_TYPE1_TWODWORD* position, int skLevel, int spCost)> CNPCSkill::_OnUseGroundSkill;
	static hook_method<void (CNPCSkill::*)(void)> CNPCSkill::_StartUseSkill;
	static hook_method<void (CNPCSkill::*)(unsigned short SKID)> CNPCSkill::_EndUseSkill;
	static hook_method<void (CNPCSkill::*)(int flag)> CNPCSkill::_CancelSkill;
	static hook_method<int (CNPCSkill::*)(unsigned long FSMState)> CNPCSkill::_IsSkillUsable;
	static hook_method<void (CNPCSkill::*)(int job)> CNPCSkill::_SetNPCJob;
	static hook_method<int (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_GetSkillLevel;
	static hook_method<void (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_SetPostDelayTimer;
	static hook_method<void (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_ResetPostDelayTimer;
	static hook_method<void (CNPCSkill::*)(unsigned long time)> CNPCSkill::_SetFSMReleaseTime;
	static hook_method<void (CNPCSkill::*)(void)> CNPCSkill::_ProcessFSMReleaseTime;
	static hook_method<void (CNPCSkill::*)(unsigned long id, unsigned long lifeTime)> CNPCSkill::_SetInfoByCreatorPC;
	static hook_method<unsigned long (CNPCSkill::*)(void)> CNPCSkill::_GetMyCreatorPCAID;
	static hook_method<void (CNPCSkill::*)(short par)> CNPCSkill::_SetEmoticon;
	static hook_method<void (CNPCSkill::*)(short par)> CNPCSkill::_SetAITypeAfter;
	static hook_method<void (CNPCSkill::*)(unsigned short SKID, int skLevel, int castTime, int chatNo)> CNPCSkill::_ForceUseSkill;
	static hook_method<void (CNPCSkill::*)(void)> CNPCSkill::_ResetAttackedState;
	static hook_method<int (CNPCSkill::*)(CNPC* npc, int condition, int value)> CNPCSkill::_IsCondition;
	static hook_method<int (CNPCSkill::*)(CNPC* npc, int condition, int value)> CNPCSkill::_IsComradeCondition;
	static hook_method<void (CNPCSkill::*)(void)> CNPCSkill::_ProcessPostDelayTimer;
	static hook_method<int (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_GetPostDelayTime;
	static hook_method<NPCSKILLINFO* (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_GetNPCSkillInfo;
	static hook_method<int (CNPCSkill::*)(unsigned long SKID)> CNPCSkill::_IsAvailableSkill;
	static hook_method<void (CNPCSkill::*)(NPCSKILLINFO* skillInfo)> CNPCSkill::_ProcessSkillPreDelayTime;
};
