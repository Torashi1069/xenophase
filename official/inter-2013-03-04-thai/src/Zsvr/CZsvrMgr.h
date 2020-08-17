#pragma once
#include "ZServerMgr.h"
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3MessageQueue.h"


class CZsvrMgr : public CZServerMgr, public N3Inter, public N3Object
{
public:
	enum { MSG_ZSVR_ACCEPT = 0, MSG_ZSVR_ALL_SEND_NPC_PROVIDE_EXPINFO = 1 };

public:
	bool isOK() const;
	void Process();
	void DeleteServer(int SID);

private:
	void ProcessMSG();

public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CZsvrMgr* GetObj(); /// @custom

private:
	CZsvrMgr();
	virtual ~CZsvrMgr();
	CZsvrMgr(CZsvrMgr&); // = delete;
	CZsvrMgr& operator=(CZsvrMgr&); // = delete;

private:
	/* static   */ static CZsvrMgr*& m_cpSelf; //TODO
	/* this+  0 */ //CZServerMgr baseclass_0;
	/* this+108 */ //N3Inter baseclass_108;
	/* this+112 */ //N3Object baseclass_112;
	/* this+120 */ bool m_bOK;
	/* this+124 */ N3MessageQueue m_MessageQueue;
};
