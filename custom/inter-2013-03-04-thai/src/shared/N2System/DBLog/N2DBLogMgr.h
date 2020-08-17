#pragma once
#include "shared/N2System/DBLog/N2DBLogRequestQueue.h"
class N2DBLogThread;


class N2DBLogMgr
{
private:
	/* static */ static N2DBLogMgr*& m_cpSelf; //TODO
	/* this+0 */ //const CGuildMgr::`vftable';
	/* this+4 */ bool m_bOK;
	typedef std::vector<N2DBLogThread*> THREADCONTAINER;
	typedef std::vector<N2DBLogThread*>::iterator THREADCONTAINER_ITER;
	/* this+ 8 */ THREADCONTAINER m_ThreadContainer;
	/* this+32 */ N2DBLogRequestQueue m_RequestQueue;

private:
	bool Create(const int in_WorkThreadNum, const std::string in_ConnectStr);
	void Destroy();

public:
	const bool isOK() const;
	bool Start();
	void Stop();
	bool Add(N2DBLog* const in_cpDBLog);

public:
	static bool CreateInstance(const int in_WorkThreadNum, const std::string in_ConnectStr);
	static void DestroyInstance();
	static N2DBLogMgr* GetObj(); /// @custom

private:
	N2DBLogMgr(const int in_WorkThreadNum, const std::string in_ConnectStr);
	virtual ~N2DBLogMgr();
};
