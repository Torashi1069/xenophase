#include "Character.h"
#include "CharacterMgr.h"
#include "MapResMgr.h"
#include "PC.h"
#include "SkillTypeInfoMgr.h"
#include "ZGuildInfo.h"
#include "ZGuildMgr.h"
#include "ZoneProcess.h"
#include "Common/Packet.h"


CZGuildInfo::CZGuildInfo()
{
	MemberFragNum = 0;
	m_JoinGID = 0;
}


CZGuildInfo::~CZGuildInfo()
{
	m_isEmblemLoad = FALSE;
	m_emblemSize = 0;
}


void CZGuildInfo::Init()
{
	this->CGuild::Init();
	m_packetDispatcher.m_guildInfo = this;
	m_skill.clear();
}


void CZGuildInfo::DeleteMember(unsigned long GID)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->GID == GID )
		{
			CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter((*iter)->AID, PC_TYPE);
			if( pc != NULL )
				pc->UpdateParameterValue(VAR_GDID, 0);

			m_GuildMInfoMPool.CMemoryMgr<GUILDMINFO>::Free(*iter);
			m_guildMInfo.erase(iter);
			return;
		}
	}
}


void CZGuildInfo::BanMember(char* Buf)
{
	PACKET_IZ_ACK_BAN_GUILD* pPacket = reinterpret_cast<PACKET_IZ_ACK_BAN_GUILD*>(Buf);

	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->GID == pPacket->GID )
		{
			if( this->CGuild::GetGuildBanishSize() >= 2 )
				this->CGuild::DeleteFirstBanishInfo();

			GUILDBANISHINFO* Info = m_GuildBanishInfoMPool.CMemoryMgr<GUILDBANISHINFO>::Alloc();
			if( Info != NULL )
			{
				Info->AID = pPacket->AID;
				Info->GDID = m_GDID;
				Info->GID = pPacket->GID;
				memcpy_s(Info->MemberAccount, 24u, pPacket->AccountName, 24u);
				memcpy_s(Info->MemberName, 24u, pPacket->charName, 24u);
				memcpy_s(Info->Reason, 50u, pPacket->reasonDesc, 40u);
				this->CGuild::AddGuildBanishInfo(Info);

				CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter((*iter)->AID, PC_TYPE);
				if( pc != NULL && pc->CPC::GetCharacterID() == pPacket->GID )
					pc->UpdateParameterValue(VAR_GDID, 0);

				m_GuildMInfoMPool.CMemoryMgr<GUILDMINFO>::Free(*iter);
				m_guildMInfo.erase(iter);
				return;
			}
		}
	}
}


void CZGuildInfo::BroadCast(int Len, char* Buf)
{
	for( std::vector<GUILDMINFO*>::const_iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->status == 1 )
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, (*iter)->AID, CM_SEND_PACKET, Len, (int)Buf, 0, 0);
}


void CZGuildInfo::SendAckBanGuild(char* CharName, char* AccountName, char* Reason)
{
	for( std::vector<GUILDMINFO*>::iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->status == 1 )
		{
			PACKET_ZC_ACK_BAN_GUILD ZCPacket;
			ZCPacket.PacketType = HEADER_ZC_ACK_BAN_GUILD;
			memcpy(ZCPacket.reasonDesc, Reason, sizeof(ZCPacket.reasonDesc));
			memcpy(ZCPacket.charName, CharName, sizeof(ZCPacket.charName));
			memcpy(ZCPacket.account, AccountName, sizeof(ZCPacket.account));
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, (*iter)->AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);
		}
	}
}


void CZGuildInfo::SendAckLeaveGuild(char* CharName, char* AccountName, char* Reason)
{
	for( std::vector<GUILDMINFO*>::const_iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->status == 1 )
		{
			PACKET_ZC_ACK_LEAVE_GUILD ZCPacket;
			ZCPacket.PacketType = 346;
			memcpy(ZCPacket.reasonDesc, Reason, sizeof(ZCPacket.reasonDesc));
			memcpy(ZCPacket.charName, CharName, sizeof(ZCPacket.charName));
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, (*iter)->AID, CM_SEND_PACKET, 66, (int)&ZCPacket, 0, 0);
		}
	}
}


void CZGuildInfo::SendGuildChat(char* Notice, int PacketLen)
{
	PACKET_ZC_GUILD_CHAT ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_GUILD_CHAT;
	ZCPacket.PacketLength = sizeof(PACKET_ZC_GUILD_CHAT) + PacketLen;

	for( std::vector<GUILDMINFO*>::const_iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->status == 1 )
		{
			CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter((*iter)->AID, PC_TYPE);
			if( pc != NULL )
			{
				int GDID;
				pc->GetParameterValue(VAR_GDID, GDID);

				if( m_GDID == GDID && pc->CPC::GetCharacterID() == (*iter)->GID )
				{
					pc->Send(sizeof(PACKET_ZC_GUILD_CHAT), (char*)&ZCPacket);
					pc->Send(PacketLen, Notice);
				}
			}
		}
	}
}


void CZGuildInfo::SendAllyGuildResult(unsigned char answer)
{
	for( std::vector<GUILDMINFO*>::const_iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		/*
		*/
	}
}


void CZGuildInfo::DisOrganizeGuild(char* Buf)
{
	PACKET_IZ_REQ_DISORGANIZE_GUILD_RESULT* pPacket = reinterpret_cast<PACKET_IZ_REQ_DISORGANIZE_GUILD_RESULT*>(Buf);

	PACKET_ZC_ACK_DISORGANIZE_GUILD_RESULT ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_ACK_DISORGANIZE_GUILD_RESULT;
	ZCPacket.reason = pPacket->result;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, pPacket->AID, CM_SEND_PACKET, sizeof(ZCPacket), (int)&ZCPacket, 0, 0);

	if( pPacket->result == 0 )
	{
		this->CZGuildInfo::DeleteMember(pPacket->GID);
		g_ZGuildMgr.CZGuildMgr::FreeGuild(this, TRUE);
	}
}


void CZGuildInfo::GetGuildPosition(char* buf, unsigned short Len)
{
	PACKET_IZ_ACK_GUILD_POSITION_INFO* pPacket = reinterpret_cast<PACKET_IZ_ACK_GUILD_POSITION_INFO*>(buf);

	size_t InfoLen = Len - sizeof(PACKET_IZ_ACK_GUILD_POSITION_INFO);
	int Count = InfoLen / sizeof(GUILD_REG_POSITION_INFO);
	if( Count == 0 )
		return;

	char Buf[3072] = {};
	for( int i = 0; i < Count; ++i )
	{
		GUILD_REG_POSITION_INFO Guild;
		memcpy_s(&Guild, sizeof(Guild), &pPacket->Info[i], sizeof(pPacket->Info[i]));

		BOOL JoinRight = ( Guild.right & 0x01 );
		BOOL PenaltyRight = ( Guild.right & 0x10 );
		this->CGuild::UpdateMemberPosition(Guild.positionID, Guild.posName, Guild.payRate, JoinRight, PenaltyRight);
	}

	PACKET_ZC_ACK_CHANGE_GUILD_POSITIONINFO ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_ACK_CHANGE_GUILD_POSITIONINFO;
	ZCPacket.PacketLength = sizeof(PACKET_ZC_ACK_CHANGE_GUILD_POSITIONINFO) + InfoLen;
	memcpy_s(Buf, sizeof(Buf), pPacket->Info, InfoLen);

	for( std::vector<GUILDMINFO*>::const_iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->status == 1 )
		{
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, (*iter)->AID, CM_SEND_PACKET, sizeof(PACKET_ZC_ACK_CHANGE_GUILD_POSITIONINFO), (int)&ZCPacket, 0, 0);
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, (*iter)->AID, CM_SEND_PACKET, Count * sizeof(GUILD_REG_POSITION_INFO), (int)Buf, 0, 0);
		}
	}
}


void CZGuildInfo::ChangeMemberPosition(char* buf, unsigned short Len)
{
	PACKET_IZ_ACK_CHANGE_MEMBERPOS* pPacket = reinterpret_cast<PACKET_IZ_ACK_CHANGE_MEMBERPOS*>(buf);

	size_t InfoLen = Len - sizeof(PACKET_IZ_ACK_CHANGE_MEMBERPOS);
	int Count = InfoLen / sizeof(MEMBER_POSITION_INFO);
	if( Count == 0 )
		return;

	char Buf[3072] = {};
	for( int i = 0; i < Count; ++i )
	{
		MEMBER_POSITION_INFO Guild;
		memcpy_s(&Guild, sizeof(Guild), &pPacket->Info[i], sizeof(pPacket->Info[i]));
		this->CGuild::UpdateMemberChangePos(Guild.GID, Guild.positionID);
	}

	PACKET_ZC_ACK_REQ_CHANGE_MEMBERS ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_ACK_REQ_CHANGE_MEMBERS;
	ZCPacket.PacketLength = sizeof(PACKET_ZC_ACK_REQ_CHANGE_MEMBERS) + InfoLen;
	memcpy_s(Buf, sizeof(Buf), pPacket->Info, InfoLen);

	for( std::vector<GUILDMINFO*>::const_iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		if( (*iter)->status == 1 )
		{
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, (*iter)->AID, CM_SEND_PACKET, sizeof(PACKET_ZC_ACK_REQ_CHANGE_MEMBERS), (int)&ZCPacket, 0, 0);
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, (*iter)->AID, CM_SEND_PACKET, Count * sizeof(MEMBER_POSITION_INFO), (int)Buf, 0, 0);
		}
	}
}


void CZGuildInfo::GetGuildNotice(char* buf)
{
	PACKET_IZ_GUILD_NOTICE* pPacket = reinterpret_cast<PACKET_IZ_GUILD_NOTICE*>(buf);

	m_guildNotice.GDID = pPacket->GDID;
	memcpy_s(m_guildNotice.Notice, sizeof(m_guildNotice.Notice), pPacket->notice, sizeof(pPacket->notice));
	memcpy_s(m_guildNotice.Subject, sizeof(m_guildNotice.Subject), pPacket->subject, sizeof(pPacket->subject));

	PACKET_ZC_GUILD_NOTICE NoticePacket;
	NoticePacket.PacketType = HEADER_ZC_GUILD_NOTICE;
	memcpy_s(NoticePacket.notice, sizeof(NoticePacket.notice), m_guildNotice.Notice, sizeof(m_guildNotice.Notice));
	memcpy_s(NoticePacket.subject, sizeof(NoticePacket.subject), m_guildNotice.Subject, sizeof(m_guildNotice.Subject));
	this->CZGuildInfo::BroadCast(182, (char*)&NoticePacket);
}


void CZGuildInfo::SendGuildNotice(unsigned long AID)
{
	PACKET_ZC_GUILD_NOTICE NoticePacket;
	NoticePacket.PacketType = HEADER_ZC_CLOSE_DIALOG;
	memcpy_s(NoticePacket.subject, sizeof(NoticePacket.subject), m_guildNotice.Subject, sizeof(m_guildNotice.Subject));
	memcpy_s(NoticePacket.notice, sizeof(NoticePacket.notice), m_guildNotice.Notice, sizeof(m_guildNotice.Notice));
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, sizeof(NoticePacket), (int)&NoticePacket, 0, 0);
}


void CZGuildInfo::GuildMemberAdd(char* buf)
{
	PACKET_IZ_GUILD_MEMBER_ADD* pPacket = reinterpret_cast<PACKET_IZ_GUILD_MEMBER_ADD*>(buf);

	GUILDMINFO* Guild = this->CGuild::AllocGuildMInfo();
	if( Guild == NULL )
		return;

	this->CGuild::InitGuildMInfo(Guild, pPacket->Info.CharName, pPacket->Info.AccountName, pPacket->Info.AID, pPacket->Info.GDID, pPacket->Info.GID, 19, 1, pPacket->Info.Level, pPacket->Info.job, pPacket->Info.head, pPacket->Info.headPalette, pPacket->Info.sex);
	this->CGuild::AddGuildMInfo(Guild);

	PACKET_ZC_MEMBER_ADD ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_MEMBER_ADD;
	this->CZGuildInfo::ConvertGuildMInfo(pPacket->Info, ZCPacket.Info);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(pPacket->Info.AID, PC_TYPE);
	if( pc != NULL )
		pc->UpdateParameterValue(VAR_GDID, pPacket->Info.GDID);

	this->CZGuildInfo::BroadCast(sizeof(ZCPacket), (char*)&ZCPacket);
}


BOOL CZGuildInfo::ConvertGuildMInfo(GUILDMINFO MInfo, GUILD_MEMBER_INFO& Info)
{
	GUILDMINFO tmpInfo;
	memcpy(&tmpInfo, &MInfo, sizeof(tmpInfo));

	Info.AID = tmpInfo.AID;
	Info.contributionExp = tmpInfo.MemberExp;
	Info.currentState = tmpInfo.status;
	Info.GID = tmpInfo.GID;
	Info.head = tmpInfo.head;
	Info.level = static_cast<short>(tmpInfo.Level);
	Info.positionID = tmpInfo.PositionID;
	memcpy_s(Info.charname, sizeof(Info.charname), tmpInfo.CharName, sizeof(Info.charname));
	memcpy_s(Info.intro, sizeof(Info.intro), tmpInfo.Memo, sizeof(tmpInfo.Memo));
	Info.head = tmpInfo.head;
	Info.job = LOWORD(tmpInfo.job);
	Info.headPalette = tmpInfo.headPalette;
	Info.sex = tmpInfo.sex;
	Info.level = static_cast<short>(tmpInfo.Level);

	return TRUE;
}


BOOL CZGuildInfo::GetGuildMInfo(char* Buf, const int in_nMaxBufSize)
{
	GUILD_MEMBER_INFO Info;
	int BufPos = 0;

	for( std::vector<GUILDMINFO*>::const_iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
	{
		Info.AID = (*iter)->AID;
		memcpy_s(Info.charname, sizeof(Info.charname), (*iter)->CharName, sizeof((*iter)->CharName));
		Info.contributionExp = (*iter)->MemberExp;
		Info.currentState = (*iter)->status;
		Info.GID = (*iter)->GID;
		memcpy_s(Info.intro, sizeof(Info.intro), (*iter)->Memo, sizeof((*iter)->Memo));
		Info.job = static_cast<short>((*iter)->job);
		Info.level = static_cast<short>((*iter)->Level);
		Info.head = (*iter)->head;
		Info.headPalette = (*iter)->headPalette;
		Info.sex = (*iter)->sex;
		Info.positionID = (*iter)->PositionID;

		memcpy_s(Buf + BufPos, in_nMaxBufSize - BufPos, &Info, sizeof(Info));
		BufPos += sizeof(Info);
	}

	return TRUE;
}


void CZGuildInfo::DeleteRelatedGuild(char* Buf)
{
	PACKET_IZ_DELETE_RELATED_GUILD* pPacket = reinterpret_cast<PACKET_IZ_DELETE_RELATED_GUILD*>(Buf);

	this->CGuild::DeleteGuildAllyInfo(pPacket->OpponentGDID, pPacket->Relation);

	PACKET_ZC_DELETE_RELATED_GUILD ZCPacket;
	ZCPacket.PacketType = HEADER_ZC_DELETE_RELATED_GUILD;
	ZCPacket.OpponentGDID = pPacket->OpponentGDID;
	ZCPacket.Relation = pPacket->Relation;
	this->CZGuildInfo::BroadCast(sizeof(ZCPacket), (char*)&ZCPacket);

	if( pPacket->Relation == 0 )
		g_mapResMgr.CMapResMgr::OnDeleteRelated(m_GDID, pPacket->OpponentGDID);
}


void CZGuildInfo::OnAddExp(char* Buf)
{
	PACKET_IZ_ADD_EXP* pPacket = reinterpret_cast<PACKET_IZ_ADD_EXP*>(Buf);

	this->CGuild::AddGuildExp(pPacket->GID, pPacket->Exp);
}


void CZGuildInfo::OnGetMemberFrag(char* Buf)
{
	PACKET_IZ_GUILD_MEMBERINFO_FRAG* pPacket = reinterpret_cast<PACKET_IZ_GUILD_MEMBERINFO_FRAG*>(Buf);

	GUILDMINFO* Info = this->CGuild::AllocGuildMInfo();
	if( Info == NULL )
		return;

	memcpy_s(Info, sizeof(*Info), &pPacket->MInfo, sizeof(pPacket->MInfo));
	this->CGuild::AddGuildMInfo(Info);
}


void CZGuildInfo::SetCompressedEmblemImage(const char* compressedEmblemImage, unsigned long emblemLen, int GDID, int emblemVersion)
{
	/*
	*/
}


void CZGuildInfo::LoadEmblem()
{
	char Folder[MAX_PATH] = {};
	GetCurrentDirectoryA(sizeof(Folder), Folder);

	char Name[MAX_PATH] = {};
	_snprintf(Name, countof(Name), "%s\\emblem\\%d_%d.emb", Folder, m_GDID, m_emblemVersion);

	FILE* fp = fopen(Name, "rb");
	if( fp == NULL )
		return;

	memset(m_guildEmblem, 0, sizeof(m_guildEmblem));

	fseek(fp, 0, SEEK_END);
	m_emblemSize = min(ftell(fp), sizeof(m_guildEmblem)); //NOTE: double evaluation
	fseek(fp, 0, SEEK_SET);

	fread(m_guildEmblem, m_emblemSize, sizeof(char), fp);
	m_isEmblemLoad = TRUE;

	fclose(fp);
}


void CZGuildInfo::SetEmblem(const char* in_guildEmblem, int in_emblemSize, int in_emblemVersion) /// @custom
{
	memset(m_guildEmblem, 0, sizeof(m_guildEmblem));
	memcpy_s(m_guildEmblem, sizeof(m_guildEmblem), in_guildEmblem, in_emblemSize);
	m_isEmblemLoad = TRUE;
	m_emblemSize = in_emblemSize;
	m_emblemVersion = in_emblemVersion;
}


void CZGuildInfo::OnZenyUpdateAll(char* Buf)
{
	/*
	*/
}


void CZGuildInfo::NotifySkillInfo(unsigned long AID)
{
	char buf[3072];
	int count = 0;

	for( std::map<unsigned short,unsigned short>::iterator it = m_skill.begin(); it != m_skill.end(); ++it )
	{
		const char* skillName = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetSkillName(it->first);
		if( skillName == NULL )
			continue;

		SKILLINFO info;
		memcpy_s(info.skillName, sizeof(info.skillName), skillName, 24);
		info.SKID = it->first;
		info.level = it->second;
		info.spcost = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetSkillSPCost(info.SKID, info.level);
		info.type = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetType(info.SKID);
		info.attackRange = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetAttackRange(info.SKID, info.level);
		info.upgradable = g_skillTypeInfoMgr.CSkillTypeInfoMgr::IsNextLevelUpgradable(info.SKID, info.level, JT_NOVICE);

		if( g_skillTypeInfoMgr.CSkillTypeInfoMgr::IsConditionalSkill(JT_NOVICE, info.SKID) )
		{
			if( this->CZGuildInfo::IsEnableSkill(info.SKID) == TRUE )
				info.upgradable = g_skillTypeInfoMgr.CSkillTypeInfoMgr::IsNextLevelUpgradable(info.SKID, info.level, JT_NOVICE);
			else
				info.upgradable = false;
		}

		if( count + sizeof(info) > sizeof(buf) )
			break;

		memcpy_s(buf + count, sizeof(buf) - count, &info, sizeof(info));
		count += sizeof(info);
	}

	PACKET_ZC_GUILD_SKILLINFO outpacket;
	outpacket.PacketType = HEADER_ZC_GUILD_SKILLINFO;
	outpacket.PacketLength = sizeof(PACKET_ZC_GUILD_SKILLINFO) + count;
	outpacket.skillPoint = static_cast<short>(m_skillPoint);
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, sizeof(PACKET_ZC_GUILD_SKILLINFO), (int)&outpacket, 0, 0);
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, AID, CM_SEND_PACKET, count, (int)buf, 0, 0);
}


void CZGuildInfo::OnNotifySkillData(char* Buf, unsigned short Len)
{
	PACKET_IZ_GUILD_NOTIFYSKILLDATA* pPacket = reinterpret_cast<PACKET_IZ_GUILD_NOTIFYSKILLDATA*>(Buf);

	m_skill.clear();

	int OffSetLevel = 0;
	int Count = Len - sizeof(PACKET_IZ_GUILD_NOTIFYSKILLDATA);

	BYTE* p = pPacket->Data;
	for( int i = 4; i <= Count; i += 4 )
	{
		unsigned short SKID;
		memcpy_s(&SKID, sizeof(SKID), p, 2);
		p += 2;

		unsigned short level;
		memcpy_s(&level, sizeof(level), p, 2);
		p += 2;

		m_skill[SKID] = level;
		OffSetLevel += level;
	}

	m_skillPoint = m_level - OffSetLevel - 1;

	if( m_skillPoint < 0 )
	{
		for( std::map<unsigned short,unsigned short>::iterator iter = m_skill.begin(); iter != m_skill.end(); ++iter )
			iter->second = 0;

		m_skillPoint = m_level - 1;
		m_maxUserNum = 16;
	}

	for( std::vector<GUILDMINFO*>::const_iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->status == 1 && pPacket->isForceSend )
				this->CZGuildInfo::NotifySkillInfo((*iter)->AID);
}


void CZGuildInfo::UpgradeSkillLevel(unsigned short SKID)
{
	std::map<unsigned short,unsigned short>::iterator iter = m_skill.find(SKID);
	if( iter == m_skill.end() )
		return;

	if( m_skillPoint <= 0 )
		return;

	if( !g_skillTypeInfoMgr.CSkillTypeInfoMgr::IsNextLevelUpgradable(SKID, iter->second, JT_NOVICE) )
		return;

	--m_skillPoint;
	++iter->second;
	int level = iter->second;

	char buf[300];
	int count = 0;
	int OffSetSkill = 0;

	for( std::map<unsigned short,unsigned short>::iterator iter = m_skill.begin(); iter != m_skill.end(); ++iter )
	{
		if( count + 4 > sizeof(buf) )
			break;

		unsigned short tmpBuf[2];
		tmpBuf[0] = iter->first;
		tmpBuf[1] = iter->second;

		memcpy_s(buf + count, sizeof(buf) - count, tmpBuf, sizeof(tmpBuf));
		OffSetSkill += iter->second;
		count += sizeof(tmpBuf);
	}

	m_skillPoint = m_level - OffSetSkill - 1;

	PACKET_ZI_GDSKILL_UPDATE packet;
	packet.PacketType = HEADER_ZI_GDSKILL_UPDATE;
	packet.PacketLength = sizeof(PACKET_ZI_GDSKILL_UPDATE) + count;
	packet.GDID = m_GDID;
	packet.SkillPoint = m_skillPoint;
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(PACKET_ZI_GDSKILL_UPDATE), (char*)&packet);
	CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(count, buf);

	if( SKID == SKID_GD_EXTENSION )
	{
		PACKET_ZI_GUILD_CHANGEMAXUSER packet;
		packet.PacketType = HEADER_ZI_GUILD_CHANGEMAXUSER;
		packet.GDID = m_GDID;
		packet.maxNum = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(NULL, SKID_GD_EXTENSION, SM_GETINFO_SKILL, level, 0, 0, 0);
		CCharacterMgr::GetObj()->CCharacterMgr::SendToIServer(sizeof(packet), (char*)&packet);
	}

}


int CZGuildInfo::GetSkillLevel(unsigned short SKID)
{
	std::map<unsigned short,unsigned short>::const_iterator it = m_skill.find(SKID);
	return ( it != m_skill.end() ) ? it->second : 0;
}


BOOL CZGuildInfo::IsEnableSkill(unsigned short SKID)
{
	if( g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID) == NULL )
		return FALSE;
	
	std::map<unsigned short,int>* Info = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetLowerSkillTreeInfo(JT_NOVICE, SKID);
	if( Info == NULL )
		return FALSE;

	for( std::map<unsigned short,int>::iterator iter = Info->begin(); iter != Info->end(); ++iter )
		if( this->CZGuildInfo::GetSkillLevel(iter->first) < iter->second )
			return FALSE;

	return TRUE;
}


void CZGuildInfo::MapChange(unsigned long AID, char* MapName)
{
	PACKET_ZC_GUILD_MEMBER_MAP_CHANGE GuildMemberMapChange;
	GuildMemberMapChange.PacketType = HEADER_ZC_GUILD_MEMBER_MAP_CHANGE;
	GuildMemberMapChange.GDID = m_GDID;
	GuildMemberMapChange.AID = AID;
	strcpy(GuildMemberMapChange.mapName, MapName);

	for( std::vector<GUILDMINFO*>::const_iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->status == 1 )
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, (*iter)->AID, CM_SEND_PACKET, sizeof(GuildMemberMapChange), (int)&GuildMemberMapChange, 0, 0);
}


void CZGuildInfo::NotifyPositionToGuild(unsigned long AID, short xPos, short yPos, int MapID)
{
	PACKET_ZC_NOTIFY_POSITION_TO_GROUPM outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_POSITION_TO_GUILDM;
	outpacket.AID = AID;
	outpacket.xPos = xPos;
	outpacket.yPos = yPos;

	for( std::vector<GUILDMINFO*>::const_iterator iter = m_guildMInfo.begin(); iter != m_guildMInfo.end(); ++iter )
		if( (*iter)->status == 1 && (*iter)->AID != AID )
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, (*iter)->AID, CM_NOTIFY_POSITION_GUILD, 10, (int)&outpacket, MapID, 0);
}


std::vector<GUILDMINFO*>::iterator CZGuildInfo::GetStartGuildIter()
{
	return m_guildMInfo.begin();
}


std::vector<GUILDMINFO*>::iterator CZGuildInfo::GetEndGuildIter()
{
	return m_guildMInfo.end();
}


void CZGuildInfo::SetJoinGID(int GID)
{
	m_JoinGID = GID;
}


int CZGuildInfo::GetJoinGID()
{
	return m_JoinGID;
}
