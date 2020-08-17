#include "enum.hpp"
#include "MapTypeProperty.h"


CMapTypeProperty::CMapTypeProperty(const int in_mapType) : m_mapType(in_mapType) // line 42
{
	m_MAPPROPERTY_NORMAL_DAMAGE = 100;
	m_MAPPROPERTY_RANGE_DAMAGE = 100;
	m_MAPPROPERTY_ALL_SKILL_DAMAGE = 100;
	m_MAPPROPERTY_PK = 0;
	m_MAPPROPERTY_TELEPORT = 0;
	m_MAPPROPERTY_NOTREMEMBER = 0;
	m_MAPPROPERTY_ITEMDROP = 0;
	m_MAPPROPERTY_EXP = 0;
	m_MAPPROPERTY_DISCONNECT_NOTREMEMBER = 0;
	m_MAPPROPERTY_CALLMONSTER = 0;
	m_MAPPROPERTY_PARTY = 0;
	m_MAPPROPERTY_GUILD = 0;
	m_MAPPROPERTY_SIEGE = 0;
	m_MAPPROPERTY_PKSERVER = 0;
	m_MAPPROPERTY_PVPSERVER = 0;
	m_MAPPROPERTY_DENYSKILL = 0;
	m_MAPPROPERTY_TURBOTRACK = 0;
	m_MAPPROPERTY_DENY_BUTTERFLY = 0;
	m_MAPPROPERTY_USE_SIMPLE_EFFECT = 0;
	m_MAPPROPERTY_DISABLE_LOCKON = 0;
	m_MAPPROPERTY_COUNT_PK = 0;
	m_MAPPROPERTY_NO_PARTY_FORMATION = 0;
	m_MAPPROPERTY_BATTLEFIELD = 0;
	m_MAPPROPERTY_HIDING_DAMAGE = 0;
	m_MAPPROPERTY_DISABLE_KNOCKBACK = 0;
	m_MAPPROPERTY_LONG_INSUPERABLE_TIME = 0;
	m_MAPPROPERTY_NO_CHATTING = 0;
	m_MAPPROPERTY_NAMED_BOOTY = 0;
	m_MAPPROPERTY_SIEGETIME_VERSION = 0;
	m_MAPPROPERTY_GOTOTOWN = 0;
	m_bOK = true;
}


CMapTypeProperty::~CMapTypeProperty(void) // line 48
{
}


hook_method<bool (CMapTypeProperty::*)(const int in_SKID, const CMapTypeProperty::tagSelectedObject in_SelectedObject)> CMapTypeProperty::_AddBlockSkill(SERVER, "CMapTypeProperty::AddBlockSkill");
bool CMapTypeProperty::AddBlockSkill(const int in_SKID, const CMapTypeProperty::tagSelectedObject in_SelectedObject) // line 54
{
	return (this->*_AddBlockSkill)(in_SKID, in_SelectedObject);

	//TODO
}


hook_method<bool (CMapTypeProperty::*)(const int in_ITID)> CMapTypeProperty::_AddBlockItem(SERVER, "CMapTypeProperty::AddBlockItem");
bool CMapTypeProperty::AddBlockItem(const int in_ITID) // line 62
{
	return (this->*_AddBlockItem)(in_ITID);

	//TODO
}


hook_method<bool (CMapTypeProperty::*)(const mystd::string in_PropertyName, const bool in_bEnable)> CMapTypeProperty::_AddProperty(SERVER, "CMapTypeProperty::AddProperty");
bool CMapTypeProperty::AddProperty(const mystd::string in_PropertyName, const bool in_bEnable) // line 94
{
	return (this->*_AddProperty)(in_PropertyName, in_bEnable);

	//TODO
}


hook_method<bool (CMapTypeProperty::*)(const mystd::string in_PropertyName, const int in_Value)> CMapTypeProperty::_AddPropertyValue(SERVER, "CMapTypeProperty::AddPropertyValue");
bool CMapTypeProperty::AddPropertyValue(const mystd::string in_PropertyName, const int in_Value) // line 229
{
	return (this->*_AddPropertyValue)(in_PropertyName, in_Value);

	//TODO
}


hook_method<bool (CMapTypeProperty::*)(const int in_SKID, const int in_Percent)> CMapTypeProperty::_AddTrapDurationPercent(SERVER, "CMapTypeProperty::AddTrapDurationPercent");
bool CMapTypeProperty::AddTrapDurationPercent(const int in_SKID, const int in_Percent) // line 247
{
	return (this->*_AddTrapDurationPercent)(in_SKID, in_Percent);

	//TODO
}


hook_method<bool (CMapTypeProperty::*)(const int in_SKID, const int in_Percent)> CMapTypeProperty::_AddSkillDamagePercent(SERVER, "CMapTypeProperty::AddSkillDamagePercent");
bool CMapTypeProperty::AddSkillDamagePercent(const int in_SKID, const int in_Percent) // line 262
{
	return (this->*_AddSkillDamagePercent)(in_SKID, in_Percent);

	//TODO
}


hook_method<bool (CMapTypeProperty::*)(const int in_ITID)> CMapTypeProperty::_AddBlockEquipItem(SERVER, "CMapTypeProperty::AddBlockEquipItem");
bool CMapTypeProperty::AddBlockEquipItem(const int in_ITID) // line 278
{
	return (this->*_AddBlockEquipItem)(in_ITID);

	//TODO
}


hook_method<bool (CMapTypeProperty::*)(const int in_BuffID)> CMapTypeProperty::_AddBlockBuff(SERVER, "CMapTypeProperty::AddBlockBuff");
bool CMapTypeProperty::AddBlockBuff(const int in_BuffID) // line 291
{
	return (this->*_AddBlockBuff)(in_BuffID);

	//TODO
}


//hook_method<bool (CMapTypeProperty::*)(void)> CMapTypeProperty::_isOK(SERVER, "CMapTypeProperty::isOK");
bool CMapTypeProperty::isOK(void) // line ???
{
//	return (this->*_isOK)();

	return m_bOK;
}


hook_method<bool (CMapTypeProperty::*)(const int in_SKID, const int in_ObjectType)> CMapTypeProperty::_isBlockSkill(SERVER, "CMapTypeProperty::isBlockSkill");
bool CMapTypeProperty::isBlockSkill(const int in_SKID, const int in_ObjectType) // line 74
{
	return (this->*_isBlockSkill)(in_SKID, in_ObjectType);

	//TODO
}


hook_method<bool (CMapTypeProperty::*)(const int in_ITID)> CMapTypeProperty::_isBlockItem(SERVER, "CMapTypeProperty::isBlockItem");
bool CMapTypeProperty::isBlockItem(const int in_ITID) // line 68
{
	return (this->*_isBlockItem)(in_ITID);

	//TODO
}


hook_method<bool (CMapTypeProperty::*)(const int in_ITID)> CMapTypeProperty::_isBlockEquipItem(SERVER, "CMapTypeProperty::isBlockEquipItem");
bool CMapTypeProperty::isBlockEquipItem(const int in_ITID) // line 284
{
	return (this->*_isBlockEquipItem)(in_ITID);

	//TODO
}


hook_method<bool (CMapTypeProperty::*)(const int in_BuffID)> CMapTypeProperty::_isBlockBuff(SERVER, "CMapTypeProperty::isBlockBuff");
bool CMapTypeProperty::isBlockBuff(const int in_BuffID) // line 297
{
	return (this->*_isBlockBuff)(in_BuffID);

	mystd::vector<int>::const_iterator it;
	for( it = m_BlockBuffContainer.begin(); it != m_BlockBuffContainer.end(); ++it )
		if( *it == in_BuffID )
			break;

	return ( it != m_BlockBuffContainer.end() );
}


hook_method<int (CMapTypeProperty::*)(int property)> CMapTypeProperty::_IsItPossible(SERVER, "CMapTypeProperty::IsItPossible");
int CMapTypeProperty::IsItPossible(int property) // line 158
{
	return (this->*_IsItPossible)(property);

	switch( property )
	{
	case MAPPROPERTY_PK                    : return m_MAPPROPERTY_PK;
	case MAPPROPERTY_TELEPORT              : return m_MAPPROPERTY_TELEPORT;
	case MAPPROPERTY_NOTREMEMBER           : return m_MAPPROPERTY_NOTREMEMBER;
	case MAPPROPERTY_ITEMDROP              : return m_MAPPROPERTY_ITEMDROP;
	case MAPPROPERTY_EXP                   : return m_MAPPROPERTY_EXP;
	case MAPPROPERTY_DISCONNECT_NOTREMEMBER: return m_MAPPROPERTY_DISCONNECT_NOTREMEMBER;
	case MAPPROPERTY_CALLMONSTER           : return m_MAPPROPERTY_CALLMONSTER;
	case MAPPROPERTY_PARTY                 : return m_MAPPROPERTY_PARTY;
	case MAPPROPERTY_GUILD                 : return m_MAPPROPERTY_GUILD;
	case MAPPROPERTY_SIEGE                 : return m_MAPPROPERTY_SIEGE;
	case MAPPROPERTY_PKSERVER              : return m_MAPPROPERTY_PKSERVER;
	case MAPPROPERTY_PVPSERVER             : return m_MAPPROPERTY_PVPSERVER;
	case MAPPROPERTY_DENYSKILL             : return m_MAPPROPERTY_DENYSKILL;
	case MAPPROPERTY_TURBOTRACK            : return m_MAPPROPERTY_TURBOTRACK;
	case MAPPROPERTY_DENY_BUTTERFLY        : return m_MAPPROPERTY_DENY_BUTTERFLY;
	case MAPPROPERTY_USE_SIMPLE_EFFECT     : return m_MAPPROPERTY_USE_SIMPLE_EFFECT;
	case MAPPROPERTY_DISABLE_LOCKON        : return m_MAPPROPERTY_DISABLE_LOCKON;
	case MAPPROPERTY_COUNT_PK              : return m_MAPPROPERTY_COUNT_PK;
	case MAPPROPERTY_NO_PARTY_FORMATION    : return m_MAPPROPERTY_NO_PARTY_FORMATION;
	case MAPPROPERTY_BATTLEFIELD           : return m_MAPPROPERTY_BATTLEFIELD;
	case MAPPROPERTY_HIDING_DAMAGE         : return m_MAPPROPERTY_HIDING_DAMAGE;
	case MAPPROPERTY_DISABLE_KNOCKBACK     : return m_MAPPROPERTY_DISABLE_KNOCKBACK;
	case MAPPROPERTY_LONG_INSUPERABLE_TIME : return m_MAPPROPERTY_LONG_INSUPERABLE_TIME;
	case MAPPROPERTY_NAMED_BOOTY           : return m_MAPPROPERTY_NAMED_BOOTY;
	case MAPPROPERTY_SIEGETIME_VERSION     : return m_MAPPROPERTY_SIEGETIME_VERSION;
	case MAPPROPERTY_GOTOTOWN              : return m_MAPPROPERTY_GOTOTOWN;
	case MAPPROPERTY_NORMAL_DAMAGE         : return m_MAPPROPERTY_NORMAL_DAMAGE;
	case MAPPROPERTY_RANGE_DAMAGE          : return m_MAPPROPERTY_RANGE_DAMAGE;
	case MAPPROPERTY_BLOCK_EQUIPITEM       : return m_BlockEquipItemContainer.size();
	case MAPPROPERTY_BLOCK_BUFF            : return m_BlockBuffContainer.size();
	case MAPPROPERTY_NO_CHATTING           : return m_MAPPROPERTY_NO_CHATTING;
	default                                : return 0;
	}
}


hook_method<int (CMapTypeProperty::*)(const int in_SKID)> CMapTypeProperty::_GetTrapDurationPercent(SERVER, "CMapTypeProperty::GetTrapDurationPercent");
int CMapTypeProperty::GetTrapDurationPercent(const int in_SKID) // line 254
{
	return (this->*_GetTrapDurationPercent)(in_SKID);

	//TODO
}


hook_method<int (CMapTypeProperty::*)(const int in_SKID)> CMapTypeProperty::_GetSkillDamagePercent(SERVER, "CMapTypeProperty::GetSkillDamagePercent");
int CMapTypeProperty::GetSkillDamagePercent(const int in_SKID) // line 269
{
	return (this->*_GetSkillDamagePercent)(in_SKID);

	//TODO
}


hook_method<void (CMapTypeProperty::*)(unsigned char* out_pArray, const int in_MaxLength)> CMapTypeProperty::_GetByteArray(SERVER, "CMapTypeProperty::GetByteArray");
void CMapTypeProperty::GetByteArray(unsigned char* out_pArray, const int in_MaxLength) // line 127
{
	return (this->*_GetByteArray)(out_pArray, in_MaxLength);

	//TODO
}
