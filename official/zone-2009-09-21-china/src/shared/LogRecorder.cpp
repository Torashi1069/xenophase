#include "DatabaseLog.h"
#include "LogRecorder.h"


hook_method<void (CLogRecorder::*)(void* pDatabaseLog)> CLogRecorder::_Add(SERVER, "CLogRecorder::Add");
void CLogRecorder::Add(void* pDatabaseLog) // line 29 (LogRecorder.h)
{
	return (this->*_Add)(pDatabaseLog);

	m_listDatabaseLog.push_back(pDatabaseLog);
}


hook_method<void (CLogRecorder::*)(void)> CLogRecorder::_BeginSaveToDatabase(SERVER, "CLogRecorder::BeginSaveToDatabase");
void CLogRecorder::BeginSaveToDatabase(void) // line 34 (LogRecorder.h)
{
	return (this->*_BeginSaveToDatabase)();

	m_hSaveDatabase = (HANDLE)_beginthread(&CLogRecorder::threadLogRecorder, 0, this);
}


//hook_method<void (CLogRecorder::*)(void)> CLogRecorder::_EndSaveToDatabase(SERVER, "CLogRecorder::EndSaveToDatabase");
void CLogRecorder::EndSaveToDatabase(void) // line ?? (LogRecorder.h)
{
//	return (this->*_EndSaveToDatabase)();

	CloseHandle(m_hSaveDatabase);
}


hook_method<static void (__cdecl *)(void* lpParam)> CLogRecorder::_threadLogRecorder(SERVER, "CLogRecorder::threadLogRecorder");
void CLogRecorder::threadLogRecorder(void* lpParam) // line 44 (LogRecorder.h)
{
	return (_threadLogRecorder)(lpParam);

	CLogRecorder* self = (CLogRecorder*)lpParam;

	while( true )
	{
		while( self->m_listDatabaseLog.begin() == self->m_listDatabaseLog.end() )
			;

		for( mystd::list<void*>::iterator it = self->m_listDatabaseLog.begin(); it != self->m_listDatabaseLog.end(); ++it )
		{
			CDatabaseLog<void*>* db = (CDatabaseLog<void*>*)*it;

			if( db == NULL )
				continue;

			db->CDatabaseLog<void*>::LogToDatabase();
			Sleep(10);
		}
	}
}
