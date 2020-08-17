#include "PremiumServiceDB.h"
#include "Common/DatabaseStatement.h"


/// singleton instance
static CPremiumServiceDB gPCBangBonusDB;
CPremiumServiceDB* CSingleton<CPremiumServiceDB>::ms_Singleton;


CPremiumServiceDB::CPremiumServiceDB()
{
}


CPremiumServiceDB::~CPremiumServiceDB()
{
}


BOOL CPremiumServiceDB::GetExtraExpInfo(char* szIP, SExtraExp* pExraExp)
{
	BOOL result;
	m_csPremiumServiceDB.Enter();

	CDatabaseStatement stmt(this);
	stmt.CDatabaseStatement::Query("{call GetExtraExpInfo( %s )}", szIP);

	stmt.CDatabaseStatement::BindFloatColumn(1, &pExraExp->fExp1);
	stmt.CDatabaseStatement::BindFloatColumn(2, &pExraExp->fExp2);
	stmt.CDatabaseStatement::BindFloatColumn(3, &pExraExp->fdrp);

	result = TRUE;
	if( !SQL_SUCCEEDED(stmt.CDatabaseStatement::Fetch()) )
		result = FALSE;

	m_csPremiumServiceDB.Leave();
	return result;
}
