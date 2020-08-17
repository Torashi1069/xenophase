#include "PC.h"
#include "SkillScriptHandler.h"
#include "SkillTypeInfo3rd1_Mechanic.h"
#include "SkillTypeInfoMgr.h"


int SK_NC_MAINFRAME::OnMsg(CCharacter* sender, unsigned short receiver, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4) // 805-839
{
	switch( MsgID )
	{
	case SM_USE_SKILL:
	{
		if( sender->GetType() != PC_TYPE )
			break;

		CPC* senderPC = static_cast<CPC*>(sender);

		int plusDEF = this->SK_NC_MAINFRAME::GetIncDEFamount(skLevel);
		int preLV = senderPC->CCharacter::GetInstantVar(CInstantVar::PassivePreLV_NC_MAINFRAME);
		if( preLV > 0 )
			plusDEF -= this->SK_NC_MAINFRAME::GetIncDEFamount(preLV);
		senderPC->m_characterInfo.extItemDefPower += plusDEF;
		senderPC->UpdateParameterValue(VAR_ITEMDEFPOWER, 0);
		senderPC->CCharacter::SetInstantVar(CInstantVar::PassivePreLV_NC_MAINFRAME, skLevel);
	}
	break;
	case SM_RESET_SKILL:
	{
		if( sender->GetType() != PC_TYPE )
			break;

		CPC* senderPC = static_cast<CPC*>(sender);

		int preLV = senderPC->CCharacter::GetInstantVar(CInstantVar::PassivePreLV_NC_MAINFRAME);
		if( preLV > 0 )
		{
			int plusDEF = this->SK_NC_MAINFRAME::GetIncDEFamount(preLV);
			senderPC->m_characterInfo.extItemDefPower -= plusDEF;
			senderPC->UpdateParameterValue(VAR_ITEMDEFPOWER, 0);
			senderPC->CCharacter::SetInstantVar(CInstantVar::PassivePreLV_NC_MAINFRAME, 0);
		}
	}
	break;
	default:
	{
		this->CSkillTypeInfo::OnMsg(sender, receiver, MsgID, skLevel, targetID, par3, 0);
	}
	break;
	};

	return 0;
}


int SK_NC_MAINFRAME::GetIncDEFamount(const int in_Level) const // 842-847
{
	static STRUCT_SK_INTVALUE* IncDEFamountTbl = (STRUCT_SK_INTVALUE*)this->CSkillTypeInfo2::GetInfo(FUNC_SKILLDATA1);
	return IncDEFamountTbl->value[in_Level - 1];
}


int SK_NC_MAINFRAME::GetAdditionalMaxOverHeatLimitPoint(const int in_Level) const // 850-856
{
	static STRUCT_SK_INTVALUE* AdditionalMaxOverHeatLimitPointTbl = (STRUCT_SK_INTVALUE*)this->CSkillTypeInfo2::GetInfo(FUNC_SKILLDATA3);

	if( in_Level < 1 )
		return 0;

	return AdditionalMaxOverHeatLimitPointTbl->value[in_Level - 1];
}


int SK_NC_MAINFRAME::GetExpireOverHeatLimitPoint(CPC* in_cpPlayer) // 860-870
{
	static SK_NC_MAINFRAME* cpSK_NC_MAINFRAME = (SK_NC_MAINFRAME*)g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID_NC_MAINFRAME);

	if( in_cpPlayer->CPC::GetCategoryThirdJob() != JT_MECHANIC )
		return 0;

	int skLevel = in_cpPlayer->m_pcSkill.CPCSkill::GetSkillLevel(SKID_NC_MAINFRAME, 0);
	return cpSK_NC_MAINFRAME->SK_NC_MAINFRAME::GetAdditionalMaxOverHeatLimitPoint(skLevel) + 150;
}
