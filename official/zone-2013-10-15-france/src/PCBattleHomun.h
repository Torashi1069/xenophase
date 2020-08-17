#pragma once
#include "HomunDataStuff.h"
class CNpcHomun; // #include "NpcHomun.h"
#include "ZoneProcess.h"
#include "AsyncDBWork/Effect3rd.h"
#include "AsyncDBWork/LogonPermitADBWork.h"


class CPCBattleHomun
{
public:
	CPCBattleHomun();
	~CPCBattleHomun();

public:
	void Reset();
	void SetHomunDBFmt(const CLogonPermitADBWork::CHomunLogonData& in_HomunData);
	void GetHomunDBFmt(CNpcHomun* in_cpHomun, HomunDataStuff::CHomunData& io_HomunData);
	void UpdateHomunData(CNpcHomun* ); //TODO

private:
	void SetHomunEffectData(const std::vector<Effect3rd::tagEffect3rdDBFmt>& ); //TODO

public:
	void SetHomunEffectData(); //TODO
	const std::vector<Effect3rd::tagEffect3rdDBFmt>& GetHomunEffectData();
	const std::map<unsigned short,HO_SKINFO>& GetHomunSkillData();

private:
	void SetHomunSkillData(const std::map<unsigned short,HO_SKINFO>& ); //TODO
	void SetHomunSkillData(); //TODO

private:
	/* this+ 0 */ std::vector<Effect3rd::tagEffect3rdDBFmt> m_EfstList;
	/* this+16 */ std::map<unsigned short,HO_SKINFO> m_Skill;
};
