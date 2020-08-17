#include "MapTypeProperty.h"
#include "shared/Client.h"
#include "shared/NCriticalErrorLog.h"


CMapTypeProperty::CMapTypeProperty(const int in_mapType)
: m_MAPPROPERTY_NORMAL_DAMAGE(100), m_MAPPROPERTY_RANGE_DAMAGE(100), m_MAPPROPERTY_ALL_SKILL_DAMAGE(100),
  m_MAPPROPERTY_PK(false), m_MAPPROPERTY_TELEPORT(false), m_MAPPROPERTY_NOTREMEMBER(false), m_MAPPROPERTY_ITEMDROP(false), m_MAPPROPERTY_EXP(false), m_MAPPROPERTY_DISCONNECT_NOTREMEMBER(false), m_MAPPROPERTY_CALLMONSTER(false), m_MAPPROPERTY_PARTY(false), m_MAPPROPERTY_GUILD(false), m_MAPPROPERTY_SIEGE(false), m_MAPPROPERTY_PKSERVER(false), m_MAPPROPERTY_PVPSERVER(false), m_MAPPROPERTY_DENYSKILL(false), m_MAPPROPERTY_TURBOTRACK(false), m_MAPPROPERTY_DENY_BUTTERFLY(false), m_MAPPROPERTY_USE_SIMPLE_EFFECT(false), m_MAPPROPERTY_DISABLE_LOCKON(false), m_MAPPROPERTY_COUNT_PK(false), m_MAPPROPERTY_NO_PARTY_FORMATION(false), m_MAPPROPERTY_BATTLEFIELD(false), m_MAPPROPERTY_HIDING_DAMAGE(false), m_MAPPROPERTY_DISABLE_KNOCKBACK(false), m_MAPPROPERTY_LONG_INSUPERABLE_TIME(false), m_MAPPROPERTY_NO_CHATTING(false), m_MAPPROPERTY_DISABLE_COSTUMEITEM(false), m_MAPPROPERTY_PREVENT_PARTY_MAKE(false), m_MAPPROPERTY_PREVENT_PARTY_JOIN(false), m_MAPPROPERTY_PREVENT_PARTY_LEAVE(false), m_MAPPROPERTY_PREVENT_PARTY_EXPEL(false), m_MAPPROPERTY_PREVENT_PARTY_MASTER_CHANGE(false),
  m_MAPPROPERTY_NAMED_BOOTY(0), m_MAPPROPERTY_SIEGETIME_VERSION(0), m_MAPPROPERTY_GOTOTOWN(0),
  m_mapType(in_mapType)
{
	m_bOK = true;
}


CMapTypeProperty::~CMapTypeProperty()
{
}


bool CMapTypeProperty::isOK() const
{
	return m_bOK;
}


bool CMapTypeProperty::AddBlockSkill(const int in_SKID, const tagSelectedObject in_SelectedObject)
{
	std::pair<BLOCKSKILL_CONTAINER_ITER,bool> ret = m_BlockSkillContainer.insert(std::pair<const int,tagSelectedObject>(in_SKID, in_SelectedObject));
	return ret.second;
}


bool CMapTypeProperty::AddBlockItem(const int in_ITID)
{
	m_BlockItemContainer.push_back(in_ITID);
	return true;
}


bool CMapTypeProperty::isBlockItem(const int in_ITID)
{
	BLOCKITEM_CONTAINER_ITER iter;
	for( iter = m_BlockItemContainer.begin(); iter != m_BlockItemContainer.end(); ++iter )
		if( *iter == in_ITID )
			break;

	return ( iter != m_BlockItemContainer.end() );
}


bool CMapTypeProperty::isBlockSkill(const int in_SKID, const int in_ObjectType)
{
	BLOCKSKILL_CONTAINER_ITER iter = m_BlockSkillContainer.find(in_SKID);
	if( iter == m_BlockSkillContainer.end() )
		return false;

	switch( in_ObjectType )
	{
	case PC_TYPE:         return ( iter->second.bPlayer != 0 );
	case NPC_MOB_TYPE:    return ( iter->second.bMonster != 0 );
	case NPC_HO_TYPE:     return ( iter->second.bHomun != 0 );
	case NPC_MERSOL_TYPE: return ( iter->second.bMercenary != 0 );
	default:
		return false;
	};
}


bool CMapTypeProperty::AddProperty(const std::string in_PropertyName, const bool in_bEnable)
{
	if     ( in_PropertyName == "PK"                          ) m_MAPPROPERTY_PK                          = in_bEnable;
	else if( in_PropertyName == "TELEPORT"                    ) m_MAPPROPERTY_TELEPORT                    = in_bEnable;
	else if( in_PropertyName == "NOTREMEMBER"                 ) m_MAPPROPERTY_NOTREMEMBER                 = in_bEnable;
	else if( in_PropertyName == "ITEMDROP"                    ) m_MAPPROPERTY_ITEMDROP                    = in_bEnable;
	else if( in_PropertyName == "EXP"                         ) m_MAPPROPERTY_EXP                         = in_bEnable;
	else if( in_PropertyName == "DISCONNECT_NOTREMEMBER"      ) m_MAPPROPERTY_DISCONNECT_NOTREMEMBER      = in_bEnable;
	else if( in_PropertyName == "CALLMONSTER"                 ) m_MAPPROPERTY_CALLMONSTER                 = in_bEnable;
	else if( in_PropertyName == "PARTY"                       ) m_MAPPROPERTY_PARTY                       = in_bEnable;
	else if( in_PropertyName == "GUILD"                       ) m_MAPPROPERTY_GUILD                       = in_bEnable;
	else if( in_PropertyName == "SIEGE"                       ) m_MAPPROPERTY_SIEGE                       = in_bEnable;
	else if( in_PropertyName == "PKSERVER"                    ) m_MAPPROPERTY_PKSERVER                    = in_bEnable;
	else if( in_PropertyName == "PVPSERVER"                   ) m_MAPPROPERTY_PVPSERVER                   = in_bEnable;
	else if( in_PropertyName == "DENYSKILL"                   ) m_MAPPROPERTY_DENYSKILL                   = in_bEnable;
	else if( in_PropertyName == "TURBOTRACK"                  ) m_MAPPROPERTY_TURBOTRACK                  = in_bEnable;
	else if( in_PropertyName == "DENY_BUTTERFLY"              ) m_MAPPROPERTY_DENY_BUTTERFLY              = in_bEnable;
	else if( in_PropertyName == "USE_SIMPLE_EFFECT"           ) m_MAPPROPERTY_USE_SIMPLE_EFFECT           = in_bEnable;
	else if( in_PropertyName == "DISABLE_LOCKON"              ) m_MAPPROPERTY_DISABLE_LOCKON              = in_bEnable;
	else if( in_PropertyName == "COUNT_PK"                    ) m_MAPPROPERTY_COUNT_PK                    = in_bEnable;
	else if( in_PropertyName == "NO_PARTY_FORMATION"          ) m_MAPPROPERTY_NO_PARTY_FORMATION          = in_bEnable;
	else if( in_PropertyName == "HIDING_DAMAGE"               ) m_MAPPROPERTY_HIDING_DAMAGE               = in_bEnable;
	else if( in_PropertyName == "DISABLE_KNOCKBACK"           ) m_MAPPROPERTY_DISABLE_KNOCKBACK           = in_bEnable;
	else if( in_PropertyName == "LONG_INSUPERABLE_TIME"       ) m_MAPPROPERTY_LONG_INSUPERABLE_TIME       = in_bEnable;
	else if( in_PropertyName == "BATTLEFIELD"                 ) m_MAPPROPERTY_BATTLEFIELD                 = in_bEnable;
	else if( in_PropertyName == "NO_CHATTING"                 ) m_MAPPROPERTY_NO_CHATTING                 = in_bEnable;
	else if( in_PropertyName == "DISABLE_COSTUMEITEM"         ) m_MAPPROPERTY_DISABLE_COSTUMEITEM         = in_bEnable;
	else if( in_PropertyName == "PREVENT_PARTY_MAKE"          ) m_MAPPROPERTY_PREVENT_PARTY_MAKE          = in_bEnable;
	else if( in_PropertyName == "PREVENT_PARTY_JOIN"          ) m_MAPPROPERTY_PREVENT_PARTY_JOIN          = in_bEnable;
	else if( in_PropertyName == "PREVENT_PARTY_LEAVE"         ) m_MAPPROPERTY_PREVENT_PARTY_LEAVE         = in_bEnable;
	else if( in_PropertyName == "PREVENT_PARTY_EXPEL"         ) m_MAPPROPERTY_PREVENT_PARTY_EXPEL         = in_bEnable;
	else if( in_PropertyName == "PREVENT_PARTY_MASTER_CHANGE" ) m_MAPPROPERTY_PREVENT_PARTY_MASTER_CHANGE = in_bEnable;
	else
		return false;

	return true;
}


void CMapTypeProperty::GetByteArray(BYTE* out_pArray, const int in_MaxLength)
{
	if( in_MaxLength != 27 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "절대로 나와서는 않됩니다");
		return;
	}

	out_pArray[ 0] = m_MAPPROPERTY_PK;
	out_pArray[ 1] = m_MAPPROPERTY_TELEPORT;
	out_pArray[ 2] = m_MAPPROPERTY_NOTREMEMBER;
	out_pArray[ 3] = m_MAPPROPERTY_ITEMDROP;
	out_pArray[ 4] = m_MAPPROPERTY_EXP;
	out_pArray[ 5] = m_MAPPROPERTY_DISCONNECT_NOTREMEMBER;
	out_pArray[ 6] = m_MAPPROPERTY_CALLMONSTER;
	out_pArray[ 7] = m_MAPPROPERTY_PARTY;
	out_pArray[ 8] = m_MAPPROPERTY_GUILD;
	out_pArray[ 9] = m_MAPPROPERTY_SIEGE;
	out_pArray[10] = m_MAPPROPERTY_PKSERVER;
	out_pArray[11] = m_MAPPROPERTY_PVPSERVER;
	out_pArray[12] = m_MAPPROPERTY_DENYSKILL;
	out_pArray[13] = m_MAPPROPERTY_TURBOTRACK;
	out_pArray[14] = m_MAPPROPERTY_DENY_BUTTERFLY;
	out_pArray[15] = m_MAPPROPERTY_USE_SIMPLE_EFFECT;
	out_pArray[16] = m_MAPPROPERTY_DISABLE_LOCKON;
	out_pArray[17] = m_MAPPROPERTY_COUNT_PK;
	out_pArray[18] = m_MAPPROPERTY_NO_PARTY_FORMATION;
	out_pArray[19] = m_MAPPROPERTY_BATTLEFIELD;
	out_pArray[20] = m_MAPPROPERTY_DISABLE_COSTUMEITEM;
	out_pArray[21] = m_MAPPROPERTY_PREVENT_PARTY_MAKE;
	out_pArray[22] = m_MAPPROPERTY_PREVENT_PARTY_JOIN;
	out_pArray[23] = m_MAPPROPERTY_PREVENT_PARTY_LEAVE;
	out_pArray[24] = m_MAPPROPERTY_PREVENT_PARTY_EXPEL;
//	out_pArray[25] = m_MAPPROPERTY_SHOW_HP_BAR;
	out_pArray[26] = m_MAPPROPERTY_PREVENT_PARTY_MASTER_CHANGE;
}


int CMapTypeProperty::IsItPossible(int property)
{
	switch( property )
	{
	case MAPPROPERTY_PK:                          return m_MAPPROPERTY_PK;
	case MAPPROPERTY_TELEPORT:                    return m_MAPPROPERTY_TELEPORT;
	case MAPPROPERTY_NOTREMEMBER:                 return m_MAPPROPERTY_NOTREMEMBER;
	case MAPPROPERTY_ITEMDROP:                    return m_MAPPROPERTY_ITEMDROP;
	case MAPPROPERTY_EXP:                         return m_MAPPROPERTY_EXP;
	case MAPPROPERTY_DISCONNECT_NOTREMEMBER:      return m_MAPPROPERTY_DISCONNECT_NOTREMEMBER;
	case MAPPROPERTY_CALLMONSTER:                 return m_MAPPROPERTY_CALLMONSTER;
	case MAPPROPERTY_PARTY:                       return m_MAPPROPERTY_PARTY;
	case MAPPROPERTY_GUILD:                       return m_MAPPROPERTY_GUILD;
	case MAPPROPERTY_SIEGE:                       return m_MAPPROPERTY_SIEGE;
	case MAPPROPERTY_PKSERVER:                    return m_MAPPROPERTY_PKSERVER;
	case MAPPROPERTY_PVPSERVER:                   return m_MAPPROPERTY_PVPSERVER;
	case MAPPROPERTY_DENYSKILL:                   return m_MAPPROPERTY_DENYSKILL;
	case MAPPROPERTY_TURBOTRACK:                  return m_MAPPROPERTY_TURBOTRACK;
	case MAPPROPERTY_DENY_BUTTERFLY:              return m_MAPPROPERTY_DENY_BUTTERFLY;
	case MAPPROPERTY_USE_SIMPLE_EFFECT:           return m_MAPPROPERTY_USE_SIMPLE_EFFECT;
	case MAPPROPERTY_DISABLE_LOCKON:              return m_MAPPROPERTY_DISABLE_LOCKON;
	case MAPPROPERTY_COUNT_PK:                    return m_MAPPROPERTY_COUNT_PK;
	case MAPPROPERTY_NO_PARTY_FORMATION:          return m_MAPPROPERTY_NO_PARTY_FORMATION;
	case MAPPROPERTY_HIDING_DAMAGE:               return m_MAPPROPERTY_HIDING_DAMAGE;
	case MAPPROPERTY_DISABLE_KNOCKBACK:           return m_MAPPROPERTY_DISABLE_KNOCKBACK;
	case MAPPROPERTY_LONG_INSUPERABLE_TIME:       return m_MAPPROPERTY_LONG_INSUPERABLE_TIME;
	case MAPPROPERTY_BATTLEFIELD:                 return m_MAPPROPERTY_BATTLEFIELD;
	case MAPPROPERTY_NO_CHATTING:                 return m_MAPPROPERTY_NO_CHATTING;
	case MAPPROPERTY_NAMED_BOOTY:                 return m_MAPPROPERTY_NAMED_BOOTY;
	case MAPPROPERTY_SIEGETIME_VERSION:           return m_MAPPROPERTY_SIEGETIME_VERSION;
	case MAPPROPERTY_GOTOTOWN:                    return m_MAPPROPERTY_GOTOTOWN;
	case MAPPROPERTY_NORMAL_DAMAGE:               return m_MAPPROPERTY_NORMAL_DAMAGE;
	case MAPPROPERTY_RANGE_DAMAGE:                return m_MAPPROPERTY_RANGE_DAMAGE;
	case MAPPROPERTY_BLOCK_EQUIPITEM:             return m_BlockEquipItemContainer.size();
	case MAPPROPERTY_BLOCK_BUFF:                  return m_BlockBuffContainer.size();
	case MAPPROPERTY_DISABLE_COSTUMEITEM:         return m_MAPPROPERTY_DISABLE_COSTUMEITEM;
	case MAPPROPERTY_PREVENT_PARTY_MAKE:          return m_MAPPROPERTY_PREVENT_PARTY_MAKE;
	case MAPPROPERTY_PREVENT_PARTY_JOIN:          return m_MAPPROPERTY_PREVENT_PARTY_JOIN;
	case MAPPROPERTY_PREVENT_PARTY_LEAVE:         return m_MAPPROPERTY_PREVENT_PARTY_LEAVE;
	case MAPPROPERTY_PREVENT_PARTY_EXPEL:         return m_MAPPROPERTY_PREVENT_PARTY_EXPEL;
	case MAPPROPERTY_PREVENT_PARTY_MASTER_CHANGE: return m_MAPPROPERTY_PREVENT_PARTY_MASTER_CHANGE;
	default:
		return false;
	}
}


bool CMapTypeProperty::AddPropertyValue(const std::string in_PropertyName, const int in_Value)
{
	if     ( in_PropertyName == "NAMED_BOOTY"       ) m_MAPPROPERTY_NAMED_BOOTY       = in_Value;
	else if( in_PropertyName == "SIEGETIME_VERSION" ) m_MAPPROPERTY_SIEGETIME_VERSION = in_Value;
	else if( in_PropertyName == "GOTOTOWN"          ) m_MAPPROPERTY_GOTOTOWN          = in_Value;
	else if( in_PropertyName == "NORMAL_DAMAGE"     ) m_MAPPROPERTY_NORMAL_DAMAGE     = in_Value;
	else if( in_PropertyName == "RANGE_DAMAGE"      ) m_MAPPROPERTY_RANGE_DAMAGE      = in_Value;
	else if( in_PropertyName == "ALL_SKILL_DAMAGE"  ) m_MAPPROPERTY_ALL_SKILL_DAMAGE  = in_Value;
	else
		return false;

	return true;
}


bool CMapTypeProperty::AddTrapDurationPercent(const int in_SKID, const int in_Percent)
{
	std::pair<TRAPDURATION_CONTAINER_ITER,bool> ret = m_TrapDurationContainer.insert(std::pair<const int,int>(in_SKID, in_Percent));
	return ret.second;
}


int CMapTypeProperty::GetTrapDurationPercent(const int in_SKID)
{
	TRAPDURATION_CONTAINER_ITER iter = m_TrapDurationContainer.find(in_SKID);
	if( iter == m_TrapDurationContainer.end() )
		return 100;

	return iter->second;
}


bool CMapTypeProperty::AddSkillDamagePercent(const int in_SKID, const int in_Percent)
{
	std::pair<SKILLDAMAGE_CONTAINER_ITER,bool> ret = m_SkillDamageContainer.insert(std::pair<const int,int>(in_SKID, in_Percent));
	return ret.second;
}


int CMapTypeProperty::GetSkillDamagePercent(const int in_SKID)
{
	SKILLDAMAGE_CONTAINER_ITER iter = m_SkillDamageContainer.find(in_SKID);
	if( iter == m_SkillDamageContainer.end() )
		return m_MAPPROPERTY_ALL_SKILL_DAMAGE;

	return iter->second;
}


bool CMapTypeProperty::AddBlockEquipItem(const int in_ITID)
{
	m_BlockEquipItemContainer.push_back(in_ITID);
	return true;
}


bool CMapTypeProperty::isBlockEquipItem(const int in_ITID)
{
	BLOCKEQUIPITEM_CONTAINER_ITER iter;
	for( iter = m_BlockEquipItemContainer.begin(); iter != m_BlockEquipItemContainer.end(); ++iter )
		if( *iter == in_ITID )
			break;

	return ( iter != m_BlockEquipItemContainer.end() );
}


bool CMapTypeProperty::AddBlockBuff(const int in_BuffID)
{
	m_BlockBuffContainer.push_back(in_BuffID);
	return true;
}


bool CMapTypeProperty::isBlockBuff(const int in_BuffID)
{
	BLOCKBUFF_CONTAINER_ITER iter;
	for( iter = m_BlockBuffContainer.begin(); iter != m_BlockBuffContainer.end(); ++iter )
		if( *iter == in_BuffID )
			break;

	return ( iter != m_BlockBuffContainer.end() );
}
