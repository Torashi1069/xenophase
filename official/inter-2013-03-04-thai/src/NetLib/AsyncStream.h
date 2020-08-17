#pragma once
#include "NetLib/PacketQueue.h"
class CAsyncStream;
class CPacketHandler;
struct CAsyncOperation;


struct CAsyncOperation : public OVERLAPPED
{
	/* this+    0 */ //OVERLAPPED baseclass_0;
	/* this+   20 */ WSABUF m_dataBuf;
	/* this+   28 */ char m_buffer[10240];
	enum { RECV = 0, SEND = 1 };
	/* this+10268 */ int m_type;
	/* this+10272 */ SOCKET m_socket;
	/* this+10276 */ CAsyncStream* m_stream;
};


class CAsyncStream
{
public:
	CAsyncStream();
	CAsyncStream(int recvSize, int sendSize);
	~CAsyncStream();

public:
	virtual void Init(CPacketHandler* handler);
	virtual bool Open(SOCKET socket);
	void Send(int len, const char* buf);
	bool Send2(const unsigned char*, const int); //TODO
	bool IsSendable2(const int); //TODO
	virtual BOOL Close(const bool in_bOnlySocketClose);
	SOCKET GetSocket();
	void SetRecvQueueSize(int size);
	void SetSendQueueSize(int size);
	ULONG GetIP();
	virtual void OnComplete(BOOL result, DWORD transferSize, CAsyncOperation* op);
	DWORD GetLastError();
	CPacketQueue* GetRecvQueuePtr();

public:
	/* this+4     */ DWORD m_completionKey;

	enum
	{
		ERR_NONE              = 0,
		ERR_RECVQUEUEOVERFLOW = 1,
		ERR_SENDQUEUEOVERFLOW = 2,
	};

	/* static     */ static DWORD& m_newCompletionKey; //TODO

protected:
	virtual BOOL SendDataInQueue(int size);
	virtual BOOL OnRecvCompletion(long len);
	virtual BOOL OnSendCompletion(long len);
	DWORD GenerateCompletionKey();

protected:
	/* this+    8 */ SOCKET m_socket;
	/* this+   12 */ CPacketQueue m_sendQueue;
	/* this+   56 */ CPacketQueue m_recvQueue;
	/* this+  100 */ RTL_CRITICAL_SECTION m_csLock;
	/* this+  124 */ CAsyncOperation m_recvOperation;
	/* this+10404 */ CAsyncOperation m_sendOperation;
	/* this+20684 */ CPacketHandler* m_packetHandler;
	/* this+20688 */ DWORD m_lastError; // enum ERR_* or WSAE*
};


BOOL StartCompletionProactor();
