#pragma once
#include "Common/CriticalSection.h"
class CStream;


class CProcess
{
public:
	CProcess();
	virtual ~CProcess();
	void SetStream(CStream* pStream);
	bool Init(DWORD dwStreamSessionID, DWORD dwIP);
	void OnStreamClose();
	bool CloseOuter(DWORD dwSessionID, DWORD dwTime);
	virtual void Send(char* buf, int len, DWORD dwSessionID, bool bBroadcast);
	DWORD GetSessionID();
	DWORD GetIP();
	virtual bool OnConnect() = 0;
	virtual void OnClose() = 0;
	virtual bool Process() = 0;

protected:
	void Close(DWORD dwTime);

protected:
	/* this+ 0 */ //const CProcess::`vftable';
	/* this+ 4 */ CCriticalSection m_cs;
	/* this+28 */ DWORD m_dwIP;
	/* this+32 */ DWORD m_dwSessionID;
	/* this+36 */ CStream* m_pStream;
};


template<typename T> bool CreateProcessList(std::list<CProcess*>* pList, int ObjNum)
{
	for( int i = 0; i < ObjNum; ++i )
	{
		CProcess* p = new T();
		if( p == NULL )
		{
			CSingleton<CReporter>::getSingletonPtr()->CReporter::Log("CreateProcessList %s error\n", typeid(T).name()); //NOTE: RTTI
			return false;
		}

		pList->push_back(p);
	}

	return true;
}


void DestroyProcessList(std::list<CProcess*>& rList);
