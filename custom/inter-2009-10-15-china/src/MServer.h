#pragma once
#include "Client.h"
#include "MSPacketHandler.h"


class CMClient : public CClient
{
	struct vtable_t
	{
		void* (CMClient::* scalar_deleting_destructor)(unsigned int flags);
		int (CMClient::* GetType)(void);
		void (CClient::* AddErrorCount)(const char* filename, int line, unsigned long count, unsigned long time);
		void (CClient::* AddErrorCount2)(unsigned long count, unsigned long time);
		void (CClient::* Init)(void);
	};

	/* this+  0 */ public: //CClient baseclass_0;
	/* this+ 40 */ public: CMCPacketHandler m_packetHandler;
	/* this+ 56 */ private: unsigned long m_lastCommunicationTime;
	/* this+ 60 */ private: int m_isValid;
	/* this+ 64 */ private: char m_ID[24];
	/* this+ 88 */ private: char m_passwd[24];
	/* this+112 */ private: int m_SID;

	public: CMClient::CMClient(void);
	public: virtual CMClient::~CMClient(void);
	public: void CMClient::Init(CAsyncStream* stream);
	public: unsigned long CMClient::GetAccountID(void);
	public: void CMClient::SetLastCommunicationTime(unsigned long time);
	public: void CMClient::SetServerID(int SID);
	public: int CMClient::GetServerID(void);
	public: int CMClient::OnProcess(void);
	public: virtual int CMClient::GetType(void);
	public: void CMClient::SetValid(int flag);
	public: int CMClient::IsValid(void);
	public: char* CMClient::GetID(void);
	public: int CMClient::CheckPasswd(char* id, char* passwd);
	public: int CMClient::ChangePasswd(char* id, char* passwd, char* oldpasswd);
	public: CAsyncStream* CMClient::GetAsyncStream(void);

private:
	static hook_method<void (CMClient::*)(CAsyncStream* stream)> CMClient::_Init;
	static hook_method<unsigned long (CMClient::*)(void)> CMClient::_GetAccountID;
	static hook_method<void (CMClient::*)(unsigned long time)> CMClient::_SetLastCommunicationTime;
	static hook_method<void (CMClient::*)(int SID)> CMClient::_SetServerID;
	static hook_method<int (CMClient::*)(void)> CMClient::_GetServerID;
	static hook_method<int (CMClient::*)(void)> CMClient::_OnProcess;
	static hook_method<int (CMClient::*)(void)> CMClient::_GetType;
	static hook_method<void (CMClient::*)(int flag)> CMClient::_SetValid;
	static hook_method<int (CMClient::*)(void)> CMClient::_IsValid;
	static hook_method<char* (CMClient::*)(void)> CMClient::_GetID;
	static hook_method<int (CMClient::*)(char* id, char* passwd)> CMClient::_CheckPasswd;
	static hook_method<int (CMClient::*)(char* id, char* passwd, char* oldpasswd)> CMClient::_ChangePasswd;
	static hook_method<CAsyncStream* (CMClient::*)(void)> CMClient::_GetAsyncStream;
};
