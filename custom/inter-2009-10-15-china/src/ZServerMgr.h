#pragma once
#include "ZServer.h"
#include "NetLib/MemoryMgr.h"
#include "std/map"


class CZServerMgr
{
	/* this+0x0  */ public: //const CZServerMgr::`vftable';
	/* this+0x4  */ private: CMemoryMgr<CZServer> m_serverMapMemoryPool;
	/* this+0x34 */ private: RTL_CRITICAL_SECTION m_serverMap_cs;
	/* this+0x4C */ private: int m_bVerMessage;
	/* this+0x50 */ private: int m_bEpisodeMessage;
	/* this+0x54 */ private: mystd::map<int,CZServer*> m_serverMap;

	public: CZServerMgr::CZServerMgr(void);
	public: virtual CZServerMgr::~CZServerMgr(void);
	public: void CZServerMgr::Init(int count);
	public: void CZServerMgr::ProcessAllCharacter(void);
	public: void CZServerMgr::SendMsgToZServer(int zServerID, short len, const char* buf);
	public: void CZServerMgr::BroadCast(short len, const char* buf);
	public: void CZServerMgr::AddServer(int SID, CZServer* zServer);
	public: void CZServerMgr::DeleteServer(int SID);
	//public: int CZServerMgr::IsConnectedServer(int);
	public: CZServer* CZServerMgr::AllocServer(void);
	public: CAsyncStream* CZServerMgr::FindServer(int SID);
	//public: int GetVerMessage();
	//public: void SetVerMessage();
	//public: int GetEpisodeMessage();
	//public: void SetEpisodeMessage();
	//public: unsigned long CZServerMgr::GetZoneNumber();
	public: void CZServerMgr::OnPaintZoneServerInfo(HDC hdc, int& nY);
	//public: void CZServerMgr::AddInstantMapZSVR(const int, const int, const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >, const int);
	//public: void CZServerMgr::RemoveInstantMapZSVR(const int, const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >);
	public: void CZServerMgr::OutputZSvrInfo(const HDC& in_hDC, int& in_X, int& in_Y);
	//public: int CZServerMgr::SelectInstantMapTargetZSVR(const int);
	public: void CZServerMgr::OutputZSVRStatisticLog(const time_t in_Date);
	public: void CZServerMgr::OutputMAPStatisticLog(const time_t in_Date);
	//public: void CZServerMgr::AddPlayer(const int, const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >);
	private: void CZServerMgr::FreeServer(CZServer* server);

private:
	static hook_method<void (CZServerMgr::*)(int count)> CZServerMgr::_Init;
	static hook_method<void (CZServerMgr::*)(void)> CZServerMgr::_ProcessAllCharacter;
	static hook_method<void (CZServerMgr::*)(int zServerID, short len, const char* buf)> CZServerMgr::_SendMsgToZServer;
	static hook_method<void (CZServerMgr::*)(short len, const char* buf)> CZServerMgr::_BroadCast;
	static hook_method<void (CZServerMgr::*)(int SID, CZServer* zServer)> CZServerMgr::_AddServer;
	static hook_method<void (CZServerMgr::*)(int SID)> CZServerMgr::_DeleteServer;
	static hook_method<CZServer* (CZServerMgr::*)(void)> CZServerMgr::_AllocServer;
	static hook_method<CAsyncStream* (CZServerMgr::*)(int SID)> CZServerMgr::_FindServer;
	static hook_method<void (CZServerMgr::*)(HDC hdc, int& nY)> CZServerMgr::_OnPaintZoneServerInfo;
	static hook_method<void (CZServerMgr::*)(const HDC& in_hDC, int& in_X, int& in_Y)> CZServerMgr::_OutputZSvrInfo;
	static hook_method<void (CZServerMgr::*)(const time_t in_Date)> CZServerMgr::_OutputZSVRStatisticLog;
	static hook_method<void (CZServerMgr::*)(const time_t in_Date)> CZServerMgr::_OutputMAPStatisticLog;
	static hook_method<void (CZServerMgr::*)(CZServer* server)> CZServerMgr::_FreeServer;
};
