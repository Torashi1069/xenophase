#include "CharacterMgr.h"
#include "Enum.h"
#include "ITPMgr.h"
#include "Msg.h"
#include "ScriptCompiler.h"
#include "ScriptEventMgr.h"
#include "StdAfx.h" // stlwipe_second()
#include "ZoneProcess.h"
#include "ItemServer/specialitemmgr.h"
#include "ItemServer/specialitemscanner.h"
#include "shared/NCriticalErrorLog.h"


/// globals
CMemoryMgr<CItemScriptEventHandler>& g_itemHandlerPool = VTOR<CMemoryMgr<CItemScriptEventHandler>>(DetourFindFunction(EXEPATH(), "g_itemHandlerPool"));
int& w_index = VTOR<int>(DetourFindFunction(EXEPATH(), "w_index"));
int& w_cardItem = VTOR<int>(DetourFindFunction(EXEPATH(), "w_cardItem"));


bool CSpecialItemMgr::Init()
{
	g_itemHandlerPool.CMemoryMgr<CItemScriptEventHandler>::Init(500);

	if( !m_binBuf.CBinBuf::Load(GetScriptFileName(BIN_ITEM)) )
		return false;

	CSpecialItemScanner scanner(this, &m_binBuf);
	return scanner.CSpecialItemScanner::Run();
}


bool CSpecialItemMgr::Run(int itemCode, int count, int eventCode, int charID, const unsigned int in_Identity)
{
	CSpecialItem* item;
	if( !this->CSpecialItemMgr::GetItem(itemCode, item) )
		return true;

	SpecialItemEvent* event;
	if( !item->CSpecialItem::GetEvent(eventCode, event) )
		return false;

	m_nItemFuncIdx = 0;
	memset(m_nRetItemFunc, 0, sizeof(m_nRetItemFunc));
	memset(m_nRetItemFuncParam, 0, sizeof(m_nRetItemFuncParam));

	CITP* itp = g_itpMgr.CITPMgr::GetITP(itemCode);
	if( itp != NULL && itp->m_isUseEvent == true )
		return this->CSpecialItemMgr::AddEvent(charID, itemCode, event->beginPos);
	else
		return this->CSpecialItemMgr::RunEvent(charID, itemCode, event->beginPos, in_Identity);
}


bool CSpecialItemMgr::AddEvent(int charID, int itemCode, int beginPos)
{
	CItemScriptEventHandler* handler = g_itemHandlerPool.CMemoryMgr<CItemScriptEventHandler>::Alloc();
	if( handler == NULL )
		return false;

	handler->CItemScriptEventHandler::Set(this, m_nItemParam, charID, itemCode, 0);

	if( !handler->CItemScriptEventHandler::Run(&m_binBuf, beginPos) )
	{
		g_itemHandlerPool.CMemoryMgr<CItemScriptEventHandler>::Free(handler);
		return false;
	}

	g_scriptEventMgr.CScriptEventMgr::AddEvent(handler);
	return true;
}


bool CSpecialItemMgr::RunEvent(int charID, int itemCode, int beginPos, const unsigned int in_Identity)
{
	CItemScriptEventHandler handler;
	handler.CItemScriptEventHandler::Set(this, m_nItemParam, charID, itemCode, in_Identity);

	if( !handler.CItemScriptEventHandler::Run(&m_binBuf, beginPos) )
		return false;

	handler.CScriptEventHandler::Proc(true);
	return true;
}


namespace {
bool IsIgnoreCombiItem(unsigned short in_ITID, unsigned long in_WearState)
{
	return ( ( in_ITID == ITID_OCTO_KITCHEN_KNIFE || in_ITID == ITID_RWC_MEMORY_KNIFE ) && in_WearState == LOCATION_LARM );
}
}; // namespace


void CSpecialItemMgr::SendMsg(unsigned long in_ITID, unsigned long in_EventID, unsigned long in_senderAID, short in_Index)
{
	CITZMsg ansMsg;
	CSendSpecialItemInfoMsg ITZMsg;
	CReceiveSpecialItemInfoMsg ZITMsg;

	ITZMsg.CSendSpecialItemInfoMsg::SetCharId(in_senderAID);
	ITZMsg.CSendSpecialItemInfoMsg::SetItemId(in_ITID);
	ITZMsg.CSendSpecialItemInfoMsg::SetEvent(in_EventID);

	if( in_ITID < 30000 && (in_EventID == EVENT_START_EQUIP || in_EventID == EVENT_FINISH_EQUIP) )
	{
		CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_senderAID, PC_TYPE);
		unsigned long loc = pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipLocationbyIndex(in_Index);
		if( !IsIgnoreCombiItem(static_cast<unsigned short>(in_ITID), loc) )
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, in_senderAID, CM_MOVED_SPITEM, in_EventID, in_ITID, 0, 0);
	}

	w_cardItem = 0;
	w_index = in_Index;

	CITP* itp = g_itpMgr.CITPMgr::GetITP(static_cast<unsigned short>(in_ITID));
	if( itp != NULL && itp->GetType() == TYPE_CARD )
	{
		CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_senderAID, PC_TYPE);
		w_cardItem = pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::GetEquipItemIDbyIndex(in_Index);
	}

	unsigned int itemIdentity = (in_ITID & 0xFFFFFF) + 0x1000000;
	if( this->CSpecialItemMgr::GetItemSpecialStatus(&ITZMsg, &ZITMsg, itemIdentity) )
	{
		ansMsg.m_ITID = in_ITID;

		for( int i = 0; i < countof(m_nRetItemFunc); ++i )
		{
			if( m_nRetItemFunc[i] > 0 )
			{
				ansMsg.CMsg::SetMsgID(m_nRetItemFunc[i]);
				ansMsg.par1 = m_nRetItemFuncParam[i][0];
				ansMsg.par2 = m_nRetItemFuncParam[i][1];
				ansMsg.par3 = m_nRetItemFuncParam[i][2];
				ansMsg.par4 = m_nRetItemFuncParam[i][3];
				CCharacterMgr::GetObj()->CCharacterMgr::SendCommand(in_senderAID, &ansMsg);
			}
		}
	}
}


bool CSpecialItemMgr::GetItemSpecialStatus(CSendSpecialItemInfoMsg* pITZMsg, CReceiveSpecialItemInfoMsg* pZITMsg, const unsigned int in_Identity)
{
	m_nScanItem = pITZMsg->CSendSpecialItemInfoMsg::GetItemId();
	m_nScanEvent = pITZMsg->CSendSpecialItemInfoMsg::GetEvent();
	m_nItemFuncIdx = 0;
	this->CSpecialItemMgr::Run(m_nScanItem, 0, m_nScanEvent, pITZMsg->CSendSpecialItemInfoMsg::GetCharId(), in_Identity);
	return ( m_nItemFuncIdx > 0 );
}


bool CSpecialItemMgr::GetItem(int itemCode, CSpecialItem*& item)
{
	std::map<int,CSpecialItem*>::iterator f = m_itemMap.find(itemCode);
	if( f == m_itemMap.end() )
		return false;

	item = f->second;
	return true;
}


CSpecialItem* CSpecialItemMgr::CreateItem(int in_ITID)
{
	std::map<int,CSpecialItem*>::iterator iter = m_itemMap.find(in_ITID);
	if( iter != m_itemMap.end() )
	{
		char Desc[260] = {};
		const char* itemName = g_itpMgr.CITPMgr::GetItemName(in_ITID);
		if( itemName == NULL )
			itemName = "UNKNOWN";
		_snprintf_s(Desc, countof(Desc), _TRUNCATE, "[special.sc] duplicate %s(%d)", itemName, in_ITID);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", Desc);

		char buffer[520] = {};
		_snprintf_s(buffer, countof(buffer), _TRUNCATE, "found duplicate special.sc continue ?\n%s", Desc);
		if( MessageBoxA(NULL, buffer, "special.sc error", MB_YESNO) != IDYES )
			ExitProcess(EXIT_FAILURE);

		delete iter->second;
		m_itemMap.erase(iter);
	}

	CSpecialItem* item = new(std::nothrow) CSpecialItem();
	m_itemMap[in_ITID] = item;
	return item;
}


CSpecialItemMgr::CSpecialItemMgr()
{
}


CSpecialItemMgr::~CSpecialItemMgr()
{
	stlwipe_second(m_itemMap);
}
