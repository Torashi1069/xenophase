#pragma once
#include "Room.h"
#include "NetLib/MemoryMgr.h"


enum enumCREATEROOMRESULT
{
	CREATEROOM_SUCCEED         = 0,
	CREATEROOM_FAILED_OVERFLOW = 1,
	CREATEROOM_FAILED_SAMENAME = 2,
};


class CRoomMgr
{
public:
	CRoomMgr();
	virtual ~CRoomMgr();
	void Init(int maxcount);
	void Reset();
	CRoom* SearchRoom(unsigned long roomID);
	CRoom* SearchRoom(const char* rname);
	unsigned char CreateRoom(const char* rname, const char* name, unsigned long AID, int size, unsigned long& roomID, char* passwd); // enumCREATEROOMRESULT
	BOOL DeleteRoom(unsigned long roomID);
	unsigned char EnterRoom(unsigned long roomID, const char* name, unsigned long AID, const char* passwd);
	void GetRoomMembers(int& count, char* buf, const int in_nMaxBufSize, unsigned long roomID);
	void BroadCast(unsigned long roomID, int len, char* buf);
	void UpdateRoom(unsigned long roomID, unsigned long AID, short size, unsigned char type, char* passwd, char* rname);
	void ReqChangeRole(unsigned long roomID, unsigned long AID, const char* name, unsigned long role);
	void ExpelMember(unsigned long roomID, unsigned long AID, const char* name);
	BOOL ExitRoom(unsigned long roomID, const char* name);
	unsigned long GetOwner(unsigned long roomID);
	int GetSize(unsigned long roomID);
	int GetMaxSize(unsigned long roomID);
	unsigned char GetType(unsigned long roomID);
	const char* GetRoomName(unsigned long roomID);

private:
	unsigned long AddRoom(CRoom* room);

private:
	/* this+ 0 */ //const CRoomMgr::`vftable';
	/* this+ 4 */ CMemoryMgr<CRoom> m_roomMPool;
	/* this+40 */ std::map<unsigned long,CRoom*> m_rooms;
	/* this+56 */ unsigned long m_roomID;
};
