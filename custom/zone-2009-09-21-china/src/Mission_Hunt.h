#pragma once


class CMission_Hunt
{
public:
	CMission_Hunt();
	virtual ~CMission_Hunt();

private:
	/* this+ 0 */ //const CMission_Hunt::`vftable';
	/* this+ 4 */ unsigned long m_questID;
	/* this+ 8 */ int m_huntIdent;
	/* this+12 */ short m_huntCount;
	/* this+14 */ short m_maxCount;
	/* this+16 */ unsigned long m_mobGID;

public:
	bool SetMission(unsigned long questID, int huntIdent, unsigned long mobGID, int maxCount, int count);
	int GetCount();
	int PlusOneCount();
	unsigned long GetMobGID();
	unsigned long GetQuestID();
	bool GetCompleteHunting();
};
