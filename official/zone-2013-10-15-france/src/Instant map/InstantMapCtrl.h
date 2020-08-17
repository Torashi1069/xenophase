#pragma once
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3MessageQueue.h"
#include "shared/N3System/N3Inter.h"
class CInstantMapRes;
class CIMWTWork;


class CInstantMapCtrl : public N3Object, public N3Inter
{
public:
	enum
	{
		MSG_NONE2                      = 0,
		MSG_REQUEST_MAPLOADING2        = 1,
		MSG_REQUEST_DESTROY2           = 2,
		MSG_DESTORY_SKILL              = 3,
		MSG_DESTROY_ITEM               = 4,
		MSG_DESTROY_NPCEVENT           = 5,
		MSG_DESTROY_NPC                = 6,
		MSG_DESTROY_MAPRES             = 7,
		MSG_REGISTERED_MAPRES          = 8,
		MSG_SCRIPT_FIRSTEVENT_COMPLETE = 9,
	};

private:
	/* this+  0 */ //N3Object baseclass_0;
	/* this+  8 */ //N3Inter baseclass_8;
	/* this+ 12 */ const int m_hInstantMapID;
	/* this+ 16 */ const std::string m_MapName;
	/* this+ 44 */ const int m_MapType;
	/* this+ 48 */ const unsigned int m_hRequestN2Obj;
	/* this+ 52 */ CInstantMapRes* m_cpInstantMapRes;
	/* this+ 56 */ N3MessageQueue m_MessageQueue;
	/* this+116 */ bool m_bOK;
	/* this+120 */ DWORD m_ScriptFirstEventRequestTM;
	enum enumSTATE {
		STATE_CREATE        = 0,
		STATE_ERROR         = 1,
		STATE_OPERATION     = 2,
		STATE_DESTROY_READY = 3,
	};
	/* this+124 */ enumSTATE m_State;
	/* this+128 */ void (CInstantMapCtrl::* m_ProcessFuncPtr)(const int in_Message, const int in_wParam, const int in_lParam);

private:
	void ProcCreate(const int in_Message, const int in_wParam, const int in_lParam);
	void ProcCreate_MSG_REQUEST_MAPLOADING();
	void ProcCreate_WorkerThread_MSG_RESPONSE_WORK(const CIMWTWork* in_cpWork);
	void ProcDestroy(const int in_Message, const int in_wParam, const int in_lParam);
	void ProcOperation(const int in_Message, const int in_wParam, const int in_lParam);

public:
	const bool isOK() const;
	void Process();
	const std::string GetMapName() const;
	const int GetMapID() const;
	const unsigned int GetRequestN2Obj() const;
	CInstantMapRes* GetMapResPtr();
	const bool IsDestroyReady();

public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

public:
	CInstantMapCtrl(const unsigned int in_hRequestN2Obj, const int in_hInstantMapID, const std::string in_MapName, const int in_MapType);
	virtual ~CInstantMapCtrl();
};
