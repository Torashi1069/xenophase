#include "Memorial Dungeon/MemorialDungeonReservedPlayer.h"


CMemorialDungeonReservedPlayer::CMemorialDungeonReservedPlayer(const int in_HsvrID, const int in_PriorityNum, const std::string in_Name, const std::string in_NickName, const int in_hParty, const std::string in_PartyName)
: m_Name(in_Name), m_NickName(in_NickName), m_hParty(in_hParty), m_PartyName(in_PartyName), m_bCreateDoing(false), m_PriorityNum(in_PriorityNum), m_PriorityNumNotifyTM(timeGetTime()), m_RequestTM(timeGetTime()), m_HsvrID(in_HsvrID)
{
}


CMemorialDungeonReservedPlayer::~CMemorialDungeonReservedPlayer()
{
}
