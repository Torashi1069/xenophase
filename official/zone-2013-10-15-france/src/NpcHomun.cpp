#include "CharacterMgr.h"
#include "Enum.h"
#include "EStateTypeInfoMgr.h"
#include "ExpParameter.h"
#include "NpcHomun.h"
#include "Common/Packet.h"


CNpcHomun::CNpcHomun() // 44-46
{
	m_type = NPC_HO_TYPE;
}


CNpcHomun::~CNpcHomun() // 49-51
{
}


CCharacter* CNpcHomun::GetMyOwner() // 36.h
{
	return this->CNpcHomun::GetOwner();
}


CPC* CNpcHomun::GetOwner() // 891-897
{
	if( m_myParentAID == 0 )
		return NULL;

	CPC* owner = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_myParentAID, PC_TYPE);
	if( owner == NULL )
		return NULL;

	return owner;
}


void CNpcHomun::SendProperty() // 1415-1455
{
	PACKET_ZC_PROPERTY_HOMUN packet;
	packet.PacketType = HEADER_ZC_PROPERTY_HOMUN;
	memcpy_s(packet.szName, sizeof(packet.szName), m_characterInfo.accountName, sizeof(m_characterInfo.accountName));
	packet.bModified = m_modified;
	packet.nLevel = m_characterInfo.clevel;
	packet.nFullness = m_fullness;
	packet.nRelationship = static_cast<short>(m_relation);
	packet.ITID = m_characterInfo.accessory;
	packet.atk = this->CNpcHomun::GetATKPoint_Client();
	packet.hit = this->CNPC::GetAttSucPercent();
	packet.critical = this->CNpcHomun::GetCRI_Client();
	packet.def = this->CNpcHomun::GetDEF_Client();
	packet.Matk = m_MATK.maximum * m_characterInfo.MATKPercent / 100;
	packet.Mdef = this->GetItemMagicDef() + this->GetStatusMagicDef();
	packet.flee = this->GetAvoidPercent_Client();
	packet.aspd = m_characterInfo.attackMT;
	packet.hp = m_characterInfo.hp;
	packet.maxHP = this->GetMaxHP();
	packet.sp = m_characterInfo.sp;
	packet.maxSP = this->GetMaxSP();
	packet.exp = m_characterInfo.exp;
	packet.maxEXP = g_expParameter.CExpParameter::GetNextExp_Homun(m_characterInfo.clevel, this->CNpcHomun::GetOwnerCategoryThirdJob());
	packet.SKPoint = m_SKPoint;
	packet.ATKRange = m_characterInfo.attackRange;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_myParentAID, CM_SEND_PACKET, sizeof(packet), (int)&packet, 0, 0);
}


short CNpcHomun::GetSKLevel(unsigned short SKID) // 1812-1819
{
	std::map<unsigned short,HO_SKINFO>::iterator it = m_skill.find(SKID);
	if( it == m_skill.end() )
		return 0;

	return it->second.level;
}


short CNpcHomun::GetATKPoint_Client() // 2489-2495
{
	return m_characterInfo.ATKPercent * (m_characterInfo.atk2 + m_charBuff2.CCharBuff::GetParameterValue(VAR_ATTPOWER)) / 100;
}


short CNpcHomun::GetCRI_Client() // 2498-2500
{
	return m_characterInfo.Luk / 3 + 1;
}


short CNpcHomun::GetDEF_Client() // 2503-2517
{
	return this->GetDefencePoint() + this->GetStatusDef();
}


BOOL CNpcHomun::IsRechargeTime() // 2568-2574
{
	return ( timeGetTime() - m_npcStateUpdater.m_npcStateInfo.reChargeTime >= (unsigned long)m_characterInfo.attackMT );
}


void CNpcHomun::NotifyStatusAmount(unsigned short type, int amount) // 3122-3125
{
	if( this->ApplyStatusAmount(type, amount) == true )
		this->CNpcHomun::SendProperty();
}


int CNpcHomun::GetOwnerCategoryThirdJob() // 3362-3366
{
	CPC* owner = this->CNpcHomun::GetOwner();
	if( owner == NULL )
		return 0;

	return owner->CPC::GetCategoryThirdJob();
}


void CNpcHomun::NotifySpiritsInfo() // 227-235 (NpcHomunMutationSkill.cpp)
{
	PACKET_ZC_SPIRITS outpacket;
	outpacket.PacketType = HEADER_ZC_SPIRITS;
	outpacket.AID = this->GetAccountID();
	outpacket.num = static_cast<short>(m_spiritsTime.size());
	this->Send(sizeof(outpacket), (char*)&outpacket);
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


void CNpcHomun::GetEffectData(std::vector<Effect3rd::tagEffect3rdDBFmt>& io_List) // 1368-1390 (NpcHomunMutationSkill.cpp)
{
	io_List.clear();
	this->CNpcHomun::SetEffectiveSpiritsSaveInfo();

	DWORD CurTM = timeGetTime();
	for( EFFECTIVE_CONTAINER::iterator iter = m_effectiveList.begin(); iter != m_effectiveList.end(); ++iter )
	{
		int EfstID = iter->first;
		EFFECTIVE_INFO& Data = iter->second;

		if( EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::IsSave(CurTM, EfstID, Data) )
		{
			int TimeMS;
			if( Data.time == 9999 )
				TimeMS = 0;
			else
				TimeMS = Data.time - CurTM;
			if( TimeMS == 9999 )
				TimeMS = 9998;

			io_List.push_back(Effect3rd::tagEffect3rdDBFmt(EfstID, TimeMS, Data.val[0], Data.val[1], Data.val[2]));
		}
	}
}


void CNpcHomun::SetEffectData(const std::vector<Effect3rd::tagEffect3rdDBFmt>& in_EfstList) // 1393-1411 (NpcHomunMutationSkill.cpp)
{
	for( std::vector<Effect3rd::tagEffect3rdDBFmt>::const_iterator iter = in_EfstList.begin(); iter != in_EfstList.end(); ++iter )
	{
		int TimeMS = iter->TimeMS;

		if( TimeMS == 0 && EStateTypeInfoMgr::GetObj()->EStateTypeInfoMgr::IsSaveInfinitTimeEfst(iter->ID) )
			TimeMS = 9999;

		this->SetEffective(iter->ID, TimeMS, iter->Data1, iter->Data2, iter->Data3, FALSE);
	}

	this->CNpcHomun::ParseSpiritsSaveInfo();
}


void CNpcHomun::GetSkillData(std::map<unsigned short,HO_SKINFO>& in_SkillSave) // 1414-1426 (NpcHomunMutationSkill.cpp)
{
	in_SkillSave.clear();
	DWORD CurTM = timeGetTime();

	for( std::map<unsigned short,HO_SKINFO>::iterator iter = m_skill.begin(); iter != m_skill.end(); ++iter )
	{
		unsigned short SKID = iter->first;
		HO_SKINFO Info = iter->second;

		if( Info.BlockUseTM != 0 )
			Info.bDBupdateWhenLogout = true;
		Info.BlockUseTM = ( CurTM < Info.BlockUseTM ) ? Info.BlockUseTM - CurTM : 0;

		in_SkillSave[SKID] = Info;
	}
}


void CNpcHomun::Send(const int in_Length, char* in_pBuffer) // 1474-1498 (NpcHomunMutationSkill.cpp)
{
	CPC* owner = this->CNpcHomun::GetOwner();
	if( owner == NULL )
		return;

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, owner, CM_SEND_PACKET, in_Length, (int)in_pBuffer, 0, 0);
}


void CNpcHomun::ParseSpiritsSaveInfo() // 1515-1536 (NpcHomunMutationSkill.cpp)
{
	m_spiritsTime.clear();

	int EfstID[] = {
		EFST_SPIRITS_SAVEINFO1,
		EFST_SPIRITS_SAVEINFO2,
	};

	DWORD curTime = timeGetTime();

	for( int id = 0; id < countof(EfstID); ++id )
	{
		EFFECTIVE_INFO* pInfo = this->CActor::GetEffectiveInfo(EfstID[id]);
		if( pInfo == NULL )
			continue;

		for( int index = 0; index < 3; ++index )
		{
			for( int pos = 0; pos < 30; pos += 10 ) // 3x 10 bits
			{
				int remainMS = 1000 * ((pInfo->val[index] >> pos) & 0x3FF);
				if( remainMS > 0 )
					m_spiritsTime.insert(curTime + remainMS);
			}
		}

		this->ResetEffective(EfstID[id], 0);
	}

	if( m_spiritsTime.size() != 0 )
		this->CNpcHomun::NotifySpiritsInfo();
}


void CNpcHomun::SetEffectiveSpiritsSaveInfo() // 1539-1571 (NpcHomunMutationSkill.cpp)
{
	if( m_spiritsTime.size() == 0 )
		return;

	int EfstID[] = {
		EFST_SPIRITS_SAVEINFO1,
		EFST_SPIRITS_SAVEINFO2,
	};

	for( int id = 0; id < countof(EfstID); ++id )
		this->ResetEffective(EfstID[id], 0);

	DWORD curTime = timeGetTime();
	SPIRITS_TIME_CONTAINER::iterator iter = m_spiritsTime.begin();

	for( int id = 0; id < countof(EfstID); ++id )
	{
		EFFECTIVE_INFO Info = {};
		bool isInfoSet = false;

		for( int index = 0; index < countof(Info.val); ++index )
		{
			for( int pos = 0; pos < 30; pos += 10 ) // 3x 10 bits
			{
				if( iter == m_spiritsTime.end() )
				{
					if( isInfoSet )
						this->SetEffective(EfstID[id], 100, Info.val[0], Info.val[1], Info.val[2], FALSE);
					return;
				}

				int remainSec = (*iter - curTime) / 1000; //FIXME: unsigned arithmetic, wrong result if negative
				if( remainSec > 0 )
					Info.val[index] |= remainSec << pos; //FIXME: missing truncation to 2^10-1 (0x3FF)

				++iter;
				isInfoSet = true;
			}
		}

		this->SetEffective(EfstID[id], 100, Info.val[0], Info.val[1], Info.val[2], FALSE);
	}
}
