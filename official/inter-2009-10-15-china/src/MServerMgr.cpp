#include "ISAcceptHandler.h"
#include "MGacceptHandler.h"
#include "MServerMgr.h"
#include "globals.hpp"


CMClientMgr::CMClientMgr(void) // line 8
{
}


CMClientMgr::~CMClientMgr(void) // line 12
{
	DeleteCriticalSection(&m_mserverMgr_cs);
}


hook_method<void (CMClientMgr::*)(int count)> CMClientMgr::_Init(SERVER, "CMClientMgr::Init");
void CMClientMgr::Init(int count) // line 49
{
	return (this->*_Init)(count);

	//TODO
}


hook_method<void (CMClientMgr::*)(void)> CMClientMgr::_ProcessAllCharacter(SERVER, "CMClientMgr::ProcessAllCharacter");
void CMClientMgr::ProcessAllCharacter(void) // line 83
{
	return (this->*_ProcessAllCharacter)();

	EnterCriticalSection(&m_mserverMgr_cs);

	for( mystd::map<int,CMClient*>::iterator it = m_mServerMap.begin(); it != m_mServerMap.end(); ++it )
	{
		CMClient* client = it->second;

		if( client->CMClient::OnProcess() == -1 && !client->CClient::IsErrorServer() )
		{
			++it;
		}
		else
		{
			Trace("Monitor Server Disconnected\n");
			client->CClient::Close();

			if( g_isExtendDB )
				_g_isMGAcceptHandler.CMGAcceptHandler::FreeStream(client->CMClient::GetAsyncStream());
			else
				_g_isAcceptHandler.CISAcceptHandler::FreeStream(client->CMClient::GetAsyncStream());

			this->CMClientMgr::FreeServer(client);
			it = m_mServerMap.erase(it);
		}
	}

	g_MServerSize = m_mServerMap.size();
	LeaveCriticalSection(&m_mserverMgr_cs);
}


hook_method<CMClient* (CMClientMgr::*)(void)> CMClientMgr::_AllocServer(SERVER, "CMClientMgr::AllocServer");
CMClient* CMClientMgr::AllocServer(void) // line 114
{
	return (this->*_AllocServer)();

	//TODO
}


hook_method<void (CMClientMgr::*)(CMClient* mServer)> CMClientMgr::_FreeServer(SERVER, "CMClientMgr::FreeServer");
void CMClientMgr::FreeServer(CMClient* mServer) // line 119
{
	return (this->*_FreeServer)(mServer);

	//TODO
}


hook_method<int (CMClientMgr::*)(CMClient* mServer)> CMClientMgr::_AddServer(SERVER, "CMClientMgr::AddServer");
int CMClientMgr::AddServer(CMClient* mServer) // line 17
{
	return (this->*_AddServer)(mServer);

	//TODO
}


hook_method<void (CMClientMgr::*)(int SID)> CMClientMgr::_DeleteServer(SERVER, "CMClientMgr::DeleteServer");
void CMClientMgr::DeleteServer(int SID) // line 29
{
	return (this->*_DeleteServer)(SID);

	//TODO
}
