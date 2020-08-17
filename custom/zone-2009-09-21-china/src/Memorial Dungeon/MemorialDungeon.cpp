#include "Memorial Dungeon/MemorialDungeon.h"


CMemorialDungeon::CMemorialDungeon(const unsigned long in_ExistZSID, const mystd::string in_Name, const unsigned long in_hPartyID, const mystd::string in_PartyName, const unsigned long in_MemorialDungeonID, const int in_Factor) // line 22
: m_ExistZSID(in_ExistZSID), m_Name(in_Name), m_hPartyID(in_hPartyID), m_PartyName(in_PartyName), m_MemorialDungeonID(in_MemorialDungeonID), m_Factor(in_Factor)
{
}	


CMemorialDungeon::~CMemorialDungeon(void) // line 28
{
}
