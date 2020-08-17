#pragma once
#include "SSIListBase.h"


struct SearchingInfo
{
	/* this+0 */ unsigned char StoreType; // enumSTORETYPE
	/* this+4 */ DWORD Time;
};


class CSearchingSSIList
{
public:
	enum { RESEARCH_POSSIBLE_TIME = 2000 };
	enum { INVALID_STORE_TYPE = 99 };

public:
	CSearchingSSIList();
	~CSearchingSSIList();

public:
	void InsertData(const unsigned int AID, SSIListInfo* inData);
	void SearchData(const unsigned int AID, std::vector<ResultItemInfo>& rOut_list, const int Size);
	void DeleteData(const SSIListInfo* pData);
	void DeleteDataFromReqAID(const unsigned int AID);
	void DeleteSearchInfo(const unsigned int AID);
	void SetSearchingInfo(const unsigned int AID, unsigned char StoreType);
	const unsigned char GetSearchingStoretype(const unsigned int AID);
	const bool PossibleTime(const unsigned int AID);
	const int GetCurSearchingDataCnt(const unsigned int AID);
	void Sort(const unsigned int AID);
	void OutPut(); //TODO

private:
	/* this+ 0 */ std::map<unsigned int,std::vector<SSIListInfo*>> m_List2;
	/* this+16 */ std::map<unsigned int,SearchingInfo> m_SearchingInfoList;
};
