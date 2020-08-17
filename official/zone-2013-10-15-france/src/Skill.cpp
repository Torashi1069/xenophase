#include "CharacterMgr.h"
#include "Enum.h"
#include "MapResMgr.h"
#include "Skill.h"
#include "Common/Packet.h"


unsigned short CSkill::GetSKID() // 494-496
{
	return m_SKID;
}


CMyRect CSkill::GetArea() const // 612-653
{
	int left = m_skillInfo.xPos - m_RadiusRange;
	int top = m_skillInfo.yPos - m_RadiusRange;
	int width = 2 * m_RadiusRange + 1;
	int height = 2 * m_RadiusRange + 1;
	return CMyRect(left, top, width, height);
}


hook_func<int (CSkill::*)()> CSkill__OnProcess(EXEPATH(), "CSkill::OnProcess");
int CSkill::OnProcess() // 1002-1210
{
	return (this->*CSkill__OnProcess)(); //TODO
}


bool CSkill::IsMyArea(const int in_xPos, const int in_yPos) // 1962-1974
{
	CMyPoint in_Point(in_xPos, in_yPos);
	return this->CSkill::GetArea().CMyRect::IsMyPoint(in_Point);
}


void CSkill::OnDisappear() // 2268-2405
{
	if( m_SKID == SKID_WZ_ICEWALL )
		g_mapResMgr.CMapResMgr::UpdateTileInfo(m_mapRes, this->CSkill::GetxPos(), this->CSkill::GetyPos(), 0, m_skillInfo.creatorAID);

	switch( m_SKID )
	{
	case SKID_BA_DISSONANCE:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::BA_DISSONANCE_CNT, -1, 0, 0);
	break;
	case SKID_GC_POISONSMOKE:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::GC_POISONSMOKE_CNT, -1, 0, 0);
	break;
	case SKID_RA_ELECTRICSHOCKER:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::RA_ELECTRICSHOCKER_INSTALL_CNT, -1, 0, 0);
	break;
	case SKID_RA_MAGENTATRAP:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::RA_MAGENTATRAP_INSTALL_CNT, -1, 0, 0);
	break;
	case SKID_RA_COBALTTRAP:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::RA_COBALTTRAP_INSTALL_CNT, -1, 0, 0);
	break;
	case SKID_RA_MAIZETRAP:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::RA_MAIZETRAP_INSTALL_CNT, -1, 0, 0);
	break;
	case SKID_RA_VERDURETRAP:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::RA_VERDURETRAP_INSTALL_CNT, -1, 0, 0);
	break;
	case SKID_RA_FIRINGTRAP:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::RA_FIRINGTRAP_INSTALL_CNT, -1, 0, 0);
	break;
	case SKID_RA_ICEBOUNDTRAP:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::RA_ICEBOUNDTRAP_INSTALL_CNT, -1, 0, 0);
	break;
	case SKID_SC_MANHOLE:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::SC_MANHOLE_CNT, -1, 0, 0);
	break;
	case SKID_SC_DIMENSIONDOOR:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::SC_DIMENSIONDOOR_CNT, -1, 0, 0);
	break;
	case SKID_SC_CHAOSPANIC:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::SC_CHAOSPANIC_CNT, -1, 0, 0);
	break;
	case SKID_GN_WALLOFTHORN:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::GN_WALLOFTHORN_CNT, -1, 0, 0);
	break;
	case SKID_GN_HELLS_PLANT:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::GN_HELLS_PLANT_INSTALL_CNT, -1, 0, 0);
	break;
	case SKID_WM_POEMOFNETHERWORLD:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::WM_POEMOFNETHERWORLD_INSTALL_CNT, -1, 0, 0);
	break;
	case SKID_GN_THORNS_TRAP:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_INSTANTVAR_ADD, CInstantVar::GN_THORNS_TRAP_INSTALL_CNT, -1, 0, 0);
	break;
	case SKID_WM_SEVERE_RAINSTORM:
	{
		CCharacter* ownerCH = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(m_skillInfo.creatorAID);
		if( ownerCH != NULL && ownerCH->GetType() == PC_TYPE )
			ownerCH->m_fvarb_WearTakeOff_Forbid.FactorVAR::BOOLvar::Reset(SKID_WM_SEVERE_RAINSTORM);
	}
	break;
	};

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, CM_MODIFY_SKILLCOUNT, m_SKID, m_fireWallIndex, -1, 0);

	PACKET_ZC_SKILL_DISAPPEAR outpacket;
	outpacket.PacketType = HEADER_ZC_SKILL_DISAPPEAR;
	outpacket.AID = m_AID;
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


short CSkill::GetxPos() // 2408-2410
{
	return m_skillInfo.xPos;
}


short CSkill::GetyPos() // 2413-2415
{
	return m_skillInfo.yPos;
}


int CSkill::GetSkillLevel() // (113.h)
{
	return m_skillInfo.level;
}


unsigned long CSkill::GetExpireTime() // (138.h)
{
	return m_skillInfo.expiredTime;
}
