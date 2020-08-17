#pragma once
#include "SkillTypeInfo.h"
#include "std/map"
#include "std/string"


class CSkillTypeBaseInfo
{
	/* this+ 0 */ public: //const CSkillTypeBaseInfo::`vftable';
	/* this+ 4 */ protected: mystd::map<mystd::string,unsigned short> m_skillName;
	/* this+16 */ protected: mystd::map<unsigned short,CSkillTypeInfo*> m_skillTypeInfo;

	public: CSkillTypeBaseInfo::CSkillTypeBaseInfo(void);
	public: virtual CSkillTypeBaseInfo::~CSkillTypeBaseInfo(void);
	public: void CSkillTypeBaseInfo::SetSKTyepBase(void); //TYPO
	//public: void CSkillTypeBaseInfo::ClearSKTypeBase(void);
	public: void CSkillTypeBaseInfo::InitGDSkill(void);
	public: void CSkillTypeBaseInfo::InitHomunSkill(void);
	public: void CSkillTypeBaseInfo::InitMercenarySkill(void);
	public: int CSkillTypeBaseInfo::SaveToFile(const char* fileName);
	public: void CSkillTypeBaseInfo::AddSkillType(CSkillTypeInfo* skinfo);

private:
	static hook_method<void (CSkillTypeBaseInfo::*)(void)> CSkillTypeBaseInfo::_SetSKTyepBase;
	//static hook_method<void (CSkillTypeBaseInfo::*)(void)> CSkillTypeBaseInfo::_ClearSKTypeBase;
	static hook_method<void (CSkillTypeBaseInfo::*)(void)> CSkillTypeBaseInfo::_InitGDSkill;
	static hook_method<void (CSkillTypeBaseInfo::*)(void)> CSkillTypeBaseInfo::_InitHomunSkill;
	static hook_method<void (CSkillTypeBaseInfo::*)(void)> CSkillTypeBaseInfo::_InitMercenarySkill;
	static hook_method<int (CSkillTypeBaseInfo::*)(const char* fileName)> CSkillTypeBaseInfo::_SaveToFile;
	static hook_method<void (CSkillTypeBaseInfo::*)(CSkillTypeInfo* skinfo)> CSkillTypeBaseInfo::_AddSkillType;
};
