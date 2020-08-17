#include "Character.h"
#include "CharacterMgr.h"
#include "Item.h"
#include "NPC.h"
#include "NpcEvt.h"
#include "PC.h"
#include "Skill.h"
#include "Client/CharacterServerClient/C2CharacterServerClient.h"
#include "Client/InterServerClient/C2InterServerClient.h"


/// singleton instance
CCharacterMgr*& CCharacterMgr::m_cpSelf = VTOR<CCharacterMgr*>(DetourFindFunction(EXEPATH(), "CCharacterMgr::m_cpSelf"));


CCharacterMgr* CCharacterMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


int CCharacterMgr::GetMonsterCount() // ??? (105.h)
{
	return m_npcMap.size();
}


CPC* CCharacterMgr::FindCharacter(const char* characterName) // 1242-1249
{
	for( int i = 0; i < m_PCCount; ++i )
	{
		CPC* pc = m_PC[i];

		if( pc != NULL && strncmp(pc->CPC::GetCharacterName(), characterName, 24) == 0 )
			return pc; // found.
	}

	return NULL; // not found.
}


CCharacter* CCharacterMgr::FindCharacter(unsigned long AID, unsigned long Type) // 1252-1274
{
	switch( Type )
	{
	case SKILL_TYPE: return this->CCharacterMgr::SearchSkill(AID);
	case NPC_TYPE:   return this->CCharacterMgr::FindNPCByAID(AID);
	case ITEM_TYPE:  return this->CCharacterMgr::SearchItem(AID);
	case PC_TYPE:    return this->CCharacterMgr::SearchPCFromIndexInfo(AID);
	default:
	{
		CCharacter* ch;
		if     ( (ch = this->CCharacterMgr::SearchSkill(AID))           != NULL ) return ch;
		else if( (ch = this->CCharacterMgr::FindNPCByAID(AID))          != NULL ) return ch;
		else if( (ch = this->CCharacterMgr::SearchItem(AID))            != NULL ) return ch;
		else if( (ch = this->CCharacterMgr::SearchPCFromIndexInfo(AID)) != NULL ) return ch;
		else return NULL;
	}
	};
}


CItem* CCharacterMgr::SearchItem(unsigned long ITAID) // 1283-1290
{
	return NULL;
	//TODO
}


CSkill* CCharacterMgr::SearchSkill(unsigned long AID) // 1293-1300
{
	return NULL;
	//TODO
}


CNPC* CCharacterMgr::FindNPCByAID(unsigned long AID) // 1633-1640
{
	return NULL;
	//TODO
}


int CCharacterMgr::SendMsg(CCharacter* sender, unsigned long receiverID, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // 2715-2721
{
	CCharacter* receiver = this->CCharacterMgr::FindCharacter(receiverID, UNKNOWN_TYPE);
	if( receiver == NULL )
		return 1;

	return receiver->OnMsg(sender, receiver, msgID, par1, par2, par3, par4);
}


int CCharacterMgr::SendMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // 2724-2730
{
	if( receiver == NULL )
		return 1;

	return receiver->OnMsg(sender, receiver, msgID, par1, par2, par3, par4);
}


void CCharacterMgr::SendToHServer(int len, const char* buf) // 2744-2750
{
	C2CharacterServerClient::GetObj()->C2CharacterServerClient::Send(len, buf);
}


void CCharacterMgr::SendToIServer(int len, const char* buf) // 2753-2755
{
	C2InterServerClient::GetObj()->C2InterServerClient::Send(len, buf);
}


CCharacter* CCharacterMgr::SearchPCFromIndexInfo(unsigned long AID) // 2796-2806
{
	return NULL;
	//TODO
}


void CCharacterMgr::SendMsgFromNPCServer(unsigned long senderAID, unsigned long receiverAID, CMsg* msg, unsigned long par1, unsigned long par2) // 2922-2927
{
	CNPC* npc = (CNPC*)this->CCharacterMgr::FindCharacter(receiverAID, NPC_TYPE);
	if( npc == NULL )
		return;

	CNpcEvt* evt = static_cast<CNpcEvt*>(npc);
	evt->CNpcEvt::OnMsgFromNPCServer(senderAID, receiverAID, msg, par1, par2);
}
