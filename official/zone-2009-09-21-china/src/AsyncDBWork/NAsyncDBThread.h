#pragma once
#include "AsyncDBWork/NInter.h"
#include "AsyncDBWork/NObject.h"
#include "AsyncDBWork/NThread.h"
#include "AsyncDBWork/NTPMessageQueue.h"
#include "AsyncDBWork/NODBCCtrl.h"
#include "AsyncDBWork/NAsyncDBRequestCircularQueue.h"
#include "AsyncDBWork/NAsyncDBResponseCircularQueue.h"
#include "std/string"


class NAsyncDBThread : public NObject, public NThread, public NInter
{
	enum enumState
	{
		STATE_DISCONNECT = 0x0,
		STATE_CONNECT = 0x1,
	};

	struct vtable_NObject_t //const NAsyncDBThread::`vftable'{for `NObject'}
	{
		void* (NAsyncDBThread::* scalar_deleting_destructor)(unsigned int);
	};

	struct vtable_NThread_t //const NAsyncDBThread::`vftable'{for `NThread'}
	{
		unsigned int (NAsyncDBThread::* ThreadFunction)(void);
		void (NAsyncDBThread::* PostThreadQuitMessage)(void);
		void* (NAsyncDBThread::* vector_deleting_destructor_adjustor_36)(unsigned int);
	};

	struct vtable_NInter_t //const NAsyncDBThread::`vftable'{for `NInter'}
	{
		void (NAsyncDBThread::* PostInterMessage)(unsigned int, unsigned long, int, int, int);
		bool (NAsyncDBThread::* PeekInterMessage)(unsigned long ,unsigned int&, int&, int&, int&, bool);
		void* (NAsyncDBThread::* vector_deleting_destructor_adjustor_56)(unsigned int);
	};

	/* this+0x0  */ //NObject
	/* this+0x24 */ //NThread
	/* this+0x38 */ //NInter
	/* this+0x3C */ private: bool m_bOK;
	/* this+0x40 */ private: const mystd::string m_ODBCConnectionStr;
	/* this+0x5C */ private: NTPMessageQueue m_MessageQueue;
	/* this+0x8C */ private: HANDLE m_hMessageEvent;
	/* this+0x90 */ private: NODBCCtrl m_ODBCCtrl;
	/* this+0xA0 */ private: const unsigned int m_hMotherInter;
	/* this+0xA4 */ private: NAsyncDBRequestCircularQueue* const m_vcpRequestCircularQueue;
	/* this+0xA8 */ private: NAsyncDBResponseCircularQueue* const m_vcpReponseCircularQueue;
	/* this+0xAC */ private: enum NAsyncDBThread::enumState m_State;

	private: bool NAsyncDBThread::Create(void);
	private: void NAsyncDBThread::Destory(void); // FIXME rename to NAsyncDBThread::Destroy
	//public: const bool NAsyncDBThread::isOK();
	public: bool NAsyncDBThread::Start(void);
	//public: void NAsyncDBThread::Stop();
	public: virtual void NAsyncDBThread::PostInterMessage(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam);
	private: virtual bool NAsyncDBThread::PeekInterMessage(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Msg, int& out_wParam, int& out_lParam, const bool in_bRemove); 
	private: virtual unsigned int NAsyncDBThread::ThreadFunction(void);
	//private: const bool NAsyncDBThread::ThreadFunction_Message();
	private: virtual void NAsyncDBThread::PostThreadQuitMessage(void);
	public: NAsyncDBThread::NAsyncDBThread(const unsigned int in_hMotherInter, const mystd::string in_ODBCConnectionStr, NAsyncDBRequestCircularQueue* const in_cpRequestCircularQueue, NAsyncDBResponseCircularQueue* const in_cpReponseCircularQueue);
	public: virtual NAsyncDBThread::~NAsyncDBThread(void);

private:
	static hook_method<bool (NAsyncDBThread::*)(void)> NAsyncDBThread::_Create;
	static hook_method<void (NAsyncDBThread::*)(void)> NAsyncDBThread::_Destory;
	static hook_method<bool (NAsyncDBThread::*)(void)> NAsyncDBThread::_Start;
	static hook_method<void (NAsyncDBThread::*)(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam)> NAsyncDBThread::_PostInterMessage;
	static hook_method<bool (NAsyncDBThread::*)(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Msg, int& out_wParam, int& out_lParam, const bool in_bRemove)> NAsyncDBThread::_PeekInterMessage;
	static hook_method<unsigned int (NAsyncDBThread::*)(void)> NAsyncDBThread::_ThreadFunction;
	static hook_method<void (NAsyncDBThread::*)(void)> NAsyncDBThread::_PostThreadQuitMessage;
};
