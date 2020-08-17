#pragma once
#include "std/string"


class CMemorialDungeonReservedPlayer
{
	/* this+0x0  */ //const CMemorialDungeonReservedPlayer::`vftable'
	/* this+0x4  */ public: mystd::string m_Name;
	/* this+0x20 */ public: mystd::string m_NickName;
	/* this+0x3C */ public: int m_hParty;
	/* this+0x40 */ public: mystd::string m_PartyName;
	/* this+0x5C */ public: bool m_bCreateDoing;
	/* this+0x60 */ public: int m_PriorityNum;
	/* this+0x64 */ public: unsigned long m_PriorityNumNotifyTM;
	/* this+0x68 */ public: unsigned long m_RequestTM;

	public: CMemorialDungeonReservedPlayer::CMemorialDungeonReservedPlayer(const int in_PriorityNum, const mystd::string in_Name, const mystd::string in_NickName, const int in_hParty, const mystd::string in_PartyName);
	public: virtual CMemorialDungeonReservedPlayer::~CMemorialDungeonReservedPlayer(void);
};
