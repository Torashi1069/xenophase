#include "CharacterMgr.h"
#include "Room.h"


CRoom::CRoom()
{
}


CRoom::~CRoom()
{
}


void CRoom::Init()
{
	this->CRoom::Reset();
}


const char* CRoom::GetRoomName()
{
	return m_roomName;
}


void CRoom::SetRoomName(const char* name)
{
	memcpy_s(m_roomName, sizeof(m_roomName), name, 128);
}


BOOL CRoom::InsertMember(const char* name, unsigned long AID, unsigned long Role)
{
	if( this->CRoom::GetSize() >= m_maxRoomSize )
		return FALSE;

	MEMBER_DATA mdata;
	mdata.AID = AID;
	mdata.ROLE = Role;
	memcpy_s(mdata.charName, sizeof(mdata.charName), name, 24);
	m_members.push_back(mdata);

	if( Role != ROOMROLE_OWNER )
	{
		PACKET_ZC_MEMBER_NEWENTRY outpacket;
		outpacket.PacketType = HEADER_ZC_MEMBER_NEWENTRY;
		outpacket.curcount = this->CRoom::GetSize();
		memcpy_s(outpacket.name, sizeof(outpacket.name), name, 24);
		this->CRoom::BroadCast(sizeof(outpacket), (char*)&outpacket, 0);
	}

	return TRUE;
}


BOOL CRoom::DeleteMember(const char* name)
{
	for( std::vector<MEMBER_DATA>::iterator iter = m_members.begin(); iter != m_members.end(); ++iter )
	{
		if( strncmp(iter->charName, name, 24) == 0 )
		{
			m_members.erase(iter);
			return TRUE; // found.
		}
	}

	return FALSE; // not found.
}


BOOL CRoom::IsPrivateRoom()
{
	return ( m_type == ROOMTYPE_PRIVATE );
}


BOOL CRoom::IsCorrectPasswd(const char* passwd)
{
	return ( strncmp(m_password, passwd, countof(m_password)) == 0 );
}


int CRoom::GetSize()
{
	return m_members.size();
}


void CRoom::Reset()
{
	m_members.clear();
	memset(m_roomName, '\0', sizeof(m_roomName));
	memset(m_password, '\0', sizeof(m_password));
	m_roomID = 0;
	m_type = ROOMTYPE_PUBLIC;
	m_maxRoomSize = 0;
	m_refuseList.clear();
	m_arenaInfo.fee = 0;
	m_arenaInfo.lowLevel = 0;
	m_arenaInfo.highLevel = 99;
	m_arenaInfo.m_exJob.clear();
}


BOOL CRoom::IsAcceptablePC(const char* name)
{
	std::list<std::string>::iterator iter;

	for( iter = m_refuseList.begin(); iter != m_refuseList.end(); ++iter )
		if( *iter == name )
			break;

	if( iter != m_refuseList.end() )
		return FALSE;

	return TRUE;
}


void CRoom::SetPasswd(const char* passwd)
{
	if( passwd[0] != '\0' )
		m_type = ROOMTYPE_PRIVATE;

	memcpy_s(m_password, sizeof(m_password), passwd, 8);
}


void CRoom::SetMaxSize(int maxsize)
{
	if( maxsize < 2 || maxsize > 20 )
		m_maxRoomSize = 20;
	else
	if( maxsize < this->CRoom::GetSize() )
		m_maxRoomSize = this->CRoom::GetSize();
	else
	{
		m_maxRoomSize = maxsize;
	}
}


void CRoom::GetRoomMembers(int& count, char* buf, const int in_nMaxBufSize)
{
	count = 0;

	for( std::vector<MEMBER_DATA>::iterator iter = m_members.begin(); iter != m_members.end(); ++iter )
	{
		ROOM_MEMBER_DATA data;
		memcpy_s(data.name, sizeof(data.name), iter->charName, sizeof(iter->charName));
		data.role = iter->ROLE;

		memcpy_s(buf + count, in_nMaxBufSize - count, &data, sizeof(data));
		count += sizeof(data);
	}
}


void CRoom::BroadCast(int len, char* buf, unsigned long AID)
{
	for( std::vector<MEMBER_DATA>::iterator iter = m_members.begin(); iter != m_members.end(); ++iter )
	{
		if( iter->AID == AID )
			continue; // skip

		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, iter->AID, CM_SEND_PACKET, len, (int)buf, 0, 0);
	}
}


void CRoom::SetRoomType(unsigned char flag)
{
	m_type = flag;
}


unsigned long CRoom::GetOwner()
{
	for( std::vector<MEMBER_DATA>::iterator iter = m_members.begin(); iter != m_members.end(); ++iter )
		if( iter->ROLE == ROOMROLE_OWNER )
			return iter->AID; // found.

	return 0; // not found.
}


void CRoom::UpdateRoom(short size, unsigned char type, char* passwd, char* rname)
{
	this->CRoom::SetRoomName(rname);
	if( type != ROOMTYPE_PRIVATE )
		this->CRoom::SetRoomType(ROOMTYPE_PUBLIC);
	else
		this->CRoom::SetPasswd(passwd);
	this->CRoom::SetMaxSize(size);

	PACKET_ZC_CHANGE_CHATROOM outpacket;
	outpacket.PacketType = HEADER_ZC_CHANGE_CHATROOM;
	outpacket.AID = this->CRoom::GetOwner();
	outpacket.curcount = this->CRoom::GetSize();
	outpacket.maxcount = static_cast<short>(m_maxRoomSize);
	outpacket.roomID = m_roomID;
	outpacket.type = m_type;

	char buf[128];
	memcpy_s(buf, sizeof(buf), this->CRoom::GetRoomName(), 128);
	buf[countof(buf)-1] = '\0';

	outpacket.PacketLength = sizeof(PACKET_ZC_CHANGE_CHATROOM) + strlen(buf);
	this->CRoom::BroadCast(sizeof(PACKET_ZC_CHANGE_CHATROOM), (char*)&outpacket, 0);
	this->CRoom::BroadCast(strlen(buf), buf, 0);

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, this->CRoom::GetOwner(), CM_MULTICAST_ROOM_NEWENTRY, m_roomID, 0, 0, 0);
}


void CRoom::MemberRoleChange(unsigned long AID, const char* name, unsigned long role)
{
	if( role == ROOMROLE_OWNER )
	{
		this->CRoom::OwnerChange(AID, name);
	}
	else
	{
		for( std::vector<MEMBER_DATA>::iterator iter = m_members.begin(); iter != m_members.end(); ++iter )
		{
			if( strncmp(iter->charName, name, 24) == 0 )
			{
				PACKET_ZC_ROLE_CHANGE outpacket;
				outpacket.PacketType = HEADER_ZC_ROLE_CHANGE;
				iter->ROLE = role;
				outpacket.role = role;
				memcpy_s(outpacket.name, sizeof(outpacket.name), name, 24);
				this->CRoom::BroadCast(sizeof(outpacket), (char*)&outpacket, 0);
			}
		}
	}
}


void CRoom::OwnerChange(unsigned long AID, const char* name)
{
	PACKET_ZC_ROLE_CHANGE oldOwner;
	oldOwner.PacketType = HEADER_ZC_ROLE_CHANGE;
	oldOwner.role = ROOMROLE_GENERAL;

	PACKET_ZC_ROLE_CHANGE newOwner;
	newOwner.PacketType = HEADER_ZC_ROLE_CHANGE;
	newOwner.role = ROOMROLE_OWNER;

	for( std::vector<MEMBER_DATA>::iterator iter = m_members.begin(); iter != m_members.end(); ++iter )
	{
		if( iter->AID == AID && iter->ROLE == ROOMROLE_OWNER )
		{
			memcpy_s(oldOwner.name, sizeof(oldOwner.name), iter->charName, 24);
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, AID, CM_MULTICAST_DESTROY_ROOM, 0, 0, 0, 0);
			iter->ROLE = ROOMROLE_GENERAL;
			this->CRoom::BroadCast(sizeof(oldOwner), (char*)&oldOwner, 0);
			break;
		}
	}

	for( std::vector<MEMBER_DATA>::iterator iter = m_members.begin(); iter != m_members.end(); ++iter )
	{
		if( strncmp(iter->charName, name, 24) == 0 )
		{
			iter->ROLE = ROOMROLE_OWNER;
			memcpy_s(newOwner.name, sizeof(newOwner.name), iter->charName, sizeof(iter->charName));
			this->CRoom::BroadCast(sizeof(newOwner), (char*)&newOwner, 0);
			return;
		}
	}

	for( std::vector<MEMBER_DATA>::iterator iter = m_members.begin(); iter != m_members.end(); ++iter )
	{
		if( iter->AID != AID )
		{
			iter->ROLE = ROOMROLE_OWNER;
			memcpy_s(newOwner.name, sizeof(newOwner.name), iter->charName, sizeof(iter->charName));
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, iter->AID, CM_MULTICAST_ROOM_NEWENTRY, m_roomID, 0, 0, 0);
			this->CRoom::BroadCast(sizeof(newOwner), (char*)&newOwner, 0);
			return;
		}
	}
}


void CRoom::ExpelMember(const char* name)
{
	PACKET_ZC_MEMBER_EXIT outpacket;
	outpacket.PacketType = HEADER_ZC_MEMBER_EXIT;

	for( std::vector<MEMBER_DATA>::iterator iter = m_members.begin(); iter != m_members.end(); )
	{
		if( strncmp(iter->charName, name, 24) == 0 )
		{
			if( iter->ROLE == ROOMROLE_OWNER )
				return; // can't expel owner.

			m_refuseList.push_back(name);

			memcpy_s(outpacket.name, sizeof(outpacket.name), name, 24);
			outpacket.type = ROOMEXITTYPE_EXPEL;
			outpacket.curcount = this->CRoom::GetSize() - 1;
			this->CRoom::BroadCast(sizeof(outpacket), (char*)&outpacket, 0);

			unsigned long memberAID = iter->AID;
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, memberAID, CM_SET_ROOMID, 0, 0, 0, 0);
			iter = m_members.erase(iter);
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, memberAID, CM_ROOM_NEWENTRY, m_roomID, 0, 0, 0);
		}
		else
		{
			++iter;
		}
	}
}


int CRoom::ExitRoom(const char* name)
{
	PACKET_ZC_MEMBER_EXIT outpacket;
	outpacket.PacketType = HEADER_ZC_MEMBER_EXIT;

	std::vector<MEMBER_DATA>::iterator iter = m_members.begin();

	if( this->CRoom::GetType() == ROOMTYPE_ARENA )
	{
		if( iter != m_members.end() )
			++iter;
	}

	for( ; iter != m_members.end(); ++iter )
	{
		if( strncmp(iter->charName, name, 24) == 0 )
		{
			if( this->CRoom::GetSize() < 2 )
			{
				CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, iter->AID, CM_MULTICAST_DESTROY_ROOM, 0, 0, 0, 0);

				memcpy_s(outpacket.name, sizeof(outpacket.name), name, 24);
				outpacket.curcount = this->CRoom::GetSize() - 1;
				this->CRoom::BroadCast(sizeof(outpacket), (char*)&outpacket, 0);
				m_members.erase(iter);
				return 0;
			}
			else
			{
				if( iter->ROLE == ROOMROLE_OWNER )
					this->CRoom::OwnerChange(iter->AID, "");

				memcpy_s(outpacket.name, sizeof(outpacket.name), name, 24);
				outpacket.curcount = this->CRoom::GetSize() - 1;
				this->CRoom::BroadCast(sizeof(outpacket), (char*)&outpacket, 0);
				m_members.erase(iter);
				return this->CRoom::GetSize();
			}
		}
	}

	return this->CRoom::GetSize();
}


int CRoom::ExitRoom(unsigned long AID)
{
	PACKET_ZC_MEMBER_EXIT outpacket;
	outpacket.PacketType = HEADER_ZC_MEMBER_EXIT;

	for( std::vector<MEMBER_DATA>::iterator iter = m_members.begin(); iter != m_members.end(); ++iter )
	{
		if( iter->AID == AID )
		{
			if( this->CRoom::GetSize() < 2 )
			{
				CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, iter->AID, CM_MULTICAST_DESTROY_ROOM, 0, 0, 0, 0);

				memcpy_s(outpacket.name, sizeof(outpacket.name), iter->charName, sizeof(iter->charName));
				outpacket.curcount = this->CRoom::GetSize() - 1;
				this->CRoom::BroadCast(sizeof(outpacket), (char*)&outpacket, 0);
				m_members.erase(iter);
				return 0;
			}
			else
			{
				if( iter->ROLE == ROOMROLE_OWNER )
					this->CRoom::OwnerChange(iter->AID, "");

				memcpy_s(outpacket.name, sizeof(outpacket.name), iter->charName, sizeof(iter->charName));
				outpacket.curcount = this->CRoom::GetSize() - 1;
				this->CRoom::BroadCast(sizeof(outpacket), (char*)&outpacket, 0);
				m_members.erase(iter);
				return this->CRoom::GetSize();
			}
		}
	}

	return this->CRoom::GetSize();
}


unsigned long CRoom::GetFirstMemberAID()
{
	std::vector<MEMBER_DATA>::iterator iter = m_members.begin() + 1;
	if( iter == m_members.end() )
		return 0;

	return iter->AID;
}


int CRoom::GetMaxSize()
{
	return m_maxRoomSize;
}


unsigned char CRoom::GetType()
{
	return m_type;
}


void CRoom::SetRoomID(unsigned long roomID)
{
	m_roomID = roomID;
}


void CRoom::SetLevel(int low, int high)
{
	m_arenaInfo.lowLevel = low;
	m_arenaInfo.highLevel = high;
}


int CRoom::GetLowLevel()
{
	return m_arenaInfo.lowLevel;
}


int CRoom::GetHighLevel()
{
	return m_arenaInfo.highLevel;
}


void CRoom::SetFee(int zeny)
{
	m_arenaInfo.fee = zeny;
}


int CRoom::GetFee()
{
	return m_arenaInfo.fee;
}


void CRoom::AddFeeItem(unsigned short ITID, int count)
{
}


void CRoom::AddExJob(int job)
{
	m_arenaInfo.m_exJob.push_back(job);
}



BOOL CRoom::IsAcceptableJob(int job)
{
	for( std::list<int>::iterator iter = m_arenaInfo.m_exJob.begin(); iter != m_arenaInfo.m_exJob.end(); ++iter )
		if( *iter == job )
			return FALSE;

	return TRUE;
}


int CRoom::GetAcceptableType(unsigned long AID)
{
	CCharacter* pc = CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(AID, PC_TYPE);
	if( pc == NULL )
		return -1;

	int zeny, level, job;
	pc->GetParameterValue(VAR_MONEY, zeny);
	pc->GetParameterValue(VAR_CLEVEL, level);
	pc->GetParameterValue(VAR_JOB, job);

	if( this->CRoom::GetSize() >= m_maxRoomSize )
		return REFUSETYPE_OVERFLOW;

	if( level < m_arenaInfo.lowLevel )
		return REFUSETYPE_LOWLEVEL;

	if( level > m_arenaInfo.highLevel )
		return REFUSETYPE_HIGHLEVEL;

	if( !this->CRoom::IsAcceptableJob(job) )
		return REFUSETYPE_JOB;

	if( zeny < this->CRoom::GetFee() )
		return REFUSETYPE_ZENY;

	return REFUSETYPE_SUCCEED;
}
