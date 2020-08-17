#pragma once
#include "MapRes.h"
#include "struct.hpp"
#include "std/list"
class CNPC;


class CBattleFieldMapRes : public CMapRes
{
public:
	struct vtable_t
	{
		//TODO
	};

	/* this+0x0   */ //CMapRes
	/* this+0x71C */ BATTLEFIELD_MAPINFO m_mapInfo;
	/* this+0x728 */ BATTLEFIELD_STATEINFO m_stateInfo;
	/* this+0x730 */ mystd::list<unsigned long> m_a_aliveMemberList;
	/* this+0x73C */ mystd::list<unsigned long> m_b_aliveMemberList;
	/* this+0x748 */ CNPC* m_campNpc;
	/* this+0x74C */ bool m_aliveCheck;
	/* this+0x74D */ bool m_checkNpcNoti;
	/* this+0x74E */ bool m_campCommand;

	public: CBattleFieldMapRes::CBattleFieldMapRes(const int in_mapType);
	public: CBattleFieldMapRes::~CBattleFieldMapRes(void);
	public: bool CBattleFieldMapRes::IsBattleField(void);
	public: void CBattleFieldMapRes::ClearState(void);
	public: void CBattleFieldMapRes::BroadcastToCamp(char campID, int len, char* buf);
	public: void CBattleFieldMapRes::SetBattleFieldMapInfo(char* key, char* value);
	public: void CBattleFieldMapRes::UpdateCampPoint(char campID, int value);
	public: int CBattleFieldMapRes::GetCampPoint(char campID);
	public: void CBattleFieldMapRes::UpdateRespawnPoint2ByNPC(char killerCampID);
	public: void CBattleFieldMapRes::MovePlayerToRespawnPoint(char campID, short RP_No, unsigned long npcID);
	public: void CBattleFieldMapRes::UpdateRespawnPoint2(char campID, short xPos, short yPos);
	//public: void CBattleFieldMapRes::GetPacketBattleFieldPoint(int& len, char* buf);
	public: bool CBattleFieldMapRes::IsPKPoint(void);
	public: bool CBattleFieldMapRes::IsAlivePCCheck(void);
	public: int CBattleFieldMapRes::AddCharacter(int xCellPos, int yCellPos, CCharacter* character);
	public: void CBattleFieldMapRes::InsertAliveMember(char campID, unsigned long accountID);
	public: void CBattleFieldMapRes::DeleteAliveMember(char campID, unsigned long accountID);
	public: void CBattleFieldMapRes::NotifyCampPoint(void);
	public: void CBattleFieldMapRes::RegisterNpc(CNPC* npc);
	public: void CBattleFieldMapRes::SendNpcServer(void);
	public: int CBattleFieldMapRes::GetAliveMemberCount(char campCode);
	public: void CBattleFieldMapRes::StartAliveCheck(void);
	public: void CBattleFieldMapRes::SetNpcNotify_Switch(const char* sw);

private:
	static hook_method<bool (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_IsBattleField;
	static hook_method<void (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_ClearState;
	static hook_method<void (CBattleFieldMapRes::*)(char campID, int len, char* buf)> CBattleFieldMapRes::_BroadcastToCamp;
	static hook_method<void (CBattleFieldMapRes::*)(char* key, char* value)> CBattleFieldMapRes::_SetBattleFieldMapInfo;
	static hook_method<void (CBattleFieldMapRes::*)(char campID, int value)> CBattleFieldMapRes::_UpdateCampPoint;
	static hook_method<int (CBattleFieldMapRes::*)(char campID)> CBattleFieldMapRes::_GetCampPoint;
	static hook_method<void (CBattleFieldMapRes::*)(char killerCampID)> CBattleFieldMapRes::_UpdateRespawnPoint2ByNPC;
	static hook_method<void (CBattleFieldMapRes::*)(char campID, short RP_No, unsigned long npcID)> CBattleFieldMapRes::_MovePlayerToRespawnPoint;
	static hook_method<void (CBattleFieldMapRes::*)(char campID, short xPos, short yPos)> CBattleFieldMapRes::_UpdateRespawnPoint2;
	static hook_method<bool (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_IsPKPoint;
	static hook_method<bool (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_IsAlivePCCheck;
	static hook_method<int (CBattleFieldMapRes::*)(int xCellPos, int yCellPos, CCharacter* character)> CBattleFieldMapRes::_AddCharacter;
	static hook_method<void (CBattleFieldMapRes::*)(char campID, unsigned long accountID)> CBattleFieldMapRes::_InsertAliveMember;
	static hook_method<void (CBattleFieldMapRes::*)(char campID, unsigned long accountID)> CBattleFieldMapRes::_DeleteAliveMember;
	static hook_method<void (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_NotifyCampPoint;
	static hook_method<void (CBattleFieldMapRes::*)(CNPC* npc)> CBattleFieldMapRes::_RegisterNpc;
	static hook_method<void (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_SendNpcServer;
	static hook_method<int (CBattleFieldMapRes::*)(char campCode)> CBattleFieldMapRes::_GetAliveMemberCount;
	static hook_method<void (CBattleFieldMapRes::*)(void)> CBattleFieldMapRes::_StartAliveCheck;
	static hook_method<void (CBattleFieldMapRes::*)(const char* sw)> CBattleFieldMapRes::_SetNpcNotify_Switch;
};
