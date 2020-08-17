#include "CharacterLogDB.h"
#include "Common/DatabaseStatement.h"


/// singleton instance
static CCharacterLogDB gCCharacterLogDB;
CCharacterLogDB* CSingleton<CCharacterLogDB>::ms_Singleton;
const std::string CCharacterLogDB::m_strFileDSNfileName = "characterlog.dsn";


CCharacterLogDB::CCharacterLogDB()
{
}


CCharacterLogDB::~CCharacterLogDB()
{
}


BOOL CCharacterLogDB::DeleteCharaterLog(const unsigned long GID, const unsigned long AID, const char* pDeleteCharname, const char* szIP)
{
	BOOL result;
	m_csCharacterLogDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call deleteCharLog(%d, %d, %s, %s)}", GID, AID, pDeleteCharname, szIP);

	result = FALSE;
	if( SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		result = TRUE;

	m_csCharacterLogDB.Leave();
	return result;
}


void CCharacterLogDB::SetPwd(const char* in_szPwd)
{
	m_strPwd = in_szPwd;
}


bool CCharacterLogDB::Connect()
{
	return this->CDatabase::Connect(m_strFileDSNfileName.c_str(), m_strPwd.c_str());
}
