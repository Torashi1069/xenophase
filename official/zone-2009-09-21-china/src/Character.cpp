#include "Character.h"
#include "CharacterMgr.h"
#include "enum.hpp"
#include "struct.hpp"
#include <math.h>


CCharacter::CCharacter(void) // line 15
{
	m_mapRes = NULL;
}


CCharacter::~CCharacter(void) // line 20
{
}


hook_method<int (CCharacter::*)(void)> CCharacter::_GetType(SERVER, "CCharacter::GetType");
int CCharacter::GetType(void) // line 146 (Character.h)
{
	return (this->*_GetType)();

	return m_type;
}


hook_method<void (CCharacter::*)(DWORD count, DWORD time)> CCharacter::_AddErrorCount2(SERVER, "?AddErrorCount@CCharacter@@UAEXKK@Z");
void CCharacter::AddErrorCount(DWORD count, DWORD time) // line 58
{
	return (this->*_AddErrorCount2)(count, time);

	this->CClient::AddErrorCount(count, time);
}


hook_method<void (CCharacter::*)(const char* filename, int line, DWORD count, DWORD time)> CCharacter::_AddErrorCount(SERVER, "?AddErrorCount@CCharacter@@UAEXPBDHKK@Z");
void CCharacter::AddErrorCount(const char* filename, int line, DWORD count, DWORD time) // line 70
{
	return (this->*_AddErrorCount)(filename, line, count, time);

	this->CClient::AddErrorCount(filename, line, count, time);
}


hook_method<void (CCharacter::*)(void)> CCharacter::_Init(SERVER, "CCharacter::Init");
void CCharacter::Init(void) // line 33
{
	return (this->*_Init)();

	m_mapRes = NULL;
	this->CCharacter::SetSectionList(NULL);
	memset(&m_characterPInfo, 0, sizeof(m_characterPInfo));
}


hook_method<int (CCharacter::*)(int position, int isArrowProperty)> CCharacter::_GetWeaponProperty(SERVER, "CCharacter::GetWeaponProperty");
int CCharacter::GetWeaponProperty(int position, int isArrowProperty) // line 385
{
	return (this->*_GetWeaponProperty)(position, isArrowProperty);

	return m_characterPInfo.attack;
}


hook_method<bool (CCharacter::*)(void)> CCharacter::_IsActor(SERVER, "CCharacter::IsActor");
bool CCharacter::IsActor(void) // line ???
{
	return (this->*_IsActor)();

	return 0;
}


//hook_method<CMapRes* (CCharacter::*)(void)> CCharacter::_GetMapRes(SERVER, "CCharacter::GetMapRes");
CMapRes* CCharacter::GetMapRes(void) // line ??
{
//	return (this->*_GetMapRes)();

	return m_mapRes;
}


hook_method<int (CCharacter::*)(int property)> CCharacter::_IsItPossible(SERVER, "CCharacter::IsItPossible");
int CCharacter::IsItPossible(int property) // line 26
{
	return (this->*_IsItPossible)(property);

	return ( m_mapRes ) ? m_mapRes->CMapRes::IsItPossible(property) : 0;
}


hook_method<int (CCharacter::*)(void)> CCharacter::_IsSiegeMode(SERVER, "CCharacter::IsSiegeMode");
int CCharacter::IsSiegeMode(void) // line ??
{
	return (this->*_IsSiegeMode)();

	return this->IsItPossible(9);
}


hook_method<int (CCharacter::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CCharacter::_OnMsg(SERVER, "CCharacter::OnMsg");
int CCharacter::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // line 76
{
	return (this->*_OnMsg)(sender, receiver, msgID, par1, par2, par3, par4);

	if( msgID == CM_SHOWEFFECT )
		this->OnShowEffect(par1);
	return 0;
}


hook_method<int (CCharacter::*)(unsigned short id, int& value)> CCharacter::_GetParameterValue(SERVER, "CCharacter::GetParameterValue");
int CCharacter::GetParameterValue(unsigned short id, int& value) // line 126
{
	return (this->*_GetParameterValue)(id, value);

	value = 0;
	return 0;
}


hook_method<int (CCharacter::*)(unsigned short id, int value)> CCharacter::_UpdateParameterValue(SERVER, "CCharacter::UpdateParameterValue");
int CCharacter::UpdateParameterValue(unsigned short id, int value) // line 132
{
	return (this->*_UpdateParameterValue)(id, value);

	return 0;
}


hook_method<void (CCharacter::*)(unsigned long commandID)> CCharacter::_DisableCommand(SERVER, "CCharacter::DisableCommand");
void CCharacter::DisableCommand(unsigned long commandID) // line ???
{
	return (this->*_DisableCommand)(commandID);

	;
}


hook_method<COMMAND_QUEUE* (CCharacter::*)(unsigned long commandID)> CCharacter::_SearchCommand(SERVER, "CCharacter::SearchCommand");
COMMAND_QUEUE* CCharacter::SearchCommand(unsigned long commandID) // line ???
{
	return (this->*_SearchCommand)(commandID);

	return 0;
}


hook_method<unsigned long (CCharacter::*)(void)> CCharacter::_GetState(SERVER, "CCharacter::GetState");
unsigned long CCharacter::GetState(void) // line ???
{
	return (this->*_GetState)();

	return CHARACTER_STATE_MOVE;
}


hook_method<int (CCharacter::*)(void)> CCharacter::_GetScale(SERVER, "CCharacter::GetScale");
int CCharacter::GetScale(void) // line ???
{
	return (this->*_GetScale)();

	return 1;
}


hook_method<int (CCharacter::*)(void)> CCharacter::_IsDamageMotionPossible(SERVER, "CCharacter::IsDamageMotionPossible");
int CCharacter::IsDamageMotionPossible(void) // line ???
{
	return (this->*_IsDamageMotionPossible)();

	return 1;
}


hook_method<int (CCharacter::*)(int property)> CCharacter::_IsRightProperty(SERVER, "CCharacter::IsRightProperty");
int CCharacter::IsRightProperty(int property) // line ???
{
	return (this->*_IsRightProperty)(property);

	return 0;
}


hook_method<int (CCharacter::*)(int race, int _class, int level)> CCharacter::_IsAvoidable(SERVER, "CCharacter::IsAvoidable");
int CCharacter::IsAvoidable(int race, int _class, int level) // line 110
{
	return (this->*_IsAvoidable)(race, _class, level);

	return 0;
}


hook_method<int (CCharacter::*)(void)> CCharacter::_IsInitingState(SERVER, "CCharacter::IsInitingState");
int CCharacter::IsInitingState(void) // line ???
{
	return (this->*_IsInitingState)();

	return 0;
}


hook_method<int (CCharacter::*)(void)> CCharacter::_IsLucky(SERVER, "CCharacter::IsLucky");
int CCharacter::IsLucky(void) // line ???
{
	return (this->*_IsLucky)();

	return 0;
}


hook_method<void (CCharacter::*)(int effect)> CCharacter::_OnShowEffect(SERVER, "CCharacter::OnShowEffect");
void CCharacter::OnShowEffect(int effect) // line ???
{
	return (this->*_OnShowEffect)(effect);

	;
}


hook_method<void (CCharacter::*)(int effect, int numdata)> CCharacter::_OnShowEffect3(SERVER, "CCharacter::OnShowEffect3");
void CCharacter::OnShowEffect3(int effect, int numdata) // line ???
{
	return (this->*_OnShowEffect3)(effect, numdata);

	;
}


hook_method<void (CCharacter::*)(char* buf, int len)> CCharacter::_MultiCast(SERVER, "CCharacter::MultiCast");
void CCharacter::MultiCast(char* buf, int len) // line 155
{
	return (this->*_MultiCast)(buf, len);

	m_neighborCache.CNeighborCache::OnMultiCast(this, len, buf, 18);
}


/// Is there a direct path between 'this' and 'ch'?
hook_method<int (CCharacter::*)(CCharacter* ch, int isClose)> CCharacter::_IsDirectPath(SERVER, "CCharacter::IsDirectPath");
int CCharacter::IsDirectPath(CCharacter* ch, int isClose) // line 159
{
	return (this->*_IsDirectPath)(ch, isClose);

	if( !this->m_mapRes )
		return 0;

	if( !ch->m_mapRes )
		return 0;

	if( this->m_mapRes != ch->m_mapRes )
	{
		if( this->GetType() == PC_TYPE )
			this->AddErrorCount(".\\Character.cpp", 168, 4, timeGetTime());
		return 0;
	}

	int srcX, srcY, destX, destY;
	this->GetParameterValue(61, srcX);
	this->GetParameterValue(62, srcY);
	ch->GetParameterValue(61, destX);
	ch->GetParameterValue(62, destY);
	return m_mapRes->CMapRes::IsDirectPath(srcX, srcY, destX, destY, isClose);
}


hook_method<int (CCharacter::*)(void)> CCharacter::_GetEffectState(SERVER, "CCharacter::GetEffectState");
int CCharacter::GetEffectState(void) // line ???
{
	return (this->*_GetEffectState)();

	return 0;
}


hook_method<mystd::vector<CCharacter*>* (CCharacter::*)(void)> CCharacter::_GetSectionList(SERVER, "CCharacter::GetSectionList");
mystd::vector<CCharacter*>* CCharacter::GetSectionList(void) // line 200
{
	return (this->*_GetSectionList)();

	return m_sectionList;
}


hook_method<void (CCharacter::*)(mystd::vector<CCharacter*>* sl)> CCharacter::_SetSectionList(SERVER, "CCharacter::SetSectionList");
void CCharacter::SetSectionList(mystd::vector<CCharacter*>* sl) // line 192
{
	return (this->*_SetSectionList)(sl);

	m_sectionList = sl;
}


hook_method<void (CCharacter::*)(unsigned long in_loc, CITZMsg* flag)> CCharacter::_OnMsgFromItemServer(SERVER, "CCharacter::OnMsgFromItemServer");
void CCharacter::OnMsgFromItemServer(unsigned long in_loc, CITZMsg* flag) // line ???
{
	return (this->*_OnMsgFromItemServer)(in_loc, flag);

	;
}


hook_method<void (CCharacter::*)(int sp)> CCharacter::_ReduceSPByUseSkill(SERVER, "CCharacter::ReduceSPByUseSkill");
void CCharacter::ReduceSPByUseSkill(int sp) // line ???
{
	return (this->*_ReduceSPByUseSkill)(sp);

	;
}


hook_method<bool (CCharacter::*)(int itemID, int count, bool isExternalEffect)> CCharacter::_IsExistItem(SERVER, "CCharacter::IsExistItem");
bool CCharacter::IsExistItem(int itemID, int count, bool isExternalEffect) // line ???
{
	return (this->*_IsExistItem)(itemID, count, isExternalEffect);

	return 1;
}


hook_method<bool (CCharacter::*)(int itemID, int count, bool isExternalEffect)> CCharacter::_ConsumeItemByUseSkill(SERVER, "CCharacter::ConsumeItemByUseSkill");
bool CCharacter::ConsumeItemByUseSkill(int itemID, int count, bool isExternalEffect) // line 185 (Character.h)
{
	return (this->*_ConsumeItemByUseSkill)(itemID, count, isExternalEffect);

	return 1;
}


hook_method<short (CCharacter::*)(CCharacter* other, int isRangeAttack)> CCharacter::_GetAttackSuccessPercent(SERVER, "CCharacter::GetAttackSuccessPercent");
short CCharacter::GetAttackSuccessPercent(CCharacter* other, int isRangeAttack) // line 132
{
	return (this->*_GetAttackSuccessPercent)(other, isRangeAttack);

	return 0;
}


hook_method<int (CCharacter::*)(ATTACK_INFO* info)> CCharacter::_GetAttackFinalDamage(SERVER, "CCharacter::GetAttackFinalDamage");
int CCharacter::GetAttackFinalDamage(ATTACK_INFO* info) // line ???
{
	return (this->*_GetAttackFinalDamage)(info);

	return 0;
}


hook_method<int (CCharacter::*)(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bHideSkill)> CCharacter::_SkillAttack(SERVER, "CCharacter::SkillAttack");
int CCharacter::SkillAttack(SKILLATTACK_MSG* msg, int plusATTPowerPercent, int plusATTSuccessPercent, const bool in_bHideSkill) // line 189 (Character.h)
{
	return (this->*_SkillAttack)(msg, plusATTPowerPercent, plusATTSuccessPercent, in_bHideSkill);

	return 0;
}


hook_method<short (CCharacter::*)(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count)> CCharacter::_SplashAttack(SERVER, "CCharacter::SplashAttack");
short CCharacter::SplashAttack(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count)
{
	return (this->*_SplashAttack)(val1, xPos, yPos, type, range, rangeIn, exceptAID, msgDataPtr, val2, count);

	return 0;
}


hook_method<int (CCharacter::*)(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc)> CCharacter::_SplashAttack2(SERVER, "CCharacter::SplashAttack2");
int CCharacter::SplashAttack2(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc) // line 192 (Character.h)
{
	return (this->*_SplashAttack2)(plusATTPower, dest, type, halfWidth, height, msgData, count, plusHitPercent, specialSrc);

	return 0;
}


hook_method<int (CCharacter::*)(int state, CCharacter* other, int percent, int preDelayTime, int delayTime, int isSpell, int isFixedDelayTime)> CCharacter::_SetHandicapState(SERVER, "CCharacter::SetHandicapState");
int CCharacter::SetHandicapState(int state, CCharacter* other, int percent, int preDelayTime, int delayTime, int isSpell, int isFixedDelayTime) // line 193 (Character.h)
{
	return (this->*_SetHandicapState)(state, other, percent, preDelayTime, delayTime, isSpell, isFixedDelayTime);

	return 0;
}


hook_method<int (CCharacter::*)(int xPos, int yPos, int range, int isAffectPlayer, int isAffectTrap, int isDeadPlayer)> CCharacter::_GetCountInArea(SERVER, "CCharacter::GetCountInArea");
int CCharacter::GetCountInArea(int xPos, int yPos, int range, int isAffectPlayer, int isAffectTrap, int isDeadPlayer) // line 263
{
	return (this->*_GetCountInArea)(xPos, yPos, range, isAffectPlayer, isAffectTrap, isDeadPlayer);

	if( m_mapRes == NULL )
		return 0;

	NEIGHBORHOOD_SECTION result;
	result.section[0] = NULL;
	result.section[1] = NULL;
	result.section[2] = NULL;
	result.section[3] = NULL;
	m_mapRes->CMapRes::GetNeighborhoodSections(xPos, yPos, min(range,1), &result);

	int nCount = 0;

	for( int i = 0; i < countof(result.section); ++i )
	{
		mystd::vector<CCharacter*>* section = result.section[i];
		if( section == NULL )
			continue;

		for( mystd::vector<CCharacter*>::iterator it = section->begin(); it != section->end(); ++it )
		{
			CCharacter* ch = *it;

			if( ch == this && !isAffectPlayer )
				continue;

			if( !ch->IsTarget(this, 10) )
			{
				if( ch->GetType() != PC_TYPE )
					continue;

				if( isAffectPlayer == 0 )
					continue;
			}
			else
			{
				if( isDeadPlayer && ch->GetState() == CHARACTER_STATE_DEAD )
					continue;

				if( ch->GetType() == SKILL_TYPE && isAffectTrap == 0 )
					continue;
			}

			int otherXPos;
			int otherYPos;
			ch->GetParameterValue(VAR_CURXPOS, otherXPos);
			ch->GetParameterValue(VAR_CURYPOS, otherYPos);

			if( abs(xPos - otherXPos) <= range && abs(yPos - otherYPos) <= range )
				++nCount;
		}
	}

	return nCount;
}


hook_method<int (CCharacter::*)(CCharacter* target)> CCharacter::_GetModifiedTargetItemDEF(SERVER, "CCharacter::GetModifiedTargetItemDEF");
int CCharacter::GetModifiedTargetItemDEF(CCharacter* target) // line 392
{
	return (this->*_GetModifiedTargetItemDEF)(target);

	int result;
	target->GetParameterValue(VAR_ITEMDEFPOWER, result);
	return result;
}


hook_method<int (CCharacter::*)(CCharacter* target)> CCharacter::_GetModifiedTargetItemMDEF(SERVER, "CCharacter::GetModifiedTargetItemMDEF");
int CCharacter::GetModifiedTargetItemMDEF(CCharacter* target) // line 399
{
	return (this->*_GetModifiedTargetItemDEF)(target);

	int result;
	target->GetParameterValue(VAR_MAGICITEMDEFPOWER, result);
	return result;
}


hook_method<int (CCharacter::*)(int index, int time, int val1, int val2, int val3, int isSendClient)> CCharacter::_SetEffective(SERVER, "CCharacter::SetEffective");
int CCharacter::SetEffective(int index, int time, int val1, int val2, int val3, int isSendClient) // line 132 (CharacterBuff.cpp)
{
	return (this->*_SetEffective)(index, time, val1, val2, val3, isSendClient);

	switch( index )
	{
	case EFST_RG_CCONFINE_M:
		this->SetEffective(EFST_DISABLEMOVE, time, 1, 0, 0, 0);
		this->OnChangeStatusAmount(SKID_RG_CLOSECONFINE, 165, time, 10);
		if( this->GetType() != PC_TYPE )
			this->OnShowEffect(EF_NPC_STOP2);
		break;
	case EFST_ASSUMPTIO:
		this->ResetEffective(EFST_KYRIE, 0);
		this->ResetEffective(EFST_BARRIER, 0);
		this->ResetEffective(EFST_KAITE, 0);
		this->SetOnShowEFST(SHOW_EFST_ASSUMPTIO);
		break;
	case EFST_STONESKIN:
		m_charBuff2.m_damaged.directSubPercent += val1;
		this->OnMsg(NULL, this, CM_SET_MDEFPERCENT, SKID_NPC_STONESKIN, time, -val1, 0);
		break;
	case EFST_ANTIMAGIC:
		m_charBuff2.m_damaged.magicSubPercent += val1;
		this->OnMsg(NULL, this, CM_SET_DEFPERCENT, SKID_NPC_ANTIMAGIC, time, -val1, 0);
		break;
	case EFST_CRITICALWOUND:
		m_charBuff2.m_heal.hp_modifyPercent -= val1;
		break;
	case EFST_MOVESLOW_POTION:
		this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
		break;
	default:
		break;
	}

	return 0;
}


hook_method<int (CCharacter::*)(int index, int enumVal)> CCharacter::_GetEffective(SERVER, "CCharacter::GetEffective");
int CCharacter::GetEffective(int index, int enumVal) // line 13 (CharacterBuff.cpp)
{
	return (this->*_GetEffective)(index, enumVal);

	if( enumVal > 2 ) //countof(EFFECTIVE_INFO::val)
		return 0;

	mystd::map<int,EFFECTIVE_INFO>::iterator it = m_effectiveList.find(index);
	if( it == m_effectiveList.end() )
		return 0;

	return it->second.val[enumVal];
}


hook_method<void (CCharacter::*)(int index, int val, int enumVal)> CCharacter::_UpdateEffective(SERVER, "CCharacter::UpdateEffective");
void CCharacter::UpdateEffective(int index, int val, int enumVal) // line 28 (CharacterBuff.cpp)
{
	return (this->*_UpdateEffective)(index, val, enumVal);

	if( enumVal > 2 ) //countof(EFFECTIVE_INFO::val)
		return;

	mystd::map<int,EFFECTIVE_INFO>::iterator it = m_effectiveList.find(index);
	if( it == m_effectiveList.end() )
		return;

	it->second.val[enumVal] += val;
}


hook_method<void (CCharacter::*)(int index, int val)> CCharacter::_ResetEffective(SERVER, "CCharacter::ResetEffective");
void CCharacter::ResetEffective(int index, int val) // line 184 (CharacterBuff.cpp)
{
	return (this->*_ResetEffective)(index, val);

	switch( index )
	{
	case EFST_RG_CCONFINE_M:
		this->CCharacter::ResetStatusAmount(SKID_RG_CLOSECONFINE, 0);
		this->ResetEffective(EFST_DISABLEMOVE, 0);
		if( this->GetType() != PC_TYPE )
			this->OnShowEffect(EF_NPC_STOP2_DEL);
		break;
	case EFST_ASSUMPTIO:
		this->SetOffShowEFST(SHOW_EFST_ASSUMPTIO);
		break;
	case EFST_STONESKIN:
		this->OnMsg(NULL, this, CM_RESET_MDEFPERCENT, SKID_NPC_STONESKIN, 0, 0, 0);
		m_charBuff2.m_damaged.directSubPercent -= val;
		break;
	case EFST_ANTIMAGIC:
		this->OnMsg(NULL, this, CM_RESET_DEFPERCENT, SKID_NPC_ANTIMAGIC, 0, 0, 0);
		m_charBuff2.m_damaged.magicSubPercent -= val;
		break;
	case EFST_CRITICALWOUND:
		m_charBuff2.m_heal.hp_modifyPercent += val;
		break;
	case EFST_MOVESLOW_POTION:
		this->UpdateParameterValue(VAR_SPEEDAMOUNT, 0);
		break;
	default:
		break;
	}
}


hook_method<bool (CCharacter::*)(int index, int time, int val)> CCharacter::_IsEnableSetEffective(SERVER, "CCharacter::IsEnableSetEffective");
bool CCharacter::IsEnableSetEffective(int index, int time, int val) // line 231 (CharacterBuff.cpp)
{
	return (this->*_IsEnableSetEffective)(index, time, val);

	//TODO
}


hook_method<void (CCharacter::*)(int index, int time)> CCharacter::_UpdateEffectiveTime(SERVER, "CCharacter::UpdateEffectiveTime");
void CCharacter::UpdateEffectiveTime(int index, int time) // line 42 (CharacterBuff.cpp)
{
	return (this->*_UpdateEffectiveTime)(index, time);

	mystd::map<int,EFFECTIVE_INFO>::iterator iter = m_effectiveList.find(index);
	if( iter != m_effectiveList.end() )
		iter->second.time = time + timeGetTime();
}


hook_method<EFFECTIVE_INFO* (CCharacter::*)(int index)> CCharacter::_GetEffectiveInfo(SERVER, "CCharacter::GetEffectiveInfo");
EFFECTIVE_INFO* CCharacter::GetEffectiveInfo(int index) // line 53 (CharacterBuff.cpp)
{
	return (this->*_GetEffectiveInfo)(index);

	mystd::map<int,EFFECTIVE_INFO>::iterator it = m_effectiveList.find(index);
	return( it != m_effectiveList.end() ) ? &it->second : 0;
}


hook_method<void (CCharacter::*)(void)> CCharacter::_ProcessAllEffective(SERVER, "CCharacter::ProcessAllEffective");
void CCharacter::ProcessAllEffective(void) // line 64 (CharacterBuff.cpp)
{
	return (this->*_ProcessAllEffective)();

	DWORD now = timeGetTime();

	mystd::map<int,EFFECTIVE_INFO>::iterator it = m_effectiveList.begin();
	while( it != m_effectiveList.end() )
	{
		const int& efst = it->first;
		EFFECTIVE_INFO& info = it->second;

		if( info.val[0] != 0 )
		{
			if( info.time == 9999 )
			{
				int SKID = 0;
				bool isPlaySolo = false;
				if( this->IsGroundEffective(efst, SKID, isPlaySolo) )
					this->ProcessGroundEffective(efst, SKID, isPlaySolo);
			}
			else
			if( now <= info.time )
			{
				this->ProcessCheckEffective(efst, &info);
			}
			else
			{
				this->ResetEffective(efst, NULL);
			}

			++it;
		}
		else
		{
			it = m_effectiveList.erase(it);
		}
	}
}


hook_method<bool (CCharacter::*)(int index, int& SKID, bool& isPlaySolo)> CCharacter::_IsGroundEffective(SERVER, "CCharacter::IsGroundEffective");
bool CCharacter::IsGroundEffective(int index, int& SKID, bool& isPlaySolo) // line 98 (CharacterBuff.cpp)
{
	return (this->*_IsGroundEffective)(index, SKID, isPlaySolo);

	switch( index )
	{
	case EFST_DONTFORGETME:
		SKID = SKID_DC_DONTFORGETME;
		isPlaySolo = true;
		return true;
	case EFST_ETERNALCHAOS:
		SKID = SKID_BD_ETERNALCHAOS;
		isPlaySolo = false;
		return true;
	case EFST_ROKISWEIL:
		SKID = SKID_BD_ROKISWEIL;
		isPlaySolo = false;
		return true;
	case EFST_FOGWALL:
		SKID = SKID_PF_FOGWALL;
		isPlaySolo = false;
		return true;
	default:
		SKID = 0;
		isPlaySolo = false;
		return false;
	}
}


hook_method<void (CCharacter::*)(int par1, int par2, bool par3)> CCharacter::_ProcessGroundEffective(SERVER, "CCharacter::ProcessGroundEffective");
void CCharacter::ProcessGroundEffective(int par1, int par2, bool par3) // line 209 (Character.h)
{
	return (this->*_ProcessGroundEffective)(par1, par2, par3);

	;
}


hook_method<void (CCharacter::*)(int index, EFFECTIVE_INFO* info)> CCharacter::_ProcessCheckEffective(SERVER, "CCharacter::ProcessCheckEffective");
void CCharacter::ProcessCheckEffective(int index, EFFECTIVE_INFO* info) // line 115 (CharacterBuff.cpp)
{
	return (this->*_ProcessCheckEffective)(index, info);

	if( index == EFST_RG_CCONFINE_M )
	{
		CCharacter* ch = g_characterMgr->CCharacterMgr::FastFindCharacter(info->val[1]);
		if( ch == NULL || !this->IsMyArea(ch, 2) )
		{
			this->ResetEffective(EFST_RG_CCONFINE_M, 0);
			g_characterMgr->CCharacterMgr::SendMsg(this, ch, CM_RESETEFFECTIVE, EFST_RG_CCONFINE_S, 0, 0, 0);
		}
	}
}


hook_method<void (CCharacter::*)(int value)> CCharacter::_SetOnShowEFST(SERVER, "CCharacter::SetOnShowEFST");
void CCharacter::SetOnShowEFST(int value) // line ???
{
	return (this->*_SetOnShowEFST)(value);

	;
}


hook_method<void (CCharacter::*)(int value)> CCharacter::_SetOffShowEFST(SERVER, "CCharacter::SetOffShowEFST");
void CCharacter::SetOffShowEFST(int value) // line ???
{
	return (this->*_SetOffShowEFST)(value);

	;
}


hook_method<void (CCharacter::*)(int& healAmount)> CCharacter::_GetModifiedHealAmount(SERVER, "CCharacter::GetModifiedHealAmount");
void CCharacter::GetModifiedHealAmount(int& healAmount) // line 278 (CharacterBuff.cpp)
{
	return (this->*_GetModifiedHealAmount)(healAmount);

	if( m_charBuff2.m_heal.hp_modifyPercent != 0 )
		healAmount += healAmount * m_charBuff2.m_heal.hp_modifyPercent / 100;
}


hook_method<void (CCharacter::*)(int in_SKLevel, unsigned short in_EFST, unsigned long in_EFST_time, int in_EFST_value)> CCharacter::_OnChangeStatusAmount(SERVER, "CCharacter::OnChangeStatusAmount");
void CCharacter::OnChangeStatusAmount(int in_SKLevel, unsigned short in_EFST, unsigned long in_EFST_time, int in_EFST_value) // line 217 (Character.h)
{
	return (this->*_OnChangeStatusAmount)(in_SKLevel, in_EFST, in_EFST_time, in_EFST_value);

	;
}


hook_method<void (CCharacter::*)(unsigned short type, int amount)> CCharacter::_NotifyStatusAmount(SERVER, "CCharacter::NotifyStatusAmount");
void CCharacter::NotifyStatusAmount(unsigned short type, int amount) // line ???
{
	return (this->*_NotifyStatusAmount)(type, amount);

	;
}


hook_method<void (CCharacter::*)(unsigned short SKID, unsigned short type)> CCharacter::_ResetStatusAmount(SERVER, "CCharacter::ResetStatusAmount");
void CCharacter::ResetStatusAmount(unsigned short SKID, unsigned short type) // line 206
{
	return (this->*_ResetStatusAmount)(SKID, type);

	//TODO
}


hook_method<void (CCharacter::*)(void)> CCharacter::_ProcessStatusAmount(SERVER, "CCharacter::ProcessStatusAmount");
void CCharacter::ProcessStatusAmount(void) // line 235
{
	return (this->*_ProcessStatusAmount)();

	//TODO
}


hook_method<void (CCharacter::*)(PosInfo src, PosInfo dest, int distance, PosInfo& result)> CCharacter::_GetPushedPosition(SERVER, "CCharacter::GetPushedPosition");
void CCharacter::GetPushedPosition(PosInfo src, PosInfo dest, int distance, PosInfo& result) // line 310
{
	return (this->*_GetPushedPosition)(src, dest, distance, result);

	if( m_mapRes != NULL )
	{
		int dx = 2 * (dest.x - src.x > 0) - 1;
		int dy = 2 * (dest.y - src.y > 0) - 1;
		float ratio = (float)fabs((double)(dest.y - src.y) / ((double)(dest.x - src.x) + 0.001));

		if( ratio <= 1/3. )
		{// horizontal
			dy = 0;
		}
		else
		if( ratio >= 3.0 )
		{// vertical
			dx = 0;
		}
		else
		{// diagonal
		}

		int px = dx;
		int py = dy;
		int d = 1;
		while( d <= distance && m_mapRes->CMapRes::IsMovableCell(px + dest.x, py + dest.y) )
		{
			px += dx;
			py += dy;
			d  += 1;
		}

		result.x = dest.x + dx * (d - 1);
		result.y = dest.y + dy * (d - 1);
	}
	else
	{
		result.x = dest.x;
		result.y = dest.y;
	}
}


//hook_method<CCharBuff& (CCharacter::*)(void)> CCharacter::_InstanceCharBuff(SERVER, "CCharacter::InstanceCharBuff");
CCharBuff& CCharacter::InstanceCharBuff(void) // line ???
{
//	return (this->*_InstanceCharBuff)();

	return m_charBuff2;
}


hook_method<bool (CCharacter::*)(void)> CCharacter::_IsBattleFieldMode(SERVER, "CCharacter::IsBattleFieldMode");
bool CCharacter::IsBattleFieldMode(void) // line 411
{
	return (this->*_IsBattleFieldMode)();

	if( m_mapRes == NULL )
		return false;

	return m_mapRes->IsBattleField();
}


hook_method<char (CCharacter::*)(void)> CCharacter::_GetCampID(SERVER, "CCharacter::GetCampID");
char CCharacter::GetCampID(void) // line ???
{
	return (this->*_GetCampID)();

	return 0;
}


hook_method<void (CCharacter::*)(char campID)> CCharacter::_SetCampID(SERVER, "CCharacter::SetCampID");
void CCharacter::SetCampID(char campID) // line ???
{
	return (this->*_SetCampID)(campID);

	;
}


hook_method<bool (CCharacter::*)(CCharacter* ch, unsigned long flag, int& result)> CCharacter::_IsTargetInBattleField(SERVER, "CCharacter::IsTargetInBattleField");
bool CCharacter::IsTargetInBattleField(CCharacter* ch, unsigned long flag, int& result) // line 423
{
	return (this->*_IsTargetInBattleField)(ch, flag, result);

	result = 1;

	if( ch == NULL )
		return false;
	
	if( !this->CCharacter::IsBattleFieldMode() )
		return false;

	if( !(flag & 4) && this->GetCampID() == ch->GetCampID() )
		result = 0;

	return true;
}
