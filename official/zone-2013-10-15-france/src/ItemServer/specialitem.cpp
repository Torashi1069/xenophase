#include "StdAfx.h" // stlwipe_second()
#include "ItemServer/specialitem.h"


CSpecialItem::CSpecialItem()
{
}


CSpecialItem::~CSpecialItem()
{
	stlwipe_second(m_eventMap);
}


bool CSpecialItem::GetEvent(int eventCode, SpecialItemEvent*& eventRet)
{
	std::map<int,SpecialItemEvent*>::iterator f = m_eventMap.find(eventCode);
	if( f == m_eventMap.end() )
		return false;

	eventRet = f->second;
	return true;
}


bool CSpecialItem::DestroyEvent(int eventCode)
{
	std::map<int,SpecialItemEvent*>::iterator f = m_eventMap.find(eventCode);
	if( f == m_eventMap.end() )
		return false;

	delete f->second;
	m_eventMap.erase(f);
	return true;
}


SpecialItemEvent* CSpecialItem::CreateEvent(int eventCode, int beginPos)
{
	this->CSpecialItem::DestroyEvent(eventCode);

	SpecialItemEvent* event = new SpecialItemEvent();
	event->beginPos = beginPos;
	event->varList.clear();

	m_eventMap[eventCode] = event;
	return event;
}
