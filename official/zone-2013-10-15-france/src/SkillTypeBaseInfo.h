#pragma once
class CSkillTypeInfo;


class CSkillTypeBaseInfo
{
public:
	CSkillTypeBaseInfo();
	virtual ~CSkillTypeBaseInfo();

public:
	void SetSKTyepBase();
	void ClearSKTypeBase();
	void InitGDSkill();
	void InitHomunSkill();
	void InitMercenarySkill();
	void InitElementalSkill();
	BOOL SaveToFile(const char* fileName);
	void AddSkillType(CSkillTypeInfo* skinfo);

protected:
	/* this+ 0 */ //const CSkillTypeBaseInfo::`vftable';
	/* this+ 4 */ std::map<std::string,unsigned short> m_skillName;
	/* this+20 */ std::map<unsigned short,CSkillTypeInfo*> m_skillTypeInfo;
};
