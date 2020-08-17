#pragma once
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3MessageQueue.h"


class CMemorialDungeon : public N3Object, public N3Inter
{
public:
	enum
	{
		MSG_NONE2               = 0,
		MSG_CREATE_ERROR2       = 1,
		MSG_ERROR2              = 2,
		MSG_DYING_WISH_REQUEST2 = 3,
		MSG_INSTANTMAP_CREATE2  = 4,
		MSG_INSTANTMAP_DESTROY2 = 5,
	};

private:
	struct tagInstantMapInfo
	{
		/* this+0 */ bool bCreateRequest;
		/* this+4 */ int mapType;

		tagInstantMapInfo(const int in_mapType) : bCreateRequest(false), mapType(in_mapType) { }
	};

	/* this+  0 */ //N3Object baseclass_0;
	/* this+  8 */ //N3Inter baseclass_8;
	typedef std::map<std::string,tagInstantMapInfo> INSTANTMAPLISTCONTAINER;
	typedef std::map<std::string,tagInstantMapInfo>::iterator INSTANTMAPLISTCONTAINER_ITER;
	/* this+ 12 */ INSTANTMAPLISTCONTAINER m_InstantMapList;
	/* this+ 44 */ bool m_bOK;
	/* this+ 48 */ N3MessageQueue m_MessageQueue;
	/* this+116 */ std::string m_Name;
	/* this+144 */ std::string m_NickName;
	/* this+172 */ int m_hParty;
	/* this+176 */ std::string m_PartyName;
	/* this+204 */ const int m_Factor;
	/* this+208 */ const int m_TargetZSID;
	/* this+212 */ unsigned long m_ZSVRregisteredFUCnt;
	/* this+216 */ std::string m_EnterInstantMapName;
	/* this+244 */ int m_EnterPosX;
	/* this+248 */ int m_EnterPosY;
	/* this+252 */ int m_LiveTimeMinute;
	/* this+256 */ const int m_HsvrID;

	enum enumSTATE
	{
		STATE_CREATE        = 0,
		STATE_OPERATION     = 1,
		STATE_ERROR         = 2,
		STATE_DESTROY_READY = 3,
	};
	/* this+260 */ enumSTATE m_State;

	class CPlayer
	{
	public:
		/* this+0 */ //const CMemorialDungeon::CPlayer::`vftable';
		/* this+4 */ unsigned long m_AID;
		/* this+8 */ unsigned long m_GID;

		CPlayer(const unsigned long in_AID, const unsigned long in_GID) : m_AID(in_AID), m_GID(in_GID) { }
		virtual ~CPlayer() { }
	};

	typedef std::map<unsigned long,CPlayer> PLAYERCONTAINER;
	typedef std::map<unsigned long,CPlayer>::iterator PLAYERCONTAINER_ITER;
	/* this+264 */ PLAYERCONTAINER m_PlayerContainer;

public:
	void OnEnter(const unsigned long in_GID, const unsigned long in_AID);
	void OnLeave(const unsigned long in_GID, const unsigned long in_AID);
	int GetHsvrID() { return m_HsvrID; }
	int GetZsvrID(); //TODO

private:
	enum enumSCHEDULE
	{
		SCHEDULE_DESTORY_LIVE_TIMEOUT  = 0,
		SCHEDULE_DESTORY_ENTER_TIMEOUT = 1,
	};

	typedef std::multimap<unsigned long,enumSCHEDULE> SCHEDULE_CONTAINER;
	typedef std::multimap<unsigned long,enumSCHEDULE>::iterator SCHEDULE_CONTAINER_ITER;
	/* this+296 */ SCHEDULE_CONTAINER m_ScheduleContainer;

	void Schedule_Add(const unsigned long in_Date, const enumSCHEDULE in_Job);
	unsigned long Schedule_GetDate(const enumSCHEDULE in_Job);
	void Schedule_Process();

	/* this+328 */ void (CMemorialDungeon::* m_ProcessFuncPtr)(const int in_Message, const int in_wParam, const int in_lParam);
	void Process_PROCSTEP_CREATE_INSTANTMAP(const int in_Message, const int in_wParam, const int in_lParam);
	void Process_PROCSTEP_DYING_WISH(const int in_Message, const int in_wParam, const int in_lParam);
	void Process_PROCSTEP_OPERATION(const int in_Message, const int in_wParam, const int in_lParam);

public:
	const bool isOK() const { return m_bOK; }
	void Process();
	const bool IsDestroyReady() const { return ( m_State == STATE_DESTROY_READY ); }
	const bool isActive() const { return ( m_State == STATE_OPERATION ); }
	const int GetTargetZSID() const { return m_TargetZSID; }
	const std::string GetName() const { return m_Name; }
	const unsigned long GetPartyID() const { return m_hParty; }
	const std::string GetPartyName() const { return m_PartyName; }
	const unsigned long GetLiveDate() { return this->CMemorialDungeon::Schedule_GetDate(SCHEDULE_DESTORY_LIVE_TIMEOUT); }
	const unsigned long GetEnterLimitDate() { return this->CMemorialDungeon::Schedule_GetDate(SCHEDULE_DESTORY_ENTER_TIMEOUT); }
	const unsigned long GetZSVRregisteredFUCnt() const { return m_ZSVRregisteredFUCnt; }
	const int GetFactor() const { return m_Factor; }
	void PartyLeave(const unsigned long in_AID, const unsigned long in_GID);
	const std::string GetEnterInstantMapName() const { return m_EnterInstantMapName; }
	const int GetEnterInstantMapX() const { return m_EnterPosX; }
	const int GetEnterInstantMapY() const { return m_EnterPosY; }
	const enumSTATE GetState() const { return m_State; }

public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

public:
	CMemorialDungeon(const std::string in_Name, const std::string in_NickName, const int in_hParty, const std::string in_PartyName, const int in_TargetZSID, const int in_HsvrID);
	virtual ~CMemorialDungeon();
	CMemorialDungeon(CMemorialDungeon&); // = delete;
	CMemorialDungeon& operator=(CMemorialDungeon&); // = delete;
};
