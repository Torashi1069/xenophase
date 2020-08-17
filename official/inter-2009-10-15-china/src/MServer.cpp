#include "MServer.h"


CMClient::CMClient(void) // line 8
{
	m_asyncStream = NULL;
}


CMClient::~CMClient(void) // line 13
{
}


hook_method<void (CMClient::*)(CAsyncStream* stream)> CMClient::_Init(SERVER, "CMClient::Init");
void CMClient::Init(CAsyncStream* stream) // line 17
{
	return (this->*_Init)(stream);

	this->CMClient::SetValid(0);
	m_packetHandler.CMCPacketHandler::SetMyOwner(this);
	m_asyncStream = stream;
	m_dwErrorCount = 0;
	m_nBanTime = 0;
	m_lastCommunicationTime = timeGetTime();
}


hook_method<unsigned long (CMClient::*)(void)> CMClient::_GetAccountID(SERVER, "CMClient::GetAccountID");
unsigned long CMClient::GetAccountID(void) // line 51
{
	return (this->*_GetAccountID)();

	return -1;
}


hook_method<void (CMClient::*)(unsigned long time)> CMClient::_SetLastCommunicationTime(SERVER, "CMClient::SetLastCommunicationTime");
void CMClient::SetLastCommunicationTime(unsigned long time) // line 105
{
	return (this->*_SetLastCommunicationTime)(time);

	m_lastCommunicationTime = time;
}


hook_method<void (CMClient::*)(int SID)> CMClient::_SetServerID(SERVER, "CMClient::SetServerID");
void CMClient::SetServerID(int SID) // line 29
{
	return (this->*_SetServerID)(SID);

	m_SID = SID;
}


hook_method<int (CMClient::*)(void)> CMClient::_GetServerID(SERVER, "CMClient::GetServerID");
int CMClient::GetServerID(void) // line 34
{
	return (this->*_GetServerID)();

	return m_SID;
}


hook_method<int (CMClient::*)(void)> CMClient::_OnProcess(SERVER, "CMClient::OnProcess");
int CMClient::OnProcess(void) // line 38
{
	return (this->*_OnProcess)();

	if( timeGetTime() - m_lastCommunicationTime >= 60000 )
		return 0;

	return m_packetHandler.OnProcess();
}


hook_method<int (CMClient::*)(void)> CMClient::_GetType(SERVER, "CMClient::GetType");
int CMClient::GetType(void) // line 20 (MServer.h)
{
	return (this->*_GetType)();

	return 0;
}


hook_method<void (CMClient::*)(int flag)> CMClient::_SetValid(SERVER, "CMClient::SetValid");
void CMClient::SetValid(int flag) // line 56
{
	return (this->*_SetValid)(flag);

	m_isValid = flag;
}


hook_method<int (CMClient::*)(void)> CMClient::_IsValid(SERVER, "CMClient::IsValid");
int CMClient::IsValid(void) // line 61
{
	return (this->*_IsValid)();

	return m_isValid;
}


hook_method<char* (CMClient::*)(void)> CMClient::_GetID(SERVER, "CMClient::GetID");
char* CMClient::GetID(void) // line 66
{
	return (this->*_GetID)();

	return m_ID;
}


hook_method<int (CMClient::*)(char* id, char* passwd)> CMClient::_CheckPasswd(SERVER, "CMClient::CheckPasswd");
int CMClient::CheckPasswd(char* id, char* passwd) // line 70
{
	return (this->*_CheckPasswd)(id, passwd);

	//TODO
}


hook_method<int (CMClient::*)(char* id, char* passwd, char* oldpasswd)> CMClient::_ChangePasswd(SERVER, "CMClient::ChangePasswd");
int CMClient::ChangePasswd(char* id, char* passwd, char* oldpasswd) // line 92
{
	return (this->*_ChangePasswd)(id, passwd, oldpasswd);

	//TODO
}


hook_method<CAsyncStream* (CMClient::*)(void)> CMClient::_GetAsyncStream(SERVER, "CMClient::GetAsyncStream");
CAsyncStream* CMClient::GetAsyncStream(void) // line 27 (MServer.h)
{
	return (this->*_GetAsyncStream)();

	return m_asyncStream;
}
