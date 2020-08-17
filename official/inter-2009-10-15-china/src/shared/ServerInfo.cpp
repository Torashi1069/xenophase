#include "ODBC.h"
#include "ServerInfo.h"
#include "NetLib/Acceptor.h"
#include "globals.hpp"
#include <sqlext.h>


CServerInfo::CServerInfo(void) // line 12
{
	m_characterServerCount = 0;
}


CServerInfo::~CServerInfo(void) // line 17
{
	mystd::map<int,_SERVERINFO*>::iterator it = m_serverInfoMap.begin();
	while( it != m_serverInfoMap.end() )
	{
		delete it->second;
		m_serverInfoMap.erase(it);
		it = m_serverInfoMap.begin();
	}
}


hook_method<int (CServerInfo::*)(void)> CServerInfo::_IsExistColumn(SERVER, "CServerInfo::IsExistColumn");
int CServerInfo::IsExistColumn(void) // line 374
{
	return (this->*_IsExistColumn)();

	CDBStatement st; // NOTE: unused?

	if( !st.CDBStatement::Init(m_hdbc) )
		return 0;

	m_retcode = SQLAllocHandle(SQL_NULL_HSTMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return 0;

	m_retcode = SQLPrepareA(m_hstmt, (SQLCHAR*)"EXEC sp_columns @table_name = ServerInfo, @column_name  = PrivateIP", SQL_NTS);
	m_retcode = SQLExecute(m_hstmt);

	int result = 0;
	if( SQL_SUCCEEDED(m_retcode) )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode != SQL_NO_DATA )
			result = 1;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != NULL )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return result;
}


hook_method<int (CServerInfo::*)(const char* ID, const char* Passwd, const char* dbname, int Type)> CServerInfo::_Init(SERVER, "CServerInfo::Init");
int CServerInfo::Init(const char* ID, const char* Passwd, const char* dbname, int Type) // line 30
{
	return (this->*_Init)(ID, Passwd, dbname, Type);

	this->CODBC::Init(dbname, ID, Passwd, dbname, 0);
	m_localServerType = Type;
	int result = this->CServerInfo::GetSvrInfoFromDB();
	this->CODBC::Reset();
	return result;
}


hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetSvrInfoFromDB(SERVER, "CServerInfo::GetSvrInfoFromDB");
int CServerInfo::GetSvrInfoFromDB(void) // line 55
{
	return (this->*_GetSvrInfoFromDB)();

	m_localServerInfo.ip = this->CServerInfo::GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS);
	m_localServerInfo.IPstr = ConvertIPaddr(m_localServerInfo.ip);
	int ExistColumn = this->CServerInfo::IsExistColumn();

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return 0;
	
	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return 0;

	int P_Port = 0;
	char P_IP[16];
	memset(P_IP, 0, sizeof(P_IP));

	int SID;
	int Type;
	char TargetValue[16];
	int Port;
	int DestinationOneSID;
	int DestinationTwoSID;
	char name[24];

	int cbAID = 0;
	int cbChar = SQL_NTS;
	int cbOneSID;
	int cbTwoSID;

	const char* query = ( ExistColumn )
		? "select  SID, Type, IP, Port, DestinationOneSID, DestinationTwoSID, SvrName, PrivateIP, PrivatePort from ServerInfo"
		: "select  SID, Type, IP, Port, DestinationOneSID, DestinationTwoSID, SvrName from ServerInfo";

	m_retcode = SQLPrepareA(m_hstmt, (SQLCHAR*)query, SQL_NTS);
	m_retcode = SQLExecute(m_hstmt);
	m_retcode = SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &SID,                0, (SQLINTEGER*)&cbAID);
	m_retcode = SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &Type,               0, (SQLINTEGER*)&cbAID);
	m_retcode = SQLBindCol(m_hstmt, 3, SQL_CHAR,    &TargetValue,       16, (SQLINTEGER*)&cbChar);
	m_retcode = SQLBindCol(m_hstmt, 4, SQL_C_SLONG, &Port,               0, (SQLINTEGER*)&cbAID);
	m_retcode = SQLBindCol(m_hstmt, 5, SQL_C_SLONG, &DestinationOneSID,  0, (SQLINTEGER*)&cbOneSID);
	m_retcode = SQLBindCol(m_hstmt, 6, SQL_C_SLONG, &DestinationTwoSID,  0, (SQLINTEGER*)&cbTwoSID);
	m_retcode = SQLBindCol(m_hstmt, 7, SQL_CHAR,    &name,              20, (SQLINTEGER*)&cbChar);
	if( ExistColumn )
	{
	m_retcode = SQLBindCol(m_hstmt, 8, SQL_CHAR,    &P_IP,              16, (SQLINTEGER*)&cbChar);
	m_retcode = SQLBindCol(m_hstmt, 9, SQL_C_SLONG, &P_Port,             0, (SQLINTEGER*)&cbAID);
	}

	int i = 0;
	while( (m_retcode = SQLFetch(m_hstmt)) != SQL_NO_DATA )
	{
		if( m_retcode == -4 ) //FIXME: undocumented retcode
			break;
		if( m_retcode == SQL_ERROR )
			break;

		if( cbOneSID == -1 )
			DestinationOneSID = 0;
		if( cbTwoSID == -1 )
			DestinationTwoSID = 0;

		_SERVERINFO* s = new _SERVERINFO;
		s->SID = SID;
		s->Type = Type;
		s->ip = inet_addr(TargetValue);
		s->IPstr = ConvertIPaddr(s->ip);
		s->Port = Port;
		s->DestinationOneSID = DestinationOneSID;
		s->DestinationTwoSID = DestinationTwoSID;
		memcpy(s->Name, name, sizeof(s->Name));
		if( ExistColumn != 0 )
		{
			s->PrivateIP = inet_addr(P_IP);
			s->PrivateIPstr = ConvertIPaddr(s->PrivateIP);
			s->PrivatePort = P_Port;

			memset(P_IP, 0, sizeof(P_IP));
			P_Port = 0;
		}

		m_serverInfoMap[SID] = s;

		char TempIP[256];
		sprintf(TempIP, "%d.%d.%d.%d", BYTE(s->ip >> 0), BYTE(s->ip >> 8), BYTE(s->ip >> 16), BYTE(s->ip >> 24));

		char TempIP2[256];
		sprintf(TempIP2, "%d.%d.%d.%d", BYTE(m_localServerInfo.ip >> 0), BYTE(m_localServerInfo.ip >> 8), BYTE(m_localServerInfo.ip >> 16), BYTE(m_localServerInfo.ip >> 24));
		Trace("GetSvrInfoFromDB:%d, serverName:%s, SID:%d, serverType:%d, localtype:%d, ip:%s, localip:%s, port:%d, DestinationOneSID:%d, DestinationTwoSID:%d\n", i, name, SID, Type, m_localServerType, TempIP, TempIP2, Port, DestinationOneSID, DestinationTwoSID);

		++i;

		if( (m_localServerInfo.ip == s->ip || m_localServerInfo.ip == s->PrivateIP) && m_localServerType == Type )
		{
			memcpy(m_localServerInfo.Name, name, sizeof(m_localServerInfo.Name));
			m_localServerInfo.Port = Port;
			m_localServerInfo.SID = SID;
			m_localServerInfo.Type = Type;
			m_localServerInfo.DestinationOneSID = DestinationOneSID;
			m_localServerInfo.DestinationTwoSID = DestinationTwoSID;
			Trace("HServerID:%d, IServerID:%d\n", DestinationOneSID, DestinationTwoSID);
		}
	}

	this->CServerInfo::SetCharacterServerInfo();

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return ExistColumn;
}


hook_method<int (CServerInfo::*)(int SID)> CServerInfo::_GetServerPort(SERVER, "CServerInfo::GetServerPort");
int CServerInfo::GetServerPort(int SID) // line 217
{
	return (this->*_GetServerPort)(SID);

	//TODO
}


hook_method<void (CServerInfo::*)(int SID, int port)> CServerInfo::_SetServerPort(SERVER, "CServerInfo::SetServerPort");
void CServerInfo::SetServerPort(int SID, int port) // line 227
{
	return (this->*_SetServerPort)(SID, port);

	//TODO
}


hook_method<unsigned long (CServerInfo::*)(int SID)> CServerInfo::_GetServerIPAddr(SERVER, "CServerInfo::GetServerIPAddr");
unsigned long CServerInfo::GetServerIPAddr(int SID) // line 207
{
	return (this->*_GetServerIPAddr)(SID);

	//TODO
}


hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetLocalPort(SERVER, "CServerInfo::GetLocalPort");
int CServerInfo::GetLocalPort(void) // line 65 (ServerInfo.h)
{
	return (this->*_GetLocalPort)();

	return m_localServerInfo.Port;
}


hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetCharacterServerInfoLength(SERVER, "CServerInfo::GetCharacterServerInfoLength");
int CServerInfo::GetCharacterServerInfoLength(void) // line 203
{
	return (this->*_GetCharacterServerInfoLength)();

	//TODO
}


hook_method<char* (CServerInfo::*)(void)> CServerInfo::_GetCharacterServerInfo(SERVER, "CServerInfo::GetCharacterServerInfo");
char* CServerInfo::GetCharacterServerInfo(void) // line 238
{
	return (this->*_GetCharacterServerInfo)();

	//TODO
}


hook_method<int (CServerInfo::*)(unsigned long IP, int Type)> CServerInfo::_IsValidServer(SERVER, "CServerInfo::IsValidServer");
int CServerInfo::IsValidServer(unsigned long IP, int Type) // line 243
{
	return (this->*_IsValidServer)(IP, Type);

	//TODO
}


hook_method<int (CServerInfo::*)(int target)> CServerInfo::_GetDestinationSID(SERVER, "CServerInfo::GetDestinationSID");
int CServerInfo::GetDestinationSID(int target) // line 261
{
	return (this->*_GetDestinationSID)(target);

	//TODO
}


hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetLocalServerID(SERVER, "CServerInfo::GetLocalServerID");
int CServerInfo::GetLocalServerID(void) // line 71 (ServerInfo.h)
{
	return (this->*_GetLocalServerID)();

	return m_localServerInfo.SID;
}


hook_method<int (CServerInfo::*)(unsigned long IP, int Type)> CServerInfo::_GetServerID(SERVER, "CServerInfo::GetServerID");
int CServerInfo::GetServerID(unsigned long IP, int Type) // line 271
{
	return (this->*_GetServerID)(IP, Type);

	//TODO
}


hook_method<int (CServerInfo::*)(unsigned long ip, int type)> CServerInfo::_GetServerIDPrivate(SERVER, "CServerInfo::GetServerIDPrivate");
int CServerInfo::GetServerIDPrivate(unsigned long ip, int type) // line 284
{
	return (this->*_GetServerIDPrivate)(ip, type);

	//TODO
}


hook_method<void (CServerInfo::*)(int interServerID, int& len, char* buf)> CServerInfo::_GetZServerIDList(SERVER, "CServerInfo::GetZServerIDList");
void CServerInfo::GetZServerIDList(int interServerID, int& len, char* buf) // line 296
{
	return (this->*_GetZServerIDList)(interServerID, len, buf);

	//TODO
}


hook_method<void (CServerInfo::*)(mystd::set<unsigned long>& zoneset)> CServerInfo::_GetZoneServerIP(SERVER, "CServerInfo::GetZoneServerIP");
void CServerInfo::GetZoneServerIP(mystd::set<unsigned long>& zoneset) // line 309
{
	return (this->*_GetZoneServerIP)(zoneset);

	//TODO
}


hook_method<void (CServerInfo::*)(mystd::set<unsigned long>& zoneset)> CServerInfo::_GetZoneServerIPPrivate(SERVER, "CServerInfo::GetZoneServerIPPrivate");
void CServerInfo::GetZoneServerIPPrivate(mystd::set<unsigned long>& zoneset) // line 320
{
	return (this->*_GetZoneServerIPPrivate)(zoneset);

	//TODO
}


hook_method<unsigned long (CServerInfo::*)(int Type)> CServerInfo::_GetLocalIPAddr(SERVER, "CServerInfo::GetLocalIPAddr");
unsigned long CServerInfo::GetLocalIPAddr(int Type) // line 180
{
	return (this->*_GetLocalIPAddr)(Type);

	return ::GetLocalIPAddr(Type);
}


hook_method<int (CServerInfo::*)(int OneZID, int TwoZID)> CServerInfo::_isSameServerSet(SERVER, "CServerInfo::isSameServerSet");
int CServerInfo::isSameServerSet(int OneZID, int TwoZID) // line 333
{
	return (this->*_isSameServerSet)(OneZID, TwoZID);

	//TODO
}


hook_method<unsigned long (CServerInfo::*)(int SID)> CServerInfo::_GetServerPrivateIPAddr(SERVER, "CServerInfo::GetServerPrivateIPAddr");
unsigned long CServerInfo::GetServerPrivateIPAddr(int SID) // line 350
{
	return (this->*_GetServerPrivateIPAddr)(SID);

	mystd::map<int,_SERVERINFO*>::const_iterator it = m_serverInfoMap.find(SID);
	return ( it != m_serverInfoMap.end() ) ? it->second->PrivateIP : 0;
}


hook_method<int (CServerInfo::*)(int SID)> CServerInfo::_GetServerPrivatePort(SERVER, "CServerInfo::GetServerPrivatePort");
int CServerInfo::GetServerPrivatePort(int SID) // line 362
{
	return (this->*_GetServerPrivatePort)(SID);

	mystd::map<int,_SERVERINFO*>::const_iterator it = m_serverInfoMap.find(SID);
	return ( it != m_serverInfoMap.end() ) ? it->second->PrivatePort : 0;
}


hook_method<void (CServerInfo::*)(void)> CServerInfo::_SetCharacterServerInfo(SERVER, "CServerInfo::SetCharacterServerInfo");
void CServerInfo::SetCharacterServerInfo(void) // line 184
{
	return (this->*_SetCharacterServerInfo)();

	//TODO
}


hook_func<mystd::string (__cdecl *)(const unsigned int in_IP)> _ConvertIPaddr(SERVER, "?ConvertIPaddr@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@K@Z");
mystd::string __cdecl ConvertIPaddr(const unsigned int in_IP) // line 39
{
	return (_ConvertIPaddr)(in_IP);

	//TODO
}
