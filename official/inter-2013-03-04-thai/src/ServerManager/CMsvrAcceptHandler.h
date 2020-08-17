#pragma once
#include "NetLib/AsyncStream.h"
#include "NetLib/MemoryMgr.h"


class CMsvrAcceptHandler
{
public:
	bool isOK() const;
	BOOL Init(int streamPoolSize);
	CAsyncStream* AllocStream();
	void FreeStream(CAsyncStream* pStream);
	virtual BOOL OnConnect(SOCKET s, DWORD ip);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CMsvrAcceptHandler* GetObj(); /// @custom

private:
	CMsvrAcceptHandler();
	virtual ~CMsvrAcceptHandler();
	CMsvrAcceptHandler(CMsvrAcceptHandler&); // = delete;
	CMsvrAcceptHandler& operator=(CMsvrAcceptHandler&); // = delete;

protected:
	/* static */ static CMsvrAcceptHandler*& m_cpSelf; //TODO
	/* this+0 */ //const CMsvrAcceptHandler::`vftable';
	/* this+4 */ bool m_bOK;
	/* this+8 */ CMemoryMgr<CAsyncStream> m_streamPool;
};
