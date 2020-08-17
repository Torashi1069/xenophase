#pragma once
#include "NetLib/PacketHandler.h"
class CPC;
class CLogonPermitADBWork;
struct PACKET_HZ_PING;
struct PACKET_HZ_CHAR_NAME_CHANGED;


class CHSvrIOPacketHandler : public CPacketHandler
{
	struct vtable_t // const CHSvrIOPacketHandler::`vftable'
	{
		int (CHSvrIOPacketHandler::* OnProcess)(void);
		int (CPacketHandler::* OnRecvHook)(int byteTransferred, char* buf);
		void (CPacketHandler::* OnRecvOverflow)(int byteTransferred);
		void (CPacketHandler::* OnRecv)(int byteTransferred);
		void (CHSvrIOPacketHandler::* OnClose)(void);
		void (CPacketHandler::* AddSendBytes)(int len);
		void (CPacketHandler::* SetQueue)(CPacketQueue* queue);
		void* (CHSvrIOPacketHandler::* scalar_deleting_destructor)(unsigned int flags);
	};

	/* this+0 */ public: //CPacketHandler baseclass_0;

	public: CHSvrIOPacketHandler::CHSvrIOPacketHandler(void);
	public: virtual CHSvrIOPacketHandler::~CHSvrIOPacketHandler(void);
	public: virtual int CHSvrIOPacketHandler::OnProcess(void);
	public: virtual void CHSvrIOPacketHandler::OnClose(void);
	private: void CHSvrIOPacketHandler::OnLogonPermit(int len);
	public: void CHSvrIOPacketHandler::OnLogonPermit(CPC* const in_pPlayer, const unsigned long in_AID, const unsigned long in_GID, const char* in_IDstr, const unsigned long in_TotalUsingTime, const int in_selectedCharNum, CLogonPermitADBWork* const in_cpADBWork);
	private: int CHSvrIOPacketHandler::DispatchPacket(short Header, int packetSize);
	private: void CHSvrIOPacketHandler::OnDisconnect(int len, int type);
	private: void CHSvrIOPacketHandler::OnLogonRefuse(int len);
	private: void CHSvrIOPacketHandler::OnMapMove(int len);
	private: void CHSvrIOPacketHandler::OnHServerRestart(int len);
	private: void CHSvrIOPacketHandler::OnInfoRemainTime(int len);
	private: void CHSvrIOPacketHandler::OnResRemainTime(int len);
	private: void CHSvrIOPacketHandler::OnNotifyPCBang(int len);
	private: void CHSvrIOPacketHandler::OnHZ_PING(const PACKET_HZ_PING& in_packet);
	private: void CHSvrIOPacketHandler::OnNotifyPCBangPlayingTime(int len);
	private: void CHSvrIOPacketHandler::OnHZ_CHAR_NAME_CHANGED(const PACKET_HZ_CHAR_NAME_CHANGED& in_Packet);

private:
	static hook_method<int (CHSvrIOPacketHandler::*)(void)> CHSvrIOPacketHandler::_OnProcess;
	static hook_method<void (CHSvrIOPacketHandler::*)(void)> CHSvrIOPacketHandler::_OnClose;
	static hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnLogonPermit;
	static hook_method<void (CHSvrIOPacketHandler::*)(CPC* const in_pPlayer, const unsigned long in_AID, const unsigned long in_GID, const char* in_IDstr, const unsigned long in_TotalUsingTime, const int in_selectedCharNum, CLogonPermitADBWork* const in_cpADBWork)> CHSvrIOPacketHandler::_OnLogonPermit2;
	static hook_method<int (CHSvrIOPacketHandler::*)(short Header, int packetSize)> CHSvrIOPacketHandler::_DispatchPacket;
	static hook_method<void (CHSvrIOPacketHandler::*)(int len, int type)> CHSvrIOPacketHandler::_OnDisconnect;
	static hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnLogonRefuse;
	static hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnMapMove;
	static hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnHServerRestart;
	static hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnInfoRemainTime;
	static hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnResRemainTime;
	static hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnNotifyPCBang;
	static hook_method<void (CHSvrIOPacketHandler::*)(const PACKET_HZ_PING& in_packet)> CHSvrIOPacketHandler::_OnHZ_PING;
	static hook_method<void (CHSvrIOPacketHandler::*)(int len)> CHSvrIOPacketHandler::_OnNotifyPCBangPlayingTime;
	static hook_method<void (CHSvrIOPacketHandler::*)(const PACKET_HZ_CHAR_NAME_CHANGED& in_Packet)> CHSvrIOPacketHandler::_OnHZ_CHAR_NAME_CHANGED;
};
