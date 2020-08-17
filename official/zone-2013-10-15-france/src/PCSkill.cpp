#include "CharacterMgr.h"
#include "Enum.h"
#include "PCSkill.h"
#include "ScriptEventHandler.h"
#include "SkillTypeInfo.h"
#include "SkillTypeInfo2_2(2).h"
#include "SkillTypeInfo3rd2_ShadowChaser.h"
#include "SkillTypeInfoMgr.h"
#include "AsyncDBWork/LoadWarpInfoADBWork.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
#include "AsyncDBWork/Skill3rd.inl"
#include "Common/Packet.h"
#include "shared/NCriticalErrorLog.h"


CPCSkill::CPCSkill() // 50-51
{
}


CPCSkill::~CPCSkill() // 54-55
{
}


void CPCSkill::Init(const bool in_bChangeJob) // 58-60
{
	this->CPCSkill::Reset(in_bChangeJob);
}


void CPCSkill::Reset(const bool in_bChangeJob) // 63-140
{
	m_warpXPos = 0;
	m_warpYPos = 0;
	m_encoreSKID = 0;
	m_encoreSkLevel = 0;
	m_warpExpireTime = 0;
	m_warpSize = 0;
	m_plusItemWeight = 0;
	m_sanctuaryCnt = 0;
	m_stormGustCnt = 0;
	m_playSkillCount = 0;
	m_warpCount = 0;
	m_playStartedTime = 0;
	m_graffitiAID = 0;
	m_partnerAID = 0;
	m_isEncoreSkill = 0;
	m_pc = NULL;
	memset(m_talkBoxContents, '\0', sizeof(m_talkBoxContents));
	memset(m_graffitiContents, '\0', sizeof(m_graffitiContents));
	memset(m_fireWallCount, 0, sizeof(m_fireWallCount));
	memset(m_monsterCreatedBySkill, 0, sizeof(m_monsterCreatedBySkill));
	m_skill.clear();
	m_disposableSkill.clear();
	m_dynamicSkill.clear();
	m_warpInfo.clear();
	m_spellCastingSKID = 0;
	m_spellCastingSKLevel = 0;
	if( !in_bChangeJob )
		m_isSkillLoaded = 0;
	m_specialZoneList.clear();
	m_spiritsTime.clear();
	m_skillCondition = 0;
	m_abracadabraSKID = 0;
	m_plusItemWeightBySkill = 0;
	m_bCallPartner = 0;
	m_limitedSkill.clear();
	m_limitedSkill.clear();
	m_GDMasterParamList.clear();
	this->CPCSkill::ResetMillenniumShield();
	m_forceOfVanguard.clear();
	m_cursedCircleAIDList.clear();
	m_SkillFakeTypeList.clear();
}


void CPCSkill::SetMyOwner(CPC* pc) // 143-145
{
	m_pc = pc;
}


BOOL CPCSkill::IsConditionalSkill(unsigned short skillID) // 168-170
{
	return g_skillTypeInfoMgr.CSkillTypeInfoMgr::IsConditionalSkill(m_pc->m_characterInfo.job, skillID);
}


BOOL CPCSkill::AddSkill(unsigned short SKID, PC_SKILL_INFO* skInfo, SKILLINFO* skillData, const bool in_bNeedDBwork) // 187-302
{
	PC_SKILL_INFO* tmpSkillInfo = this->CPCSkill::GetSkill(SKID, FALSE);
	if( skInfo->type == 0 && tmpSkillInfo != NULL )
	{
		if( tmpSkillInfo->type != 4 )
			return FALSE;

		PC_SKILL_INFO* cpRG_PLAGIARISM = this->CPCSkill::GetSkill(SKID_RG_PLAGIARISM, FALSE);
		if( cpRG_PLAGIARISM != NULL )
		{
			SK_RG_PLAGIARISM::DATA PLAGIARISM = cpRG_PLAGIARISM->Data;
			unsigned short plagiarismSKID = PLAGIARISM.Imitation.SKID;
			int plagiarismSKLevel = PLAGIARISM.Imitation.SKLevel;

			if( plagiarismSKID == SKID && plagiarismSKLevel > 0 )
			{
				cpRG_PLAGIARISM->Data = 0;
				cpRG_PLAGIARISM->bDBupdateWhenLogout = true;
			}
		}

		PC_SKILL_INFO* cpSC_REPRODUCE = this->CPCSkill::GetSkill(SKID_SC_REPRODUCE, FALSE);
		if( cpSC_REPRODUCE != NULL )
		{
			SK_SC_REPRODUCE::DATA REPRODUCE = cpSC_REPRODUCE->Data;
			unsigned short reproduceSKID = REPRODUCE.Imitation.SKID;
			int reproduceSKLevel = REPRODUCE.Imitation.SKLevel;

			if( reproduceSKID == SKID && reproduceSKLevel > 0 )
			{
				cpSC_REPRODUCE->Data = 0;
				cpSC_REPRODUCE->bDBupdateWhenLogout = true;
			}
		}
	}

	CSkillTypeInfo* skillTypeInfo = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( skillTypeInfo == NULL )
		return FALSE;

	if( skInfo->type == 0
		&& SKID != SKID_NV_BASIC
		&& SKID != SKID_SYS_FIRSTJOBLV
		&& SKID != SKID_SYS_SECONDJOBLV
		&& !g_skillTypeInfoMgr.CSkillTypeInfoMgr::IsAvailableJob(m_pc->m_characterInfo.job, SKID)
		&& !skillTypeInfo->CSkillTypeInfo::IsEventSkill() )
		return FALSE;

	if( skInfo->type == 2 )
	{
		memcpy(&m_disposableSkill[SKID], skInfo, sizeof(*skInfo));
		if( SKID == SKID_AL_TELEPORT )
			m_pc->CPC::OnDisableItemMove();

		PACKET_ZC_ADD_SKILL outpacket;
		outpacket.PacketType = HEADER_ZC_AUTORUN_SKILL;
		memcpy_s(&outpacket.data, sizeof(outpacket.data), skillData, sizeof(*skillData));
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_pc, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
		return FALSE;
	}

	if( tmpSkillInfo != NULL )
	{
		memcpy_s(tmpSkillInfo, sizeof(*tmpSkillInfo), skInfo, sizeof(*skInfo));
	}
	else
	{
		memcpy(&m_skill[SKID], skInfo, sizeof(*skInfo));
		if( in_bNeedDBwork )
			Skill3rd::Update(m_pc, CSkill3rdUpdateADBWork::AFTER_ACTION_NONE, SKID, skInfo);
	}

	if( skillData != NULL && SKID != SKID_SYS_FIRSTJOBLV && SKID != SKID_SYS_SECONDJOBLV )
	{
		PACKET_ZC_ADD_SKILL outpacket;
		outpacket.PacketType = HEADER_ZC_ADD_SKILL;
		memcpy_s(&outpacket.data, sizeof(outpacket.data), skillData, sizeof(*skillData));
		if( this->CPCSkill::IsConditionalSkill(SKID) == TRUE )
			outpacket.data.upgradable = false;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_pc, CM_SEND_PACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
	}

	this->CPCSkill::ApplyPassiveSkill(SKID, skInfo->level);
	return TRUE;
}


void CPCSkill::DeleteSkill(unsigned short SKID, BOOL isDisposable) // 451-524
{
	if( isDisposable )
	{
		SKILL_CONTAINER::iterator iter = m_disposableSkill.find(SKID);
		if( iter != m_disposableSkill.end() )
		{
			m_disposableSkill.erase(iter);
			m_pc->CPC::OnEnableItemMove(TRUE);
		}

		return;
	}

	SKILL_CONTAINER::iterator iter = m_skill.find(SKID);
	if( iter == m_skill.end() )
		return;

	switch( iter->second.type )
	{
	case DYNAMIC_SKILL:
	case DISPOSABLE_SKILL:
		--iter->second.count;

		if( g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID) == NULL )
			return;

		if( iter->second.count > 0 )
		{
			if( iter->second.type == DISPOSABLE_SKILL )
				iter->second.type = iter->second.typeBefore;

			return;
		}

		if( iter->second.level == 0 && !g_skillTypeInfoMgr.CSkillTypeInfoMgr::IsAvailableJob(m_pc->m_characterInfo.job, SKID) )
		{
			m_skill.erase(iter);
			return;
		}

		iter->second.type = FIXED_SKILL;
	break;
	case TEMPORARY_DISPOSABLE_SKILL:
		iter->second.type = FIXED_SKILL;
	break;
	case IMITATION_SKILL:
		m_skill.erase(iter);
	break;
	default:
		m_skill.erase(iter);
		if( SKID == SKID_ALL_INCCARRY )
			this->CPCSkill::UpdatePlusItemWeightBySkill();
	break;
	};
}


void CPCSkill::LoadWarpInfo() // 529-536
{
	CLoadWarpInfoADBWork* cpDBWork = new(std::nothrow) CLoadWarpInfoADBWork(m_pc->GetAccountID(), m_pc->CPC::GetCharacterID(), CLoadWarpInfoADBWork::LOAD_TYPE_PORTAL);
	if( cpDBWork == NULL )
		return;

	if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(cpDBWork) )
	{
		delete cpDBWork;
		return;
	}
}


void CPCSkill::SetWarpInfo(const WARPPORTAL_INFO& in_WarpInfo) // 539-552
{
	m_warpInfo.clear();

	for( size_t i = 0; i < 3; ++i )
	{
		if( in_WarpInfo.mapName[i] == NULL || in_WarpInfo.xPos[i] == 0 || in_WarpInfo.yPos[i] == 0 )
			continue;

		WARP_POSITION push_Data;
		push_Data.xPos = in_WarpInfo.xPos[i];
		push_Data.yPos = in_WarpInfo.yPos[i];
		memcpy_s(push_Data.mapName, sizeof(push_Data.mapName), in_WarpInfo.mapName[i], sizeof(in_WarpInfo.mapName[i]));

		m_warpInfo.push_back(push_Data);
	}
}


int CPCSkill::GetWarpInfoXpos(char xnum) // 579-581
{
	return m_warpInfo[xnum].xPos;
}


void CPCSkill::LoadStarPlaceInfo() // 584-591
{
	CLoadWarpInfoADBWork* cpDBWork = new(std::nothrow) CLoadWarpInfoADBWork(m_pc->GetAccountID(), m_pc->CPC::GetCharacterID(), CLoadWarpInfoADBWork::LOAD_TYPE_STAR_PLACE);
	if( cpDBWork == NULL )
		return;

	if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(cpDBWork) )
	{
		delete cpDBWork;
		return;
	}
}


void CPCSkill::SetStarPlaceInfo(const WARPPORTAL_INFO& in_WarpInfo) // 593-603
{
	m_warpInfo.clear();

	for( size_t i = 0; i < 3; ++i )
	{
		WARP_POSITION push_Data;
		push_Data.xPos = in_WarpInfo.xPos[i];
		push_Data.yPos = in_WarpInfo.yPos[i];
		memcpy_s(push_Data.mapName, sizeof(push_Data.mapName), in_WarpInfo.mapName[i], sizeof(in_WarpInfo.mapName[i]));

		m_warpInfo.push_back(push_Data);
	}
}


int CPCSkill::GetWarpInfo(WARPPORTAL_INFO* warpinfo) // 643-654
{
	memset(warpinfo, 0, sizeof(*warpinfo));

	std::deque<WARP_POSITION>::iterator iter;
	int i;
	for( iter = m_warpInfo.begin(), i = 0; iter != m_warpInfo.end() && i < 3; ++iter, ++i )
	{
		memcpy_s(warpinfo->mapName[i], sizeof(warpinfo->mapName[i]), iter->mapName, sizeof(iter->mapName));
		warpinfo->xPos[i] = iter->xPos;
		warpinfo->yPos[i] = iter->yPos;
	}

	return i;
}


void CPCSkill::UpdateWarpList(char* mapName, short xPos, short yPos) // 674-683
{
	for( std::deque<WARP_POSITION>::iterator iter = m_warpInfo.begin(); iter != m_warpInfo.end(); ++iter )
	{
		if( strncmp(iter->mapName, mapName, countof(iter->mapName)) == 0 )
		{
			iter->xPos = xPos;
			iter->yPos = yPos;
		}
	}
}


void CPCSkill::UpdateStarPlace(char* mapName, short num) // 686-751
{
	if( num == 100 )
	{// reset
		for( size_t num = 0; num < 3; ++num )
		{
			if( (size_t)num >= m_warpInfo.size() )
				continue;

			memcpy_s(m_warpInfo[num].mapName, sizeof(m_warpInfo[num].mapName), mapName, 16);
			m_warpInfo[num].xPos = 0;
			m_warpInfo[num].yPos = 0;
		}
	}
	else
	if( num < 200 )
	{// feeling
		if( num >= 3 || (size_t)num >= m_warpInfo.size() )
			return;

		if( strcmp(m_warpInfo[num].mapName, "") != 0 && m_warpInfo[num].mapName != NULL )
		{
			PACKET_ZC_STARSKILL outpacket;
			outpacket.PacketType = HEADER_ZC_STARSKILL;
			memcpy_s(outpacket.mapName, sizeof(outpacket.mapName), m_warpInfo[num].mapName, sizeof(m_warpInfo[num].mapName));
//			outpacket.monsterID = ?;
			outpacket.star = static_cast<unsigned char>(num);
			outpacket.result = 1;
			m_pc->Send(sizeof(outpacket), (char*)&outpacket);
		}
		else
		{
			PACKET_ZC_STARPLACE outpacket;
			outpacket.PacketType = HEADER_ZC_STARPLACE;
			outpacket.which = static_cast<char>(num);
			m_pc->Send(sizeof(outpacket), (char*)&outpacket);
		}
	}
	else
	{// hatred
		num -= 200;
		if( num >= 3 || (size_t)num >= m_warpInfo.size() )
			return;

		if( strcmp(m_warpInfo[num].mapName, "") != 0 && m_warpInfo[num].mapName != NULL )
		{
			PACKET_ZC_STARSKILL outpacket;
			outpacket.PacketType = HEADER_ZC_STARSKILL;
			memcpy_s(outpacket.mapName, sizeof(outpacket.mapName), m_warpInfo[num].mapName, sizeof(m_warpInfo[num].mapName));
//			outpacket.monsterID = ?;
			outpacket.star = static_cast<unsigned char>(num);;
			outpacket.result = 1;
			m_pc->Send(sizeof(outpacket), (char*)&outpacket);
		}
		else
		{
			PACKET_ZC_STARSKILL outpacket;
			outpacket.PacketType = HEADER_ZC_STARSKILL;
			memcpy_s(outpacket.mapName, sizeof(outpacket.mapName), mapName, 16);
			memcpy_s(m_warpInfo[num].mapName, sizeof(m_warpInfo[num].mapName), mapName, 16);
//			outpacket.monsterID = ?;
			outpacket.star = static_cast<unsigned char>(num);
			outpacket.result = 0;
			m_pc->OnShowEffect(432); //TODO: client's EF_ELECTRIC
			m_pc->OnShowEffect(543); //TODO: client's EF_HATED
			m_pc->Send(sizeof(outpacket), (char*)&outpacket);
		}
	}
}


PC_SKILL_INFO* CPCSkill::GetSkill(unsigned short SKID, BOOL isFixedSkill) // 755-767
{
	if( !isFixedSkill )
	{
	std::map<unsigned short,PC_SKILL_INFO>::iterator it = m_disposableSkill.find(SKID);
	if( it != m_disposableSkill.end() )
		return &it->second;
	}

	std::map<unsigned short,PC_SKILL_INFO>::iterator it = m_skill.find(SKID);
	if( it != m_skill.end() )
		return &it->second;

	return NULL; // not found.
}


short CPCSkill::GetSkillLevel(unsigned short SKID, BOOL isFixedSkill) // 770-806
{
	if( !isFixedSkill )
	{
	std::map<unsigned short,PC_SKILL_INFO>::iterator it = m_disposableSkill.find(SKID);
	if( it != m_disposableSkill.end() )
		return it->second.disposableLevel;
	}

	std::map<unsigned short,PC_SKILL_INFO>::iterator it = m_skill.find(SKID);
	if( it == m_skill.end() )
		return 0;

	if( it->second.type == 0 )
		return it->second.level;
	else
	if( isFixedSkill )
		return it->second.level;
	else
	if( it->second.type == 4 )
		return it->second.imitationLevel;
	else
	{
		return it->second.disposableLevel;
	}
}


int CPCSkill::GetSkillType(unsigned short SKID) // 1167-1177
{
	SKILL_CONTAINER::iterator it;
	
	it = m_disposableSkill.find(SKID);
	if( it != m_disposableSkill.end() )
		return it->second.type;
	
	it = m_skill.find(SKID);
	if( it != m_skill.end() )
		return it->second.type;

	return -1; // not found.
}


hook_func<void (__stdcall *)()> CPCSkill__GetSkillRange(EXEPATH(), "CPCSkill::GetSkillRange");
short CPCSkill::GetSkillRange(unsigned short SKID, short level) // 1180-1202
{
	short result;
	void* hookptr = CPCSkill__GetSkillRange;
	__asm push level
	__asm mov ax, SKID
	__asm mov ebx, this
	__asm call hookptr
	__asm mov result, ax
	return result; //TODO
}


void CPCSkill::NotifySkillInfoDelete(const int in_SKID) const // 1547-1552
{
	PACKET_ZC_SKILLINFO_DELETE packet;
	packet.PacketType = HEADER_ZC_SKILLINFO_DELETE;
	packet.SKID = in_SKID;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_pc, CM_SEND_PACKET, sizeof(packet), (int)&packet, 0, 0);
}


void CPCSkill::SetPlusItemWeight(int weight) // ??? (2649-2651)
{
	m_plusItemWeight = weight;
}


void CPCSkill::DestroyPlayingSkill() // 4217-4233
{
	for( std::vector<PLAY_SKILLINFO>::iterator iter = m_playSkillList.begin(); iter != m_playSkillList.end(); ++iter )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, iter->skAID, CM_SKILL_EXPIRETIME, 0, 0, 0, 0);

	m_playSkillList.clear();
	m_playSkillCount = 0;
	m_pc->ResetEffective(EFST_BDPLAYING, 0);
	m_pc->ResetEffective(EFST_SG_WARM, 0);
	m_pc->ResetEffective(EFST_SG_SUN_WARM, 0);
	m_pc->ResetEffective(EFST_SG_MOON_WARM, 0);
	m_pc->ResetEffective(EFST_SG_STAR_WARM, 0);
	m_pc->ResetEffective(EFST_LONGING, 0);
	m_pc->ResetEffective(EFST_DAURA, 0);
	m_partnerAID = 0;
}


void CPCSkill::ApplyPassiveSkill(unsigned short SKID, unsigned short level) // 4487-4506
{
	if( level >= 1 )
	{
		if( g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetType(SKID) == SKILLTYPE_PASSIVE )
			g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(m_pc, SKID, SM_USE_SKILL, level, 0, 0, 0);
	}

	switch( SKID )
	{
	case SKID_AL_WARP:
	{
		this->CPCSkill::LoadWarpInfo();
	}
	break;
	case SKID_RG_PLAGIARISM:
	{
		PC_SKILL_INFO* pRG_PLAGIARISM = this->CPCSkill::GetSkill(SKID_RG_PLAGIARISM, FALSE);
		if( pRG_PLAGIARISM == NULL )
			return;

		SK_RG_PLAGIARISM::DATA data(pRG_PLAGIARISM->Data);
		unsigned short ImitationSKID = data.Imitation.SKID;
		int ImitationSKLevel = data.Imitation.SKLevel;

		if( level > 0 )
		{
			if( ImitationSKID != 0 && ImitationSKLevel != 0 )
			{
				CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_pc, CM_SKILL_ADDIMITATION3rd, ImitationSKID, ImitationSKLevel, SKID_RG_PLAGIARISM, 0);
			}
		}
		else
		{
			PC_SKILL_INFO* pImitationSKinfo = this->CPCSkill::GetSkill(ImitationSKID, FALSE);
			if( pImitationSKinfo != NULL && pImitationSKinfo->type == IMITATION_SKILL )
			{
				this->CPCSkill::DeleteSkill(ImitationSKID, 0);
				this->CPCSkill::NotifySkillInfoDelete(ImitationSKID);
				pRG_PLAGIARISM->Data = 0;
				pRG_PLAGIARISM->bDBupdateWhenLogout = true;
			}
		}
	}
	break;
	case SKID_SG_FEEL:
	case SKID_TK_MISSION:
	case SKID_MB_MISSION:
	case SKID_DA_ZENYRANK:
	{
		this->CPCSkill::LoadStarPlaceInfo();
	}
	break;
	case SKID_SG_FUSION:
	{
		m_pc->ResetEffectState(EFFECTSTATE_STAR2);
	}
	break;
	case SKID_ALL_INCCARRY:
	{
		this->CPCSkill::UpdatePlusItemWeightBySkill();
	}
	break;
	};
}


hook_func<void (__stdcall *)()> CPCSkill__UpdatePlusItemWeightBySkill(EXEPATH(), "CPCSkill::UpdatePlusItemWeightBySkill");
void CPCSkill::UpdatePlusItemWeightBySkill() // 4509-4523
{
	void* hookptr = CPCSkill__UpdatePlusItemWeightBySkill;
	__asm mov eax, this
	__asm call hookptr
	return; // TODO
/*
	m_plusItemWeightBySkill = 0;

	short skLevel = this->CPCSkill::GetSkillLevel(SKID_ALL_INCCARRY, FALSE);
	if( skLevel > 0 )
	{
		SK_ALL_INCCARRY* cpSK_ALL_INCCARRY = static_cast<SK_ALL_INCCARRY*>(g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID_ALL_INCCARRY));
		if( cpSK_ALL_INCCARRY != NULL )
			m_plusItemWeightBySkill += cpSK_ALL_INCCARRY->CSkillTypeInfo2::GetData(FUNC_SKILLDATA1, skLevel);
	}

	m_pc->m_pcClientUpdater.CPCClientUpdater::NotifyParameter(VAR_MAXWEIGHT, m_pc->CPC::GetBodyMaxItemWeight());
*/
}


void CPCSkill::ResetMillenniumShield() // 4528-4537
{
	if( m_millenniumShieldList.empty() )
		return;

	m_millenniumShieldList.clear();

	if( m_pc == NULL )
		return;

	this->CPCSkill::NotifyMillenniumShieldCount(m_pc->CPC::IsSendable() != FALSE);
}


void CPCSkill::NotifyMillenniumShieldCount(bool option) // 4602-4617
{
	if( m_pc == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "NULL == m_pc");
		return;
	}

	if( option )
	{
		PACKET_ZC_MILLENNIUMSHIELD outpacket;
		outpacket.PacketType = HEADER_ZC_MILLENNIUMSHIELD;
		outpacket.AID = m_pc->GetAccountID();
		outpacket.num = static_cast<short>(m_millenniumShieldList.size());
		outpacket.state = 0;
		m_pc->Send(sizeof(outpacket), (char*)&outpacket);
		m_pc->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
	}
}


void CPCSkill::AddForceOfVanguard(const unsigned short in_Count) // 4669-4683
{
	unsigned short nMaxForceOfRageCount = m_pc->GetEffective(EFST_FORCEOFVANGUARD, 0);
	bool bAdded = false;

	for( int i = 0; i < in_Count; ++i )
	{
		if( m_forceOfVanguard.size() < nMaxForceOfRageCount )
		{
			m_forceOfVanguard.push_back(timeGetTime() + 300000);
			bAdded = true;
		}
	}

	if( bAdded )
		this->CPCSkill::NotifyForceOfVanguardCount();
}


void CPCSkill::NotifyForceOfVanguardCount() // 4708-4720
{
	if( m_pc == NULL )
		return;

	PACKET_ZC_MILLENNIUMSHIELD outpacket;
	outpacket.PacketType = HEADER_ZC_MILLENNIUMSHIELD;
	outpacket.AID = m_pc->GetAccountID();
	outpacket.num = static_cast<short>(m_forceOfVanguard.size());
	outpacket.state = 0;
	m_pc->Send(sizeof(outpacket), (const char*)&outpacket);
	m_pc->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


void CPCSkill::SetPartnerAID(unsigned long AID) // ??? (228.h)
{
	m_partnerAID = AID;
}


void CPCSkill::SetWeaponMasterAID(unsigned long AID) // ??? (229.h)
{
	m_weaponMasterAID = AID;
}


unsigned long CPCSkill::GetPartnerAID() // ??? (230.h)
{
	return m_partnerAID;
}


unsigned long CPCSkill::GetWeaponMasterAID() // ??? (231.h)
{
	return m_weaponMasterAID;
}


short CPCSkill::GetNumOfSpirits() // ??? (239.h)
{
	return static_cast<short>(m_spiritsTime.size());
}


void CPCSkill::ResetSpirits() // 381-384 (PCSkill2_2(1).cpp)
{
	m_spiritsTime.clear();
	m_pc->CPC::NotifySpiritsInfo();
}


unsigned long CPCSkill::GetSKIDFromAbracadabra() // ??? (245.h)
{
	return m_abracadabraSKID;
}


void CPCSkill::SetSKIDFromAbracadabra(unsigned long SKID) // ??? (246.h)
{
	m_abracadabraSKID = SKID;
}
