#include "Instant map/InstantMapConfiguration.h"
#include "Instant map/InstantMapMgr.h"
#include "Instant map/InstantMapWorkerThread.h"


/// singleton instance
CInstantMapMgr*& CInstantMapMgr::m_cpSelf = VTOR<CInstantMapMgr*>(DetourFindFunction(EXEPATH(), "CInstantMapMgr::m_cpSelf"));


CInstantMapMgr::CInstantMapMgr()
: m_InstantMapCtrlContainer(), m_bOK(false)
{
	if( this->CInstantMapMgr::Create() )
		m_bOK = true;
}


CInstantMapMgr::~CInstantMapMgr()
{
	this->CInstantMapMgr::Destory();
}


bool CInstantMapMgr::Create()
{
	if( !CInstantMapConfiguration::CreateInstance() )
		return false;

	if( !CInstantMapWorkerThread::CreateInstance() )
		return false;

	return true;
}


void CInstantMapMgr::Destory()
{
	//TODO
/*
	CInstantMapWorkerThread::DestoryInstance();

	for( INSTANTMAPCTRL_CONTAINER_ITER iter = m_InstantMapCtrlContainer.begin(); iter != m_InstantMapCtrlContainer.end(); ++iter )
		delete iter->second;

	m_InstantMapCtrlContainer.clear();

	CInstantMapConfiguration::DestroyInstance();
*/
}


bool CInstantMapMgr::Start()
{
	return CInstantMapWorkerThread::GetObj()->CInstantMapWorkerThread::Start();
}


void CInstantMapMgr::Stop()
{
	if( this == NULL )
		return;

	CInstantMapWorkerThread::GetObj()->CInstantMapWorkerThread::Stop();
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


void CInstantMapMgr::DestoryInstance()
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


void CInstantMapMgr::Process()
{
	//TODO
}


void CInstantMapMgr::RequestDestory(const int in_hInstantMapID, const std::string in_MapName)
{
	//TODO
}


bool CInstantMapMgr::RequestCreate(const unsigned int in_hRequestN2Obj, const int in_hInstantMapID, const std::string in_MapName, const int in_MapType)
{
	return false;
	//TODO
}


CInstantMapCtrl* CInstantMapMgr::GetInstantMapCtrlPtr(const std::string in_mapName, const int in_mapID)
{
	return NULL;
	//TODO
/*
	for( INSTANTMAPCTRL_CONTAINER_ITER iter = m_InstantMapCtrlContainer.begin(); iter != m_InstantMapCtrlContainer.end(); ++iter )
		if( iter->second->m_hInstantMapID == in_mapID && iter->second->CInstantMapCtrl::GetMapName() == in_mapName )
			return iter->second;

	return 0;
*/
}


void CInstantMapMgr::Add(const int in_ZSID, const std::string in_mapName, const int in_mapID, const int in_mapType, const bool in_bPlayerEnter)
{
	//TODO
}


void CInstantMapMgr::Remove(const int in_ZSID, const std::string in_mapName, const int in_mapID)
{
	//TODO
}


void CInstantMapMgr::SetPlayerEnter(const int in_mapID, const bool in_bPlayerEnter)
{
	//TODO
}


void CInstantMapMgr::DisconnectISVR()
{
	//TODO
}


int CInstantMapMgr::GetCtrlCount()
{
	return m_InstantMapCtrlContainer.size();
}
