#include "N2System/DBLog/N2DBLog.h"


class CMemorialDungeonDBLog : public N2DBLog
{
	struct vtable_t
	{
		bool (CMemorialDungeonDBLog::* Run)(N2ODBCCtrl& in_ODBCCtrl);
		void* (CMemorialDungeonDBLog::* scalar_deleting_destructor)(unsigned int flags);
	};

	public: enum enumTYPE
	{
		TYPE_SUBSCRIPTION                       = 0,
		TYPE_SUBSCRIPTION_CANCEL_BY_USER        = 1,
		TYPE_SUBSCRIPTION_CANCEL_BY_CREATE_FAIL = 2,
		TYPE_CREATE                             = 3,
		TYPE_DESTROY_BY_USER                    = 4,
		TYPE_DESTROY_BY_LIVETIME                = 5,
		TYPE_DESTROY_BY_ENTERTIME               = 6,
	};

	/* this+ 0 */ public: //N2DBLog baseclass_0;
	/* this+ 8 */ private: bool m_bOK;
	/* this+12 */ private: const enum CMemorialDungeonDBLog::enumTYPE m_Type;
	/* this+16 */ private: const mystd::string m_MemorialDungeonName;
	/* this+44 */ private: const mystd::string m_PartyName;
	/* this+72 */ private: const int m_PartyID;
	/* this+76 */ private: const int m_CreateZSID;

	public: CMemorialDungeonDBLog::CMemorialDungeonDBLog(const enum CMemorialDungeonDBLog::enumTYPE in_Type, const mystd::string in_MemorialDungeonName, const mystd::string in_PartyName, const int in_PartyID, const int in_CreateZSID);
	public: virtual CMemorialDungeonDBLog::~CMemorialDungeonDBLog(void);
	public: bool CMemorialDungeonDBLog::isOK(void);
	private: virtual bool CMemorialDungeonDBLog::Run(N2ODBCCtrl& in_ODBCCtrl);

private:
	static hook_method<bool (CMemorialDungeonDBLog::*)(void)> CMemorialDungeonDBLog::_isOK;
	static hook_method<bool (CMemorialDungeonDBLog::*)(N2ODBCCtrl& in_ODBCCtrl)> CMemorialDungeonDBLog::_Run;
};
