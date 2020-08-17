#include "SearchingSSIList.h"


CSearchingSSIList::CSearchingSSIList()
{
}


CSearchingSSIList::~CSearchingSSIList()
{
}


void CSearchingSSIList::InsertData(const unsigned int AID, SSIListInfo* inData)
{
	if( inData == NULL )
		return;

	m_List2[AID].push_back(inData);
}


void CSearchingSSIList::SearchData(const unsigned int AID, std::vector<ResultItemInfo>& rOut_list, const int Size)
{
	std::map<unsigned int,std::vector<SSIListInfo*>>::iterator find_it = m_List2.find(AID);
	if( find_it == m_List2.end() )
		return;

	std::vector<SSIListInfo*>::iterator begin_it = find_it->second.begin();
	int cnt = 0;

	while( begin_it != find_it->second.end() && cnt < Size )
	{
		SSIListInfo* info = *begin_it;

		if( info != NULL )
		{
			rOut_list.push_back(*info);
			++cnt;

			begin_it = find_it->second.erase(begin_it);
		}
		else
		{
			++begin_it;
		}
	}
}


void CSearchingSSIList::DeleteDataFromReqAID(const unsigned int AID)
{
	std::map<unsigned int,std::vector<SSIListInfo*>>::iterator find_it = m_List2.find(AID);
	if( find_it == m_List2.end() )
		return;

	find_it->second.clear();
	m_List2.erase(find_it);
}


void CSearchingSSIList::DeleteData(const SSIListInfo* pData)
{
	if( pData == NULL )
		return;

	for( std::map<unsigned int,std::vector<SSIListInfo*>>::iterator iter_list = m_List2.begin(); iter_list != m_List2.end(); ++iter_list )
	{
		std::vector<SSIListInfo*>::iterator iter = iter_list->second.begin();
		while( iter != iter_list->second.end() )
		{
			if( pData == *iter )
			{
				iter = iter_list->second.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
}


const unsigned char CSearchingSSIList::GetSearchingStoretype(const unsigned int AID)
{
	std::map<unsigned int,SearchingInfo>::const_iterator iter = m_SearchingInfoList.find(AID);
	if( iter == m_SearchingInfoList.end() )
		return INVALID_STORE_TYPE;

	return iter->second.StoreType;
}


void CSearchingSSIList::SetSearchingInfo(const unsigned int AID, unsigned char StoreType)
{
	m_SearchingInfoList[AID].Time = timeGetTime() + RESEARCH_POSSIBLE_TIME;
	m_SearchingInfoList[AID].StoreType = StoreType;
}


const bool CSearchingSSIList::PossibleTime(const unsigned int AID)
{
	if( m_SearchingInfoList.find(AID) == m_SearchingInfoList.end() )
		return true; // no delay record

	if( timeGetTime() >= m_SearchingInfoList[AID].Time )
		return true; // delay expired

	return false; // still under delay
}


void CSearchingSSIList::DeleteSearchInfo(const unsigned int AID)
{
	m_SearchingInfoList.erase(AID);
}


namespace {
bool __cdecl _Pred_Sort(SSIListInfo* lpt, SSIListInfo* rpt)
{
	return ( lpt->price < rpt->price );
}
}; // namespace


void CSearchingSSIList::Sort(const unsigned int AID)
{
	std::map<unsigned int,std::vector<SSIListInfo*>>::iterator find_it = m_List2.find(AID);
	if( find_it == m_List2.end() )
		return;

	std::sort(find_it->second.begin(), find_it->second.end(), &_Pred_Sort);
}


const int CSearchingSSIList::GetCurSearchingDataCnt(const unsigned int AID)
{
	std::map<unsigned int,std::vector<SSIListInfo*>>::const_iterator find_it = m_List2.find(AID);
	if( find_it == m_List2.end() )
		return 0;

	return find_it->second.size();
}
