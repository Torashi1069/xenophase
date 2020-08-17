#pragma once
#include "Room.h"
#include "NetLib/MemoryMgr.h"
#include "std/map"


class CRoomMgr
{
	/* this+ 0 */ public: //const CRoomMgr::`vftable';
	/* this+ 4 */ private: CMemoryMgr<CRoom> m_roomMPool;
	/* this+52 */ private: mystd::map<unsigned long,CRoom*> m_rooms;
	/* this+64 */ private: unsigned long m_roomID;

	public: CRoomMgr::CRoomMgr(void);
	public: virtual CRoomMgr::~CRoomMgr(void);
	public: void CRoomMgr::Init(int maxcount);
	//public: void CRoomMgr::Reset();
	//public: CRoom* SearchRoom(const char *);
	public: CRoom* CRoomMgr::SearchRoom(unsigned long roomID);
	//public: unsigned char CRoomMgr::CreateRoom(const char *, const char *, unsigned long, int, unsigned long &, char *);
	//public: int CRoomMgr::DeleteRoom(unsigned long);
	//public: unsigned char CRoomMgr::EnterRoom(unsigned long, const char *, unsigned long, const char *);
	//public: void CRoomMgr::GetRoomMembers(int &, char *, unsigned long);
	//public: void BroadCast(unsigned long, int, char *);
	//public: void CRoomMgr::UpdateRoom(unsigned long, unsigned long, short, unsigned char, char *, char *);
	//public: void CRoomMgr::ReqChangeRole(unsigned long, unsigned long, const char *, unsigned long);
	//public: void CRoomMgr::ExpelMember(unsigned long, unsigned long, const char *);
	public: int CRoomMgr::ExitRoom(unsigned long roomID, const char* name);
	public: unsigned long CRoomMgr::GetOwner(unsigned long roomID);
	//public: int CRoomMgr::GetSize(unsigned long);
	//public: int CRoomMgr::GetMaxSize(unsigned long);
	//public: unsigned char CRoomMgr::GetType(unsigned long);
	//public: const char * CRoomMgr::GetRoomName(unsigned long);
	//private: unsigned long CRoomMgr::AddRoom(CRoom *);

private:
	static hook_method<void (CRoomMgr::*)(int maxcount)> CRoomMgr::_Init;
	static hook_method<CRoom* (CRoomMgr::*)(unsigned long roomID)> CRoomMgr::_SearchRoom;
	static hook_method<int (CRoomMgr::*)(unsigned long roomID, const char* name)> CRoomMgr::_ExitRoom;
	static hook_method<unsigned long (CRoomMgr::*)(unsigned long roomID)> CRoomMgr::_GetOwner;
};
