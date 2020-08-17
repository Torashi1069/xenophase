#pragma once
#include "N2System/N2Object.h"
#include "N2System/N2Inter.h"
#include "N2System/N2InterMessageQueue.h"
#include "std/map"
#include "std/string"


class CInstantMap : public N2Object, public N2Inter
{
	struct vtable_N2Object_t //const CInstantMap::`vftable'{for `N2Object'}
	{
		void* (CInstantMap::* scalar_deleting_destructor)(unsigned int);
	};

	struct vtable_N2Inter_t // const CInstantMap::`vftable'{for `N2Inter'}
	{
		void (CInstantMap::* PostInterMessage)(const unsigned int, const int, const int, const int);
		bool (CInstantMap::* PeekInterMessage)(unsigned int&, int&, int&, int&, const bool);
		void* (CInstantMap::* vector_deleting_destructor)(unsigned int);
	};

	/* this+0x0  */ //N2Object
	/* this+0x8  */ //N2Inter
	/* this+0xC  */ private: bool m_bOK;
	/* this+0x10 */ private: N2InterMessageQueue m_MessageQueue;
	/* this+0x38 */ private: const int m_ZSID;
	/* this+0x3C */ private: mystd::string m_Name;
	/* this+0x58 */ private: int m_MapID;
	/* this+0x5C */ private: const int m_MapType;
	/* this+0x60 */ private: const unsigned int m_RequestCreateInter;
	/* this+0x64 */ private: unsigned long m_ZSVRregisteredFUCnt;
	/* this+0x68 */ private: enum enumSTATE m_State;
	/* this+0x6C */ private: mystd::multimap<unsigned long,enum enumSCHEDULE> m_ScheduleContainer;
	/* this+0x78 */ private: void (CInstantMap::* m_ProcessFuncPtr)(const int, const int, const int, const unsigned int);

	enum
	{
		MSG_NONE2 = 0x0,
		MSG_CREATE_ERROR2 = 0x1,
		MSG_CREATE_SUCCESS2 = 0x2,
		MSG_TARGETZSVR_CREATE_REQUEST2 = 0x3,
		MSG_TARGETZSVR_CREATE_RESPONSE2 = 0x4,
		MSG_ERROR_FOUND_FROMZSVR2 = 0x5,
		MSG_ERROR_FOUND2 = 0x6,
		MSG_DYING_WISH_REQUEST2 = 0x7,
	};

	class InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE
	{
		/* this+0x0  */ public: mystd::string m_mapName;
		/* this+0x1C */ public: int m_mapID;
		/* this+0x20 */ public: bool m_bSuccess;

		//public: void CInstantMap::InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE::InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE(const mystd::string, const int, const bool);
		//public: void CInstantMap::InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE::~InstantMap_MSGwparam_TARGETZSVR_CREATE_RESPONSE();
	};

	enum enumSTATE
	{
		STATE_CREATE = 0x0,
		STATE_ERROR = 0x1,
		STATE_OPERATION = 0x2,
		STATE_DESTROY_WAIT = 0x3,
		STATE_DESTORY_READY = 0x4,
	};

	enum enumSCHEDULE
	{
		SCHEDULE_DESTORY = 0x0,
		SCHEDULE_CREATERES_WAITTIME_fromZSVR = 0x1,
	};

	//typedef mystd::multimap<unsigned long,enum CInstantMap::enumSCHEDULE>::const_iterator SCHEDULE_CONTAINER_ITER;

	//private: void CInstantMap::Schedule_Add(const unsigned long, const enum CInstantMap::enumSCHEDULE);
	//private: void CInstantMap::Schedule_Remove(const enum CInstantMap::enumSCHEDULE);
	//private: void CInstantMap::Schedule_Process();
	//private: void CInstantMap::Process_PROCSTEP_TARGETZSVR_CREATE(const int, const int, const int, const unsigned int);
	//private: void CInstantMap::Process_PROCSTEP_OPERATION(const int, const int, const int, const unsigned int);
	//public: const bool CInstantMap::isOK();
	//public: void CInstantMap::Process();
	//public: const unsigned int GetReqeustCreateInter();
	//public: const bool CInstantMap::IsDestoryReady();
	//public: const bool CInstantMap::IsOperation();
	//public: const unsigned long CInstantMap::GetZSVRregisteredFUCnt();
	//public: const mystd::string CInstantMap::GetMapName();
	//public: const int CInstantMap::GetMapID();
	//public: const int CInstantMap::GetMapType();
	//public: const int CInstantMap::GetZSID();
	//public: void CInstantMap::PostInterMessage(const unsigned int, const int, const int, const int);
	//public: bool CInstantMap::PeekInterMessage(unsigned int &, int &, int &, int &, const bool);
	//public: void CInstantMap::CInstantMap(const unsigned int, const int, const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >, const int);
	//public: void CInstantMap::~CInstantMap();
};
