#pragma once
#include "N2System/N2Object.h"
#include "N2System/N2Inter.h"
#include "N2System/N2InterMessageQueue.h"
#include "std/map"
#include "std/string"


class CMemorialDungeon : public N2Object, public N2Inter
{
public:
	struct tagInstantMapInfo
	{
		/* this+0x0 */ bool bCreateRequest;
		/* this+0x4 */ int mapType;

		//public: CMemorialDungeon::tagInstantMapInfo::tagInstantMapInfo(const int);
	};

	class CPlayer
	{
		/* this+0x0 */ void* vtable;
		/* this+0x4 */ public: unsigned long m_AID;
		/* this+0x8 */ public: unsigned long m_GID;

		//public: void CMemorialDungeon::CPlayer::CPlayer(const unsigned long, const unsigned long);
		//public: void CMemorialDungeon::CPlayer::~CPlayer();
	};

	enum
	{
		MSG_NONE2               = 0x0,
		MSG_CREATE_ERROR2       = 0x1,
		MSG_ERROR2              = 0x2,
		MSG_DYING_WISH_REQUEST2 = 0x3,
		MSG_INSTANTMAP_CREATE2  = 0x4,
		MSG_INSTANTMAP_DESTROY2 = 0x5,
	};

	enum enumSTATE
	{
		STATE_CREATE        = 0x0,
		STATE_OPERATION     = 0x1,
		STATE_ERROR         = 0x2,
		STATE_DESTROY_READY = 0x3,
	};

	enum enumSCHEDULE
	{
		SCHEDULE_DESTORY_LIVE_TIMEOUT = 0x0,
		SCHEDULE_DESTORY_ENTER_TIMEOUT = 0x1,
	};

	typedef mystd::map<mystd::string,CMemorialDungeon::tagInstantMapInfo>::const_iterator INSTANTMAPLISTCONTAINER_ITER;
	typedef mystd::map<unsigned long,CMemorialDungeon::CPlayer>::const_iterator PLAYERCONTAINER_ITER;
	//typedef mystd::multimap<unsigned long,enum CMemorialDungeon::enumSCHEDULE>::const_iterator SCHEDULE_CONTAINER_ITER;

	/* this+0x0  */ //N2Object
	/* this+0x8  */ //N2Inter
	/* this+0xC  */ private: mystd::map<mystd::string,CMemorialDungeon::tagInstantMapInfo> m_InstantMapList;
	/* this+0x18 */ private: bool m_bOK;
	/* this+0x1C */ private: N2InterMessageQueue m_MessageQueue;
	/* this+0x44 */ private: mystd::string m_Name;
	/* this+0x60 */ private: mystd::string m_NickName;
	/* this+0x7C */ private: int m_hParty;
	/* this+0x80 */ private: mystd::string m_PartyName;
	/* this+0x9C */ private: const int m_Factor;
	/* this+0xA0 */ private: const int m_TargetZSID;
	/* this+0xA4 */ private: unsigned long m_ZSVRregisteredFUCnt;
	/* this+0xA8 */ private: mystd::string m_EnterInstantMapName;
	/* this+0xC4 */ private: int m_EnterPosX;
	/* this+0xC8 */ private: int m_EnterPosY;
	/* this+0xCC */ private: int m_LiveTimeMinute;
	/* this+0xD0 */ private: enum CMemorialDungeon::enumSTATE m_State;
	/* this+0xD4 */ private: mystd::map<unsigned long,CMemorialDungeon::CPlayer> m_PlayerContainer;
	/* this+0xE0 */ private: mystd::multimap<unsigned long,enum enumSCHEDULE> m_ScheduleContainer;
	/* this+0xF0 */ private: void (CMemorialDungeon::* m_ProcessFuncPtr)(const int, const int, const int, const unsigned int);

	//public: void CMemorialDungeon::OnEnter(const unsigned long, const unsigned long);
	//public: void CMemorialDungeon::OnLeave(const unsigned long, const unsigned long);
	//private: void CMemorialDungeon::Schedule_Add(const unsigned long, const enum CMemorialDungeon::enumSCHEDULE);
	private: unsigned long CMemorialDungeon::Schedule_GetDate(const enum CMemorialDungeon::enumSCHEDULE in_Job);
	//private: void CMemorialDungeon::Schedule_Process();
	//private: void CMemorialDungeon::Process_PROCSTEP_CREATE_INSTANTMAP(const int, const int, const int, const unsigned int);
	//private: void CMemorialDungeon::Process_PROCSTEP_DYING_WISH(const int, const int, const int, const unsigned int);
	//private: void CMemorialDungeon::Process_PROCSTEP_OPERATION(const int, const int, const int, const unsigned int);
	//public: const bool CMemorialDungeon::isOK();
	//public: void CMemorialDungeon::Process();
	//public: const bool CMemorialDungeon::IsDestroyReady();
	//public: const bool CMemorialDungeon::isActive();
	//public: const int CMemorialDungeon::GetTargetZSID();
	public: const mystd::string CMemorialDungeon::GetName(void);
	public: const unsigned long CMemorialDungeon::GetPartyID(void);
	//public: const class std::basic_string<char,std::char_traits<char>,std::allocator<char> > CMemorialDungeon::GetPartyName();
	public: const unsigned long CMemorialDungeon::GetLiveDate(void);
	public: const unsigned long CMemorialDungeon::GetEnterLimitDate(void);
	//public: const unsigned long CMemorialDungeon::GetZSVRregisteredFUCnt();
	//public: const int CMemorialDungeon::GetFactor();
	public: void CMemorialDungeon::PartyLeave(const unsigned long in_AID, const unsigned long in_GID);
	//public: const class std::basic_string<char,std::char_traits<char>,std::allocator<char> > CMemorialDungeon::GetEnterInstantMapName();
	//public: const int CMemorialDungeon::GetEnterInstantMapX();
	//public: const int CMemorialDungeon::GetEnterInstantMapY();
	public: const enum CMemorialDungeon::enumSTATE CMemorialDungeon::GetState(void);
	//public: void CMemorialDungeon::PostInterMessage(const unsigned int, const int, const int, const int);
	//public: bool CMemorialDungeon::PeekInterMessage(unsigned int &, int &, int &, int &, const bool);
	//public: void CMemorialDungeon::CMemorialDungeon(const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >, const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >, const int, const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >, const int);
	//public: void CMemorialDungeon::~CMemorialDungeon();

private:
	static hook_method<unsigned long (CMemorialDungeon::*)(const enum CMemorialDungeon::enumSCHEDULE in_Job)> CMemorialDungeon::_Schedule_GetDate;
	static hook_method<const mystd::string (CMemorialDungeon::*)(void)> CMemorialDungeon::_GetName;
	static hook_method<const unsigned long (CMemorialDungeon::*)(void)> CMemorialDungeon::_GetPartyID;
	static hook_method<const unsigned long (CMemorialDungeon::*)(void)> CMemorialDungeon::_GetLiveDate;
	static hook_method<const unsigned long (CMemorialDungeon::*)(void)> CMemorialDungeon::_GetEnterLimitDate;
	static hook_method<void (CMemorialDungeon::*)(const unsigned long in_AID, const unsigned long in_GID)> CMemorialDungeon::_PartyLeave;
	static hook_method<const enum CMemorialDungeon::enumSTATE (CMemorialDungeon::*)(void)> CMemorialDungeon::_GetState;
};
