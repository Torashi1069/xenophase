#include "SkillScriptHandler.h"
#include "SkillTypeInfo2.h"
#include "SkillTypeInfoMgr.h"
#include "ZoneProcess.h"


CSkillScriptHandler::CSkillScriptHandler()
: m_skillTypeInfo(NULL), m_isError(false), m_eventCase(0)
{
	m_interpreter.CInterpreter::RegisterHandler(this);
}


bool CSkillScriptHandler::Run(CBinBuf* binBuf)
{
	m_interpreter.CInterpreter::Scan(binBuf, 0);

	while( m_interpreter.CInterpreter::Proc() )
		;

	return ( m_isError != true );
}


void CSkillScriptHandler::EventLog(char* str, ...)
{
	va_list va;
	va_start(va, str);

	char buf[1024];
	vsprintf(buf, str, va);

	MessageBoxA(NULL, buf, "SkillSpecial.sc ERROR", MB_OK);
}


bool CSkillScriptHandler::IsDuplicate(int func)
{
	std::map<unsigned long,void*>::iterator iter = m_skillTypeInfo->m_infoMap.find(func);
	return ( iter != m_skillTypeInfo->m_infoMap.end() );
}


bool CSkillScriptHandler::OnFunc(int func, std::deque<TokenData>& parm, TokenData& ret)
{
	if( func == FUNC_SETSKILL )
	{
		int SKID = parm[0].TokenData::GetNum();
		if( this->CSkillScriptHandler::FuncSetSkill(SKID) )
			return true;

		m_isError = true;
		return false;
	}

	if( m_skillTypeInfo == NULL )
	{
		this->EventLog("No Skill");

		m_isError = true;
		return false;
	}

	switch( func )
	{
	case FUNC_ONUSE:
	{
		if( this->CSkillScriptHandler::FuncOnEvent(func) )
			return true;
	}
	break;
	case FUNC_ONSUCCESS:
	{
		if( this->CSkillScriptHandler::FuncOnEvent(func) )
			return true;
	}
	break;
	case FUNC_RETURN:
	{
		m_eventCase = 0;
		return true;
	}
	break;
	case FUNC_ONINIT:
	{
		return true;
	}
	break;
	case FUNC_SKILLTYPE:
	{
		int type = parm[0].TokenData::GetNum();
		m_skillTypeInfo->CSkillTypeInfo::SetType(type);
		return true;
	}
	break;
	case FUNC_SKILLMAXLV:
	{
		int level = parm[0].TokenData::GetNum();
		m_skillTypeInfo->CSkillTypeInfo2::SetMaxLevel(level);
		return true;
	}
	break;
	case FUNC_SKILLPATTERN:
	{
		int pattern = parm[0].TokenData::GetNum();
		m_skillTypeInfo->CSkillTypeInfo::SetPattern(pattern);
		return true;
	}
	break;
	case FUNC_SKILLSPLASH:
	{
		if( this->CSkillScriptHandler::FuncSkillSplash(parm) )
			return true;
	}
	break;
	case FUNC_SKILLPREDELAYTIME:
	{
		if( m_skillTypeInfo->GetVersion() == 2 )
		{
			for( size_t i = 0; i < 10 && i < parm.size(); ++i )
				parm[i].num *= 1000;

			if( this->CSkillScriptHandler::FuncSkillSetInfo(parm, &CSkillTypeInfo::SetCastFixedDelay) )
				return true;

			break;
		}
	}
//	break; //FIXME: unintended fall-through?
	case FUNC_SKILLPOSTDELAYTIME:
	{
		if( m_skillTypeInfo->GetVersion() == 2 )
		{
			for( size_t i = 0; i < 10 && i < parm.size(); ++i )
				parm[i].num *= 1000;

			if( this->CSkillScriptHandler::FuncSkillSetInfo(parm, &CSkillTypeInfo::SetGlobalPostDelay) )
				return true;

			break;
		}
	}
//	break; //FIXME: unintended fall-through?
	case FUNC_SKILLHITPERCENT:
	case FUNC_SKILLATKPERCENT:
	case FUNC_SKILLDATA1:
	case FUNC_SKILLDATA2:
	case FUNC_SKILLRANGE:
	case FUNC_SKILLSP:
	case FUNC_SKILLDATA3:
	case FUNC_SKILLDATA4:
	case FUNC_SKILLDATA5:
	case FUNC_SKILLDATA6:
	{
		if( this->CSkillScriptHandler::FuncSkillCommonIntValue(func, parm) )
			return true;
	}
	break;
	case FUNC_SKILLDATASTRING:
	{
		if( this->CSkillScriptHandler::FuncSkillStringValue(parm) )
			return true;
	}
	break;
	case FUNC_SKILLFLAG:
	{
		for( size_t i = 0; i < parm.size(); ++i )
		{
			unsigned long flag = parm[i].TokenData::GetNum();
			m_skillTypeInfo->CSkillTypeInfo::SetFlag(flag);
		}
		return true;
	}
	break;
	case FUNC_SKILLPROPERTY:
	{
		unsigned long property = parm[0].TokenData::GetNum();
		m_skillTypeInfo->SetProperty(property);
		return true;
	}
	break;
	case FUNC_SKILLEVENT:
	{
		m_skillTypeInfo->CSkillTypeInfo::SetEventSkill(TRUE);
		return true;
	}
	break;
	case FUNC_SKILLCASTFIXEDDELAY:
	{
		if( this->CSkillScriptHandler::FuncSkillSetInfo(parm, &CSkillTypeInfo::SetCastFixedDelay) )
			return true;
	}
//	break; //FIXME: unintended fall-through?
	case FUNC_SKILLCASTSTATDELAY:
	{
		if( this->CSkillScriptHandler::FuncSkillSetInfo(parm, &CSkillTypeInfo::SetCastStatDelay) )
			return true;
	}
//	break; //FIXME: unintended fall-through?
	case FUNC_SKILLGLOBALPOSTDELAY:
	{
		if( this->CSkillScriptHandler::FuncSkillSetInfo(parm, &CSkillTypeInfo::SetGlobalPostDelay) )
			return true;
	}
//	break; //FIXME: unintended fall-through?
	case FUNC_SKILLSINGLEPOSTDELAY:
	{
		if( this->CSkillScriptHandler::FuncSkillSetInfo(parm, &CSkillTypeInfo::SetSinglePostDelay) )
			return true;
	}
//	break; //FIXME: unintended fall-through?
	case FUNC_SKILLHANDICAP:
	{
		if( this->CSkillScriptHandler::FuncSkillHandicap(parm) )
			return true;
	}
	break;
	case FUNC_SKILLKNOCKBACK:
	{
		if( this->CSkillScriptHandler::FuncSkillKnockBack(parm) )
			return true;
	}
	break;
	case FUNC_SKILLNODAMAGE:
	{
		if( this->CSkillScriptHandler::FuncSkillNoDamage() )
			return true;
	}
	break;
	case FUNC_SKILLRESETHANDICAP:
	{
		if( this->CSkillScriptHandler::FuncSkillResetHandicap(parm) )
			return true;
	}
	break;
	case FUNC_SKILLDRAINHP:
	{
		if( this->CSkillScriptHandler::FuncSkillEventIntValue(func, parm, "SkillDrainHP") )
			return true;
	}
	break;
	case FUNC_SKILLDRAINSP:
	{
		if( this->CSkillScriptHandler::FuncSkillEventIntValue(func, parm, "SkillDrainSP") )
			return true;
	}
	break;
	};

	// error
	m_isError = true;
	return false;
}


void* CSkillScriptHandler::GetEventCase()
{
	if( m_eventCase == 0 )
	{
		this->EventLog("SkillName[%s], OnUse / OnSuccess", m_skillTypeInfo->CSkillTypeInfo::GetName());
		return NULL;
	}

	std::map<unsigned long,void*>::iterator iter = m_skillTypeInfo->m_infoMap.find(m_eventCase);
	if( iter == m_skillTypeInfo->m_infoMap.end() )
	{
		this->EventLog("SkillName[%s], SetHandicap, Need Event", m_skillTypeInfo->CSkillTypeInfo::GetName());
		return NULL;
	}

	return iter->second;
}


bool CSkillScriptHandler::FuncSetSkill(int SKID)
{
	m_skillTypeInfo = (CSkillTypeInfo2*)g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( m_skillTypeInfo == NULL || m_skillTypeInfo->GetVersion() != 2 )
	{
		m_skillTypeInfo = NULL;
		this->EventLog("FUNC_SETSKILL, Invalid Skill ID [%d]", SKID);
		return false;
	}

	return true;
}


bool CSkillScriptHandler::FuncOnEvent(int event)
{
	if( this->CSkillScriptHandler::IsDuplicate(event) == true )
	{
		this->EventLog("SkillName[%s], Check OnUse, OnSuccess", m_skillTypeInfo->CSkillTypeInfo::GetName());
		return false;
	}

	STRUCT_SK_EVENT* temp = new STRUCT_SK_EVENT;

	m_skillTypeInfo->m_infoMap[event] = temp;
	m_eventCase = event;
	return true;
}


bool CSkillScriptHandler::FuncSkillSplash(std::deque<TokenData>& parm)
{
	if( this->CSkillScriptHandler::IsDuplicate(FUNC_SKILLSPLASH) == true )
	{
		this->EventLog("SkillName[%s], Duplicate Splash\n", m_skillTypeInfo->CSkillTypeInfo::GetName());
		return false;
	}

	STRUCT_SK_SPLASH* temp = new STRUCT_SK_SPLASH;
	memset(temp, 0, sizeof(*temp));

	temp->shape = parm[0].TokenData::GetNum();
	for( size_t i = 1; i < parm.size() && i <= countof(temp->range); ++i )
		temp->range[i - 1] = parm[i].TokenData::GetNum();

	m_skillTypeInfo->m_infoMap[FUNC_SKILLSPLASH] = temp;
	return true;
}


bool CSkillScriptHandler::FuncSkillCommonIntValue(int func, std::deque<TokenData>& parm)
{
	if( this->CSkillScriptHandler::IsDuplicate(func) == true )
	{
		this->EventLog("SkillName[%s], Duplicate HitPercent or AtkPercent or Range or KnockBack\n", m_skillTypeInfo->CSkillTypeInfo::GetName());
		return true; //FIXME
	}

	STRUCT_SK_INTVALUE* temp = new STRUCT_SK_INTVALUE;
	memset(temp, 0, sizeof(*temp));

	for( size_t i = 0; i < parm.size() && i < countof(temp->value); ++i )
		temp->value[i] = parm[i].TokenData::GetNum();

	m_skillTypeInfo->m_infoMap[func] = temp;
	return true;
}


bool CSkillScriptHandler::FuncSkillHandicap(std::deque<TokenData>& parm)
{
	STRUCT_SK_EVENT* event = (STRUCT_SK_EVENT*)this->CSkillScriptHandler::GetEventCase();
	if( event == NULL )
		return false;

	std::map<unsigned long,void*>::iterator iter = event->infoMap.find(FUNC_SKILLHANDICAP);
	if( iter != event->infoMap.end() )
	{
		this->EventLog("SkillName[%s], Duplicate SkillHandicap", m_skillTypeInfo->CSkillTypeInfo::GetName());
		return false;
	}

	STRUCT_SK_HANDICAP* handicap = new STRUCT_SK_HANDICAP;
	memset(handicap, 0, sizeof(*handicap));

	event->infoMap[FUNC_SKILLHANDICAP] = handicap;

	handicap->handicapType = parm[0].TokenData::GetNum();
	for( size_t i = 1, k = 0; i < parm.size() && i <= (size_t)m_skillTypeInfo->GetMaxLevel(); ++i, ++k )
		handicap->percent[k] = parm[i].TokenData::GetNum();

	for( size_t i = m_skillTypeInfo->GetMaxLevel() + 1, k = 0; i < parm.size(); ++i, ++k )
		handicap->time[k] = parm[i].TokenData::GetNum();

	return true;
}


bool CSkillScriptHandler::FuncSkillKnockBack(std::deque<TokenData>& parm)
{
	STRUCT_SK_EVENT* event = (STRUCT_SK_EVENT*)this->CSkillScriptHandler::GetEventCase();
	if( event == NULL )
		return false;

	std::map<unsigned long,void*>::iterator iter = event->infoMap.find(FUNC_SKILLKNOCKBACK);
	if( iter != event->infoMap.end() )
	{
		this->EventLog("SkillName[%s], Duplicate SkillKnockBack", m_skillTypeInfo->CSkillTypeInfo::GetName());
		return false;
	}

	STRUCT_SK_INTVALUE* temp = new STRUCT_SK_INTVALUE;
	memset(temp, 0, sizeof(*temp));

	event->infoMap[FUNC_SKILLKNOCKBACK] = temp;

	for( size_t i = 0; i < parm.size() && i < countof(temp->value); ++i )
		temp->value[i] = parm[i].TokenData::GetNum();

	return true;
}


bool CSkillScriptHandler::FuncSkillNoDamage()
{
	if( m_eventCase != FUNC_ONUSE )
	{
		this->EventLog("SkillNoDamage, Need OnUse:");
		return false;
	}

	STRUCT_SK_EVENT* event = (STRUCT_SK_EVENT*)this->CSkillScriptHandler::GetEventCase();
	if( event == NULL )
		return false;

	event->infoMap[FUNC_SKILLNODAMAGE] = NULL;
	return true;
}


bool CSkillScriptHandler::FuncSkillResetHandicap(std::deque<TokenData>& parm)
{
	STRUCT_SK_EVENT* event = (STRUCT_SK_EVENT*)this->CSkillScriptHandler::GetEventCase();
	if( event == NULL )
		return false;

	std::map<unsigned long,void*>::iterator iter = event->infoMap.find(FUNC_SKILLRESETHANDICAP);
	if( iter != event->infoMap.end() )
	{
		this->EventLog("SkillName[%s], Duplicate SkillResetHandicap", m_skillTypeInfo->CSkillTypeInfo::GetName());
		return false;
	}

	STRUCT_SK_INTVALUE* handicapTypes = new STRUCT_SK_INTVALUE;
	memset(handicapTypes, 0, sizeof(*handicapTypes));

	event->infoMap[FUNC_SKILLRESETHANDICAP] = handicapTypes;

	for( size_t i = 0; i < parm.size(); ++i )
		handicapTypes->value[i] = parm[i].TokenData::GetNum();

	return true;
}


bool CSkillScriptHandler::FuncSkillEventIntValue(int func, std::deque<TokenData>& parm, const char* errorMsg)
{
	STRUCT_SK_EVENT* event = (STRUCT_SK_EVENT*)this->CSkillScriptHandler::GetEventCase();
	if( event == NULL )
		return false;

	std::map<unsigned long,void*>::iterator iter = event->infoMap.find(func);
	if( iter != event->infoMap.end() )
	{
		if( errorMsg != NULL )
			this->EventLog("SkillName[%s], Duplicate %s", m_skillTypeInfo->CSkillTypeInfo::GetName(), errorMsg);
		else
			this->EventLog("SkillName[%s], Duplicate Error", m_skillTypeInfo->CSkillTypeInfo::GetName());
		return false;
	}

	STRUCT_SK_INTVALUE* temp = new STRUCT_SK_INTVALUE;
	memset(temp, 0, sizeof(*temp));

	event->infoMap[func] = temp;

	for( size_t i = 0; i < parm.size() && i < countof(temp->value); ++i )
		temp->value[i] = parm[i].TokenData::GetNum();

	return true;
}


bool CSkillScriptHandler::FuncSkillSetInfo(std::deque<TokenData>& parm, void (CSkillTypeInfo::* func)(short skLevel, int time))
{
	int time = 0;
	for( size_t i = 1; i <= 10; ++i )
	{
		if( i <= parm.size() )
			time = parm[i - 1].TokenData::GetNum();

		(m_skillTypeInfo->*func)(i, time);
	}

	return true;
}


bool CSkillScriptHandler::FuncSkillStringValue(std::deque<TokenData>& parm)
{
	if( this->CSkillScriptHandler::IsDuplicate(FUNC_SKILLDATASTRING) == true )
	{
		this->EventLog("SkillName[%s], SkillDataString\n", m_skillTypeInfo->CSkillTypeInfo::GetName());
		return true; //FIXME
	}

	STRUCT_SK_STRINGVALUE* temp = new STRUCT_SK_STRINGVALUE;

	for( size_t i = 0; i < parm.size() && i < countof(temp->value); ++i )
		temp->value[i] = parm[i].TokenData::GetStr();

	m_skillTypeInfo->m_infoMap[FUNC_SKILLDATASTRING] = temp;
	return true;
}
