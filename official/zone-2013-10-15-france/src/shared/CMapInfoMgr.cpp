#include "Enum.h"
#include "shared/CMapInfoMgr.h"
#include "shared/N3System/N3ODBCCtrl.h"
#include "shared/N3System/N3ODBCHandler.h"


/// singleton instance
CMapInfoMgr*& CMapInfoMgr::m_cpSelf = VTOR<CMapInfoMgr*>(DetourFindFunction(EXEPATH(), "CMapInfoMgr::m_cpSelf"));


CMapInfoMgr::CMapInfoMgr(const std::string in_ConnectionString)
{
	m_bOK = false;

	if( this->CMapInfoMgr::Create(in_ConnectionString) )
		m_bOK = true;
}


CMapInfoMgr::~CMapInfoMgr()
{
	this->CMapInfoMgr::Destroy();
}


bool CMapInfoMgr::Create(const std::string in_ConnectionString)
{
	std::pair<bool,std::string> ret = this->CMapInfoMgr::LoadMapInfo(in_ConnectionString);
	if( !ret.first )
	{
		MessageBoxA(NULL, ret.second.c_str(), "CMapInfoMgr", MB_OK);
		return false;
	}

	return true;
}


void CMapInfoMgr::Destroy()
{
}


bool CMapInfoMgr::CreateInstance(const std::string in_ConnectionString)
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CMapInfoMgr(in_ConnectionString);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMapInfoMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMapInfoMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMapInfoMgr* CMapInfoMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CMapInfoMgr::isOK() const
{
	return m_bOK;
}


std::pair<bool,std::string> CMapInfoMgr::LoadMapInfo(const std::string in_ConnectionString)
{
	N3ODBCCtrl ODBCCtrl;
	if( !ODBCCtrl.N3ODBCCtrl::Connect(in_ConnectionString) )
		return std::pair<bool,std::string>(false, "ODBC connect fail");

	N3ODBCHandler Handler(ODBCCtrl);
	std::string query = "select ZSID, MapName, MapID, type from MapInfo";
	if( !SQL_SUCCEEDED(Handler.N3ODBCHandler::ExecDirect(query)) )
	{
		Handler.N3ODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return std::pair<bool,std::string>(false, "ExecDirect:" + query);
	}

	int ZSID = 0;
	char name[24] = {};
	int MapID = 0;
	int type = 0;
	SQLINTEGER cbAID = 0;
	SQLINTEGER cbChar = SQL_NTS;

	Handler.N3ODBCHandler::BindCol(1, SQL_C_SLONG, (SQLPOINTER*)&ZSID, 0, &cbAID);
	Handler.N3ODBCHandler::BindCol(2, SQL_C_CHAR, (SQLPOINTER*)name, 24, &cbChar);
	Handler.N3ODBCHandler::BindCol(3, SQL_C_SLONG, (SQLPOINTER*)&MapID, 0, &cbAID);
	Handler.N3ODBCHandler::BindCol(4, SQL_C_SLONG, (SQLPOINTER*)&type, 0, &cbAID);

	while( 1 )
	{
		SQLRETURN ret = Handler.N3ODBCHandler::Fetch();
		if( ret == SQL_NO_DATA )
			break; // done.

		if( !SQL_SUCCEEDED(ret) )
		{
			Handler.N3ODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
			return std::pair<bool,std::string>(false, "Fetch");
		}

		CMapInfo mapinfo;
		mapinfo.MapID = MapID;
		mapinfo.ZSID = ZSID;
		mapinfo.type = type;
		strncpy_s(mapinfo.Name, countof(mapinfo.Name), name, _TRUNCATE);
		mapinfo.bPlayerEnter = true;

		if( !m_MapInfoTbl.insert(std::pair<const unsigned int,CMapInfo>(MapID, mapinfo)).second )
		{
			char buffer[260] = {};
			_snprintf_s(buffer, countof(buffer), _TRUNCATE, "m_MapInfoTbl insert fail\n %s(%d)", mapinfo.Name, mapinfo.MapID);
			return std::pair<bool,std::string>(false, buffer);
		}

		if( !m_MappingTbl.insert(std::pair<const std::string,unsigned int>(mapinfo.Name, mapinfo.MapID)).second )
		{
			char buffer[260] = {};
			_snprintf_s(buffer, countof(buffer), _TRUNCATE, "m_MappingTbl insert fail\n %s(%d)", mapinfo.Name, mapinfo.MapID);
			return std::pair<bool,std::string>(false, buffer);
		}
	}

	return std::pair<bool,std::string>(true, "good");
}


int CMapInfoMgr::GetServerID(const std::string in_mapName) const
{
	MAPPINGTBL::const_iterator mIter = m_MappingTbl.find(in_mapName);
	if( mIter == m_MappingTbl.end() )
		return -1;

	MAPINFOTBL::const_iterator iter = m_MapInfoTbl.find(mIter->second);
	if( iter == m_MapInfoTbl.end() )
		return -1;

	return iter->second.ZSID;
}


bool CMapInfoMgr::IsSiege(const std::string in_mapName) const
{
	MAPPINGTBL::const_iterator mIter = m_MappingTbl.find(in_mapName);
	if( mIter == m_MappingTbl.end() )
		return false;

	MAPINFOTBL::const_iterator iter = m_MapInfoTbl.find(mIter->second);
	if( iter == m_MapInfoTbl.end() )
		return false;

	return ( iter->second.type == MAPTYPE_AGIT );
}


bool CMapInfoMgr::InstantMapAdd2(const CMapInfo& in_MapInfo)
{
	if( !m_MapInfoTbl.insert(std::pair<const unsigned int,CMapInfo>(in_MapInfo.MapID, in_MapInfo)).second )
		return false;

	m_MappingTbl.insert(std::pair<const std::string,unsigned int>(in_MapInfo.Name, in_MapInfo.MapID));
	return true;
}


void CMapInfoMgr::InstantMapRemove(const std::string in_mapName)
{
	MAPPINGTBL::iterator mIter = m_MappingTbl.find(in_mapName);
	if( mIter == m_MappingTbl.end() )
		return;

	MAPINFOTBL::iterator iter = m_MapInfoTbl.find(mIter->second);
	if( iter == m_MapInfoTbl.end() )
		return;

	m_MappingTbl.erase(mIter);
	m_MapInfoTbl.erase(iter);
}


bool CMapInfoMgr::GetPlayerEnter(const std::string in_mapName) const
{
	MAPPINGTBL::const_iterator mIter = m_MappingTbl.find(in_mapName);
	if( mIter == m_MappingTbl.end() )
		return false;

	MAPINFOTBL::const_iterator iter = m_MapInfoTbl.find(mIter->second);
	if( iter == m_MapInfoTbl.end() )
		return false;

	return iter->second.bPlayerEnter;
}


void CMapInfoMgr::SetPlayerEnter(const unsigned int in_MapID, const bool in_bPlayerEnter)
{
	MAPINFOTBL::iterator iter = m_MapInfoTbl.find(in_MapID);
	if( iter == m_MapInfoTbl.end() )
		return;

	iter->second.bPlayerEnter = in_bPlayerEnter;
}


void CMapInfoMgr::SetPlayerEnter(const std::string in_mapName, const bool in_bPlayerEnter)
{
	MAPPINGTBL::iterator mIter = m_MappingTbl.find(in_mapName);
	if( mIter == m_MappingTbl.end() )
		return;

	MAPINFOTBL::iterator iter = m_MapInfoTbl.find(mIter->second);
	if( iter == m_MapInfoTbl.end() )
		return;

	iter->second.bPlayerEnter = in_bPlayerEnter;
}


std::pair<bool,CMapInfo> CMapInfoMgr::GetMapInfo(const int MapID) const
{
	MAPINFOTBL::const_iterator iter = m_MapInfoTbl.find(MapID);
	if( iter == m_MapInfoTbl.end() )
		return std::make_pair(false, CMapInfo());

	return std::make_pair(true, iter->second);
}


std::vector<int> CMapInfoMgr::GetMapIDList() const
{
	std::vector<int> result;

	for( MAPINFOTBL::const_iterator iter = m_MapInfoTbl.begin(); iter != m_MapInfoTbl.end(); ++iter )
		result.push_back(iter->second.MapID);

	return result;
}


std::pair<int,bool> CMapInfoMgr::GetZSVRandPlayerEnter(const std::string in_mapName)
{
	MAPPINGTBL::iterator mIter = m_MappingTbl.find(in_mapName);
	if( mIter == m_MappingTbl.end() )
		return std::pair<int,bool>(-1, false);

	MAPINFOTBL::iterator iter = m_MapInfoTbl.find(mIter->second);
	if( iter == m_MapInfoTbl.end() )
		return std::pair<int,bool>(-1, false);

	return std::pair<int,bool>(iter->second.ZSID, iter->second.bPlayerEnter);
}
