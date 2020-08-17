#pragma once
#include "AsyncDBWork/NAsyncDBWork.h"


class CLoadCartADBWork : public NAsyncDBWork
{
	enum enumResult
	{
		RESULT_SUCCESS                = 0,
		RESULT_ERROR_UNKNOWN          = 1,
		RESULT_ERROR_LOAD_CART        = 2,
		RESULT_ERROR_LOAD_CART_INSERT = 3,
	};

	struct vtable_t //const CLoadCartADBWork::`vftable'
	{
		bool (CLoadCartADBWork::* ExecQuery)(NODBCCtrl& in_ODBCCtrl);
		void* (CLoadCartADBWork::* vector_deleting_destructor)(unsigned int);
	};

	/* this+0x0    */ //NAsyncDBWork
	/* this+0x14   */ private: const unsigned long m_AID;
	/* this+0x18   */ private: const unsigned long m_GID;
	/* this+0x1C   */ private: enum CLoadCartADBWork::enumResult m_Result;
	/* this+0x20   */ public: unsigned char m_Data[16300];
	/* this+0x3FCC */ public: int m_Length;
	/* this+0x3FD0 */ public: const int m_SKLevel;

	//public: const enum CLoadCartADBWork::enumResult GetResult();
	//public: const unsigned long GetGID();
	//public: const unsigned long GetAID();
	private: virtual bool CLoadCartADBWork::ExecQuery(class NODBCCtrl& in_ODBCCtrl);
	//private: enum NAsyncDBWork::enumRETURN CLoadCartADBWork::LoadCart(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLoadCartADBWork::InsertCart(NODBCCtrl &);
	public: CLoadCartADBWork::CLoadCartADBWork(const unsigned long in_AID, const unsigned long in_GID, const int in_SKLevel);
	public: virtual CLoadCartADBWork::~CLoadCartADBWork(void);

private:
	static hook_method<bool (CLoadCartADBWork::*)(NODBCCtrl& in_ODBCCtrl)> CLoadCartADBWork::_ExecQuery;
};
