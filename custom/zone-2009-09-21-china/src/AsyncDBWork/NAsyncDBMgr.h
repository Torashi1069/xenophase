#pragma once
#include "AsyncDBWork/NAsyncDBRequestCircularQueue.h"
#include "AsyncDBWork/NAsyncDBResponseCircularQueue.h"
#include "AsyncDBWork/NAsyncDBThread.h"
#include "AsyncDBWork/NInter.h"
#include "AsyncDBWork/NInterMessageQueue.h"
#include "AsyncDBWork/NObject.h"
#include "std/vector"


class NAsyncDBMgr : public NObject, public NInter
{
	enum
	{
		TIMEOUT = 40000,
	};

	enum
	{
		MAX_ASYNCDB_WORK = 15000,
		MAX_TASK_NUM_PER_PROCESSLOOP = 150,
	};

	struct vtable_NObject_t //const NAsyncDBMgr::`vftable'{for `NObject'}
	{
		void* (NAsyncDBMgr::* scalar_deleting_destructor)(unsigned int flags);
	};

	struct vtable_NInter_t //const NAsyncDBMgr::`vftable'{for `NInter'}
	{
		void (NAsyncDBMgr::* PostInterMessage)(const unsigned int, const unsigned long, const int, const int, const int);
		bool (NAsyncDBMgr::* PeekInterMessage)(const unsigned long, unsigned int&, int&, int&, int&, const bool);
		void* (NAsyncDBMgr::* scalar_deleting_destructor_adjustor_36)(unsigned int flags);
	};

	/* this+  0 */ public: //NObject baseclass_0;
	/* this+ 36 */ public: //NInter baseclass_36;
	/* static   */ private: static hook_ptr<NAsyncDBMgr*> m_cpSelf;
	/* this+ 40 */ private: bool m_bOK;
	/* this+ 44 */ private: NAsyncDBRequestCircularQueue* m_cpRequestCircularQueue;
	/* this+ 48 */ private: NAsyncDBResponseCircularQueue* m_cpReponseCircularQueue;
	/* this+ 52 */ private: NInterMessageQueue m_MessageQueue;
	/* this+100 */ private: mystd::vector<NAsyncDBThread*> m_WorkThreadContainer;
	/* this+116 */ private: int m_WorkThreadGroupID;

	private: bool NAsyncDBMgr::Create(const mystd::string in_ODBCConnectionStr);
	private: void NAsyncDBMgr::Destory(void); // FIXME rename to NAsyncDBMgr::Destroy
	//private: void NAsyncDBMgr::ProcessMessage();
	//private: void NAsyncDBMgr::ProcessDBWork(NAsyncDBWork * const);
	//private: void NAsyncDBMgr::ProcessDBWork_SAVE_ALL(CSaveAllADBWork * const);
	//private: void NAsyncDBMgr::ProcessDBWork_LogonPermit(CLogonPermitADBWork * const);
	//private: void NAsyncDBMgr::ProcessDBWork_SAVE_SKILL(CSaveSkillADBWork * const);
	//private: void NAsyncDBMgr::ProcessDBWork_LOAD_STORE(CLoadStoreADBWork * const);
	//private: void NAsyncDBMgr::ProcessDBWork_SAVE_STORE(CSaveStoreADBWork * const);
	//private: void NAsyncDBMgr::ProcessDBWork_LOAD_CART(CLoadCartADBWork * const);
	//private: void NAsyncDBMgr::ProcessDBWork_SAVE_CART(CSaveCartADBWork * const);
	//private: void NAsyncDBMgr::ProcessDBWork_MERCENARY_CREATE(CMercenaryCreateADBWork * const);
	//private: void NAsyncDBMgr::ProcessDBWork_MERCENARY_DELETE(CMercenaryDeleteADBWork * const);
	//private: void NAsyncDBMgr::ProcessDBWork_SAVE_EFFECTIVEINFO(CSaveEffectiveInfoADBWork * const);
	//public: const bool NAsyncDBMgr::isOK();
	public: bool NAsyncDBMgr::Start(void);
	public: void NAsyncDBMgr::Stop(void);
	public: void NAsyncDBMgr::Process(void);
	public: bool NAsyncDBMgr::RequestWork(NAsyncDBWork* in_cpWork);
	//public: NAsyncDBWork* NAsyncDBMgr::ResponseWork();
	//public: int NAsyncDBMgr::GetRequestWorkNum();
	//public: void NAsyncDBMgr::PostInterMessage(const unsigned int, const unsigned long, const int, const int, const int);
	//public: bool NAsyncDBMgr::PeekInterMessage(const unsigned long, unsigned int &, int &, int &, int &, const bool);
	public: static bool NAsyncDBMgr::CreateInstance(const mystd::string in_ODBCConnectionStr);
	public: static void NAsyncDBMgr::DestoryInstance(void); // FIXME rename to NAsyncDBMgr::DestroyInstance
	public: static NAsyncDBMgr* NAsyncDBMgr::GetObj(void);
	private: NAsyncDBMgr::NAsyncDBMgr(const mystd::string in_ODBCConnectionStr);
	private: NAsyncDBMgr::~NAsyncDBMgr(void);

private:
	static hook_method<bool (NAsyncDBMgr::*)(const mystd::string in_ODBCConnectionStr)> NAsyncDBMgr::_Create;
	static hook_method<void (NAsyncDBMgr::*)(void)> NAsyncDBMgr::_Destory;
	static hook_method<bool (NAsyncDBMgr::*)(void)> NAsyncDBMgr::_Start;
	static hook_method<void (NAsyncDBMgr::*)(void)> NAsyncDBMgr::_Stop;
	static hook_method<void (NAsyncDBMgr::*)(void)> NAsyncDBMgr::_Process;
	static hook_method<bool (NAsyncDBMgr::*)(NAsyncDBWork* in_cpWork)> NAsyncDBMgr::_RequestWork;
	static hook_method<bool (__cdecl *)(const mystd::string in_ODBCConnectionStr)> NAsyncDBMgr::_CreateInstance;
	static hook_method<void (__cdecl *)(void)> NAsyncDBMgr::_DestoryInstance;
};
