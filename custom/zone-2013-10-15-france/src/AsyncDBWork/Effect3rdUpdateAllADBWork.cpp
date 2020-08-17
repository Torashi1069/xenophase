#include "AsyncDBWork/Effect3rdUpdateAllADBWork.h"


CEffect3rdUpdateAllADBWork::CEffect3rdUpdateAllADBWork(const unsigned long in_AID, const unsigned long in_GID)
: NAsyncDBWork(TYPE_EFFECT3RD_UPDATEALL), m_Result(RESULT_ERROR_UNKNOWN), m_GID(in_GID), m_AID(in_AID), m_List()
{
	this->NAsyncDBWork::Init(in_AID);
}


CEffect3rdUpdateAllADBWork::~CEffect3rdUpdateAllADBWork()
{
}


const unsigned long CEffect3rdUpdateAllADBWork::GetAID()
{
	return m_AID;
}


const unsigned long CEffect3rdUpdateAllADBWork::GetGID()
{
	return m_GID;
}


const CEffect3rdUpdateAllADBWork::enumResult CEffect3rdUpdateAllADBWork::GetResult()
{
	return m_Result;
}


bool CEffect3rdUpdateAllADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = RESULT_ERROR_UNKNOWN;

	if( m_List.size() != 0 )
	{
		NAsyncDBWork::enumRETURN ret = this->NAsyncDBWork::SaveEffect3rd(in_ODBCCtrl, m_GID, m_List);
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			m_Result = RESULT_ERROR_UNKNOWN;
			return ( ret != NAsyncDBWork::RETURN_ERROR_ODBC );
		}
	}

	m_Result = RESULT_SUCCESS;
	return true;
}
