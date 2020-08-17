#include "DGNpcMgr.h"


/// singleton instance
CDGNpcMgr*& CDGNpcMgr::m_cpSelf = VTOR<CDGNpcMgr*>(DetourFindFunction(EXEPATH(), "CDGNpcMgr::m_cpSelf"));


CDGNpcMgr::CDGNpcMgr()
{
	this->CDGNpcMgr::Clear();
}


CDGNpcMgr::~CDGNpcMgr()
{
	this->CDGNpcMgr::Clear();
}


void CDGNpcMgr::Clear()
{
	for( TMAP::iterator iter = m_map.begin(); iter != m_map.end(); ++iter ) //NOTE: infinite loop in official code
		delete iter->second;

	m_map.clear();
}


bool CDGNpcMgr::AddInstantMap(const char* mapName)
{
	if( this->CDGNpcMgr::FindDunGeonBin(mapName) )
		return false;

	CDGNpcBin* dgn = new(std::nothrow) CDGNpcBin();
	if( dgn == NULL )
		return false;

	if( !dgn->CDGNpcBin::LoadScriptBin(mapName) )
	{
//		delete dgn; //FIXME: memleak
		return false;
	}

	m_map.insert(std::pair<const std::string,CDGNpcBin*>(mapName, dgn));
	return true;
}


void CDGNpcMgr::DeleteDunGeon(const char* mapName)
{
	CDGNpcBin* dgn = this->CDGNpcMgr::FindDunGeonBin(mapName);
	if( dgn != NULL )
		delete dgn;
	m_map.erase(mapName);
}


CDGNpcBin* CDGNpcMgr::FindDunGeonBin(const char* mapName)
{
	TMAP::iterator iter = m_map.find(mapName);
	if( iter == m_map.end() )
		return NULL;

	return iter->second;
}


CDGNpcMgr* CDGNpcMgr::GetObj()
{
	if( m_cpSelf == NULL )
		m_cpSelf = new CDGNpcMgr();

	return m_cpSelf;
}
