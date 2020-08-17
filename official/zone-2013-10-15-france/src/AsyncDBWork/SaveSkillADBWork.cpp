#include "AsyncDBWork/NODBCHandler.h"
#include "AsyncDBWork/SaveSkillADBWork.h"


CSaveSkillADBWork::CSaveSkillADBWork(const unsigned long in_AID, const unsigned long in_GID)
: NAsyncDBWork(TYPE_SAVE_SKILL),
  m_AID(in_AID),
  m_GID(in_GID),
  m_Result(RESULT_ERROR_UNKNOWN),
//m_Data(),
  m_Length(0)
{
}


CSaveSkillADBWork::~CSaveSkillADBWork()
{
}


const unsigned long CSaveSkillADBWork::GetGID() const
{
	return m_GID;
}


const unsigned long CSaveSkillADBWork::GetAID() const
{
	return m_AID;
}


const CSaveSkillADBWork::enumResult CSaveSkillADBWork::GetResult() const
{
	return m_Result;
}


bool CSaveSkillADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = RESULT_ERROR_UNKNOWN;

	NAsyncDBWork::enumRETURN ret = this->CSaveSkillADBWork::SaveSkill(in_ODBCCtrl);
	if( ret != NAsyncDBWork::RETURN_SUCCESS )
	{
		m_Result = RESULT_ERROR_SAVE_SKILL;
		if( ret == NAsyncDBWork::RETURN_ERROR_ODBC )
			return false;
	}

	return true;
}


NAsyncDBWork::enumRETURN CSaveSkillADBWork::SaveSkill(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbGID = 0;
	if( m_Length <= 0 )
	{
		Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<unsigned long*>(&m_GID), 0, &cbGID);

		SQLRETURN ret = Handler.NODBCHandler::ExecDirect("{call UpdateSkill(NULL, ?)}");
		if( !SQL_SUCCEEDED(ret) )
		{
			Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
			return NAsyncDBWork::RETURN_ERROR_ODBC;
		}
	}
	else
	{
		SQLINTEGER cbequipbin = m_Length;
		Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, m_Length, 0, m_Data, 0, &cbequipbin);
		Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<unsigned long*>(&m_GID), 0, &cbGID);

		SQLRETURN ret = Handler.NODBCHandler::ExecDirect("{call UpdateSkill(?, ?)}");
		if( !SQL_SUCCEEDED(ret) )
		{
			Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
			return NAsyncDBWork::RETURN_ERROR_ODBC;
		}
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}
