#pragma once
#include "NetLib/AsyncStream.h"


class C2StreamObject : public CAsyncStream
{
public:
	enum
	{
		MSG_DISCONNECT = 0,
	};

public:
	LONG GetIOCPoperationCnt();
	virtual bool Open(SOCKET in_hSocket);
	virtual BOOL Close(const bool in_bOnlySocketClose);
	virtual void Init(CPacketHandler* in_cpPacketHandler);
	virtual void OnComplete(BOOL result, DWORD transferSize, CAsyncOperation* op);

protected:
	virtual BOOL SendDataInQueue(int size);
	virtual BOOL OnRecvCompletion(long len);

public:
	C2StreamObject(SOCKET in_hClient, int in_RecvQueueSize, int in_SendQueueSize);
	virtual ~C2StreamObject();

private:
	/* this+    0 */ //CAsyncStream baseclass_0;
	/* this+20692 */ LONG m_IOCPoperationCnt;
	/* this+20696 */ RTL_CRITICAL_SECTION m_CS;
	/* this+20720 */ const SOCKET m_hClient;
};
