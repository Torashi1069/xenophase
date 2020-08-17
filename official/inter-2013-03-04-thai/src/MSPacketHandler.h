#pragma once
#include "NetLib/PacketHandler.h"
class CMClient;
struct PACKET_MI_MSG;
struct PACKET_MI_REQ_EDIT_EXP;


class CMCPacketHandler : public CPacketHandler
{
public:
	CMCPacketHandler();
	virtual ~CMCPacketHandler();
	virtual void OnClose();
	virtual int OnProcess();
	void SetMyOwner(CMClient* mServer);

private:
	/* this+ 8 */ short OldHeader;

private:
	int DispatchPacket(short Header, int packetSize);
	void OnMIEnter(int len);
	void OnMIReqServerState(int len);
	void OnMI_MSG(const PACKET_MI_MSG* in_pPacket);
	void OnMIShotDown(int len);
	void OnMIGetGuildInfo(int len);
	void OnMIGuildInfoInit(int len);
	void OnMIAllyGuildInfoInit(int len);
	void OnMI_REQ_EDIT_EXP(const PACKET_MI_REQ_EDIT_EXP& in_packet);

private:
	/* this+12 */ CMClient* m_mServer;
};
