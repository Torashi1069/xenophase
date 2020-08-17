#pragma once
#include "ZSPacketHandler.h"
#include "NetLib/AsyncStream.h"
#include "shared/Client.h"
#include "shared/N3System/N3Scheduler.h"


class CZServer : public CClient
{
public:
	CZServer();
	virtual ~CZServer();

public:
	void Cleanup();
	unsigned int GetLastPacketRecvTM();
	unsigned int GetLastPacketSendTM();
	void Init(const int in_ZSID, CAsyncStream* stream);
	void SetZServerID(const int in_ServerID, const unsigned long in_IP);
	virtual void AddErrorCnt(const char* in_pSourceFileName, const int in_SourceLineNum, const unsigned long in_Cnt, const unsigned long in_TM);
	virtual void Send(int len, const char* buf);

public:
	/* this+ 0 */ //CClient baseclass_0;
	/* this+40 */ CZSPacketHandler m_packetHandler;

public:
	int OnProcess();
	virtual int GetType();
	unsigned long GetAccountID();
	CAsyncStream* GetAsyncStream();
	int GetZServerID();
	unsigned long GetIP();
	int GetHsvrID();
	void SendIZResultEntryQueueApply(const unsigned long in_GID, const unsigned char in_Result, const std::string in_EntryQueueName);

private:
	/* this+ 56 */ int m_ZServerID;
	/* this+ 60 */ unsigned long m_IP;
	/* this+ 64 */ int m_first;
	/* this+ 68 */ unsigned long m_firstTick;
	/* this+ 72 */ std::list<unsigned long> m_SendListGDID;
	/* this+100 */ BOOL m_bSendInfo;
	/* this+104 */ int m_HsvrID;
	/* this+108 */ N3Scheduler<CZServer> m_Scheduler;
	/* this+144 */ unsigned int m_LastPacketSendTM;
	typedef std::map<std::string,int> SERVICEMAPCONTAINER;
	typedef SERVICEMAPCONTAINER::iterator SERVICEMAPCONTAINER_ITER;
	/* this+148 */ SERVICEMAPCONTAINER m_ServiceMap;
	/* this+180 */ int m_TotalPlayerNum;
	/* this+184 */ int m_UsedMemoryKBytes;
	/* this+188 */ int m_TotalNPCNum;
	/* this+192 */ int m_InstantMapNum;
	/* this+196 */ int m_InstantMapBlockCnt;
	/* this+200 */ unsigned long m_RegisteredMgrFUCnt;

public:
	void AddPlayer(const std::string in_mapName);
	void RemovePlayer(const std::string in_mapName);
	const int GetServiceMapNum() const;
	const int GetPlayerNum() const;
	const int GetNPCNum() const;
	const int GetUsedMemoryKBytes() const;
	const int GetInstantMapNum() const;
	const unsigned long GetRegisteredMgrFUCnt() const;
	const bool isInstantMapAllow() const;
	const int GetInstantMapBlockCnt() const;
	void AddInstantMap(const int in_MapID, const std::string in_MapName, const int in_MapType);
	void RemoveInstantMap(const std::string in_MapName);
	void OnMgrRegistered();
	void OutputZSVRStatisticLog(const time_t in_Date);
	void OutputMAPStatisticLog(const time_t in_Date);

	friend class CZSPacketHandler; // m_UsedMemoryKBytes, m_TotalNPCNum @ OnZI_PING(), OnZI_STATEINFO()
	friend class CZSPacketHandler; // m_InstantMapBlockCnt @ OnZI_INSTANTMAP_ALLOW()
};
