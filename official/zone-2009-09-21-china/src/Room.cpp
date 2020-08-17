#include "CharacterMgr.h"
#include "Room.h"
#include "Common/Packet.h"
#include "globals.hpp"


CRoom::CRoom(void) // line 8
{
}


CRoom::~CRoom(void) // line 12
{
}


hook_method<void (CRoom::*)(void)> CRoom::_Init(SERVER, "CRoom::Init");
void CRoom::Init(void) // line 17
{
	return (this->*_Init)();

	this->CRoom::Reset();
}


hook_method<const char* (CRoom::*)(void)> CRoom::_GetRoomName(SERVER, "CRoom::GetRoomName");
const char* CRoom::GetRoomName(void) // line ??
{
	return (this->*_GetRoomName)();

	return m_roomName;
}


hook_method<void (CRoom::*)(const char* name)> CRoom::_SetRoomName(SERVER, "CRoom::SetRoomName");
void CRoom::SetRoomName(const char* name) // line 26
{
	return (this->*_SetRoomName)(name);

	memcpy(m_roomName, name, sizeof(m_roomName));
}


hook_method<int (CRoom::*)(const char* name, unsigned long AID, unsigned long Role)> CRoom::_InsertMember(SERVER, "CRoom::InsertMember");
int CRoom::InsertMember(const char* name, unsigned long AID, unsigned long Role) // line 31
{
	return (this->*_InsertMember)(name, AID, Role);

	if( this->CRoom::GetSize() >= m_maxRoomSize )
		return 0;

	MEMBER_DATA member;
	member.AID = AID;
	member.ROLE = Role;
	memcpy(member.charName, name, sizeof(member.charName));
	m_members.push_back(member);

	if( Role == ROOMROLE_GENERAL )
	{
		PACKET_ZC_MEMBER_NEWENTRY outpacket;
		outpacket.PacketType = HEADER_ZC_MEMBER_NEWENTRY;
		outpacket.curcount = this->CRoom::GetSize();
		memcpy(outpacket.name, name, sizeof(outpacket.name));
		this->CRoom::BroadCast(sizeof(outpacket), (char*)&outpacket, 0);
	}

	return 1;
}


//hook_method<int (CRoom::*)(const char* name)> CRoom::_DeleteMember(SERVER, "CRoom::DeleteMember");
int CRoom::DeleteMember(const char* name) // line ??
{
//	return (this->*_DeleteMember)(name);

	assert(false);
	return 0;
	//TODO
}


//hook_method<int (CRoom::*)(void)> CRoom::_IsPrivateRoom(SERVER, "CRoom::IsPrivateRoom");
int CRoom::IsPrivateRoom(void) // line ??
{
//	return (this->*_IsPrivateRoom)();

	assert(false);
	return 0;
	//TODO
}


hook_method<void (CRoom::*)(unsigned char flag)> CRoom::_SetRoomType(SERVER, "CRoom::SetRoomType");
void CRoom::SetRoomType(unsigned char flag) // line 163
{
	return (this->*_SetRoomType)(flag);

	m_type = flag;
}


hook_method<int (CRoom::*)(const char* passwd)> CRoom::_IsCorrectPasswd(SERVER, "CRoom::IsCorrectPasswd");
int CRoom::IsCorrectPasswd(const char* passwd) // line 76
{
	return (this->*_IsCorrectPasswd)(passwd);

	return ( strncmp(m_password, passwd, sizeof(m_password)) == 0 );
}


hook_method<int (CRoom::*)(void)> CRoom::_GetSize(SERVER, "CRoom::GetSize");
int CRoom::GetSize(void) // line 85
{
	return (this->*_GetSize)();

	return m_members.size();
}


hook_method<int (CRoom::*)(const char* name)> CRoom::_IsAcceptablePC(SERVER, "CRoom::IsAcceptablePC");
int CRoom::IsAcceptablePC(const char* name) // line 106
{
	return (this->*_IsAcceptablePC)(name);

	return ( mystd::find(m_refuseList.begin(), m_refuseList.end(), name) == m_refuseList.end() );
}


hook_method<void (CRoom::*)(void)> CRoom::_Reset(SERVER, "CRoom::Reset");
void CRoom::Reset(void) // line 89
{
	return (this->*_Reset)();

	m_members.clear();
	memset(m_roomName, 0, sizeof(m_roomName));
	m_roomID = 0;
	memset(m_password, 0, sizeof(m_password));
	m_type = 1;
	m_maxRoomSize = 0;
	m_refuseList.clear();
	m_arenaInfo.lowLevel = 0;
	m_arenaInfo.highLevel = 99;
	m_arenaInfo.fee = 0;
	m_arenaInfo.m_exJob.clear();
}


hook_method<void (CRoom::*)(const char* passwd)> CRoom::_SetPasswd(SERVER, "CRoom::SetPasswd");
void CRoom::SetPasswd(const char* passwd) // line 118
{
	return (this->*_SetPasswd)(passwd);

	if( *passwd != '\0' )
		m_type = 0;
	memcpy(m_password, passwd, sizeof(m_password));
}


hook_method<void (CRoom::*)(int maxsize)> CRoom::_SetMaxSize(SERVER, "CRoom::SetMaxSize");
void CRoom::SetMaxSize(int maxsize) // line 126
{
	return (this->*_SetMaxSize)(maxsize);

	if( maxsize > 20 )
		m_maxRoomSize = 20;
	else
	if( maxsize < (int)m_members.size() )
		m_maxRoomSize = m_members.size();
	else
		m_maxRoomSize = maxsize;
}


hook_method<void (CRoom::*)(int& count, char* buf)> CRoom::_GetRoomMembers(SERVER, "CRoom::GetRoomMembers");
void CRoom::GetRoomMembers(int& count, char* buf) // line 138
{
	return (this->*_GetRoomMembers)(count, buf);

	count = 0;
	for( mystd::vector<MEMBER_DATA>::const_iterator i = m_members.begin(); i != m_members.end(); ++i )
	{
		ROOM_MEMBER_DATA data;
		data.role = i->ROLE;
		memcpy(data.name, i->charName, sizeof(data.name));

		memcpy(&buf[count], &data, sizeof(data));
		count += sizeof(data);
	}
}


hook_method<void (CRoom::*)(int len, char* buf, unsigned long AID)> CRoom::_BroadCast(SERVER, "CRoom::BroadCast");
void CRoom::BroadCast(int len, char* buf, unsigned long AID) // line 152
{
	return (this->*_BroadCast)(len, buf, AID);

	for( mystd::vector<MEMBER_DATA>::const_iterator i = m_members.begin(); i != m_members.end(); ++i )
		if( i->AID != AID )
			g_characterMgr->CCharacterMgr::SendMsg(NULL, i->AID, CM_SEND_PACKET, len, (int)buf, 0, 0);
}


hook_method<unsigned long (CRoom::*)(void)> CRoom::_GetOwner(SERVER, "CRoom::GetOwner");
unsigned long CRoom::GetOwner(void) // line 169
{
	return (this->*_GetOwner)();

	mystd::vector<MEMBER_DATA>::const_iterator it;

	for( it = m_members.begin(); it != m_members.end(); ++it )
		if( it->ROLE == ROOMROLE_OWNER )
			return it->AID;

	return 0;
}


hook_method<int (CRoom::*)(void)> CRoom::_GetMaxSize(SERVER, "CRoom::GetMaxSize");
int CRoom::GetMaxSize(void) // line 387
{
	return (this->*_GetMaxSize)();

	return m_maxRoomSize;
}


hook_method<unsigned char (CRoom::*)(void)> CRoom::_GetType(SERVER, "CRoom::GetType");
unsigned char CRoom::GetType(void) // line 392
{
	return (this->*_GetType)();

	return m_type;
}


hook_method<void (CRoom::*)(unsigned long roomID)> CRoom::_SetRoomID(SERVER, "CRoom::SetRoomID");
void CRoom::SetRoomID(unsigned long roomID) // line ???
{
	return (this->*_SetRoomID)(roomID);

	m_roomID = roomID;
}


hook_method<unsigned long (CRoom::*)(void)> CRoom::_GetFirstMemberAID(SERVER, "CRoom::GetFirstMemberAID");
unsigned long CRoom::GetFirstMemberAID(void) // line 378
{
	return (this->*_GetFirstMemberAID)();

	//TODO
}


hook_method<int (CRoom::*)(unsigned long AID)> CRoom::_GetAcceptableType(SERVER, "CRoom::GetAcceptableType");
int CRoom::GetAcceptableType(unsigned long AID) // line 440
{
	return (this->*_GetAcceptableType)(AID);

	//TODO
}


hook_method<void (CRoom::*)(int low, int high)> CRoom::_SetLevel(SERVER, "CRoom::SetLevel");
void CRoom::SetLevel(int low, int high) // line 403
{
	return (this->*_SetLevel)(low, high);

	m_arenaInfo.lowLevel = low;
	m_arenaInfo.highLevel = high;
}


hook_method<void (CRoom::*)(int zeny)> CRoom::_SetFee(SERVER, "CRoom::SetFee");
void CRoom::SetFee(int zeny) // line 409
{
	return (this->*_SetFee)(zeny);

	m_arenaInfo.fee = zeny;
}


hook_method<void (CRoom::*)(int job)> CRoom::_AddExJob(SERVER, "CRoom::AddExJob");
void CRoom::AddExJob(int job) // line 423
{
	return (this->*_AddExJob)(job);

	m_arenaInfo.m_exJob.push_back(job);
}


hook_method<int (CRoom::*)(void)> CRoom::_GetFee(SERVER, "CRoom::GetFee");
int CRoom::GetFee(void) // line 414
{
	return (this->*_GetFee)();

	return m_arenaInfo.fee;
}


//hook_method<int (CRoom::*)(void)> CRoom::_GetLowLevel(SERVER, "CRoom::GetLowLevel");
int CRoom::GetLowLevel(void) // line ???
{
//	return (this->*_GetLowLevel)();

	return m_arenaInfo.lowLevel;
}


//hook_method<int (CRoom::*)(void)> CRoom::_GetHighLevel(SERVER, "CRoom::GetHighLevel");
int CRoom::GetHighLevel(void) // line ???
{
//	return (this->*_GetHighLevel)();

	return m_arenaInfo.highLevel;
}


hook_method<int (CRoom::*)(int job)> CRoom::_IsAcceptableJob(SERVER, "CRoom::IsAcceptableJob");
int CRoom::IsAcceptableJob(int job) // line 430
{
	return (this->*_IsAcceptableJob)(job);

	mystd::list<int>::const_iterator it;

	for( it = m_arenaInfo.m_exJob.begin(); it != m_arenaInfo.m_exJob.end(); ++it )
		if( *it == job )
			return 1;

	return 0;
}
