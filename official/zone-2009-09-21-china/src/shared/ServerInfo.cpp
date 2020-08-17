#include "ServerInfo.h"


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

	//TODO
}


hook_method<int (CServerInfo::*)(const char* ID, const char* Passwd, const char* dbname, int Type)> CServerInfo::_Init(SERVER, "CServerInfo::Init");
int CServerInfo::Init(const char* ID, const char* Passwd, const char* dbname, int Type) // line 30
{
	return (this->*_Init)(ID, Passwd, dbname, Type);

	//TODO
}


hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetSvrInfoFromDB(SERVER, "CServerInfo::GetSvrInfoFromDB");
int CServerInfo::GetSvrInfoFromDB(void) // line 55
{
	return (this->*_GetSvrInfoFromDB)();

	//TODO
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


//hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetLocalPort(SERVER, "CServerInfo::GetLocalPort");
int CServerInfo::GetLocalPort(void) // line ???
{
//	return (this->*_GetLocalPort)();

	return m_localServerInfo.Port;
}


hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetCharacterServerInfoLength(SERVER, "CServerInfo::GetCharacterServerInfoLength");
int CServerInfo::GetCharacterServerInfoLength(void) // line 203
{
	return (this->*_GetCharacterServerInfoLength)();

	//TODO
}


//hook_method<char* (CServerInfo::*)(void)> CServerInfo::_GetCharacterServerInfo(SERVER, "CServerInfo::GetCharacterServerInfo");
char* CServerInfo::GetCharacterServerInfo(void) // line ???
{
//	return (this->*_GetCharacterServerInfo)();

	return m_characterServerInfo;
}


/* hook_method<int (CServerInfo::*)(unsigned long IP, int Type)> CServerInfo::_IsValidServer(SERVER, "CServerInfo::IsValidServer");
int CServerInfo::IsValidServer(unsigned long IP, int Type) // line ???
{
	return (this->*_IsValidServer)(IP, Type);

	//TODO
} */


hook_method<int (CServerInfo::*)(int target)> CServerInfo::_GetDestinationSID(SERVER, "CServerInfo::GetDestinationSID");
int CServerInfo::GetDestinationSID(int target) // line 261
{
	return (this->*_GetDestinationSID)(target);

	//TODO
}


//hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetLocalServerID(SERVER, "CServerInfo::GetLocalServerID");
int CServerInfo::GetLocalServerID(void) // line ???
{
//	return (this->*_GetLocalServerID)();

	return m_localServerInfo.SID;
}


/* hook_method<int (CServerInfo::*)(unsigned long ip, int type)> CServerInfo::_GetServerID(SERVER, "CServerInfo::GetServerID");
int CServerInfo::GetServerID(unsigned long ip, int type) // line ???
{
	return (this->*_GetServerID)(ip, type);

	//TODO
} */


/* hook_method<int (CServerInfo::*)(unsigned long ip, int type)> CServerInfo::_GetServerIDPrivate(SERVER, "CServerInfo::GetServerIDPrivate");
int CServerInfo::GetServerIDPrivate(unsigned long ip, int type) // line ???
{
	return (this->*_GetServerIDPrivate)(ip, type);

	//TODO
} */


/* hook_method<void (CServerInfo::*)(int interServerID, int& len, char* buf)> CServerInfo::_GetZServerIDList(SERVER, "CServerInfo::GetZServerIDList");
void CServerInfo::GetZServerIDList(int interServerID, int& len, char* buf) // line ???
{
	return (this->*_GetZServerIDList)(interServerID, len, buf);

	//TODO
} */


/* hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetInterServerID(SERVER, "CServerInfo::GetInterServerID");
int CServerInfo::GetInterServerID(void) // line ???
{
	return (this->*_GetInterServerID)();

	//TODO
} */


/* hook_method<void (CServerInfo::*)(mystd::set<unsigned long>& zoneset)> CServerInfo::_GetZoneServerIP(SERVER, "CServerInfo::GetZoneServerIP");
void CServerInfo::GetZoneServerIP(mystd::set<unsigned long>& zoneset) // line ???
{
	return (this->*_GetZoneServerIP)(zoneset);

	//TODO
} */


/* hook_method<void (CServerInfo::*)(mystd::set<unsigned long>& zoneset)> CServerInfo::_GetZoneServerIPPrivate(SERVER, "CServerInfo::GetZoneServerIPPrivate");
void CServerInfo::GetZoneServerIPPrivate(mystd::set<unsigned long>& zoneset) // line ???
{
	return (this->*_GetZoneServerIPPrivate)(zoneset);

	//TODO
} */


hook_method<unsigned long (CServerInfo::*)(int SID)> CServerInfo::_GetLocalIPAddr(SERVER, "CServerInfo::GetLocalIPAddr");
unsigned long CServerInfo::GetLocalIPAddr(int SID) // line 180
{
	return (this->*_GetLocalIPAddr)(SID);

	//TODO
}


/* hook_method<int (CServerInfo::*)(int OneZID, int TwoZID)> CServerInfo::_isSameServerSet(SERVER, "CServerInfo::isSameServerSet");
int CServerInfo::isSameServerSet(int OneZID, int TwoZID) // line ???
{
	return (this->*_isSameServerSet)(OneZID, TwoZID);

	//TODO
} */


hook_method<unsigned long (CServerInfo::*)(int SID)> CServerInfo::_GetServerPrivateIPAddr(SERVER, "CServerInfo::GetServerPrivateIPAddr");
unsigned long CServerInfo::GetServerPrivateIPAddr(int SID) // line 350
{
	return (this->*_GetServerPrivateIPAddr)(SID);

	//TODO
}


hook_method<int (CServerInfo::*)(int SID)> CServerInfo::_GetServerPrivatePort(SERVER, "CServerInfo::GetServerPrivatePort");
int CServerInfo::GetServerPrivatePort(int SID) // line 362
{
	return (this->*_GetServerPrivatePort)(SID);

	//TODO
}


hook_method<void (CServerInfo::*)(void)> CServerInfo::_SetCharacterServerInfo(SERVER, "CServerInfo::SetCharacterServerInfo");
void CServerInfo::SetCharacterServerInfo(void) // line 184
{
	return (this->*_SetCharacterServerInfo)();

	//TODO
}
