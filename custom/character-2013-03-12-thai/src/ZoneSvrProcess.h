#pragma once
#include "Network3/AsyncProcess.h"
#include "Network3/Process.h"
struct PACKET_ZH_AUTH_REQ;
struct PACKET_ZH_CHAR_EXIT2;
struct PACKET_ZH_PING_LIVE;
struct PACKET_ZH_RESTART2;


class CZoneSvrProcess : public CProcess, public CAsyncProcess
{
public:
	CZoneSvrProcess();
	virtual ~CZoneSvrProcess();
	virtual bool OnRecv(char* buffer, int* len);
	virtual bool OnConnect();
	virtual void OnClose();
	virtual bool ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize);

public:
	/* this+ 0 */ //CProcess baseclass_0;
	/* this+56 */ //CAsyncProcess baseclass_56;

private:
	void OnZH_CHAR_EXIT(const DWORD in_AID, const BYTE in_disconnetedType, const int in_TotalCnt);
	void OnZH_RESTART(const DWORD in_dwSessionID, const DWORD in_AID, const int in_TotalCnt);
//	void OnZH_CONNECT_AUTH();
	void OnZI_PING_LIVE(const DWORD in_dwSessionID, const PACKET_ZH_PING_LIVE& in_pPacket);
	bool ProcessPacket_ZH_PING(const DWORD dwSessionID, const char* pPacket);
	bool ProcessPacket_ZH_ZSVR_INFO(const DWORD dwSessionID, const char* pPacket);
	bool ProcessPacket_ServerEntry(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_Logon(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_CharExit(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_ZH_CHAR_EXIT2(const DWORD in_dwSessionID, const PACKET_ZH_CHAR_EXIT2& in_pPacket);
	bool ProcessPacket_ZH_CONNECTED_AUTH(const DWORD in_dwSessionID, const PACKET_ZH_AUTH_REQ& in_pPacket);
	bool ProcessPacket_MapMove(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_SaveUsingTime(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_Restart(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_ZH_RESTART2(const DWORD in_dwSessionID, const PACKET_ZH_RESTART2& in_pPacket); /// @custom
	bool ProcessPacket_ReqRemainTime(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_MoveToPVPWorld(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_SaveCharInfo(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_PLAYER_ALIVE(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_CASTLE_MAP_MOVE(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_ZONE_USER_COUNT_ACK(DWORD dwSessionID, char* pPacket);

private:
	/* this+60 */ int m_nZoneListenPort;
	/* this+64 */ short m_nBeforePKTHeader;
	/* this+68 */ int m_nBeforePKTRecvLength;
	/* this+72 */ int m_nBeforeOrgPKTSize;
};
