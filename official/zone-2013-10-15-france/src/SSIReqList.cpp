#include "SSIReqList.h"
////////////////////////////////////////


SSIRequest::SSIRequest()
{
	this->SSIRequest::Clear();
}


SSIRequest::SSIRequest(unsigned int inMaxPrice, unsigned int inMinPrice, unsigned int inReqAID, unsigned char inStoreType, unsigned int inMapID, const unsigned short* pITIDList, const unsigned char ITIDSize, const unsigned short* pCardInItemList, const unsigned char CardSize)
: ITIDList(), CardInItemList(), MaxPrice(inMaxPrice), MinPrice(inMinPrice), SearchType(0), ReqAID(inReqAID), StoreType(inStoreType), MapID(inMapID)
{
	if( ITIDSize == 0 || pITIDList == NULL )
		return;

	for( int i = 0; i < ITIDSize; ++i )
		this->ITIDList.push_back(pITIDList[i]);

	this->SearchType |= SEARCH_TYPE_ID;

	if( this->MaxPrice != 0 || this->MinPrice != 0 )
	{
		this->SearchType |= SEARCH_TYPE_PRICE;

		if( this->MaxPrice > 0 && this->MinPrice == 0 )
			this->SearchType |= SEARCH_TYPE_PRICE_LOWER;
		else if( this->MinPrice > 0 && this->MaxPrice == 0 )
			this->SearchType |= SEARCH_TYPE_PRICE_UPPER;
		else
			this->SearchType |= SEARCH_TYPE_PRICE_LOWER_TO_UPPER;
	}

	if( CardSize != 0 && pCardInItemList != NULL )
	{
		for( int i = 0; i < CardSize; ++i )
			CardInItemList.push_back(pCardInItemList[i]);

		this->SearchType |= SEARCH_TYPE_CARD_SLOT;
	}
}


void SSIRequest::Clear()
{
	this->ITIDList.clear();
	this->CardInItemList.clear();
	this->MaxPrice = 0;
	this->MinPrice = 0;
	this->SearchType = 0;
	this->ReqAID = 0;
	this->StoreType = 0;
	this->MapID = 0;
}


////////////////////////////////////////


CSSIReqList::CSSIReqList()
{
}


CSSIReqList::~CSSIReqList()
{
}


void CSSIReqList::InsertData(SSIRequest& in_Request)
{
	m_Queue.push(in_Request);
}


void CSSIReqList::GetRequestData(SSIRequest& outRequest)
{
	outRequest = m_Queue.front();
	m_Queue.pop();
}


bool CSSIReqList::IsEmptyRequestData()
{
	return m_Queue.empty();
}


////////////////////////////////////////
