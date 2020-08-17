#pragma once
#include "NetLib/PacketHandler.h"
class CMClient;


class CMCPacketHandler : public CPacketHandler
{
	struct vtable_t
	{
		int (CMCPacketHandler::* OnProcess)(void);
		int (CPacketHandler::* OnRecvHook)(int byteTransferred, char* buf);
		void (CPacketHandler::* OnRecvOverflow)(int byteTransferred);
		void (CPacketHandler::* OnRecv)(int byteTransferred);
		void (CMCPacketHandler::* OnClose) (void);
		void (CPacketHandler::* SetLastError)(unsigned long lastError);
		void (CPacketHandler::* AddSendBytes)(int len);
		void (CPacketHandler::* SetQueue)(CPacketQueue* queue);
		void* (CMCPacketHandler::* scalar_deleting_destructor)(unsigned int flags);
	};

	/* this+ 0 */ public: //CPacketHandler baseclass_0;
	/* this+ 8 */ private: short OldHeader;
	/* this+12 */ private: CMClient* m_mServer;

	public: CMCPacketHandler::CMCPacketHandler(void);
	public: virtual CMCPacketHandler::~CMCPacketHandler(void);
	public: virtual void CMCPacketHandler::OnClose(void);
	public: virtual int CMCPacketHandler::OnProcess(void);
	public: void CMCPacketHandler::SetMyOwner(CMClient* mServer);
	private: int CMCPacketHandler::DispatchPacket(short Header, int packetSize);
	private: void CMCPacketHandler::OnMIEnter(int len);
	private: void CMCPacketHandler::OnMIReqServerState(int len);
	private: void CMCPacketHandler::OnMIMsg(int len);
	private: void CMCPacketHandler::OnMIShotDown(int len);
	private: void CMCPacketHandler::OnMIGetGuildInfo(int len);
	private: void CMCPacketHandler::OnMIGuildInfoInit(int len);
	private: void CMCPacketHandler::OnMIAllyGuildInfoInit(int len);

private:
	static hook_method<void (CMCPacketHandler::*)(void)> CMCPacketHandler::_OnClose;
	static hook_method<int (CMCPacketHandler::*)(void)> CMCPacketHandler::_OnProcess;
	static hook_method<void (CMCPacketHandler::*)(CMClient* mServer)> CMCPacketHandler::_SetMyOwner;
	static hook_method<int (CMCPacketHandler::*)(short Header, int packetSize)> CMCPacketHandler::_DispatchPacket;
	static hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIEnter;
	static hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIReqServerState;
	static hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIMsg;
	static hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIShotDown;
	static hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIGetGuildInfo;
	static hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIGuildInfoInit;
	static hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIAllyGuildInfoInit;
};
