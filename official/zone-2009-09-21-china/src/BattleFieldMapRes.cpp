#include "BattleFieldMapRes.h"


hook_method<void (CBattleFieldMapRes::*)(char campID, int len, char* buf)> CBattleFieldMapRes::_BroadcastToCamp(SERVER, "CBattleFieldMapRes::BroadcastToCamp");


CBattleFieldMapRes::CBattleFieldMapRes(const int in_mapType) : CMapRes(in_mapType)
{
	memset(&m_mapInfo, 0, sizeof(m_mapInfo));
	memset(&m_stateInfo, 0, sizeof(m_stateInfo));
	m_campNpc = NULL;
	m_aliveCheck = false;
	m_checkNpcNoti = false;
	m_campCommand = false;
}


CBattleFieldMapRes::~CBattleFieldMapRes(void)
{
}


//hook_method<bool (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_IsBattleField(SERVER, "CBattleFieldMapRes::IsBattleField");
bool CBattleFieldMapRes::IsBattleField(void)
{
//	return (this->*_IsBattleField)();

	return 1;
}


hook_method<void (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_ClearState(SERVER, "CBattleFieldMapRes::ClearState");
void CBattleFieldMapRes::ClearState(void)
{
	return (this->*_ClearState)();

	//TODO
}


void CBattleFieldMapRes::BroadcastToCamp(char campID, int len, char* buf)
{
	return (this->*_BroadcastToCamp)(campID, len, buf);

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(char* key, char* value)> CBattleFieldMapRes::_SetBattleFieldMapInfo(SERVER, "CBattleFieldMapRes::SetBattleFieldMapInfo");
void CBattleFieldMapRes::SetBattleFieldMapInfo(char* key, char* value)
{
	return (this->*_SetBattleFieldMapInfo)(key, value);

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(char campID, int value)> CBattleFieldMapRes::_UpdateCampPoint(SERVER, "CBattleFieldMapRes::UpdateCampPoint");
void CBattleFieldMapRes::UpdateCampPoint(char campID, int value)
{
	return (this->*_UpdateCampPoint)(campID, value);

	//TODO
}


hook_method<int (CBattleFieldMapRes::*)(char campID)> CBattleFieldMapRes::_GetCampPoint(SERVER, "CBattleFieldMapRes::GetCampPoint");
int CBattleFieldMapRes::GetCampPoint(char campID)
{
	return (this->*_GetCampPoint)(campID);

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(char killerCampID)> CBattleFieldMapRes::_UpdateRespawnPoint2ByNPC(SERVER, "CBattleFieldMapRes::UpdateRespawnPoint2ByNPC");
void CBattleFieldMapRes::UpdateRespawnPoint2ByNPC(char killerCampID)
{
	return (this->*_UpdateRespawnPoint2ByNPC)(killerCampID);

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(char campID, short RP_No, unsigned long npcID)> CBattleFieldMapRes::_MovePlayerToRespawnPoint(SERVER, "CBattleFieldMapRes::MovePlayerToRespawnPoint");
void CBattleFieldMapRes::MovePlayerToRespawnPoint(char campID, short RP_No, unsigned long npcID)
{
	return (this->*_MovePlayerToRespawnPoint)(campID, RP_No, npcID);

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(char campID, short xPos, short yPos)> CBattleFieldMapRes::_UpdateRespawnPoint2(SERVER, "CBattleFieldMapRes::UpdateRespawnPoint2");
void CBattleFieldMapRes::UpdateRespawnPoint2(char campID, short xPos, short yPos)
{
	return (this->*_UpdateRespawnPoint2)(campID, xPos, yPos);

	//TODO
}


//hook_method<bool (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_IsPKPoint(SERVER, "CBattleFieldMapRes::IsPKPoint");
bool CBattleFieldMapRes::IsPKPoint(void)
{
//	return (this->*_IsPKPoint)();

	return m_mapInfo.isPKPoint;
}


//hook_method<bool (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_IsAlivePCCheck(SERVER, "CBattleFieldMapRes::IsAlivePCCheck");
bool CBattleFieldMapRes::IsAlivePCCheck(void)
{
//	return (this->*_IsAlivePCCheck)();

	return m_mapInfo.isAlivePCCheck;
}


hook_method<int (CBattleFieldMapRes::*)(int xCellPos, int yCellPos, CCharacter* character)> CBattleFieldMapRes::_AddCharacter(SERVER, "CBattleFieldMapRes::AddCharacter");
int CBattleFieldMapRes::AddCharacter(int xCellPos, int yCellPos, CCharacter* character)
{
	return (this->*_AddCharacter)(xCellPos, yCellPos, character);

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(char campID, unsigned long accountID)> CBattleFieldMapRes::_InsertAliveMember(SERVER, "CBattleFieldMapRes::InsertAliveMember");
void CBattleFieldMapRes::InsertAliveMember(char campID, unsigned long accountID)
{
	return (this->*_InsertAliveMember)(campID, accountID);

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(char campID, unsigned long accountID)> CBattleFieldMapRes::_DeleteAliveMember(SERVER, "CBattleFieldMapRes::DeleteAliveMember");
void CBattleFieldMapRes::DeleteAliveMember(char campID, unsigned long accountID)
{
	return (this->*_DeleteAliveMember)(campID, accountID);

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_NotifyCampPoint(SERVER, "CBattleFieldMapRes::NotifyCampPoint");
void CBattleFieldMapRes::NotifyCampPoint(void)
{
	return (this->*_NotifyCampPoint)();

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(CNPC* npc)> CBattleFieldMapRes::_RegisterNpc(SERVER, "CBattleFieldMapRes::RegisterNpc");
void CBattleFieldMapRes::RegisterNpc(CNPC* npc)
{
	return (this->*_RegisterNpc)(npc);

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_SendNpcServer(SERVER, "CBattleFieldMapRes::SendNpcServer");
void CBattleFieldMapRes::SendNpcServer(void)
{
	return (this->*_SendNpcServer)();

	//TODO
}


hook_method<int (CBattleFieldMapRes::*)(char campCode)> CBattleFieldMapRes::_GetAliveMemberCount(SERVER, "CBattleFieldMapRes::GetAliveMemberCount");
int CBattleFieldMapRes::GetAliveMemberCount(char campCode)
{
	return (this->*_GetAliveMemberCount)(campCode);

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_StartAliveCheck(SERVER, "CBattleFieldMapRes::StartAliveCheck");
void CBattleFieldMapRes::StartAliveCheck(void)
{
	return (this->*_StartAliveCheck)();

	//TODO
}


hook_method<void (CBattleFieldMapRes::*)(const char* sw)> CBattleFieldMapRes::_SetNpcNotify_Switch(SERVER, "CBattleFieldMapRes::SetNpcNotify_Switch");
void CBattleFieldMapRes::SetNpcNotify_Switch(const char* sw)
{
	return (this->*_SetNpcNotify_Switch)(sw);

	//TODO
}
