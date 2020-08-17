#pragma once
#include "shared/ODBC.h"
class CAcceptor;
#pragma pack(push,1)


enum enumSERVERTYPE
{
	ACCOUNTSERVERTYPE          = 1,
	CHARACTERSERVERTYPE        = 2,
	ZONEPROCESSSERVERTYPE      = 3,
	INTERPROCESSTYPE           = 4,
	NPCSERVERTYPE              = 5,
	ENGLISHCHARACTERSERVERTYPE = 6,
	MONITOR_SERVER             = 7,
};


/// @see CServerInfo::GetDestinationSID()
enum enumTARGETSIDTYPE
{
	LOCAL_SID      = 0,
	TARGET_ONE_SID = 1,
	TARGET_TWO_SID = 2,
};


struct _SERVERINFO
{
	/* this+  0 */ int SID;
	/* this+  4 */ int Type; // enumSERVERTYPE
	/* this+  8 */ unsigned long ip;
	/* this+ 12 */ std::string IPstr;
	/* this+ 40 */ int Port;
	/* this+ 44 */ int DestinationOneSID;
	/* this+ 48 */ int DestinationTwoSID;
	/* this+ 52 */ char Name[20];
	/* this+ 72 */ unsigned long PrivateIP;
	/* this+ 76 */ std::string PrivateIPstr;
	/* this+104 */ int PrivatePort;
	/* this+108 */ bool bReady;
	/* this+109 */ bool bOverpopulation;

	_SERVERINFO() { memset(this, 0, sizeof(*this)); }
};


class CServerInfo : public CODBC
{
public:
	BOOL IsExistColumn();
	BOOL Init(const char* dsnFILE, const char* Passwd, int Type, const int in_hExpectSID);
	BOOL GetSvrInfoFromDB(const int in_hExpectSvrType, const int in_hExpectSID);
	int GetServerPort(int SID);
	void SetServerPort(int SID, int port);
	unsigned long GetServerIPAddr(int SID);
	int GetLocalPort();
	int GetCharacterServerInfoLength() const;
	char* GetCharacterServerInfo(); //TODO
	int IsValidServer(unsigned long, int); //TODO
	const char* GetSVRName(const int); //TODO
	int GetDestinationSID(const int in_SID, const int in_Target) const;
	int GetDestinationSID(int target);
	int GetLocalServerID();
	int GetServerID(unsigned long, int); //TODO
	int GetServerIDPrivate(unsigned long, int); //TODO
	void GetZServerIDList(int interServerID, int& len, char* buf, const int in_nMaxBufSize);
	int GetInterServerID(); //TODO
	void GetZoneServerIP(std::set<unsigned long>& zoneset);
	void GetZoneServerIPPrivate(std::set<unsigned long>& zoneset);
	unsigned long GetLocalIPAddr(int Type);
	bool isSameServerSet(int in_SourceSID, int in_TargetSID);
	unsigned long GetServerPrivateIPAddr(int SID);
	int GetServerPrivatePort(int SID);
	void Set(const int, const bool, const bool); //TODO
	bool IsActive(const int); //TODO
	const unsigned long GetLocalIP(); //TODO
	void SetLocalServerIpAddr(const unsigned long); //TODO

public:
	CServerInfo();
	virtual ~CServerInfo();

private:
	/* this+  0 */ //CODBC baseclass_0;
	/* this+ 18 */ int m_localServerType;
	/* this+ 22 */ int m_characterServerCount;
	/* this+ 26 */ std::map<int,_SERVERINFO*> m_serverInfoMap;
	/* this+ 58 */ _SERVERINFO m_localServerInfo;
	/* this+168 */ std::list<int> m_MyServerSet;
	/* this+196 */ char m_characterServerInfo[1024]; // SERVER_ADDR[]

private:
	void SetCharacterServerInfo();
	void CharacterServerRegister(CAcceptor*); //TODO
};


#pragma pack(pop)
