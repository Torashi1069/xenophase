#pragma once


enum enumSTORESEARCHTYPE
{
	SEARCH_TYPE_ID                   = 0x01,
	SEARCH_TYPE_CARD_SLOT            = 0x04,
	SEARCH_TYPE_PRICE                = 0x08,
	SEARCH_TYPE_PRICE_UPPER          = 0x10,
	SEARCH_TYPE_PRICE_LOWER          = 0x20,
	SEARCH_TYPE_PRICE_LOWER_TO_UPPER = 0x40,
};


struct SSIRequest
{
public:
	typedef std::vector<unsigned short> type_ITIDList;
	/* this+ 0 */ std::vector<unsigned short> ITIDList;
	/* this+16 */ std::vector<unsigned short> CardInItemList;
	/* this+32 */ unsigned int MaxPrice;
	/* this+36 */ unsigned int MinPrice;
	/* this+40 */ int SearchType; // enumSTORESEARCHTYPE
	/* this+44 */ unsigned int ReqAID;
	/* this+48 */ unsigned char StoreType; // enumSTORETYPE
	/* this+52 */ unsigned int MapID;

public:
	void AddSearchType(const int ); //TODO
	void SetRequestAID(const unsigned int ); //TODO

public:
	SSIRequest();
	SSIRequest(unsigned int inMaxPrice, unsigned int inMinPrice, unsigned int inReqAID, unsigned char inStoreType, unsigned int inMapID, const unsigned short* pITIDList, const unsigned char ITIDSize, const unsigned short* pCardInItemList, const unsigned char CardSize);

public:
	void InsertITID(const unsigned short* , const int ); //TODO
	void InsertCardITID(const unsigned short* , const int ); //TODO
	void Clear();
};


class CSSIReqList
{
public:
	CSSIReqList();
	~CSSIReqList();

public:
	void InsertData(SSIRequest& in_Request);
	void GetRequestData(SSIRequest& outRequest);
	bool IsEmptyRequestData();

private:
	/* this+0 */ std::queue<SSIRequest> m_Queue;
};
