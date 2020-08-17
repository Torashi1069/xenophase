#pragma once
#include "ISvrIOPacketHandler.h"
struct PACKET_IZ_PING_LIVE;
struct PACKET_IZ_OTHER_ZONE_PC_SEND_MSG;
struct PACKET_IZ_INSTANTMAP_ADD3;
struct PACKET_IZ_INSTANTMAP_REMOVE3;
struct PACKET_IZ_INSTANTMAP_PLAYER_ENTER3;


class C2InterServerClientPacketHandler : public CISvrIOPacketHandler
{
public:
	virtual void OnClose();
	virtual int OnProcess();

public:
	DWORD GetLastPacketRecvTM();
	void SetLastPacketRecvTM(DWORD in_LastPacketRecvTM);

private:
	virtual int DispatchPacket(short Header, int packetSize);
	void OnIZ_PING_LIVE(const PACKET_IZ_PING_LIVE& in_packet);
	void OnIZ_OTHER_ZONE_PC_SEND_MSG(const PACKET_IZ_OTHER_ZONE_PC_SEND_MSG& in_packet);
	void OnIZ_INSTANTMAP_ADD3(const PACKET_IZ_INSTANTMAP_ADD3& in_packet);
	void OnIZ_INSTANTMAP_REMOVE3(const PACKET_IZ_INSTANTMAP_REMOVE3& in_packet);
	void OnIZ_INSTANTMAP_PLAYER_ENTER3(const PACKET_IZ_INSTANTMAP_PLAYER_ENTER3& in_packet);
	void OnIZ_RELAY_NOTIFY(const int packetSize, const char* buf);

public:
	C2InterServerClientPacketHandler();
	virtual ~C2InterServerClientPacketHandler();

private:
	/* this+    0 */ //CISvrIOPacketHandler baseclass_0;
	/* this+15380 */ DWORD m_LastPacketRecvTM;
};
