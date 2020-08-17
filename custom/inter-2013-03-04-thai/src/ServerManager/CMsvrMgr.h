#pragma once
#include "MServerMgr.h"
#include "shared/N3System/N3Inter.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3MessageQueue.h"


class CMsvrMgr : public CMClientMgr, public N3Inter, public N3Object
{
public:
	enum { MSG_MSVR_ACCEPT = 0 };

public:
	bool isOK() const;
	void Process();
	int GetClientNumber() const;
	void DeleteServer(int SID);

private:
	void ProcessMSG();

public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CMsvrMgr* GetObj(); /// @custom

private:
	CMsvrMgr();
	virtual ~CMsvrMgr();
	CMsvrMgr(CMsvrMgr&); // = delete;
	CMsvrMgr& operator=(CMsvrMgr&); // = delete;

private:
	/* static   */ static CMsvrMgr*& m_cpSelf; //TODO
	/* this+  0 */ //CMClientMgr baseclass_0;
	/* this+104 */ //N3Inter baseclass_104;
	/* this+108 */ //N3Object baseclass_108;
	/* this+116 */ bool m_bOK;
	/* this+120 */ N3MessageQueue m_MessageQueue;
};
