#pragma once
#include "Character.h" // MAX_CHARINFO_SLOT_COUNT
#include "CharacterDB.h" // SCHARINFO
#include "Network3/AsyncProcess.h"
#include "Network3/Process.h"
struct PACKET_AH_LOGON_ACK;


class CUserProcess : public CProcess, public CAsyncProcess
{
public:
	CUserProcess();
	virtual ~CUserProcess();
	virtual bool OnRecv(char* buffer, int* len);
	virtual bool OnConnect();
	virtual void OnClose();
	void CloseForce(DWORD dwSessionID, DWORD dwTime);
	int GetPacketSize(WORD wPacketType);
	virtual bool ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize);
	void OnLogonAck(PACKET_AH_LOGON_ACK* pLogonAck, DWORD dwSessionID);
//	DWORD GetAID();

public:
	/* this+   0 */ //CProcess baseclass_0;
	/* this+  40 */ //CAsyncProcess baseclass_40;
	/* this+  44 */ bool m_bAuthPending;
	/* this+  45 */ bool m_bAuthenticated;

private:
	bool ProcessPacket_Enter(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_SelectCharacter(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_Ack_Character_Password(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_MakeCharacter(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_DeleteCharacter(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_DeleteCharacter2(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_Ping(DWORD dwSessionID, char* pPacket);
//	bool ProcessPacket_IsValidCharName(DWORD dwSessionID, char* pPacket);
//	bool ProcessPacket_ChangeCharName(DWORD dwSessionID, char* pPacket);
	bool ChangeDoNotSaveMap(int nCount);

private:
	/* this+  48 */ int m_iSelectedSlot;
	/* this+  52 */ unsigned char m_bytePanaltyCount;
	/* this+  53 */ bool m_bCharSelected;
	/* this+  56 */ DWORD m_dwAID;
	/* this+  60 */ SCHARINFO m_charInfo[MAX_CHARINFO_SLOT_COUNT];
	/* this+1428 */ DWORD m_dwCharacterPassSeedValue;
};
