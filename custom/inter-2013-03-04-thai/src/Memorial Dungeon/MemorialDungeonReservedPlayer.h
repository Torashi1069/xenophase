#pragma once


class CMemorialDungeonReservedPlayer
{
public:
	/* this+  0 */ //const CMemorialDungeonReservedPlayer::`vftable';
	/* this+  4 */ std::string m_Name;
	/* this+ 32 */ std::string m_NickName;
	/* this+ 60 */ int m_hParty;
	/* this+ 64 */ std::string m_PartyName;
	/* this+ 92 */ bool m_bCreateDoing;
	/* this+ 96 */ int m_PriorityNum;
	/* this+100 */ DWORD m_PriorityNumNotifyTM;
	/* this+104 */ DWORD m_RequestTM;
	/* this+108 */ int m_HsvrID;

public:
	CMemorialDungeonReservedPlayer(const int in_HsvrID, const int in_PriorityNum, const std::string in_Name, const std::string in_NickName, const int in_hParty, const std::string in_PartyName);
	virtual ~CMemorialDungeonReservedPlayer();
};
