#include "CPCFriendClass.h"
#include "MapRes.h"
#include "PC.h"
#include "SectionMgr.h"


void CPCFriendClass::HPRecoveryProhibitionSet(CPC* in_cpPlayer)
{
	in_cpPlayer->m_HPAmount.CHPAmount::RecoveryProhibitionSet();
}


void CPCFriendClass::HPRecoveryProhibitionReset(CPC* in_cpPlayer)
{
	in_cpPlayer->m_HPAmount.CHPAmount::RecoveryProhibitionReset();
}


void CPCFriendClass::SPRecoveryProhibitionSet(CPC* in_cpPlayer)
{
	in_cpPlayer->m_SPAmount.CSPAmount::RecoveryProhibitionSet();
}


void CPCFriendClass::SPRecoveryProhibitionReset(CPC* in_cpPlayer)
{
	in_cpPlayer->m_SPAmount.CSPAmount::RecoveryProhibitionReset();
}


bool CPCFriendClass::CheckNPCAround(CPC* in_cpPlayer)
{
	if( in_cpPlayer == NULL )
		return false;

	CMapRes* cpMapRes = in_cpPlayer->m_mapRes;
	if( cpMapRes != NULL )
	{
		int orgXpos = in_cpPlayer->m_pathInfo.m_moveInfo.xPos;
		int orgYpos = in_cpPlayer->m_pathInfo.m_moveInfo.yPos;

		NEIGHBORHOOD_SECTION Neighborhood = {};
		cpMapRes->CMapRes::GetNeighborhoodSections(orgXpos, orgYpos, 3, &Neighborhood);

		for( size_t i = 0; i < countof(Neighborhood.section); ++i )
		{
			std::vector<CCharacter*>* section = Neighborhood.section[i];
			if( section == NULL )
				continue;

			for( std::vector<CCharacter*>::iterator iter = section->begin(); iter != section->end(); ++iter )
			{
				CCharacter* cpTargetCH = *iter;
				if( cpTargetCH == NULL )
					continue;

				if( cpTargetCH->GetType() != NPC_EVT_TYPE && cpTargetCH->GetType() != NPC_TYPE )
					continue;

				int targetXpos = 0, targetYpos = 0;
				cpTargetCH->GetParameterValue(VAR_CURXPOS, targetXpos);
				cpTargetCH->GetParameterValue(VAR_CURYPOS, targetYpos);

				if( abs(orgXpos - targetXpos) > 3 || abs(orgYpos - targetYpos) > 3 )
					continue;

				return true; // found a nearby npc.
			}
		}
	}

	return false; // no npcs in area.
}
