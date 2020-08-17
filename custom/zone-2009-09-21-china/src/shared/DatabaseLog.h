#pragma once
#include "CriticalSection.h"
#include "ExtendedODBC.h"
#include "std/queue"
#include <sql.h>


template<typename T> class CDatabaseLog : public CExtendedODBC
{
public:
	struct vtable_t //const CDatabaseLog<T>::`vftable'
	{
		void* (CDatabaseLog<T>::* scalar_deleting_destructor)(unsigned int flags);
		void (CDatabaseLog<T>::* ConnectToDatabase)(const char* Log); //__purecall
		int (CDatabaseLog<T>::* SaveToDatabase)(SQLHSTMT, T); //__purecall
	};

	/* this+ 0 */ public: //CExtendedODBC baseclass_0;
	/* this+20 */ protected: mystd::queue<T> m_queLog;
	/* this+52 */ protected: CCriticalSection m_csLog;

	public: CDatabaseLog(void);
	public: virtual ~CDatabaseLog(void);
	public: void CDatabaseLog<T>::AddLog(T Log);
	public: void CDatabaseLog<T>::LogToDatabase(void);
	public: virtual void CDatabaseLog<T>::ConnectToDatabase(const char* Log) = 0;
	private: virtual int CDatabaseLog<T>::SaveToDatabase(SQLHSTMT hStmt, T pLog) = 0;
};


template<typename T> CDatabaseLog<T>::CDatabaseLog(void)
{
}


template<typename T> CDatabaseLog<T>::~CDatabaseLog(void)
{
}


template<typename T> void CDatabaseLog<T>::AddLog(T Log)
{
	m_csLog.Enter();
	m_queLog.push_back(Log);
	m_csLog.Leave();
}


template<typename T> void CDatabaseLog<T>::LogToDatabase(void)
{
	m_csLog.Enter();

	if( m_queLog.size() == 0 )
	{
		m_csLog.Leave();
		return;
	}

	T log = m_queLog.front();
	m_queLog.pop();

	m_csLog.Leave();

	SQLHSTMT hStmt = SQL_NULL_HSTMT;
	if( !this->CExtendedODBC::AllocStmt(&hStmt) )
	{
		MessageBoxA(NULL, "CDatabaseLog::AllocStmt() - AllocStmt() Fail!\n", "", MB_OK);
		return;
	}

	
	if( !this->SaveToDatabase(hStmt, log) )
	{
		MessageBoxA(NULL, "CDatabaseLog::LogToDatabase() - SaveToDatabase() Fail!", "", MB_OK);
		this->CExtendedODBC::FreeStmt(&hStmt, 1);
		return;
	}

	this->CExtendedODBC::FreeStmt(&hStmt, 1);
}
