#include "CAuctionDB.hpp"


CAuctionDB::CAuctionDB(void)
{
}


CAuctionDB::~CAuctionDB(void)
{
}


hook_method<unsigned long (CAuctionDB::*)(unsigned long ZoneServerID, DBAUCTIONINFO* pAuctionDB)> CAuctionDB::_AddAuction(SERVER, "CAuctionDB::AddAuction");
unsigned long CAuctionDB::AddAuction(unsigned long ZoneServerID, DBAUCTIONINFO* pAuctionDB)
{
	return (this->*_AddAuction)(ZoneServerID, pAuctionDB);

	//TODO
}


hook_method<int (CAuctionDB::*)(unsigned long AuctionID)> CAuctionDB::_DeleteAuction(SERVER, "CAuctionDB::DeleteAuction");
int CAuctionDB::DeleteAuction(unsigned long AuctionID)
{
	return (this->*_DeleteAuction)(AuctionID);

	//TODO
}


hook_method<int (CAuctionDB::*)(unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice)> CAuctionDB::_ChangeBuyerAuction(SERVER, "CAuctionDB::ChangeBuyerAuction");
int CAuctionDB::ChangeBuyerAuction(unsigned long AuctionID, unsigned long BuyAID, unsigned long BuyGID, char* BuyName, int NowPrice)
{
	return (this->*_ChangeBuyerAuction)(AuctionID, BuyAID, BuyGID, BuyName, NowPrice);

	//TODO
}


hook_method<int (CAuctionDB::*)(unsigned long ZoneServerID, int Type, CMemoryMgr<AUCTIONINFO>* pPool, mystd::map<unsigned long,AUCTIONINFO*>& AuctionInfo)> CAuctionDB::_GetAuction(SERVER, "CAuctionDB::GetAuction");
int CAuctionDB::GetAuction(unsigned long ZoneServerID, int Type, CMemoryMgr<AUCTIONINFO>* pPool, mystd::map<unsigned long,AUCTIONINFO*>& AuctionInfo)
{
	return (this->*_GetAuction)(ZoneServerID, Type, pPool, AuctionInfo);

	//TODO
}


hook_method<int (CAuctionDB::*)(unsigned long ZoneServerID, unsigned long BuyAID, unsigned long BuyGID, unsigned long* AuctionIDList)> CAuctionDB::_GetBuyerAuctionID(SERVER, "CAuctionDB::GetBuyerAuctionID");
int CAuctionDB::GetBuyerAuctionID(unsigned long ZoneServerID, unsigned long BuyAID, unsigned long BuyGID, unsigned long* AuctionIDList)
{
	return (this->*_GetBuyerAuctionID)(ZoneServerID, BuyAID, BuyGID, AuctionIDList);

	//TODO
}


hook_method<int (CAuctionDB::*)(unsigned long ZoneServerID, unsigned long SellerAID, unsigned long SellerGID, unsigned long* AuctionIDList)> CAuctionDB::_GetSellerAuctionID(SERVER, "CAuctionDB::GetSellerAuctionID");
int CAuctionDB::GetSellerAuctionID(unsigned long ZoneServerID, unsigned long SellerAID, unsigned long SellerGID, unsigned long* AuctionIDList)
{
	return (this->*_GetSellerAuctionID)(ZoneServerID, SellerAID, SellerGID, AuctionIDList);

	//TODO
}


hook_method<int (CAuctionDB::*)(unsigned long ZoneServerID, unsigned long AID, unsigned long GID)> CAuctionDB::_GetCountSellItem(SERVER, "CAuctionDB::GetCountSellItem");
int CAuctionDB::GetCountSellItem(unsigned long ZoneServerID, unsigned long AID, unsigned long GID)
{
	return (this->*_GetCountSellItem)(ZoneServerID, AID, GID);

	//TODO
}


hook_method<int (CAuctionDB::*)(unsigned long ZoneServerID, unsigned long AID, unsigned long GID)> CAuctionDB::_GetCountBuyItem(SERVER, "CAuctionDB::GetCountBuyItem");
int CAuctionDB::GetCountBuyItem(unsigned long ZoneServerID, unsigned long AID, unsigned long GID)
{
	return (this->*_GetCountBuyItem)(ZoneServerID, AID, GID);

	//TODO
}
