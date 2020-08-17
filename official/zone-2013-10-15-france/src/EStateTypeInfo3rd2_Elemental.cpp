#include "CharacterMgr.h"
#include "Enum.h"
#include "EStateTypeInfo3rd2_Elemental.h"
#include "PC.h"
#include "SkillStuff.h"
#include "ZoneProcessStuff.h"


ESTATE_CIRCLE_OF_FIRE_OPTION::ESTATE_CIRCLE_OF_FIRE_OPTION() // 970.h
: ESTATE(EFST_CIRCLE_OF_FIRE_OPTION, "EFST_CIRCLE_OF_FIRE_OPTION")
{
}


ESTATE_CIRCLE_OF_FIRE_OPTION::~ESTATE_CIRCLE_OF_FIRE_OPTION() // ???
{
}


bool ESTATE_CIRCLE_OF_FIRE_OPTION::SetCheckup(CActor* in_cpActor, int& io_Time, int& io_Val1, int& io_Val2, int& io_val3) // ???
{
	in_cpActor->ResetEffective(m_EfstID, 0);
	return true;
}


void ESTATE_CIRCLE_OF_FIRE_OPTION::SetComplete(CActor* in_cpActor, const int in_Time, const int in_Val1, const int in_Val2, const int in_Val3) // ???
{
}


void ESTATE_CIRCLE_OF_FIRE_OPTION::ResetComplete(CActor* in_cpActor, const int in_Val1, const int in_Val2, const int in_Val3) // ???
{
}


namespace {
class CIRCLE_OF_FIRE_OPTIONoperation : public SkillStuff::Operation_BT
{
public:
	virtual void operator()(CActor* in_cpActor) const
	{
		if( in_cpActor->IsTarget(m_cpOwnerPlayer, 0) && in_cpActor != m_cpOwnerPlayer )
			const_cast<CIRCLE_OF_FIRE_OPTIONoperation*>(this)->m_TargetActors.push_back(in_cpActor);
	}

	void final(const int in_skLevel, const int in_originXpos, const int in_originYpos, const int in_ATKpercent) const
	{
		if( m_TargetActors.size() == 0 )
			return;

		SKILLATTACK_MSG msg;
		msg.SKID = SKID_EL_CIRCLE_OF_FIRE;
		msg.level = -1;
		msg.skLevel = 1;
		msg.xPos = in_originXpos;
		msg.yPos = in_originYpos;
		msg.count = 1;
		msg.actionType = ACTION_SPLASH;
		m_cpNpcElemental->CActor::Broadcast_ZC_NOTIFY_SKILL2(m_cpOwnerPlayer->GetAccountID(), SKID_EL_CIRCLE_OF_FIRE, 1);

		for( std::vector<CActor*>::const_iterator iter = m_TargetActors.begin(); iter != m_TargetActors.end(); ++iter )
		{
			CActor* cpTargetActor = *iter;
			msg.targetAID = cpTargetActor->GetAccountID();

			if( m_cpNpcElemental->CNpcElemental::SkillAttackExt(&msg, in_ATKpercent, 100, false) )
			{
				PosInfo src;
				src.x = in_originXpos;
				src.y = in_originYpos;

				PosInfo dest;
				cpTargetActor->GetParameterValue(VAR_CURXPOS, dest.x);
				cpTargetActor->GetParameterValue(VAR_CURYPOS, dest.y);

				PosInfo newPos;
				m_cpOwnerPlayer->CActor::GetPushedPosition(src, dest, 3, newPos);

				CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(m_cpOwnerPlayer, cpTargetActor, CM_KNOCKBACK, newPos.x, newPos.y, 1, 0);
			}
		}
	}

private:
	/* this+ 0 */ //SkillStuff::Operation_BT baseclass_0;
	/* this+ 4 */ CPC* m_cpOwnerPlayer;
	/* this+ 8 */ CNpcElemental* m_cpNpcElemental;
	/* this+12 */ std::vector<CActor*> m_TargetActors;

public:
	CIRCLE_OF_FIRE_OPTIONoperation(CPC* in_cpOwnerPlayer, CNpcElemental* in_cpNpcElemental) : m_cpOwnerPlayer(in_cpOwnerPlayer), m_cpNpcElemental(in_cpNpcElemental) { }
};
}; // namespace


template<typename T, class F> void for_each(T& _Cont, F& _Func) /// @custom //TODO
{
	std::for_each(_Cont.begin(), _Cont.end(), _Func);
}


void ESTATE_CIRCLE_OF_FIRE_OPTION::Operation(CPC* in_cpPlayer, const int in_ATKpercent) // 2787-2809
{
	if( GetServerRandom(0, 20000) % 100 < 25 )
		return;

	CMapRes* cpMapRes = in_cpPlayer->CCharacter::GetMapRes();
	if( cpMapRes == NULL )
		return;

	CNpcElemental* cpNpcElemental = in_cpPlayer->CPC::GetNpcElemental();
	if( cpNpcElemental == NULL )
		return;

	int xPos, yPos;
	in_cpPlayer->GetParameterValue(VAR_CURXPOS, xPos);
	in_cpPlayer->GetParameterValue(VAR_CURYPOS, yPos);

	CIRCLE_OF_FIRE_OPTIONoperation operation(in_cpPlayer, cpNpcElemental);
	for_each(SkillStuff::GetNeighborActorList(cpMapRes, xPos, yPos, 1), operation);
	operation.CIRCLE_OF_FIRE_OPTIONoperation::final(1, xPos, yPos, in_ATKpercent);
}
