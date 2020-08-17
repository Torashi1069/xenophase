#pragma once
#include "NetLib/PacketHandler.h"
#include "NetLib/PacketQueue.h"
#include "structs.hpp" // CAsyncOperation


class CAsyncStream
{
	/* static     */ public: static hook_val<unsigned long> m_newCompletionKey;
	/* this+    0 */ public: unsigned long m_completionKey;
	/* this+    4 */ protected: SOCKET m_socket;
	/* this+    8 */ protected: CPacketQueue m_sendQueue;
	/* this+   52 */ protected: CPacketQueue m_recvQueue;
	/* this+   96 */ protected: RTL_CRITICAL_SECTION m_csLock;
	/* this+  120 */ protected: CAsyncOperation m_recvOperation;
	/* this+10400 */ protected: CAsyncOperation m_sendOperation;
	/* this+20680 */ protected: CPacketHandler* m_packetHandler;
	/* this+20684 */ protected: unsigned long m_lastError;

	enum
	{
		ERR_NONE = 0x0,
		ERR_RECVQUEUEOVERFLOW = 0x1,
		ERR_SENDQUEUEOVERFLOW = 0x2,
	};

	//public: void CAsyncStream::CAsyncStream(int, int);
	//public: void CAsyncStream::CAsyncStream();
	//public: void CAsyncStream::~CAsyncStream();
	public: void CAsyncStream::Init(CPacketHandler* handler);
	public: bool CAsyncStream::Open(SOCKET s);
	public: void CAsyncStream::Send(int len, const char* buf);
	//public: bool CAsyncStream::Send2(const unsigned char *, const int);
	//public: bool CAsyncStream::IsSendable2(const int);
	public: int CAsyncStream::Close(void);
	//public: unsigned int GetSocket();
	public: void CAsyncStream::SetRecvQueueSize(int size);
	public: void CAsyncStream::SetSendQueueSize(int size);
	//public: unsigned long CAsyncStream::GetIP();
	//public: void CAsyncStream::OnComplete(int, unsigned long, struct CAsyncOperation *);
	//public: unsigned long CAsyncStream::GetLastError();
	//public: class CPacketQueue * CAsyncStream::GetRecvQueuePtr();
	//protected: int CAsyncStream::SendDataInQueue(int);
	//protected: int CAsyncStream::OnRecvCompletion(long);
	//protected: int CAsyncStream::OnSendCompletion(long);
	//protected: unsigned long CAsyncStream::GenerateCompletionKey();

private:
	static hook_method<void (CAsyncStream::*)(CPacketHandler* handler)> CAsyncStream::_Init;
	static hook_method<bool (CAsyncStream::*)(SOCKET s)> CAsyncStream::_Open;
	static hook_method<void (CAsyncStream::*)(int len, const char* buf)> CAsyncStream::_Send;
	static hook_method<int (CAsyncStream::*)(void)> CAsyncStream::_Close;
	static hook_method<void (CAsyncStream::*)(int size)> CAsyncStream::_SetRecvQueueSize;
	static hook_method<void (CAsyncStream::*)(int size)> CAsyncStream::_SetSendQueueSize;
};


int __cdecl StartCompletionProactor(void);
