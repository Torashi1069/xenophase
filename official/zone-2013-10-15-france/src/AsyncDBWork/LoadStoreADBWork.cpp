#include "AsyncDBWork/LoadStoreADBWork.h"
#include "AsyncDBWork/NODBCHandler.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/ZLib.h"


CLoadStoreADBWork::CLoadStoreADBWork()
: NAsyncDBWork(TYPE_LOAD_STORE),
  m_AID(0),
  m_GID(0),
  m_Result(RESULT_ERROR_UNKNOWN),
//m_Data(),
  m_Length(0)
{
}


CLoadStoreADBWork::~CLoadStoreADBWork()
{
}


const CLoadStoreADBWork::enumResult CLoadStoreADBWork::GetResult() const
{
	return m_Result;
}


const unsigned long CLoadStoreADBWork::GetGID() const
{
	return m_GID;
}


const unsigned long CLoadStoreADBWork::GetAID() const
{
	return m_AID;
}


void CLoadStoreADBWork::Init(const unsigned long in_AID, const unsigned long in_GID)
{
	this->NAsyncDBWork::Init(in_AID);
//	memset(m_Data, 0x00, sizeof(m_Data));
	m_Length = 0;
	m_AID = in_AID;
	m_GID = in_GID;
	m_Result = RESULT_ERROR_UNKNOWN;
}


bool CLoadStoreADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = RESULT_SUCCESS;

	NAsyncDBWork::enumRETURN ret = this->CLoadStoreADBWork::LoadStore(in_ODBCCtrl);
	switch( ret )
	{
	case NAsyncDBWork::RETURN_SUCCESS:
		return true;
	break;
	case NAsyncDBWork::RETURN_ERROR_ODBC:
		m_Result = RESULT_ERROR_LOAD_STORE;
		return false;
	break;
	case NAsyncDBWork::RETURN_NO_DATA:
	{
		NAsyncDBWork::enumRETURN ret2 = this->CLoadStoreADBWork::InsertStore(in_ODBCCtrl);
		if( ret2 != NAsyncDBWork::RETURN_SUCCESS )
		{
			m_Result = RESULT_ERROR_LOAD_STORE_INSERT;
			if( ret2 == NAsyncDBWork::RETURN_ERROR_ODBC )
				return false;
		}

		return true;
	}
	break;
	default:
		m_Result = RESULT_ERROR_LOAD_STORE;
		return true;
	break;
	};
}


NAsyncDBWork::enumRETURN CLoadStoreADBWork::LoadStore(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	m_Length = -1;

	SQLINTEGER cbAID = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_AID, 0, &cbAID);

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call GetItemStore(?)}");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	unsigned char ZipBuffer[16300] = {};
	SQLINTEGER cbstoredbin = SQL_NTS;
	Handler.NODBCHandler::BindCol(1, SQL_C_BINARY, ZipBuffer, sizeof(ZipBuffer), &cbstoredbin);

	SQLRETURN sqlRet2 = Handler.NODBCHandler::Fetch();
	if( sqlRet2 < SQL_SUCCESS )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	if( sqlRet2 > SQL_SUCCESS_WITH_INFO )
	{
		if( sqlRet2 == SQL_NO_DATA )
		{
			m_Length = 0;
			return NAsyncDBWork::RETURN_NO_DATA;
		}

		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	if( cbstoredbin == -1 )
	{
		*(DWORD*)&m_Data[0] = 4;
		m_Length = 2;
		return NAsyncDBWork::RETURN_SUCCESS;
	}

	unsigned short Version = *(unsigned short*)ZipBuffer;
	if( Version == 3 || Version == 4 )
	{
		CZLib zlib;
		unsigned long UnzipLength = sizeof(ZipBuffer) - 2;
		int zRet = zlib.CZLib::Uncompress(m_Data + 2, &UnzipLength, ZipBuffer + 2, cbstoredbin - 2);
		if( zRet != 0 ) // Z_OK
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "stored item uncompress: error %d, AID:%d,GID:%d\n", zRet, m_AID, m_GID);
			return NAsyncDBWork::RETURN_ERROR;
		}

		*(unsigned short*)&m_Data[0] = Version;
		m_Length = sizeof(unsigned short) + UnzipLength;
		return NAsyncDBWork::RETURN_SUCCESS;
	}
	else
	{
		m_Length = cbstoredbin;
		memcpy_s(m_Data, sizeof(m_Data), ZipBuffer, cbstoredbin);
		return NAsyncDBWork::RETURN_SUCCESS;
	}
}


NAsyncDBWork::enumRETURN CLoadStoreADBWork::InsertStore(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbAID = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_AID, 0, &cbAID);

	SQLINTEGER sqlRet = Handler.NODBCHandler::ExecDirect("{call InsertStoreItem(?)}");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}
