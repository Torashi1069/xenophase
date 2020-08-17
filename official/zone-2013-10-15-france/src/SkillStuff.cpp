#include "Character.h"
#include "CharacterMgr.h"
#include "MapRes.h"
#include "PC.h"
#include "SkillStuff.h"


namespace SkillStuff
{


const std::vector<CCharacter*> GetNeighborCharacterList(CMapRes* in_cpMapRes, const int in_originXpos, const int in_originYpos, const int in_Radius)
{
	std::vector<CCharacter*> targetlist;

	if( in_cpMapRes != NULL )
	{
		NEIGHBORHOOD_SECTION Neighborhood = {};
		in_cpMapRes->CMapRes::GetNeighborhoodSections(in_originXpos, in_originYpos, in_Radius, &Neighborhood);

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

				int targetXpos = 0, targetYpos = 0;
				cpTargetCH->GetParameterValue(VAR_CURXPOS, targetXpos);
				cpTargetCH->GetParameterValue(VAR_CURYPOS, targetYpos);

				if( abs(in_originXpos - targetXpos) > in_Radius || abs(in_originYpos - targetYpos) > in_Radius )
					continue;

				targetlist.push_back(cpTargetCH);
			}
		}
	}

	return targetlist;
}


const std::vector<CActor*> GetNeighborActorList(CMapRes* in_cpMapRes, const int in_originXpos, const int in_originYpos, const int in_Radius)
{
	std::vector<CActor*> targetlist;

	if( in_cpMapRes != NULL )
	{
		NEIGHBORHOOD_SECTION Neighborhood = {};
		in_cpMapRes->CMapRes::GetNeighborhoodSections(in_originXpos, in_originYpos, in_Radius, &Neighborhood);

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

				if( !cpTargetCH->IsActor() )
					continue;

				int targetXpos = 0, targetYpos = 0;
				cpTargetCH->GetParameterValue(VAR_CURXPOS, targetXpos);
				cpTargetCH->GetParameterValue(VAR_CURYPOS, targetYpos);

				if( abs(in_originXpos - targetXpos) > in_Radius || abs(in_originYpos - targetYpos) > in_Radius )
					continue;

				CActor* cpTargetActor = static_cast<CActor*>(cpTargetCH);
				targetlist.push_back(cpTargetActor);
			}
		}
	}

	return targetlist;
}


void PartyOperation(CPC* in_cpPlayer, const int in_RadiusRange, Operation_BT& in_Operation, const bool in_bMustIncludePlayer)
{
	if( in_cpPlayer->m_groupMember.size() != 0 )
	{
		for( std::list<unsigned long>::iterator iter = in_cpPlayer->m_groupMember.begin(); iter != in_cpPlayer->m_groupMember.end(); ++iter )
		{
			CPC* memberPC = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(*iter, PC_TYPE);
			if( memberPC != NULL && in_cpPlayer->IsMyArea(memberPC, in_RadiusRange) && !memberPC->CPC::IsDeadState() )
				in_Operation.operator()(memberPC);
		}
	}
	else
	{
		if( in_bMustIncludePlayer )
		{
			if( !in_cpPlayer->CPC::IsDeadState() )
				in_Operation.operator()(in_cpPlayer);
		}
	}
};


}; // namespace SkillStuff
