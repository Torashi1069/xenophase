#pragma once
#include "SearchingSSIList.h"
#include "SSIListBase.h"
#include "SSIReqList.h"


enum enumSTORETYPE
{
	MC_STORE_TYPE     = 0,
	BUYING_STORE_TYPE = 1,
	STORE_TYPE_LAST      ,
};


class CSSIList
{
public:
	enum { GERNERNATOR_SSIID_MAX = 200000000 };

public:
	CSSIList();
	virtual ~CSSIList();

public:
	void InsertData(const unsigned char StoreType, const int MapID, std::tr1::shared_ptr<AllocSSIListInfoData> inData);
	void UpdateData(const unsigned char StoreType, const int MapID, const unsigned int SSI_ID, const short cnt);
	void DeleteData(const unsigned char StoreType, const int MapID, const unsigned int AID);
	int SearchData(const SSIRequest& in_Request);
	const POINTS GetStorePos(const unsigned int AID, const int MapID, const unsigned short ITID, const unsigned int SSI_ID);
	void DeleteSearchData(const unsigned int AID);
	void GetSearchingData(const unsigned int AID, std::vector<ResultItemInfo>& rOut_list, const int Size);
	const int GetSearchingStoretype(const unsigned int AID);
	const int GetCurSeachingDataCnt(const unsigned int AID);
	const bool PossibleTime(const unsigned int AID);
	const int GetSize(); //TODO
	bool IsExistSSI_ID(const unsigned int AID, const int MapID, const unsigned short ITID, const unsigned int SSI_ID);
	const unsigned int GeneratorSSI_ID();
	void Output(); //TODO

private:
	/* this+ 0 */ //const CSSIList::`vftable';
	/* this+ 4 */ std::map<int,std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>> m_List4[STORE_TYPE_LAST];
	/* this+36 */ CSearchingSSIList m_SearchingList;
	/* this+68 */ unsigned int m_SSI_ID;
};
