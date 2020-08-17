#pragma once
#include "NetLib/AsyncStream.h"
#include "NetLib/MemoryMgr.h"


class CZsvrAcceptHandler
{
public:
	bool isOK() const;
	BOOL Init(bool in_bUsePrivateIP, int in_StreamPoolSize);
	CAsyncStream* AllocStream();
	void FreeStream(CAsyncStream* stream);
	bool OnConnect(const SOCKET in_Socket, const int in_ZSID, const DWORD in_dwIP);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CZsvrAcceptHandler* GetObj(); /// @custom

private:
	CZsvrAcceptHandler();
	virtual ~CZsvrAcceptHandler();
	CZsvrAcceptHandler(CZsvrAcceptHandler&); // = delete;
	CZsvrAcceptHandler& operator=(CZsvrAcceptHandler&); // = delete;

private:
	/* static  */ static CZsvrAcceptHandler*& m_cpSelf; //TODO
	/* this+ 0 */ //const CZsvrAcceptHandler::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ CMemoryMgr<CAsyncStream> m_streamPool;
	/* this+48 */ std::set<DWORD> m_set;
};
