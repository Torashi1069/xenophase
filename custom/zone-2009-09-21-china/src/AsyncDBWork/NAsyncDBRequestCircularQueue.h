#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"
#include "std/list"
#include "std/vector"


class NAsyncDBRequestCircularQueue
{
	enum enumRETURN
	{
		RETURN_ERROR                     = -1,
		RETURN_SUCCESS_NOT_DIRECTLYWORK  =  0,
		RETURN_SUCCESS_WITH_DIRECTLYWORK =  1,
	};

	/* this+0x0  */ //const NAsyncDBRequestCircularQueue::`vftable'
	/* this+0x4  */ private: const int m_MaxEleNum;
	/* this+0x8  */ private: RTL_CRITICAL_SECTION m_CS;
	/* this+0x20 */ private: bool m_bOK;
	/* this+0x24 */ private: HANDLE m_hSemaphore;
	/* this+0x28 */ private: int m_DuplicateRefCnt;
	/* this+0x2C */ private: mystd::list<NAsyncDBWork*> m_Container;
	/* this+0x38 */ private: mystd::vector<unsigned int> m_SerialCheckContainer;

	typedef mystd::list<NAsyncDBWork*> CONTAINERITOR;

	private: bool NAsyncDBRequestCircularQueue::Create(void);
	private: void NAsyncDBRequestCircularQueue::Destroy(void);
	public: const bool NAsyncDBRequestCircularQueue::isOK(void) const;
	//public: const bool NAsyncDBRequestCircularQueue::Write3(NAsyncDBWork * const);
	//public: NAsyncDBWork* NAsyncDBRequestCircularQueue::Read3();
	//public: const void NAsyncDBRequestCircularQueue::Complete3(const NAsyncDBWork *);
	//public: void* const GetEventObj();
	//public: const int GetSize();
	public: NAsyncDBRequestCircularQueue::NAsyncDBRequestCircularQueue(const int in_MaxEleNum);
	public: virtual NAsyncDBRequestCircularQueue::~NAsyncDBRequestCircularQueue(void);

private:
	static hook_method<bool (NAsyncDBRequestCircularQueue::*)(void)> NAsyncDBRequestCircularQueue::_Create;
	static hook_method<void (NAsyncDBRequestCircularQueue::*)(void)> NAsyncDBRequestCircularQueue::_Destroy;
	static hook_method<const bool (NAsyncDBRequestCircularQueue::*)(void) const> NAsyncDBRequestCircularQueue::_isOK;
};
