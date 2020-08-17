#include "CDisconnectLog.h"
#include "Character.h"
#include "CharacterMgr.h"
#include "MapRes.h"
#include "MapTypeProperty.h"


CCharacter::CCharacter()
{
//	m_type = UNKNOWN_TYPE;
	m_mapRes = NULL;
//	m_sectionList = NULL;

	m_fvars.push_back(&mfvarb_RNG_Physics_ATKED_Cancel);
	m_fvars.push_back(&mfvarb_Skill_ATKED_Cancel);
	m_fvars.push_back(&mfvarm_Melee_Physics_ATKED_Cancel_Percent);
	m_fvars.push_back(&mfvarm_Magic_ATKED_Cancel_Percent);
	m_fvars.push_back(&m_fvarm_Item_DEF_INC_Percent);
	m_fvars.push_back(&m_fvarm_Item_DEF_DEC_Percent);
	m_fvars.push_back(&m_fvars_Item_DEF_INC_Amount);
	m_fvars.push_back(&m_fvarm_Status_DEF_INC_Percent);
	m_fvars.push_back(&m_fvars_Status_DEF_INC_Amount);
	m_fvars.push_back(&m_fvarb_HEALTH_BLOODING_Cancel);
	m_fvars.push_back(&m_fvarb_BODYSTATE_STONECURSE_Cancel);
	m_fvars.push_back(&m_fvarm_Move_Speed_DEC_Percent);
	m_fvars.push_back(&m_fvarind_Appoint_Skill_MATK_Percent);
	m_fvars.push_back(&m_fvarindhistory_Appoint_Skill_Change_Property);
	m_fvars.push_back(&m_fvarindminhistory_UseSkill_SPcost_Percent);
	m_fvars.push_back(&m_fvarindmaxhistory_UseSkill_ConsumItem_CancelPermil);
	m_fvars.push_back(&m_fvarh_ATK_Property);
	m_fvars.push_back(&m_fvarshistory_INC_ItemATK_Percent);
	m_fvars.push_back(&m_fvarshistory_ItemATK_Amount);
	m_fvars.push_back(&m_fvarindsumhistory_GlobalPostDelay_Percent);
	m_fvars.push_back(&m_fvarshistory_ItemMATK_Amount);
	m_fvars.push_back(&m_fvars_FinalDamage_DEC_Amount);
	m_fvars.push_back(&m_fvarPassiveSKHPRecovery);
	m_fvars.push_back(&m_fvarPassiveSKSPRecovery);
	m_fvars.push_back(&m_fvarshistory_NearPhysicsAtkPercent);
	m_fvars.push_back(&m_fvarb_WearTakeOff_Forbid);
	m_fvars.push_back(&m_fvarb_MoveBlock);
	m_fvars.push_back(&m_fvarb_SkillUseBlock);
	m_fvars.push_back(&m_fvarb_ItemUseBlock);
	m_fvars.push_back(&m_fvarb_MeleeAtkBlock);
}


CCharacter::~CCharacter()
{
}


int CCharacter::IsItPossible(int property)
{
	if( m_mapRes == NULL )
		return 0;

	return m_mapRes->CMapRes::IsItPossible(property);
}


void CCharacter::Init()
{
	m_mapRes = NULL;

	this->CCharacter::SetSectionList(NULL);

	m_characterPInfo.bodyState = 0;
	m_characterPInfo.healthState = 0;
	m_characterPInfo.effectState = 0;
	m_characterPInfo.armor = 0;
	m_characterPInfo.currentProperty = 0;
	m_characterPInfo.attack = 0;

	m_commandQueue.clear();

	m_InstantVar.CInstantVar::Init();

	this->RecycleInit();
}


void CCharacter::RecycleInit()
{
	for( std::vector<FactorVAR::Fvar*>::iterator iter = m_fvars.begin(); iter != m_fvars.end(); ++iter )
		(*iter)->Init();
}


void CCharacter::AddErrorCnt(const char* in_SourceFileName, const int in_SourceLineNum, const DWORD in_Cnt, const DWORD in_TM)
{
	if( this->GetType() == PC_TYPE && CDisconnectLog::GetObj()->NFileLog::GetOutput() == true && in_Cnt != 65535 && m_dwErrorCount < 4 )
		CDisconnectLog::GetObj()->NFileLog::WriteFmt(in_SourceFileName, in_SourceLineNum, "AID(%d) Cnt(%d/%d)", this->GetAccountID(), in_Cnt, m_dwErrorCount);

	this->CClient::AddErrorCnt(in_SourceFileName, in_SourceLineNum, in_Cnt, in_TM);
}


int CCharacter::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)
{
	switch( msgID )
	{
	case CM_SHOWEFFECT:
	{
		int effect = (int)par1;
		this->OnShowEffect(effect);
	}
	break;
	case CM_INSTANTVAR_GET:
	{
		CInstantVar::enumVAR var = (CInstantVar::enumVAR)par1;
		return m_InstantVar(var);
	}
	break;
	case CM_INSTANTVAR_SET:
	{
		CInstantVar::enumVAR var = (CInstantVar::enumVAR)par1;
		int value = (int)par2;
		m_InstantVar(var, value);
	}
	break;
	case CM_INSTANTVAR_ADD:
	{
		CInstantVar::enumVAR var = (CInstantVar::enumVAR)par1;
		int value = (int)par2;
		m_InstantVar(var, m_InstantVar(var) + value);
	}
	break;
	case CM_SHOWSCRIPT:
	{
		const char* msg = (const char*)par1;
		this->OnShowScript(msg);
	}
	break;
	};

	return 0;
}


BOOL CCharacter::IsDamageMotionPossible()
{
	return TRUE;
}


unsigned long CCharacter::GetState()
{
	return CHARACTER_STATE_MOVE;
}


BOOL CCharacter::IsAvoidable(int race, int _class, int level)
{
	return FALSE;
}


BOOL CCharacter::IsInitingState()
{
	return FALSE;
}


BOOL CCharacter::IsLucky()
{
	return FALSE;
}


int CCharacter::GetParameterValue(unsigned short id, int& value)
{
	value = 0;
	return 0;
}


int CCharacter::UpdateParameterValue(unsigned short id, int value)
{
	return 0;
}


void CCharacter::DisableCommand(unsigned long commandID)
{
}


COMMAND_QUEUE* CCharacter::SearchCommand(unsigned long commandID)
{
	return NULL;
}


int CCharacter::GetScale()
{
	return CHAR_SCALE_MEDIUM;
}


void CCharacter::MultiCast(char* buf, int len)
{
	m_neighborCache.CNeighborCache::OnMultiCast(this, len, buf, 18);
}


BOOL CCharacter::IsDirectPath(CCharacter* ch, BOOL isClose)
{
	if( m_mapRes == NULL || ch->m_mapRes == NULL )
		return FALSE;

	if( m_mapRes != ch->m_mapRes )
		return FALSE;

	int srcX, srcY, destX, destY;
	this->GetParameterValue(VAR_CURXPOS, srcX);
	this->GetParameterValue(VAR_CURYPOS, srcY);
	ch->GetParameterValue(VAR_CURXPOS, destX);
	ch->GetParameterValue(VAR_CURYPOS, destY);

	return m_mapRes->CMapRes::IsDirectPath(srcX, srcY, destX, destY, isClose);
}


void CCharacter::SetSectionList(std::vector<CCharacter*>* sl)
{
	m_sectionList = sl;
}


std::vector<CCharacter*>* CCharacter::GetSectionList()
{
	return m_sectionList;
}


int CCharacter::GetWeaponProperty(int position, BOOL isArrowProperty)
{
	return m_characterPInfo.attack;
}


BOOL CCharacter::IsSiegeMode()
{
	return this->IsItPossible(MAPPROPERTY_SIEGE);
}


bool CCharacter::IsBattleFieldMode()
{
	if( m_mapRes == NULL )
		return false;

	return m_mapRes->IsBattleField();
}


bool CCharacter::IsTargetInBattleField(CCharacter* ch, unsigned long flag, BOOL& result)
{
	result = TRUE;

	if( ch == NULL )
		return false;

	if( !this->CCharacter::IsBattleFieldMode() )
		return false;

	if( !(flag & 4) && this->GetCampID() == ch->GetCampID() )
		result = FALSE;

	return true;
}


bool CCharacter::IsActor()
{
	return false;
}


int CCharacter::GetType()
{
	return m_type;
}


CMapRes* CCharacter::GetMapRes()
{
	return m_mapRes;
}


BOOL CCharacter::IsRightProperty(int property)
{
	return FALSE;
}


void CCharacter::OnShowEffect(int effect)
{
}


void CCharacter::OnShowEffect3(int effect, int numdata)
{
}


void CCharacter::OnShowScript(const char* In_Msg)
{
}


int CCharacter::GetEffectState()
{
	return 0;
}


void CCharacter::OnMsgFromItemServer(unsigned long AID, CITZMsg* reqMsg)
{
}


char CCharacter::GetCampID()
{
	return 0;
}


void CCharacter::SetCampID(char campID)
{
}


int CCharacter::GetEffective(int index, int enumVal)
{
	return 0;
}


void CCharacter::UpdateEffective(int index, int val, int enumVal)
{
}


int CCharacter::SetEffective(int index, int time, int val1, int val2, int val3, BOOL isSendClient)
{
	return 0;
}


void CCharacter::ResetEffective(int index, int val)
{
}


void CCharacter::GetModifiedHealAmount(int& healAmount)
{
}


int CCharacter::GetNeighborPlayerNum()
{
	return m_neighborCache.CNeighborCache::GetNum();
}


int CCharacter::GetInstantVar(const CInstantVar::enumVAR in_Var)
{
	return m_InstantVar(in_Var);
}


void CCharacter::SetInstantVar(const CInstantVar::enumVAR in_Var, const int in_Data)
{
	m_InstantVar(in_Var, in_Data);
}
