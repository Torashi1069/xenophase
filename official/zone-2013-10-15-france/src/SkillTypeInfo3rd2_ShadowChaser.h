#pragma once
#include "SkillTypeInfo2.h"
class CPC;


class SK_SC_REPRODUCE : public CSkillTypeInfo2
{
public:
	union DATA
	{
	public:
		struct {
			/* this(bf)+0: 0 len(16) */ int SKID    : 16;
			/* this(bf)+0:16 len( 8) */ int SKLevel : 8;
			/* this(bf)+0:24 len( 8) */ int unused  : 8;
		} Imitation;

	private:
		int value;

	public:
		operator int() { return value; }
		DATA(const int in_value) { value = in_value; }
		DATA(const int in_SKID, const int in_SKLevel) { Imitation.SKID = in_SKID; Imitation.SKLevel = in_SKLevel; }
	};

public:
	virtual int OnMsg(CCharacter* sender, unsigned short SKID, int MsgID, int skLevel, int targetID, int spCost, MSGpar::CVar par4);
	int GetLifeSupportSpCost(const int in_Level);
};


class SK_SC_AUTOSHADOWSPELL : public CSkillTypeInfo2
{
private:
	/* this+  0 */ //CSkillTypeInfo2 baseclass_0;
	typedef std::vector<int> SKILLLISTCONTAINER;
	/* this+252 */ SKILLLISTCONTAINER m_SkillList;

private:
	enum { RESPONSE_WAIT_TM = 10000 };

public:
	virtual int OnMsg(CCharacter* in_cpSender, unsigned short in_SKID, int in_MsgID, int in_par1, int in_par2, int in_par3, MSGpar::CVar in_par4);
	std::vector<int> GetImitationSKlist(CPC* in_pPlayer) const;
	bool IsAllowSkill(CPC* in_pPlayer, const unsigned short in_SKID) const;
	int GetLifeTM(const int in_Level) const;
	int GetAutoSpellMiliPercent(const int in_Level) const;
	int GetAutoSpellLevel(const int in_Level, const int in_ImitationSKLevel) const;
	bool LoadAllowSkillListFile();
};
