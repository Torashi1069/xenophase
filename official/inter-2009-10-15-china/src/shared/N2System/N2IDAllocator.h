#pragma once
#include "N2System/N2IDGenerator.h"
#include "std/map"


class N2IDAllocator
{
	/* this+0x0  */ void* vtable;
	/* static    */ private: static hook_ptr<N2IDAllocator*> m_cpSelf;
	/* this+0x4  */ private: RTL_CRITICAL_SECTION m_CS;
	/* this+0x1C */ private: bool m_bOK;
	/* this+0x20 */ private: mystd::map<unsigned short,N2IDGenerator*> m_GroupContainer;

	typedef mystd::map<unsigned short,N2IDGenerator*>::const_iterator GROUPCONTAINERITOR;

	//private: bool N2IDAllocator::Create();
	//private: void N2IDAllocator::Destroy();
	//public: bool N2IDAllocator::isOK();
	//public: bool N2IDAllocator::RegisterGroup(const unsigned short, const unsigned short, const unsigned short);
	public: unsigned int N2IDAllocator::Alloc(const unsigned short in_GroupID);
	//public: static unsigned short N2IDAllocator::GetGroupID(const unsigned int);
	public: void N2IDAllocator::Free(const unsigned int in_ID);
	//public: static bool N2IDAllocator::CreateInstance();
	//public: static void N2IDAllocator::DestoryInstance();
	public: static N2IDAllocator* N2IDAllocator::GetObj(void);
	//protected: N2IDAllocator::N2IDAllocator(void);
	//protected: N2IDAllocator::~N2IDAllocator(void);

private:
	static hook_method<unsigned int (N2IDAllocator::*)(const unsigned short in_GroupID)> N2IDAllocator::_Alloc;
	static hook_method<void (N2IDAllocator::*)(const unsigned int in_ID)> N2IDAllocator::_Free;
};
