#include "CharacterMgr.h"
#include "Room.h"
#include "RoomMgr.h"


CRoomMgr::CRoomMgr()
{
}


CRoomMgr::~CRoomMgr()
{
}


void CRoomMgr::Init(int maxcount)
{
	this->CRoomMgr::Reset();
	m_roomMPool.CMemoryMgr<CRoom>::Init(maxcount);
}


void CRoomMgr::Reset()
{
	m_roomID = 1;
}


CRoom* CRoomMgr::SearchRoom(unsigned long roomID)
{
	std::map<unsigned long,CRoom*>::iterator iter = m_rooms.find(roomID);
	if( iter == m_rooms.end() )
		return NULL;

	return iter->second;
}


CRoom* CRoomMgr::SearchRoom(const char* rname)
{
	for( std::map<unsigned long,CRoom*>::iterator iter = m_rooms.begin(); iter != m_rooms.end(); ++iter )
	{
		CRoom* room = iter->second;

		const char* name = room->CRoom::GetRoomName();
		if( name != NULL && strncmp(name, rname, 128) == 0 )
			return room; // found.
	}

	return NULL; // not found.
}


unsigned char CRoomMgr::CreateRoom(const char* rname, const char* name, unsigned long AID, int size, unsigned long& roomID, char* passwd)
{
	CRoom* room = m_roomMPool.CMemoryMgr<CRoom>::Alloc();
	if( room == NULL )
		return CREATEROOM_FAILED_OVERFLOW;

	room->CRoom::Init();
	room->CRoom::SetRoomName(rname);
	room->CRoom::SetMaxSize(size);
	room->CRoom::SetPasswd(passwd);
	room->CRoom::InsertMember(name, AID, ROOMROLE_OWNER);
	roomID = this->CRoomMgr::AddRoom(room);
	room->CRoom::SetRoomID(roomID);
	return CREATEROOM_SUCCEED;
}


unsigned long CRoomMgr::AddRoom(CRoom* room)
{
	m_rooms[++m_roomID] = room;
	return m_roomID;
}


BOOL CRoomMgr::DeleteRoom(unsigned long roomID)
{
	std::map<unsigned long,CRoom*>::iterator iter = m_rooms.find(roomID);
	if( iter == m_rooms.end() )
		return FALSE;

	iter->second->CRoom::Reset();
	m_roomMPool.CMemoryMgr<CRoom>::Free(iter->second);
	m_rooms.erase(iter);
	return TRUE;
}


unsigned char CRoomMgr::EnterRoom(unsigned long roomID, const char* name, unsigned long AID, const char* passwd)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
		return -1;

	if( !room->CRoom::IsAcceptablePC(name) )
	{
		PACKET_ZC_REFUSE_ENTER_ROOM outpacket;
		outpacket.PacketType = HEADER_ZC_REFUSE_ENTER_ROOM;
		outpacket.result = REFUSETYPE_EXPEL;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
		return REFUSETYPE_EXPEL;
	}

	unsigned char roomType = room->CRoom::GetType();
	if( roomType == ROOMTYPE_PRIVATE )
	{
		if( !room->CRoom::IsCorrectPasswd(passwd) )
		{
			PACKET_ZC_REFUSE_ENTER_ROOM outpacket;
			outpacket.PacketType = HEADER_ZC_REFUSE_ENTER_ROOM;
			outpacket.result = REFUSETYPE_WRONGPASSWD;
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
			return REFUSETYPE_WRONGPASSWD;
		}
	}
	else
	if( roomType == ROOMTYPE_ARENA )
	{
		unsigned char ret = room->CRoom::GetAcceptableType(AID);
		if( ret != REFUSETYPE_SUCCEED )
		{
			PACKET_ZC_REFUSE_ENTER_ROOM outpacket;
			outpacket.PacketType = HEADER_ZC_REFUSE_ENTER_ROOM;
			outpacket.result = ret;
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
			return ret;
		}
	}

	if( !room->CRoom::InsertMember(name, AID, ROOMROLE_GENERAL) )
	{
		PACKET_ZC_REFUSE_ENTER_ROOM outpacket;
		outpacket.PacketType = HEADER_ZC_REFUSE_ENTER_ROOM;
		outpacket.result = REFUSETYPE_OVERFLOW;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
		return REFUSETYPE_OVERFLOW;
	}

	PACKET_ZC_ENTER_ROOM outpacket;
	outpacket.PacketType = HEADER_ZC_ENTER_ROOM;
	outpacket.PacketLength = sizeof(PACKET_ZC_ENTER_ROOM);
	outpacket.roomID = roomID;

	int count = 0;
	char buf[1024];
	this->CRoomMgr::GetRoomMembers(count, buf, sizeof(buf), roomID);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, sizeof(PACKET_ZC_ENTER_ROOM), (int)&outpacket, 0, 0);
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, count, (int)buf, 0, 0);

	return REFUSETYPE_SUCCEED;
}


void CRoomMgr::GetRoomMembers(int& count, char* buf, const int in_nMaxBufSize, unsigned long roomID)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
	{
		count = 0;
		return;
	}

	room->CRoom::GetRoomMembers(count, buf, in_nMaxBufSize);
}


void CRoomMgr::BroadCast(unsigned long roomID, int len, char* buf)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
		return;

	room->CRoom::BroadCast(len, buf, 0);
}


void CRoomMgr::UpdateRoom(unsigned long roomID, unsigned long AID, short size, unsigned char type, char* passwd, char* rname)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
		return;

	if( AID != room->CRoom::GetOwner() )
		return;

	room->CRoom::UpdateRoom(size, type, passwd, rname);
}


void CRoomMgr::ReqChangeRole(unsigned long roomID, unsigned long AID, const char* name, unsigned long role)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
		return;

	if( AID != room->CRoom::GetOwner() )
		return;

	room->CRoom::MemberRoleChange(AID, name, role);
}


void CRoomMgr::ExpelMember(unsigned long roomID, unsigned long AID, const char* name)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
		return;

	if( AID != room->CRoom::GetOwner() )
		return;

	room->CRoom::ExpelMember(name);
}


BOOL CRoomMgr::ExitRoom(unsigned long roomID, const char* name)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
		return FALSE;

	if( room->CRoom::ExitRoom(name) <= 0 )
	{
		this->CRoomMgr::DeleteRoom(roomID);
		return FALSE;
	}

	return TRUE;
}


unsigned long CRoomMgr::GetOwner(unsigned long roomID)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
		return 0;

	return room->CRoom::GetOwner();
}


int CRoomMgr::GetSize(unsigned long roomID)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
		return 0;

	return room->CRoom::GetSize();
}


int CRoomMgr::GetMaxSize(unsigned long roomID)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
		return 0;

	return room->CRoom::GetMaxSize();
}


unsigned char CRoomMgr::GetType(unsigned long roomID)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
		return -1;

	return room->CRoom::GetType();
}


const char* CRoomMgr::GetRoomName(unsigned long roomID)
{
	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	if( room == NULL )
		return NULL;

	return room->CRoom::GetRoomName();
}
