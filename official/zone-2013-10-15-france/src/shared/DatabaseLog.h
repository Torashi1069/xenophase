#pragma once
#include "shared/CriticalSection.h"
#include "shared/ExtendedODBC.h"


template<typename T> class CDatabaseLog : public CExtendedODBC
{
public:
	void AddLog(T Log);
	void LogToDatabase();
	virtual void ConnectToDatabase(const char* Log) = 0;
	int GetSize() const;

private:
	virtual BOOL SaveToDatabase(SQLHSTMT hStmt, T Log) = 0;

protected:
	/* this+ 0 */ //CExtendedODBC baseclass_0;
	/* this+20 */ std::queue<T> m_queLog;
	/* this+44 */ CCriticalSection m_csLog;
};


template<typename T> void CDatabaseLog<T>::AddLog(T Log)
{
	m_csLog.CCriticalSection::Enter();
	m_queLog.push(Log);
	m_csLog.CCriticalSection::Leave();
}


template<typename T> int CDatabaseLog<T>::GetSize() const
{
	const_cast<CCriticalSection&>(m_csLog).CCriticalSection::Enter();
	int size = m_queLog.size();
	const_cast<CCriticalSection&>(m_csLog).CCriticalSection::Leave();

	return size;
}


template<typename T> void CDatabaseLog<T>::LogToDatabase()
{
	m_csLog.CCriticalSection::Enter();
	if( m_queLog.size() == 0 )
	{
		m_csLog.CCriticalSection::Leave();
		return;
	}
	T Log = m_queLog.front();
	m_queLog.pop();
	m_csLog.CCriticalSection::Leave();

	SQLHSTMT hStmt = SQL_NULL_HSTMT;
	if( !this->CExtendedODBC::AllocStmt(&hStmt) )
	{
		MessageBoxA(NULL, "CDatabaseLog::AllocStmt() - AllocStmt() Fail!\n", "", MB_OK);
		return;
	}

	if( !this->SaveToDatabase(hStmt, Log) )
	{
		MessageBoxA(NULL, "CDatabaseLog::LogToDatabase() - SaveToDatabase() Fail!", "", MB_OK);
		this->CExtendedODBC::FreeStmt(&hStmt, SQL_DROP);
		return;
	}

	this->CExtendedODBC::FreeStmt(&hStmt, SQL_DROP);
}
