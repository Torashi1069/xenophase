#include "ODBCV2Connector.h"


CODBCV2Connector::CODBCV2Connector(SQLHENV const in_hENV, SQLHDBC const in_hDBC, mystd::string in_strDSN, mystd::string in_strID, mystd::string in_strPassword, mystd::string in_strDB, enum CODBCV2Connector::enumConnectType in_ConnectType) // line 21
: m_copyhENV(in_hENV), m_copyhDBC(in_hDBC), m_strDSN(in_strDSN), m_strID(in_strID), m_strPassword(in_strPassword), m_strDB(in_strDB), m_ConnectType(in_ConnectType), m_hThread(NULL), m_State(CState::STATE_DISCONNECT)
{
}


CODBCV2Connector::~CODBCV2Connector(void) // line 34
{
	if( m_hThread != NULL )
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	this->CODBCV2Connector::Disconnect();
}


hook_method<bool (CODBCV2Connector::*)(void)> CODBCV2Connector::_Connect(SERVER, "CODBCV2Connector::Connect");
bool CODBCV2Connector::Connect(void) // line 111
{
	return (this->*_Connect)();

	//TODO
}


hook_method<bool (CODBCV2Connector::*)(void)> CODBCV2Connector::_isConnect(SERVER, "CODBCV2Connector::isConnect");
bool CODBCV2Connector::isConnect(void) // line 50
{
	return (this->*_isConnect)();

	//TODO
}


hook_method<void (CODBCV2Connector::*)(void)> CODBCV2Connector::_AsyncConnect(SERVER, "CODBCV2Connector::AsyncConnect");
void CODBCV2Connector::AsyncConnect(void) // line 77
{
	return (this->*_AsyncConnect)();

	//TODO
}


hook_method<void (CODBCV2Connector::*)(void)> CODBCV2Connector::_Disconnect(SERVER, "CODBCV2Connector::Disconnect");
void CODBCV2Connector::Disconnect(void) // line 68
{
	return (this->*_Disconnect)();

	//TODO
}


hook_method<void (CODBCV2Connector::*)(void)> CODBCV2Connector::_SyncConnect(SERVER, "CODBCV2Connector::SyncConnect");
void CODBCV2Connector::SyncConnect(void) // line 58
{
	return (this->*_SyncConnect)();

	//TODO
}


CODBCV2Connector::CState::CState(const enum CODBCV2Connector::CState::enumState in_State) // line 155
{
	m_State = in_State;
	InitializeCriticalSection(&m_CS);
}


CODBCV2Connector::CState::~CState(void) // line ???
{
	DeleteCriticalSection(&m_CS);
}
