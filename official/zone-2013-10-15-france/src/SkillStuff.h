#pragma once
class CActor;
class CCharacter;
class CMapRes;


namespace SkillStuff
{


struct Operation_BT
{
public:
	virtual void operator()(CActor* in_cpActor) const = 0;
};


const std::vector<CCharacter*> GetNeighborCharacterList(CMapRes* in_cpMapRes, const int in_originXpos, const int in_originYpos, const int in_Radius);
const std::vector<CActor*> GetNeighborActorList(CMapRes* in_cpMapRes, const int in_originXpos, const int in_originYpos, const int in_Radius);
void PartyOperation(CPC* in_cpPlayer, const int in_RadiusRange, Operation_BT& in_Operation, const bool in_bMustIncludePlayer);


}; // namespace SkillStuff
