#pragma once
#include "ZServer.h"
#include "NetLib/MemoryMgr.h"


class CZServerMgr
{
public:
	CZServerMgr();
	virtual ~CZServerMgr();

public:
	void Init(int count);
	void SendMsgToZServer(const int in_HsvrID, const int in_ZsvrID, const int in_Length, const char* in_pBuffer);
	void SendMsgToZServer(int zServerID, short len, const char* buf);
	void BroadCast(short len, const char* buf);
	void BroadCast(const int in_HsvrID, const int in_Length, const char* in_pBuffer);
	void AddServer(const int in_SID, CZServer* cpZSVR, const unsigned long in_IP);
	BOOL IsConnectedServer(int SID);
	CZServer* AllocServer();
	CAsyncStream* FindServer(int SID);
	BOOL GetVerMessage(); //TODO
	void SetVerMessage(); //TODO
	BOOL GetEpisodeMessage(); //TODO
	void SetEpisodeMessage(); //TODO
	unsigned long GetZoneNumber();
	void OnPaintZoneServerInfo(HDC hdc, int& nY);
	void AddInstantMapZSVR(const int in_ZSID, const int in_MapID, const std::string in_MapName, const int in_MapType);
	void RemoveInstantMapZSVR(const int in_ZSID, const std::string in_MapName);
	void OutputZSvrInfo(const HDC& in_hDC, int& in_X, int& in_Y);
	int SelectInstantMapTargetZSVR(const int in_HsvrID, const int in_TargetZSID);
	void OutputZSVRStatisticLog(const time_t in_Date);
	void OutputMAPStatisticLog(const time_t in_Date);
	void AddPlayer(const int in_ZSID, const std::string in_mapName);

protected:
	void FreeServer(CZServer* server);

protected:
	/* this+ 0 */ //const CZServerMgr::`vftable';
	/* this+ 4 */ CMemoryMgr<CZServer> m_serverMapMemoryPool;
	/* this+44 */ RTL_CRITICAL_SECTION m_serverMap_cs;
	/* this+68 */ BOOL m_bVerMessage;
	/* this+72 */ BOOL m_bEpisodeMessage;
	/* this+76 */ std::map<int,CZServer*> m_serverMap;
};
