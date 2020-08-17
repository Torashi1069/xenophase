#include "CharSkill.h"
#include "CharacterMgr.h"
#include "ItemLog.h"
#include "CITPMgr.hpp"
#include "MapResMgr.h"
#include "CNpcMob.hpp"
#include "CSkill.hpp"
#include "CSkillTypeInfoMgr.hpp"
#include "Common/Packet.h"
#include "shared.h"


CSkill::CSkill(void) // line 36
{	
	m_GroupUniqueID = 0;
	m_mapRes = NULL;
	m_type = SKILL_TYPE;
	_snprintf(m_Name, sizeof(m_Name), "UNKNOWN");
}


CSkill::~CSkill(void) // line 43
{
}


hook_method<const char* (CSkill::*)(void)> CSkill::_GetNamePtr(SERVER, "CSkill::GetNamePtr");
const char* CSkill::GetNamePtr(void) // line 65 (Skill.h)
{
	return (this->*_GetNamePtr)();

	return m_Name;
}


hook_method<void (CSkill::*)(const unsigned int in_GroupUniqueID, short x, short y, CMapRes* mapRes, unsigned char job, unsigned long creatorAID, unsigned long expiredTime, short level, unsigned short SKID, int par1, int par2)> CSkill::_Init2(SERVER, "CSkill::Init2");
void CSkill::Init2(const unsigned int in_GroupUniqueID, short x, short y, CMapRes* mapRes, unsigned char job, unsigned long creatorAID, unsigned long expiredTime, short level, unsigned short SKID, int par1, int par2) // line 58
{
	return (this->*_Init2)(in_GroupUniqueID, x, y, mapRes, job, creatorAID, expiredTime, level, SKID, par1, par2);

	this->CCharacter::Init();

	DWORD now = timeGetTime();

	m_GroupUniqueID = in_GroupUniqueID;
	m_mapRes = mapRes;
	m_mapID = mapRes->CMapRes::GetID();
	m_skillInfo.job = job;
	m_skillInfo.originalJob = job;
	m_skillInfo.xPos = x;
	m_skillInfo.operateTime = now + 1500;
	m_skillInfo.expiredTime = expiredTime;
	m_skillInfo.level = level;
	m_fireWallIndex = par2;
	m_skillInfo.yPos = y;
	m_skillInfo.hp = par1;
	m_expiredCount = par1;
	m_skillInfo.MoveReqLastTime = now;
	m_skillInfo.birthTime = now;
	m_skillInfo.creatorAID = creatorAID;
	m_skillInfo.state = 3;
	m_skillInfo.creatorPos.x = 0;
	m_skillInfo.creatorPos.y = 0;
	m_skillTimeInfo.lastHPMinusTime = 0;
	m_dwErrorCount = 0;
	m_property = 0;
	m_trapState = 0;
	m_master = NULL;
	m_targetAID = 0;
	m_reactSKID = 0;
	this->CSkill::SetSKID(SKID);

	m_master = g_characterMgr->CCharacterMgr::FastFindCharacter(creatorAID);
	if( m_master != NULL )
	{
		m_master->GetParameterValue(VAR_CURXPOS, m_skillInfo.creatorPos.x);
		m_master->GetParameterValue(VAR_CURYPOS, m_skillInfo.creatorPos.y);
	}

	switch( SKID )
	{
	case SKID_AL_WARP:
		m_warpSize = par1;
	break;
	case SKID_PR_SANCTUARY:
	case SKID_WZ_QUAGMIRE:
	case SKID_AM_DEMONSTRATION:
	case SKID_CR_GRANDCROSS:
		m_property |= 2u;
	break;
	case SKID_WZ_FIREPILLAR:
		m_property |= 9u;
		m_property |= 2u;
		m_skillInfo.operateTime = now;
	break;
	case SKID_WZ_WATERBALL:
		m_targetAID = par1;
		m_expiredCount = par2;
	break;
	case SKID_WZ_ICEWALL:
		g_mapResMgr->CMapResMgr::UpdateTileInfo(m_mapRes, x, y, 5, 0);
	break;
	case SKID_HT_BLASTMINE:
	case SKID_HT_CLAYMORETRAP:
		m_property |= 0xBu;
		m_skillInfo.operateTime = now + 400;
	break;
	case SKID_HT_TALKIEBOX:
		m_property |= 9u;
		m_property |= 4u;
	break;
	case SKID_SA_VOLCANO:
	case SKID_SA_DELUGE:
	case SKID_SA_VIOLENTGALE:
		m_property |= 2u;
	// fall through
	case SKID_SA_LANDPROTECTOR:
	case SKID_HP_BASILICA:
	case SKID_PA_GOSPEL:
	case SKID_HW_GRAVITATION:
		if( m_master != NULL )
			g_characterMgr->CCharacterMgr::SendMsg(0, m_master, 0xD2u, this->GetAccountID(), 0, 0, 0);
	break;
	case SKID_BD_DRUMBATTLEFIELD:
	case SKID_BD_RINGNIBELUNGEN:
	case SKID_BD_INTOABYSS:
	case SKID_BD_SIEGFRIED:
	case SKID_BA_WHISTLE:
	case SKID_BA_ASSASSINCROSS:
	case SKID_BA_POEMBRAGI:
	case SKID_BA_APPLEIDUN:
	case SKID_DC_HUMMING:
	case SKID_DC_FORTUNEKISS:
	case SKID_DC_SERVICEFORYOU:
		m_property |= 4u;
	break;
	case SKID_NPC_GRANDDARKNESS:
	case SKID_PF_FOGWALL:
		m_property |= 2u;
	break;
	case SKID_GS_GROUNDDRIFT:
	case SKID_NJ_KAENSIN:
	case SKID_DE_WAVE:
	case SKID_DE_WATERATTACK:
	case SKID_WZ_SIGHTBLASTER:
		m_property |= 8u;
		m_skillInfo.operateTime = now;
	break;
	case SKID_NPC_EVILLAND:
	case SKID_NC_NEUTRALBARRIER:
	case SKID_SC_DIMENSIONDOOR:
	case SKID_SC_CHAOSPANIC:
	case SKID_SO_WARMER:
		m_property |= 2u;
	break;
	case SKID_HT_SKIDTRAP:
	case SKID_HT_LANDMINE:
	case SKID_HT_ANKLESNARE:
	case SKID_HT_SHOCKWAVE:
	case SKID_HT_FLASHER:
	case SKID_HT_FREEZINGTRAP:
	case SKID_MA_SKIDTRAP:
	case SKID_MA_LANDMINE:
	case SKID_MA_FREEZINGTRAP:
		m_property |= 8u;
	// fall through
	case SKID_HT_SANDMAN:
	case SKID_MA_SANDMAN:
		m_property |= 3u;
		m_trapState = 1;
		m_skillInfo.operateTime = now + 400;
	break;
	default:
	break;
	}

	if( m_SKID != SKID_RG_GRAFFITI )
		this->CSkill::UpdateNeighborhood();
}


namespace
{

hook_func<mystd::vector<int> (__cdecl *)(void)> _InitAttackedSKJobTbl(SERVER, "?InitAttackedSKJobTbl@?A0x19c1cc07@@YA?AV?$vector@HV?$allocator@H@std@@@std@@XZ");
mystd::vector<int> __cdecl InitAttackedSKJobTbl(void) // line 2360
{
	return (_InitAttackedSKJobTbl)();

	//TODO
}

};


hook_method<int (CSkill::*)(CCharacter* ch, unsigned long flag)> CSkill::_IsTarget(SERVER, "CSkill::IsTarget");
int CSkill::IsTarget(CCharacter* ch, unsigned long flag) // line 2371
{
	return (this->*_IsTarget)(ch, flag);

	static mystd::vector<int> AttackedSKJobTbl = InitAttackedSKJobTbl();

	if( flag & 2 && m_property & 1 )
		return 1;

	mystd::vector<int>::const_iterator it;

	for( it = AttackedSKJobTbl.begin(); it != AttackedSKJobTbl.end(); ++it )
		if( *it == m_skillInfo.job )
			break;

	return ( it != AttackedSKJobTbl.end() ) ? 1 : 0;
}


hook_method<unsigned long (CSkill::*)(void)> CSkill::_GetState(SERVER, "CSkill::GetState");
unsigned long CSkill::GetState(void) // line 85 (Skill.h)
{
	return (this->*_GetState)();

	return m_skillInfo.state;
}


hook_method<int (CSkill::*)(void)> CSkill::_OnProcess(SERVER, "CSkill::OnProcess");
int CSkill::OnProcess(void) // line 747
{
	return (this->*_OnProcess)();

	if( m_dwErrorCount >= 4 )
		return 0;

	m_master = g_characterMgr->CCharacterMgr::FastFindCharacter(m_skillInfo.creatorAID);
	if( m_master == NULL )
		return 0;

	if( m_master->CCharacter::GetMapRes() != m_mapRes )
		return 0;

	this->CheckCommandQueue();
	if( timeGetTime() > m_skillInfo.expiredTime )
	{
		int masterJob;
		if( m_master->GetType() != PC_TYPE )
			m_master->GetParameterValue(VAR_JOB, masterJob);
		else
			masterJob = ((CPC*)m_master)->CPC::GetCategorySecondJob();

		if( masterJob == JT_HUNTER && ( m_trapState == 0 || m_trapState == 1 ) && m_skillInfo.job != 140 && g_skillTypeInfoMgr->CSkillTypeInfoMgr::IsSkillCategory(m_SKID, 0) == 1 )
		{
			IVItItem item;
			item.m_ID = 1065; // Booby_Trap
			item.m_count = 1;
			item.m_isIdentified = false;

			ITEM_INFO itemInfo;
			itemInfo.count = 1;
			itemInfo.unique_identity_numberV2 = 0i64;
			itemInfo.hire_expire_date = 0;
			itemInfo.IsIdentified = false;
			itemInfo.IsDamaged = false;
			itemInfo.RefiningLevel = 0;
			itemInfo.xPos = m_skillInfo.xPos;
			itemInfo.yPos = m_skillInfo.yPos;
			itemInfo.mapRes = m_master->CCharacter::GetMapRes();
			CopyEquipItemSlotInfo(&itemInfo.slot, NULL);

			if( g_characterMgr->CCharacterMgr::CreateItem(g_itpMgr->CITPMgr::GetITP(1065), &itemInfo) )
				g_itemLog->CItemLog::AddItemLog(0, (CPC *)m_master, NULL, &item, 0, itemInfo.count, NULL);
		}

		return 0;
	}

	switch( m_SKID )
	{
	case SKID_PR_SANCTUARY:
		int dur;

		if( m_master->GetType() == NPC_MOB_TYPE )
			dur = ((CNpcMob *)m_master)->CNpcMob::ChkGndSkillDurability();
		else
			dur = ((CPC *)m_master)->CPC::ChkGndSkillDurability();

		if( dur == 0 )
			return 0;
	break;
	case SKID_WZ_METEOR:
		if( m_trapState == 0 && timeGetTime() >= m_skillInfo.birthTime + 1000 * (m_expiredCount - 1) )
		{
			MSG_TYPE1_TWODWORD data;
			data.data1 = m_skillInfo.xPos;
			data.data2 = m_skillInfo.yPos;
			g_characterMgr->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, 111, m_SKID, m_skillInfo.level, (int)&data, 0);
			m_trapState = 2;
		}
	break;
	case SKID_WZ_ICEWALL:
		if( m_skillInfo.hp <= 0 )
			return 0;
	break;
	case SKID_GS_DESPERADO:
		if( m_trapState == 0 && timeGetTime() >= m_skillInfo.birthTime + 100 * (m_expiredCount - 1) )
		{
			MSG_TYPE1_TWODWORD data;
			data.data2 = m_skillInfo.yPos;
			data.data1 = m_skillInfo.xPos;
			g_characterMgr->CCharacterMgr::SendMsg(this, m_skillInfo.creatorAID, 111, m_SKID, m_skillInfo.level, (int)&data, 0);
			m_trapState = 2;
		}
	break;
	case SKID_NPC_EARTHQUAKE:
		if( timeGetTime() >= m_skillInfo.birthTime + 300 * (3 - m_expiredCount) )
		{
			MSG_TYPE4_FIVEDWORD data;
			data.data1 = m_AID;
			data.data2 = m_skillInfo.level;
			data.data3 = m_SKID;
			data.data4 = m_skillInfo.xPos;
			data.data5 = m_skillInfo.yPos;
			GetCharSkill()->CCharSkill::OnTouchedSkillObj(m_master, m_master, m_SKID, &data, 1);
			--m_expiredCount;
		}
	break;
	default:
	break;
	}

	if( m_skillInfo.job == 129 )
	{
		if( timeGetTime() > m_skillInfo.birthTime + 2000 )
			this->UpdateParameterValue(VAR_JOB, 128);
	}

	if( m_expiredCount > 0 )
	{
		this->CSkill::ProcessNeighborhood();
		this->CSkill::CheckStateChange();
	}

	return 1;
}


hook_method<void (CSkill::*)(void)> CSkill::_CheckStateChange(SERVER, "CSkill::CheckStateChange");
void CSkill::CheckStateChange(void) // line 895
{
	return (this->*_CheckStateChange)();

	//TODO
}


unsigned long CSkill::GetAccountID(void) // line 373
{
	return m_AID;
}


void CSkill::SetAccountID(unsigned long AID)
{
	m_AID = AID;
}


hook_method<int (CSkill::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CSkill::_OnMsg(SERVER, "CSkill::OnMsg");
int CSkill::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // line 382
{
	return (this->*_OnMsg)(sender, receiver, msgID, par1, par2, par3, par4);

	//TODO
}


hook_method<void (CSkill::*)(COMMAND_QUEUE* command)> CSkill::_InsertCommand(SERVER, "CSkill::InsertCommand");
void CSkill::InsertCommand(COMMAND_QUEUE* command) // line 3967
{
	return (this->*_InsertCommand)(command);

	//TODO
}


hook_method<void (CSkill::*)(void)> CSkill::_CheckCommandQueue(SERVER, "CSkill::CheckCommandQueue");
void CSkill::CheckCommandQueue(void)
{
	return (this->*_CheckCommandQueue)();

	//TODO
}


hook_method<void (CSkill::*)(unsigned long commandID)> CSkill::_DisableCommand(SERVER, "CSkill::DisableCommand");
void CSkill::DisableCommand(unsigned long commandID)
{
	return (this->*_DisableCommand)(commandID);

	//TODO
}


hook_method<int (CSkill::*)(CCharacter* ch, int range)> CSkill::_IsMyArea(SERVER, "CSkill::IsMyArea");
int CSkill::IsMyArea(CCharacter* ch, int range)
{
	return (this->*_IsMyArea)(ch, range);

	//TODO
}


hook_method<void (CSkill::*)(CPC* other)> CSkill::_NotifyUpdateInfo(SERVER, "CSkill::NotifyUpdateInfo");
void CSkill::NotifyUpdateInfo(CPC* other)
{
	return (this->*_NotifyUpdateInfo)(other);

	switch( m_neighborCache.CNeighborCache::GetUpdateInfo(this, other) )
	{
	case CHARACTER_STATE_STAND:
	case CHARACTER_STATE_ENTER:
	{
		if( other->m_isLessEffect && (m_property & PROPERTY_HUNTERTRAP) == 0 && m_skillInfo.job != JT_WARPPORTAL && m_skillInfo.job != JT_PREWARPPORTAL )
		{// reduced effects
			PACKET_ZC_SKILL_ENTRY packet;
			packet.PacketType = HEADER_ZC_SKILL_ENTRY;
			packet.AID = m_AID;
			packet.creatorAID = m_skillInfo.creatorAID;
			packet.job = m_skillInfo.job;
			packet.xPos = m_skillInfo.xPos;
			packet.yPos = m_skillInfo.yPos;
			packet.isVisible = (m_trapState == 0);
			other->CPC::Send(sizeof(packet), (char*)&packet);
		}
		else
		if( m_SKID == SKID_RG_GRAFFITI )
		{// graffiti
			PACKET_ZC_SKILL_ENTRY2 packet;
			packet.PacketType = HEADER_ZC_SKILL_ENTRY2;
			packet.AID = m_AID;
			packet.job = m_skillInfo.job;
			packet.creatorAID = m_skillInfo.creatorAID;
			packet.yPos = m_skillInfo.yPos;
			packet.xPos = m_skillInfo.xPos;
			packet.isContens = 1;
			packet.isVisible = (m_trapState == 0);
			memcpy(packet.msg, m_talkBoxContents, sizeof(packet.msg));
			Trace("Send Client Msg: %s\n", packet.msg);
			other->CPC::Send(sizeof(packet), (char*)&packet);
		}
		else
		{// normal skill
			PACKET_ZC_SKILL_ENTRY packet;
			packet.PacketType = HEADER_ZC_SKILL_ENTRY;
			packet.AID = m_AID;
			packet.creatorAID = m_skillInfo.creatorAID;
			packet.job = m_skillInfo.job;
			packet.xPos = m_skillInfo.xPos;
			packet.yPos = m_skillInfo.yPos;
			packet.isVisible = (m_trapState == 0);
			other->CPC::Send(sizeof(packet), (char*)&packet);
		}
	}
	break;
	case CHARACTER_STATE_EXIT:
	{
		PACKET_ZC_SKILL_DISAPPEAR packet;
		packet.PacketType = HEADER_ZC_SKILL_DISAPPEAR;
		packet.AID = m_AID;
		other->CPC::Send(sizeof(packet), (char*)&packet);
	}
	break;
	default:
	break;
	}
}


hook_method<void (CSkill::*)(void)> CSkill::_OnDisappear(SERVER, "CSkill::OnDisappear");
void CSkill::OnDisappear(void)
{
	return (this->*_OnDisappear)();

	//TODO
}


hook_method<short (CSkill::*)(void)> CSkill::_GetxPos(SERVER, "CSkill::GetxPos");
short CSkill::GetxPos(void) // line 1821-1823
{
	return (this->*_GetxPos)();

	return m_skillInfo.xPos;
}


hook_method<short (CSkill::*)(void)> CSkill::_GetyPos(SERVER, "CSkill::GetyPos");
short CSkill::GetyPos(void) // line 1826-1828
{
	return (this->*_GetyPos)();

	return m_skillInfo.yPos;
}


hook_method<int (CSkill::*)(unsigned short id, int& value)> CSkill::_GetParameterValue(SERVER, "CSkill::GetParameterValue");
int CSkill::GetParameterValue(unsigned short id, int& value)
{
	return (this->*_GetParameterValue)(id, value);

	//TODO
}


hook_method<int (CSkill::*)(unsigned short id, int value)> CSkill::_UpdateParameterValue(SERVER, "CSkill::UpdateParameterValue");
int CSkill::UpdateParameterValue(unsigned short id, int value)
{
	return (this->*_UpdateParameterValue)(id, value);

	//TODO
}


hook_method<unsigned short (CSkill::*)(void)> CSkill::_GetSKID(SERVER, "CSkill::GetSKID");
unsigned short CSkill::GetSKID(void) // line 356-358
{
	return (this->*_GetSKID)();

	return m_SKID;
}


hook_method<void (CSkill::*)(unsigned short SKID)> CSkill::_SetSKID(SERVER, "CSkill::SetSKID");
void CSkill::SetSKID(unsigned short SKID)
{
	return (this->*_SetSKID)(SKID);

	m_SKID = SKID;
}


hook_method<int (CSkill::*)(const unsigned long in_AID, const unsigned short in_SKID, const int in_SKLevel, const short in_x, const short in_y, CMapRes* const in_cpMapRes, unsigned long& io_ExpiredTime)> CSkill::_IsPossibleCreateSkill(SERVER, "CSkill::IsPossibleCreateSkill");
int CSkill::IsPossibleCreateSkill(const unsigned long in_AID, const unsigned short in_SKID, const int in_SKLevel, const short in_x, const short in_y, CMapRes* const in_cpMapRes, unsigned long& io_ExpiredTime)
{
	return (this->*_IsPossibleCreateSkill)(in_AID, in_SKID, in_SKLevel, in_x, in_y, in_cpMapRes, io_ExpiredTime);

	//TODO
}


hook_method<void (CSkill::*)(void)> CSkill::_UpdateNeighborhood(SERVER, "CSkill::UpdateNeighborhood");
void CSkill::UpdateNeighborhood(void)
{
	return (this->*_UpdateNeighborhood)();

	//TODO
}


hook_method<void (CSkill::*)(void)> CSkill::_ProcessNeighborhood(SERVER, "CSkill::ProcessNeighborhood");
void CSkill::ProcessNeighborhood(void)
{
	return (this->*_ProcessNeighborhood)();

	//TODO
}
