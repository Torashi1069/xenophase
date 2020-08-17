#include "InterServer.h"
#include "Instant Map/InstantMap.h"
#include "Instant Map/InstantMapConfiguration.h"
#include "Instant Map/InstantMapIDGenerator.h"
#include "Instant Map/InstantMapMgr.h"
#include "shared/N3System/N3MessageMgr.h"
#include "shared/shared.h" // Decrypt()


/// singleton instance
CInstantMapMgr*& CInstantMapMgr::m_cpSelf = VTOR<CInstantMapMgr*>(DetourFindFunction(EXEPATH(), "CInstantMapMgr::m_cpSelf"));


CInstantMapMgr::CInstantMapMgr()
{
	m_bOK = false;

	if( this->CInstantMapMgr::Create() )
		m_bOK = true;
}


CInstantMapMgr::~CInstantMapMgr()
{
	this->CInstantMapMgr::Destroy();
}


void CInstantMapMgr::NotifyAllInstantMap(const int in_ZSVR, const unsigned long& in_ZSVRRegisteredMgrFUCnt)
{
	for( CONTAINER_ITER iter = m_Container.begin(); iter != m_Container.end(); ++iter )
	{
		CInstantMap* map = iter->second;

		if( map->CInstantMap::IsOperation() )
		{
			unsigned long cnt = map->CInstantMap::GetZSVRregisteredFUCnt();
			if( cnt != 0 && in_ZSVRRegisteredMgrFUCnt > cnt )
				InstantMap::SendPacket_IZ_INSTANTMAP_ADD3(in_ZSVR, map->CInstantMap::GetZSID(), map->CInstantMap::GetMapID(), map->CInstantMap::GetMapType(), map->CInstantMap::GetMapName(), true);
		}
	}
}


void CInstantMapMgr::Process()
{
	for( CONTAINER_ITER iter = m_Container.begin(); iter != m_Container.end(); )
	{
		CInstantMap* map = iter->second;

		if( map->CInstantMap::IsDestoryReady() )
		{
			m_IndexMap.erase(map->CInstantMap::GetMapName());
			delete map;
			iter = m_Container.erase(iter);
		}
		else
		{
			map->CInstantMap::Process();
			++iter;
		}
	}
}


bool CInstantMapMgr::InstantMapDestory(const unsigned int in_FromInter, const std::string in_Name)
{
	INDEXMAP_ITER idxiter = m_IndexMap.find(in_Name);
	if( idxiter == m_IndexMap.end() )
		return false;

	unsigned int hInstantMap = idxiter->second;
	CONTAINER_ITER iter = m_Container.find(hInstantMap);
	if( iter == m_Container.end() )
		return false;

	CInstantMap* map = iter->second;
	N3MessageMgr::GetObj()->N3MessageMgr::Post(map->N3Object::GetMyID(), N3MSGID(CInstantMap,MSG_DYING_WISH_REQUEST2), 0, 0);
	return true;
}


std::pair<bool,std::string> CInstantMapMgr::InstantMapCreate(const unsigned int in_FromInter, const int in_TargetZSID, const std::string in_Name, const int in_mapType)
{
	CInstantMap* map = new(std::nothrow) CInstantMap(in_FromInter, in_TargetZSID, in_Name, in_mapType);
	if( map == NULL )
	{
		return std::pair<bool,std::string>(false, "(NULL == cpInstantMap)");
	}

	if( !map->CInstantMap::isOK() )
	{
		delete map;
		return std::pair<bool,std::string>(false, "cpInstantMap->isOK()");
	}

	std::pair<CONTAINER_ITER,bool> container_ret = m_Container.insert(std::pair<const unsigned int,CInstantMap*>(map->N3Object::GetMyID(), map));
	if( !container_ret.second )
	{
		delete map;
		return std::pair<bool,std::string>(false, "m_Container.insert()");
	}

	std::pair<INDEXMAP_ITER,bool> index_ret = m_IndexMap.insert(std::make_pair(map->CInstantMap::GetMapName(), map->N3Object::GetMyID()));
	if( !index_ret.second )
	{
		m_Container.erase(container_ret.first);
		delete map;
		return std::pair<bool,std::string>(false, "m_IndexMap.insert()");
	}

	return std::pair<bool,std::string>(true, "good");
}


std::string CInstantMapMgr::GetInstantMapName(const unsigned int in_hInstantMap)
{
	CONTAINER_ITER iter = m_Container.find(in_hInstantMap);
	if( iter == m_Container.end() )
		return "";

	CInstantMap* map = iter->second;
	return map->CInstantMap::GetMapName();
}


bool CInstantMapMgr::Create()
{
	if( !CInstantMapConfiguration::CreateInstance() || !CInstantMapIDGenerator::CreateInstance() )
		return false;

	char encBuf[256];
	GetPrivateProfileStringA("ETC", "DB", "", encBuf, 64, g_infFile);

	char dbPWD[256];
	Decrypt(encBuf, (unsigned char*)dbPWD);

	std::string connectionstr = std::string("FILEDSN=.\\") + std::string(IPINFO_DSN_FILE) + std::string(";PWD=") + std::string(dbPWD);
	//NOTE: 18 lines missing here

	return true;
}


void CInstantMapMgr::Destroy()
{
	for( CONTAINER_ITER iter = m_Container.begin(); iter != m_Container.end(); ++iter )
		delete iter->second;

	m_Container.clear();
	m_IndexMap.clear();

	CInstantMapIDGenerator::DestoryInstance();
	CInstantMapConfiguration::DestroyInstance();
}


bool CInstantMapMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CInstantMapMgr();
	if( m_cpSelf == NULL )
		return false;
	
	if( !m_cpSelf->CInstantMapMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CInstantMapMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CInstantMapMgr* CInstantMapMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


const bool CInstantMapMgr::isOK() const
{
	return m_bOK;
}


const int CInstantMapMgr::GetNum() const
{
	return m_Container.size();
}
