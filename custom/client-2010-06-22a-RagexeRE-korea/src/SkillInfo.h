#pragma once


struct SKILL_INFO
{
	/* this+ 0 */ int m_isValid;
	/* this+ 4 */ int SKID;
	/* this+ 8 */ int type;
	/* this+12 */ int level;
	/* this+16 */ int spcost;
	/* this+20 */ int upgradable;
	/* this+24 */ int attackRange;
	/* this+28 */ const char* skillName;
	/* this+32 */ int skillPos;
	/* this+36 */ int skillMaxLv;
	/* this+40 */ int field_28; //TODO
	/* this+44 */ mystd::vector<int> needSkillList;

	static bool IsGoodSkillForActor(int skillId);
};
C_ASSERT( sizeof SKILL_INFO == 60 );


const char* GetSkillName(int SKID);
