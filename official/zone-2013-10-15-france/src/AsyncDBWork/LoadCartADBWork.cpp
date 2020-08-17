#include "AsyncDBWork/LoadCartADBWork.h"
#include "AsyncDBWork/NODBCHandler.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/ZLib.h"


CLoadCartADBWork::CLoadCartADBWork()
: NAsyncDBWork(TYPE_LOAD_CART),
  m_AID(0),
  m_GID(0),
  m_Result(RESULT_ERROR_UNKNOWN),
//m_Data(),
  m_Length(0),
  m_SKLevel(0)
{
}


void CLoadCartADBWork::Init(const unsigned long in_AID, const unsigned long in_GID, const int in_SKLevel)
{
	this->NAsyncDBWork::Init(in_AID);
//	memset(m_Data, 0x00, sizeof(m_Data);
	m_Length = 0;
	m_GID = in_GID;
	m_AID = in_AID;
	m_Result = CLoadCartADBWork::RESULT_ERROR_UNKNOWN;
	m_SKLevel = in_SKLevel;
}


CLoadCartADBWork::~CLoadCartADBWork()
{
}


const CLoadCartADBWork::enumResult CLoadCartADBWork::GetResult() const
{
	return m_Result;
}


const unsigned long CLoadCartADBWork::GetGID() const
{
	return m_GID;
}


const unsigned long CLoadCartADBWork::GetAID() const
{
	return m_AID;
}


bool CLoadCartADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = CLoadCartADBWork::RESULT_SUCCESS;

	switch( this->CLoadCartADBWork::LoadCart(in_ODBCCtrl) )
	{
	case NAsyncDBWork::RETURN_SUCCESS:
		return true;
	break;
	case NAsyncDBWork::RETURN_ERROR_ODBC:
		m_Result = CLoadCartADBWork::RESULT_ERROR_LOAD_CART;
		return false;
	break;
	case NAsyncDBWork::RETURN_ERROR:
	default:
		m_Result = CLoadCartADBWork::RESULT_ERROR_LOAD_CART;
		return true;
	break;
	case NAsyncDBWork::RETURN_NO_DATA:
		switch( this->CLoadCartADBWork::InsertCart(in_ODBCCtrl) )
		{
		case NAsyncDBWork::RETURN_SUCCESS:
			return true;
		break;
		case NAsyncDBWork::RETURN_ERROR_ODBC:
			m_Result = CLoadCartADBWork::RESULT_ERROR_LOAD_CART_INSERT;
			return false;
		break;
		default:
			m_Result = CLoadCartADBWork::RESULT_ERROR_LOAD_CART_INSERT;
			return true;
		break;
		};
	break;
	};
}


NAsyncDBWork::enumRETURN CLoadCartADBWork::LoadCart(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);
	m_Length = -1;

	SQLINTEGER cbGID = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_GID, 0, &cbGID);

	if( !SQL_SUCCEEDED(Handler.NODBCHandler::ExecDirect("{call GetItemCart(?)}")) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "call GetItemCart(%d)", m_GID);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	BYTE ZipBuffer[16300];
	memset(ZipBuffer, 0x00, sizeof(ZipBuffer));

	SQLINTEGER cbcartbin = SQL_NTS;
	Handler.NODBCHandler::BindCol(1, SQL_C_BINARY, ZipBuffer, sizeof(ZipBuffer), &cbcartbin);

	SQLRETURN sqlRet = Handler.NODBCHandler::Fetch();
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		if( sqlRet == SQL_NO_DATA )
		{
			m_Length = 0;
			return NAsyncDBWork::RETURN_NO_DATA;
		}

		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	if( cbcartbin == SQL_NULL_DATA )
	{// `cartItem` column was NULL
		*(WORD*)m_Data = 4; // version
		m_Length = 2;
		return NAsyncDBWork::RETURN_SUCCESS;
	}

	WORD wVersion = *(WORD*)ZipBuffer;

	if( wVersion == 3 || wVersion == 4 || wVersion == 5 )
	{
		CZLib zlib;
		unsigned long UnzipLength = sizeof(ZipBuffer) - 2;
		int zRet = zlib.CZLib::Uncompress(m_Data + 2, &UnzipLength, ZipBuffer + 2, cbcartbin - 2);
		if( zRet != 0 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "cart item uncompress: error %d, AID:%d,GID:%d\n", zRet, m_AID, m_GID);
			return NAsyncDBWork::RETURN_ERROR;
		}

		*(WORD*)m_Data = wVersion;
		m_Length = UnzipLength + 2;
	}
	else
	{
		memcpy_s(m_Data, sizeof(m_Data), ZipBuffer, cbcartbin);
		m_Length = cbcartbin;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}


NAsyncDBWork::enumRETURN CLoadCartADBWork::InsertCart(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbGID = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_GID, 0, &cbGID);

	if( !SQL_SUCCEEDED(Handler.NODBCHandler::ExecDirect("{call InsertCartItem(?)}")) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "call InsertCartItem(%d)", m_GID);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}
