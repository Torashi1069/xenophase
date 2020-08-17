#include "AsyncDBWork/ElementalCreateADBWork.h"
#include "AsyncDBWork/NODBCHandler.h"


CElementalCreateADBWork::CElementalCreateADBWork(const unsigned long in_AID, const unsigned long in_GID, const ElementalStuff::enumKind in_Kind, const ElementalStuff::enumScale in_Scale, const ElementalStuff::ESummaryData& in_SummaryData, const int in_LifeTM, const int in_ReduceSPAmount)
: NAsyncDBWork(TYPE_ELEMENTAL_CREATE),
  m_Result(RESULT_ERROR_UNKNOWN),
  m_GID(in_GID),
  m_Kind(in_Kind),
  m_Scale(in_Scale),
  m_SummaryData(in_SummaryData),
  m_LifeTM(in_LifeTM),
  m_ReduceSPAmount(in_ReduceSPAmount)
{
	this->NAsyncDBWork::Init(in_AID);
}


CElementalCreateADBWork::~CElementalCreateADBWork()
{
}


unsigned long CElementalCreateADBWork::GetGID()
{
	return m_GID;
}


CElementalCreateADBWork::enumResult CElementalCreateADBWork::GetResult()
{
	return m_Result;
}


ElementalStuff::enumKind CElementalCreateADBWork::GetKind()
{
	return m_Kind;
}


ElementalStuff::enumScale CElementalCreateADBWork::GetScale()
{
	return m_Scale;
}


ElementalStuff::ESummaryData CElementalCreateADBWork::GetSummaryData()
{
	return m_SummaryData;
}


int CElementalCreateADBWork::GetLifeTM()
{
	return m_LifeTM;
}


int CElementalCreateADBWork::GetReduceSPAmount()
{
	return m_ReduceSPAmount;
}


bool CElementalCreateADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = RESULT_SUCCESS;

	NAsyncDBWork::enumRETURN ret = this->CElementalCreateADBWork::Create(in_ODBCCtrl);
	if( ret != NAsyncDBWork::RETURN_SUCCESS )
	{
		m_Result = RESULT_ERROR_ELEMENTAL_CREATE;
		if( ret == NAsyncDBWork::RETURN_ERROR_ODBC )
			return false;
	}

	return true;
}


NAsyncDBWork::enumRETURN CElementalCreateADBWork::Create(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbInt = 0;
	int result = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_OUTPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &result, sizeof(result), &cbInt);
	Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<unsigned long*>(&m_GID), sizeof(m_GID), &cbInt);
	Handler.NODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<ElementalStuff::enumKind*>(&m_Kind), sizeof(m_Kind), &cbInt);
	Handler.NODBCHandler::BindParameter(4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<ElementalStuff::enumScale*>(&m_Scale), sizeof(m_Scale), &cbInt);
	Handler.NODBCHandler::BindParameter(5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_SummaryData.m_hp), sizeof(m_SummaryData.m_hp), &cbInt);
	Handler.NODBCHandler::BindParameter(6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_SummaryData.m_maxhp), sizeof(m_SummaryData.m_maxhp), &cbInt);
	Handler.NODBCHandler::BindParameter(7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_SummaryData.m_sp), sizeof(m_SummaryData.m_sp), &cbInt);
	Handler.NODBCHandler::BindParameter(8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_SummaryData.m_maxsp), sizeof(m_SummaryData.m_maxsp), &cbInt);
	Handler.NODBCHandler::BindParameter(9, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_SummaryData.m_atk), sizeof(m_SummaryData.m_atk), &cbInt);
	Handler.NODBCHandler::BindParameter(10, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_SummaryData.m_matk), sizeof(m_SummaryData.m_matk), &cbInt);
	Handler.NODBCHandler::BindParameter(11, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_SummaryData.m_attackMT), sizeof(m_SummaryData.m_attackMT), &cbInt);
	Handler.NODBCHandler::BindParameter(12, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_SummaryData.m_def), sizeof(m_SummaryData.m_def), &cbInt);
	Handler.NODBCHandler::BindParameter(13, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_SummaryData.m_mdef), sizeof(m_SummaryData.m_mdef), &cbInt);
	Handler.NODBCHandler::BindParameter(14, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_SummaryData.m_flee), sizeof(m_SummaryData.m_flee), &cbInt);
	Handler.NODBCHandler::BindParameter(15, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&m_SummaryData.m_hit), sizeof(m_SummaryData.m_hit), &cbInt);

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{?=call usp_elemental_create(?,?,?,?,?,?,?,?,?,?,?,?,?,?)}");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	if( result != 1 )
		return NAsyncDBWork::RETURN_ERROR;

	return NAsyncDBWork::RETURN_SUCCESS;
}
