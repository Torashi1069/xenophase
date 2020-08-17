#pragma once
#include "SkillTypeBaseInfo.h"
#include "std/map"


class CSkillTypeInfoMgr : public CSkillTypeBaseInfo
{
	/* this+ 0 */ public: //CSkillTypeBaseInfo baseclass_0;
	/* this+28 */ private: mystd::map<short,mystd::map<unsigned short,mystd::map<unsigned short,int> > > m_skillTreeInfo;
	/* this+40 */ private: mystd::map<unsigned short,mystd::map<unsigned short,int> > m_GDSkillTreeInfo;
	/* this+52 */ private: mystd::map<short,mystd::map<unsigned short,std::map<unsigned short,int> > > m_SKTree_Homun;
	/* this+64 */ private: mystd::map<short,mystd::map<unsigned short,int> > m_SKTree_Merce;

	public: CSkillTypeInfoMgr::CSkillTypeInfoMgr(void);
	public: virtual CSkillTypeInfoMgr::~CSkillTypeInfoMgr(void);
	public: void CSkillTypeInfoMgr::Init(void);
	public: void CSkillTypeInfoMgr::Reset(void);
	public: unsigned short CSkillTypeInfoMgr::GetSKID(const char* skName) const;
	//public: void CSkillTypeInfoMgr::LoadSKInfoFromDB();
	public: int CSkillTypeInfoMgr::SendMsg(CCharacter* sender, int SKID, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4);
	public: CSkillTypeInfo* CSkillTypeInfoMgr::SearchSkillTypeInfo(unsigned short SKID);
	//public: short CSkillTypeInfoMgr::GetSkillSPCost(unsigned short, short);
	//public: char * CSkillTypeInfoMgr::GetSkillName(unsigned short);
	//public: bool CSkillTypeInfoMgr::IsNextLevelUpgradable(unsigned short, short, short);
	//public: int CSkillTypeInfoMgr::IsChangeStatusSkill(unsigned short);
	//public: int CSkillTypeInfoMgr::GetIndexGroundSkill(unsigned short);
	//public: int CSkillTypeInfoMgr::GetSkillPattern(unsigned short);
	public: short CSkillTypeInfoMgr::GetSKClass(unsigned short SKID);
	//public: void CSkillTypeInfoMgr::AddSkill(CCharacter *, short);
	//public: void CSkillTypeInfoMgr::AddSkill_Homun(CCharacter *, short);
	//public: void CSkillTypeInfoMgr::AddSkill_Merce(CCharacter *, short);
	//public: int CSkillTypeInfoMgr::GetType(unsigned short);
	public: short CSkillTypeInfoMgr::GetAttackRange(unsigned short SKID, int level);
	//public: int CSkillTypeInfoMgr::GetProperty(unsigned short);
	//public: void CSkillTypeInfoMgr::RegisterSkillName(char *);
	public: int CSkillTypeInfoMgr::IsAvailableJob(short job, unsigned short SKID);
	//public: short CSkillTypeInfoMgr::IsAvailable_Merce(short, unsigned short);
	public: int CSkillTypeInfoMgr::IsConditionalSkill(short job, unsigned short SKID);
	public: int CSkillTypeInfoMgr::IsConditionSkill_HO(short job, unsigned short SKID);
	//public: int CSkillTypeInfoMgr::IsGuildSkill(int);
	public: mystd::map<unsigned short,int>* CSkillTypeInfoMgr::GetLowerSkillTreeInfo(short job, unsigned short SKID);
	//public: void CSkillTypeInfoMgr::InheritFirstJobSkill(short, short);
	//public: void CSkillTypeInfoMgr::InheritPreJobSkill_HO(short, short);
	//public: mystd::map<unsigned short,mystd::map<unsigned short,int> >* CSkillTypeInfoMgr::GetAllAvailableSkill(short);
	public: int CSkillTypeInfoMgr::IsSkillCategory(unsigned short SKID, int type);
	public: short CSkillTypeInfoMgr::GetPostDelayTM(unsigned short SKID, short level);
	//public: unsigned long CSkillTypeInfoMgr::GetFlag(unsigned short);
	public: bool CSkillTypeInfoMgr::InitSkillScript(void);
	//public: void CSkillTypeInfoMgr::LoadSkillDelay(const char *, function  *);
	//public: int CSkillTypeInfoMgr::GetSkillSinglePostDelay(unsigned short, int);
	//public: int CSkillTypeInfoMgr::GetSkillGlobalPostDelay(unsigned short, int);
	//public: bool CSkillTypeInfoMgr::GetSkillTypeInfo2_SkillData(unsigned short, unsigned long, short, int &);
	//private: void CSkillTypeInfoMgr::LoadSkillTree(const char *);
	//private: int CSkillTypeInfoMgr::LoadGDSkillTree();
	//private: int CSkillTypeInfoMgr::LoadSKTree_Homun(const char *);
	//private: int CSkillTypeInfoMgr::LoadSKTree_Merce(const char *);

private:
	static hook_method<void (CSkillTypeInfoMgr::*)(void)> CSkillTypeInfoMgr::_Init;
	static hook_method<void (CSkillTypeInfoMgr::*)(void)> CSkillTypeInfoMgr::_Reset;
	static hook_method<unsigned short (CSkillTypeInfoMgr::*)(const char* skName) const> CSkillTypeInfoMgr::_GetSKID;
	static hook_method<int (CSkillTypeInfoMgr::*)(CCharacter* sender, int SKID, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)> CSkillTypeInfoMgr::_SendMsg;
	static hook_method<CSkillTypeInfo* (CSkillTypeInfoMgr::*)(unsigned short SKID)> CSkillTypeInfoMgr::_SearchSkillTypeInfo;
	static hook_method<short (CSkillTypeInfoMgr::*)(unsigned short SKID)> CSkillTypeInfoMgr::_GetSKClass;
	static hook_method<short (CSkillTypeInfoMgr::*)(unsigned short SKID, int level)> CSkillTypeInfoMgr::_GetAttackRange;
	static hook_method<int (CSkillTypeInfoMgr::*)(short job, unsigned short SKID)> CSkillTypeInfoMgr::_IsAvailableJob;
	static hook_method<int (CSkillTypeInfoMgr::*)(short job, unsigned short SKID)> CSkillTypeInfoMgr::_IsConditionalSkill;
	static hook_method<int (CSkillTypeInfoMgr::*)(short job, unsigned short SKID)> CSkillTypeInfoMgr::_IsConditionSkill_HO;
	static hook_method<mystd::map<unsigned short,int>* (CSkillTypeInfoMgr::*)(short job, unsigned short SKID)> CSkillTypeInfoMgr::_GetLowerSkillTreeInfo;
	static hook_method<int (CSkillTypeInfoMgr::*)(unsigned short SKID, int type)> CSkillTypeInfoMgr::_IsSkillCategory;
	static hook_method<short (CSkillTypeInfoMgr::*)(unsigned short SKID, short level)> CSkillTypeInfoMgr::_GetPostDelayTM;
	static hook_method<bool (CSkillTypeInfoMgr::*)(void)> CSkillTypeInfoMgr::_InitSkillScript;
};
