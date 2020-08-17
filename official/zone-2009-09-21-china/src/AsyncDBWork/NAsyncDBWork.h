#pragma once
#include "AsyncDBWork/NODBCCtrl.h"


class NAsyncDBWork
{
	public: enum enumType
	{
		TYPE_UNZIP               = 0,
		TYPE_ZIP                 = 1,
		TYPE_LOGON_PERMIT        = 2,
		TYPE_SAVE_ALL            = 3,
		TYPE_SAVE_BODYITEM       = 4,
		TYPE_SAVE_CHARACTERINFO  = 5,
		TYPE_SAVE_SKILL          = 6,
		TYPE_LOAD_STORE          = 7,
		TYPE_SAVE_STORE          = 8,
		TYPE_LOAD_CART           = 9,
		TYPE_SAVE_CART           = 10,
		TYPE_MERCENARY_CREATE    = 11,
		TYPE_MERCENARY_DELETE    = 12,
		TYPE_SAVE_EFFECTIVEINFO  = 13,
		TYPE_SAVE_QUESTEVENT     = 14,
		TYPE_SAVE_BATTLEFIELD    = 15,
		TYPE_SKILL3RD_UPDATE     = 16,
		TYPE_SKILL3RD_DELETE     = 17,
		TYPE_SKILL3RD_RESET      = 18,
		TYPE_JOB_CHANGE          = 19,
		TYPE_JOB_TRANSCENDENT    = 20,
		TYPE_EFFECT3RD_DELETE    = 21,
		TYPE_EFFECT3RD_UPDATEALL = 22,
		TYPE_LOAD_CHARNAME       = 23,
		TYPE_TEST                = 24,
	};

	protected: enum enumRETURN
	{
		RETURN_SUCCESS    = 0,
		RETURN_ERROR_ODBC = 1,
		RETURN_ERROR      = 2,
		RETURN_NO_DATA    = 3,
	};

	enum
	{
		MAXNUM_TRYCNT = 65535,
	};

	struct vtable_t
	{
		bool (NAsyncDBWork::* ExecQuery)(NODBCCtrl& in_ODBCCtrl); //__purecall
		void* (NAsyncDBWork::* vector_deleting_destructor)(unsigned int);
	};

	/* this+0x0  */ //const NAsyncDBWork::`vftable'
	/* this+0x4  */ private: const enum NAsyncDBWork::enumType m_Type;
	/* this+0x8  */ private: const unsigned int m_ID;
	/* this+0xC  */ private: const unsigned long m_StartTM;
	/* this+0x10 */ private: const int m_Identity;


	private: virtual bool NAsyncDBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl) = 0;
	//protected: enum NAsyncDBWork::enumRETURN NAsyncDBWork::SaveBodyItem(NODBCCtrl &, const unsigned long, const unsigned char *, const int);
	//protected: enum NAsyncDBWork::enumRETURN NAsyncDBWork::SaveCharacterInfo(NODBCCtrl &, const unsigned long, const char *, CHARINFO_TO_CHARACTERDB &);
	//protected: enum NAsyncDBWork::enumRETURN NAsyncDBWork::SaveEffective(NODBCCtrl &, const unsigned long, const unsigned char *, const int);
	//protected: enum NAsyncDBWork::enumRETURN NAsyncDBWork::SaveStoreItem(NODBCCtrl &, const unsigned long, const unsigned char *, const int);
	//protected: enum NAsyncDBWork::enumRETURN NAsyncDBWork::SaveCartItem(NODBCCtrl &, const unsigned long, const unsigned char *, const int);
	//protected: enum NAsyncDBWork::enumRETURN NAsyncDBWork::SaveQuestEvent(NODBCCtrl &, const unsigned long, const unsigned char *, const int, const unsigned char *, const int, const unsigned char *, const int, const unsigned char *, const int);
	public: const enum NAsyncDBWork::enumType NAsyncDBWork::GetType(void);
	public: const unsigned int NAsyncDBWork::GetID(void);
	public: const unsigned long NAsyncDBWork::GetStartTM(void);
	public: const int NAsyncDBWork::GetIdentity(void);
	public: NAsyncDBWork::NAsyncDBWork(const enum NAsyncDBWork::enumType in_Type, const unsigned int in_ID);
	public: virtual NAsyncDBWork::~NAsyncDBWork(void);

private:
	static hook_method<const enum NAsyncDBWork::enumType (NAsyncDBWork::*)(void)> NAsyncDBWork::_GetType;
	static hook_method<const unsigned int (NAsyncDBWork::*)(void)> NAsyncDBWork::_GetID;
	static hook_method<const unsigned long (NAsyncDBWork::*)(void)> NAsyncDBWork::_GetStartTM;
	static hook_method<const int (NAsyncDBWork::*)(void)> NAsyncDBWork::_GetIdentity;
};
