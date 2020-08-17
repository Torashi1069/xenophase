#include "SSIList.h"


CSSIList::CSSIList()
{
	m_SSI_ID = 1;
}


CSSIList::~CSSIList()
{
}


const unsigned int CSSIList::GeneratorSSI_ID()
{
	++m_SSI_ID;
	if( m_SSI_ID > GERNERNATOR_SSIID_MAX )
		m_SSI_ID = 1;

	return m_SSI_ID;
}


void CSSIList::InsertData(const unsigned char StoreType, const int MapID, std::tr1::shared_ptr<AllocSSIListInfoData> inData)
{
	if( inData.get() == NULL )
		return;

	if( StoreType != MC_STORE_TYPE && StoreType != BUYING_STORE_TYPE )
		return;

	m_List4[StoreType][MapID].insert(std::pair<const unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>(inData->m_pData->ITID, inData));
}


void CSSIList::UpdateData(const unsigned char StoreType, const int MapID, const unsigned int SSI_ID, const short cnt)
{
	if( StoreType != MC_STORE_TYPE && StoreType != BUYING_STORE_TYPE )
		return;

	std::map<int,std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>>::iterator find_iter  = m_List4[StoreType].find(MapID);
	if( find_iter == m_List4[StoreType].end() )
		return;

	std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>& rList = find_iter->second;

	for( std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator iter_item = rList.begin(); iter_item != rList.end(); ++iter_item )
	{
		SSIListInfo* pData = iter_item->second->m_pData;
		if( pData != NULL && SSI_ID == pData->SSI_ID )
		{
			if( cnt <= 0 )
			{
				m_SearchingList.CSearchingSSIList::DeleteData(pData);
				iter_item = rList.erase(iter_item);
			}
			else
			{
				pData->count = cnt;
			}
			return;
		}
	}
}


void CSSIList::DeleteData(const unsigned char StoreType, const int MapID, const unsigned int AID)
{
	if( StoreType != MC_STORE_TYPE && StoreType != BUYING_STORE_TYPE )
		return;

	std::map<int,std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>>::iterator find_iter = m_List4[StoreType].find(MapID);
	if( find_iter == m_List4[StoreType].end() )
		return;

	std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>& rList = find_iter->second;

	std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator iter_item = rList.begin();
	while( iter_item != rList.end() )
	{
		SSIListInfo* pData = iter_item->second->m_pData;
		if( pData != NULL && AID == pData->AID )
		{
			m_SearchingList.CSearchingSSIList::DeleteData(pData);
			iter_item = rList.erase(iter_item);
		}
		else
		{
			++iter_item;
		}
	}
}


int CSSIList::SearchData(const SSIRequest& in_Request)
{
	if( m_SearchingList.CSearchingSSIList::GetCurSearchingDataCnt(in_Request.ReqAID) > 0 )
		m_SearchingList.CSearchingSSIList::DeleteDataFromReqAID(in_Request.ReqAID);

	if( in_Request.StoreType != MC_STORE_TYPE && in_Request.StoreType != BUYING_STORE_TYPE )
		return -1;

	if( !(in_Request.SearchType & SEARCH_TYPE_ID) )
		return -1;

	std::map<int,std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>>::iterator find_iter = m_List4[in_Request.StoreType].find(in_Request.MapID);
	if( find_iter == m_List4[in_Request.StoreType].end() )
		return 0;

	std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>& rList = find_iter->second;

	std::map<int,std::vector<SSIListInfo*>> step_list;
	int nSearchingNum = 0;

	for( std::vector<unsigned short>::const_iterator iter_ITIDList = in_Request.ITIDList.begin(); iter_ITIDList != in_Request.ITIDList.end(); ++iter_ITIDList )
	{
		unsigned short ITID = *iter_ITIDList;

		int cur_step_cnt = 0;
		int old_step_cnt = 0;
		step_list.clear();

		std::pair<std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator,std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator> infoRange = rList.equal_range(ITID);
		if( infoRange.first == infoRange.second )
			continue;

		if( in_Request.SearchType == SEARCH_TYPE_ID )
		{
			for( std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator iter_item = infoRange.first; iter_item != infoRange.second; ++iter_item )
			{
				AllocSSIListInfoData* item = iter_item->second.get();
				if( item != NULL )
				{
					SSIListInfo* pInfo = item->m_pData;
					m_SearchingList.CSearchingSSIList::InsertData(in_Request.ReqAID, pInfo);
					++nSearchingNum;
				}
			}

			continue; // fast-path
		}

		if( in_Request.SearchType & SEARCH_TYPE_ID )
		{
			for( std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator iter_item = infoRange.first; iter_item != infoRange.second; ++iter_item )
			{
				AllocSSIListInfoData* item = iter_item->second.get();
				if( item != NULL )
				{
					SSIListInfo* pInfo = item->m_pData;
					step_list[cur_step_cnt].push_back(pInfo);
				}
			}

			if( step_list[cur_step_cnt].size() == 0 )
				continue;

			old_step_cnt = 0;
			cur_step_cnt = 1;
		}

		if( in_Request.SearchType & SEARCH_TYPE_CARD_SLOT )
		{
			std::vector<SSIListInfo*>& list = step_list[old_step_cnt];
			for( std::vector<SSIListInfo*>::const_iterator step_iter = list.begin(); step_iter != list.end(); ++step_iter )
			{
				for( std::vector<unsigned short>::const_iterator card_iter = in_Request.CardInItemList.begin(); card_iter != in_Request.CardInItemList.end(); ++card_iter )
				{
					SSIListInfo* pInfo = *step_iter;
					if( pInfo != NULL )
					{
						for( int i = 0; i < countof(pInfo->CardSlot.info); ++i )
						{
							if( pInfo->CardSlot.info[i] == *card_iter )
							{
								step_list[cur_step_cnt].push_back(pInfo);
								break;
							}
						}
					}
				}
			}

			if( step_list[cur_step_cnt].size() == 0 )
				continue;

			old_step_cnt = 1;
			cur_step_cnt = 2;
		}

		if( in_Request.SearchType & SEARCH_TYPE_PRICE )
		{
			std::vector<SSIListInfo*>& list = step_list[old_step_cnt];
			for( std::vector<SSIListInfo*>::const_iterator step_iter = list.begin(); step_iter != list.end(); ++step_iter )
			{
				SSIListInfo* pInfo = *step_iter;
				if( pInfo != NULL )
				{
					if( in_Request.SearchType & SEARCH_TYPE_PRICE_LOWER )
					{
						if( in_Request.MaxPrice >= (unsigned int)pInfo->price )
							step_list[cur_step_cnt].push_back(pInfo);
					}
					else
					if( in_Request.SearchType & SEARCH_TYPE_PRICE_UPPER )
					{
						if( in_Request.MinPrice <= (unsigned int)pInfo->price )
							step_list[cur_step_cnt].push_back(pInfo);
					}
					else
					if( in_Request.SearchType & SEARCH_TYPE_PRICE_LOWER_TO_UPPER )
					{
						if( in_Request.MinPrice <= (unsigned int)pInfo->price && in_Request.MaxPrice >= (unsigned int)pInfo->price )
							step_list[cur_step_cnt].push_back(pInfo);
					}
				}
			}

			if( step_list[cur_step_cnt].size() == 0 )
				continue;

			old_step_cnt = cur_step_cnt;
		}

		std::vector<SSIListInfo*>& list = step_list[old_step_cnt];
		for( std::vector<SSIListInfo*>::const_iterator out_iter = list.begin(); out_iter != list.end(); ++out_iter )
		{
			SSIListInfo* pInfo = *out_iter;
			if( pInfo != NULL )
			{
				m_SearchingList.CSearchingSSIList::InsertData(in_Request.ReqAID, pInfo);
				++nSearchingNum;
			}
		}
	}

	m_SearchingList.CSearchingSSIList::SetSearchingInfo(in_Request.ReqAID, in_Request.StoreType);
	m_SearchingList.CSearchingSSIList::Sort(in_Request.ReqAID);
	return nSearchingNum;
}


void CSSIList::GetSearchingData(const unsigned int AID, std::vector<ResultItemInfo>& rOut_list, const int Size)
{
	if( AID == 0 || Size > 10 )
		return;

	m_SearchingList.CSearchingSSIList::SearchData(AID, rOut_list, Size);
}


void CSSIList::DeleteSearchData(const unsigned int AID)
{
	m_SearchingList.CSearchingSSIList::DeleteDataFromReqAID(AID);
	m_SearchingList.CSearchingSSIList::DeleteSearchInfo(AID);
}


const POINTS CSSIList::GetStorePos(const unsigned int AID, const int MapID, const unsigned short ITID, const unsigned int SSI_ID)
{
	POINTS result = { -1, -1 };

	unsigned char StoreType = m_SearchingList.CSearchingSSIList::GetSearchingStoretype(AID);
	if( StoreType == 99 )
		return result;

	std::map<int,std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>>::iterator find_iter = m_List4[StoreType].find(MapID);
	if( find_iter == m_List4[StoreType].end() )
		return result;

	std::pair<std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator,std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator> infoRange = find_iter->second.equal_range(ITID);
	for( std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator iter_item = infoRange.first; iter_item != infoRange.second; ++iter_item )
	{
		SSIListInfo* pData = iter_item->second->m_pData;
		if( SSI_ID == pData->SSI_ID )
		{
			result.x = pData->x;
			result.y = pData->y;
			break; // found.
		}
	}

	return result;
}


bool CSSIList::IsExistSSI_ID(const unsigned int AID, const int MapID, const unsigned short ITID, const unsigned int SSI_ID)
{
	unsigned char StoreType = m_SearchingList.CSearchingSSIList::GetSearchingStoretype(AID);
	if( StoreType == CSearchingSSIList::INVALID_STORE_TYPE )
		return false;

	std::map<int,std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>>::iterator find_iter = m_List4[StoreType].find(MapID);
	if( find_iter == m_List4[StoreType].end() )
		return false;

	std::pair<std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator,std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator> infoRange = find_iter->second.equal_range(ITID);
	for( std::multimap<unsigned short,std::tr1::shared_ptr<AllocSSIListInfoData>>::iterator iter_item = infoRange.first; iter_item != infoRange.second; ++iter_item )
	{
		SSIListInfo* pData = iter_item->second->m_pData;
		if( SSI_ID == pData->SSI_ID )
			return true; // found.
	}

	return false; // not found.
}


const int CSSIList::GetSearchingStoretype(const unsigned int AID)
{
	return m_SearchingList.CSearchingSSIList::GetSearchingStoretype(AID);
}


const int CSSIList::GetCurSeachingDataCnt(const unsigned int AID)
{
	return m_SearchingList.CSearchingSSIList::GetCurSearchingDataCnt(AID);
}


const bool CSSIList::PossibleTime(const unsigned int AID)
{
	return m_SearchingList.CSearchingSSIList::PossibleTime(AID);
}
