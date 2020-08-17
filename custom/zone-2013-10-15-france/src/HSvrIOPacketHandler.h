#pragma once
#include "NetLib/PacketHandler.h"


class CHSvrIOPacketHandler : public CPacketHandler
{
public:
	CHSvrIOPacketHandler();
	virtual ~CHSvrIOPacketHandler();

public:
	virtual int OnProcess();

private:
	virtual int DispatchPacket(short Header, int packetSize);
	void OnXX_CONNECT();
//	void OnHZ_HZ_ZSVR_INFO(const struct PACKET_HZ_ZSVR_INFO &);
//	void OnDisconnect(int, int);
//	void OnLogonPermit(int);
//	void OnLogonRefuse(int);
//	void OnHZ_LOGON_CHN(struct PACKET_HZ_LOGON_CHN &);
//	void OnMapMove(const unsigned long, const unsigned long);
//	void OnHServerRestart(int);
//	void OnInfoRemainTime(int);
//	void OnResRemainTime(int);
//	void OnHZ_NOTIFY_PCBANG(const struct PACKET_HZ_NOTIFY_PCBANG &);
//	void OnHZ_PERSONAL_INFORMATION(const struct PACKET_HZ_PERSONAL_INFORMATION &);
//	void OnHZ_PERSONAL_INFORMATION_2ND(const struct PACKET_HZ_PERSONAL_INFORMATION_2ND *);
//	void OnHZ_PERSONAL_INFORMATION_BRZ(const struct PACKET_HZ_PERSONAL_INFORMATION_BRZ *);
//	void OnHZ_PERSONAL_INFORMATION_CHN(const struct PACKET_HZ_PERSONAL_INFORMATION_CHN *);
//	void OnHZ_FATIGUE_INFO_CHN(const struct PACKET_HZ_FATIGUE_INFO_CHN &);
//	void OnHZ_DISPATCH_TIMING_CHN(const struct PACKET_HZ_DISPATCH_TIMING_CHN &);
//	void OnHZ_LOGON_TW(const struct PACKET_HZ_LOGON_TW &);
//	void OnHZ_PING(const struct PACKET_HZ_PING &);
//	void OnNotifyPCBangPlayingTime(int);
//	void OnHZ_CHAR_NAME_CHANGED(const struct PACKET_HZ_CHAR_NAME_CHANGED &);
//	void OnHZ_USER_COUNT_REQ(const struct PACKET_HZ_USER_COUNT_REQ &);
//	void OnHZ_AUTH_ACK(const struct PACKET_HZ_AUTH_ACK &);
//	void OnXX_DISCONNECT(const struct PACKET_XX_DISCONNECT &);
//	void OnHZ_LOGON_FRA(const struct PACKET_HZ_LOGON_FRA &);

private:
	/* this+ 0 */ //CHSvrIOPacketHandler baseclass_0;
	/* this+ 8 */ DWORD m_OverPopulationCheckTM;
	/* this+12 */ bool m_bOverPopulation;

	friend class C2CharacterServerClientPacketHandler;
};
