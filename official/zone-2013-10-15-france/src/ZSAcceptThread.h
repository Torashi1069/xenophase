#pragma once
class CZSAcceptHandler; // #include "ZSAcceptHandler.h"
#include "shared/N3System/N3Object.h"
#include "shared/N3System/N3Thread.h"


class CZSAcceptThread : public N3Thread, public N3Object
{
public:
	bool isOK() const;
	std::pair<bool,std::string> Start(const unsigned long in_IPaddr, const int in_Port, CZSAcceptHandler* in_cpAcceptHandler);
	void Stop();

private:
	virtual unsigned int ThreadFunction();
	virtual void PostThreadQuitMessage();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CZSAcceptThread* GetObj(); /// @custom

private:
	CZSAcceptThread();
	virtual ~CZSAcceptThread();
	CZSAcceptThread(const CZSAcceptThread&); // = delete;
	CZSAcceptThread& operator=(const CZSAcceptThread&); // = delete;

private:
	/* static  */ static CZSAcceptThread*& m_cpSelf; //TODO
	/* this+ 0 */ //N3Thread baseclass_0;
	/* this+48 */ //N3Object baseclass_48;
	/* this+56 */ bool m_bOK;
	/* this+60 */ CZSAcceptHandler* m_cpAcceptHandler;
	/* this+64 */ SOCKET m_listenSocket;
	/* this+68 */ bool m_ReqExit;
};
