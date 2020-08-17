#include "Character.h"
#include "CharacterMgr.h"
#include "NPC.h"
#include "NPCUpdater.h"


CNPCUpdater::CNPCUpdater() // 51-52
{
}


CNPCUpdater::~CNPCUpdater() // 55-56
{
}


BOOL CNPCUpdater::SetAccountID(int AccountID) // 64-77
{
	if( AccountID == 0 )
	{
		AccountID = CCharacterMgr::GetObj()->CCharacterMgr::GetAID();
		if( AccountID == 0 )
			return FALSE;

		m_npc->m_characterInfo.IsRegen = 0;
	}

	m_npc->m_characterInfo.accountID = AccountID;
	return TRUE;
}


hook_func<void (__stdcall *)()> CNPCUpdater__CheckMove(EXEPATH(), "CNPCUpdater::CheckMove");
void CNPCUpdater::CheckMove() // 90-163
{
	void* hookptr = CNPCUpdater__CheckMove;
	__asm push this
	__asm call hookptr
	return; //TODO
}


void CNPCUpdater::SetValidate(BOOL isActive) // 959-961
{
	m_npc->m_characterInfo.isValid = isActive;
}


BOOL CNPCUpdater::IsMyArea(CCharacter* other, int Range) // 964-976 (417-429)
{
	int x, y, mapID;
	other->GetParameterValue(VAR_CURXPOS, x);
	other->GetParameterValue(VAR_CURYPOS, y);
	other->GetParameterValue(VAR_MAPID, mapID);

	return ( abs(m_npc->m_pathInfo.m_moveInfo.xPos - x) <= Range
	      && abs(m_npc->m_pathInfo.m_moveInfo.yPos - y) <= Range
	      && m_npc->m_characterInfo.mapID == mapID );
}


BOOL CNPCUpdater::IsMyArea(CCharacter* other, int xRange, int yRange) // 980-993 (433-446)
{
	int x, y, mapID;
	other->GetParameterValue(VAR_CURXPOS, x);
	other->GetParameterValue(VAR_CURYPOS, y);
	other->GetParameterValue(VAR_MAPID, mapID);

	return ( abs(m_npc->m_pathInfo.m_moveInfo.xPos - x) <= xRange
	      && abs(m_npc->m_pathInfo.m_moveInfo.yPos - y) <= yRange
	      && m_npc->m_characterInfo.mapID == mapID );
}


BOOL CNPCUpdater::AddSectionMgr() // 1124-1126
{
	return m_npc->m_mapRes->AddCharacter(m_npc->m_pathInfo.m_moveInfo.xPos, m_npc->m_pathInfo.m_moveInfo.yPos, m_npc);
}


hook_func<void (__stdcall *)()> CNPCUpdater__CheckState(EXEPATH(), "CNPCUpdater::CheckState");
void CNPCUpdater::CheckState() // 1662-1853
{
	void* hookptr = CNPCUpdater__CheckState;
	__asm mov eax, this
	__asm call hookptr
	return; //TODO
}


hook_func<void (__stdcall *)()> CNPCUpdater__GetPickableSortList(EXEPATH(), "CNPCUpdater::GetPickableSortList");
void CNPCUpdater::GetPickableSortList(SORTED_PCLIST* sortList) // 2259-2309
{
	void* hookptr = CNPCUpdater__GetPickableSortList;
	__asm push sortList
	__asm push this
	__asm call hookptr
	return; //TODO
}


BOOL CNPCUpdater::InitPosition(int xPos, int yPos, unsigned char dir) // 2326-2329
{
	m_npc->m_pathInfo.CHostPathInfo::InitPosition(xPos, yPos, dir);
	return this->CNPCUpdater::AddSectionMgr();
}
