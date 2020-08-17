#include "MemorialDungeonReservedPlayer.h"


CMemorialDungeonReservedPlayer::CMemorialDungeonReservedPlayer(const int in_PriorityNum, const mystd::string in_Name, const mystd::string in_NickName, const int in_hParty, const mystd::string in_PartyName) // line 26
: m_Name(in_Name), m_NickName(in_NickName), m_hParty(in_hParty), m_PartyName(in_PartyName), m_bCreateDoing(false), m_PriorityNum(in_PriorityNum), m_PriorityNumNotifyTM(timeGetTime()), m_RequestTM(timeGetTime())
{
}


CMemorialDungeonReservedPlayer::~CMemorialDungeonReservedPlayer(void) // line 31
{
}
