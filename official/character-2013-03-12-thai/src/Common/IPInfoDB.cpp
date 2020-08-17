#include "Common/DatabaseStatement.h"
#include "Common/IPInfoDB.h"
#include "Common/MapInfoList.h"


/// singleton instance
static CIPInfoDB g_IPInfoDB;
CIPInfoDB* CSingleton<CIPInfoDB>::ms_Singleton;
const std::string CIPInfoDB::m_strFileDSNfileName = "ipinfo.dsn";


CIPInfoDB::CIPInfoDB()
{
}


CIPInfoDB::~CIPInfoDB()
{
}


void CIPInfoDB::SetPwd(const char* in_szPwd)
{
	m_strPwd = in_szPwd;
}


bool CIPInfoDB::Connect()
{
	return this->CDatabase::Connect(m_strFileDSNfileName.c_str(), m_strPwd.c_str());
}


void CIPInfoDB::InitMapInfoList()
{
	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("SELECT * FROM MapInfo");

	SMAPINFO mapinfo;
	stmt.CDatabaseStatement::BindNumberColumn(1, &mapinfo.m_dwSID);
	stmt.CDatabaseStatement::BindStringColumn(2, mapinfo.m_szMapName, sizeof(mapinfo.m_szMapName));
	stmt.CDatabaseStatement::BindNumberColumn(3, &mapinfo.m_dwMapID);
	stmt.CDatabaseStatement::BindNumberColumn(4, &mapinfo.m_dwMapType);

	memset(&mapinfo, 0, sizeof(mapinfo));
	while( SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
	{
		CSingleton<CMapInfoList>::getSingletonPtr()->CMapInfoList::AddMapInfo(&mapinfo);
		printf("%4d %16s %4d %4d\n", mapinfo.m_dwSID, mapinfo.m_szMapName, mapinfo.m_dwMapID, mapinfo.m_dwMapType);
		memset(&mapinfo, 0, sizeof(mapinfo));
	}
}
