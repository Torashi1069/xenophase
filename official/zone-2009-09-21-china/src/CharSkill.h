#pragma once
class CCharacter;
class CSkillTypeInfo2;
struct SKILLATTACK_MSG;
struct MSG_TYPE4_FIVEDWORD;


class CCharSkill
{
	/* this+ 0 */ public: int m_SKID;
	/* this+ 4 */ public: CCharacter* m_owner;
	/* this+ 8 */ public: CCharacter* m_target;
	/* this+12 */ public: int m_result;
	/* this+16 */ public: SKILLATTACK_MSG* m_skillMsg;
	/* this+20 */ public: CSkillTypeInfo2* m_skillTypeInfo2;

	//public: void CCharSkill::CCharSkill();
	//public: int CCharSkill::OperSkillToChar(CCharacter*, CCharacter*, int, MSG_TYPE4_FIVEDWORD*);
	//public: int CCharSkill::OnGroundSkill(CCharacter*, int, int, MSG_TYPE5_SIXDWORD*);
	public: int CCharSkill::OnTouchedSkillObj(CCharacter* owner, CCharacter* target, int SKID, MSG_TYPE4_FIVEDWORD* data, int sectionMove);
	public: int CCharSkill::AttSkillToChar(CCharacter* owner, CCharacter* target, int SKID, MSG_TYPE4_FIVEDWORD* data, SKILLATTACK_MSG* skillMsg);
	//public: bool CCharSkill::PreApplySkill(CCharacter*, SKILLATTACK_MSG*, void*);
	//public: bool CCharSkill::PostApplySkill(CCharacter*, SKILLATTACK_MSG*, void*);
	//public: PosInfo* CCharSkill::GetSplashCells(unsigned long, PosInfo, PosInfo, int, int, int&);
	//public: int CCharSkill::GetPlusATTPower_KN_BRANDISHSPEAR(int, int, int, int);
	//private: int CCharSkill::UseSkill_ST_FULLSTRIP(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_RG_CLOSECONFINE(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_LK_SPIRALPIERCE(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_HP_ASSUMPTIO(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_ASC_BREAKER(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_ASC_METEORASSAULT(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_SN_SHARPSHOOTING(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_HW_NAPALMVULCAN(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_NPC_EARTHQUAKE(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_SKILLTYPEINFO2(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_MER_SCAPEGOAT(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_NPC_HELLPOWER(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_NPC_WIDEHELLDIGNITY(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_NPC_INVINCIBLE(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_NPC_INVINCIBLEOFF(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_NPC_ALLHEAL(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_GM_SANDMAN(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_CASH_BLESSING(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_CASH_INCAGI(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_CASH_ASSUMPTIO(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_SOUND(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::UseSkill_HW_GANBANTEIN(MSG_TYPE5_SIXDWORD*);
	//private: int CCharSkill::UseSkill_PF_SPIDERWEB(MSG_TYPE5_SIXDWORD*);
	//private: int CCharSkill::UseSkill_SA_LANDPROTECTOR(MSG_TYPE5_SIXDWORD*);
	//private: int CCharSkill::TouchedSkill_PF_SPIDERWEB(MSG_TYPE4_FIVEDWORD*, int);
	//private: int CCharSkill::TouchedSkill_NPC_EARTHQUAKE(MSG_TYPE4_FIVEDWORD*, int);
	//private: int CCharSkill::TouchedSkill_NPC_EVILLAND(MSG_TYPE4_FIVEDWORD*, int);
	//private: bool CCharSkill::PreApply_HW_NAPALMVULCAN(CCharacter*, SKILLATTACK_MSG*, void*);
	//private: bool CCharSkill::PreApply_NPC_DRAGONFEAR(CCharacter*, SKILLATTACK_MSG*, void*);
	//private: bool CCharSkill::PreApply_NPC_EARTHQUAKE(CCharacter*, SKILLATTACK_MSG*, void*);
	//private: bool CCharSkill::PreApply_SKILLTYPEINFO2(CCharacter*, SKILLATTACK_MSG*, void*);
	//private: bool CCharSkill::PreApply_NPC_WIDESIGHT(CCharacter*, SKILLATTACK_MSG*, void*);
	//private: bool CCharSkill::PreApply_NPC_EXPULSION(CCharacter*, SKILLATTACK_MSG*, void*);
	//private: bool CCharSkill::PreApply_NPC_SLOWCAST(CCharacter*, SKILLATTACK_MSG*, void*);
	//private: bool CCharSkill::PostApply_ASC_METEORASSAULT(CCharacter*, SKILLATTACK_MSG*, void*);
	//private: bool CCharSkill::PostApply_HW_NAPALMVULCAN(CCharacter*, SKILLATTACK_MSG*, void*);
	//private: bool CCharSkill::PostApply_SKILLTYPEINFO2(CCharacter*, SKILLATTACK_MSG*, void*);
	//private: int CCharSkill::UseSkill_RG_STRIPWEAPON(MSG_TYPE4_FIVEDWORD*, bool);
	//private: int CCharSkill::UseSkill_RG_STRIPSHIELD(MSG_TYPE4_FIVEDWORD*, bool);
	//private: int CCharSkill::UseSkill_RG_STRIPARMOR(MSG_TYPE4_FIVEDWORD*, bool);
	//private: int CCharSkill::UseSkill_RG_STRIPHELM(MSG_TYPE4_FIVEDWORD*, bool);
	//private: int CCharSkill::UseSkill_GROUND_SKILLTYPEINFO2(MSG_TYPE5_SIXDWORD*, int);
	//private: bool CCharSkill::IsEnableStrip(CCharacter*, int, int&);
	//private: int CCharSkill::ExecuteTargetSkill(MSG_TYPE4_FIVEDWORD*);
	//private: int CCharSkill::ExecuteSplashSkill(MSG_TYPE4_FIVEDWORD*, STRUCT_SK_SPLASH*);
	//private: bool CCharSkill::ParseSkillInfo(mystd::map<unsigned long,void*>&, CCharacter*, SKILLATTACK_MSG*, void*, bool);
	//private: void CCharSkill::BroadcastSkillEffect(unsigned short, unsigned long, unsigned long, short, bool);
	//private: void CCharSkill::BroadcastSkillEffect(unsigned long, int);
	//private: bool CCharSkill::SetEffective_SKILLTYPEINFO2(CCharacter*, int, int);

private:
	static hook_method<int (CCharSkill::*)(CCharacter* owner, CCharacter* target, int SKID, MSG_TYPE4_FIVEDWORD* data, int sectionMove)> CCharSkill::_OnTouchedSkillObj;
	static hook_method<int (CCharSkill::*)(CCharacter* owner, CCharacter* target, int SKID, MSG_TYPE4_FIVEDWORD* data, SKILLATTACK_MSG* skillMsg)> CCharSkill::_AttSkillToChar;
};


CCharSkill* __cdecl GetCharSkill(void);
