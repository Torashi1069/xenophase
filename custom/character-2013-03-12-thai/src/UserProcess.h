#pragma once
#include "Character.h" // MAX_CHARINFO_SLOT_COUNT
#include "CharacterDB.h" // SCHARINFO
#include "Network3/AsyncProcess.h"
#include "Network3/Process.h"


class CUserProcess : public CProcess, public CAsyncProcess
{
public:
	CUserProcess();
	virtual ~CUserProcess();
	virtual bool OnRecv(char* buffer, int* len);
	virtual bool OnConnect();
	virtual void OnClose();
	void CloseForce(DWORD dwSessionID, DWORD dwTime);
	virtual bool ProcessPacket(DWORD dwSessionID, char* pPacket, WORD wPacketType, int nPacketSize);
	void OnLogonAck(void* pvLogonAck, DWORD in_SessionID, int nPremiumService);
//	void OnHCSecondPWReq(const DWORD, const DWORD, const bool, const bool);
//	DWORD GetAID();

public:
	/* this+   0 */ //CProcess baseclass_0;
	/* this+  56 */ //CAsyncProcess baseclass_56;
	/* this+  60 */ bool m_bAuthPending;
	/* this+  61 */ bool m_bAuthenticated;
	/* this+  64 */ RTL_CRITICAL_SECTION m_CS;

private:
	bool ProcessPacket_Enter(DWORD in_SessionID, char* pPacket);
	bool ProcessPacket_SelectCharacter(DWORD in_SessionID, char* pPacket);
	bool ProcessPacket_Ack_Character_Password(DWORD in_SessionID, char* pPacket);
	bool ProcessPacket_MakeCharacter(const DWORD dwSessionID, const char* pPacket);
//	bool ProcessPacket_CH_DELETE_CHAR3_RESERVED(const DWORD, const PACKET_CH_DELETE_CHAR3_RESERVED&);
//	bool ProcessPacket_CH_DELETE_CHAR3(const DWORD, const PACKET_CH_DELETE_CHAR3&);
//	bool ProcessPacket_CH_DELETE_CHAR3_CANCEL(const DWORD, const PACKET_CH_DELETE_CHAR3_CANCEL&);
//	bool ProcessPacket_CH_DELETE_CHAR3_EXT(const DWORD, const PACKET_CH_DELETE_CHAR3_EXT&);
	bool ProcessPacket_DeleteCharacter(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_DeleteCharacter2(DWORD dwSessionID, char* pPacket);
	bool ProcessPacket_Ping(DWORD dwSessionID, char* pPacket);
//	bool ProcessPacket_IsValidCharName(DWORD dwSessionID, char* pPacket);
//	bool ProcessPacket_ChangeCharName(DWORD dwSessionID, char* pPacket);
//	bool ProcessPacket_Select_Char_GoingToBeUsed(DWORD dwSessionID, char* pPacket);
	bool ChangeDoNotSaveMap(int nCount, const int nMaxCharInfoSlotCount);
//	bool LoadCharacters(const DWORD);
//	SCHARINFO* FindCharacterbyGID(const DWORD);

private:
	/* this+  88 */ bool m_bCharSelected;
	/* this+  92 */ DWORD m_dwAID;
	/* this+  96 */ DWORD m_dwCharacterPassSeedValue;
	/* this+ 100 */ bool m_bSelectCharToBeUsed;
	/* this+ 104 */ SCHARINFO m_charInfo[MAX_CHARINFO_SLOT_COUNT];
	/* this+4352 */ int m_iSelectedSlot;
	/* this+4356 */ BYTE m_bytePanaltyCount;

private:
//	bool UpdateCharInfoFromGID(const DWORD);
//	bool UpdateCharInfoFromSlotNum(const DWORD);
};
