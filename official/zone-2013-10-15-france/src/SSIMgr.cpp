#include "CharacterMgr.h"
#include "SSIMgr.h"
#include "Common/Packet.h"


/// singleton instance
CSSIMgr*& CSSIMgr::m_pSelf = VTOR<CSSIMgr*>(DetourFindFunction(EXEPATH(), "CSSIMgr::m_pSelf"));


CSSIMgr::CSSIMgr()
{
}


CSSIMgr::~CSSIMgr()
{
}


bool CSSIMgr::CreateInstance()
{
	if( m_pSelf != NULL )
		return false;

	m_pSelf = new CSSIMgr();
	if( m_pSelf == NULL )
		return false;

	return true;
}


void CSSIMgr::DestoryInstance()
{
	if( m_pSelf != NULL )
	{
		delete m_pSelf;
		m_pSelf = NULL;
	}
}


CSSIMgr* CSSIMgr::GetObj() /// @custom
{
	return m_pSelf;
}


namespace {
void SendFailedPakcet(const unsigned int AID, const int Reason)
{
	PACKET_ZC_SEARCH_STORE_INFO_FAILED outPacket;
	outPacket.PacketType = HEADER_ZC_SEARCH_STORE_INFO_FAILED;
	outPacket.Reason = Reason;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, sizeof(outPacket), (int)&outPacket, 0, 0);
}
}; // namespace


void CSSIMgr::Proc()
{
	if( m_SSIRequest.IsEmptyRequestData() )
		return;

	SSIRequest data;
	data.SSIRequest::Clear();
	m_SSIRequest.CSSIReqList::GetRequestData(data);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(data.ReqAID, PC_TYPE);
	if( pc == NULL )
		return;

	if( pc->CPC::GetSSI_LimitSearchCnt() <= 0 )
	{
		SendFailedPakcet(data.ReqAID, SSI_FAILED_SEARCH_CNT);
		return;
	}

	pc->CPC::SetSSI_LimitSearchCnt(pc->CPC::GetSSI_LimitSearchCnt() - 1);

	int nSearchingNum = m_SSIList.CSSIList::SearchData(data);
	if( nSearchingNum == -1 )
		return;

	PACKET_ZC_SEARCH_STORE_INFO_ACK outpacket = {};
	outpacket.PacketType = HEADER_ZC_SEARCH_STORE_INFO_ACK;
	outpacket.RemainedSearchCnt = pc->CPC::GetSSI_LimitSearchCnt();
	outpacket.IsNexPage = ( nSearchingNum > 10 );

	if( nSearchingNum <= 0 )
	{
		outpacket.PacketLength = sizeof(outpacket);
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, data.ReqAID, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
		SendFailedPakcet(data.ReqAID, SSI_FAILED_NOTHING_SEARCH_ITEM);
		return;
	}

	std::vector<ResultItemInfo> ResultList;
	ResultList.reserve(10);
	m_SSIList.CSSIList::GetSearchingData(data.ReqAID, ResultList, min(nSearchingNum,10));
	size_t ResultListSize = ResultList.size() * sizeof(ResultItemInfo);

	outpacket.IsFirstPage = true;
	outpacket.PacketLength = sizeof(outpacket) + ResultListSize;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, data.ReqAID, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
	if( ResultListSize > 0 )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, data.ReqAID, CM_SEND_PACKET, ResultListSize, (int)&ResultList.front(), 0, 0);
}
