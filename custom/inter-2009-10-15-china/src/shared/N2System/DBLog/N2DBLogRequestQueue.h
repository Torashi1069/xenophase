#pragma once
#include "N2DBLog.h"
#include "std/list"


class N2DBLogRequestQueue
{
	/* this+0x0  */ void* vtable;
	/* this+0x4  */ private: mystd::list<N2DBLog*> m_Container;
	/* this+0x10 */ private: bool m_bOK;
	/* this+0x14 */ private: HANDLE m_hSemaphore;
	/* this+0x18 */ private: RTL_CRITICAL_SECTION m_CS;

	typedef mystd::list<N2DBLog*>::const_iterator CONTAINER_ITER;

	//private: bool N2DBLogRequestQueue::Create();
	//private: void N2DBLogRequestQueue::Destroy();
	//private: class N2DBLog * N2DBLogRequestQueue::Get();
	//private: void* & N2DBLogRequestQueue::GetEventObject();
	//public: bool isOK();
	//public: bool N2DBLogRequestQueue::Add(class N2DBLog * const);
	//private: void N2DBLogRequestQueue::N2DBLogRequestQueue();
	//private: void N2DBLogRequestQueue::~N2DBLogRequestQueue();
};
