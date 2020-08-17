#include "AsyncDBWork/SaveStoreADBWork.h"


CSaveStoreADBWork::CSaveStoreADBWork()
: NAsyncDBWork(TYPE_SAVE_STORE),
  m_Result(RESULT_ERROR_UNKNOWN),
  m_GID(0),
  m_AID(0)
//m_bAfterCloseStore(false),
//m_Data(),
//m_Length(0)
{
}


void CSaveStoreADBWork::Init(const unsigned long in_AID, const unsigned long in_GID, const bool in_bAfterCloseStore)
{
	this->NAsyncDBWork::Init(in_AID);
	m_GID = in_GID;
	m_AID = in_AID;
	m_bAfterCloseStore = in_bAfterCloseStore;
	m_Result = RESULT_ERROR_UNKNOWN;
}


CSaveStoreADBWork::~CSaveStoreADBWork()
{
}


const unsigned long CSaveStoreADBWork::GetAID() const
{
	return m_AID;
}


const unsigned long CSaveStoreADBWork::GetGID() const
{
	return m_GID;
}


const CSaveStoreADBWork::enumResult CSaveStoreADBWork::GetResult() const
{
	return m_Result;
}


bool CSaveStoreADBWork::IsCloseStore() const
{
	return m_bAfterCloseStore;
}


bool CSaveStoreADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = RESULT_ERROR_UNKNOWN;

	NAsyncDBWork::enumRETURN ret = this->NAsyncDBWork::SaveStoreItem(in_ODBCCtrl, m_AID, m_Data, m_Length);
	switch( ret )
	{
	case NAsyncDBWork::RETURN_SUCCESS:
		m_Result = RESULT_SUCCESS;
		return true;
	break;
	case NAsyncDBWork::RETURN_ERROR_ODBC:
		m_Result = RESULT_ERROR_SAVE_STORE;
		return false;
	break;
	case NAsyncDBWork::RETURN_ERROR:
		m_Result = RESULT_ERROR_SAVE_STORE;
		return true;
	break;
	default:
		m_Result = RESULT_ERROR_UNKNOWN;
		return false;
	break;
	};
}
