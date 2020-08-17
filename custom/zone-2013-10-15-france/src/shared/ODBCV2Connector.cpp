#include "shared/NCriticalErrorLog.h"
#include "shared/ODBCV2Connector.h"
#include "shared/ODBCV2Util.h"


CODBCV2Connector::CODBCV2Connector(const SQLHENV in_hENV, const SQLHDBC in_hDBC, std::string in_strFileDSN, std::string in_strPassword, enumConncetType in_ConnectType)
: m_ConnectType(in_ConnectType), m_State(CState::STATE_DISCONNECT)
{
	m_copyhENV = in_hENV;
	m_copyhDBC = in_hDBC;
	m_hThread = NULL;
	m_strFileDSN = in_strFileDSN;
//	m_strID = in_strID;
	m_strPassword = in_strPassword;
//	m_strDB = in_strDB;
}


CODBCV2Connector::~CODBCV2Connector()
{
	if( m_hThread != NULL )
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	this->CODBCV2Connector::Disconnect();
}


bool CODBCV2Connector::isConnect()
{
	return ( m_State == CState::STATE_CONNECT );
}


void CODBCV2Connector::SyncConnect()
{
	if( m_State != CState::STATE_DISCONNECT )
		return;

	m_State = CState::STATE_CONNECT_TRY;

	if( this->CODBCV2Connector::Connect() )
		m_State = CState::STATE_CONNECT;
	else
		m_State = CState::STATE_DISCONNECT;
}


void CODBCV2Connector::Disconnect()
{
	if( m_State != CState::STATE_CONNECT )
		return;

	if( !SQL_SUCCEEDED(SQLDisconnect(m_copyhDBC)) )
		m_State = CState::STATE_DISCONNECT;
}


void CODBCV2Connector::AsyncConnect()
{
	if( m_State != CState::STATE_DISCONNECT )
		return;

	if( m_hThread != NULL )
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	unsigned int dwThreadID;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, &ThreadFunctionCaller, (void*)this, CREATE_SUSPENDED, &dwThreadID);
	if( m_hThread == NULL )
		return;

	SetThreadPriority(m_hThread, THREAD_PRIORITY_BELOW_NORMAL);
	m_State = CState::STATE_CONNECT_TRY;
	ResumeThread(m_hThread);
}


unsigned int __stdcall CODBCV2Connector::ThreadFunctionCaller(void* in_pParam)
{
	CODBCV2Connector* self = reinterpret_cast<CODBCV2Connector*>(in_pParam);

	if( self->CODBCV2Connector::Connect() )
		self->m_State = CState::STATE_CONNECT;
	else
		self->m_State = CState::STATE_DISCONNECT;

	return 1;
}


bool CODBCV2Connector::Connect()
{
	switch( m_ConnectType )
	{
	case DSN_CONNECT_TYPE:
	{
		if( !SQL_SUCCEEDED(SQLConnect(m_copyhDBC, (SQLCHAR*)m_strDSN.c_str(), SQL_NTS, (SQLCHAR*)m_strID.c_str(), SQL_NTS, (SQLCHAR*)m_strPassword.c_str(), SQL_NTS)) )
		{
			std::string strError = CODBCV2Util::GetObj()->CODBCV2Util::GetErrorString(SQL_HANDLE_DBC, m_copyhDBC);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", strError.c_str());
			return false;
		}
	}
	break;
	case DRIVER_CONNECT_TYPE:
	{
		char ConnStrIn[255];
		sprintf_s(ConnStrIn, countof(ConnStrIn), "DRIVER={SQL Server}; SERVER=%s; UID=%s; PWD=%s; DATABASE=%s; ", m_strDSN.c_str(), m_strID.c_str(), m_strPassword.c_str(), m_strDB.c_str());

		char ConnStrOut[255];
		SQLSMALLINT cbConnStrOut = 0;
		if( !SQL_SUCCEEDED(SQLDriverConnectA(m_copyhDBC, NULL, (SQLCHAR*)ConnStrIn, SQL_NTS, (SQLCHAR*)ConnStrOut, countof(ConnStrOut), &cbConnStrOut, SQL_DRIVER_NOPROMPT)) )
		{
			std::string strError = CODBCV2Util::GetObj()->CODBCV2Util::GetErrorString(SQL_HANDLE_DBC, m_copyhDBC);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", strError.c_str());
			return false;
		}
	}
	break;
	case FILE_DSN_CONNECT_TYPE:
	{
		std::string strConnectInfo = "FILEDSN=.\\" + m_strFileDSN + ";PWD=" + m_strPassword;

		char ConnStrOut[255];
		SQLSMALLINT cbConnStrOut = 0;
		if( !SQL_SUCCEEDED(SQLDriverConnectA(m_copyhDBC, NULL, (SQLCHAR*)strConnectInfo.c_str(), SQL_NTS, (SQLCHAR*)ConnStrOut, countof(ConnStrOut), &cbConnStrOut, SQL_DRIVER_NOPROMPT)) )
		{
			std::string strError = CODBCV2Util::GetObj()->CODBCV2Util::GetErrorString(SQL_HANDLE_DBC, m_copyhDBC);
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", strError.c_str());
			return false;
		}
	}
	break;
	default:
		return false;
	break;
	};

	return true;
}


CODBCV2Connector::CState::CState(const enumState in_State)
{
	m_State = CState::STATE_DISCONNECT;
	InitializeCriticalSection(&m_CS);
}


CODBCV2Connector::CState::~CState()
{
	DeleteCriticalSection(&m_CS);
}


CODBCV2Connector::CState::operator enumState()
{
	return m_State;
}


void CODBCV2Connector::CState::operator=(enumState in_rhs)
{
	EnterCriticalSection(&m_CS);
	m_State = in_rhs;
	LeaveCriticalSection(&m_CS);
}


bool CODBCV2Connector::CState::operator==(const enumState& in_Rhs)
{
	bool result;
	EnterCriticalSection(&m_CS);

	result = false;
	if( m_State == in_Rhs )
		result = true;

	LeaveCriticalSection(&m_CS);
	return result;
}


bool CODBCV2Connector::CState::operator!=(const enumState& in_Rhs)
{
	bool result;
	EnterCriticalSection(&m_CS);

	result = false;
	if( m_State != in_Rhs )
		result = true;

	LeaveCriticalSection(&m_CS);
	return result;
}
