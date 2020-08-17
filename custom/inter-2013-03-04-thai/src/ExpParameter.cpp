#include "ExpParameter.h"


CExpParameter::CExpParameter()
{
}


CExpParameter::~CExpParameter()
{
}


void CExpParameter::Init(const char* script, const char* dbPassword)
{
	this->CODBC::Init(script, dbPassword);
	this->CExpParameter::GetGuildExpParameter();
	this->CODBC::Reset();
}


void CExpParameter::GetGuildExpParameter()
{

	m_retcode = SQLAllocHandle(3, m_hdbc, &m_hstmt);
	if( SQL_SUCCEEDED(m_retcode) )
	{
		m_retcode = SQLExecDirectA(m_hstmt, (SQLCHAR*)"{call GetGuildexp}", SQL_NTS);

		short level;
		int exp;
		SQLINTEGER cbInt = 0;

		SQLBindCol(m_hstmt, 1, SQL_C_SSHORT, &level, 0, &cbInt);
		SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &exp, 0, &cbInt);

		for( int i = 0; i <= 100; ++i )
		{
			m_retcode = SQLFetch(m_hstmt);
			if( !SQL_SUCCEEDED(m_retcode) )
				break;

			m_guildexpValue[level] = exp;
		}

		SQLCloseCursor(m_hstmt);
	}

	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


int CExpParameter::GetGuildNextExp(short level)
{
	if( level >= 99 )
		return 99999999;

	std::map<short,int>::iterator iter = m_guildexpValue.find(level + 1);
	if( iter == m_guildexpValue.end() )
		return 0;

	return iter->second;
}
