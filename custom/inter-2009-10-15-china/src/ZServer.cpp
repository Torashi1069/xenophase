#include "ZServer.h"
#include "globals.hpp"


hook_method<void (CZServer::*)(const int in_ZSID, CAsyncStream* stream)> CZServer::_Init(SERVER, "CZServer::Init");
void CZServer::Init(const int in_ZSID, CAsyncStream* stream) // line 43
{
	return (this->*_Init)(in_ZSID, stream);

	//TODO
}


hook_method<void (CZServer::*)(int ServerID)> CZServer::_SetZServerID(SERVER, "CZServer::SetZServerID");
void CZServer::SetZServerID(int ServerID) // line 151
{
	return (this->*_SetZServerID)(ServerID);

	m_ZServerID = ServerID;
}


hook_method<unsigned long (CZServer::*)(void)> CZServer::_GetAccountID(SERVER, "CZServer::GetAccountID");
unsigned long CZServer::GetAccountID(void) // line 161
{
	return (this->*_GetAccountID)();

	return -1;
}


hook_method<CAsyncStream* (CZServer::*)(void)> CZServer::_GetAsyncStream(SERVER, "CZServer::GetAsyncStream");
CAsyncStream* CZServer::GetAsyncStream(void) // line 34 (ZServer.h)
{
	return (this->*_GetAsyncStream)();

	return m_asyncStream;
}


hook_method<int (CZServer::*)(void)> CZServer::_GetZServerID(SERVER, "CZServer::GetZServerID");
int CZServer::GetZServerID(void) // line 156
{
	return (this->*_GetZServerID)();

	return m_ZServerID;
}


hook_method<void (CZServer::*)(const mystd::string in_mapName)> CZServer::_AddPlayer(SERVER, "CZServer::AddPlayer");
void CZServer::AddPlayer(const mystd::string in_mapName) // line 83-88
{
	return (this->*_AddPlayer)(in_mapName);

	mystd::map<mystd::string,int>::iterator iter = m_ServiceMap.find(in_mapName);
	if( iter == m_ServiceMap.end() )
		return; // map not found

	++iter->second;
	++m_TotalPlayerNum;
}


hook_method<void (CZServer::*)(const mystd::string in_mapName)> CZServer::_RemovePlayer(SERVER, "CZServer::RemovePlayer");
void CZServer::RemovePlayer(const mystd::string in_mapName) // line 94-99
{
	return (this->*_RemovePlayer)(in_mapName);

	// TODO
}


hook_method<const int (CZServer::*)(void)> CZServer::_GetServiceMapNum(SERVER, "CZServer::GetServiceMapNum");
const int CZServer::GetServiceMapNum(void) // line 75 (ZServer.h)
{
	return (this->*_GetServiceMapNum)();

	return m_ServiceMap.size();
}


hook_method<const int (CZServer::*)(void)> CZServer::_GetPlayerNum(SERVER, "CZServer::GetPlayerNum");
const int CZServer::GetPlayerNum(void) // line 76 (ZServer.h)
{
	return (this->*_GetPlayerNum)();

	return m_TotalPlayerNum;
}


hook_method<const int (CZServer::*)(void)> CZServer::_GetNPCNum(SERVER, "CZServer::GetNPCNum");
const int CZServer::GetNPCNum(void) // line 77 (ZServer.h)
{
	return (this->*_GetNPCNum)();

	return m_TotalNPCNum;
}


hook_method<const int (CZServer::*)(void)> CZServer::_GetUsedMemoryKBytes(SERVER, "CZServer::GetUsedMemoryKBytes");
const int CZServer::GetUsedMemoryKBytes(void) // line 78 (ZServer.h)
{
	return (this->*_GetUsedMemoryKBytes)();

	return m_UsedMemoryKBytes;
}


hook_method<const int (CZServer::*)(void)> CZServer::_GetInstantMapNum(SERVER, "CZServer::GetInstantMapNum");
const int CZServer::GetInstantMapNum(void) // line 79 (ZServer.h)
{
	return (this->*_GetInstantMapNum)();

	return m_InstantMapNum;
}


hook_method<const int (CZServer::*)(void)> CZServer::_GetInstantMapBlockCnt(SERVER, "CZServer::GetInstantMapBlockCnt");
const int CZServer::GetInstantMapBlockCnt(void) // line 82 (ZServer.h)
{
	return (this->*_GetInstantMapBlockCnt)();

	return m_InstantMapBlockCnt;
}


hook_method<void (CZServer::*)(void)> CZServer::_OnMgrRegistered(SERVER, "CZServer::OnMgrRegistered");
void CZServer::OnMgrRegistered(void) // line 167
{
	return (this->*_OnMgrRegistered)();

	m_RegisteredMgrFUCnt = ++g_FunctionUniqueCnt;
}
