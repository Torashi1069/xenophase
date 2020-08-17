#pragma once
#include "NetLib/PacketHandler.h"
#include "NetLib/PacketQueue.h"
#include "struct.hpp"


class CAsyncStream
{
public:
	enum
	{
		ERR_NONE              = 0x0,
		ERR_RECVQUEUEOVERFLOW = 0x1,
		ERR_SENDQUEUEOVERFLOW = 0x2,
	};

	/* this+    0 */ public: unsigned long m_completionKey;
	/* static     */ public: static hook_val<unsigned long> m_newCompletionKey;
	/* this+    4 */ protected: SOCKET m_socket;
	/* this+    8 */ protected: CPacketQueue m_sendQueue;
	/* this+   52 */ protected: CPacketQueue m_recvQueue;
	/* this+   96 */ protected: RTL_CRITICAL_SECTION m_csLock;
	/* this+  120 */ protected: CAsyncOperation m_recvOperation;
	/* this+10400 */ protected: CAsyncOperation m_sendOperation;
	/* this+20680 */ protected: CPacketHandler* m_packetHandler;
	/* this+20684 */ protected: unsigned long m_lastError;

	public: HOOKED CAsyncStream::CAsyncStream(int recvSize, int sendSize);
	public: CAsyncStream::CAsyncStream(void);
	public: CAsyncStream::~CAsyncStream(void);
	public: void CAsyncStream::Init(CPacketHandler* handler);
	public: bool CAsyncStream::Open(SOCKET socket);
	public: void CAsyncStream::Send(int len, const char* buf);
	public: bool CAsyncStream::Send2(const unsigned char* in_pData, const int in_DataBytes);
	public: bool CAsyncStream::IsSendable2(const int in_DataBytes);
	public: HOOKED int CAsyncStream::Close(void);
	public: SOCKET CAsyncStream::GetSocket(void);
	public: void CAsyncStream::SetRecvQueueSize(int size);
	public: void CAsyncStream::SetSendQueueSize(int size);
	public: unsigned long CAsyncStream::GetIP(void);
	public: void CAsyncStream::OnComplete(int result, unsigned long transferSize, CAsyncOperation* op);
	public: unsigned long CAsyncStream::GetLastError(void);
	public: CPacketQueue* CAsyncStream::GetRecvQueuePtr(void);
	protected: int CAsyncStream::SendDataInQueue(int size);
	protected: int CAsyncStream::OnRecvCompletion(long len);
	protected: int CAsyncStream::OnSendCompletion(long len);
	protected: unsigned long CAsyncStream::GenerateCompletionKey(void);

	public: void CAsyncStream::Recv(int len, const char* buf);

private:
	static hook_method<void (CAsyncStream::*)(CPacketHandler* handler)> CAsyncStream::_Init;
	static hook_method<bool (CAsyncStream::*)(SOCKET socket)> CAsyncStream::_Open;
	static hook_method<void (CAsyncStream::*)(int len, const char* buf)> CAsyncStream::_Send;
	static hook_method<bool (CAsyncStream::*)(const unsigned char* in_pData, const int in_DataBytes)> CAsyncStream::_Send2;
	static hook_method<bool (CAsyncStream::*)(const int in_DataBytes)> CAsyncStream::_IsSendable2;
	static hook_method<int (CAsyncStream::*)(void)> CAsyncStream::_Close;
	static hook_method<SOCKET (CAsyncStream::*)(void)> CAsyncStream::_GetSocket;
	static hook_method<void (CAsyncStream::*)(int size)> CAsyncStream::_SetRecvQueueSize;
	static hook_method<void (CAsyncStream::*)(int size)> CAsyncStream::_SetSendQueueSize;
	static hook_method<unsigned long (CAsyncStream::*)(void)> CAsyncStream::_GetIP;
	static hook_method<void (CAsyncStream::*)(int result, unsigned long transferSize, CAsyncOperation* op)> CAsyncStream::_OnComplete;
	static hook_method<unsigned long (CAsyncStream::*)(void)> CAsyncStream::_GetLastError;
	static hook_method<CPacketQueue* (CAsyncStream::*)(void)> CAsyncStream::_GetRecvQueuePtr;
	static hook_method<int (CAsyncStream::*)(int size)> CAsyncStream::_SendDataInQueue;
	static hook_method<int (CAsyncStream::*)(long len)> CAsyncStream::_OnRecvCompletion;
	static hook_method<int (CAsyncStream::*)(long len)> CAsyncStream::_OnSendCompletion;
	static hook_method<unsigned long (CAsyncStream::*)(void)> CAsyncStream::_GenerateCompletionKey;
};


unsigned int __stdcall CompletionProactor(void* CP);
int __cdecl StartCompletionProactor(void);
