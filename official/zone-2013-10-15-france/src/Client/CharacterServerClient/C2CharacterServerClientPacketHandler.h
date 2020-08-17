#pragma once
#include "HSvrIOPacketHandler.h"
struct PACKET_HZ_PING_LIVE;
struct PACKET_HZ_LOGON_KOR;
struct PACKET_HZ_PERSONAL_INFORMATION_PHL;
struct PACKET_HZ_PERSONAL_INFORMATION_THAI;
struct PACKET_HZ_PERSONAL_INFORMATION_TW;
struct PACKET_HZ_LOGON_INDONESIA;


class C2CharacterServerClientPacketHandler : public CHSvrIOPacketHandler
{
public:
	void OnClose();
	virtual int OnProcess();

public:
	DWORD GetLastPacketRecvTM();
	void SetLastPacketRecvTM(const DWORD in_LastPacketRecvTM);

private:
	virtual int DispatchPacket(short in_nHeader, int in_nPacketSize);
	void OnHZ_PING_LIVE(PACKET_HZ_PING_LIVE& in_packet);
	void OnHZ_LOGON_KOR(const PACKET_HZ_LOGON_KOR& in_packet);
	void OnHZ_PERSONAL_INFORMATION_PHL(const PACKET_HZ_PERSONAL_INFORMATION_PHL* in_packet);
	void OnHZ_PERSONAL_INFORMATION_THAI(const PACKET_HZ_PERSONAL_INFORMATION_THAI* in_packet);
	void OnHZ_PERSONAL_INFORMATION_TW(const PACKET_HZ_PERSONAL_INFORMATION_TW* in_packet);
	void OnHZ_LOGON_INDONESIA(const PACKET_HZ_LOGON_INDONESIA& in_packet);
	void OnHZ_PERSONAL_INFORMATION_INDONESIA(const char* buf);

public:
	C2CharacterServerClientPacketHandler();
	virtual ~C2CharacterServerClientPacketHandler();

public:
	/* this+ 0 */ //CHSvrIOPacketHandler baseclass_0;
	/* this+16 */ DWORD m_dwLastRecvPacketTM;
};
