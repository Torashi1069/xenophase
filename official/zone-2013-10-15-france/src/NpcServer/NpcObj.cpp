#include "NpcObj.h"
#include "ZoneProcess.h"
#include "NpcServer/NpcSvr.h"
#include "shared/NCriticalErrorLog.h"


CNpc::CNpc()
{
	this->CNpc::Clear();
}


CNpc::~CNpc()
{
}


void CNpc::Clear()
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
		memset(&m_ParamName[i], 0, sizeof(m_ParamName[i]));
	}

	m_baseTime = 0;
	m_onTimerActNo = 0;
	m_timerEventNo = 0;
	m_onTimerActIdx = 0;
}


void CNpc::SetInfo(int id, const NpcSvrNpcInfo* npcInfo)
{
	m_id = id;
	m_type = npcInfo->type;
	m_name = ( npcInfo->name != NULL ) ? npcInfo->name : "";
	m_npcType = npcInfo->npcType;
	if( npcInfo->zone != NULL )
		strcpy(m_mapName, npcInfo->zone);
}


int CNpc::SetActionScript(int action, int pos, std::deque<TokenData>& parm)
{
	if( m_actCount >= 50 )
		return 0;

	if( action == 5 )
	{
		m_actionScriptOnTimerActIdx[m_onTimerActNo] = m_actCount;
		++m_onTimerActNo;
	}

	m_actionScriptAction[m_actCount] = action;

	m_actionScriptPos[m_actCount] = pos;

	if( parm.size() != 0 )
		m_actionScriptParam[m_actCount] = parm[0];

	++m_actCount;
	return 1;
}


int CNpc::GetActionScriptPos(int index)
{
	if( index == 0 )
		return 0;

	int idx = index - 1;
	if( idx < 0 || idx >= m_actCount )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "OUT OF RANGE: GetActionScriptPos(%d)", idx);
		return 0;
	}

	return m_actionScriptPos[idx];
}


int CNpc::GetActionScriptIdx(int act, int nParam, char* strParam)
{
	for( int i = 0; i < m_actCount; ++i )
	{
		if( m_actionScriptAction[i] == act )
		{
			if( strParam )
			{
				if( strcmp(m_actionScriptParam[i].TokenData::GetStr(), strParam) == 0 )
					return i + 1; // found.
			}
			else
			{
				if( nParam == 0 || m_actionScriptParam[i].TokenData::GetNum() == nParam )
					return i + 1; // found.
			}
		}
	}

	return 0; // not found.
}


int CNpc::GetLocalVarIdx(char* varName)
{
	for( int i = 0; i < 16; ++i )
		if( strcmp(varName, m_ParamName[i]) == 0 )
			return i; // found.

	return -1; // not found.
}


bool CNpc::SetLocalVarName(int slot, const char* name)
{
	if( strlen(name) > 100 || slot < 0 || slot >= 16 )
		return false;

	strcpy(m_ParamName[slot], name);
	return true;
}


void CNpc::InitTimer()
{
	this->CNpc::PauseTimer();
	m_onTimerActIdx = 0;
	m_baseTime = timeGetTime();
	this->CNpc::OnTimer();
}


void CNpc::OnTimer()
{
	if( m_onTimerActIdx >= m_onTimerActNo )
	{
		m_timerEventNo = 0;
	}
	else
	{
		int act = m_actionScriptOnTimerActIdx[m_onTimerActIdx];
		int time = m_actionScriptParam[m_actionScriptOnTimerActIdx[m_onTimerActIdx]].TokenData::GetNum();
		m_timerEventNo = g_npcSvr.CNpcSvr::RunEvent(0, m_id, act + 1, m_baseTime + time, false);
		++m_onTimerActIdx;
	}
}


void CNpc::PauseTimer()
{
	if( m_timerEventNo != 0 )
	{
		g_npcSvr.CNpcSvr::CancelEvent(m_timerEventNo);
		m_timerEventNo = 0;
	}

	m_onTimerActIdx = m_onTimerActNo;
}


void CNpc::AddTimer(unsigned long num)
{
	m_baseTime += num;
}

void CNpc::SubTimer(unsigned long num)
{
	m_baseTime -= num;
}


int CNpc::GetId()
{
	return m_id;
}


int CNpc::GetType()
{
	return m_type;
}


char* CNpc::GetName()
{
	return const_cast<char*>(m_name.c_str());
}


int CNpc::GetLocalVar(int idx)
{
	return m_param[idx];
}


char* CNpc::GetLocalVarName(int idx)
{
	if( idx < 0 || idx >= 16 )
		return NULL;

	return m_ParamName[idx];
}


void CNpc::IncLocalVar(int idx, int val)
{
	m_param[idx] += val;
	if( m_param[idx] < 0 )
		m_param[idx] = 0;
}


void CNpc::DecLocalVar(int idx, int val)
{
	m_param[idx] -= val;
	if( m_param[idx] < 0 )
		m_param[idx] = 0;
}


void CNpc::SetLocalVar(int idx, int val)
{
	m_param[idx] = val;
	if( m_param[idx] < 0 )
		m_param[idx] = 0;
}


bool CNpc::GetOnInit() const
{
	return m_OnInit;
}


void CNpc::SetOnInit(bool b)
{
	m_OnInit = b;
}


int CNpc::IsNpcType()
{
	return m_npcType;
}


char* CNpc::GetMapName()
{
	return m_mapName;
}
