#pragma once
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3MessageQueue.h"


namespace InstantMap
{
void SendPacket_IZ_INSTANTMAP_ADD3(const int in_TargetZSID, const int in_ZSID, const int in_MapID, const int in_MapType, std::string in_Name, const bool in_bPlayerEnter);
void SendPacket_IZ_INSTANTMAP_CREATE_REQ(const int in_TargetZSID, const unsigned int in_hRequestN2Obj, std::string in_MapName, const int in_MapID, const int in_MapType);
void SendPacket_IZ_INSTNATMAP_DESTROY_temp(const int in_TargetZSID, const int in_MapID, std::string in_Name);
void BroadCastPacket_IZ_INSTANTMAP_ADD3(const int in_ZSID, const int in_MapID, const int in_MapType, std::string in_Name, const bool in_bPlayerEnter);
void BroadCastPacket_IZ_INSTANTMAP_PLAYER_ENTER3(const int in_MapID, const bool in_bPlayerEnter);
void BroadCastPacket_IZ_INSTANTMAP_REMOVE3(const int in_ZSID, const int in_MapID, std::string in_Name);
};


class CInstantMap : public N3Object, public N3Inter
{
public:
	enum
	{
		MSG_NONE2                       = 0,
		MSG_CREATE_ERROR2               = 1,
		MSG_CREATE_SUCCESS2             = 2,
		MSG_TARGETZSVR_CREATE_REQUEST2  = 3,
		MSG_TARGETZSVR_CREATE_RESPONSE2 = 4,
		MSG_ERROR_FOUND_FROMZSVR2       = 5,
		MSG_ERROR_FOUND2                = 6,
		MSG_DYING_WISH_REQUEST2         = 7,
	};

public:
	class InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE
	{
	public:
		InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE(const std::string in_mapName, const int in_mapID, const bool in_bSuccess) : m_mapName(in_mapName), m_mapID(in_mapID), m_bSuccess(in_bSuccess) { }
		~InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE() { }

	public:
		/* this+ 0 */ std::string m_mapName;
		/* this+28 */ int m_mapID;
		/* this+32 */ bool m_bSuccess;
	};

private:
	/* this+  0 */ //N3Object baseclass_0;
	/* this+  8 */ //N3Inter baseclass_8;
	/* this+ 12 */ bool m_bOK;
	/* this+ 16 */ const int m_ZSID;
	/* this+ 20 */ const int m_MapType;
	/* this+ 24 */ std::string m_Name;
	/* this+ 52 */ int m_MapID;
	/* this+ 56 */ const unsigned int m_RequestCreateInter;
	/* this+ 60 */ unsigned long m_ZSVRregisteredFUCnt;
	/* this+ 64 */ N3MessageQueue m_MessageQueue;

	enum enumSTATE
	{
		STATE_CREATE        = 0,
		STATE_ERROR         = 1,
		STATE_OPERATION     = 2,
		STATE_DESTROY_WAIT  = 3,
		STATE_DESTORY_READY = 4,
	};

	/* this+132 */ enumSTATE m_State;

	enum enumSCHEDULE
	{
		SCHEDULE_DESTORY                     = 0,
		SCHEDULE_CREATERES_WAITTIME_fromZSVR = 1,
	};

	typedef std::multimap<unsigned long,enumSCHEDULE> SCHEDULE_CONTAINER;
	typedef std::multimap<unsigned long,enumSCHEDULE>::iterator SCHEDULE_CONTAINER_ITER;
	/* this+136 */ SCHEDULE_CONTAINER m_ScheduleContainer;

	void Schedule_Add(const unsigned long in_Date, const enumSCHEDULE in_Job);
	void Schedule_Remove(const enumSCHEDULE in_Job);
	void Schedule_Process();

	/* this+168 */ void (CInstantMap::* m_ProcessFuncPtr)(const int in_Message, const int in_wParam, const int in_lParam);
	void Process_PROCSTEP_TARGETZSVR_CREATE(const int in_Message, const int in_wParam, const int in_lParam);
	void Process_PROCSTEP_OPERATION(const int in_Message, const int in_wParam, const int in_lParam);

public:
	const bool isOK() const { return m_bOK; }
	void Process();
	const unsigned int GetReqeustCreateInter() const { return m_RequestCreateInter; }
	const bool IsDestoryReady() const { return ( m_State == STATE_DESTORY_READY ); }
	const bool IsOperation() const { return ( m_State == STATE_OPERATION ); }
	const unsigned long GetZSVRregisteredFUCnt() const { return m_ZSVRregisteredFUCnt; }
	const std::string GetMapName() const { return m_Name; }
	const int GetMapID() const { return m_MapID; }
	const int GetMapType() const { return m_MapType; }
	const int GetZSID() const { return m_ZSID; }

public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

public:
	CInstantMap(const unsigned int in_RequestCreateInter, const int in_ZSID, const std::string in_Name, const int in_mapType);
	virtual ~CInstantMap();
};
