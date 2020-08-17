#pragma once
#include "AsyncDBWork/NInter.h"
#include "std/map"


class NInterMessageSystem
{
	/* this+0x0  */ //const NInterMessageSystem::`vftable'
	/* static    */ private: static hook_ptr<NInterMessageSystem*> m_cpSelf;
	/* this+0x4  */ private: RTL_CRITICAL_SECTION m_CS;
	/* this+0x1C */ private: bool m_bOK;
	/* this+0x20 */ private: mystd::map<unsigned int,NInter*> m_InterObjContainer;

	typedef mystd::map<unsigned int,NInter*>::const_iterator IOBJCONTAINERITOR;

	//public: bool NInterMessageSystem::isOK();
	public: bool NInterMessageSystem::Insert(const unsigned int in_hID, NInter* in_cpInter);
	public: void NInterMessageSystem::Remove(const unsigned int in_hID, NInter* in_cpInter);
	//public: bool NInterMessageSystem::PostInterMessage(const unsigned int, const unsigned int, const unsigned long, const int, const int, const int);
	public: static NInterMessageSystem* __cdecl NInterMessageSystem::GetObj(void);
	//public: static bool NInterMessageSystem::CreateInstance();
	//public: static void NInterMessageSystem::DestoryInstance();
	protected: NInterMessageSystem::NInterMessageSystem(void);
	protected: virtual NInterMessageSystem::~NInterMessageSystem(void);

private:
	static hook_method<bool (NInterMessageSystem::*)(const unsigned int in_hID, NInter* in_cpInter)> NInterMessageSystem::_Insert;
	static hook_method<void (NInterMessageSystem::*)(const unsigned int in_hID, NInter* in_cpInter)> NInterMessageSystem::_Remove;
	static hook_method<static NInterMessageSystem* (__cdecl *)(void)> NInterMessageSystem::_GetObj;
};
