#include "CharacterMgr.h"
#include "ScriptEventMgr.h"


CScriptEventMgr::~CScriptEventMgr()
{
	this->CScriptEventMgr::Reset();
}


void CScriptEventMgr::Process()
{
	for( SCRIPT_EVENTS::iterator iter = m_events.begin(); iter != m_events.end(); )
	{
		CScriptEventHandler* handler = iter->second;
		if( handler->Proc(false) != 0 )
		{
			++iter;
		}
		else
		{
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, handler->CScriptEventHandler::GetOwnerID(), CM_SET_SCRIPT_EVENT_NO, 0, 0, 0, 0);
			handler->Free();
			iter = m_events.erase(iter);
		}
	}
}


bool CScriptEventMgr::SendMsg(int eventNo, unsigned long msgID, int par1, int par2, int par3)
{
	CScriptEventHandler* handler = this->CScriptEventMgr::GetEvent(eventNo);
	if( handler == NULL )
		return false;

	handler->CScriptEventHandler::OnMsg(msgID, par1, par2, par3);
	return true;
}


CScriptEventHandler* CScriptEventMgr::GetEvent(int eventNo)
{
	SCRIPT_EVENTS::iterator iter = m_events.find(eventNo);
	if( iter == m_events.end() )
		return NULL;

	return iter->second;
}


void CScriptEventMgr::AddEvent(CScriptEventHandler* event)
{
	int eventNo = this->CScriptEventMgr::AllocEventNo();
	m_events.insert(std::pair<const int,CScriptEventHandler*>(eventNo, event));
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, event->CScriptEventHandler::GetOwnerID(), CM_SET_SCRIPT_EVENT_NO, eventNo, 0, 0, 0);
}


void CScriptEventMgr::RemoveEvent(int eventNo)
{
	SCRIPT_EVENTS::iterator iter = m_events.find(eventNo);
	if( iter == m_events.end() )
		return;

	iter->second->Free();
	m_events.erase(iter);
}


void CScriptEventMgr::Reset()
{
	for( SCRIPT_EVENTS::iterator iter = m_events.begin(); iter != m_events.end(); ++iter )
		delete iter->second;

	m_events.clear();
}


int CScriptEventMgr::AllocEventNo()
{
	static int g_scriptEventNo;
	return ++g_scriptEventNo;
}
