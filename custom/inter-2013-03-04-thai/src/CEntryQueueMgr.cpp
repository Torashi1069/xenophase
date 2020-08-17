#include "CEntryQueueMgr.h"
#include "InterServer.h" // g_userMgr
#include "UserMgr.h"
#include "Common/Packet.h"
#include "Zsvr/CZsvrMgr.h"


/// singleton instance
CEntryQueueMgr*& CEntryQueueMgr::m_cpSelf = VTOR<CEntryQueueMgr*>(DetourFindFunction(EXEPATH(), "CEntryQueueMgr::m_cpSelf"));


CEntryQueueMgr::CEntryQueueMgr()
{
	m_bOK = false;

	if( this->CEntryQueueMgr::Create() )
		m_bOK = true;
}


CEntryQueueMgr::~CEntryQueueMgr()
{
	this->CEntryQueueMgr::Destroy();
}


bool CEntryQueueMgr::Create()
{
	m_setBattleFieldMapName.insert("bat_a01.gat");
	m_setBattleFieldMapName.insert("bat_b01.gat");
	m_setBattleFieldMapName.insert("bat_c01.gat");
	m_setBattleFieldMapName.insert("bat_c02.gat");
	m_setBattleFieldMapName.insert("bat_c03.gat");

	return true;
}


void CEntryQueueMgr::Destroy()
{
}


bool CEntryQueueMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CEntryQueueMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CEntryQueueMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CEntryQueueMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CEntryQueueMgr* CEntryQueueMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CEntryQueueMgr::isOK() const
{
	return m_bOK;
}


void CEntryQueueMgr::AddEntryQueue(const std::string in_EntryQueueName, const int in_ZSID)
{
	m_hashmapEntryQueue.insert(std::pair<const std::string,int>(in_EntryQueueName, in_ZSID));
}


int CEntryQueueMgr::GetZSID(const std::string in_EntryQueueName) const
{
	HASHMAP_ENTRY_QUEUE::const_iterator iter = m_hashmapEntryQueue.lower_bound(in_EntryQueueName);
	if( iter == m_hashmapEntryQueue.end() )
		return -1;

	return  iter->second;
}


bool CEntryQueueMgr::AddApplicant(const unsigned long in_GID, const unsigned long in_AID, const std::string in_EntryQueueName)
{
	return m_mapEntryQueueNameForGID.insert(std::make_pair(in_GID, std::make_pair(in_AID, in_EntryQueueName))).second;
}


void CEntryQueueMgr::DelApplicant(const unsigned long in_GID)
{
	ENTRY_QUEUE_NAME_FOR_GID::iterator iter = m_mapEntryQueueNameForGID.find(in_GID);
	if( iter != m_mapEntryQueueNameForGID.end() )
		m_mapEntryQueueNameForGID.erase(iter);
}


void CEntryQueueMgr::LogOut(const unsigned long in_GID)
{
	ENTRY_QUEUE_NAME_FOR_GID::iterator iter = m_mapEntryQueueNameForGID.find(in_GID);
	if( iter == m_mapEntryQueueNameForGID.end() )
		return;

	unsigned long GID = iter->first;
	std::string EntryQueueName = iter->second.second;

	int ZSID = CEntryQueueMgr::GetObj()->CEntryQueueMgr::GetZSID(EntryQueueName);
	if( ZSID != -1 )
	{
		PACKET_IZ_ENTRY_QUEUE_LOGOUT outPacket = {};
		outPacket.PacketType = HEADER_IZ_ENTRY_QUEUE_LOGOUT;
		strncpy_s(outPacket.EntryQueueName, 24, EntryQueueName.c_str(), _TRUNCATE);
		outPacket.GID = in_GID;
		CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(outPacket), (char*)&outPacket);
	}

	this->CEntryQueueMgr::DelApplicant(in_GID);
}


bool CEntryQueueMgr::IsApplicant(const unsigned long in_GID, std::string& out_EntryQueueName)
{
	ENTRY_QUEUE_NAME_FOR_GID::iterator iter = m_mapEntryQueueNameForGID.find(in_GID);
	if( iter == m_mapEntryQueueNameForGID.end() )
		return false;

	out_EntryQueueName = iter->second.second.c_str();
	return true;
}	


void CEntryQueueMgr::DisconnectZSVR(const unsigned long in_ZSID)
{
	for( ENTRY_QUEUE_NAME_FOR_GID::iterator iter = m_mapEntryQueueNameForGID.begin(); iter != m_mapEntryQueueNameForGID.end(); )
	{
		unsigned long GID = iter->first;
		unsigned long AID = iter->second.first;
		std::string EntryQueueName = iter->second.second;

		if( in_ZSID == CEntryQueueMgr::GetObj()->CEntryQueueMgr::GetZSID(EntryQueueName) )
		{
			unsigned long ZSID = g_userMgr.CUserMgr::SearchUserServerID(GID, AID);
			if( ZSID != 0 && ZSID != in_ZSID )
			{
				PACKET_IZ_RESULT_ENTRY_QUEUE_CANCEL packet = {};
				packet.PacketType = HEADER_IZ_RESULT_ENTRY_QUEUE_CANCEL;
				packet.GID = GID;
				packet.Result = EQ_ZSVR_DISCONNECT;
				strncpy_s(packet.EntryQueueName, 24, EntryQueueName.c_str(), _TRUNCATE);
				CZsvrMgr::GetObj()->CZServerMgr::SendMsgToZServer(ZSID, sizeof(packet), (char*)&packet);
			}

			iter = m_mapEntryQueueNameForGID.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}


bool CEntryQueueMgr::IsBattleFieldMap(const std::string in_UserLocation) const
{
	return ( m_setBattleFieldMapName.find(in_UserLocation) != m_setBattleFieldMapName.end() );
}
