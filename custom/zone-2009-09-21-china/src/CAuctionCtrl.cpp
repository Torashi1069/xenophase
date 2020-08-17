#include "Custom/Settings.h"
#include "CAuctionCtrl.hpp"
#include "ItemLog.h"
#include "PC.h"


CAuctionCtrl::CAuctionCtrl(void)
{
	m_EndChkItemType = 0;
	m_lastTime = timeGetTime() + 600000;
	m_DateTime.CDateTime::GetNowTime();
}


CAuctionCtrl::~CAuctionCtrl(void)
{
}


/// @patch auction item pool memory usage reduction - r2562
hook_method<void (CAuctionCtrl::*)(unsigned int ZoneServerID, const char* DSN, const char* UID, const char* PASS, const char* DB, char type)> CAuctionCtrl::_Init(SERVER, "CAuctionCtrl::Init");
HOOKED void CAuctionCtrl::Init(unsigned int ZoneServerID, const char* DSN, const char* UID, const char* PASS, const char* DB, char type)
{
//	return (this->*_Init)(ZoneServerID, DSN, UID, PASS, DB, type);

	m_ZoneServerID = ZoneServerID;
	m_AuctionDB.CODBC::Init(DSN, UID, PASS, DB, type);

	m_ArmorPool.CMemoryMgr<AUCTIONINFO>::Init(CSettings::GetObj()->auction_pool_size);
	m_WeaponPool.CMemoryMgr<AUCTIONINFO>::Init(CSettings::GetObj()->auction_pool_size);
	m_CardPool.CMemoryMgr<AUCTIONINFO>::Init(CSettings::GetObj()->auction_pool_size);
	m_EtcPool.CMemoryMgr<AUCTIONINFO>::Init(CSettings::GetObj()->auction_pool_size);

	m_ArmorItem.clear();
	m_WeaponItem.clear();
	m_CardItem.clear();
	m_EtcItem.clear();

	m_AuctionDB.CAuctionDB::GetAuction(m_ZoneServerID, TYPE_AUCTION_ARMOR, &m_ArmorPool, m_ArmorItem);
	this->CAuctionCtrl::ItemParser(TYPE_AUCTION_ARMOR);
	m_AuctionDB.CAuctionDB::GetAuction(m_ZoneServerID, TYPE_AUCTION_WEAPON, &m_WeaponPool, m_WeaponItem);
	this->CAuctionCtrl::ItemParser(TYPE_AUCTION_WEAPON);
	m_AuctionDB.CAuctionDB::GetAuction(m_ZoneServerID, TYPE_AUCTION_CARD, &m_CardPool, m_CardItem);
	this->CAuctionCtrl::ItemParser(TYPE_AUCTION_CARD);
	m_AuctionDB.CAuctionDB::GetAuction(m_ZoneServerID, TYPE_AUCTION_ETC, &m_EtcPool, m_EtcItem);
	this->CAuctionCtrl::ItemParser(TYPE_AUCTION_ETC);
}


hook_method<void (CAuctionCtrl::*)(void)> CAuctionCtrl::_Process(SERVER, "CAuctionCtrl::Process");
void CAuctionCtrl::Process(void)
{
	return (this->*_Process)();

	//TODO
}


hook_method<int (CAuctionCtrl::*)(CPC* pPC, unsigned long NowPrice, unsigned long MaxPrice, int Hour, CommonItemInfo* pCommonItemInfo, char* pItemBuffer, int ItemLen)> CAuctionCtrl::_AddAuction(SERVER, "CAuctionCtrl::AddAuction");
int CAuctionCtrl::AddAuction(CPC* pPC, unsigned long NowPrice, unsigned long MaxPrice, int Hour, CommonItemInfo* pCommonItemInfo, char* pItemBuffer, int ItemLen)
{
	return (this->*_AddAuction)(pPC, NowPrice, MaxPrice, Hour, pCommonItemInfo, pItemBuffer, ItemLen);

	AUCTIONINFO* info;
	switch( this->CAuctionCtrl::GetAuctionType(pCommonItemInfo->ITID) )
	{
	case TYPE_AUCTION_ARMOR : info = m_ArmorPool.CMemoryMgr<AUCTIONINFO>::Alloc(); break;
	case TYPE_AUCTION_WEAPON: info = m_WeaponPool.CMemoryMgr<AUCTIONINFO>::Alloc(); break;
	case TYPE_AUCTION_CARD  : info = m_CardPool.CMemoryMgr<AUCTIONINFO>::Alloc(); break;
	case TYPE_AUCTION_ETC   : info = m_EtcPool.CMemoryMgr<AUCTIONINFO>::Alloc(); break;
	default:
		return 0;
	}

	if( info == NULL )
		return 0;

	info->isBuyer = 0;
	info->AuctionID = 0;
	info->AID = pPC->GetAccountID();
	info->GID = pPC->CPC::GetCharacterID();
	memcpy(info->SellerName, pPC->m_characterInfo.characterName, sizeof(info->BuyerName));
	info->BuyerAID = 0;
	info->BuyerGID = 0;
	memset(info->BuyerName, 0, sizeof(info->BuyerName));
	info->MaxPrice = MaxPrice;
	info->NowPrice = NowPrice;

	CDateTime DateTime;
	DateTime.CDateTime::GetNowTime();
	DateTime.CDateTime::AddTime(0, Hour + 1, 0);
	DateTime.CDateTime::GetTime(info->EndTime.Year, info->EndTime.Month, info->EndTime.Day, info->EndTime.Hour);

	memcpy(info->Item, pItemBuffer, sizeof(info->Item));
	info->ItemLen = ItemLen;
	info->ITID = pCommonItemInfo->ITID;
	info->ItemType = pCommonItemInfo->Type;
	info->AuctionType = this->CAuctionCtrl::GetAuctionType(pCommonItemInfo->ITID);
	info->count = pCommonItemInfo->count;
	info->IsIdentified = pCommonItemInfo->IsIdentified;

	if( pCommonItemInfo->ServerItemType == 3 )
	{
		info->IsDamaged = pCommonItemInfo->IsDamaged;
		info->refiningLevel = pCommonItemInfo->refiningLevel;
		memcpy(info->slot.info, pCommonItemInfo->slot.info, sizeof(info->slot.info));
	}
	else
	{
		info->IsDamaged = 0;
		info->refiningLevel = 0;
		memcpy(info->slot.info, pCommonItemInfo->slot.info, sizeof(info->slot.info));
	}

	if( m_AuctionDB.CAuctionDB::AddAuction(m_ZoneServerID, info) == 0 )
	{
		switch( this->CAuctionCtrl::GetAuctionType(pCommonItemInfo->ITID) )
		{
		case TYPE_AUCTION_ARMOR : m_ArmorPool.CMemoryMgr<AUCTIONINFO>::Free(info); break;
		case TYPE_AUCTION_WEAPON: m_WeaponPool.CMemoryMgr<AUCTIONINFO>::Free(info); break;
		case TYPE_AUCTION_CARD  : m_CardPool.CMemoryMgr<AUCTIONINFO>::Free(info); break;
		case TYPE_AUCTION_ETC   : m_EtcPool.CMemoryMgr<AUCTIONINFO>::Free(info); break;
		default:
			return 0;
		}

		return 0;
	}

	switch( info->AuctionType )
	{
	case TYPE_AUCTION_ARMOR : m_ArmorItem[info->AuctionID] = info; break;
	case TYPE_AUCTION_WEAPON: m_WeaponItem[info->AuctionID] = info; break;
	case TYPE_AUCTION_CARD  : m_CardItem[info->AuctionID] = info; break;
	case TYPE_AUCTION_ETC   : m_EtcItem[info->AuctionID] = info; break;
	default:
		return 0;
	}

	CommonItemInfo ItemInfo;
	CPCItemInventoryMgr::DBValueParser(&ItemInfo, info->Item, ItemLen);
	g_itemLog->CItemLog::AddMailSendLog(info->AuctionID, 29, pPC, 0, 0, "", &ItemInfo, 12000 * Hour);
		
	return 1;
}


hook_method<int (CAuctionCtrl::*)(unsigned long AuctionID, int ItemType)> CAuctionCtrl::_DeleteAuction(SERVER, "CAuctionCtrl::DeleteAuction");
int CAuctionCtrl::DeleteAuction(unsigned long AuctionID, int ItemType)
{
	return (this->*_DeleteAuction)(AuctionID, ItemType);

	//TODO
}


hook_method<int (CAuctionCtrl::*)(CPC* pBuyerPc, unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice)> CAuctionCtrl::_ChangeBuyerAuction(SERVER, "CAuctionCtrl::ChangeBuyerAuction");
int CAuctionCtrl::ChangeBuyerAuction(CPC* pBuyerPc, unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice)
{
	return (this->*_ChangeBuyerAuction)(pBuyerPc, AuctionID, BuyAID, BuyGID, BuyName, NowPrice);

	//TODO
}


hook_method<void (CAuctionCtrl::*)(unsigned long AccountID, int ItemType, int Page)> CAuctionCtrl::_FindItem(SERVER, "CAuctionCtrl::FindItem");
void CAuctionCtrl::FindItem(unsigned long AccountID, int ItemType, int Page)
{
	return (this->*_FindItem)(AccountID, ItemType, Page);

	//TODO
}


hook_method<void (CAuctionCtrl::*)(unsigned long AccountID, unsigned long AuctionID)> CAuctionCtrl::_FindItemAuctionID(SERVER, "CAuctionCtrl::FindItemAuctionID");
void CAuctionCtrl::FindItemAuctionID(unsigned long AccountID, unsigned long AuctionID)
{
	return (this->*_FindItemAuctionID)(AccountID, AuctionID);

	//TODO
}


hook_method<void (CAuctionCtrl::*)(unsigned long AccountID, char* ItemName, int Page)> CAuctionCtrl::_FindItemName(SERVER, "CAuctionCtrl::FindItemName");
void CAuctionCtrl::FindItemName(unsigned long AccountID, char* ItemName, int Page)
{
	return (this->*_FindItemName)(AccountID, ItemName, Page);

	//TODO
}


hook_method<int (CAuctionCtrl::*)(unsigned long AuctionID, unsigned long SellerAID, unsigned long SellerGID)> CAuctionCtrl::_AuctionAddCancel(SERVER, "CAuctionCtrl::AuctionAddCancel");
int CAuctionCtrl::AuctionAddCancel(unsigned long AuctionID, unsigned long SellerAID, unsigned long SellerGID)
{
	return (this->*_AuctionAddCancel)(AuctionID, SellerAID, SellerGID);

	//TODO
}


hook_method<int (CAuctionCtrl::*)(int Type, unsigned long AID, unsigned long GID)> CAuctionCtrl::_ReqMyInfo(SERVER, "CAuctionCtrl::ReqMyInfo");
int CAuctionCtrl::ReqMyInfo(int Type, unsigned long AID, unsigned long GID)
{
	return (this->*_ReqMyInfo)(Type, AID, GID);

	//TODO
}


hook_method<int (CAuctionCtrl::*)(unsigned long AuctionID, unsigned long AID, unsigned long GID)> CAuctionCtrl::_MySellStop(SERVER, "CAuctionCtrl::MySellStop");
int CAuctionCtrl::MySellStop(unsigned long AuctionID, unsigned long AID, unsigned long GID)
{
	return (this->*_MySellStop)(AuctionID, AID, GID);

	//TODO
}


hook_method<int (CAuctionCtrl::*)(unsigned long AID, unsigned long GID)> CAuctionCtrl::_GetCountSellItem(SERVER, "CAuctionCtrl::GetCountSellItem");
int CAuctionCtrl::GetCountSellItem(unsigned long AID, unsigned long GID)
{
	return (this->*_GetCountSellItem)(AID, GID);

	//TODO
}


hook_method<int (CAuctionCtrl::*)(unsigned long AID, unsigned long GID)> CAuctionCtrl::_GetCountBuyItem(SERVER, "CAuctionCtrl::GetCountBuyItem");
int CAuctionCtrl::GetCountBuyItem(unsigned long AID, unsigned long GID)
{
	return (this->*_GetCountBuyItem)(AID, GID);

	//TODO
}


hook_method<int (CAuctionCtrl::*)(AUCTIONINFO* pAuctionInfo)> CAuctionCtrl::_SendMailAuctionEnd(SERVER, "CAuctionCtrl::SendMailAuctionEnd");
int CAuctionCtrl::SendMailAuctionEnd(AUCTIONINFO* pAuctionInfo)
{
	return (this->*_SendMailAuctionEnd)(pAuctionInfo);

	//TODO
}


hook_method<int (CAuctionCtrl::*)(AUCTIONINFO* pAuctionInfo)> CAuctionCtrl::_SendMailAuctionCanle(SERVER, "CAuctionCtrl::SendMailAuctionCanle");
int CAuctionCtrl::SendMailAuctionCanle(AUCTIONINFO* pAuctionInfo)
{
	return (this->*_SendMailAuctionCanle)(pAuctionInfo);

	//TODO
}


hook_method<int (CAuctionCtrl::*)(AUCTIONINFO* pAuctionInfo, unsigned long AuctionID)> CAuctionCtrl::_SendBuyerAuctionCancel(SERVER, "CAuctionCtrl::SendBuyerAuctionCancel");
int CAuctionCtrl::SendBuyerAuctionCancel(AUCTIONINFO* pAuctionInfo, unsigned long AuctionID)
{
	return (this->*_SendBuyerAuctionCancel)(pAuctionInfo, AuctionID);

	//TODO
}


hook_method<void (CAuctionCtrl::*)(int ItemType)> CAuctionCtrl::_TimeOver(SERVER, "CAuctionCtrl::TimeOver");
void CAuctionCtrl::TimeOver(int ItemType)
{
	return (this->*_TimeOver)(ItemType);

	//TODO
}


hook_method<AUCTIONINFO* (CAuctionCtrl::*)(unsigned long AuctionID)> CAuctionCtrl::_GetAuctionInfo(SERVER, "CAuctionCtrl::GetAuctionInfo");
AUCTIONINFO* CAuctionCtrl::GetAuctionInfo(unsigned long AuctionID)
{
	return (this->*_GetAuctionInfo)(AuctionID);

	//TODO
}


hook_method<void (CAuctionCtrl::*)(int PaserType)> CAuctionCtrl::_ItemParser(SERVER, "CAuctionCtrl::ItemParser");
void CAuctionCtrl::ItemParser(int PaserType)
{
	return (this->*_ItemParser)(PaserType);

	//TODO
}


hook_method<int (CAuctionCtrl::*)(int ITID)> CAuctionCtrl::_GetAuctionType(SERVER, "CAuctionCtrl::GetAuctionType");
int CAuctionCtrl::GetAuctionType(int ITID)
{
	return (this->*_GetAuctionType)(ITID);

	//TODO
}


hook_method<void (CAuctionCtrl::*)(unsigned long AID, int ItemCounter, int MaxCounter, char* Buffer, int BufferSize)> CAuctionCtrl::_SendAuctionInfo(SERVER, "CAuctionCtrl::SendAuctionInfo");
void CAuctionCtrl::SendAuctionInfo(unsigned long AID, int ItemCounter, int MaxCounter, char* Buffer, int BufferSize)
{
	return (this->*_SendAuctionInfo)(AID, ItemCounter, MaxCounter, Buffer, BufferSize);

	//TODO
}


hook_method<void (CAuctionCtrl::*)(int ITID, char* ItemName)> CAuctionCtrl::_GetClientItemName(SERVER, "CAuctionCtrl::GetClientItemName");
void CAuctionCtrl::GetClientItemName(int ITID, char* ItemName)
{
	return (this->*_GetClientItemName)(ITID, ItemName);

	//TODO
}
