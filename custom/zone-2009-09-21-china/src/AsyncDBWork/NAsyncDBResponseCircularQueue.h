#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"
#include "AsyncDBWork/templateNCircularQueue.h"


class NAsyncDBResponseCircularQueue : public templateNCircularQueue<NAsyncDBWork *>
{
	struct vtable_t //const NAsyncDBResponseCircularQueue::`vftable'
	{
		bool (NAsyncDBResponseCircularQueue::* isFull)(void);
		bool (NAsyncDBResponseCircularQueue::* isEmpty)(void);
		bool (NAsyncDBResponseCircularQueue::* Write)(NAsyncDBWork* const);
		bool (NAsyncDBResponseCircularQueue::* Read)(NAsyncDBWork*&);
		bool (NAsyncDBResponseCircularQueue::* View)(NAsyncDBWork*&);
		void (NAsyncDBResponseCircularQueue::* Clear)(void);
		unsigned int (NAsyncDBResponseCircularQueue::* GetLastWriteTime)(void);
		int (NAsyncDBResponseCircularQueue::* GetNum)(void);
		int (NAsyncDBResponseCircularQueue::* GetMaxNum)(void);
		void* (NAsyncDBResponseCircularQueue::* vector_deleting_destructor)(unsigned int);
	};

	/* this+0x0  */ //templateNCircularQueue<NAsyncDBWork*>
	/* this+0x20 */ private: bool m_bOK;
	/* this+0x24 */ private: RTL_CRITICAL_SECTION m_CS;

	public: const bool NAsyncDBResponseCircularQueue::isOK(void) const;
	//public: bool NAsyncDBResponseCircularQueue::isFull();
	//public: bool NAsyncDBResponseCircularQueue::isEmpty();
	//public: bool NAsyncDBResponseCircularQueue::Write(NAsyncDBWork* const);
	//public: bool NAsyncDBResponseCircularQueue::Read(NAsyncDBWork*&);
	//public: bool NAsyncDBResponseCircularQueue::View(NAsyncDBWork*&);
	//public: void NAsyncDBResponseCircularQueue::Clear();
	//public: unsigned int NAsyncDBResponseCircularQueue::GetLastWriteTime();
	//public: int NAsyncDBResponseCircularQueue::GetNum();
	//public: int NAsyncDBResponseCircularQueue::GetMaxNum();
	public: NAsyncDBResponseCircularQueue::NAsyncDBResponseCircularQueue(const mystd::string in_strName, const int in_MaxEleNum);
	public: virtual NAsyncDBResponseCircularQueue::~NAsyncDBResponseCircularQueue(void);

private:
	static hook_method<const bool (NAsyncDBResponseCircularQueue::*)(void) const> NAsyncDBResponseCircularQueue::_isOK;
};
