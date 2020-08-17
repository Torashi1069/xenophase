#include "CharacterMgr.h"
#include "SkillScriptHandler.h"
#include "SkillTypeInfo2.h"
#include "SkillTypeInfoMgr.h"
#include "shared/NCriticalErrorLog.h"


static bool IsValidLevel(int level)
{
	return ( level >= 1 && level <= 10 );
}


CSkillTypeInfo2::CSkillTypeInfo2()
{
	m_maxLevel = 0;
}


CSkillTypeInfo2::~CSkillTypeInfo2()
{
	for( std::map<unsigned long,void*>::iterator iter = m_infoMap.begin(); iter != m_infoMap.end(); ++iter )
	{
		if( iter->first == FUNC_ONUSE || iter->first == FUNC_ONSUCCESS )
		{
			STRUCT_SK_EVENT* ev = reinterpret_cast<STRUCT_SK_EVENT*>(iter->second);
			for( std::map<unsigned long,void*>::iterator iter2 = ev->infoMap.begin(); iter2 != ev->infoMap.end(); ++iter2 )
				delete iter2->second;
			//FIXME: check possible memleak on iter->second
		}
		else
		{
			delete iter->second;
		}
	}
}


void CSkillTypeInfo2::Init()
{
}


short CSkillTypeInfo2::GetVersion()
{
	return 2;
}


short CSkillTypeInfo2::GetMaxLevel()
{
	return m_maxLevel;
}


void CSkillTypeInfo2::SetMaxLevel(int level)
{
	m_maxLevel = level;
}


short CSkillTypeInfo2::GetAttackRange(int level)
{
	if( !IsValidLevel(level) )
		return m_attackRange;

	std::map<unsigned long,void*>::iterator iter = m_infoMap.find(FUNC_SKILLRANGE);
	if( iter == m_infoMap.end() )
		return m_attackRange;

	STRUCT_SK_INTVALUE* data = reinterpret_cast<STRUCT_SK_INTVALUE*>(iter->second);
	return data->value[level - 1];
}


int CSkillTypeInfo2::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)
{
	switch( MsgID )
	{
	case SM_USE_SKILL:
	{
		switch( m_type )
		{
		case SKILLTYPE_TOCHARACTER:
		case SKILLTYPE_TOME:
		case SKILLTYPE_TOALL:
		{
			MSG_TYPE4_FIVEDWORD data;
			data.data1 = 100;
			data.data2 = 100;
			data.data3 = 1;
			data.data4 = par3;
			data.data5 = skLevel;
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, sender, CM_ATTSKILL_TOCHAR22_1, receiver, targetID, (int)&data, 0);
		}
		break;
		case SKILLTYPE_TOGROUND:
		{
			MSG_TYPE5_SIXDWORD data;
			data.data1 = *(int*)(par3 + 0); //TODO
			data.data2 = *(int*)(par3 + 4); //TODO
			data.data3 = 1;
			data.data4 = 0;
			data.data5 = targetID;
			data.data6 = skLevel;
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, sender, CM_SKILL_GROUNDTYPE22_1, receiver, targetID, (int)&data, 0);
		}
		break;
		};
	}
	break;
	default:
	{
		this->CSkillTypeInfo::OnMsg(sender, receiver, MsgID, skLevel, targetID, par3, par4);
	}
	break;
	};

	return 0;
}


void* CSkillTypeInfo2::GetInfo(unsigned long tokenType) const
{
	std::map<unsigned long,void*>::const_iterator iter = m_infoMap.find(tokenType);
	if( iter == m_infoMap.end() )
	{
		if( tokenType >= FUNC_SKILLDATA1 && tokenType <= FUNC_SKILLDATA2 || tokenType >= FUNC_SKILLDATA3 && tokenType <= FUNC_SKILLDATA6 )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[critical error SkillSpecial.sc] SKID = %d SkillData%d", m_SKID, tokenType);
			static STRUCT_SK_INTVALUE defaultINTVALUE;
			return &defaultINTVALUE;
		}

		return NULL;
	}

	return iter->second;
}


int CSkillTypeInfo2::GetHitPercent(int level)
{
	if( !IsValidLevel(level) )
		return 100;
	
	STRUCT_SK_INTVALUE* data = reinterpret_cast<STRUCT_SK_INTVALUE*>(this->CSkillTypeInfo2::GetInfo(FUNC_SKILLHITPERCENT));
	if( data == NULL )
		return 100;

	return data->value[level - 1];
}


int CSkillTypeInfo2::GetATKPercent(int level) const
{
	if( !IsValidLevel(level) )
		return 100;
	
	STRUCT_SK_INTVALUE* data = reinterpret_cast<STRUCT_SK_INTVALUE*>(this->CSkillTypeInfo2::GetInfo(FUNC_SKILLATKPERCENT));
	if( data == NULL )
		return 100;

	return data->value[level - 1];
}


int CSkillTypeInfo2::GetData(int type, int level) const
{
	if( !IsValidLevel(level) )
		return 0;
	
	STRUCT_SK_INTVALUE* data = reinterpret_cast<STRUCT_SK_INTVALUE*>(this->CSkillTypeInfo2::GetInfo(type));
	if( data == NULL )
		return 0;

	return data->value[level - 1];
}


int CSkillTypeInfo2::GetSplashRange(int level)
{
	if( !IsValidLevel(level) )
		return 0;
	
	STRUCT_SK_SPLASH* data = reinterpret_cast<STRUCT_SK_SPLASH*>(this->CSkillTypeInfo2::GetInfo(FUNC_SKILLSPLASH));
	if( data == NULL )
		return 0;

	return data->range[level - 1];
}


void CSkillTypeInfo2::GetSplashRange(int level, int& halfWidth, int& height)
{
	halfWidth = 0;
	height    = 0;

	if( !IsValidLevel(level) )
		return;

	STRUCT_SK_SPLASH* data = reinterpret_cast<STRUCT_SK_SPLASH*>(this->CSkillTypeInfo2::GetInfo(FUNC_SKILLSPLASH));
	if( data == NULL )
		return;

	halfWidth = data->range[2 * (level - 1)];
	height    = data->range[2 * (level - 1) + 1];
}


short CSkillTypeInfo2::GetSPCost(short level)
{
	if( !IsValidLevel(level) )
		return 0;
	
	STRUCT_SK_INTVALUE* data = reinterpret_cast<STRUCT_SK_INTVALUE*>(this->CSkillTypeInfo2::GetInfo(FUNC_SKILLSP));
	if( data == NULL )
		return 0;

	return data->value[level - 1];
}


short CSkillTypeInfo2::GetPreDelayTime(short level)
{
	if( !IsValidLevel(level) )
		return 0;
	
	STRUCT_SK_INTVALUE* data = reinterpret_cast<STRUCT_SK_INTVALUE*>(this->CSkillTypeInfo2::GetInfo(FUNC_SKILLPREDELAYTIME));
	if( data == NULL )
		return 0;

	return 1000 * data->value[level - 1];
}


short CSkillTypeInfo2::GetPostDelayTM(short level)
{
	if( !IsValidLevel(level) )
		return 0;
	
	STRUCT_SK_INTVALUE* data = reinterpret_cast<STRUCT_SK_INTVALUE*>(this->CSkillTypeInfo2::GetInfo(FUNC_SKILLPOSTDELAYTIME));
	if( data == NULL )
		return 0;
	
	return 1000 * data->value[level - 1];
}
