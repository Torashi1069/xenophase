#pragma once
#include "std/deque"
#include "std/map"
#include "std/queue"
#include "std/string"


class NIDAllocator
{
public:
	class NIDGenerator
	{
		/* this+0x0  */ //const NIDAllocator::NIDGenerator::`vftable'
		/* this+0x4  */ private: const unsigned int m_MinID;
		/* this+0x8  */ private: const unsigned int m_MaxID;
		/* this+0xC  */ private: const unsigned char m_GroupID;
		/* this+0x10 */ private: mystd::queue< unsigned int,mystd::deque<unsigned int> > m_StandbyIDqueue;
		/* this+0x30 */ private: mystd::map<unsigned int,bool> m_IDContainer;
		/* this+0x3C */ private: bool m_bOK;

		typedef mystd::map<unsigned int,bool>::const_iterator IDCONTAINERITOR;

		public: bool NIDAllocator::NIDGenerator::isOK(void);
		//public: unsigned int NIDAllocator::NIDGenerator::Alloc();
		//public: void NIDAllocator::NIDGenerator::Free(const unsigned int);
		//public: const int GetGroupID();
		public: NIDAllocator::NIDGenerator::NIDGenerator(const unsigned int in_GroupID, const unsigned int in_MinID, const unsigned int in_MaxID);
		public: virtual NIDAllocator::NIDGenerator::~NIDGenerator(void);

	private:
		static hook_method<bool (NIDAllocator::NIDGenerator::*)(void)> NIDAllocator::NIDGenerator::_isOK;
	};

	/* this+0x0  */ //const NIDAllocator::`vftable'
	/* static    */ private: static hook_ptr<NIDAllocator*> m_cpSelf;
	/* this+0x4  */ private: RTL_CRITICAL_SECTION m_CS;
	/* this+0x1C */ private: bool m_bOK;
	/* this+0x20 */ private: mystd::map<mystd::string,NIDAllocator::NIDGenerator*> m_GroupContainer;
	/* this+0x2C */ private: unsigned int m_LastAlloGroupNum;

	typedef mystd::map<mystd::string,NIDAllocator::NIDGenerator*>::const_iterator GROUPCONTAINERITOR;

	private: bool NIDAllocator::Create(void);
	private: void NIDAllocator::Destroy(void);
	public: bool NIDAllocator::isOK(void);
	public: bool NIDAllocator::RegisterGroup(const mystd::string in_strGroupName, const unsigned int in_MinID, const unsigned int in_MaxID);
	public: unsigned int NIDAllocator::Alloc(const mystd::string in_strGroupName);
	public: void NIDAllocator::Free(const mystd::string in_strGroupName, const unsigned int in_ID);
	public: const int NIDAllocator::GetGroupID(const mystd::string in_strGroupName);
	public: const int NIDAllocator::GetGroupID(const unsigned int in_ID);
	public: static NIDAllocator* NIDAllocator::GetObj(void);
	public: static bool __cdecl NIDAllocator::CreateInstance(void);
	public: static void __cdecl NIDAllocator::DestroyInstance(void);
	protected: NIDAllocator::NIDAllocator(void);
	protected: virtual NIDAllocator::~NIDAllocator(void);

private:
	static hook_method<bool (NIDAllocator::*)(void)> NIDAllocator::_Create;
	static hook_method<void (NIDAllocator::*)(void)> NIDAllocator::_Destroy;
	static hook_method<bool (NIDAllocator::*)(void)> NIDAllocator::_isOK;
	static hook_method<bool (NIDAllocator::*)(const mystd::string in_strGroupName, const unsigned int in_MinID, const unsigned int in_MaxID)> NIDAllocator::_RegisterGroup;
	static hook_method<unsigned int (NIDAllocator::*)(const mystd::string in_strGroupName)> NIDAllocator::_Alloc;
	static hook_method<void (NIDAllocator::*)(const mystd::string in_strGroupName, const unsigned int in_ID)> NIDAllocator::_Free;
	static hook_method<const int (NIDAllocator::*)(const mystd::string in_strGroupName)> NIDAllocator::_GetGroupID;
	static hook_method<const int (NIDAllocator::*)(const unsigned int in_ID)> NIDAllocator::_GetGroupID2;
	static hook_method<static NIDAllocator* (__cdecl *)(void)> NIDAllocator::_GetObj;
	static hook_method<bool (__cdecl *)(void)> NIDAllocator::_CreateInstance;
	static hook_method<void (__cdecl *)(void)> NIDAllocator::_DestroyInstance;
};
