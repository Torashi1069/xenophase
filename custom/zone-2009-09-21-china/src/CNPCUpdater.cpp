#include "CharacterMgr.h"
#include "CITPMgr.hpp"
#include "CMakerRankMgr.hpp"
#include "MonParameterMgr.h"
#include "NPC.h"
#include "CNPCUpdater.hpp"
#include "PathFinder.h"
#include "RoomMgr.h"
#include "ZoneProcess.h" // GetServerRandom()
#include "Common/Packet.h"


CNPCUpdater::CNPCUpdater(void) // line 45
{
}


CNPCUpdater::~CNPCUpdater(void) // line 49
{
}


hook_method<void (CNPCUpdater::*)(CNPC* npc)> CNPCUpdater::_SetMyOwner(SERVER, "CNPCUpdater::SetMyOwner");
void CNPCUpdater::SetMyOwner(CNPC* npc) // line ??
{
	return (this->*_SetMyOwner)(npc);

	m_npc = npc;
}


hook_method<int (CNPCUpdater::*)(int AccountID)> CNPCUpdater::_SetAccountID(SERVER, "CNPCUpdater::SetAccountID");
BOOL CNPCUpdater::SetAccountID(int AccountID) // line 59
{
	return (this->*_SetAccountID)(AccountID);

	if( AccountID == 0 )
	{// get one from free AID pool
		AccountID = g_characterMgr->CCharacterMgr::GetAID();
		if( AccountID == 0 )
			return FALSE;

		m_npc->m_characterInfo.IsRegen = 0;
	}

	m_npc->m_characterInfo.accountID = AccountID;
	return TRUE;
}


/* hook_method<void (CNPCUpdater::*)(const char* buf)> CNPCUpdater::_SetAccountName(SERVER, "CNPCUpdater::SetAccountName");
void CNPCUpdater::SetAccountName(const char* buf)
{
	return (this->*_SetAccountName)(buf);

	//TODO
} */


hook_method<void (CNPCUpdater::*)(int isActive)> CNPCUpdater::_SetValidate(SERVER, "CNPCUpdater::SetValidate");
void CNPCUpdater::SetValidate(int isActive) // line 415
{
	return (this->*_SetValidate)(isActive);

	//TODO
}


hook_method<int (CNPCUpdater::*)(CCharacter* other, int xRange, int yRange)> CNPCUpdater::_IsMyArea(SERVER, "?IsMyArea@CNPCUpdater@@QAEHPAVCCharacter@@H@Z");
int CNPCUpdater::IsMyArea(CCharacter* other, int xRange, int yRange)
{
	return (this->*_IsMyArea)(other, xRange, yRange);

	//TODO
}


hook_method<int (CNPCUpdater::*)(CCharacter* other, int Range)> CNPCUpdater::_IsMyArea2(SERVER, "?IsMyArea@CNPCUpdater@@QAEHPAVCCharacter@@HH@Z");
int CNPCUpdater::IsMyArea(CCharacter* other, int Range)
{
	return (this->*_IsMyArea2)(other, Range);

	//TODO
}


/* hook_method<int (CNPCUpdater::*)(int x, int y, int range)> CNPCUpdater::_IsSomeOne(SERVER, "CNPCUpdater::IsSomeOne");
int CNPCUpdater::IsSomeOne(int x, int y, int range)
{
	return (this->*_IsSomeOne)(x, y, range);

	//TODO
} */


/* hook_method<void (CNPCUpdater::*)(unsigned long time)> CNPCUpdater::_Pause(SERVER, "CNPCUpdater::Pause");
void CNPCUpdater::Pause(unsigned long time)
{
	return (this->*_Pause)(time);

	//TODO
} */


hook_method<int (CNPCUpdater::*)(void)> CNPCUpdater::_AddSectionMgr(SERVER, "CNPCUpdater::AddSectionMgr");
int CNPCUpdater::AddSectionMgr(void)
{
	return (this->*_AddSectionMgr)();

	//TODO
}


hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_RemoveSectionMgr(SERVER, "CNPCUpdater::RemoveSectionMgr");
void CNPCUpdater::RemoveSectionMgr(void) // line 572
{
	return (this->*_RemoveSectionMgr)();

	m_npc->m_mapRes->CMapRes::RemoveCharacter(m_npc); //inlined
}


hook_method<CNPC* (CNPCUpdater::*)(int range, unsigned long state)> CNPCUpdater::_GetNeighborFriendNpc(SERVER, "CNPCUpdater::GetNeighborFriendNpc");
CNPC* CNPCUpdater::GetNeighborFriendNpc(int range, unsigned long state)
{
	return (this->*_GetNeighborFriendNpc)(range, state);

	//TODO
}


hook_method<CPC* (CNPCUpdater::*)(int xRange, int yRange)> CNPCUpdater::_GetNeighborPc(SERVER, "?GetNeighborPc@CNPCUpdater@@QAEPAVCPC@@H@Z");
CPC* CNPCUpdater::GetNeighborPc(int xRange, int yRange)
{
	return (this->*_GetNeighborPc)(xRange, yRange);

	//TODO
}


hook_method<CPC* (CNPCUpdater::*)(int range)> CNPCUpdater::_GetNeighborPc2(SERVER, "?GetNeighborPc@CNPCUpdater@@QAEPAVCPC@@HH@Z");
CPC* CNPCUpdater::GetNeighborPc(int range)
{
	return (this->*_GetNeighborPc2)(range);

	//TODO
}


hook_method<CPC* (CNPCUpdater::*)(int range)> CNPCUpdater::_GetNeighborPcExceptG(SERVER, "CNPCUpdater::GetNeighborPcExceptG");
CPC* CNPCUpdater::GetNeighborPcExceptG(int range)
{
	return (this->*_GetNeighborPcExceptG)(range);

	//TODO
}


hook_method<CPC* (CNPCUpdater::*)(int range, int level)> CNPCUpdater::_GetNeighborLowerLevelPc(SERVER, "CNPCUpdater::GetNeighborLowerLevelPc");
CPC* CNPCUpdater::GetNeighborLowerLevelPc(int range, int level)
{
	return (this->*_GetNeighborLowerLevelPc)(range, level);

	//TODO
}


hook_method<CCharacter* (CNPCUpdater::*)(int range)> CNPCUpdater::_GetNeighborEnemy(SERVER, "CNPCUpdater::GetNeighborEnemy");
CCharacter* CNPCUpdater::GetNeighborEnemy(int range)
{
	return (this->*_GetNeighborEnemy)(range);

	//TODO
}


hook_method<CCharacter* (CNPCUpdater::*)(int range)> CNPCUpdater::_GetMyOwnerEnemy(SERVER, "CNPCUpdater::GetMyOwnerEnemy");
CCharacter* CNPCUpdater::GetMyOwnerEnemy(int range)
{
	return (this->*_GetMyOwnerEnemy)(range);

	//TODO
}


hook_method<void (CNPCUpdater::*)(CCharacter* ch, int damage, int attdamage)> CNPCUpdater::_AddEnemy(SERVER, "CNPCUpdater::AddEnemy");
void CNPCUpdater::AddEnemy(CCharacter* ch, int damage, int attdamage)
{
	return (this->*_AddEnemy)(ch, damage, attdamage);

	unsigned long AID = ch->GetAccountID();
	unsigned long GID = ch->OnMsg(NULL, NULL, CM_GET_CHARACTERID, 0, 0, 0, 0);
	unsigned long GRID = ch->OnMsg(NULL, NULL, CM_GET_GRID_IFEXPSHARE, 0, 0, 0, 0);

	for( mystd::list<ATTACK_PC>::iterator it = m_attackPC.begin(); it != m_attackPC.end(); ++it )
	{
		if( it->AID == AID && it->GID == GID )
		{
			it->damage += damage;
			it->attdamage += attdamage;
			it->GRID = GRID;
			return; // added to existing entry.
		}
	}

	if( m_attackPC.size() > 20 )
		m_attackPC.pop_front(); // discard oldest entry.

	ATTACK_PC attackPC;
	attackPC.GRID = GRID;
	attackPC.damage = damage;
	attackPC.attdamage = attdamage;
	attackPC.AID = AID;
	attackPC.GID = GID;

	m_attackPC.push_back(attackPC);
}


/* hook_method<CCharacter* (CNPCUpdater::*)(int range)> CNPCUpdater::_GetEnemy_AttackMyOwer(SERVER, "CNPCUpdater::GetEnemy_AttackMyOwer");
CCharacter* CNPCUpdater::GetEnemy_AttackMyOwer(int range)
{
	return (this->*_GetEnemy_AttackMyOwer)(range);

	//TODO
} */


hook_method<int (CNPCUpdater::*)(int xPos, int yPos, unsigned char dir)> CNPCUpdater::_InitPosition(SERVER, "CNPCUpdater::InitPosition");
int CNPCUpdater::InitPosition(int xPos, int yPos, unsigned char dir)
{
	return (this->*_InitPosition)(xPos, yPos, dir);

	//TODO
}


//hook_method<short (CNPCUpdater::*)(unsigned long AID)> CNPCUpdater::_GetEnemy(SERVER, "CNPCUpdater::GetEnemy");
short CNPCUpdater::GetEnemy(unsigned long AID)
{
//	return (this->*_GetEnemy)(AID);

	for( mystd::list<ATTACK_PC>::const_iterator i = m_attackPC.begin(); i != m_attackPC.end(); ++i )
		if( i->AID == AID )
			return static_cast<short>(i->damage);

	return 0;
}


hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_GiveExpToPC(SERVER, "CNPCUpdater::GiveExpToPC");
void CNPCUpdater::GiveExpToPC(void) // line 1274
{
	return (this->*_GiveExpToPC)();

	if( m_npc->m_characterInfo.maxhp <= 0 )
		return; // already processed.

	float totaldamage = 0.0;

	for( mystd::list<ATTACK_PC>::iterator it = m_attackPC.begin(); it != m_attackPC.end(); )
	{
		ATTACK_PC& atk = *it;

		totaldamage += atk.damage;

		CCharacter* CH = g_characterMgr->CCharacterMgr::FastFindCharacter(atk.AID);
		if( CH == NULL )
		{
			it = m_attackPC.erase(it);
			continue;
		}

		int CH_GID, CH_MapID, myMapID;
		CH->GetParameterValue(VAR_CHARACTERID, CH_GID);
		CH->GetParameterValue(VAR_MAPID, CH_MapID);
		m_npc->GetParameterValue(VAR_MAPID, myMapID);

		if( atk.GID != CH_GID || CH->GetState() == CHARACTER_STATE_DEAD || CH_MapID != myMapID )
		{
			it = m_attackPC.erase(it);
			continue;
		}

		++it; // eligible person
	}

	size_t nOthers = m_attackPC.size() - 1;
	if( nOthers >= 20 ) nOthers = 20;

	double peopleBonus = nOthers * 25.0 / 100.0;

	double totalbexp = m_npc->m_characterInfo.exp;
	totalbexp += totalbexp * peopleBonus;

	double totaljexp = m_npc->m_characterInfo.jexp;
	totaljexp += totaljexp * peopleBonus;

	int efstBonus = m_npc->GetEffective(EFST_EXPUP,0) + m_npc->GetEffective(EFST_RICHMANKIM,0);
	if( efstBonus > 0 )
	{
		totalbexp = totalbexp * efstBonus / 100.0;
		totaljexp = totaljexp * efstBonus / 100.0;
	}

	MVPINFO* mvpinfo = this->CNPCUpdater::GetMVPInfo();
	if( mvpinfo != NULL )
	{
		unsigned long mvpAID = this->CNPCUpdater::GetMVP();

		PACKET_ZC_MVP_GETTING_SPECIAL_EXP exppkt;
		exppkt.PacketType = HEADER_ZC_MVP_GETTING_SPECIAL_EXP;
		exppkt.exp = (unsigned long)(totalbexp * mvpinfo->expPercent / 10000.0);
		g_characterMgr->CCharacterMgr::SendMsg(m_npc, mvpAID, CM_SEND_PACKET, sizeof(exppkt), (int)&exppkt, 0, 0);
		g_characterMgr->CCharacterMgr::SendMsg(m_npc, mvpAID, CM_ADD_MVPEXP, (int)exppkt.exp, 0, 0, 0);

		// mvp exp reward reduces the remaining shared exp pool!
		totalbexp -= exppkt.exp;

		for( int i = 0; i < countof(mvpinfo->itemPercent); ++i )
		{
			if( GetServerRandom(0, 20000) % 10000 < mvpinfo->itemPercent[i] )
			{
				const char* itemName = mvpinfo->itemName[i];

				PACKET_ZC_MVP_GETTING_ITEM itempkt;
				itempkt.PacketType = HEADER_ZC_MVP_GETTING_ITEM;
				itempkt.ITID = g_itpMgr->CITPMgr::GetITID(itemName);

				g_characterMgr->CCharacterMgr::SendMsg(m_npc, mvpAID, CM_SEND_PACKET, sizeof(itempkt), (int)&itempkt, 0, 0);
				g_characterMgr->CCharacterMgr::SendMsg(m_npc, mvpAID, CM_ADD_MVPITEM, (int)itemName, 0, 0, 0);
				break;
			}
		}
	}

	for( mystd::list<ATTACK_PC>::const_iterator it = m_attackPC.begin(); it != m_attackPC.end(); ++it )
	{
		const ATTACK_PC& atk = *it;

		int baseexp = static_cast<int>(totalbexp * atk.damage / totaldamage);
		int jobexp  = static_cast<int>(totaljexp * atk.damage / totaldamage);

		CPC* pc = (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(atk.AID, PC_TYPE);
		if( pc != NULL )
		{
			if( pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_TK_MISSION,0) == 1 && pc->m_characterInfo.job == JT_TAEKWON && atk.damage / totaldamage >= 0.5 )
			{
				WARP_POSITION& warpinfo = pc->m_pcSkill.CPCSkill::GetWarpPosInfo()->front();
				short& missionTarget = warpinfo.xPos;
				short& killCount = warpinfo.yPos;

				const char* monMission = g_monParameter->CMonParameterMgr::GetMonsterName(missionTarget);
				const char* monKilled = g_monParameter->CMonParameterMgr::GetMonsterName(m_npc->m_characterInfo.job);

				if( monMission != NULL && monKilled != NULL && strcmp(monMission, monKilled) == 0 )
				{
					if( killCount == 99 )
						g_makerRankMgr->CMakerRankMgr::UpdateMakerRank(pc, 2, 0, pc->m_makerRankPoint);

					++killCount;
					if( killCount > 100 )
						killCount = 100;
				}
			}

			if( pc->m_pcSkill.CPCSkill::GetSkillLevel(SKID_MB_PETMEMORY,0) == 1 )
			{
				if( atk.damage / totaldamage >= 0.5 )
				{
					int origexp = baseexp;

					if( pc->CPC::GetMyPetObject() != NULL )
					{
						int storedexp = pc->GetEffective(EFST_EXPMEMORY,0);

						if( storedexp != 0 && baseexp < storedexp )
							baseexp = storedexp; // gain (bigger) stored exp instead!

						int npcClass;
						m_npc->GetParameterValue(VAR_CLASS, npcClass);

						if( npcClass != NPC_CLASS_BOSS )
							pc->SetEffective(EFST_EXPMEMORY, 9999, origexp, 0, 0, 1);
					}
				}
			}
		}

		if( baseexp > 0 )
		{
			if( atk.GRID == 0 )
				g_characterMgr->CCharacterMgr::SendMsg(m_npc, atk.AID, CM_ADD_EXP, baseexp, atk.damage, 0, 0);
			else
				g_characterMgr->CCharacterMgr::SendMsg(m_npc, atk.AID, CM_SHARE_EXP, baseexp, 0, 0, 0);
		}

		if( jobexp > 0 )
		{
			if( atk.GRID == 0 )
				g_characterMgr->CCharacterMgr::SendMsg(m_npc, atk.AID, CM_ADD_JOBEXP, jobexp, m_npc->m_pathInfo.m_moveInfo.xPos, m_npc->m_pathInfo.m_moveInfo.yPos, 0);
			else
				g_characterMgr->CCharacterMgr::SendMsg(m_npc, atk.AID, CM_SHARE_JOBEXP, jobexp, 0, 0, 0);
		}
	}
}


hook_method<void (CNPCUpdater::*)(CPC* other)> CNPCUpdater::_NotifyUpdateInfo(SERVER, "CNPCUpdater::NotifyUpdateInfo");
void CNPCUpdater::NotifyUpdateInfo(CPC* other)
{
	return (this->*_NotifyUpdateInfo)(other);

	switch( m_npc->m_neighborCache.CNeighborCache::GetUpdateInfo(m_npc, other) )
	{
	case 0:
	{
		PACKET_ZC_NOTIFY_MOVEENTRY3 packet;
		packet.PacketType = HEADER_ZC_NOTIFY_MOVEENTRY3;
		packet.objecttype = m_npc->GetType();
		packet.GID = this->CNPCUpdater::GetAccountID();
		packet.job = m_npc->m_characterInfo.job;
		packet.sex = m_npc->m_characterInfo.sex;
		packet.speed = m_npc->GetSpeed();
		packet.moveStartTime = m_npc->m_pathInfo.m_moveInfo.LastTime;
		packet.xSize = static_cast<unsigned char>(m_npc->m_characterInfo.xSize);
		packet.ySize = static_cast<unsigned char>(m_npc->m_characterInfo.ySize);
		packet.head = m_npc->m_characterInfo.head;
		packet.weapon = m_npc->m_characterInfo.weapon;
		packet.accessory = m_npc->m_characterInfo.accessory;
		packet.bodyState = m_npc->CNPC::GetBodyState();
		packet.healthState = m_npc->GetHealthState();
		packet.effectState = m_npc->GetEffectState();
		packet.headpalette = 0;
		packet.bodypalette = 0;
		packet.isPKModeON = 0;
		packet.headDir = m_npc->m_characterInfo.headerDir;
		packet.accessory2 = HIWORD(m_npc->m_characterInfo.GuildID);
		packet.accessory3 = LOWORD(m_npc->m_characterInfo.GuildID);
		packet.GUID = 0;
		packet.GEmblemVer = 0;
		packet.honor = 0;
		packet.virtue = m_npc->m_characterInfo.virtue;
		packet.clevel = m_npc->m_characterInfo.clevel;

		float xPos; float yPos; int dir;
		m_npc->m_pathInfo.CPathInfo::GetPos(m_npc->GetSpeed(), timeGetTime(), xPos, yPos, dir);

		int sx, sy, xsubcell, ysubcell;
		TransformFloatPosCellPos(xPos, sx, xsubcell);
		TransformFloatPosCellPos(yPos, sy, ysubcell);

		EncodeSrcDst(sx, sy, m_npc->m_pathInfo.m_moveInfo.dxPos, m_npc->m_pathInfo.m_moveInfo.dyPos, xsubcell, ysubcell, packet.MoveData);
		other->CPC::Send(sizeof(packet), (char*)&packet);
	}
	break;
	case 3:
	{
		PACKET_ZC_NOTIFY_STANDENTRY_NPC packet;
		packet.PacketType = HEADER_ZC_NOTIFY_STANDENTRY_NPC;
		packet.objecttype = m_npc->GetType();
		packet.GID = this->CNPCUpdater::GetAccountID();
		packet.job = m_npc->m_characterInfo.job;
		packet.sex = m_npc->m_characterInfo.sex;
		packet.speed = m_npc->GetSpeed();
		packet.xSize = static_cast<unsigned char>(m_npc->m_characterInfo.xSize);
		packet.ySize = static_cast<unsigned char>(m_npc->m_characterInfo.ySize);
		packet.head = m_npc->m_characterInfo.head;
		packet.weapon = m_npc->m_characterInfo.weapon;
		packet.accessory = m_npc->m_characterInfo.accessory;
		packet.bodyState = m_npc->CNPC::GetBodyState();
		packet.healthState = m_npc->GetHealthState();
		packet.effectState = m_npc->GetEffectState();
		packet.isPKModeON = 0;
		packet.headpalette = m_npc->GetType();
		packet.bodypalette = 0;
		packet.headDir = m_npc->m_characterInfo.headerDir;
		packet.accessory2 = HIWORD(m_npc->m_characterInfo.GuildID);
		packet.accessory3 = LOWORD(m_npc->m_characterInfo.GuildID);
		packet.shield = m_npc->GetEmblemVersion();
		EncodePosDir(m_npc->m_pathInfo.m_moveInfo.xPos, m_npc->m_pathInfo.m_moveInfo.yPos, m_npc->m_pathInfo.m_moveInfo.dir, packet.PosDir);
		other->CPC::Send(sizeof(packet), (char*)&packet);
	}
	break;
	case 1:
	{
		PACKET_ZC_NOTIFY_STANDENTRY packet;
		packet.PacketType = HEADER_ZC_NOTIFY_STANDENTRY;
		packet.objecttype = m_npc->GetType();
		packet.GID = this->CNPCUpdater::GetAccountID();
		packet.job = m_npc->m_characterInfo.job;
		packet.sex = m_npc->m_characterInfo.sex;
		packet.speed = m_npc->GetSpeed();
		packet.xSize = static_cast<unsigned char>(m_npc->m_characterInfo.xSize);
		packet.ySize = static_cast<unsigned char>(m_npc->m_characterInfo.ySize);
		packet.head = m_npc->m_characterInfo.head;
		packet.weapon = m_npc->m_characterInfo.weapon;
		packet.accessory = m_npc->m_characterInfo.accessory;
		packet.bodyState = m_npc->CNPC::GetBodyState();
		packet.healthState = m_npc->GetHealthState();
		packet.effectState = m_npc->GetEffectState();
		packet.headpalette = 0;
		packet.bodypalette = 0;
		packet.state = 0;
		packet.isPKModeON = 0;
		packet.headDir = m_npc->m_characterInfo.headerDir;
		packet.accessory2 = HIWORD(m_npc->m_characterInfo.GuildID);
		packet.accessory3 = LOWORD(m_npc->m_characterInfo.GuildID);
		packet.shield = m_npc->GetEmblemVersion();
		packet.GEmblemVer = 0;
		packet.GUID = 0;
		packet.honor = 0;
		packet.virtue = static_cast<short>(m_npc->m_characterInfo.virtue);
		packet.clevel = m_npc->m_characterInfo.clevel;
		EncodePosDir(m_npc->m_pathInfo.m_moveInfo.xPos, m_npc->m_pathInfo.m_moveInfo.yPos, m_npc->m_pathInfo.m_moveInfo.dir, packet.PosDir);
		other->CPC::Send(sizeof(packet), (char*)&packet);

		unsigned long roomID = m_npc->CNPC::GetRoomID();
		if( roomID != 0 )
		{
			unsigned long ownerID = g_roomMgr->CRoomMgr::GetOwner(roomID);
			if( ownerID == this->CNPCUpdater::GetAccountID() )
				g_characterMgr->CCharacterMgr::SendMsg(m_npc, other->GetAccountID(), 0x1Fu, roomID, 0, 0, 0);
		}
	}
	break;
	case 2:
	case 4:
	{
		PACKET_ZC_NOTIFY_VANISH packet;
		packet.PacketType = HEADER_ZC_NOTIFY_VANISH;
		packet.GID = this->CNPCUpdater::GetAccountID();
		packet.type = VT_OUTOFSIGHT;
		other->CPC::Send(sizeof(packet), (char*)&packet);
	}
	break;
	default:
	break;
	}
}


hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_StopMoveSlowly(SERVER, "CNPCUpdater::StopMoveSlowly");
void CNPCUpdater::StopMoveSlowly(void)
{
	return (this->*_StopMoveSlowly)();

	//TODO
}


hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_StopMove(SERVER, "?StopMove@CNPCUpdater@@QAEXXZ");
void CNPCUpdater::StopMove(void)
{
	return (this->*_StopMove)();

	//TODO
}


hook_method<void (CNPCUpdater::*)(short x, short y, int isMove)> CNPCUpdater::_StopMove2(SERVER, "?StopMove@CNPCUpdater@@QAEXFFH@Z");
void CNPCUpdater::StopMove(short x, short y, int isMove)
{
	return (this->*_StopMove2)(x, y, isMove);

	//TODO
}


hook_method<unsigned long (CNPCUpdater::*)(void)> CNPCUpdater::_GetAccountID(SERVER, "CNPCUpdater::GetAccountID");
unsigned long CNPCUpdater::GetAccountID(void)
{
	return (this->*_GetAccountID)();

	return m_npc->m_characterInfo.accountID;
}


hook_method<void (CNPCUpdater::*)(unsigned long type)> CNPCUpdater::_NotifyStopMove(SERVER, "CNPCUpdater::NotifyStopMove");
void CNPCUpdater::NotifyStopMove(unsigned long type)
{
	return (this->*_NotifyStopMove)(type);

	//TODO
}


//hook_method<int (CNPCUpdater::*)(void)> CNPCUpdater::_IsValid(SERVER, "CNPCUpdater::IsValid");
int CNPCUpdater::IsValid(void)
{
//	return (this->*_IsValid)();

	return m_npc->m_characterInfo.isValid;
}


hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_Stop(SERVER, "CNPCUpdater::Stop");
void CNPCUpdater::Stop(void)
{
	return (this->*_Stop)();

	//TODO
}


hook_method<MVPINFO* (CNPCUpdater::*)(void)> CNPCUpdater::_GetMVPInfo(SERVER, "CNPCUpdater::GetMVPInfo");
MVPINFO* CNPCUpdater::GetMVPInfo(void)
{
	return (this->*_GetMVPInfo)();

	//TODO
}


hook_method<unsigned long (CNPCUpdater::*)(void)> CNPCUpdater::_GetMVP(SERVER, "CNPCUpdater::GetMVP");
unsigned long CNPCUpdater::GetMVP(void) // line 1771
{
	return (this->*_GetMVP)();

	int maxdmg = 0;
	unsigned long AID = 0;
	CCharacter* mvpCH = NULL;

	for( mystd::list<ATTACK_PC>::const_iterator it = m_attackPC.begin(); it != m_attackPC.end(); ++it )
	{
		const ATTACK_PC& atk = *it;

		CCharacter* CH = g_characterMgr->CCharacterMgr::FastFindCharacter(atk.AID);
		if( CH == NULL )
			continue; // offline

		int CH_CharID;
		CH->GetParameterValue(VAR_CHARACTERID, CH_CharID);
		if( atk.GID != CH_CharID )
			continue; // same account but not this char

		if( CH->GetState() == CHARACTER_STATE_DEAD )
			continue; // is dead

		int CH_mapID;
		CH->GetParameterValue(VAR_MAPID, CH_mapID);
		if( CH_mapID != m_npc->m_characterInfo.mapID )
			continue; // is not on same map
		
		if( maxdmg >= atk.damage + atk.attdamage )
			continue; // not the highest damage

		// found potential mvp candidate
		maxdmg = atk.damage + atk.attdamage;
		AID = atk.AID;
		mvpCH = CH;
	}

	if( mvpCH != NULL && (mvpCH->GetType() == NPC_HO_TYPE || mvpCH->GetType() == NPC_MERSOL_TYPE) )
		return ((CNPC*)mvpCH)->m_myParentAID; // homuns&mercs delegate to owner
	
	return AID;
}


class TItemRoutingPriority
{
public:
	/* this+0 */ unsigned long m_AID;
	/* this+4 */ int m_damage;

	bool operator ==(const TItemRoutingPriority& rhs) { return m_AID == rhs.m_AID; }
	TItemRoutingPriority& operator=(const TItemRoutingPriority& rhs) { m_AID = rhs.m_AID; m_damage = rhs.m_damage; return *this; }
	TItemRoutingPriority(const unsigned long AID, const int damage) { m_AID = AID; m_damage = damage; }
	~TItemRoutingPriority() { }
};


struct ItemRoutingComp : public mystd::binary_function<TItemRoutingPriority,TItemRoutingPriority,bool>
{
	public: bool operator()(const TItemRoutingPriority& lhs, const TItemRoutingPriority& rhs) const
	{
		return ( lhs.m_damage < rhs.m_damage );
	}
};


hook_method<void (CNPCUpdater::*)(SORTED_PCLIST* sortList)> CNPCUpdater::_GetPickableSortList(SERVER, "CNPCUpdater::GetPickableSortList");
void CNPCUpdater::GetPickableSortList(SORTED_PCLIST* sortList) // line 1839-1889
{
	return (this->*_GetPickableSortList)(sortList);

	mystd::vector<TItemRoutingPriority> Container;
	int totalDamage = 0;

	for( mystd::list<ATTACK_PC>::iterator it = m_attackPC.begin(); it != m_attackPC.end(); ++it )
	{
		unsigned long AID = it->AID;
		int damage = it->damage;

		totalDamage += damage;

		CNPC* npc = (CNPC*)g_characterMgr->CCharacterMgr::FindCharacter(AID, NPC_TYPE);
		if( npc != NULL && npc->GetType() == NPC_MERSOL_TYPE || npc->GetType() == NPC_HO_TYPE )
			AID = npc->m_myParentAID;

		mystd::vector<TItemRoutingPriority>::iterator itContainer;
		for( itContainer = Container.begin(); itContainer != Container.end(); ++itContainer )
			if( itContainer->m_AID == AID )
				break;

		if( itContainer == Container.end() )
		{
			TItemRoutingPriority TempIRPriority(AID, damage);
			Container.push_back(TempIRPriority);
		}
		else
		{
			itContainer->m_damage += damage;
		}
	}

	if( Container.size() != 0 )
		Container[0].m_damage += totalDamage * 30 / 100;

	if( Container.size() > 1 )
	{
		int nMax = Container.size();
		if( nMax > 3 )
			nMax = 3;
		mystd::partial_sort(Container.begin(), Container.begin() + nMax, Container.end(), ItemRoutingComp());
	}

	int i;
	mystd::vector<TItemRoutingPriority>::const_iterator it;
	for( i = 0, it = Container.begin(); i < 3 && it != Container.end(); ++i, ++it )
	{
		sortList[i].AID = it->m_AID;
		sortList[i].val = it->m_damage;
	}
}


hook_method<CPC* (CNPCUpdater::*)(int length, int curEnemyAID)> CNPCUpdater::_GetNearestPcMoreThanEnemy(SERVER, "CNPCUpdater::GetNearestPcMoreThanEnemy");
CPC* CNPCUpdater::GetNearestPcMoreThanEnemy(int length, int curEnemyAID)
{
	return (this->*_GetNearestPcMoreThanEnemy)(length, curEnemyAID);

	//TODO
}


hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_CheckMove(SERVER, "CNPCUpdater::CheckMove");
void CNPCUpdater::CheckMove(void) // line 84
{
	return (this->*_CheckMove)();

	//TODO
}


hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_CheckState(SERVER, "CNPCUpdater::CheckState");
void CNPCUpdater::CheckState(void) // line 1040
{
	return (this->*_CheckState)();

	//TODO
}


hook_method<unsigned long (CNPCUpdater::*)(int range)> CNPCUpdater::_GetNeighborPcNumber(SERVER, "CNPCUpdater::GetNeighborPcNumber");
unsigned long CNPCUpdater::GetNeighborPcNumber(int range)
{
	return (this->*_GetNeighborPcNumber)(range);

	//TODO
}


hook_method<CNPC* (CNPCUpdater::*)(int xRange, int yRange)> CNPCUpdater::_GetNeighborNPC(SERVER, "CNPCUpdater::GetNeighborNPC");
CNPC* CNPCUpdater::GetNeighborNPC(int xRange, int yRange)
{
	return (this->*_GetNeighborNPC)(xRange, yRange);

	//TODO
}


//hook_method<void (CNPCUpdater::*)(CPC* other, int characterState)> CNPCUpdater::_NotifyOptionalInfo(SERVER, "CNPCUpdater::NotifyOptionalInfo");
void CNPCUpdater::NotifyOptionalInfo(CPC* other, int characterState)
{
//	return (this->*_NotifyOptionalInfo)(other, characterState);

	;
}


hook_method<void (CNPCUpdater::*)(mystd::vector<CCharacter *>* section)> CNPCUpdater::_UpdateCharacter(SERVER, "CNPCUpdater::UpdateCharacter");
void CNPCUpdater::UpdateCharacter(mystd::vector<CCharacter *>* section)
{
	return (this->*_UpdateCharacter)(section);

	//TODO
}


/* hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_NotifyDisconnect(SERVER, "CNPCUpdater::NotifyDisconnect");
void CNPCUpdater::NotifyDisconnect(void)
{
	return (this->*_NotifyDisconnect)();

	//TODO
} */


hook_method<void (CNPCUpdater::*)(void)> CNPCUpdater::_ResetAttackPCList(SERVER, "CNPCUpdater::ResetAttackPCList");
void CNPCUpdater::ResetAttackPCList(void) // line 1932
{
	return (this->*_ResetAttackPCList)();

	//TODO
}
