#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"


class NAsyncDBRequestCircularQueue
{
public:
	enum enumRETURN
	{
		RETURN_ERROR                     = -1,
		RETURN_SUCCESS_NOT_DIRECTLYWORK  =  0,
		RETURN_SUCCESS_WITH_DIRECTLYWORK =  1,
	};

private:
	/* this+ 0 */ //const NAsyncDBRequestCircularQueue::`vftable';
	/* this+ 4 */ const int m_MaxEleNum;
	/* this+ 8 */ RTL_CRITICAL_SECTION m_CS;
	/* this+32 */ bool m_bOK;
	/* this+36 */ HANDLE m_hSemaphore;
	/* this+40 */ int m_DuplicateRefCnt;
	typedef std::list<NAsyncDBWork*> CONTAINER;
	typedef std::list<NAsyncDBWork*>::iterator CONTAINERITOR;
	/* this+44 */ CONTAINER m_Container;
	typedef std::vector<unsigned int> SERIALCHECKCONTAINER;
	typedef std::vector<unsigned int>::iterator SERIALCHECKCONTAINERITOR;
	/* this+56 */ SERIALCHECKCONTAINER m_SerialCheckContainer;

private:
	bool Create();
	void Destory();

public:
	const bool isOK() const;
	const bool Write3(NAsyncDBWork* const in_cpAsyncDBWork);
	NAsyncDBWork* Read3();
	const void Complete3(const NAsyncDBWork* in_cpAsyncDBWork);
	const HANDLE GetEventObj() const;
	const int GetSize();

public:
	NAsyncDBRequestCircularQueue(const int in_MaxEleNum);
	virtual ~NAsyncDBRequestCircularQueue();
};
