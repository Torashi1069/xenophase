#include "CAuctionCtrl.h"
#include "CharacterMgr.h"
#include "ItemLog.h"
#include "ITPMgr.h"
#include "PCItemInventoryMgr.h"
#include "ZoneProcess.h"
#include "Common/Packet.h"
#include "shared/NCriticalErrorLog.h"


CAuctionCtrl::CAuctionCtrl()
{
	m_EndChkItemType = TYPE_AUCTION_ARMOR;
	m_lastTime = timeGetTime() + 600000;
	m_DateTime.CDateTime::GetNowTime();
}


CAuctionCtrl::~CAuctionCtrl()
{
	m_ArmorPool.CMemoryMgr<AUCTIONINFO>::Reset();
}


void CAuctionCtrl::Init(unsigned long ZoneServerID, const char* FileDSN, const char* PASS)
{
	m_AuctionDB.CODBC::Init(FileDSN, PASS);
	m_ZoneServerID = ZoneServerID;

	m_ArmorPool.CMemoryMgr<AUCTIONINFO>::Init(50000);
	m_WeaponPool.CMemoryMgr<AUCTIONINFO>::Init(50000);
	m_CardPool.CMemoryMgr<AUCTIONINFO>::Init(50000);
	m_EtcPool.CMemoryMgr<AUCTIONINFO>::Init(50000);
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


void CAuctionCtrl::ItemParser(int PaserType)
{
	std::map<unsigned long,AUCTIONINFO*>::iterator Beginiter;
	std::map<unsigned long,AUCTIONINFO*>::iterator Enditer;
	switch( PaserType )
	{
	case TYPE_AUCTION_ARMOR:
		Beginiter = m_ArmorItem.begin();
		Enditer = m_ArmorItem.end();
	break;
	case TYPE_AUCTION_WEAPON:
		Beginiter = m_WeaponItem.begin();
		Enditer = m_WeaponItem.end();
	break;
	case TYPE_AUCTION_CARD:
		Beginiter = m_CardItem.begin();
		Enditer = m_CardItem.end();
	break;
	case TYPE_AUCTION_ETC:
		Beginiter = m_EtcItem.begin();
		Enditer = m_EtcItem.end();
	break;
	default:
		return;
	break;
	};

	for( std::map<unsigned long,AUCTIONINFO*>::iterator iter = Beginiter; iter != Enditer; ++iter )
	{
		AUCTIONINFO* pAuctionInfo = iter->second;

		if( strlen(pAuctionInfo->BuyerName) >= 4 && pAuctionInfo->BuyerAID != 0 && pAuctionInfo->BuyerGID != 0 )
			pAuctionInfo->isBuyer = TRUE;

		CommonItemInfo CommonInfo;
		if( CPCItemInventoryMgr::DBValueParser(&CommonInfo, pAuctionInfo->Item, pAuctionInfo->ItemLen) != TRUE )
			continue; // error

		pAuctionInfo->ItemType = CommonInfo.Type;
		pAuctionInfo->ITID = CommonInfo.ITID;
		pAuctionInfo->count = CommonInfo.count;
		pAuctionInfo->IsIdentified = CommonInfo.IsIdentified;
		pAuctionInfo->IsDamaged = CommonInfo.IsIdentified;
		pAuctionInfo->refiningLevel = CommonInfo.refiningLevel;
		pAuctionInfo->slot = CommonInfo.slot;
	}
}


void CAuctionCtrl::Process()
{
	DWORD CurTM = timeGetTime();
	m_DateTime.CDateTime::GetNowTime();

	if( CurTM < m_lastTime )
		return;
	m_lastTime = CurTM + 300000;

	this->CAuctionCtrl::TimeOver(m_EndChkItemType);

	if( m_EndChkItemType == TYPE_AUCTION_ARMOR )
		m_EndChkItemType = TYPE_AUCTION_WEAPON;
	else
	if( m_EndChkItemType == TYPE_AUCTION_WEAPON )
		m_EndChkItemType = TYPE_AUCTION_CARD;
	else
	if( m_EndChkItemType == TYPE_AUCTION_CARD )
		m_EndChkItemType = TYPE_AUCTION_ETC;
	else
	{//(m_EndChkItemType == TYPE_AUCTION_ETC )
		m_EndChkItemType = TYPE_AUCTION_ARMOR;
	}
}


BOOL CAuctionCtrl::AddAuction(CPC* pPC, unsigned long NowPrice, unsigned long MaxPrice, int Hour, CommonItemInfo* pCommonItemInfo, char* pItemBuffer, int ItemLen)
{
	AUCTIONINFO* pAuctionInfo;
	switch( this->CAuctionCtrl::GetAuctionType(pCommonItemInfo->ITID) )
	{
	case TYPE_AUCTION_ARMOR:  pAuctionInfo = m_ArmorPool.CMemoryMgr<AUCTIONINFO>::Alloc();  break;
	case TYPE_AUCTION_WEAPON: pAuctionInfo = m_WeaponPool.CMemoryMgr<AUCTIONINFO>::Alloc(); break;
	case TYPE_AUCTION_CARD:   pAuctionInfo = m_CardPool.CMemoryMgr<AUCTIONINFO>::Alloc();   break;
	case TYPE_AUCTION_ETC:    pAuctionInfo = m_EtcPool.CMemoryMgr<AUCTIONINFO>::Alloc();    break;
	default:
		return FALSE;
	};
	if( pAuctionInfo == NULL )
		return FALSE;

	pAuctionInfo->isBuyer = FALSE;
	pAuctionInfo->AuctionID = 0;
	pAuctionInfo->AID = pPC->GetAccountID();
	pAuctionInfo->GID = pPC->CPC::GetCharacterID();
	memcpy_s(pAuctionInfo->SellerName, sizeof(pAuctionInfo->SellerName), pPC->m_characterInfo.characterName, sizeof(pPC->m_characterInfo.characterName));
	pAuctionInfo->BuyerAID = 0;
	pAuctionInfo->BuyerGID = 0;
	memset(pAuctionInfo->BuyerName, '\0', sizeof(pAuctionInfo->BuyerName));
	pAuctionInfo->NowPrice = NowPrice;
	pAuctionInfo->MaxPrice = MaxPrice;

	CDateTime DateTime;
	DateTime.CDateTime::GetNowTime();
	DateTime.CDateTime::AddTime(0, Hour + 1, 0);
	DateTime.CDateTime::GetTime(pAuctionInfo->EndTime.Year, pAuctionInfo->EndTime.Month, pAuctionInfo->EndTime.Day, pAuctionInfo->EndTime.Hour);

	memcpy_s(pAuctionInfo->Item, sizeof(pAuctionInfo->Item), pItemBuffer, 40);
	pAuctionInfo->ItemLen = ItemLen;
	pAuctionInfo->ITID = pCommonItemInfo->ITID;
	pAuctionInfo->ItemType = pCommonItemInfo->Type;
	pAuctionInfo->AuctionType = this->CAuctionCtrl::GetAuctionType(pCommonItemInfo->ITID);
	pAuctionInfo->count = pCommonItemInfo->count;
	pAuctionInfo->IsIdentified = pCommonItemInfo->IsIdentified;
	if( pCommonItemInfo->ServerItemType == INVENTORYITEMTYPE_EQUIPITEM )
	{
		pAuctionInfo->IsDamaged = pCommonItemInfo->IsDamaged;
		pAuctionInfo->refiningLevel = pCommonItemInfo->refiningLevel;
	}
	else
	{
		pAuctionInfo->IsDamaged = false;
		pAuctionInfo->refiningLevel = 0;
	}
	memcpy_s(&pAuctionInfo->slot, sizeof(pAuctionInfo->slot), &pCommonItemInfo->slot, sizeof(pCommonItemInfo->slot));

	if( !m_AuctionDB.CAuctionDB::AddAuction(m_ZoneServerID, pAuctionInfo) )
	{
		switch( this->CAuctionCtrl::GetAuctionType(pCommonItemInfo->ITID) )
		{
		case TYPE_AUCTION_ARMOR:  m_ArmorPool.CMemoryMgr<AUCTIONINFO>::Free(pAuctionInfo);  break;
		case TYPE_AUCTION_WEAPON: m_WeaponPool.CMemoryMgr<AUCTIONINFO>::Free(pAuctionInfo); break;
		case TYPE_AUCTION_CARD:   m_CardPool.CMemoryMgr<AUCTIONINFO>::Free(pAuctionInfo);   break;
		case TYPE_AUCTION_ETC:    m_EtcPool.CMemoryMgr<AUCTIONINFO>::Free(pAuctionInfo);    break;
		default:
			return FALSE;
		};

		return FALSE;
	}

	switch( pAuctionInfo->AuctionType )
	{
	case TYPE_AUCTION_ARMOR:  m_ArmorItem[pAuctionInfo->AuctionID] = pAuctionInfo;  break;
	case TYPE_AUCTION_WEAPON: m_WeaponItem[pAuctionInfo->AuctionID] = pAuctionInfo; break;
	case TYPE_AUCTION_CARD:   m_CardItem[pAuctionInfo->AuctionID] = pAuctionInfo;   break;
	case TYPE_AUCTION_ETC:    m_EtcItem[pAuctionInfo->AuctionID] = pAuctionInfo;    break;
	default:
		return FALSE;
	};

	CommonItemInfo ItemInfo;
	CPCItemInventoryMgr::DBValueParser(&ItemInfo, pAuctionInfo->Item, ItemLen);
	g_itemLog.CItemLog::AddMailSendLog(pAuctionInfo->AuctionID, ITEMLOG_AUCTION_START, pPC, 0, 0, "", &ItemInfo, 12000 * Hour);

	return TRUE;
}


BOOL CAuctionCtrl::DeleteAuction(unsigned long AuctionID, int ItemType)
{
	if( !m_AuctionDB.CAuctionDB::DeleteAuction(AuctionID) )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "DeleteAuction DB  %d", AuctionID);

	std::map<unsigned long,AUCTIONINFO*>::iterator iter;

	switch( ItemType )
	{
	case TYPE_AUCTION_ARMOR:
		iter = m_ArmorItem.find(AuctionID);
		if( iter != m_ArmorItem.end() )
			m_ArmorItem.erase(iter);
	break;
	case TYPE_AUCTION_WEAPON:
		iter = m_WeaponItem.find(AuctionID);
		if( iter != m_WeaponItem.end() )
			m_WeaponItem.erase(iter);
	break;
	case TYPE_AUCTION_CARD:
		iter = m_CardItem.find(AuctionID);
		if( iter != m_CardItem.end() )
			m_CardItem.erase(iter);
	break;
	case TYPE_AUCTION_ETC:
		iter = m_EtcItem.find(AuctionID);
		if( iter != m_EtcItem.end() )
			m_EtcItem.erase(iter);
	break;
	};

	return TRUE;
}


BOOL CAuctionCtrl::ChangeBuyerAuction(CPC* pBuyerPc, unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice)
{
	AUCTIONINFO* pAuctionInfo = this->CAuctionCtrl::GetAuctionInfo(AuctionID);
	if( pAuctionInfo == NULL )
		return FALSE;

	if( (unsigned long)NowPrice <= pAuctionInfo->NowPrice )
	{
		if( NowPrice != pAuctionInfo->NowPrice || pAuctionInfo->isBuyer )
			return FALSE;
	}
	else
	{
		if( pAuctionInfo->MaxPrice != 0 && (unsigned long)NowPrice > pAuctionInfo->MaxPrice )
			NowPrice = (int)pAuctionInfo->MaxPrice;
	}

	if( pAuctionInfo->MaxPrice != 0 && (unsigned long)NowPrice >= pAuctionInfo->MaxPrice )
	{
		if( pAuctionInfo->isBuyer == TRUE )
			this->CAuctionCtrl::SendBuyerAuctionCancel(pAuctionInfo, AuctionID);

		pAuctionInfo->BuyerAID = BuyAID;
		pAuctionInfo->BuyerGID = BuyGID;
		pAuctionInfo->NowPrice = (unsigned long)NowPrice;
		pAuctionInfo->isBuyer = TRUE;
		memcpy_s(pAuctionInfo->BuyerName, sizeof(pAuctionInfo->BuyerName), BuyName, 24);
		this->CAuctionCtrl::SendMailAuctionEnd(pAuctionInfo);
		this->CAuctionCtrl::DeleteAuction(AuctionID, pAuctionInfo->AuctionType);
		pBuyerPc->CPC::DeleteMoney(NowPrice);
		return TRUE;
	}
	else
	{
		if( pAuctionInfo->isBuyer == TRUE )
			this->CAuctionCtrl::SendBuyerAuctionCancel(pAuctionInfo, AuctionID);

		pAuctionInfo->BuyerAID = BuyAID;
		pAuctionInfo->BuyerGID = BuyGID;
		pAuctionInfo->NowPrice = (unsigned long)NowPrice;
		pAuctionInfo->isBuyer = TRUE;
		memcpy_s(pAuctionInfo->BuyerName, sizeof(pAuctionInfo->BuyerName), BuyName, 24);
		g_itemLog.CItemLog::AddItemLogOnMoney(ITEMLOG_AUCTION_BUYER_ADD, pBuyerPc, NULL, NowPrice, 0, pAuctionInfo->AuctionID, 0);

		if( !m_AuctionDB.CAuctionDB::ChangeBuyerAuction(AuctionID, BuyAID, BuyGID, BuyName, NowPrice) )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "DeleteAuction DB  %d", AuctionID);
			return FALSE;
		}

		pBuyerPc->CPC::DeleteMoney(NowPrice);
		return TRUE;
	}
}


int CAuctionCtrl::MySellStop(unsigned long AuctionID, unsigned long AID, unsigned long GID)
{
	AUCTIONINFO* pAuctionInfo = this->CAuctionCtrl::GetAuctionInfo(AuctionID);
	if( pAuctionInfo == NULL )
		return PACKET_ZC_AUCTION_ACK_MY_SELL_STOP::TYPE_AUCTION_ID_FALSE;

	if( pAuctionInfo->AID != AID || pAuctionInfo->GID != GID || pAuctionInfo->isBuyer != TRUE )
		return PACKET_ZC_AUCTION_ACK_MY_SELL_STOP::TYPE_FALSE;

	this->CAuctionCtrl::SendMailAuctionEnd(pAuctionInfo);
	this->CAuctionCtrl::DeleteAuction(AuctionID, pAuctionInfo->AuctionType);
	return PACKET_ZC_AUCTION_ACK_MY_SELL_STOP::TYPE_TRUE;
}


BOOL CAuctionCtrl::SendMailAuctionEnd(AUCTIONINFO* pAuctionInfo)
{
	if( !pAuctionInfo->isBuyer || strlen(pAuctionInfo->BuyerName) < 4 )
	{
		if( pAuctionInfo->BuyerAID != 0 )
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CAuctionCtrl :: SendMailAuctionEnd => pAuctionInfo->BuyerAID  %d", pAuctionInfo->BuyerAID);

		this->CAuctionCtrl::SendMailAuctionCanle(pAuctionInfo);
		return TRUE;
	}

	char ItemNameBuffer[80];
	this->CAuctionCtrl::GetClientItemName(pAuctionInfo->ITID, ItemNameBuffer);

	char Text[200];
	wsprintfA(Text + 1, "Auction Success %s", ItemNameBuffer);
	size_t TextLen = strlen(Text);
	Text[0] = TextLen;
	memset(Text + TextLen + 1, '\0', 13);

	PACKET_ZI_MAIL_SEND ZIPacket;

	ZIPacket.PacketType = HEADER_ZI_MAIL_SEND;
	ZIPacket.PacketLength = sizeof(PACKET_ZI_MAIL_SEND) + TextLen + 14;
	ZIPacket.AID = pAuctionInfo->AID;
	ZIPacket.GID = pAuctionInfo->GID;
	strcpy(ZIPacket.Header, "Auction");
	memset(ZIPacket.ItemInfo, 0, 40u);
	ZIPacket.Money = pAuctionInfo->NowPrice;
	ZIPacket.ItemLen = 0;
	strcpy(ZIPacket.SendName, "AuctionManager");
	ZIPacket.SendAID = 0;
	strcpy(ZIPacket.Header, "Auction");
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(PACKET_ZI_MAIL_SEND), (char*)&ZIPacket);
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(TextLen + 14, Text);

	ZIPacket.PacketType = HEADER_ZI_MAIL_SEND;
	ZIPacket.PacketLength = sizeof(PACKET_ZI_MAIL_SEND) + TextLen + 14;
	ZIPacket.AID = pAuctionInfo->BuyerAID;
	ZIPacket.GID = pAuctionInfo->BuyerGID;
	strcpy(ZIPacket.Header, "Auction");
	memcpy_s(ZIPacket.ItemInfo, sizeof(ZIPacket.ItemInfo), pAuctionInfo->Item, sizeof(pAuctionInfo->Item));
	ZIPacket.ItemLen = static_cast<char>(pAuctionInfo->ItemLen);
	strcpy(ZIPacket.SendName, "AuctionManager");
	ZIPacket.SendAID = 0;
	ZIPacket.Money = 0;
	strcpy(ZIPacket.Header, "Auction");
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(PACKET_ZI_MAIL_SEND), (char*)&ZIPacket);
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(TextLen + 14, Text);

	CommonItemInfo ItemInfo;
	CPCItemInventoryMgr::DBValueParser(&ItemInfo, pAuctionInfo->Item, pAuctionInfo->ItemLen);
	g_itemLog.CItemLog::AddMailAuctionLog(pAuctionInfo->AuctionID, ITEMLOG_AUCTION_END, pAuctionInfo->AID, pAuctionInfo->GID, pAuctionInfo->SellerName, pAuctionInfo->BuyerAID, pAuctionInfo->BuyerGID, pAuctionInfo->BuyerName, &ItemInfo, pAuctionInfo->NowPrice);

	return TRUE;
}


BOOL CAuctionCtrl::SendMailAuctionCanle(AUCTIONINFO* pAuctionInfo)
{
	char Text[200];
	strcpy(Text, "   Auction ");
	size_t TextLen = strlen(Text);
	Text[0] = TextLen;
	memset(Text + TextLen, '\0', 13);

	PACKET_ZI_MAIL_SEND ZIPacket;
	ZIPacket.PacketType = HEADER_ZI_MAIL_SEND;
	ZIPacket.PacketLength = sizeof(PACKET_ZI_MAIL_SEND) + TextLen + 13;
	ZIPacket.AID = pAuctionInfo->AID;
	ZIPacket.GID = pAuctionInfo->GID;
	strcpy(ZIPacket.Header, "Auction"); //NOTE: gets overwritten below
	memcpy_s(ZIPacket.ItemInfo, sizeof(ZIPacket.ItemInfo), pAuctionInfo->Item, sizeof(ZIPacket.ItemInfo));
	ZIPacket.ItemLen = static_cast<char>(pAuctionInfo->ItemLen);
	strcpy(ZIPacket.SendName, "AuctionManager");
	ZIPacket.SendAID = 0;
	ZIPacket.Money = 0;
	strcpy(ZIPacket.Header, "Auction");
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(PACKET_ZI_MAIL_SEND), (char*)&ZIPacket);
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(TextLen + 13, Text);

	CommonItemInfo ItemInfo;
	CPCItemInventoryMgr::DBValueParser(&ItemInfo, pAuctionInfo->Item, pAuctionInfo->ItemLen);
	g_itemLog.CItemLog::AddMailAuctionLog(pAuctionInfo->AuctionID, ITEMLOG_AUCTION_SELLER_CANCLE, pAuctionInfo->AID, pAuctionInfo->GID, pAuctionInfo->SellerName, 0, 0, "Auction", &ItemInfo, pAuctionInfo->NowPrice);

	return TRUE;
}


BOOL CAuctionCtrl::SendBuyerAuctionCancel(AUCTIONINFO* pAuctionInfo, unsigned long AuctionID)
{
	char ItemNameBuffer[80];
	this->CAuctionCtrl::GetClientItemName(pAuctionInfo->ITID, ItemNameBuffer);

	char Text[200];

	wsprintfA(Text + 1, "  Auction Cancel %s", ItemNameBuffer);
	size_t Part1MsgLen = strlen(Text + 1);
	size_t Part1TotalLen = Part1MsgLen + 1;
	Text[0] = Part1MsgLen;

	wsprintfA(Text + Part1TotalLen + 1, "  Auction ID %d ", pAuctionInfo->AuctionID);
	size_t Part2MsgLen = strlen(Text + Part1TotalLen + 1);
	size_t Part2TotalLen = Part2MsgLen + 1;
	Text[Part1TotalLen] = Part2MsgLen;

	Text[Part2MsgLen] = '\0';

	PACKET_ZI_MAIL_SEND ZIPacket;
	ZIPacket.PacketType = HEADER_ZI_MAIL_SEND;
	ZIPacket.PacketLength = sizeof(PACKET_ZI_MAIL_SEND) + 12 + Part2TotalLen;
	ZIPacket.AID = pAuctionInfo->BuyerAID;
	ZIPacket.GID = pAuctionInfo->BuyerGID;
	strcpy(ZIPacket.Header, "Auction"); //NOTE: gets overwritten below
	memset(ZIPacket.ItemInfo, 0, sizeof(ZIPacket.ItemInfo));
	ZIPacket.ItemLen = 0;
	strcpy(ZIPacket.SendName, "AuctionManager");
	ZIPacket.Money = pAuctionInfo->NowPrice;
	ZIPacket.SendAID = 0;
	strcpy(ZIPacket.Header, "Auction Cancel");
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(PACKET_ZI_MAIL_SEND), (char*)&ZIPacket);
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(12 + Part2TotalLen, Text);

	CommonItemInfo ItemInfo;
	CPCItemInventoryMgr::DBValueParser(&ItemInfo, pAuctionInfo->Item, pAuctionInfo->ItemLen);
	g_itemLog.CItemLog::AddMailAuctionLog(pAuctionInfo->AuctionID, ITEMLOG_AUCTION_BUYER_CANCLE, pAuctionInfo->BuyerAID, pAuctionInfo->BuyerGID, pAuctionInfo->SellerName, 0, 0, "Auction", &ItemInfo, pAuctionInfo->NowPrice);

	return TRUE;
}


void CAuctionCtrl::FindItem(unsigned long AccountID, int ItemType, int Page)
{
	int Counter;
	std::map<unsigned long,AUCTIONINFO*>::iterator Beginiter;
	std::map<unsigned long,AUCTIONINFO*>::iterator Enditer;
	switch( ItemType )
	{
	case TYPE_AUCTION_ARMOR:
		Counter = m_ArmorItem.size();
		Beginiter = m_ArmorItem.begin();
		Enditer = m_ArmorItem.end();
	break;
	case TYPE_AUCTION_WEAPON:
		Counter = m_WeaponItem.size();
		Beginiter = m_WeaponItem.begin();
		Enditer = m_WeaponItem.end();
	break;
	case TYPE_AUCTION_CARD:
		Counter = m_CardItem.size();
		Beginiter = m_CardItem.begin();
		Enditer = m_CardItem.end();
	break;
	case TYPE_AUCTION_ETC:
		Counter = m_EtcItem.size();
		Beginiter = m_EtcItem.begin();
		Enditer = m_EtcItem.end();
	break;
	default:
		return;
	break;
	};

	char buf[4150];
	int DataSize = 0;
	int ItemCounter = 0;
	int SkipCount = 5 * Page;

	AUCTION_ITEM_SEARCH_INFO* Info = reinterpret_cast<AUCTION_ITEM_SEARCH_INFO*>(buf);
	for( std::map<unsigned long,AUCTIONINFO*>::iterator iter = Beginiter; iter != Enditer; ++iter )
	{
		if( SkipCount != 0 )
		{
			--SkipCount;
			continue;
		}

		if( ItemCounter >= 5 )
			break; // reached maximum

		AUCTIONINFO* pAuctionInfo = iter->second;

		Info->AuctionID = pAuctionInfo->AuctionID;
		memcpy_s(Info->SellerName, sizeof(Info->SellerName), pAuctionInfo->SellerName, sizeof(pAuctionInfo->SellerName));
		Info->MaxPrice = pAuctionInfo->MaxPrice;
		Info->NowPrice = pAuctionInfo->NowPrice;
		Info->ITID = pAuctionInfo->ITID;
		Info->Type = pAuctionInfo->ItemType;
		Info->count = static_cast<short>(pAuctionInfo->count);
		Info->IsIdentified = pAuctionInfo->IsIdentified;
		Info->IsDamaged = pAuctionInfo->IsDamaged;
		Info->refiningLevel = pAuctionInfo->refiningLevel;
		memcpy_s(&Info->slot, sizeof(Info->slot), &pAuctionInfo->slot, sizeof(pAuctionInfo->slot));
		memcpy_s(Info->BuyerName, sizeof(Info->BuyerName), pAuctionInfo->BuyerName, sizeof(pAuctionInfo->BuyerName));
		CDateTime DateTime;
		DateTime.CDateTime::SetTime(pAuctionInfo->EndTime.Year, pAuctionInfo->EndTime.Month, pAuctionInfo->EndTime.Day, pAuctionInfo->EndTime.Hour),
		Info->DeleteTime = DateTime;

		DataSize += sizeof(AUCTION_ITEM_SEARCH_INFO);
		++Info;
		++ItemCounter;

		if( DataSize + sizeof(AUCTION_ITEM_SEARCH_INFO) > sizeof(buf) )
			break; // no more room for another entry
	}

	this->CAuctionCtrl::SendAuctionInfo(AccountID, ItemCounter, Counter, buf, DataSize);
}


void CAuctionCtrl::FindItemAuctionID(unsigned long AccountID, unsigned long AuctionID)
{
	AUCTIONINFO* pAuctionInfo = this->CAuctionCtrl::GetAuctionInfo(AuctionID);

	char buf[50 * sizeof(AUCTION_ITEM_SEARCH_INFO)];
	int DataSize = 0;

	AUCTION_ITEM_SEARCH_INFO* Info = reinterpret_cast<AUCTION_ITEM_SEARCH_INFO*>(buf);
	if( pAuctionInfo != NULL )
	{
		Info->AuctionID = pAuctionInfo->AuctionID;
		memcpy_s(Info->SellerName, sizeof(Info->SellerName), pAuctionInfo->SellerName, sizeof(pAuctionInfo->SellerName));
		Info->MaxPrice = pAuctionInfo->MaxPrice;
		Info->NowPrice = pAuctionInfo->NowPrice;
		Info->ITID = pAuctionInfo->ITID;
		Info->Type = pAuctionInfo->ItemType;
		Info->count = static_cast<short>(pAuctionInfo->count);
		Info->IsIdentified = pAuctionInfo->IsIdentified;
		Info->IsDamaged = pAuctionInfo->IsDamaged;
		Info->refiningLevel = pAuctionInfo->refiningLevel;
		memcpy_s(&Info->slot, sizeof(Info->slot), &pAuctionInfo->slot, sizeof(pAuctionInfo->slot));
		memcpy_s(Info->BuyerName, sizeof(Info->BuyerName), pAuctionInfo->BuyerName, sizeof(pAuctionInfo->BuyerName));
		CDateTime DateTime;
		DateTime.CDateTime::SetTime(pAuctionInfo->EndTime.Year, pAuctionInfo->EndTime.Month, pAuctionInfo->EndTime.Day, pAuctionInfo->EndTime.Hour);
		Info->DeleteTime = DateTime;

		DataSize = sizeof(AUCTION_ITEM_SEARCH_INFO);
	}

	this->CAuctionCtrl::SendAuctionInfo(AccountID, 1, 1, buf, DataSize);
}


void CAuctionCtrl::FindItemName(unsigned long AccountID, char* ItemName, int Page)
{
	char buf[50 * sizeof(AUCTION_ITEM_SEARCH_INFO)];
	int DataSize = 0;
	int SkipCount = 5 * Page;
	int AuctionCounter = 0;
	int FindTotal = 0;

	char NameBuffer[80];
	strcpy(NameBuffer, ItemName);

	if( strlen(NameBuffer) < 4 )
		this->CAuctionCtrl::SendAuctionInfo(AccountID, 0, 0, buf, 0);

	unsigned long IDTList[10];
	int FindIDTCount = g_itpMgr.CITPMgr::FindITID(NameBuffer, IDTList);
	if( FindIDTCount > 10 )
		FindIDTCount = 10;

	AUCTION_ITEM_SEARCH_INFO* Info = reinterpret_cast<AUCTION_ITEM_SEARCH_INFO*>(buf);
	for( int i = 0; i < FindIDTCount; ++i )
	{
		std::map<unsigned long,AUCTIONINFO*>::iterator Beginiter;
		std::map<unsigned long,AUCTIONINFO*>::iterator Enditer;
		switch( this->CAuctionCtrl::GetAuctionType(IDTList[i]) )
		{
		case TYPE_AUCTION_ARMOR:
			Beginiter = m_ArmorItem.begin();
			Enditer = m_ArmorItem.end();
		break;
		case TYPE_AUCTION_WEAPON:
			Beginiter = m_WeaponItem.begin();
			Enditer = m_WeaponItem.end();
		break;
		case TYPE_AUCTION_CARD:
			Beginiter = m_CardItem.begin();
			Enditer = m_CardItem.end();
		break;
		case TYPE_AUCTION_ETC:
			Beginiter = m_EtcItem.begin();
			Enditer = m_EtcItem.end();
		break;
		default:
			this->CAuctionCtrl::SendAuctionInfo(AccountID, 0, 0, buf, DataSize);
			return;
		break;
		};

		for( std::map<unsigned long,AUCTIONINFO*>::iterator iter = Beginiter; iter != Enditer; ++iter )
		{
			AUCTIONINFO* pAuctionInfo = iter->second;

			if( pAuctionInfo->ITID != IDTList[i] )
				continue;

			if( SkipCount != 0 )
			{
				--SkipCount;
				continue;
			}

			if( AuctionCounter >= 5 )
				continue;

			++FindTotal;

			Info->AuctionID = pAuctionInfo->AuctionID;
			memcpy_s(Info->SellerName, sizeof(Info->SellerName), pAuctionInfo->SellerName, sizeof(pAuctionInfo->SellerName));
			Info->MaxPrice = pAuctionInfo->MaxPrice;
			Info->NowPrice = pAuctionInfo->NowPrice;
			Info->ITID = pAuctionInfo->ITID;
			Info->Type = pAuctionInfo->ItemType;
			Info->count = static_cast<short>(pAuctionInfo->count);
			Info->IsIdentified = pAuctionInfo->IsIdentified;
			Info->IsDamaged = pAuctionInfo->IsDamaged;
			Info->refiningLevel = pAuctionInfo->refiningLevel;
			memcpy_s(&Info->slot, sizeof(Info->slot), &pAuctionInfo->slot, sizeof(pAuctionInfo->slot));
			memcpy_s(Info->BuyerName, sizeof(Info->BuyerName), pAuctionInfo->BuyerName, sizeof(pAuctionInfo->BuyerName));
			CDateTime DateTime;
			DateTime.CDateTime::SetTime(pAuctionInfo->EndTime.Year, pAuctionInfo->EndTime.Month, pAuctionInfo->EndTime.Day, pAuctionInfo->EndTime.Hour);
			Info->DeleteTime = DateTime;

			DataSize += sizeof(AUCTION_ITEM_SEARCH_INFO);
			++Info;
			++AuctionCounter;
		}
	}

	this->CAuctionCtrl::SendAuctionInfo(AccountID, AuctionCounter, FindTotal, buf, DataSize);
}


void CAuctionCtrl::TimeOver(int ItemType)
{
	std::map<unsigned long,AUCTIONINFO*>::iterator Beginiter;
	std::map<unsigned long,AUCTIONINFO*>::iterator Enditer;
	switch( ItemType )
	{
	case TYPE_AUCTION_ARMOR:
		Beginiter = m_ArmorItem.begin();
		Enditer = m_ArmorItem.end();
	break;
	case TYPE_AUCTION_WEAPON:
		Beginiter = m_WeaponItem.begin();
		Enditer = m_WeaponItem.end();
	break;
	case TYPE_AUCTION_CARD:
		Beginiter = m_CardItem.begin();
		Enditer = m_CardItem.end();
	break;
	case TYPE_AUCTION_ETC:
		Beginiter = m_EtcItem.begin();
		Enditer = m_EtcItem.end();
	break;
	default:
		return;
	break;
	};

	CDateTime DateTime;
	for( std::map<unsigned long,AUCTIONINFO*>::iterator iter = Beginiter; iter != Enditer; )
	{
		AUCTIONINFO* pAuctionInfo = iter->second;

		DateTime.CDateTime::SetTime(pAuctionInfo->EndTime.Year, pAuctionInfo->EndTime.Month, pAuctionInfo->EndTime.Day, pAuctionInfo->EndTime.Hour);
		if( !DateTime.CDateTime::CheckTimeOut(m_DateTime) )
		{
			++iter;
			continue;
		}

		if( !m_AuctionDB.CAuctionDB::DeleteAuction(pAuctionInfo->AuctionID) )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "DeleteAuction DB  %d", pAuctionInfo->AuctionID);
			continue; //FIXME: no increment or erase, will loop forever
		}

		this->CAuctionCtrl::SendMailAuctionEnd(pAuctionInfo);

		switch( ItemType )
		{
		case TYPE_AUCTION_ARMOR:
			iter = m_ArmorItem.erase(iter);
		break;
		case TYPE_AUCTION_WEAPON:
			iter = m_WeaponItem.erase(iter);
		break;
		case TYPE_AUCTION_CARD:
			iter = m_CardItem.erase(iter);
		break;
		case TYPE_AUCTION_ETC:
			iter = m_EtcItem.erase(iter);
		break;
		};
	}
}


BOOL CAuctionCtrl::AuctionAddCancel(unsigned long AuctionID, unsigned long SellerAID, unsigned long SellerGID)
{
	AUCTIONINFO* pAuctionInfo = this->CAuctionCtrl::GetAuctionInfo(AuctionID);
	if( pAuctionInfo == NULL )
		return FALSE;

	if( pAuctionInfo->GID != SellerGID || pAuctionInfo->BuyerAID && pAuctionInfo->BuyerGID )
		return FALSE;

	AUCTIONINFO TempAuctionInfo;
	memcpy_s(&TempAuctionInfo, sizeof(TempAuctionInfo), pAuctionInfo, sizeof(*pAuctionInfo));

	if( this->CAuctionCtrl::DeleteAuction(pAuctionInfo->AuctionID, pAuctionInfo->AuctionType) != TRUE )
		return FALSE;

	this->CAuctionCtrl::SendMailAuctionCanle(&TempAuctionInfo);
	return TRUE;
}


BOOL CAuctionCtrl::ReqMyInfo(int Type, unsigned long AID, unsigned long GID)
{
	unsigned long AuctionIDList[50];
	int AuctionCounter = 0;
	if( Type == PACKET_CZ_AUCTION_REQ_MY_INFO::TYPE_MY_SELL )
		AuctionCounter = m_AuctionDB.CAuctionDB::GetSellerAuctionID(m_ZoneServerID, AID, GID, AuctionIDList);
	else
	if( Type == PACKET_CZ_AUCTION_REQ_MY_INFO::TYPE_MY_BUY )
		AuctionCounter = m_AuctionDB.CAuctionDB::GetBuyerAuctionID(m_ZoneServerID, AID, GID, AuctionIDList);

	if( AuctionCounter > 5 )
		AuctionCounter = 5;

	char buf[50 * sizeof(AUCTION_ITEM_SEARCH_INFO)];
	int DataSize = 0;

	AUCTION_ITEM_SEARCH_INFO* Info = reinterpret_cast<AUCTION_ITEM_SEARCH_INFO*>(buf);
	for( int i = 0; i < AuctionCounter; ++i )
	{
		AUCTIONINFO* pAuctionInfo = this->CAuctionCtrl::GetAuctionInfo(AuctionIDList[i]);

		Info->AuctionID = pAuctionInfo->AuctionID;
		memcpy_s(Info->SellerName, sizeof(Info->SellerName), pAuctionInfo->SellerName, sizeof(pAuctionInfo->SellerName));
		Info->MaxPrice = pAuctionInfo->MaxPrice;
		Info->NowPrice = pAuctionInfo->NowPrice;
		Info->ITID = pAuctionInfo->ITID;
		Info->Type = pAuctionInfo->ItemType;
		Info->count = static_cast<short>(pAuctionInfo->count);
		Info->IsIdentified = pAuctionInfo->IsIdentified;
		Info->IsDamaged = pAuctionInfo->IsDamaged;
		Info->refiningLevel = pAuctionInfo->refiningLevel;
		memcpy_s(&Info->slot, sizeof(Info->slot), &pAuctionInfo->slot, sizeof(pAuctionInfo->slot));
		memcpy_s(Info->BuyerName, sizeof(Info->BuyerName), pAuctionInfo->BuyerName, sizeof(pAuctionInfo->BuyerName));
		CDateTime DateTime;
		DateTime.CDateTime::SetTime(pAuctionInfo->EndTime.Year, pAuctionInfo->EndTime.Month, pAuctionInfo->EndTime.Day, pAuctionInfo->EndTime.Hour);
		Info->DeleteTime = DateTime;

		++Info;
		DataSize += sizeof(AUCTION_ITEM_SEARCH_INFO);

		if( DataSize + sizeof(AUCTION_ITEM_SEARCH_INFO) > sizeof(buf) )
			break; // no more room for another entry
	}

	this->CAuctionCtrl::SendAuctionInfo(AID, AuctionCounter, AuctionCounter, buf, DataSize);
	return TRUE;
}


AUCTIONINFO* CAuctionCtrl::GetAuctionInfo(unsigned long AuctionID)
{
	std::map<unsigned long,AUCTIONINFO*>::iterator iter;

	iter = m_ArmorItem.find(AuctionID);
	if( iter != m_ArmorItem.end() )
		return iter->second;

	iter = m_WeaponItem.find(AuctionID);
	if( iter != m_WeaponItem.end() )
		return iter->second;

	iter = m_CardItem.find(AuctionID);
	if( iter != m_CardItem.end() )
		return iter->second;

	iter = m_EtcItem.find(AuctionID);
	if( iter != m_EtcItem.end() )
		return iter->second;

	return NULL; // not found.
}


int CAuctionCtrl::GetAuctionType(int ITID)
{
	CITP* itp = g_itpMgr.CITPMgr::GetITP(ITID);
	if( itp == NULL )
		return TYPE_AUCTION_ETC;

	switch( itp->GetType() )
	{
	case TYPE_ARMOR:
	case TYPE_ARMORTM:
	case TYPE_ARMORTB:
	case TYPE_ARMORMB:
	case TYPE_ARMORTMB:
		return TYPE_AUCTION_ARMOR;
	case TYPE_WEAPON:
	case TYPE_BOW:
	case TYPE_BOTHHAND:
	case TYPE_ARROW:
	case TYPE_GUN:
	case TYPE_AMMO:
	case TYPE_THROWWEAPON:
		return TYPE_AUCTION_WEAPON;
	case TYPE_CARD:
		return TYPE_AUCTION_CARD;
	default:
		return TYPE_AUCTION_ETC;
	};
}


void CAuctionCtrl::SendAuctionInfo(unsigned long AID, int ItemCounter, int MaxCounter, char* Buffer, int BufferSize)
{
	CPC* pPC = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(AID, PC_TYPE);

	PACKET_ZC_AUCTION_ITEM_REQ_SEARCH outpacket;
	outpacket.PacketType = HEADER_ZC_AUCTION_ITEM_REQ_SEARCH;
	outpacket.PacketLength = sizeof(PACKET_ZC_AUCTION_ITEM_REQ_SEARCH) + BufferSize;
	outpacket.MaxPage = MaxCounter / 5 + ( MaxCounter % 5 != 0 );
	outpacket.Number = ItemCounter;

	pPC->CPC::Send(sizeof(outpacket), (char*)&outpacket);
	if( BufferSize != 0 )
		pPC->CPC::Send(BufferSize, Buffer);
}


int CAuctionCtrl::GetCountSellItem(unsigned long AID, unsigned long GID)
{
	return m_AuctionDB.CAuctionDB::GetCountSellItem(m_ZoneServerID, AID, GID);
}


int CAuctionCtrl::GetCountBuyItem(unsigned long AID, unsigned long GID)
{
	return m_AuctionDB.CAuctionDB::GetCountBuyItem(m_ZoneServerID, AID, GID);
}


void CAuctionCtrl::GetClientItemName(int ITID, char* ItemName)
{
	CITP* itp = g_itpMgr.CITPMgr::GetITP(ITID);

	strcpy(ItemName, itp->m_name);

	for( size_t i = 0; i < strlen(ItemName); ++i )
	{
		if( ItemName[i] == '_' )
		{
			ItemName[i] = '\0';
			break; // done.
		}
	}
}
