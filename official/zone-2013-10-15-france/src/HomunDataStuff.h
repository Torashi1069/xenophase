#pragma once
#include "ZoneProcess.h"
#include "AsyncDBWork/Effect3rd.h"
namespace HomunDataStuff {


class CHomunData
{
public:
	/* this+ 0 */ //const CHomunData::`vftable';
	/* this+ 4 */ bool m_bExist;
	/* this+ 8 */ std::vector<Effect3rd::tagEffect3rdDBFmt> m_EfstList;
	/* this+24 */ std::map<unsigned short,HO_SKINFO> m_Skill;

public:
	virtual void Init() { m_bExist = false; m_EfstList.clear(); m_Skill.clear(); }
	bool isExist() { return m_bExist; }

public:
	CHomunData() { }
	virtual ~CHomunData() { }
};


}; // namespace
