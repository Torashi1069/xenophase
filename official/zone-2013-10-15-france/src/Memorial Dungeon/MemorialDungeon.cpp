#include "Memorial Dungeon/MemorialDungeon.h"


CMemorialDungeon::CMemorialDungeon(const unsigned long in_ExistZSID, const std::string in_Name, const unsigned long in_hPartyID, const std::string in_PartyName, const unsigned long in_MemorialDungeonID, const int in_Factor)
: m_ExistZSID(in_ExistZSID), m_Name(in_Name), m_hPartyID(in_hPartyID), m_PartyName(in_PartyName), m_MemorialDungeonID(in_MemorialDungeonID), m_Factor(in_Factor)
{
}


CMemorialDungeon::~CMemorialDungeon()
{
}
