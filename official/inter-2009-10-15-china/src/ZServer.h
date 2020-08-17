#pragma once
#include "ZSPacketHandler.h"
#include "Client.h"
#include "std/list"
#include "std/map"
#include "std/string"


class CZServer : public CClient
{
	struct vtable_t
	{
		void* (CZServer::* scalar_deleting_destructor)(unsigned int flags);
		int (CZServer::* GetType)(void);
		void (CClient::* AddErrorCount)(const char* filename, int line, unsigned long count, unsigned long time);
		void (CClient::* AddErrorCount2)(unsigned long count, unsigned long time);
		void (CClient::* Init)(void);
	};

	/* this+  0 */ public: //CClient baseclass_0;
	/* this+ 40 */ public: CZSPacketHandler m_packetHandler;
	/* this+ 52 */ private: int m_ZServerID;
	/* this+ 56 */ private: int m_first;
	/* this+ 60 */ private: unsigned long m_firstTick;
	/* this+ 64 */ private: mystd::list<unsigned long> m_SendListGDID;
	/* this+ 76 */ private: int m_bSendInfo;
	/* this+ 80 */ private: mystd::map<mystd::string,int> m_ServiceMap;
	/* this+ 92 */ private: int m_TotalPlayerNum;
	/* this+ 96 */ private: int m_UsedMemoryKBytes;
	/* this+100 */ private: int m_TotalNPCNum;
	/* this+104 */ private: int m_InstantMapNum;
	/* this+108 */ private: int m_InstantMapBlockCnt;
	/* this+112 */ private: unsigned long m_RegisteredMgrFUCnt;

	//public: CZServer::CZServer(void);
	//public: CZServer::~CZServer(void);
	public: void CZServer::Init(const int in_ZSID, CAsyncStream* stream);
	public: void CZServer::SetZServerID(int ServerID);
	//public: int CZServer::OnProcess(void);
	//public: int CZServer::GetType(void);
	public: unsigned long CZServer::GetAccountID(void);
	public: CAsyncStream* CZServer::GetAsyncStream(void);
	public: int CZServer::GetZServerID(void);
	public: void CZServer::AddPlayer(const mystd::string in_mapName);
	public: void CZServer::RemovePlayer(const mystd::string in_mapName);
	public: const int CZServer::GetServiceMapNum(void);
	public: const int CZServer::GetPlayerNum(void);
	public: const int CZServer::GetNPCNum(void);
	public: const int CZServer::GetUsedMemoryKBytes(void);
	public: const int CZServer::GetInstantMapNum(void);
	//public: const unsigned long CZServer::GetRegisteredMgrFUCnt(void);
	//public: const bool CZServer::isInstantMapAllow(void);
	public: const int CZServer::GetInstantMapBlockCnt(void);
	//public: void CZServer::AddInstantMap(const int, const mystd::string, const int);
	//public: void CZServer::RemoveInstantMap(const mystd::string);
	public: void CZServer::OnMgrRegistered(void);
	//public: void CZServer::OutputZSVRStatisticLog(const long);
	//public: void CZServer::OutputMAPStatisticLog(const long);

	typedef mystd::map<mystd::string,int>::const_iterator SERVICEMAPCONTAINER_ITER;

private:
	static hook_method<void (CZServer::*)(const int in_ZSID, CAsyncStream* stream)> CZServer::_Init;
	static hook_method<void (CZServer::*)(int ServerID)> CZServer::_SetZServerID;
	static hook_method<unsigned long (CZServer::*)(void)> CZServer::_GetAccountID;
	static hook_method<CAsyncStream* (CZServer::*)(void)> CZServer::_GetAsyncStream;
	static hook_method<int (CZServer::*)(void)> CZServer::_GetZServerID;
	static hook_method<void (CZServer::*)(const mystd::string in_mapName)> CZServer::_AddPlayer;
	static hook_method<void (CZServer::*)(const mystd::string in_mapName)> CZServer::_RemovePlayer;
	static hook_method<const int (CZServer::*)(void)> CZServer::_GetServiceMapNum;
	static hook_method<const int (CZServer::*)(void)> CZServer::_GetPlayerNum;
	static hook_method<const int (CZServer::*)(void)> CZServer::_GetNPCNum;
	static hook_method<const int (CZServer::*)(void)> CZServer::_GetUsedMemoryKBytes;
	static hook_method<const int (CZServer::*)(void)> CZServer::_GetInstantMapNum;
	static hook_method<const int (CZServer::*)(void)> CZServer::_GetInstantMapBlockCnt;
	static hook_method<void (CZServer::*)(void)> CZServer::_OnMgrRegistered;
};
