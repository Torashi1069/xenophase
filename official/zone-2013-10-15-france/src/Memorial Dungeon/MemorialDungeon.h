#pragma once


class CMemorialDungeon
{
public:
	/* this+ 0 */ //const CMemorialDungeon::`vftable';
	/* this+ 4 */ unsigned long m_ExistZSID;
	/* this+ 8 */ std::string m_Name;
	/* this+36 */ unsigned long m_hPartyID;
	/* this+40 */ std::string m_PartyName;
	/* this+68 */ unsigned long m_MemorialDungeonID;
	/* this+72 */ int m_Factor;

public:
	CMemorialDungeon(const unsigned long in_ExistZSID, const std::string in_Name, const unsigned long in_hPartyID, const std::string in_PartyName, const unsigned long in_MemorialDungeonID, const int in_Factor);
	virtual ~CMemorialDungeon();
};
