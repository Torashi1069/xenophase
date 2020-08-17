#include "CheckUseItemList.h"
#include "ITP.h"
#include "ITPMgr.h"
#include "ZoneProcess.h"
#include "ItemServer/specialitemscanner.h"


CSpecialItemScanner::CSpecialItemScanner(CSpecialItemMgr* itemMgr, CBinBuf* binBuf)
: m_interpreter(),
  m_isError(false),
  m_itemMgr(&g_specialItmMgr)
{
	m_interpreter.CInterpreter::RegisterHandler(this);
	m_interpreter.CInterpreter::Scan(binBuf, 0);
	m_currentItemID = 0;
}


CSpecialItemScanner::~CSpecialItemScanner()
{
}


bool CSpecialItemScanner::Run()
{
	while( m_interpreter.CInterpreter::Proc() )
		;

	return ( m_isError == false );
}


bool CSpecialItemScanner::OnFunc(int func, std::deque<TokenData>& parm, TokenData& ret)
{
	switch( func )
	{
	case FUNC_ITEM2:
	{
		if( parm.size() != 1 )
			return false;

		int itemID = parm[0].TokenData::GetNum();
		m_currentItemID = itemID;
		return this->CSpecialItemScanner::FuncItem(itemID, true);
	}
	break;
	case FUNC_CREATEITEM:
	case FUNC_ITEMCREATE:
	case FUNC_COOKING:
	{
		CCheckUseItemList::GetObj()->CCheckUseItemList::AddItemID_Create(m_currentItemID);
		return true;
	}
	break;
	case FUNC_ITEM:
	{
		if( parm.size() != 1 )
			return false;

		int itemID = parm[0].TokenData::GetNum();
		m_currentItemID = itemID;
		return this->CSpecialItemScanner::FuncItem(itemID, false);
	}
	break;
	case FUNC_EVENT:
	{
		if( parm.size() != 1 || m_item == NULL )
			return false;

		int eventCode = parm[0].TokenData::GetNum();
		int beginPos = m_interpreter.CInterpreter::GetCurPos();
		m_event = m_item->CSpecialItem::CreateEvent(eventCode, beginPos);
		return true;
	}
	break;
	case FUNC_GET:
	{
		if( parm.size() != 1 || m_item == NULL || m_event == NULL )
			return false;

		int var = parm[0].TokenData::GetNum();
		m_event->varList.push_back(var);
		return true;
	}
	break;
	default:
	{
		return true;
	}
	break;
	};
}


void CSpecialItemScanner::OnError(const char* str)
{
	m_isError = true;
	printf(str); //FIXME: uncontrolled format string vulnerability
}


bool CSpecialItemScanner::FuncItem(int itemID, bool isUseEvent)
{
	CITP* itp = g_itpMgr.CITPMgr::GetITP(itemID);
	if( itp != NULL )
		itp->m_isUseEvent = isUseEvent;

	m_item = m_itemMgr->CSpecialItemMgr::CreateItem(itemID);
	return true;
}
