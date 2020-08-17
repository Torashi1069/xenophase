#pragma once
#include "NetLib/PacketQueue.h"


class CPacketHandler
{
	struct vtable_t
	{
		int (CPacketHandler::* OnProcess)(void);
		int (CPacketHandler::* OnRecvHook)(int byteTransferred, char* buf);
		void (CPacketHandler::* OnRecvOverflow)(int byteTransferred);
		void (CPacketHandler::* OnRecv)(int byteTransferred);
		void (CPacketHandler::* OnClose)(void);
		void (CPacketHandler::* AddSendBytes)(int len);
		void (CPacketHandler::* SetQueue)(CPacketQueue* queue);
	};

	/* this+0 */ public: //const CPacketHandler::`vftable';
	/* this+4 */ protected: CPacketQueue* m_recvQueue;

	public: CPacketHandler::CPacketHandler(void);
	public: void CPacketHandler::Reset(void);
	public: virtual int CPacketHandler::OnProcess(void);
	public: virtual int CPacketHandler::OnRecvHook(int byteTransferred, char* buf);
	public: virtual void CPacketHandler::OnRecvOverflow(int byteTransferred);
	public: virtual void CPacketHandler::OnRecv(int byteTransferred);
	public: virtual void CPacketHandler::OnClose(void);
	public: virtual void CPacketHandler::AddSendBytes(int len);
	public: virtual void CPacketHandler::SetQueue(CPacketQueue* queue);

private:
	static hook_method<void (CPacketHandler::*)(void)> CPacketHandler::_Reset;
	static hook_method<int  (CPacketHandler::*)(void)> CPacketHandler::_OnProcess;
	static hook_method<int  (CPacketHandler::*)(int byteTransferred, char* buf)> CPacketHandler::_OnRecvHook;
	static hook_method<void (CPacketHandler::*)(int byteTransferred)> CPacketHandler::_OnRecvOverflow;
	static hook_method<void (CPacketHandler::*)(int byteTransferred)> CPacketHandler::_OnRecv;
	static hook_method<void (CPacketHandler::*)(void)> CPacketHandler::_OnClose;
	static hook_method<void (CPacketHandler::*)(int len)> CPacketHandler::_AddSendBytes;
	static hook_method<void (CPacketHandler::*)(CPacketQueue* queue)> CPacketHandler::_SetQueue;
};
