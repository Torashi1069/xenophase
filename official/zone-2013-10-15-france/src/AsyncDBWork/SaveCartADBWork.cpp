#include "AsyncDBWork/SaveCartADBWork.h"


CSaveCartADBWork::CSaveCartADBWork()
: NAsyncDBWork(TYPE_SAVE_CART),
  m_Result(CSaveCartADBWork::RESULT_ERROR_UNKNOWN),
  m_GID(0),
  m_AID(0),
//m_Data(),
  m_Length(0)
{
}


void CSaveCartADBWork::Init(const unsigned long in_AID, const unsigned long in_GID)
{
	this->NAsyncDBWork::Init(in_AID);
//	memset(m_Data, 0x00, sizeof(m_Data);
	m_Length = 0;
	m_GID = in_GID;
	m_AID = in_AID;
	m_Result = CSaveCartADBWork::RESULT_ERROR_UNKNOWN;
}


CSaveCartADBWork::~CSaveCartADBWork()
{
}


const unsigned long CSaveCartADBWork::GetAID() const
{
	return m_AID;
}


const unsigned long CSaveCartADBWork::GetGID() const
{
	return m_GID;
}


const CSaveCartADBWork::enumResult CSaveCartADBWork::GetResult() const
{
	return m_Result;
}


bool CSaveCartADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = CSaveCartADBWork::RESULT_SUCCESS;

	NAsyncDBWork::enumRETURN ret = this->NAsyncDBWork::SaveCartItem(in_ODBCCtrl, m_GID, m_Data, m_Length);
	switch( ret )
	{
	case NAsyncDBWork::RETURN_SUCCESS:
		return true;
	break;
	case NAsyncDBWork::RETURN_ERROR_ODBC:
		m_Result = CSaveCartADBWork::RESULT_ERROR_SAVE_CART;
		return false;
	break;
	case NAsyncDBWork::RETURN_ERROR:
		m_Result = CSaveCartADBWork::RESULT_ERROR_SAVE_CART;
		return true;
	break;
	default:
		m_Result = CSaveCartADBWork::RESULT_ERROR_UNKNOWN;
		return false;
	break;
	};
}
