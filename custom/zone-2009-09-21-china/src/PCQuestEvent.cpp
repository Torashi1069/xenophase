#include "Mission_Hunt.h"
#include "PC.h"
#include "PCQuestEvent.h"
#include "QuestEventInfo.h"
#include "Common/Packet.h"


CPCQuestEvent::CPCQuestEvent() // line 24
{
	this->CPCQuestEvent::Reset();
}


CPCQuestEvent::~CPCQuestEvent() // line 29
{
	this->CPCQuestEvent::Reset();
}


bool CPCQuestEvent::InIt(CPC* pc) // line 34
{
	this->CPCQuestEvent::Reset();

	if( pc == NULL )
		return false;

	m_owner = pc;
	return true;
}


void CPCQuestEvent::Reset() // line 43-86
{
	m_isUpdateData = false;

	for( TQUEST_MAP::iterator it = m_map.begin(); it != m_map.end(); ++it )
		delete it->second;	
	m_map.clear();

	for( TMISSION_MAP::iterator it = m_huntMap.begin(); it != m_huntMap.end(); ++it )
		delete it->second;
	m_huntMap.clear();

	m_huntIndex.CPCHuntIndex::Clear();

	m_vCompleteQuest.clear();

	m_owner = NULL;
}


hook_method<bool (CPCQuestEvent::*)(const unsigned char* in_pData_quest, const int in_Length_quest, const unsigned char* in_pData_hunt, const int in_Length_hunt, const unsigned char* in_pData_time, const int in_Length_time, const unsigned char* in_pData_complete, const int in_Length_complete)> CPCQuestEvent::_AsyncDBComplete_LoadQuestEvent(SERVER, "CPCQuestEvent::AsyncDBComplete_LoadQuestEvent");
bool CPCQuestEvent::AsyncDBComplete_LoadQuestEvent(const unsigned char* in_pData_quest, const int in_Length_quest, const unsigned char* in_pData_hunt, const int in_Length_hunt, const unsigned char* in_pData_time, const int in_Length_time, const unsigned char* in_pData_complete, const int in_Length_complete) // line 175
{
	return (this->*_AsyncDBComplete_LoadQuestEvent)(in_pData_quest, in_Length_quest, in_pData_hunt, in_Length_hunt, in_pData_time, in_Length_time, in_pData_complete, in_Length_complete);

	//TODO
}


hook_method<int (CPCQuestEvent::*)(unsigned char* buff, int maxSize)> CPCQuestEvent::_Save_QuestInfo(SERVER, "CPCQuestEvent::Save_QuestInfo");
int CPCQuestEvent::Save_QuestInfo(unsigned char* buff, int maxSize) // line 491
{
	return (this->*_Save_QuestInfo)(buff, maxSize);

	//TODO
}


hook_method<int (CPCQuestEvent::*)(unsigned char* buff, int maxSize)> CPCQuestEvent::_Save_CompleteQuest(SERVER, "CPCQuestEvent::Save_CompleteQuest");
int CPCQuestEvent::Save_CompleteQuest(unsigned char* buff, int maxSize) // line 572
{
	return (this->*_Save_CompleteQuest)(buff, maxSize);

	//TODO
}


hook_method<int (CPCQuestEvent::*)(unsigned char* buff, int maxSize)> CPCQuestEvent::_Save_Quest_Hunt(SERVER, "CPCQuestEvent::Save_Quest_Hunt");
int CPCQuestEvent::Save_Quest_Hunt(unsigned char* buff, int maxSize) // line 520
{
	return (this->*_Save_Quest_Hunt)(buff, maxSize);

	//TODO
}


hook_method<int (CPCQuestEvent::*)(unsigned char* buff, int maxSize)> CPCQuestEvent::_Save_Quest_Time(SERVER, "CPCQuestEvent::Save_Quest_Time");
int CPCQuestEvent::Save_Quest_Time(unsigned char* buff, int maxSize) // line 546
{
	return (this->*_Save_Quest_Time)(buff, maxSize);

	//TODO
}


hook_method<int (CPCQuestEvent::*)(int msg, int par1, int par2)> CPCQuestEvent::_OnMessage(SERVER, "CPCQuestEvent::OnMessage");
int CPCQuestEvent::OnMessage(int msg, int par1, int par2) // line 662
{
	return (this->*_OnMessage)(msg, par1, par2);

	//TODO
}


void CPCQuestEvent::UpdateMission_Hunt(unsigned long mobGID) // line 966
{
	if( mobGID <= 0 )
		return;

	mystd::list<int> identList;
	if( m_huntIndex.CPCHuntIndex::GetHuntIdentList(mobGID, identList) <= 0 )
		return;

	char temp[10000] = {};
	int count = 0;

	PACKET_MOB_HUNTING* p = (PACKET_MOB_HUNTING*)temp;
	while( identList.size() != 0 )
	{
		m_isUpdateData = true;

		int huntId = identList.front();
		identList.pop_front();
		if( huntId <= 0 )
			continue;

		TMISSION_MAP::iterator it = m_huntMap.find(huntId);
		if( it == m_huntMap.end() )
			continue;

		CMission_Hunt* hunt = it->second;
		if( hunt == 0 )
			continue;

		hunt->CMission_Hunt::PlusOneCount();
		if( hunt->CMission_Hunt::GetCompleteHunting() )
			m_huntIndex.CPCHuntIndex::EraseHuntIdent(mobGID, huntId);

		p->questID = hunt->CMission_Hunt::GetQuestID();
		p->mobGID = hunt->CMission_Hunt::GetMobGID();
		p->count = hunt->CMission_Hunt::GetCount();

		++p;
		++count;
	}

	PACKET_ZC_UPDATE_MISSION_HUNT packet;
	packet.PacketType = HEADER_ZC_UPDATE_MISSION_HUNT;
	packet.PacketLength = sizeof(PACKET_ZC_UPDATE_MISSION_HUNT) + count * sizeof(PACKET_MOB_HUNTING);
	packet.count = count;

	if( m_owner != NULL )
	{
		m_owner->CPC::Send(sizeof(packet), (char*)&packet);
		if( count > 0 )
			m_owner->CPC::Send(packet.PacketLength - sizeof(packet), (char*)p);
	}
}


void CPCQuestEvent::SetUpdateData() // line ???
{
	m_isUpdateData = true;
}


bool CPCQuestEvent::GetUpdateData() // line ???
{
	return m_isUpdateData;
}
