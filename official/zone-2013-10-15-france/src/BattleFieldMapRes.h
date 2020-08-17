#pragma once
#include "MapRes.h"
class CNPC;


struct BATTLEFIELD_MAPINFO
{
	/* this+ 0 */ short aX2;
	/* this+ 2 */ short aY2;
	/* this+ 4 */ short bX2;
	/* this+ 6 */ short bY2;
	/* this+ 8 */ bool isPointNotify;
	/* this+ 9 */ bool isPKPoint;
	/* this+10 */ bool isAlivePCCheck;
	/* this+11 */ bool isNpcNotify;
};


struct BATTLEFIELD_STATEINFO
{
	/* this+0 */ int a_point;
	/* this+4 */ int b_point;
};


class CBattleFieldMapRes : public CMapRes
{
public:
	CBattleFieldMapRes(const int in_mapType);
//	virtual ~CBattleFieldMapRes();

public:
	virtual bool IsBattleField();
	void ClearState();
	void BroadcastToCamp(char campID, int len, char* buf);
	void SetBattleFieldMapInfo(char* key, char* value);
	void UpdateCampPoint(char campID, int value);
	int GetCampPoint(char campID);
	void UpdateRespawnPoint2ByNPC(char killerCampID);
	void MovePlayerToRespawnPoint(char campID, short RP_No, unsigned long npcID);
	void UpdateRespawnPoint2(char campID, short xPos, short yPos);
	void GetPacketBattleFieldPoint(int& len, char* buf, const int in_nMaxBufSize);
	bool IsPKPoint();
	bool IsAlivePCCheck();
	virtual BOOL AddCharacter(int xCellPos, int yCellPos, CCharacter* character);
	void InsertAliveMember(char campID, unsigned long accountID);
	void DeleteAliveMember(char campID, unsigned long accountID);
	void NotifyCampPoint();
	void RegisterNpc(CNPC* npc);
	void SendNpcServer();
	int GetAliveMemberCount(char campCode);
	void StartAliveCheck();
	void SetNpcNotify_Switch(const char* sw);
	bool SetBattleFieldMovePostion(const char campID, const int xPos, const int yPos);
	bool IsAliveCheck();

private:
	/* this+   0 */ //CMapRes baseclass_0;
	/* this+1860 */ BATTLEFIELD_MAPINFO m_mapInfo;
	/* this+1872 */ BATTLEFIELD_STATEINFO m_stateInfo;
	/* this+1880 */ std::list<unsigned long> m_a_aliveMemberList;
	/* this+1892 */ std::list<unsigned long> m_b_aliveMemberList;
	/* this+1904 */ CNPC* m_campNpc;
	/* this+1908 */ bool m_aliveCheck;
	/* this+1909 */ bool m_checkNpcNoti;
	/* this+1910 */ bool m_campCommand;
};
