#include "CharacterLogDB.h"
#include "Common/DatabaseStatement.h"


/// singleton instance
static CCharacterLogDB gCCharacterLogDB;
CCharacterLogDB* CSingleton<CCharacterLogDB>::ms_Singleton;


CCharacterLogDB::CCharacterLogDB()
{
}


CCharacterLogDB::~CCharacterLogDB()
{
}


BOOL CCharacterLogDB::DeleteCharaterLog(unsigned long GID, unsigned long AID, char* pDeleteCharname, char* szIP)
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
