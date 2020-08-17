#include "NetLib/Acceptor.h" // GetLocalIPAddr()
#include "NetLib/Addr.h"
#include "shared/ServerInfo.h"
#include "shared/NSystem/NIPAddr.h"


struct SERVER_ADDR
{
	/* this+ 0 */ unsigned long ip;
	/* this+ 4 */ short port;
	/* this+ 6 */ unsigned char name[20];
	/* this+26 */ unsigned short usercount;
	/* this+28 */ unsigned short state;
	/* this+30 */ unsigned short property;
};


CServerInfo::CServerInfo()
{
	m_localServerInfo.SID = -1;
	m_localServerInfo.ip = INADDR_ANY;
	m_characterServerCount = 0;
}


CServerInfo::~CServerInfo()
{
	while( 1 )
	{
		std::map<int,_SERVERINFO*>::iterator iterator = m_serverInfoMap.begin();
		if( iterator == m_serverInfoMap.end() )
			break; // done.

		delete iterator->second;
		m_serverInfoMap.erase(iterator);
	}
}


BOOL CServerInfo::GetSvrInfoFromDB(const int in_hExpectSvrType, const int in_hExpectSID)
{
	m_localServerInfo.ip = this->CServerInfo::GetLocalIPAddr(PUBLIC_OR_PRIVATE_IP_ADDRESS);
	m_localServerInfo.IPstr = NIPAddapter(NIPAddr(m_localServerInfo.ip));

	BOOL ExistColumn = this->CServerInfo::IsExistColumn();

	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return FALSE;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return FALSE;

	int SID;
	int Type;
	char IP[16];
	int Port;
	int DestinationOneSID;
	int DestinationTwoSID;
	char name[24];
	char P_IP[16] = {};
	int P_Port = 0;

	SQLINTEGER cbAID = 0;
	SQLINTEGER cbChar = SQL_NTS;
	SQLINTEGER cbOneSID;
	SQLINTEGER cbTwoSID;

	if( ExistColumn )
		m_retcode = SQLPrepareA(m_hstmt, (SQLCHAR*)"select  SID, Type, IP, Port, DestinationOneSID, DestinationTwoSID, SvrName, PrivateIP, PrivatePort from ServerInfo", SQL_NTS);
	else
		m_retcode = SQLPrepareA(m_hstmt, (SQLCHAR*)"select  SID, Type, IP, Port, DestinationOneSID, DestinationTwoSID, SvrName from ServerInfo", SQL_NTS);

	m_retcode = SQLExecute(m_hstmt);
	m_retcode = SQLBindCol(m_hstmt, 1, SQL_C_SLONG, &SID, 0, &cbAID);
	m_retcode = SQLBindCol(m_hstmt, 2, SQL_C_SLONG, &Type, 0, &cbAID);
	m_retcode = SQLBindCol(m_hstmt, 3, SQL_C_CHAR, &IP, sizeof(IP), &cbChar);
	m_retcode = SQLBindCol(m_hstmt, 4, SQL_C_SLONG, &Port, 0, &cbAID);
	m_retcode = SQLBindCol(m_hstmt, 5, SQL_C_SLONG, &DestinationOneSID, 0, &cbOneSID);
	m_retcode = SQLBindCol(m_hstmt, 6, SQL_C_SLONG, &DestinationTwoSID, 0, &cbTwoSID);
	m_retcode = SQLBindCol(m_hstmt, 7, SQL_C_CHAR, name, 20, &cbChar);
	if( ExistColumn )
	{
	m_retcode = SQLBindCol(m_hstmt, 8, SQL_C_CHAR, P_IP, sizeof(P_IP), &cbChar);
	m_retcode = SQLBindCol(m_hstmt, 9, SQL_C_SLONG, &P_Port, 0, &cbAID);
	}

	while( 1 )
	{
		m_retcode = SQLFetch(m_hstmt);
		if( m_retcode == SQL_NO_DATA )
			break;

		if( m_retcode == -4 || m_retcode == SQL_ERROR )
			break;

		if( cbOneSID == SQL_NULL_DATA )
			DestinationOneSID = 0;
		if( cbTwoSID == SQL_NULL_DATA )
			DestinationTwoSID = 0;

		Addr addr;
		addr.SetIp(IP);

		_SERVERINFO* info = new _SERVERINFO;
		info->SID = SID;
		info->Type = Type;
		info->ip = addr.ip;
		info->IPstr = NIPAddapter(NIPAddr(addr.ip));
		info->Port = Port;
		info->DestinationOneSID = DestinationOneSID;
		info->DestinationTwoSID = DestinationTwoSID;
		memcpy_s(info->Name, sizeof(info->Name), name, 20);
		if( ExistColumn )
		{
			info->PrivateIP = inet_addr(P_IP);
			info->PrivateIPstr = NIPAddapter(NIPAddr(info->PrivateIP));
			info->PrivatePort = P_Port;

			memset(P_IP, '\0', sizeof(P_IP));
			P_Port = 0;
		}

		m_serverInfoMap[SID] = info;

		unsigned char Ip[4];
		memcpy_s(&Ip, sizeof(Ip), &addr.ip, sizeof(addr.ip));

		char TempIP[256];
		sprintf_s(TempIP, countof(TempIP), "%d.%d.%d.%d", Ip[0], Ip[1], Ip[2], Ip[3]);

		unsigned char Ip2[4];
		memcpy_s(Ip2, sizeof(Ip2), &m_localServerInfo.ip, sizeof(m_localServerInfo.ip));

		char TempIP2[256];
		sprintf_s(TempIP2, countof(TempIP2), "%d.%d.%d.%d", Ip2[0], Ip2[1], Ip2[2], Ip2[3]);

		if( in_hExpectSID == -1 || in_hExpectSID == SID )
		{
			if( Type == in_hExpectSvrType )
			{
				if( m_localServerInfo.ip == info->ip || m_localServerInfo.ip == info->PrivateIP )
				{
					m_localServerInfo.SID = SID;
					m_localServerInfo.Port = Port;
					m_localServerInfo.DestinationOneSID = DestinationOneSID;
					m_localServerInfo.DestinationTwoSID = DestinationTwoSID;
					m_localServerInfo.Type = INTERPROCESSTYPE;
					memset(m_localServerInfo.Name, '\0', sizeof(m_localServerInfo.Name));
					memcpy_s(m_localServerInfo.Name, sizeof(m_localServerInfo.Name), name, 20-1);
				}
			}
		}
	}

	this->CServerInfo::SetCharacterServerInfo();

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return ExistColumn;
}


unsigned long CServerInfo::GetLocalIPAddr(int Type)
{
	return ::GetLocalIPAddr(Type);
}


void CServerInfo::SetCharacterServerInfo()
{
	for( std::map<int,_SERVERINFO*>::iterator ServerInfoiterator = m_serverInfoMap.begin(); ServerInfoiterator != m_serverInfoMap.end(); ++ServerInfoiterator )
	{
		_SERVERINFO* info = ServerInfoiterator->second;

		if( info->Type == CHARACTERSERVERTYPE || info->Type == ENGLISHCHARACTERSERVERTYPE )
		{
			SERVER_ADDR serverAddress;
			serverAddress.ip = info->ip;
			serverAddress.port = info->Port;
			memcpy_s(serverAddress.name, sizeof(serverAddress.name), info->Name, sizeof(info->Name));

			memcpy_s(m_characterServerInfo + this->CServerInfo::GetCharacterServerInfoLength(), sizeof(m_characterServerInfo) - this->CServerInfo::GetCharacterServerInfoLength(), &serverAddress, sizeof(serverAddress));
			++m_characterServerCount;
		}
	}
}


int CServerInfo::GetCharacterServerInfoLength() const
{
	return m_characterServerCount * sizeof(SERVER_ADDR);
}


unsigned long CServerInfo::GetServerIPAddr(int SID)
{
	std::map<int,_SERVERINFO*>::iterator iterator = m_serverInfoMap.find(SID);
	if( iterator == m_serverInfoMap.end() )
		return INADDR_ANY;

	return iterator->second->ip;
}


int CServerInfo::GetServerPort(int SID)
{
	std::map<int,_SERVERINFO*>::iterator iterator = m_serverInfoMap.find(SID);
	if( iterator == m_serverInfoMap.end() )
		return INADDR_ANY;

	return iterator->second->Port;
}


void CServerInfo::SetServerPort(int SID, int port)
{
	std::map<int,_SERVERINFO*>::iterator iterator = m_serverInfoMap.find(SID);
	if( iterator == m_serverInfoMap.end() )
		return;

	iterator->second->Port = port;
}


int CServerInfo::GetLocalPort()
{
	return m_localServerInfo.Port;
}


int CServerInfo::GetLocalServerID()
{
	return m_localServerInfo.SID;
}


int CServerInfo::GetDestinationSID(const int in_SID, const int in_Target) const
{
	std::map<int,_SERVERINFO*>::const_iterator iter = m_serverInfoMap.find(in_SID);
	if( iter == m_serverInfoMap.end() )
		return 0;

	if( in_Target == TARGET_ONE_SID ) 
		return iter->second->DestinationOneSID;
	else if( in_Target == TARGET_TWO_SID )
		return iter->second->DestinationTwoSID;
	else
		return iter->second->SID;
}


int CServerInfo::GetDestinationSID(int target)
{
	if( target == TARGET_ONE_SID ) 
		return m_localServerInfo.DestinationOneSID;
	else if( target == TARGET_TWO_SID )
		return m_localServerInfo.DestinationTwoSID;
	else
		return m_localServerInfo.SID;
}


void CServerInfo::GetZServerIDList(int interServerID, int& len, char* buf, const int in_nMaxBufSize)
{
	len = 0;

	for( std::map<int,_SERVERINFO*>::iterator iterator = m_serverInfoMap.begin(); iterator != m_serverInfoMap.end(); ++iterator )
	{
		_SERVERINFO* info = iterator->second;

		if( info->Type == ZONEPROCESSSERVERTYPE && info->DestinationTwoSID == interServerID )
		{
			memcpy_s(buf + len, in_nMaxBufSize - len, &info->SID, sizeof(info->SID));
			len += sizeof(info->SID);
		}
	}
}


void CServerInfo::GetZoneServerIP(std::set<unsigned long>& zoneset)
{
	for( std::map<int,_SERVERINFO*>::iterator iterator = m_serverInfoMap.begin(); iterator != m_serverInfoMap.end(); ++iterator )
	{
		_SERVERINFO* info = iterator->second;

		if( info->Type == ZONEPROCESSSERVERTYPE )
		{
			zoneset.insert(info->ip);
		}
	}
}


void CServerInfo::GetZoneServerIPPrivate(std::set<unsigned long>& zoneset)
{
	for( std::map<int,_SERVERINFO*>::iterator iterator = m_serverInfoMap.begin(); iterator != m_serverInfoMap.end(); ++iterator )
	{
		_SERVERINFO* info = iterator->second;

		if( info->Type == ZONEPROCESSSERVERTYPE )
		{
			zoneset.insert(info->PrivateIP);
			zoneset.insert(info->ip);
		}
	}
}


bool CServerInfo::isSameServerSet(int in_SourceSID, int in_TargetSID)
{
	std::map<int,_SERVERINFO*>::const_iterator sourceIter = m_serverInfoMap.find(in_SourceSID);
	if( sourceIter == m_serverInfoMap.end() )
		return false;

	std::map<int,_SERVERINFO*>::const_iterator targetIter = m_serverInfoMap.find(in_TargetSID);
	if( targetIter == m_serverInfoMap.end() )
		return false;

	return ( sourceIter->second->DestinationOneSID == targetIter->second->DestinationOneSID );
}


unsigned long CServerInfo::GetServerPrivateIPAddr(int SID)
{
	std::map<int,_SERVERINFO*>::iterator iterator = m_serverInfoMap.find(SID);
	if( iterator == m_serverInfoMap.end() )
		return INADDR_ANY;

	return iterator->second->PrivateIP;
}


int CServerInfo::GetServerPrivatePort(int SID)
{
	std::map<int,_SERVERINFO*>::iterator iterator = m_serverInfoMap.find(SID);
	if( iterator == m_serverInfoMap.end() )
		return INADDR_ANY;

	return iterator->second->PrivatePort;
}


BOOL CServerInfo::IsExistColumn()
{
	CDBStatement st;
	if( !st.CDBStatement::Init(m_hdbc) )
		return FALSE;

	m_retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
		return FALSE;

	m_retcode = SQLPrepareA(m_hstmt, (SQLCHAR*)"EXEC sp_columns @table_name = ServerInfo, @column_name  = PrivateIP", SQL_NTS);
	m_retcode = SQLExecute(m_hstmt);
	if( !SQL_SUCCEEDED(m_retcode) )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	m_retcode = SQLFetch(m_hstmt);
	if( m_retcode == SQL_NO_DATA )
	{
		SQLCloseCursor(m_hstmt);
		if( m_hstmt != SQL_NULL_HSTMT )
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

		return FALSE;
	}

	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);

	return TRUE;
}


BOOL CServerInfo::Init(const char* dsnFILE, const char* Passwd, int Type, const int in_hExpectSID)
{
	this->CODBC::Init(dsnFILE, Passwd);
	BOOL result = this->CServerInfo::GetSvrInfoFromDB(Type, in_hExpectSID);
	this->CODBC::Reset();

	return result;
}
