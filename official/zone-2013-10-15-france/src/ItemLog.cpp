#include "GVar.h"
#include "ImportantItem.h"
#include "ItemLog.h"
#include "ITPMgr.h"
#include "PC.h"
#include "ZoneProcess.h"
#include "Player/Inventory/CIVItEquipItem.h"
#include "shared/CDateTime.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/ServerInfo.h"


void CItemLog::ConnectToDatabase(const char* Log)
{
	this->CExtendedODBC::Connect(Log, g_dbPWD);
}


static void ItemLog_SetUserInfo(SITEMLOG_USERINFO* pUserInfo, CCharacter* pChar)
{
	if( pChar->GetType() == PC_TYPE )
	{
		CPC* pPC = static_cast<CPC*>(pChar);
		pUserInfo->m_nAccountID = pPC->m_characterInfo.accountID;
		pUserInfo->m_dwCharID = pPC->m_characterInfo.characterID;
		memcpy_s(pUserInfo->m_szAccount, sizeof(pUserInfo->m_szAccount), pPC->m_characterInfo.accountName, sizeof(pPC->m_characterInfo.accountName));
		memcpy_s(pUserInfo->m_szCharName, sizeof(pUserInfo->m_szCharName), pPC->m_characterInfo.characterName, sizeof(pPC->m_characterInfo.characterName));
	}
	else
	{
		CNPC* pNPC = static_cast<CNPC*>(pChar);
		memcpy_s(pUserInfo->m_szCharName, sizeof(pUserInfo->m_szCharName), pNPC->CNPC::GetAccountName(), strlen(pNPC->CNPC::GetAccountName())); //FIXME: off-by-one
	}
}


void CItemLog::AddItemLogOnMoney(int nType, CPC* pPC, CCharacter* pDestChar, int nPrice, int nCount, unsigned long AuctionID, const __int64 in_Identity)
{
	SITEMLOG* pLog = new SITEMLOG;
	if( pLog == NULL )
		return;

	memset(pLog, 0, sizeof(*pLog));
	static int nServerID = g_serverInfo.CServerInfo::GetLocalServerID();

	pLog->m_nServerID = nServerID;
	pLog->m_Identity = in_Identity;
	pLog->m_ActionType = nType;
	pPC->GetParameterValue(VAR_CURXPOS, pLog->m_nEventPosX);
	pPC->GetParameterValue(VAR_CURYPOS, pLog->m_nEventPosY);
	ItemLog_SetUserInfo(&pLog->m_srcUserInfo, pPC);
	if( pDestChar != NULL )
		ItemLog_SetUserInfo(&pLog->m_desUserInfo, pDestChar);
	pLog->m_nVersion = 2;

	in_addr addr;
	addr.s_addr = pPC->m_ip;
	strcpy(pLog->m_szIP, inet_ntoa(addr));

	pLog->m_dwPrice = nPrice;
	pLog->m_dwItemCount = nCount;
	strcpy(pLog->m_szMapName, pPC->m_characterInfo.mapName);
	pLog->m_dwAuctionID = AuctionID;
	pPC->GetParameterValue(VAR_MONEY, *(int*)&pLog->m_dwRemainZeny);
	if( pDestChar != NULL )
		pDestChar->GetParameterValue(VAR_MONEY, *(int*)&pLog->m_dwDestRemainZeny);
	else
		pLog->m_dwDestRemainZeny = -1;

	this->CDatabaseLog<SITEMLOG*>::AddLog(pLog);
}


void CItemLog::AddMailAuctionLog(unsigned long AuctionID, int nType, unsigned long SrcAID, unsigned long SrcGID, char* SrcName, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice)
{
	SITEMLOG* pLog = new SITEMLOG;
	if( pLog == NULL )
		return;

	memset(pLog, 0, sizeof(*pLog));
	static int nServerID = g_serverInfo.CServerInfo::GetLocalServerID();

	pLog->m_nEventPosX = 0;
	pLog->m_nEventPosY = 0;
	pLog->m_nServerID = nServerID;
	pLog->m_ActionType = nType;
	pLog->m_srcUserInfo.m_nAccountID = SrcAID;
	pLog->m_srcUserInfo.m_dwCharID = SrcGID;
	strcpy(pLog->m_srcUserInfo.m_szCharName, SrcName);
	strcpy(pLog->m_srcUserInfo.m_szAccount, "Unknow");
	pLog->m_desUserInfo.m_nAccountID = DestAID;
	pLog->m_desUserInfo.m_dwCharID = DestGID;
	strcpy(pLog->m_desUserInfo.m_szCharName, DestName);
	strcpy(pLog->m_desUserInfo.m_szAccount, "Unknow");
	pLog->m_nVersion = 2;

	in_addr addr;
	addr.s_addr = INADDR_ANY;
	strcpy(pLog->m_szIP, inet_ntoa(addr));

	CITP* itp = g_itpMgr.CITPMgr::GetITP(pItemInfo->ITID);
	if( itp != NULL )
	{
		if( pItemInfo->ServerItemType == INVENTORYITEMTYPE_EQUIPITEM )
		{
			pLog->m_dwItemSerialcode = static_cast<DWORD>(pItemInfo->UniqueSerialNum);
			pLog->m_equipSlotInfo.info[0] = pItemInfo->slot.info[0];
			pLog->m_equipSlotInfo.info[1] = pItemInfo->slot.info[1];
			pLog->m_equipSlotInfo.info[2] = pItemInfo->slot.info[2];
			pLog->m_equipSlotInfo.info[3] = pItemInfo->slot.info[3];
			pLog->m_nRefingLevel = pItemInfo->refiningLevel;
		}

		pLog->m_dwITID = pItemInfo->ITID;
		pLog->m_dwPrice = nPrice;
		pLog->m_dwItemCount = pItemInfo->count;
		strcpy(pLog->m_szItemName, itp->m_name);
		strcpy(pLog->m_szMapName, "");
		pLog->m_NP_bCashItem = itp->IsCashItem();
		pLog->m_NP_ItemSerialNum = pItemInfo->UniqueSerialNum;
		pLog->m_NP_ItemHireExpireDate = pItemInfo->HireExpireDate;
	}
	else
	{
		pLog->m_dwITID = 0;
		pLog->m_dwItemCount = 0;
		pLog->m_dwPrice = nPrice;
		strcpy(pLog->m_szItemName, "");
		strcpy(pLog->m_szMapName, "");
		pLog->m_NP_ItemSerialNum = 0;
		pLog->m_NP_ItemHireExpireDate = 0;
	}

	pLog->m_dwAuctionID = AuctionID;

	this->CDatabaseLog<SITEMLOG*>::AddLog(pLog);
}


void CItemLog::AddMailSendLog(unsigned long AuctionID, int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice) // 236-307 (180-249)
{
	if( pItemInfo->ITID == 0 && nPrice == 0 )
		return;

	SITEMLOG* pLog = new SITEMLOG;
	if( pLog == NULL )
		return;

	memset(pLog, 0, sizeof(*pLog));
	static int nServerID = g_serverInfo.CServerInfo::GetLocalServerID();

	pLog->m_nServerID = nServerID;
	pLog->m_ActionType = nType;
	pPC->GetParameterValue(VAR_CURXPOS, pLog->m_nEventPosX);
	pPC->GetParameterValue(VAR_CURYPOS, pLog->m_nEventPosY);
	ItemLog_SetUserInfo(&pLog->m_srcUserInfo, pPC);
	pLog->m_desUserInfo.m_nAccountID = DestAID;
	pLog->m_desUserInfo.m_dwCharID = DestGID;
	strcpy(pLog->m_desUserInfo.m_szCharName, DestName);
	strcpy(pLog->m_desUserInfo.m_szAccount, "Unknow");
	pLog->m_nVersion = 2;

	in_addr addr;
	addr.s_addr = pPC->m_ip;
	strcpy(pLog->m_szIP, inet_ntoa(addr));

	CITP* pItemMgrinfo = g_itpMgr.CITPMgr::GetITP(pItemInfo->ITID);
	if( pItemMgrinfo != NULL )
	{
		if( pItemInfo->ServerItemType == INVENTORYITEMTYPE_EQUIPITEM )
		{
			pLog->m_dwItemSerialcode = static_cast<DWORD>(pItemInfo->UniqueSerialNum);
			pLog->m_equipSlotInfo.info[0] = pItemInfo->slot.info[0];
			pLog->m_equipSlotInfo.info[1] = pItemInfo->slot.info[1];
			pLog->m_equipSlotInfo.info[2] = pItemInfo->slot.info[2];
			pLog->m_equipSlotInfo.info[3] = pItemInfo->slot.info[3];
			pLog->m_nRefingLevel = pItemInfo->refiningLevel;
		}

		pLog->m_dwITID = pItemInfo->ITID;
		pLog->m_dwPrice = nPrice;
		pLog->m_dwItemCount = pItemInfo->count;
		strcpy(pLog->m_szItemName, pItemMgrinfo->m_name);
		strcpy(pLog->m_szMapName, "");
		pLog->m_NP_bCashItem = pItemMgrinfo->IsCashItem();
		pLog->m_NP_ItemSerialNum = pItemInfo->UniqueSerialNum;
		pLog->m_NP_ItemHireExpireDate = pItemInfo->HireExpireDate;
	}
	else
	{
		pLog->m_dwITID = 0;
		pLog->m_dwItemCount = 0;
		pLog->m_dwPrice = nPrice;
		strcpy(pLog->m_szItemName, "");
		strcpy(pLog->m_szMapName, "");
		pLog->m_NP_ItemSerialNum = 0;
		pLog->m_NP_ItemHireExpireDate = 0;
	}

	strcpy(pLog->m_szMapName, pPC->m_characterInfo.mapName);
	pLog->m_dwAuctionID = AuctionID;
	this->CDatabaseLog<SITEMLOG*>::AddLog(pLog);
}


void CItemLog::AddMailReceiveLog(int nType, CPC* pPC, unsigned long DestAID, unsigned long DestGID, char* DestName, CommonItemInfo* pItemInfo, int nPrice) // 310-381 (252-321)
{
	SITEMLOG* pLog = new SITEMLOG;
	if( pLog == NULL )
		return;

	memset(pLog, 0, sizeof(*pLog));
	static int nServerID = g_serverInfo.CServerInfo::GetLocalServerID();

	pLog->m_nServerID = nServerID;
	pLog->m_ActionType = ITEMLOG_MAIL_RECEIVE;
	pPC->GetParameterValue(VAR_CURXPOS, pLog->m_nEventPosX);
	pPC->GetParameterValue(VAR_CURYPOS, pLog->m_nEventPosY);
	ItemLog_SetUserInfo(&pLog->m_srcUserInfo, pPC);
	pLog->m_desUserInfo.m_nAccountID = DestAID;
	pLog->m_desUserInfo.m_dwCharID = DestGID;
	strcpy(pLog->m_desUserInfo.m_szCharName, DestName);
	strcpy(pLog->m_desUserInfo.m_szAccount, "Unknow");
	pLog->m_nVersion = 2;

	in_addr addr;
	addr.s_addr = pPC->m_ip;
	strcpy(pLog->m_szIP, inet_ntoa(addr));

	CITP* piteminfo = g_itpMgr.CITPMgr::GetITP(pItemInfo->ITID);
	if( piteminfo != NULL )
	{
		if( pItemInfo->ServerItemType == INVENTORYITEMTYPE_EQUIPITEM )
		{
			pLog->m_dwItemSerialcode = static_cast<DWORD>(pItemInfo->UniqueSerialNum);
			pLog->m_equipSlotInfo.info[0] = pItemInfo->slot.info[0];
			pLog->m_equipSlotInfo.info[1] = pItemInfo->slot.info[1];
			pLog->m_equipSlotInfo.info[2] = pItemInfo->slot.info[2];
			pLog->m_equipSlotInfo.info[3] = pItemInfo->slot.info[3];
			pLog->m_nRefingLevel = pItemInfo->refiningLevel;
		}

		pLog->m_dwITID = piteminfo->m_ITID;
		pLog->m_dwPrice = nPrice;
		pLog->m_dwItemCount = pItemInfo->count;
		strcpy(pLog->m_szItemName, piteminfo->m_name);
		pLog->m_NP_bCashItem = piteminfo->IsCashItem();
		pLog->m_NP_ItemSerialNum = pItemInfo->UniqueSerialNum;
		pLog->m_NP_ItemHireExpireDate = pItemInfo->HireExpireDate;
	}
	else
	{
		pLog->m_dwITID = 0;
		pLog->m_dwItemCount = 0;
		pLog->m_dwPrice = nPrice;
		strcpy(pLog->m_szItemName, "");
		pLog->m_NP_ItemSerialNum = 0;
		pLog->m_NP_ItemHireExpireDate = 0;
	}

	strcpy(pLog->m_szMapName, pPC->m_characterInfo.mapName);

	this->CDatabaseLog<SITEMLOG*>::AddLog(pLog);
}


void CItemLog::AddItemLog(int nType, CPC* pPC, CCharacter* pDestChar, IVItItem* pIvitItem, int nPrice, int nCount, char* Tx_ID, const __int64 in_Identity)
{
	if( pIvitItem == NULL )
	{
		if( nPrice >= CGVar::GetObj()->CGVar::GetMIN_ZENY_ITEMLOG_EXECEXCHANGEITEM() )
			this->CItemLog::AddItemLogOnMoney(nType, pPC, pDestChar, nPrice, nCount, 0, in_Identity);

		return;
	}

	if( !g_importantItem.CImportantItem::IsImportantItem(pIvitItem->InventoryItem::GetID()) )
		return;

	CITP* piteminfo = g_itpMgr.CITPMgr::GetITP(pIvitItem->InventoryItem::GetID());
	if( piteminfo == NULL )
		return;

	if( this->CDatabaseLog<SITEMLOG*>::GetSize() >= KEEP_OBJECT_MAXCNT )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "ItemLog Cnt Over(%d / %d) ITID(%d)", this->CDatabaseLog<SITEMLOG*>::GetSize(), KEEP_OBJECT_MAXCNT, pIvitItem->InventoryItem::GetID());
		return;
	}

	SITEMLOG* pLog = new(std::nothrow) SITEMLOG;
	if( pLog == NULL )
		return;

	memset(pLog, 0, sizeof(*pLog));
	static int nServerID = g_serverInfo.CServerInfo::GetLocalServerID();

	pLog->m_nServerID = nServerID;
	pLog->m_Identity = in_Identity;
	pLog->m_ActionType = nType;
	pPC->GetParameterValue(VAR_CURXPOS, pLog->m_nEventPosX);
	pPC->GetParameterValue(VAR_CURYPOS, pLog->m_nEventPosY);
	ItemLog_SetUserInfo(&pLog->m_srcUserInfo, pPC);
	if( pDestChar != NULL )
		ItemLog_SetUserInfo(&pLog->m_desUserInfo, pDestChar);
	pLog->m_nVersion = 2;

	in_addr addr;
	addr.s_addr = pPC->m_ip;
	strcpy(pLog->m_szIP, inet_ntoa(addr));

	if( pIvitItem->GetType() == INVENTORYITEMTYPE_EQUIPITEM )
	{
		IVItEquipItem* pIvitEquipItem = static_cast<IVItEquipItem*>(pIvitItem);
		pLog->m_dwItemSerialcode = static_cast<DWORD>(pIvitItem->IVItItem::GetUniqueIdentityNumV2());
		pLog->m_equipSlotInfo.info[0] = pIvitItem->m_slotInfo.info[0];
		pLog->m_equipSlotInfo.info[1] = pIvitItem->m_slotInfo.info[1];
		pLog->m_equipSlotInfo.info[2] = pIvitItem->m_slotInfo.info[2];
		pLog->m_equipSlotInfo.info[3] = pIvitItem->m_slotInfo.info[3];
		pLog->m_nRefingLevel = pIvitEquipItem->IVItEquipItem::GetRefiningLevel();
	}

	pLog->m_dwITID = piteminfo->m_ITID;
	pLog->m_dwPrice = nPrice;
	pLog->m_dwItemCount = nCount;
	strcpy(pLog->m_szItemName, piteminfo->m_name);
	strcpy(pLog->m_szMapName, pPC->m_characterInfo.mapName);
	pLog->m_NP_ItemSerialNum = pIvitItem->IVItItem::GetUniqueIdentityNumV2();
	pLog->m_NP_ItemHireExpireDate = pIvitItem->IVItItem::GetHireExpireDate();
	pLog->m_NP_bCashItem = piteminfo->IsCashItem();
	pPC->GetParameterValue(VAR_MONEY, *(int*)&pLog->m_dwRemainZeny);
	if( pDestChar != NULL )
		pDestChar->GetParameterValue(VAR_MONEY, *(int*)&pLog->m_dwDestRemainZeny);
	else
		pLog->m_dwDestRemainZeny = -1;

	this->CDatabaseLog<SITEMLOG*>::AddLog(pLog);
}


void CItemLog::AddCITPLog(int nType, CPC* pPC, CPC* pDestPC, CITP* piteminfo, int nPrice, int nCount)
{
	SITEMLOG* pLog = new SITEMLOG;
	if( pLog == NULL )
		return;

	memset(pLog, 0, sizeof(*pLog));
	static int nServerID = g_serverInfo.CServerInfo::GetLocalServerID();

	pLog->m_nServerID = nServerID;
	pLog->m_ActionType = nType;
	pPC->GetParameterValue(VAR_CURXPOS, pLog->m_nEventPosX);
	pPC->GetParameterValue(VAR_CURYPOS, pLog->m_nEventPosY);
	ItemLog_SetUserInfo(&pLog->m_srcUserInfo, pPC);
	if( pDestPC != NULL )
		ItemLog_SetUserInfo(&pLog->m_desUserInfo, pDestPC);
	pLog->m_nVersion = 2;

	in_addr addr;
	addr.s_addr = pPC->m_ip;
	strcpy(pLog->m_szIP, inet_ntoa(addr));

	if( piteminfo == NULL )
		return;

	pLog->m_dwITID = piteminfo->m_ITID;
	pLog->m_dwPrice = nPrice;
	pLog->m_dwItemCount = nCount;
	strcpy(pLog->m_szItemName, piteminfo->m_name);
	strcpy(pLog->m_szMapName, pPC->m_characterInfo.mapName);
	pLog->m_NP_bCashItem = piteminfo->IsCashItem();

	this->CDatabaseLog<SITEMLOG*>::AddLog(pLog);
}


BOOL CItemLog::SaveToDatabase(SQLHSTMT hStmt, SITEMLOG* pLog)
{
	return this->CItemLog::SaveToDatabaseV2(hStmt, pLog);
}


BOOL CItemLog::SaveToDatabaseV1(SQLHSTMT hStmt, SITEMLOG* pLog)
{
	if( pLog == NULL )
		return TRUE;

	BOOL ret = this->CExtendedODBC::Query(hStmt, "{call AddItemLog(%d, %d, %d, %s, %d, %d, %d, %s, %d, %s, %d, %s, %d, %s, %d, %s, %d, %d, %s, %d, %d, %d, %d, %d, %d, %d)}");
	delete pLog;

	return ret;
}


BOOL CItemLog::SaveToDatabaseV2(const SQLHSTMT in_hStmt, SITEMLOG* pLog)
{
	if( pLog == NULL )
		return TRUE;

	SQLINTEGER cbChar = SQL_NTS;

	SQLBindParameter(in_hStmt,  1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_nVersion, 0, 0);
	SQLBindParameter(in_hStmt,  2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_nServerID, 0, 0);
	SQLBindParameter(in_hStmt,  3, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_ActionType, 0, 0);
	SQLBindParameter(in_hStmt,  4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, max(1,strlen(pLog->m_szIP)), 0, pLog->m_szIP, 0, &cbChar);
	SQLBindParameter(in_hStmt,  5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, max(1,strlen(pLog->m_szMapName)), 0, pLog->m_szMapName, 0, &cbChar);
	SQLBindParameter(in_hStmt,  6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_nEventPosX, 0, 0);
	SQLBindParameter(in_hStmt,  7, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_nEventPosY, 0, 0);
	SQLBindParameter(in_hStmt,  8, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_srcUserInfo, 0, 0);
	SQLBindParameter(in_hStmt,  9, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, max(1,strlen(pLog->m_srcUserInfo.m_szAccount)), 0, pLog->m_srcUserInfo.m_szAccount, 0, &cbChar);
	SQLBindParameter(in_hStmt, 10, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_srcUserInfo.m_dwCharID, 0, 0);
	SQLBindParameter(in_hStmt, 11, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, max(1,strlen(pLog->m_srcUserInfo.m_szCharName)), 0, pLog->m_srcUserInfo.m_szCharName, 0, &cbChar);
	SQLBindParameter(in_hStmt, 12, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_desUserInfo, 0, 0);
	SQLBindParameter(in_hStmt, 13, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, max(1,strlen(pLog->m_desUserInfo.m_szAccount)), 0, pLog->m_desUserInfo.m_szAccount, 0, &cbChar);
	SQLBindParameter(in_hStmt, 14, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_desUserInfo.m_dwCharID, 0, 0);
	SQLBindParameter(in_hStmt, 15, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, max(1,strlen(pLog->m_desUserInfo.m_szCharName)), 0, pLog->m_desUserInfo.m_szCharName, 0, &cbChar);
	SQLBindParameter(in_hStmt, 16, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_dwITID, 0, 0);
	SQLBindParameter(in_hStmt, 17, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, max(1,strlen(pLog->m_szItemName)), 0, pLog->m_szItemName, 0, &cbChar);
	SQLBindParameter(in_hStmt, 18, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_NP_bCashItem, 0, 0);
	SQLBindParameter(in_hStmt, 19, SQL_PARAM_INPUT, SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &pLog->m_NP_ItemSerialNum, 0, 0);
	SQLBindParameter(in_hStmt, 20, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_dwItemCount, 0, 0);
	SQLBindParameter(in_hStmt, 21, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_dwPrice, 0, 0);
	int Slot1 = pLog->m_equipSlotInfo.info[0];
	int Slot2 = pLog->m_equipSlotInfo.info[1];
	int Slot3 = pLog->m_equipSlotInfo.info[2];
	int Slot4 = pLog->m_equipSlotInfo.info[3];
	SQLBindParameter(in_hStmt, 22, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &Slot1, 0, 0);
	SQLBindParameter(in_hStmt, 23, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &Slot2, 0, 0);
	SQLBindParameter(in_hStmt, 24, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &Slot3, 0, 0);
	SQLBindParameter(in_hStmt, 25, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &Slot4, 0, 0);
	SQLBindParameter(in_hStmt, 26, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_nRefingLevel, 0, 0);
	TIMESTAMP_STRUCT ItemHireExpireDate = CDateTime(pLog->m_NP_ItemHireExpireDate);
	SQLINTEGER cbDateTime = sizeof(ItemHireExpireDate);
	SQLBindParameter(in_hStmt, 27, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 22, 0, &ItemHireExpireDate, sizeof(ItemHireExpireDate), &cbDateTime);
	SQLBindParameter(in_hStmt, 28, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_dwAuctionID, 0, 0);
	SQLBindParameter(in_hStmt, 29, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_dwRemainZeny, 0, 0);
	SQLBindParameter(in_hStmt, 30, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &pLog->m_dwDestRemainZeny, 0, 0);
	int NotUsebizType = 0;
	SQLBindParameter(in_hStmt, 31, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &NotUsebizType, 0, 0);

	BOOL bRet = TRUE;

	if( !SQL_SUCCEEDED(SQLExecDirectA(in_hStmt, (SQLCHAR*)"{call usp_add_itemlog_zeny_2(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)}", SQL_NTS)) )
	{
		char szSQLError[256] = {};
		this->CExtendedODBC::GetErrorString(in_hStmt, szSQLError);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s %s", __FUNCTION__, szSQLError);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", "{call usp_add_itemlog_zeny_2(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)}");

		char szError[256] = {};
		_snprintf(szError, countof(szError), "CDatabase::Query() - SQLExecDirect() Fail!(%s)", szSQLError);
		MessageBoxA(NULL, szError, "", MB_OK);

		bRet = FALSE;
	}

	delete pLog;
	return bRet;
}
