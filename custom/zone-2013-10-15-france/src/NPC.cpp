#include "CharacterMgr.h"
#include "Enum.h"
#include "NPC.h"
#include "Common/Packet.h"


void CNPC::SetEffectState(int state) // 1399-1420
{
	if ( state )
	{
		m_characterPInfo.effectState |= state;
	}
	else
	{
		m_characterPInfo.effectState &= 0xFFFFFFF8;

		this->ResetEffective(EFST_HIDING, 0);
		this->ResetEffective(EFST_CLOAKING, 0);
		this->ResetEffective(EFST_CLOAKINGEXCEED, 0);
	}

	this->CNPC::MultiCastStateInfo();
}


void CNPC::MultiCastStateInfo() // 1561-1570
{
	PACKET_ZC_STATE_CHANGE3 outpacket;
	outpacket.PacketType = HEADER_ZC_STATE_CHANGE3;
	outpacket.AID = this->GetAccountID();
	outpacket.bodyState = static_cast<short>(m_characterPInfo.bodyState);
	outpacket.healthState = static_cast<short>(m_characterPInfo.healthState);
	outpacket.effectState = m_characterPInfo.effectState;
	outpacket.isPKModeON = false;
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


BOOL CNPC::IsEnable() // 3421-3424
{
	return (m_characterPInfo.effectState & 2) != 2;
}


void CNPC::Enable() // 3427-3429
{
	this->SetEffectState(0);
}


void CNPC::Disable() // 3432-3434
{
	this->SetEffectState(2);
}


void CNPC::OnResetMyMob() // 5014-5019
{
	for( std::list<MYMOBDATA>::iterator it = m_myMobList.begin(); it != m_myMobList.end(); ++it )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, it->AID, CM_DISAPPEAR, 1, 0, 0, 0);

	m_myMobList.clear();
}
