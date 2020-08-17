#include "CharacterMgr.h"
#include "CharSkill.h"
#include "CStaticNPCAIDGenerator.h"
#include "Enum.h"
#include "FSMMgr.h"
#include "FSMState.h"
#include "MapResScheduler.h"
#include "MobTombInfo.h"
#include "NpcMob.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "Common/Packet.h"
#include "NpcServer/NpcObj.h"
#include "NpcServer/NpcSvr.h"


CNpcMob::CNpcMob() // 37-47
{
	m_type = NPC_MOB_TYPE;
	m_bossInfo.BOSS_INFO::Init(m_pathInfo.m_moveInfo.yPos, m_pathInfo.m_moveInfo.xPos);
	m_SvrScriptAppID = 0;
}


CNpcMob::~CNpcMob() // 50-51
{
}


void CNpcMob::InitCore() // 58-64 (51-66)
{
	this->CNPC::InitCore();
	m_stateTimer.CPollTimer::Reset(timeGetTime(), 350);
}


void CNpcMob::OnProcess() // 143-192
{
	if( m_characterInfo.isValid )
	{
		this->CheckCommandQueue();

		if( m_currentState != DEAD_ST )
		{
			m_npcUpdater.CNPCUpdater::CheckMove();

			if( m_stateTimer.CPollTimer::CheckTimeout(timeGetTime()) )
				m_npcUpdater.CNPCUpdater::CheckState();

			if( m_SvrScriptAppID != 0 || m_npcSkill.CNPCSkill::OnProcess() )
				if( m_neighborCache.CNeighborCache::GetListPoint().size() != 0 )
					m_npcStateUpdater.CNPCStateUpdater::CheckInput();
		}

		this->CActor::Process();
	}
	else
	{
		if( m_currentState == DEAD_ST )
		{
			if( !m_npcSkill.CNPCSkill::OnProcess() )
				m_npcStateUpdater.CNPCStateUpdater::CheckInput();
		}
	}

	this->CNpcMob::UpdateBossInfo();
}


int CNpcMob::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // 195-273 (121-196)
{
	return 0;
	//TODO
}


void CNpcMob::OnHealHP(int par1) // ??? (199-201)
{
	this->UpdateParameterValue(VAR_HP, par1);
}


void CNpcMob::OnDecreaseDef(CCharacter* sender, int par1) // 281-295
{
	if( m_isSkilledFromCrucis )
		return;
	m_isSkilledFromCrucis = true;

	m_characterInfo.def = short(m_characterInfo.def - m_characterInfo.def * par1 / 100.0);

	PACKET_ZC_EMOTION outpacket;
	outpacket.PacketType = HEADER_ZC_EMOTION;
	outpacket.GID = this->GetAccountID();
	outpacket.type = 4;
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


int CNpcMob::GetInvincibleTimeInfo(int skillID) // 348-360
{
	return 0;
	//TODO
}


int CNpcMob::ChkGndSkillDurability() // 450-452 (370-372)
{
	return 0;
	//TODO
}


void CNpcMob::SetEffectByGospel(CCharacter* ch) // (375-478)
{
	if( !this->IsTarget(ch, TARGET_NORMAL) || m_characterInfo._class == NPC_CLASS_BOSS )
		return;

	int effect = this->GetEffective(EFST_GOSPEL, 0);
	if( effect == 0 )
	{
		effect = 40 + GetServerRandom(0, 20000) % 10;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(ch, this, CM_SETEFFECTIVE, EFST_GOSPEL, 60000, effect, 0);
	}

	switch( effect )
	{
	case 40:
	case 41:
	{
		int damage = 300 + GetServerRandom(0, 20000) % 500;
		if( effect == 40 )
		{
			damage = int(damage - damage * this->GetDefencePoint() / 100.0 - this->GetStatusDef());
			if( damage < 0 )
				damage = 0;
		}
		SendPacket_ZC_NOTIFY_ACT(this, this->GetAccountID(), this->GetAccountID(), timeGetTime(), 0, this->CNPC::GetAttackedMotionTime(), damage, 1, 0, -1);

		COMMAND_QUEUE command;
		command.commandID = ATTACKED_IN;
		command.executionTime = timeGetTime();
		command.sender = this->GetAccountID();
		command.par1 = damage;
		command.par2 = 1;
		this->InsertCommand(&command);
	}
	break;
	case 42:
		this->SetHandicapState(HEALTH_CURSE, this, 1000, 0, 9999, 0, 0);
	break;
	case 43:
		this->SetHandicapState(HEALTH_BLIND, this, 1000, 0, 9999, 0, 0);
	break;
	case 44:
		this->SetHandicapState(HEALTH_POISON, this, 1000, 0, 9999, 0, 0);
	break;
	case 45:
		this->CNPC::SetATKPercentInfo(SKID_PA_GOSPEL, 9999, 32);
		this->CNPC::SetDEFPercentInfo(SKID_PA_GOSPEL, 9999, -55);
	break;
	case 46:
		this->CNPC::SetDEFPercentInfo(SKID_PA_GOSPEL, 9999, -50);
	break;
	case 47:
		this->CNPC::SetATKPercentInfo(SKID_PA_GOSPEL, 9999, -50);
	break;
	case 48:
		this->CNPC::OnChangeAGI(-12, 60000, SKID_PA_GOSPEL);
		this->CNPC::OnChangeDEX(-12, 60000, SKID_PA_GOSPEL);
	break;
	case 49:
		if( !this->GetEffective(EFST_DEC_AGI, 0) )
		{
			this->SetEffective(EFST_DEC_AGI, 60000, 10, 0, 0, 0);
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(ch, this, CM_AGI_CHANGE, -12, 60000, 30, 0);
		}
	break;
	}

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(ch, this, CM_SETINVINCIBLE, 10000, SKID_PA_GOSPEL, 0, 0);
}


void CNpcMob::ResetEffectByGospel(int value) // (481-483)
{
}


void CNpcMob::OnSetBossInMap() // 566-571 (486-491)
{
	m_bossInfo.isBossInMap = true;
	m_bossInfo.lastNotifyPositionX = m_pathInfo.m_moveInfo.xPos;
	m_bossInfo.lastNotifyPositionY = m_pathInfo.m_moveInfo.yPos;
	m_bossInfo.lastNotifyTime = 0;
}



void CNpcMob::UpdateBossInfo() // 574-623
{
	//TODO
}


char* CNpcMob::GetBossInfo(bool isWithMsg) // 666-748
{
	return NULL;
	//TODO
}


void CNpcMob::SetBossRegenTime(const unsigned long in_AfterTime) // 768-772
{
	//TODO
}


void CNpcMob::Reset() // 775-808 (658-670)
{
	if( m_bossInfo.isBossInMap == true )
	{
		unsigned long RegenTime = GetServerRandom(m_characterInfo.RegenMinTime, m_characterInfo.RegenMinTime + m_characterInfo.RegenMaxTime);
		this->CNpcMob::SetBossRegenTime(RegenTime);
	}

	this->CNPC::Reset();

	if( m_SvrScriptAppID != 0 )
	{
		m_npcType = ( this->GetType() != NPC_ELEMENTAL_TYPE ) ? LUA_AI_TYPE : LUA_ELEMENTAL_TYPE;
		m_npcStateUpdater.CNPCStateUpdater::SetFSM(g_fsmMgr.CFSMMgr::GetFSM(m_npcType));
	}
}


short CNpcMob::CheckBossEnableRegen() // ???-819 (683-691)
{
	if( !m_bossInfo.isBossInMap )
		return BOSSREGEN_NOT_BOSS;
	else
	if( timeGetTime() < m_bossInfo.regenTime )
		return BOSSREGEN_NOT_YET;
	else
	{
		return BOSSREGEN_PERMIT;
	}
}


void CNpcMob::ResetEffectiveByDispel() // 822-844 (694-710)
{
	//TODO
}


int CNpcMob::GetRevivalTerm() // 847-851
{
	if( m_bossInfo.isBossInMap )
		return m_bossInfo.regenTerm;

	return this->CNPC::GetRevivalTerm();
}


namespace {
class CTask_CheckMobRespawn : public MapResScheduler::CTask
{
public:
	virtual bool operator()(CMapRes* in_cpMapRes)
	{
		if( !m_bRegen )
			return this->CTask_CheckMobRespawn::RemoveTomb(in_cpMapRes);

		if( m_cpMob == NULL )
			return true;

		if( m_cpMob->CNPC::GetCurrentFSMState() != DEAD_ST )
			return this->CTask_CheckMobRespawn::RemoveTomb(in_cpMapRes);

		m_Time = timeGetTime() + CHECK_TIME;
		return false;
	}

public:
	CTask_CheckMobRespawn(const unsigned int in_MOB_AID, const unsigned int in_NPC_AID)
	: MapResScheduler::CTask(TASK_VARIABLE_IDENENTITY_USE, timeGetTime()),
	  m_MOB_AID(in_MOB_AID), m_NPC_AID(in_NPC_AID), m_bRegen(FALSE), m_OldTime(timeGetTime())
	{
		m_cpMob = (CNPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_MOB_AID, UNKNOWN_TYPE);
		if( m_cpMob != NULL )
			m_bRegen = m_cpMob->CNPC::IsRegen();
		m_Time = ( m_bRegen ) ? m_OldTime + CHECK_TIME : m_OldTime + DISAPPEAR_TIME;
	}

	virtual ~CTask_CheckMobRespawn()
	{
	}

private:
	bool RemoveTomb(CMapRes* in_cpMapRes)
	{
		CNPC* pNPC = (CNpcMob*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_NPC_AID, NPC_MOB_TYPE);
		if( pNPC == NULL )
			return true; // nothing to remove

		pNPC->CNPC::DisappearBossTomb();
		CCharacterMgr::GetObj()->CCharacterMgr::RemoveCharacter(pNPC);
		in_cpMapRes->CMapRes::DeleteMobTombInfo(m_NPC_AID);
		g_npcSvr.CNpcSvr::GetStaticNpcMgr()->CNpcMgr::Delete(m_NPC_AID);
		return true;
	}

private:
	/* this+ 0 */ //MapResScheduler::CTask baseclass_0;
	/* this+12 */ const unsigned int m_MOB_AID;
	/* this+16 */ const unsigned int m_NPC_AID;
	/* this+20 */ const unsigned long m_OldTime;
	/* this+24 */ CNPC* m_cpMob;
	/* this+28 */ BOOL m_bRegen;

private:
	enum
	{
		CHECK_TIME = 10000,
		DISAPPEAR_TIME = 1200000,
	};
};
} // namespace


namespace {
class CTask_CreateMobTomb : public MapResScheduler::CTask
{
public:
	virtual bool operator()(CMapRes* in_cpMapRes) // 933-996
	{
		CStaticNPCAID NAID = CStaticNPCAIDGenerator::GetObj()->CStaticNPCAIDGenerator::Alloc();
		if( NAID == 0 )
			return true;

		CNpc* cpNpc = g_npcSvr.CNpcSvr::GetStaticNpcMgr()->CNpcMgr::Add(NAID);
		if( cpNpc == NULL )
			return true;

		NpcSvrNpcInfo npcInfo = {};
		npcInfo.NpcSvrNpcInfo::SetDefault();
		npcInfo.type = MOB_TOMB_NPC;
		npcInfo.zone = in_cpMapRes->CMapRes::GetName();
		npcInfo.name = CScriptMobTombInfo::GetObj()->CScriptMobTombInfo::GetMobTombInfo().NpcName.c_str();
		npcInfo.y = m_posY;
		npcInfo.sprite = JT_MOB_TOMB;
		npcInfo.x = m_posX;
		npcInfo.direction = 0;
		npcInfo.w = 0;
		npcInfo.h = 0;
		cpNpc->CNpc::SetInfo(NAID, &npcInfo);
		cpNpc->CNpc::SetOnInit(true);

		PACKET_NZ_NEWNPC packet = {};
		packet.NAID = NAID;
		packet.spriteType = JT_MOB_TOMB;
		packet.RegenMinTime = npcInfo.regenMin;
		packet.RegenMaxTime = npcInfo.regenMax;
		packet.RegenType = npcInfo.regenType;
		packet.xPos = (short)npcInfo.dx + (short)npcInfo.x;
		packet.yPos = (short)npcInfo.dy + (short)npcInfo.y;
		packet.xSize = 0;
		packet.ySize = 0;
		packet.force = false;
		packet.npcType = MOB_TOMB_NPC;
		packet.direction = 0;
		memcpy_s(packet.NPCName, sizeof(packet.NPCName), npcInfo.name, sizeof(npcInfo.name));
		packet.NPCName[countof(packet.NPCName)-1] = '\0';
		memcpy_s(packet.mapName, sizeof(packet.mapName), npcInfo.zone, sizeof(npcInfo.zone));
		packet.NPCName[countof(packet.NPCName)-1] = '\0';

		if( !CCharacterMgr::GetObj()->CCharacterMgr::AddNPC(&packet, 0, 0) )
		{
			g_npcSvr.CNpcSvr::GetStaticNpcMgr()->CNpcMgr::Delete(NAID);
			return true;
		}

		g_npcSvr.m_npcNames.insert(npcInfo.name);
		in_cpMapRes->CMapRes::AddMobTombInfo(NAID, m_DeadHour, m_DeadMin, m_MVPNAME, m_MOB_NAME);

		CTask_CheckMobRespawn* pTask = new(std::nothrow) CTask_CheckMobRespawn(m_MOB_AID, NAID);
		in_cpMapRes->CMapRes::InsertSchedule(std::tr1::shared_ptr<MapResScheduler::CTask>(pTask));

		NAID.CStaticNPCAID::Release();
		return true;
	}

public:
	CTask_CreateMobTomb(const short in_posX, const short in_posY, const short in_DeadHour, const short in_DeadMin, const std::string in_MVPNAME, const unsigned int in_MOB_AID, const std::string in_MOB_NAME)
	: MapResScheduler::CTask(TASK_CREATE_BOSS_TOMB, timeGetTime()),
	m_posX(in_posX), m_posY(in_posY), m_DeadHour(in_DeadHour), m_DeadMin(in_DeadMin), m_MOB_AID(in_MOB_AID), m_MVPNAME(in_MVPNAME), m_MOB_NAME(in_MOB_NAME)
	{
		m_Time = timeGetTime() + CREATE_TIME;
	}

	virtual ~CTask_CreateMobTomb()
	{
	}

private:
	/* this+ 0 */ //MapResScheduler::CTask baseclass_0;
	/* this+12 */ const short m_posX;
	/* this+14 */ const short m_posY;
	/* this+16 */ const short m_DeadHour;
	/* this+18 */ const short m_DeadMin;
	/* this+20 */ const unsigned int m_MOB_AID;
	/* this+24 */ const std::string m_MVPNAME;
	/* this+52 */ const std::string m_MOB_NAME;

private:
	enum
	{
		SPRITE_NUMBER = JT_MOB_TOMB,
		CREATE_TIME = 10000,
	};
};
} // namespace


void CNpcMob::CreateMobTomb(const unsigned int in_KillerAID) // 1100-1121
{
	if( in_KillerAID == 0 )
		return;

	const char* killerName = CCharacterMgr::GetObj()->CCharacterMgr::GetCharName(in_KillerAID);
	if( killerName == NULL )
		return;

	if( m_mapRes->isInstantMap() )
		return;

	SYSTEMTIME curSystemTime;
	GetLocalTime(&curSystemTime);

	CTask_CreateMobTomb* pTask = new(std::nothrow) CTask_CreateMobTomb(m_pathInfo.m_moveInfo.xPos, m_pathInfo.m_moveInfo.yPos, curSystemTime.wHour, curSystemTime.wMinute, killerName, this->GetAccountID(), this->GetNamePtr());
	m_mapRes->CMapRes::InsertSchedule(std::tr1::shared_ptr<MapResScheduler::CTask>(pTask));
}


int CNpcMob::GetMonsterDBDef() // (61.h)
{
	return m_characterInfo.def;
}


int CNpcMob::GetMonsterDBMdef() // (62.h)
{
	return m_characterInfo.mdef;
}


void CNpcMob::GetBossRegenSystemTime(unsigned long& hour, unsigned long& minute) // (74-77.h)
{
	hour = m_bossInfo.regenSystemTime.wHour;
	minute = m_bossInfo.regenSystemTime.wMinute;
}


bool CNpcMob::IsBossInMap() // (78.h)
{
	return m_bossInfo.isBossInMap;
}


void CNpcMob::SetSvrScriptAppID(int in_SvrScriptAppID)
{
	m_SvrScriptAppID = in_SvrScriptAppID;
}


int CNpcMob::GetSvrScriptAppID()
{
	return m_SvrScriptAppID;
}
