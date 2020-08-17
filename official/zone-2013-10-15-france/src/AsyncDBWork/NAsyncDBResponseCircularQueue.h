#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"
#include "AsyncDBWork/NCircularQueue.h"


class NAsyncDBResponseCircularQueue : public templateNCircularQueue<NAsyncDBWork*>
{
private:
	/* this+ 0 */ //templateNCircularQueue<NAsyncDBWork*> baseclass_0;
	/* this+32 */ bool m_bOK;
	/* this+36 */ RTL_CRITICAL_SECTION m_CS;

public:
	const bool isOK() const;
	virtual bool isFull();
	virtual bool isEmpty();
	virtual bool Write(NAsyncDBWork* const in_pAsyncDBWork);
	virtual bool Read(NAsyncDBWork*& out_Data);
	virtual bool View(NAsyncDBWork*& out_Data);
	virtual void Clear();
	virtual unsigned int GetLastWriteTime();
	virtual int GetNum();
	virtual int GetMaxNum();

public:
	NAsyncDBResponseCircularQueue(const std::string in_strName, const int in_MaxEleNum);
	virtual ~NAsyncDBResponseCircularQueue();
};
