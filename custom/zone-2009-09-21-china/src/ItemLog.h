#pragma once
#include "DatabaseLog.h"
#include "struct.hpp"
struct IVItItem;
class CCharacter;
class CPC;
class CITP;


struct SITEMLOG_USERINFO
{
	/* this+ 0 */ int m_nAccountID;
	/* this+ 4 */ char m_szAccount[24];
	/* this+28 */ DWORD m_dwCharID;
	/* this+32 */ char m_szCharName[24];
};


struct SITEMLOG
{
	/* this+  0 */ int m_nVersion;
	/* this+  4 */ int m_nServerID;
	/* this+  8 */ int m_ActionType;
	/* this+ 12 */ char m_szIP[20];
	/* this+ 32 */ int m_nEventPosX;
	/* this+ 36 */ int m_nEventPosY;
	/* this+ 40 */ SITEMLOG_USERINFO m_srcUserInfo;
	/* this+ 96 */ SITEMLOG_USERINFO m_desUserInfo;
	/* this+152 */ DWORD m_dwItemSerialcode;
	/* this+156 */ char m_szItemName[24];
	/* this+180 */ DWORD m_dwITID;
	/* this+184 */ DWORD m_dwItemCount;
	/* this+188 */ char m_szMapName[25];
	/* this+216 */ DWORD m_dwPrice;
	/* this+220 */ EQUIPSLOTINFO m_equipSlotInfo;
	/* this+228 */ int m_nRefingLevel;
	/* this+232 */ DWORD m_dwAuctionID;
	/* this+236 */ DWORD m_dwRemainZeny;
	/* this+240 */ DWORD m_dwDestRemainZeny;
	/* this+248 */ __int64 m_NP_ItemSerialNum;
	/* this+256 */ long m_NP_ItemHireExpireDate;
	/* this+260 */ int m_NP_bCashItem;
};


class CItemLog : public CDatabaseLog<SITEMLOG*>
{
	/* this+0 */ public: //CDatabaseLog<SITEMLOG*> baseclass_0;

	public: void CItemLog::AddItemLog(int nType, CPC* pPC, CCharacter* pDestChar, IVItItem* pIvitItem, int nPrice, int nCount, char* Tx_ID);
	public: void CItemLog::AddMailAuctionLog(unsigned long AuctionID, int nType, unsigned long SrcAID, unsigned long SrcGID, char* SrcName, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice);
	public: void CItemLog::AddMailSendLog(unsigned long AuctionID, int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice);
	public: void CItemLog::AddMailReceiveLog(int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice);
	public: void CItemLog::AddItemLogOnMoney(int nType, CPC* pPC, CCharacter* pDestChar, int nPrice, int nCount, unsigned long AuctionID);
	public: virtual void CItemLog::ConnectToDatabase(const char* Log);
	public: void CItemLog::AddCITPLog(int nType, CPC* pPC, CPC* pDestPC, CITP* piteminfo, int nPrice, int nCount);
	private: virtual int CItemLog::SaveToDatabase(SQLHSTMT hStmt, SITEMLOG* pLog);
	private: int CItemLog::SaveToDatabaseV1(SQLHSTMT hStmt, SITEMLOG* pLog);
	private: int CItemLog::SaveToDatabaseV2(SQLHSTMT const in_hStmt, SITEMLOG* pLog);

private:
	static hook_method<void (CItemLog::*)(int nType, CPC* pPC, CCharacter* pDestChar, IVItItem* pIvitItem, int nPrice, int nCount, char* Tx_ID)> CItemLog::_AddItemLog;
	static hook_method<void (CItemLog::*)(unsigned long AuctionID, int nType, unsigned long SrcAID, unsigned long SrcGID, char* SrcName, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice)> CItemLog::_AddMailAuctionLog;
	static hook_method<void (CItemLog::*)(unsigned long AuctionID, int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice)> CItemLog::_AddMailSendLog;
	static hook_method<void (CItemLog::*)(int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice)> CItemLog::_AddMailReceiveLog;
	static hook_method<void (CItemLog::*)(int nType, CPC* pPC, CCharacter* pDestChar, int nPrice, int nCount, unsigned long AuctionID)> CItemLog::_AddItemLogOnMoney;
	static hook_method<void (CItemLog::*)(const char* Log)> CItemLog::_ConnectToDatabase;
	static hook_method<void (CItemLog::*)(int nType, CPC* pPC, CPC* pDestPC, CITP* piteminfo, int nPrice, int nCount)> CItemLog::_AddCITPLog;
	static hook_method<int (CItemLog::*)(SQLHSTMT hStmt, SITEMLOG* pLog)> CItemLog::_SaveToDatabase;
	static hook_method<int (CItemLog::*)(SQLHSTMT hStmt, SITEMLOG* pLog)> CItemLog::_SaveToDatabaseV1;
	static hook_method<int (CItemLog::*)(SQLHSTMT const in_hStmt, SITEMLOG* pLog)> CItemLog::_SaveToDatabaseV2;
};
