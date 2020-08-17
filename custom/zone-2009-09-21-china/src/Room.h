#pragma once
#include "std/list"
#include "std/string"
#include "std/vector"
#include "struct.hpp"


enum eRoomRole
{
	ROOMROLE_OWNER   = 0,
	ROOMROLE_GENERAL = 1,
};


struct MEMBER_DATA
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ unsigned long ROLE; // enum eRoomRole
	/* this+8 */ char charName[24];
};


struct ROOM_MEMBER_DATA
{
	/* this+0 */ unsigned long role;
	/* this+4 */ char name[24];
};


class CRoom
{
	/* this+  0 */ public: //const CRoom::`vftable';
	/* this+  4 */ private: char m_roomName[128];
	/* this+132 */ private: unsigned long m_roomID;
	/* this+136 */ private: int m_maxRoomSize;
	/* this+140 */ private: ARENA_ROOM_INFO m_arenaInfo;
	/* this+164 */ private: char m_password[8];
	/* this+172 */ private: unsigned char m_type;
	/* this+176 */ private: mystd::vector<MEMBER_DATA> m_members;
	/* this+192 */ private: mystd::list<mystd::string> m_refuseList;

	public: CRoom::CRoom(void);
	public: virtual CRoom::~CRoom(void);
	public: void CRoom::Init(void);
	public: const char* CRoom::GetRoomName(void);
	public: void CRoom::SetRoomName(const char* name);
	public: int CRoom::InsertMember(const char* name, unsigned long AID, unsigned long Role);
	public: int CRoom::DeleteMember(const char* name);
	public: int CRoom::IsPrivateRoom(void);
	public: void CRoom::SetRoomType(unsigned char flag);
	public: int CRoom::IsCorrectPasswd(const char* passwd);
	public: int CRoom::GetSize(void);
	public: int CRoom::IsAcceptablePC(const char* name);
	public: void CRoom::Reset(void);
	public: void CRoom::SetPasswd(const char* passwd);
	public: void CRoom::SetMaxSize(int maxsize);
	public: void CRoom::GetRoomMembers(int& count, char* buf);
	public: void CRoom::BroadCast(int len, char* buf, unsigned long AID);
	//public: void CRoom::UpdateRoom(short size, unsigned char type, char* passwd, char* rname);
	public: unsigned long CRoom::GetOwner(void);
	//public: void CRoom::MemberRoleChange(unsigned long AID, const char* name, unsigned long role);
	//public: void CRoom::OwnerChange(unsigned long AID, const char* name);
	//public: void CRoom::ExpelMember(const char* name);
	//public: int CRoom::ExitRoom(unsigned long AID);
	//public: int CRoom::ExitRoom(const char* name);
	public: int CRoom::GetMaxSize(void);
	public: unsigned char CRoom::GetType(void);
	public: void CRoom::SetRoomID(unsigned long roomID);
	public: unsigned long CRoom::GetFirstMemberAID(void);
	public: int CRoom::GetAcceptableType(unsigned long AID);
	public: void CRoom::SetLevel(int low, int high);
	public: void CRoom::SetFee(int zeny);
	//public: void CRoom::AddFeeItem(unsigned short, int);
	public: void CRoom::AddExJob(int job);
	public: int CRoom::GetFee(void);
	public: int CRoom::GetLowLevel(void);
	public: int CRoom::GetHighLevel(void);
	private: int CRoom::IsAcceptableJob(int job);

private:
	static hook_method<void (CRoom::*)(void)> CRoom::_Init;
	static hook_method<const char* (CRoom::*)(void)> CRoom::_GetRoomName;
	static hook_method<void (CRoom::*)(const char* name)> CRoom::_SetRoomName;
	static hook_method<int (CRoom::*)(const char* name, unsigned long AID, unsigned long Role)> CRoom::_InsertMember;
	static hook_method<int (CRoom::*)(const char* name)> CRoom::_DeleteMember;
	static hook_method<int (CRoom::*)(void)> CRoom::_IsPrivateRoom;
	static hook_method<void (CRoom::*)(unsigned char flag)> CRoom::_SetRoomType;
	static hook_method<int (CRoom::*)(const char* passwd)> CRoom::_IsCorrectPasswd;
	static hook_method<int (CRoom::*)(void)> CRoom::_GetSize;
	static hook_method<int (CRoom::*)(const char* name)> CRoom::_IsAcceptablePC;
	static hook_method<void (CRoom::*)(void)> CRoom::_Reset;
	static hook_method<void (CRoom::*)(const char* passwd)> CRoom::_SetPasswd;
	static hook_method<void (CRoom::*)(int maxsize)> CRoom::_SetMaxSize;
	static hook_method<void (CRoom::*)(int& count, char* buf)> CRoom::_GetRoomMembers;
	static hook_method<void (CRoom::*)(int len, char* buf, unsigned long AID)> CRoom::_BroadCast;
	static hook_method<unsigned long (CRoom::*)(void)> CRoom::_GetOwner;
	static hook_method<int (CRoom::*)(void)> CRoom::_GetMaxSize;
	static hook_method<unsigned char (CRoom::*)(void)> CRoom::_GetType;
	static hook_method<void (CRoom::*)(unsigned long roomID)> CRoom::_SetRoomID;
	static hook_method<unsigned long (CRoom::*)(void)> CRoom::_GetFirstMemberAID;
	static hook_method<int (CRoom::*)(unsigned long AID)> CRoom::_GetAcceptableType;
	static hook_method<void (CRoom::*)(int low, int high)> CRoom::_SetLevel;
	static hook_method<void (CRoom::*)(int zeny)> CRoom::_SetFee;
	static hook_method<void (CRoom::*)(int job)> CRoom::_AddExJob;
	static hook_method<int (CRoom::*)(void)> CRoom::_GetFee;
	static hook_method<int (CRoom::*)(void)> CRoom::_GetLowLevel;
	static hook_method<int (CRoom::*)(void)> CRoom::_GetHighLevel;
	static hook_method<int (CRoom::*)(int job)> CRoom::_IsAcceptableJob;
};
