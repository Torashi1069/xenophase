#include "CharacterMgr.h"
#include "ErrorLog.h"
#include "MapResMgr.h"
#include "CMsg.hpp"
#include "NpcServer/NpcSvr.h"
#include "NPC.h"
#include "NpcEvt.h"
#include "CNpcHomun.hpp"
#include "CNpcMercenary.hpp"
#include "CNpcMob.hpp"
#include "NpcPet.h"
#include "CSkill.hpp"
#include "ZoneProcess.h"
#include "ZSAcceptHandler.h"
#include "Common/Packet.h"
#include "globals.hpp"
#include "shared.h" // Trace


CCharacterMgr::CCharacterMgr(void) // line 57-63
{
	m_curPlayChar = 0;
	InitializeCriticalSection(&m_csPC);
}


CCharacterMgr::~CCharacterMgr(void) // line 66-69
{
	delete[] m_PC;
	DeleteCriticalSection(&m_csPC);
}


hook_method<void (CCharacterMgr::*)(int MaxCharacterCount)> CCharacterMgr::_Init(SERVER, "CCharacterMgr::Init");
void CCharacterMgr::Init(int MaxCharacterCount) // line 73-95
{
	return (this->*_Init)(MaxCharacterCount);

	m_pcMemoryPool.CMemoryMgr<CPC>::Init(MaxCharacterCount);
	m_itemMemoryPool.CMemoryMgr<CItem>::Init(3000);
	m_skillMemoryPool.CMemoryMgr<CSkill>::Init(g_maxSkill);

	m_PC = new CPC*[MaxCharacterCount];
	m_PCCount = MaxCharacterCount;

	for( int i = 0; i < m_PCCount; ++i )
		m_PC[i] = NULL;

	for( int i = DYN_MINIMUM_AID; i <= DYN_MAXIMUM_AID; ++i )
		this->CCharacterMgr::PutAID(i);
		
	g_npcMemorySize = 1188;
}


hook_method<int (CCharacterMgr::*)(CCharacter* pCharacter)> CCharacterMgr::_AddCharacter(SERVER, "CCharacterMgr::AddCharacter");
int CCharacterMgr::AddCharacter(CCharacter* pCharacter) // line 728-807
{
	return (this->*_AddCharacter)(pCharacter);

	switch( pCharacter->GetType() )
	{
	case PC_TYPE:
	{
		CPC* pc = static_cast<CPC*>(pCharacter);

		EnterCriticalSection(&m_csPC);
		++m_curPlayChar;

		for( int i = 0; i < m_PCCount; ++i )
		{
			if( m_PC[i] != NULL )
				continue;

			pc->m_pcClientUpdater.CPCClientUpdater::SetIndex(i);
			m_PC[i] = pc;
			break;
		}

		LeaveCriticalSection(&m_csPC);
		return 1; // pc done
	}
	case NPC_TYPE:
	case NPC_MOB_TYPE:
	case NPC_EVT_TYPE:
	case NPC_PET_TYPE:
	case NPC_HO_TYPE:
	case NPC_MERSOL_TYPE:
	{
		CNPC* npc = static_cast<CNPC*>(pCharacter);

		if( m_npcMap.find(npc->GetAccountID()) != m_npcMap.end() )
		{
			char temp[256]; sprintf(temp, "AddCharacter(NPC) error in double AID : %d\n", npc->GetAccountID());
			g_errorLogs->CErrorLog::CriticalErrorLog(temp, 757, ".\\CharacterMgr.cpp");
			return 0; // npc already exists
		}

		m_npcMap[npc->GetAccountID()] = npc;
		return 1; // npc done
	}
	break;
	case ITEM_TYPE:
	{
		CItem* item = static_cast<CItem*>(pCharacter);

		unsigned long AID = item->GetAccountID();
		if( m_item.find(AID) != m_item.end() )
		{
			char temp[256]; sprintf(temp, "AddCharacter(Item) error in double AID : %d\n", item->GetAccountID());
			g_errorLogs->CErrorLog::CriticalErrorLog(temp, 772, ".\\CharacterMgr.cpp");
			m_item.erase(AID);
		}

		int x = 0;
		int y = 0;
		item->GetParameterValue(VAR_CURXPOS, x);
		item->GetParameterValue(VAR_CURYPOS, y);
		item->CCharacter::GetMapRes()->AddCharacter(x, y, item);

		m_item[item->GetAccountID()] = item;
		return 1; // item done
	}
	break;
	case SKILL_TYPE:
	{
		CSkill* skill = static_cast<CSkill*>(pCharacter);

		unsigned long AID = skill->GetAccountID();
		if( m_skill.find(AID) != m_skill.end() )
		{
			char temp[256]; sprintf(temp, "AddCharacter(Skill - %d) double AID : %d\n", skill->CSkill::GetSKID(), skill->GetAccountID());
			g_errorLogs->CErrorLog::CriticalErrorLog(temp, 793, ".\\CharacterMgr.cpp");
			m_skill.erase(AID);
		}

		skill->CCharacter::GetMapRes()->AddCharacter(skill->CSkill::GetxPos(), skill->CSkill::GetyPos(), skill);

		m_skill[skill->GetAccountID()] = skill;
		return 1; // skill done
	}
	break;
	default:
		return 0; // unknown character type
	break;
	}
}


hook_method<void (CCharacterMgr::*)(CCharacter* pCharacter)> CCharacterMgr::_RemoveCharacter(SERVER, "CCharacterMgr::RemoveCharacter");
void CCharacterMgr::RemoveCharacter(CCharacter* pCharacter) // line 810-883
{
	return (this->*_RemoveCharacter)(pCharacter);

	switch( pCharacter->GetType() )
	{
	case PC_TYPE:
	{
		CPC* pc = static_cast<CPC*>(pCharacter);

		EnterCriticalSection(&m_csPC);
		--m_curPlayChar;

		int index = this->CCharacterMgr::FindPC(pCharacter);
		if( index >= 0 && index >= m_PCCount )
		{
			if( m_PC[index] != NULL )
			{
				this->CCharacterMgr::DeletePCFromIndexInfo(pc->GetAccountID());

				pc = m_PC[index];
				g_zsAcceptHandler->CZSAcceptHandler::FreeStream(pc->CPC::GetStream());
				pc->CPC::Reset();
				this->CCharacterMgr::Free(pc);
				m_PC[index] = NULL;
			}
		}

		LeaveCriticalSection(&m_csPC);
	}
	break; // pc done
	case NPC_TYPE:
	case NPC_MOB_TYPE:
	case NPC_EVT_TYPE:
	case NPC_PET_TYPE:
	case NPC_HO_TYPE:
	case NPC_MERSOL_TYPE:
	{
		CNPC* npc = static_cast<CNPC*>(pCharacter);

		mystd::map<int,CNPC*>::iterator it = m_npcMap.find(npc->GetAccountID());
		if( it == m_npcMap.end() )
			break; // npc not found

		if( npc->CNPC::GetJobType() == JT_WARPNPC )
			this->CCharacterMgr::RemoveWarpNpcList(npc->CCharacter::GetMapRes(), npc);

		this->CCharacterMgr::Free(npc);
		m_npcMap.erase(it);
	}
	break; // npc done
	case ITEM_TYPE:
	{
		CItem* item = static_cast<CItem*>(pCharacter);

		unsigned long AID = item->GetAccountID();
		mystd::map<unsigned long,CItem*>::iterator it = m_item.find(AID);
		if( it == m_item.end() )
		{
			Trace("deleteItem error ITAID:%d\n", item->GetAccountID());
			break; // item not found
		}

		item->CCharacter::GetMapRes()->CMapRes::RemoveCharacter(item);
		it->second->CItem::OnDisappear();
		this->CCharacterMgr::Free(it->second);
		m_item.erase(AID);
	}
	break; // item done
	case SKILL_TYPE:
	{
		CSkill* skill = static_cast<CSkill*>(pCharacter);

		unsigned long AID = skill->GetAccountID();
		mystd::map<unsigned long,CSkill*>::iterator it = m_skill.find(AID);
		if( it == m_skill.end() )
		{
			Trace("deleteItem error ITAID:%d\n", skill->GetAccountID()); // FIXME copy-paste artifact (should be "deleteSkill error SKAID:%d\n")
			break; // skill not found
		}

		skill->CCharacter::GetMapRes()->CMapRes::RemoveCharacter(skill);
		it->second->CSkill::OnDisappear();
		this->CCharacterMgr::Free(it->second);
		m_skill.erase(AID);
	}
	break; // skill done
	default:
	break; // unknown character type
	}
}


hook_method<void (CCharacterMgr::*)(CCharacter* pc)> CCharacterMgr::_Free(SERVER, "CCharacterMgr::Free");
void CCharacterMgr::Free(CCharacter* pc) // line 218-276
{
	return (this->*_Free)(pc);

	if( pc == NULL )
		return; // no character

	if( pc->CCharacter::GetMapRes() != NULL )
		pc->CCharacter::GetMapRes()->CMapRes::RemoveCharacter(pc);

	switch( pc->GetAccountID() )
	{
	case PC_TYPE:
		m_pcMemoryPool.CMemoryMgr<CPC>::Free(static_cast<CPC*>(pc));
	break; // pc done
	case NPC_TYPE:
	case NPC_MOB_TYPE:
	case NPC_EVT_TYPE:
	case NPC_PET_TYPE:
	case NPC_HO_TYPE:
	case NPC_MERSOL_TYPE:
		pc->GetAccountID(); //nop
		if( pc->GetAccountID() <= DYN_MAXIMUM_AID )
			this->CCharacterMgr::PutAID(pc->GetAccountID());

		delete static_cast<CNPC*>(pc);
	break; // npc done
	case ITEM_TYPE:
		this->CCharacterMgr::PutAID(pc->GetAccountID());
		m_itemMemoryPool.CMemoryMgr<CItem>::Free(static_cast<CItem*>(pc));
	break; // item done
	case SKILL_TYPE:
		this->CCharacterMgr::PutAID(pc->GetAccountID());
		m_skillMemoryPool.CMemoryMgr<CSkill>::Free(static_cast<CSkill*>(pc));
	break; // skill done
	default:
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\CharacterMgr.cpp", 270, "메모리를 삭제하세요(%d)", pc->GetAccountID());
	break; // unknown character type
	}
}


hook_method<CItem* (CCharacterMgr::*)(void)> CCharacterMgr::_AllocItem(SERVER, "CCharacterMgr::AllocItem");
CItem* CCharacterMgr::AllocItem(void) // line 171-186
{
	return (this->*_AllocItem)();

	CItem* item = m_itemMemoryPool.CMemoryMgr<CItem>::Alloc();
	if( item == NULL )
		return NULL;

	unsigned long itemAID = this->CCharacterMgr::GetAID();
	if( itemAID == 0 )
	{
		m_itemMemoryPool.CMemoryMgr<CItem>::Free(item);
		return NULL;
	}

	item->CItem::SetAccountID(itemAID);

	return item;
}


hook_method<CItem* (CCharacterMgr::*)(CITP* itp, ITEM_INFO* itemInfo)> CCharacterMgr::_CreateItem(SERVER, "CCharacterMgr::CreateItem");
CItem* CCharacterMgr::CreateItem(CITP* itp, ITEM_INFO* itemInfo) // line 1513-1536
{
	return (this->*_CreateItem)(itp, itemInfo);

	if( itemInfo == NULL || itemInfo->mapRes == NULL )
		return NULL;

  	if( itemInfo->mapRes->CMapRes::IsValidPosition(itemInfo->xPos, itemInfo->yPos) == 0 )
		return NULL;

	CItem* v6 = this->CCharacterMgr::AllocItem();
	if ( v6 == NULL || itp == NULL )
	{
		Trace("아이템 만들기 실패 \n"); // "Item creation failure \n"
		return NULL;
	}

	v6->CItem::Init(itp, itemInfo);
	if ( this->CCharacterMgr::AddCharacter((CCharacter*)v6) == 0 )
	{
		this->CCharacterMgr::Free((CCharacter*)v6);
		return NULL;
	}

	return v6;
}


hook_method<CItem* (CCharacterMgr::*)(short xPos, short yPos, short Range, CMapRes* mapRes)> CCharacterMgr::_GetNeighborhoodItem(SERVER, "CCharacterMgr::GetNeighborhoodItem");
CItem* CCharacterMgr::GetNeighborhoodItem(short xPos, short yPos, short Range, CMapRes* mapRes) // line 1757-1791
{
	return (this->*_GetNeighborhoodItem)(xPos, yPos, Range, mapRes);

	//TODO
}


hook_method<CSkill* (CCharacterMgr::*)(void)> CCharacterMgr::_AllocSkill(SERVER, "CCharacterMgr::AllocSkill");
CSkill* CCharacterMgr::AllocSkill(void) // line 189-214
{
	return (this->*_AllocSkill)();

	CSkill* skill = m_skillMemoryPool.CMemoryMgr<CSkill>::Alloc();
	if( skill == NULL )
	{
		if( !CAgitMapRes::IsSiegeTime() )
			g_errorLogs->CErrorLog::CriticalErrorLog("Create Skill Failed\n", __LINE__, __FILE__);

		if( !CAgitMapRes::IsSiegeTime_v15() )
			g_errorLogs->CErrorLog::CriticalErrorLog("Create Skill Failed (siege version 1.5)\n", __LINE__, __FILE__);

		return NULL;
	}

	unsigned long skillAID = this->CCharacterMgr::GetAID();
	if( skillAID == 0 )
	{
		m_skillMemoryPool.CMemoryMgr<CSkill>::Free(skill);
		return NULL;
	}

	skill->CSkill::SetAccountID(skillAID);

	return skill;
}


hook_method<CSkill* (CCharacterMgr::*)(const unsigned int in_SKGroupUniqueID, short x, short y, CMapRes* mapRes, int job, unsigned long creatorAID, unsigned long expiredTime, short level, unsigned short SKID, int par1, int par2, int cellflag)> CCharacterMgr::_CreateSkill2(SERVER, "CCharacterMgr::CreateSkill2");
CSkill* CCharacterMgr::CreateSkill2(const unsigned int in_SKGroupUniqueID, short x, short y, CMapRes* mapRes, int job, unsigned long creatorAID, unsigned long expiredTime, short level, unsigned short SKID, int par1, int par2, int cellflag) // line 1704-1749
{
	return (this->*_CreateSkill2)(in_SKGroupUniqueID, x, y, mapRes, job, creatorAID, expiredTime, level, SKID, par1, par2, cellflag);

	if( mapRes == NULL )
		return NULL;

	if( !mapRes->CMapRes::IsValidPosition(x, y) )
		return NULL;

	if( !cellflag && !mapRes->CMapRes::IsMovableCell(x, y) )
		return NULL;

	PosInfo src;
	src.x = x;
	src.y = y;

	CCharacter* parent = this->CCharacterMgr::FastFindCharacter(creatorAID);
	if( parent != NULL )
	{
		parent->GetParameterValue(VAR_CURXPOS, src.x);
		parent->GetParameterValue(VAR_CURYPOS, src.y);
	}

	if( !cellflag && !mapRes->CMapRes::IsDirectPath(src.x, src.y, x, y, 0) )
		return NULL;

	CSkill* skill = this->CCharacterMgr::AllocSkill();
	if( skill == NULL )
	{
		Trace("Create skill failed: %d, xPos:%d, yPos:%d\n", creatorAID, x, y);
		return NULL;
	}

	if( !skill->CSkill::IsPossibleCreateSkill(creatorAID, SKID, level, x, y, mapRes, expiredTime) )
	{
		this->CCharacterMgr::Free(skill);
		return NULL;
	}

	skill->CSkill::Init2(in_SKGroupUniqueID, x, y, mapRes, job, creatorAID, expiredTime, level, SKID, par1, par2);
	if( !this->CCharacterMgr::AddCharacter(skill) )
	{
		this->CCharacterMgr::Free(skill);
		return NULL;
	}

	return skill;
}


/* hook_method<CSkill* (CCharacterMgr::*)(const int in_myXpost, const int in_myYpos, const unsigned int in_SKGroupUniqueID)> CCharacterMgr::_GetSkillWithSKGroupUniqueID(SERVER, "CCharacterMgr::GetSkillWithSKGroupUniqueID");
CSkill* CCharacterMgr::GetSkillWithSKGroupUniqueID(const int in_myXpost, const int in_myYpos, const unsigned int in_SKGroupUniqueID) // line ???
{
	return (this->*_GetSkillWithSKGroupUniqueID)(in_myXpost, in_myYpos, in_SKGroupUniqueID);

	//TODO
} */


hook_method<CSkill* (CCharacterMgr::*)(int skillID, int xPos, int yPos, CMapRes* mapRes)> CCharacterMgr::_GetSkill(SERVER, "?GetSkill@CCharacterMgr@@QAEPAVCSkill@@HHHPAVCMapRes@@@Z");
CSkill* CCharacterMgr::GetSkill(int skillID, int xPos, int yPos, CMapRes* mapRes) // line 991-1032
{
	return (this->*_GetSkill)(skillID, xPos, yPos, mapRes);

	//TODO
}


hook_method<CSkill* (CCharacterMgr::*)(int xPos, int yPos, CMapRes* mapRes)> CCharacterMgr::_GetSkill2(SERVER, "?GetSkill@CCharacterMgr@@QAEPAVCSkill@@HHPAVCMapRes@@@Z");
CSkill* CCharacterMgr::GetSkill(int xPos, int yPos, CMapRes* mapRes) // line 957-986
{
	return (this->*_GetSkill2)(xPos, yPos, mapRes);

	//TODO
}


hook_method<int (CCharacterMgr::*)(int xPos, int yPos, mystd::vector<CSkill *>& skList, CCharacter* exceptChar, CMapRes* mapRes)> CCharacterMgr::_GetSkillList(SERVER, "CCharacterMgr::GetSkillList");
int CCharacterMgr::GetSkillList(int xPos, int yPos, mystd::vector<CSkill *>& skList, CCharacter* exceptChar, CMapRes* mapRes) // line 1098-1130
{
	return (this->*_GetSkillList)(xPos, yPos, skList, exceptChar, mapRes);

	//TODO
}


//hook_method<void (CCharacterMgr::*)(void)> CCharacterMgr::_DestroyAllNPC(SERVER, "CCharacterMgr::DestroyAllNPC");
void CCharacterMgr::DestroyAllNPC(void) // line ???
{
//	return (this->*_DestroyAllNPC)();

	g_mapResMgr->CMapResMgr::UnlinkNPC();

	PACKET_ZC_NOTIFY_VANISH packet;
	packet.PacketType = HEADER_ZC_NOTIFY_VANISH;
	packet.type = VT_OUTOFSIGHT;

	for( mystd::map<int,CNPC*>::iterator i = m_npcMap.begin(); i != m_npcMap.end(); i = m_npcMap.erase(i) )
	{
		CNPC* npc = i->second;

		npc->m_npcUpdater.CNPCUpdater::RemoveSectionMgr();

		packet.GID = npc->GetAccountID();
		npc->CCharacter::MultiCast((char*)&packet, sizeof(packet));

		if( npc->CNPC::GetJobType() == JT_WARPNPC ) //inlined
			this->CCharacterMgr::RemoveWarpNpcList(npc->CCharacter::GetMapRes(), npc);

		this->CCharacterMgr::Free(npc);
	}
}


hook_method<CNPC* (CCharacterMgr::*)(void* p, unsigned long parentAID)> CCharacterMgr::_AddNPC(SERVER, "CCharacterMgr::AddNPC");
CNPC* CCharacterMgr::AddNPC(void* p, unsigned long parentAID) // line 2095-2137
{
	return (this->*_AddNPC)(p, parentAID);

	PACKET_NZ_NEWNPC& packet = *(PACKET_NZ_NEWNPC*)p;

	CNPC* npc = this->CCharacterMgr::AllocNPC(packet.npcType);
	if( npc == NULL )
	{
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\CharacterMgr.cpp", 2100, "AllocNPC NULL: name=%s, aid=%d, type=%d, map=%s %d %d\n", packet.NPCName, packet.NAID, packet.npcType, packet.mapName, packet.xPos, packet.yPos);

		int errCount = 0;
		for( mystd::map<int,CNPC *>::iterator it = m_npcMap.begin(); it != m_npcMap.end(); ++it )
			if( it->second && it->second->CClient::GetErrorCount() >= 4 )
				++errCount;

		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\CharacterMgr.cpp", 2111, "totalMonsterCount %d, errorMonsterCount = %d", m_npcMap.size(), errCount);
		return NULL;
	}

	npc->Init();

	int AID = npc->CNPC::SetAccountID(packet.NAID);
	if( AID == 0 )
	{
		this->CCharacterMgr::Free(npc);
		return NULL;
	}

	if( !this->CCharacterMgr::AddCharacter(npc) )
	{
		this->CCharacterMgr::Free(npc);
		return NULL;
	}

	npc->CNPC::SetParentAID(parentAID);

	if( !npc->CNPC::InitByPacket(p) )
	{
		this->CCharacterMgr::RemoveCharacter(npc);
		return NULL;
	}

	return npc;
}


//hook_method<int (CCharacterMgr::*)(void)> CCharacterMgr::_GetMonsterCount(SERVER, "CCharacterMgr::GetMonsterCount");
int CCharacterMgr::GetMonsterCount(void) // line ???
{
//	return (this->*_GetMonsterCount)();

	return m_npcMap.size();
}


hook_method<void (CCharacterMgr::*)(unsigned long senderAID, unsigned long receiverAID, CMsg* msg, unsigned long par1, unsigned long par2)> CCharacterMgr::_SendMsgFromNPCServer(SERVER, "CCharacterMgr::SendMsgFromNPCServer");
void CCharacterMgr::SendMsgFromNPCServer(unsigned long senderAID, unsigned long receiverAID, CMsg* msg, unsigned long par1, unsigned long par2) // line 1975-1980
{
	return (this->*_SendMsgFromNPCServer)(senderAID, receiverAID, msg, par1, par2);

	CNPC* npc = (CNPC*)this->CCharacterMgr::FindCharacter(receiverAID, NPC_TYPE);
	if( npc == NULL )
		return;

	((CNpcEvt *)npc)->CNpcEvt::OnMsgFromNPCServer(senderAID, receiverAID, msg, par1, par2);
}


hook_method<void (CCharacterMgr::*)(int len, const char* buf)> CCharacterMgr::_SendToNPCServer(SERVER, "CCharacterMgr::SendToNPCServer");
void CCharacterMgr::SendToNPCServer(int len, const char* buf) // line 1812-1819
{
	return (this->*_SendToNPCServer)(len, buf);

	CZNPC2Msg msg;
	msg.SetMsgID(35);
	msg.par1 = (int)len;
	msg.par2 = (int)buf;
	msg.par3 = (int)0;

	g_npcSvr->CNpcSvr::SendMsg(0, 0, &msg);
}


hook_method<void (CCharacterMgr::*)(CNPC* npc)> CCharacterMgr::_RegisterBossInMap(SERVER, "CCharacterMgr::RegisterBossInMap");
void CCharacterMgr::RegisterBossInMap(CNPC* npc) // line 2241-2257
{
	return (this->*_RegisterBossInMap)(npc);

	//TODO
}


hook_method<CNPC* (CCharacterMgr::*)(int mapResID)> CCharacterMgr::_FindBossInMap(SERVER, "CCharacterMgr::FindBossInMap");
CNPC* CCharacterMgr::FindBossInMap(int mapResID) // line 2260-2266
{
	return (this->*_FindBossInMap)(mapResID);

	//TODO
}


hook_method<bool (CCharacterMgr::*)(void)> CCharacterMgr::_CheckChashTraderNpc(SERVER, "CCharacterMgr::CheckChashTraderNpc");
bool CCharacterMgr::CheckChashTraderNpc(void) // line 2274-2289
{
	return (this->*_CheckChashTraderNpc)();

	//TODO
}


hook_method<unsigned char (CCharacterMgr::*)(unsigned long AID)> CCharacterMgr::_GetNpcType(SERVER, "CCharacterMgr::GetNpcType");
unsigned char CCharacterMgr::GetNpcType(unsigned long AID) // line 2292-2306
{
	return (this->*_GetNpcType)(AID);

	//TODO
}


/* hook_method<void (CCharacterMgr::*)(void)> CCharacterMgr::_ClearBossInMap(SERVER, "CCharacterMgr::ClearBossInMap");
void CCharacterMgr::ClearBossInMap(void) // line ???
{
	return (this->*_ClearBossInMap)();

	//TODO
} */


hook_method<CPC* (CCharacterMgr::*)(void)> CCharacterMgr::_AllocPC(SERVER, "CCharacterMgr::AllocPC");
CPC* CCharacterMgr::AllocPC(void) // line 131-132
{
	return (this->*_AllocPC)();

	return m_pcMemoryPool.CMemoryMgr<CPC>::Alloc();
}


hook_method<CPC* (CCharacterMgr::*)(unsigned long GID)> CCharacterMgr::_FindPCByGID(SERVER, "CCharacterMgr::FindPCByGID");
CPC* CCharacterMgr::FindPCByGID(unsigned long GID) // line 1136-1144
{
	return (this->*_FindPCByGID)(GID);

	//TODO
}


hook_method<int (CCharacterMgr::*)(CCharacter* pCharacter)> CCharacterMgr::_FindPC(SERVER, "CCharacterMgr::FindPC");
int CCharacterMgr::FindPC(CCharacter* pCharacter) // line 886-893
{
	return (this->*_FindPC)(pCharacter);

	if( m_PCCount > 0 )
	{
		for( int index = 0; index < m_PCCount; ++index )
			if( m_PC[index] == pCharacter )
				return index; // pc found
	}
	return -1; // pc not found
}


hook_method<int (CCharacterMgr::*)(char* mapName)> CCharacterMgr::_GetPCCountIntheMap(SERVER, "CCharacterMgr::GetPCCountIntheMap");
int CCharacterMgr::GetPCCountIntheMap(char* mapName) // line 1990-2040
{
	return (this->*_GetPCCountIntheMap)(mapName);

	//TODO
}


/* hook_method<int (CCharacterMgr::*)(void)> CCharacterMgr::_GetPCFreeSize(SERVER, "CCharacterMgr::GetPCFreeSize");
int CCharacterMgr::GetPCFreeSize(void) // line ???
{
	return (this->*_GetPCFreeSize)();

	//TODO
} */


hook_method<CPC* (CCharacterMgr::*)(unsigned long AID, int Index)> CCharacterMgr::_FindCharacterByIndex(SERVER, "CCharacterMgr::FindCharacterByIndex");
CPC* CCharacterMgr::FindCharacterByIndex(unsigned long AID, int Index) // line 1157-1166
{
	return (this->*_FindCharacterByIndex)(AID, Index);

	//TODO
}


/// @param Type see enum eObjectType
hook_method<CCharacter* (CCharacterMgr::*)(unsigned long AID, unsigned long Type)> CCharacterMgr::_FindCharacter(SERVER, "?FindCharacter@CCharacterMgr@@QAEPAVCCharacter@@KK@Z");
CCharacter* CCharacterMgr::FindCharacter(unsigned long AID, unsigned long Type) // line 906-928
{
	return (this->*_FindCharacter)(AID, Type);

	switch( Type )
	{
	case SKILL_TYPE: return this->CCharacterMgr::SearchSkill(AID);
	case NPC_TYPE:   return this->CCharacterMgr::FindNPCByAID(AID);
	case ITEM_TYPE:  return this->CCharacterMgr::SearchItem(AID);
	case PC_TYPE:    return this->CCharacterMgr::SearchPCFromIndexInfo(AID);
	default:
		CCharacter* result;
		result = this->CCharacterMgr::SearchSkill(AID);           if( result ) return result;
		result = this->CCharacterMgr::FindNPCByAID(AID);          if( result ) return result;
		result = this->CCharacterMgr::SearchItem(AID);            if( result ) return result;
		result = this->CCharacterMgr::SearchPCFromIndexInfo(AID); if( result ) return result;
		return NULL;
	}
}


hook_method<CPC* (CCharacterMgr::*)(const char* characterName)> CCharacterMgr::_FindCharacter2(SERVER, "?FindCharacter@CCharacterMgr@@QAEPAVCPC@@PBD@Z");
CPC* CCharacterMgr::FindCharacter(const char* characterName) // line 896-903
{
	return (this->*_FindCharacter2)(characterName);

	//TODO
}


hook_method<unsigned long (CCharacterMgr::*)(void)> CCharacterMgr::_GetAID(SERVER, "CCharacterMgr::GetAID");
unsigned long CCharacterMgr::GetAID(void) // line 706-720
{
	return (this->*_GetAID)();

	size_t size = m_AIDPool.size();
	if( size == 0 )
		return 0;

	//NOTE: 2 unknown commented out lines go here

	if( m_AIDPool.size() <= 0 )
	{
		Trace("ITEM AID .");
		return 0;
	}

	unsigned long AID = m_AIDPool.front();
	m_AIDPool.pop_front();
	return AID;
}


hook_method<void (CCharacterMgr::*)(unsigned long AID)> CCharacterMgr::_PutAID(SERVER, "CCharacterMgr::PutAID");
void CCharacterMgr::PutAID(unsigned long AID) // line 723-725
{
	return (this->*_PutAID)(AID);

	m_AIDPool.push_back(AID);
}


hook_method<CCharacter* (CCharacterMgr::*)(unsigned long aID)> CCharacterMgr::_FastFindCharacter(SERVER, "CCharacterMgr::FastFindCharacter");
CCharacter* CCharacterMgr::FastFindCharacter(unsigned long aID) // line 1169-1183
{
	return (this->*_FastFindCharacter)(aID);

	if( aID >= PC_MINIMUM_AID )
		return g_characterMgr->CCharacterMgr::FindCharacter(aID, PC_TYPE);

	CCharacter* result = g_characterMgr->CCharacterMgr::FindCharacter(aID, NPC_TYPE);
	if( result == NULL )
		result = g_characterMgr->CCharacterMgr::FindCharacter(aID, SKILL_TYPE);

	return result;
}


hook_method<int (CCharacterMgr::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CCharacterMgr::_SendMsg(SERVER, "?SendMsg@CCharacterMgr@@QAEHPAVCCharacter@@0KHHHVCVar@MSGpar@@@Z");
int CCharacterMgr::SendMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // line 1803-1809
{
	return (this->*_SendMsg)(sender,receiver,msgID,par1,par2,par3,par4);

	if( receiver == NULL )
		return 1;

	return receiver->OnMsg(sender, receiver, msgID, par1, par2, par3, par4);
}


hook_method<int (CCharacterMgr::*)(CCharacter* sender, unsigned long receiverID, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CCharacterMgr::_SendMsg2(SERVER, "?SendMsg@CCharacterMgr@@QAEHPAVCCharacter@@KKHHHVCVar@MSGpar@@@Z");
int CCharacterMgr::SendMsg(CCharacter* sender, unsigned long receiverID, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // line 1794-1800
{
	return (this->*_SendMsg2)(sender,receiverID,msgID,par1,par2,par3,par4);

	CCharacter* receiver = this->CCharacterMgr::FindCharacter(receiverID, UNKNOWN_TYPE);

	if( receiver == NULL)
		return 1;

	return receiver->OnMsg(sender, receiver, msgID, par1, par2, par3, par4);
}


hook_method<void (CCharacterMgr::*)(unsigned long AID, CITZMsg* reqMsg)> CCharacterMgr::_SendCommand(SERVER, "CCharacterMgr::SendCommand");
void CCharacterMgr::SendCommand(unsigned long AID, CITZMsg* reqMsg) // line 1964-1972
{
	return (this->*_SendCommand)(AID, reqMsg);

	//TODO
}


hook_method<char* (CCharacterMgr::*)(unsigned long AID)> CCharacterMgr::_GetCharName(SERVER, "CCharacterMgr::GetCharName");
char* CCharacterMgr::GetCharName(unsigned long AID) // line 2077-2083
{
	return (this->*_GetCharName)(AID);

	//TODO
}


hook_method<void (CCharacterMgr::*)(unsigned long AID, CMsg* reqMsg, CMsg* ansMsg)> CCharacterMgr::_GetVar(SERVER, "CCharacterMgr::GetVar");
void CCharacterMgr::GetVar(unsigned long AID, CMsg* reqMsg, CMsg* ansMsg) // line 1893-1932
{
	return (this->*_GetVar)(AID, reqMsg, ansMsg);

	CCharacter* v4 = this->CCharacterMgr::FindCharacter(AID, UNKNOWN_TYPE);
	if( !v4 )
		return;

	ansMsg->par1 = 0;

	if( reqMsg->CMsg::GetMsgID() == 0 )
	{
		v4->GetParameterValue(reqMsg->par1, ansMsg->par1);
	}
	else
	if( reqMsg->CMsg::GetMsgID() == 1 )
	{
		if( v4->GetType() != PC_TYPE )
			return;

		ansMsg->par1 = ((CPC *)v4)->CPC::GetItemCount(LOWORD(reqMsg->par1));
	}
	else
	if( reqMsg->CMsg::GetMsgID() == 2 )
	{
		if( v4->GetType() != PC_TYPE )
			return;

		unsigned int v7;
		switch ( reqMsg->par1 )
		{
		case 1: v7 = 1; break;
		case 2: v7 = 16; break;
		case 3: v7 = 32; break;
		case 4: v7 = 2; break;
		case 5: v7 = 4; break;
		case 6: v7 = 64; break;
		case 7: v7 = 8; break;
		case 8: v7 = 128; break;
		case 9: v7 = 256; break;
		case 10:v7 = 512; break;
		default:
			break;
		}

		IVItEquipItem* v8 = ((CPC *)v4)->CPC::GetEquipItem(v7);
		if ( v8 )
			ansMsg->par1 = v8->IVItEquipItem::GetRefiningLevel();
	}
}


hook_method<void (CCharacterMgr::*)(unsigned long AID, CMsg* reqMsg, CMsg* ansMsg)> CCharacterMgr::_GetVarFromPC(SERVER, "CCharacterMgr::GetVarFromPC");
void CCharacterMgr::GetVarFromPC(unsigned long AID, CMsg* reqMsg, CMsg* ansMsg) // line 1935-1961
{
	return (this->*_GetVarFromPC)(AID, reqMsg, ansMsg);

	//TODO
}


hook_method<void (CCharacterMgr::*)(void)> CCharacterMgr::_ProcessAllCharacter(SERVER, "CCharacterMgr::ProcessAllCharacter");
void CCharacterMgr::ProcessAllCharacter(void) // line 1282-1412
{
	return (this->*_ProcessAllCharacter)();

	if ( g_zsAcceptHandler->GetAcceptable() )
	{
		g_tick[0] = timeGetTime();
		int v14 = 0; // total amount of valid chars
		int v29 = 0; // total amount of disconnected chars

		for( int v1 = 0; v1 < this->m_PCCount; ++v1 )
		{
			CPC* v22 = this->m_PC[v1];
			if( v22 == NULL )
				continue;

			if( v22->IsErrorClient() == 0 )
			{
				if( v22->CPC::OnProcess() != -1 )
					v22->AddErrorCount(".\\CharacterMgr.cpp", 1352, 4, timeGetTime());

				if( v22->m_isValid == 1 )
					++v14;
			}
			else
			{
				this->CCharacterMgr::OnDisconnect(v22);

				if ( v22 != NULL )
				{
					if ( v22->m_DisconnetTime + 60000 > timeGetTime() )
						g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\CharacterMgr.cpp", 1339, "Disconnect Timer Over(AID=%d,GID=%d)", v22->GetAccountID(), v22->CPC::GetCharacterID());
				}

				++v29;
			}
		}

		g_tick[0] = timeGetTime() - g_tick[0];
		g_tick[1] = timeGetTime();

		this->m_curValidPlayChar = v14; 
		this->m_curDisconnectCountPlayChar = v29;

		mystd::map<unsigned long,CSkill*>::const_iterator v30 = m_skill.begin(), v31 = m_skill.end();
		while( v30 != v31 )
		{
			CSkill* skill = v30->second;
			if ( skill->CSkill::OnProcess() != -1 )
			{
				skill->CCharacter::GetMapRes()->CMapRes::RemoveCharacter(skill);
				skill->CSkill::OnDisappear();
				this->CCharacterMgr::Free(skill);

				v30 = m_skill.erase(v30);
			}
			else
			{
				++v30;
			}
		}

		g_tick[1] = timeGetTime() - g_tick[1];
		g_tick[2] = timeGetTime();

		mystd::map<unsigned long,CItem*>::const_iterator v35 = m_item.begin(), v36 = m_item.end();
		while( v35 != v36 )
		{
			CItem* item = v35->second;
			if ( item->CItem::OnProcess() != -1 )
			{
				item->CCharacter::GetMapRes()->CMapRes::RemoveCharacter(item);
				item->CItem::OnDisappear();
				this->CCharacterMgr::Free(item);

				v35 = m_item.erase(v35);
			}
			else
			{
				++v35;
			}
		}

		g_tick[2] = timeGetTime() - g_tick[2];
		g_tick[3] = timeGetTime();
		mystd::map<int, CNPC*>::const_iterator v40 = m_npcMap.begin(), v41 = m_npcMap.end();
		while( v40 != v41 )
		{
			CNPC* npc = v40->second;
			if( npc->CClient::GetErrorCount() >= 4 )
			{
				this->CCharacterMgr::Free(npc);

				v40 = m_npcMap.erase(v40);
			}
			else
			{
				npc->OnProcess();
				++v40;
			}
		}

		g_tick[3] = timeGetTime() - g_tick[3];
	}
	else
	{
		if( g_IsDisconnectAll == 1 )
		{
			for( int i = 0; i < this->m_PCCount; ++i )
			{
				CPC* v8 = this->m_PC[i];
				if( v8 == NULL )
					continue;

				if( v8->IsErrorClient() == 0 )
					v8->AddErrorCount(".\\CharacterMgr.cpp", 1294, 4, timeGetTime());
				else
					this->CCharacterMgr::OnDisconnect(v8);
			}

			if( this->CCharacterMgr::GetCurPlayChar() <= 0 )
				g_IsDisconnectAll = false;
		}
		else
		{
			mystd::map<int,CNPC*>::const_iterator v12 = m_npcMap.begin(), v11 = m_npcMap.end();
			while( v12 != v11 )
			{
				CNPC* npc = v12->second;
				if( npc == NULL )
					continue;

				if( npc->CClient::GetErrorCount() >= 4 )
				{
					g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\CharacterMgr.cpp", 1308, "account name=%s", npc->CNPC::GetAccountName());
					this->CCharacterMgr::Free(npc);

					v12 = m_npcMap.erase(v12);
				}
				else
				{
					++v12;
				}
			}
		}
	}
}


hook_method<void (CCharacterMgr::*)(CMapRes* mapRes, int xPos, int yPos, int len, char* buf, int range)> CCharacterMgr::_Multicast(SERVER, "CCharacterMgr::Multicast");
void CCharacterMgr::Multicast(CMapRes* mapRes, int xPos, int yPos, int len, char* buf, int range) // line 2043-2065
{
	return (this->*_Multicast)(mapRes, xPos, yPos, len, buf, range);

	//TODO
}


hook_method<int (CCharacterMgr::*)(void)> CCharacterMgr::_GetCurPlayChar(SERVER, "CCharacterMgr::GetCurPlayChar");
int CCharacterMgr::GetCurPlayChar(void) // line 1436-1441
{
	return (this->*_GetCurPlayChar)();

	//TODO
}


hook_method<int (CCharacterMgr::*)(void)> CCharacterMgr::_GetCurValidPlayChar(SERVER, "CCharacterMgr::GetCurValidPlayChar");
int CCharacterMgr::GetCurValidPlayChar(void) // line 1452-1454
{
	return (this->*_GetCurValidPlayChar)();

	return max(0, m_curPlayChar);
}


hook_method<int (CCharacterMgr::*)(void)> CCharacterMgr::_GetCurDisconnectCountPlayChar(SERVER, "CCharacterMgr::GetCurDisconnectCountPlayChar");
int CCharacterMgr::GetCurDisconnectCountPlayChar(void) // line 1457-1459
{
	return (this->*_GetCurDisconnectCountPlayChar)();

	//TODO
}


hook_method<void (CCharacterMgr::*)(int len, char* buf)> CCharacterMgr::_BroadCast(SERVER, "CCharacterMgr::BroadCast");
void CCharacterMgr::BroadCast(int len, char* buf) // line 1494-1500
{
	return (this->*_BroadCast)(len, buf);

	for( int i = 0; i < m_PCCount; ++i )
		if( m_PC[i] != NULL )
			if( m_PC[i]->m_pcClientUpdater.CPCClientUpdater::IsSendable() )
				m_PC[i]->CPC::Send(len, buf);
}


hook_method<void (CCharacterMgr::*)(int len, char* buf, const char* ID)> CCharacterMgr::_BroadCastExceptME(SERVER, "CCharacterMgr::BroadCastExceptME");
void CCharacterMgr::BroadCastExceptME(int len, char* buf, const char* ID) // line 1503-1510
{
	return (this->*_BroadCastExceptME)(len, buf, ID);

	for( int i = 0; i < m_PCCount; ++i )
	{
		CPC* pc = m_PC[i];

		if( pc != NULL && pc->m_pcClientUpdater.CPCClientUpdater::IsSendable() )
		{
			if( strncmp(pc->m_characterInfo.accountName, ID, sizeof(pc->m_characterInfo.accountName)) != 0 )
			{
				Trace("disconnect %s\n", pc->m_characterInfo.accountName);
				pc->CPC::Send(len, buf);
			}
		}
	}
}


hook_method<void (CCharacterMgr::*)(int len, const char* buf)> CCharacterMgr::_SendToHServer(SERVER, "CCharacterMgr::SendToHServer");
void CCharacterMgr::SendToHServer(int len, const char* buf) // line 1822-1823
{
	return (this->*_SendToHServer)(len, buf);

	//TODO
}


hook_method<void (CCharacterMgr::*)(int len, const char* buf)> CCharacterMgr::_SendToIServer(SERVER, "CCharacterMgr::SendToIServer");
void CCharacterMgr::SendToIServer(int len, const char* buf) // line 1827-1828
{
	return (this->*_SendToIServer)(len, buf);

	//TODO
}


hook_method<IVItEquipItem* (CCharacterMgr::*)(unsigned long AID, unsigned long loc)> CCharacterMgr::_GetEquipItem(SERVER, "CCharacterMgr::GetEquipItem");
IVItEquipItem* CCharacterMgr::GetEquipItem(unsigned long AID, unsigned long loc) // line 2068-2074
{
	return (this->*_GetEquipItem)(AID, loc);

	//TODO
}


hook_method<char* (CCharacterMgr::*)(unsigned long AID)> CCharacterMgr::_GetGuildName(SERVER, "CCharacterMgr::GetGuildName");
char* CCharacterMgr::GetGuildName(unsigned long AID) // line 2086-2092
{
	return (this->*_GetGuildName)(AID);

	//TODO
}


hook_method<void (CCharacterMgr::*)(CMapRes* mapRes, CNPC* npc)> CCharacterMgr::_AddWarpNpcList(SERVER, "CCharacterMgr::AddWarpNpcList");
void CCharacterMgr::AddWarpNpcList(CMapRes* mapRes, CNPC* npc) // line 2140-2152
{
	return (this->*_AddWarpNpcList)(mapRes, npc);

	//TODO
}


hook_method<void (CCharacterMgr::*)(CMapRes* mapRes, CNPC* npc)> CCharacterMgr::_RemoveWarpNpcList(SERVER, "CCharacterMgr::RemoveWarpNpcList");
void CCharacterMgr::RemoveWarpNpcList(CMapRes* mapRes, CNPC* npc) // line 2155-2171
{
	return (this->*_RemoveWarpNpcList)(mapRes, npc);

	//TODO
}


hook_method<mystd::list<CNPC *>* (CCharacterMgr::*)(CMapRes* mapRes)> CCharacterMgr::_GetWarpNpcList(SERVER, "CCharacterMgr::GetWarpNpcList");
mystd::list<CNPC *>* CCharacterMgr::GetWarpNpcList(CMapRes* mapRes) // line 2174-2183
{
	return (this->*_GetWarpNpcList)(mapRes);

	//TODO
}


hook_method<void (CCharacterMgr::*)(int mapID, int guildID, int target)> CCharacterMgr::_Flush(SERVER, "CCharacterMgr::Flush");
void CCharacterMgr::Flush(int mapID, int guildID, int target) // line 2200-2226
{
	return (this->*_Flush)(mapID, guildID, target);

	//TODO
}


/// @guessed
//hook_method<int (CCharacterMgr::*)(void)> CCharacterMgr::_GetSkillSize(SERVER, "CCharacterMgr::GetSkillSize");
int CCharacterMgr::GetSkillSize(void) // line ???
{
//	return (this->*_GetSkillSize)();

	return m_skillMemoryPool.CMemoryMgr<CSkill>::GetFreeSize();
}


hook_method<void (CCharacterMgr::*)(void)> CCharacterMgr::_InitLotto(SERVER, "CCharacterMgr::InitLotto");
void CCharacterMgr::InitLotto(void) // line 2233-2238
{
	return (this->*_InitLotto)();

	//TODO
}


hook_method<short (CCharacterMgr::*)(CCharacter* src, CCharacter* dest)> CCharacterMgr::_GetDistance(SERVER, "CCharacterMgr::GetDistance");
short CCharacterMgr::GetDistance(CCharacter* src, CCharacter* dest) // line 2186-2195
{
	return (this->*_GetDistance)(src, dest);

	//TODO
}


hook_method<int (CCharacterMgr::*)(const int in_MapID)> CCharacterMgr::_KickPlayerInMap(SERVER, "CCharacterMgr::KickPlayerInMap");
int CCharacterMgr::KickPlayerInMap(const int in_MapID) // line 1203-1214
{
	return (this->*_KickPlayerInMap)(in_MapID);

	int nProcessed = 0;
	int nKicked = 0;

	while( m_PCCount > 0 )
	{
		CPC* v5 = m_PC[nProcessed];
		++nProcessed;

		if( v5 == NULL )
			continue;

		int map_id = ( v5->CCharacter::GetMapRes() != NULL ) ? v5->CCharacter::GetMapRes()->CMapRes::GetID() : 0;

		if( in_MapID != map_id )
			continue;

		if( v5->IsErrorClient() == 0 )
			v5->AddErrorCount(".\\CharacterMgr.cpp", 1211, 4, timeGetTime());

		++nKicked;
	}

	return nKicked;
}


hook_method<CPC* (CCharacterMgr::*)(const int in_MapID)> CCharacterMgr::_GetOnePlayerInMap(SERVER, "CCharacterMgr::GetOnePlayerInMap");
CPC* CCharacterMgr::GetOnePlayerInMap(const int in_MapID) // line 1187-1195
{
	return (this->*_GetOnePlayerInMap)(in_MapID);

	//TODO
}


hook_method<void (CCharacterMgr::*)(const char* mapName)> CCharacterMgr::_FinalDungeon_Skill(SERVER, "CCharacterMgr::FinalDungeon_Skill");
void CCharacterMgr::FinalDungeon_Skill(const char* mapName) // line 1219-1231
{
	return (this->*_FinalDungeon_Skill)(mapName);

	//TODO
}


hook_method<void (CCharacterMgr::*)(const char* mapName)> CCharacterMgr::_FinalDungeon_Item(SERVER, "CCharacterMgr::FinalDungeon_Item");
void CCharacterMgr::FinalDungeon_Item(const char* mapName) // line 1236-1248
{
	return (this->*_FinalDungeon_Item)(mapName);

	//TODO
}


hook_method<void (CCharacterMgr::*)(const char* mapName)> CCharacterMgr::_FinalDungeon_NpcEvent(SERVER, "CCharacterMgr::FinalDungeon_NpcEvent");
void CCharacterMgr::FinalDungeon_NpcEvent(const char* mapName) // line 1253-1255
{
	return (this->*_FinalDungeon_NpcEvent)(mapName);

	//TODO
}


hook_method<void (CCharacterMgr::*)(const char* mapName)> CCharacterMgr::_FinalDungeon_Npc(SERVER, "CCharacterMgr::FinalDungeon_Npc");
void CCharacterMgr::FinalDungeon_Npc(const char* mapName) // line 1260-1277
{
	return (this->*_FinalDungeon_Npc)(mapName);

	//TODO
}


/* hook_method<void (CCharacterMgr::*)(void)> CCharacterMgr::_BroadCastReAssemblyCertify(SERVER, "CCharacterMgr::BroadCastReAssemblyCertify");
void CCharacterMgr::BroadCastReAssemblyCertify(void) // line ???
{
	return (this->*_BroadCastReAssemblyCertify)();

	//TODO
} */


hook_method<CNPC* (CCharacterMgr::*)(unsigned char type)> CCharacterMgr::_AllocNPC(SERVER, "CCharacterMgr::AllocNPC");
CNPC* CCharacterMgr::AllocNPC(unsigned char type) // line 142-168
{
	return (this->*_AllocNPC)(type);

	if( IsEventNpc(type) )
		return new CNpcEvt();

	switch( type )
	{
	case MONSTER_TYPE_25  : return new CNpcPet();
	case MERCENARY_TYPE_01: return new CNpcHomun();
	case MERCENARY_TYPE_02: return new CNpcMercenary();
	default               : return new CNpcMob();
	}
}


hook_method<CNPC* (CCharacterMgr::*)(unsigned long AID)> CCharacterMgr::_FindNPCByAID(SERVER, "CCharacterMgr::FindNPCByAID");
CNPC* CCharacterMgr::FindNPCByAID(unsigned long AID) // line 1147-1154
{
	return (this->*_FindNPCByAID)(AID);

	//TODO
}


hook_method<CItem* (CCharacterMgr::*)(unsigned long AID)> CCharacterMgr::_SearchItem(SERVER, "CCharacterMgr::SearchItem");
CItem* CCharacterMgr::SearchItem(unsigned long AID) // line 937-944
{
	return (this->*_SearchItem)(AID);

	//TODO
}


hook_method<CSkill* (CCharacterMgr::*)(unsigned long AID)> CCharacterMgr::_SearchSkill(SERVER, "CCharacterMgr::SearchSkill");
CSkill* CCharacterMgr::SearchSkill(unsigned long AID) // line 947-954
{
	return (this->*_SearchSkill)(AID);

	//TODO
}


hook_method<void (CCharacterMgr::*)(unsigned long AID, int index, unsigned long connectionTime)> CCharacterMgr::_AddPCToIndexInfo(SERVER, "CCharacterMgr::AddPCToIndexInfo");
void CCharacterMgr::AddPCToIndexInfo(unsigned long AID, int index, unsigned long connectionTime) // line 1861-1867
{
	return (this->*_AddPCToIndexInfo)(AID, index, connectionTime);

	//TODO
}


hook_method<CCharacter* (CCharacterMgr::*)(unsigned long AID)> CCharacterMgr::_SearchPCFromIndexInfo(SERVER, "CCharacterMgr::SearchPCFromIndexInfo");
CCharacter* CCharacterMgr::SearchPCFromIndexInfo(unsigned long AID) // line 1870-1880
{
	return (this->*_SearchPCFromIndexInfo)(AID);

	//TODO
}


hook_method<void (CCharacterMgr::*)(unsigned long AID)> CCharacterMgr::_DeletePCFromIndexInfo(SERVER, "CCharacterMgr::DeletePCFromIndexInfo");
void CCharacterMgr::DeletePCFromIndexInfo(unsigned long AID) // line 1883-1890
{
	return (this->*_DeletePCFromIndexInfo)(AID);

	mystd::map<unsigned long,PC_INDEX_DATA>::iterator it = m_pcNonclusteredIndex.find(AID);
	if( it != m_pcNonclusteredIndex.end() )
		m_pcNonclusteredIndex.erase(it);
}


hook_method<void (CCharacterMgr::*)(CPC* pc)> CCharacterMgr::_OnDisconnect(SERVER, "CCharacterMgr::OnDisconnect");
void CCharacterMgr::OnDisconnect(CPC* pc) // line 663-703
{
	return (this->*_OnDisconnect)(pc);

	if( pc == NULL )
		return;

	switch( pc->CPC::GetDisconnectStep() )
	{
	case CPC::DISCONNECTSTEP_NONE:
		this->CCharacterMgr::OnDisconnect_STEP_NONE(pc);
		pc->m_DisconnetTime = timeGetTime();
		break;
	case CPC::DISCONNECTSTEP_ARRANGE:
		this->CCharacterMgr::OnDisconnect_STEP_ARRANGE(pc);
		break;
	case CPC::DISCONNECTSTEP_ASYNCDB_SAVE_REQUEST:
		this->CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_REQUEST(pc);
		break;
	case CPC::DISCONNECTSTEP_ASYNCDB_SAVE_WAIT:
		return;
	case CPC::DISCONNECTSTEP_ASYNCDB_SAVE_COMPLETE:
		this->CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_COMPLETE(pc);
		break;
	case CPC::DISCONNECTSTEP_COMPLETE:
		this->CCharacterMgr::OnDisconnect_STEP_COMPLETE(pc);
		break;
	case CPC::DISCONNECTSTEP_REMOVE:
		this->CCharacterMgr::OnDisconnect_STEP_REMOVE(pc);
		break;
	default:
		MessageBoxA(0, "unknow disconnect type found", "critical", 0);
		break;
	}
}


hook_method<void (CCharacterMgr::*)(CPC* pc)> CCharacterMgr::_OnDisconnect_STEP_NONE(SERVER, "CCharacterMgr::OnDisconnect_STEP_NONE");
void CCharacterMgr::OnDisconnect_STEP_NONE(CPC* pc) // line 288-300
{
	return (this->*_OnDisconnect_STEP_NONE)(pc);

	pc->CPC::SetDisconnectStep(CPC::DISCONNECTSTEP_ARRANGE);
	if( pc->m_isValid != 1 )
		pc->CPC::SetDisconnectStep(CPC::DISCONNECTSTEP_REMOVE);
}


hook_method<void (CCharacterMgr::*)(CPC* pc)> CCharacterMgr::_OnDisconnect_STEP_REMOVE(SERVER, "CCharacterMgr::OnDisconnect_STEP_REMOVE");
void CCharacterMgr::OnDisconnect_STEP_REMOVE(CPC* pc) // line 306-310
{
	return (this->*_OnDisconnect_STEP_REMOVE)(pc);

	pc->CClient::Close();
	pc->CPC::SetMapLoadingFlag(0);
	this->CCharacterMgr::RemoveCharacter(pc);
}


hook_method<void (CCharacterMgr::*)(CPC* pc)> CCharacterMgr::_OnDisconnect_STEP_ARRANGE(SERVER, "CCharacterMgr::OnDisconnect_STEP_ARRANGE");
void CCharacterMgr::OnDisconnect_STEP_ARRANGE(CPC* pc) // line 315-391
{
	return (this->*_OnDisconnect_STEP_ARRANGE)(pc);

	//TODO
}


hook_method<void (CCharacterMgr::*)(CPC* const pc)> CCharacterMgr::_OnDisconnect_STEP_ASYNCDB_SAVE_REQUEST(SERVER, "CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_REQUEST");
void CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_REQUEST(CPC* const pc) // line 492-603
{
	return (this->*_OnDisconnect_STEP_ASYNCDB_SAVE_REQUEST)(pc);

	//TODO
}


hook_method<void (CCharacterMgr::*)(CPC* pc)> CCharacterMgr::_OnDisconnect_STEP_COMPLETE(SERVER, "CCharacterMgr::OnDisconnect_STEP_COMPLETE");
void CCharacterMgr::OnDisconnect_STEP_COMPLETE(CPC* pc) // line 397-487
{
	return (this->*_OnDisconnect_STEP_COMPLETE)(pc);

	//TODO
}


hook_method<void (CCharacterMgr::*)(CPC* pc)> CCharacterMgr::_OnDisconnect_STEP_ASYNCDB_SAVE_COMPLETE(SERVER, "CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_COMPLETE");
void CCharacterMgr::OnDisconnect_STEP_ASYNCDB_SAVE_COMPLETE(CPC* pc) // line 608-660
{
	return (this->*_OnDisconnect_STEP_ASYNCDB_SAVE_COMPLETE)(pc);

	//TODO
}


//hook_method<int (CCharacterMgr::*)(CPC* pc)> CCharacterMgr::_IsSendable(SERVER, "CCharacterMgr::IsSendable");
int CCharacterMgr::IsSendable(CPC* pc) // line ???
{
//	return (this->*_IsSendable)(pc);

	return pc->m_pcClientUpdater.CPCClientUpdater::IsSendable();
}
