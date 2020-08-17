#pragma once
#include "std/string"


class CMemorialDungeon
{
	/* this+0x0  */ //const CMemorialDungeon::`vftable'
	/* this+0x4  */ public: unsigned long m_ExistZSID;
	/* this+0x8  */ public: mystd::string m_Name;
	/* this+0x24 */ public: unsigned long m_hPartyID;
	/* this+0x28 */ public: mystd::string m_PartyName;
	/* this+0x44 */ public: unsigned long m_MemorialDungeonID;
	/* this+0x48 */ public: int m_Factor;

	//public: void CMemorialDungeon::CMemorialDungeon(const CMemorialDungeon& __that);
	public: CMemorialDungeon::CMemorialDungeon(const unsigned long in_ExistZSID, const mystd::string in_Name, const unsigned long in_hPartyID, const mystd::string in_PartyName, const unsigned long in_MemorialDungeonID, const int in_Factor);
	public: virtual CMemorialDungeon::~CMemorialDungeon(void);
};
