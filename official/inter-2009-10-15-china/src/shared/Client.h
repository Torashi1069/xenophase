#pragma once
#include "NetLib/AsyncStream.h"


class CClient
{
	struct vtable_t
	{
		void* (CClient::* scalar_deleting_destructor)(unsigned int flags);
		int (CClient::* GetType)(void);
		void (CClient::* AddErrorCount)(const char* filename, int line, unsigned long count, unsigned long time);
		void (CClient::* AddErrorCount2)(unsigned long count, unsigned long time);
		void (CClient::* Init)(void);
	};

	/* this+ 0 */ public: //const CClient::`vftable';
	/* this+ 4 */ protected: CAsyncStream* m_asyncStream;
	/* this+ 8 */ protected: RTL_CRITICAL_SECTION m_disconnector_cs;
	/* this+32 */ protected: DWORD m_dwErrorCount;
	/* this+36 */ protected: DWORD m_nBanTime;

	public: CClient::CClient(void);
	public: virtual CClient::~CClient(void);
	public: int CClient::GetType(void);
	public: void CClient::AddErrorCount(const char* filename, int line, unsigned long count, unsigned long time);
	public: void CClient::AddErrorCount(unsigned long count, unsigned long time);
	public: void CClient::Init(void);
	public: int CClient::IsErrorClient(void);
	public: int CClient::IsErrorServer(void);
	public: int CClient::Close(void);
	public: void CClient::Send(int len, const char* buf);
	public: int CClient::GetErrorCount(void);

private:
	static hook_method<int (CClient::*)(void)> CClient::_GetType;
	static hook_method<void (CClient::*)(const char* filename, int line, unsigned long count, unsigned long time)> CClient::_AddErrorCount;
	static hook_method<void (CClient::*)(unsigned long count, unsigned long time)> CClient::_AddErrorCount2;
	static hook_method<void (CClient::*)(void)> CClient::_Init;
	static hook_method<int (CClient::*)(void)> CClient::_IsErrorClient;
	static hook_method<int (CClient::*)(void)> CClient::_IsErrorServer;
	static hook_method<int (CClient::*)(void)> CClient::_Close;
	static hook_method<void (CClient::*)(int len, const char* buf)> CClient::_Send;
	static hook_method<int (CClient::*)(void)> CClient::_GetErrorCount;
};
