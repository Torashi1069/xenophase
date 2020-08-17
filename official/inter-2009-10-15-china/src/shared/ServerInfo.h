#pragma once
#include "shared/ODBC.h"
#include "structs.hpp"
#include "std/list"
#include "std/map"
#include "std/set"
#include "std/string"


#pragma pack(push,1)
class CServerInfo : public CODBC
{
	/* this+0x0  */ //CODBC
	/* this+0x12 */ private: int m_localServerType;
	/* this+0x16 */ private: int m_characterServerCount;
	/* this+0x1A */ private: mystd::map<int,_SERVERINFO *> m_serverInfoMap;
	/* this+0x26 */ private: _SERVERINFO m_localServerInfo;
	/* this+0x92 */ private: mystd::list<int> m_MyServerSet;
	/* this+0x9E */ private: char m_characterServerInfo[1024];

	public: CServerInfo::CServerInfo(void);
	public: CServerInfo::~CServerInfo(void);
	public: int CServerInfo::IsExistColumn(void);
	public: int CServerInfo::Init(const char* ID, const char* Passwd, const char* dbname, int Type);
	public: int CServerInfo::GetSvrInfoFromDB(void);
	public: int CServerInfo::GetServerPort(int SID);
	public: void CServerInfo::SetServerPort(int SID, int port);
	public: unsigned long CServerInfo::GetServerIPAddr(int SID);
	public: int CServerInfo::GetLocalPort(void);
	public: int CServerInfo::GetCharacterServerInfoLength(void);
	public: char* CServerInfo::GetCharacterServerInfo(void);
	public: int CServerInfo::IsValidServer(unsigned long IP, int Type);
	public: int CServerInfo::GetDestinationSID(int target);
	public: int CServerInfo::GetLocalServerID(void);
	public: int CServerInfo::GetServerID(unsigned long IP, int Type);
	public: int CServerInfo::GetServerIDPrivate(unsigned long ip, int type);
	public: void CServerInfo::GetZServerIDList(int interServerID, int& len, char* buf);
	//public: int CServerInfo::GetInterServerID(void);
	public: void CServerInfo::GetZoneServerIP(mystd::set<unsigned long>& zoneset);
	public: void CServerInfo::GetZoneServerIPPrivate(mystd::set<unsigned long>& zoneset);
	public: unsigned long CServerInfo::GetLocalIPAddr(int Type);
	public: int CServerInfo::isSameServerSet(int OneZID, int TwoZID);
	public: unsigned long CServerInfo::GetServerPrivateIPAddr(int SID);
	public: int CServerInfo::GetServerPrivatePort(int SID);
	private: void CServerInfo::SetCharacterServerInfo(void);
	//private: void CharacterServerRegister(class CAcceptor *);

private:
	static hook_method<int (CServerInfo::*)(void)> CServerInfo::_IsExistColumn;
	static hook_method<int (CServerInfo::*)(const char* ID, const char* Passwd, const char* dbname, int Type)> CServerInfo::_Init;
	static hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetSvrInfoFromDB;
	static hook_method<int (CServerInfo::*)(int SID)> CServerInfo::_GetServerPort;
	static hook_method<void (CServerInfo::*)(int SID, int port)> CServerInfo::_SetServerPort;
	static hook_method<unsigned long (CServerInfo::*)(int SID)> CServerInfo::_GetServerIPAddr;
	static hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetLocalPort;
	static hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetCharacterServerInfoLength;
	static hook_method<char* (CServerInfo::*)(void)> CServerInfo::_GetCharacterServerInfo;
	static hook_method<int (CServerInfo::*)(unsigned long IP, int Type)> CServerInfo::_IsValidServer;
	static hook_method<int (CServerInfo::*)(int target)> CServerInfo::_GetDestinationSID;
	static hook_method<int (CServerInfo::*)(void)> CServerInfo::_GetLocalServerID;
	static hook_method<int (CServerInfo::*)(unsigned long IP, int Type)> CServerInfo::_GetServerID;
	static hook_method<int (CServerInfo::*)(unsigned long ip, int type)> CServerInfo::_GetServerIDPrivate;
	static hook_method<void (CServerInfo::*)(int interServerID, int& len, char* buf)> CServerInfo::_GetZServerIDList;
	static hook_method<void (CServerInfo::*)(mystd::set<unsigned long>& zoneset)> CServerInfo::_GetZoneServerIP;
	static hook_method<void (CServerInfo::*)(mystd::set<unsigned long>& zoneset)> CServerInfo::_GetZoneServerIPPrivate;
	static hook_method<unsigned long (CServerInfo::*)(int Type)> CServerInfo::_GetLocalIPAddr;
	static hook_method<int (CServerInfo::*)(int OneZID, int TwoZID)> CServerInfo::_isSameServerSet;
	static hook_method<unsigned long (CServerInfo::*)(int SID)> CServerInfo::_GetServerPrivateIPAddr;
	static hook_method<int (CServerInfo::*)(int SID)> CServerInfo::_GetServerPrivatePort;
	static hook_method<void (CServerInfo::*)(void)> CServerInfo::_SetCharacterServerInfo;
};
#pragma pack(pop)


mystd::string __cdecl ConvertIPaddr(const unsigned int in_IP);
