#include "NpcServer/NpcObj.h"
#include "NpcServer/NpcSvr.h"
#include "globals.hpp"


CNpc::CNpc() // 9-11
{
	this->CNpc::Clear();
}


CNpc::~CNpc() // 14-15
{
}


void CNpc::Clear() // 18-40
{
	m_type = 2;

	m_name = "";
	m_id = 0;
	m_actCount = 0;

	for( int i = 0; i < 50; ++i )
	{
		m_actionScriptAction[i] = 0;
		m_actionScriptPos[i] = 0;
		m_actionScriptOnTimerActIdx[i] = 0;
		memset(&m_actionScriptParam[i], 0, sizeof(m_actionScriptParam[i]));
	}

	for( int i = 0; i < 16; ++i )
	{
		m_param[i] = 0;
		memset(m_ParamName[i], '\0', sizeof(m_ParamName[i]));
	}

	m_baseTime = 0;
	m_onTimerActNo = 0;
	m_timerEventNo = 0;
	m_onTimerActIdx = 0;
}


int CNpc::GetId() // line ???
{
	return m_id;
}


int CNpc::GetType() // line ???
{
	return m_type;
}


char* CNpc::GetName() // line ???
{
	return (char*)m_name.c_str();
}


void CNpc::SetInfo(int id, const NpcSvrNpcInfo* npcInfo) // line 43-57
{
	m_id = id;
	m_type = npcInfo->type;
	m_name = ( npcInfo->name != NULL ) ? npcInfo->name : "";
	m_npcType = npcInfo->npcType;
	strcpy(m_mapName, npcInfo->zone);
}


void CNpc::OnTimer() // line 180-194
{
	if( m_onTimerActIdx < m_onTimerActNo )
	{
		int act = m_actionScriptOnTimerActIdx[m_onTimerActIdx];
		int num = m_actionScriptParam[act].TokenData::GetNum();
		m_timerEventNo = g_npcSvr->CNpcSvr::RunEvent(0, m_id, act + 1, m_baseTime + num, false);
		++m_onTimerActIdx;
	}
	else
	{
		m_timerEventNo = 0;
	}
}


void CNpc::PauseTimer() // line 197-204
{
	if( m_timerEventNo != 0 )
	{
		g_npcSvr->CNpcSvr::CancelEvent(m_timerEventNo);
		m_timerEventNo = 0;
		m_onTimerActIdx = m_onTimerActNo;
	}
	else
	{
		m_onTimerActIdx = m_onTimerActNo;
	}
}


void CNpc::SetOnInit(bool b) // line ???
{
	m_OnInit = b;
}


char* CNpc::GetMapName() // line ???
{
	return m_mapName;
}
