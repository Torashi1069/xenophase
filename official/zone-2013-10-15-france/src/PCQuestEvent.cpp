	#include "PCQuestEvent.h"


CPCQuestEvent::CPCQuestEvent() // 27-29
{
	this->CPCQuestEvent::Reset();
}


CPCQuestEvent::~CPCQuestEvent() // 32-34
{
	this->CPCQuestEvent::Reset();
}


bool CPCQuestEvent::InIt(CPC* pc) // 37-43
{
	this->CPCQuestEvent::Reset();

	if( pc == NULL )
		return false;

	m_owner = pc;
	return true;
}


void CPCQuestEvent::Reset() // 46-89
{
	//TODO
}


int CPCQuestEvent::IsBeginQuest(unsigned long questID) // 293-300
{
	if( questID < 1 )
		return 0;

	if( this->CPCQuestEvent::FindCompleteQuest(questID) )
		return 2;
	else
	if( this->CPCQuestEvent::IsQuest(questID) )
		return 1;
	else
	{
		return 0;
	}
}


bool CPCQuestEvent::IsQuest(unsigned long quest) // 725-734
{
	return ( m_map.find(quest) != m_map.end() );
}


bool CPCQuestEvent::FindCompleteQuest(unsigned long quest) // 756-767
{
	for( TCOMPLETEQUEST_VT::const_iterator iter = m_vCompleteQuest.begin(); iter != m_vCompleteQuest.end(); ++iter )
		if( *iter == quest )
			return true; // found.
	

	return false; // not found.
}


void CPCQuestEvent::SetArlimiList(unsigned long npcID)
{
	m_arlimiList.push_back(npcID);
}


unsigned long CPCQuestEvent::GetArlimiList() // 783-791
{
	if( m_arlimiList.size() == 0 )
		return 0;

	unsigned long npcID = m_arlimiList.front();
	m_arlimiList.pop_front();
	return npcID;
}


void CPCQuestEvent::ResetArlimiList()
{
	m_arlimiList.clear();
}
