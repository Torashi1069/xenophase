#pragma once
#include "std/list"


class CLogRecorder
{
	/* this+ 0 */ private: mystd::list<void*> m_listDatabaseLog;
	/* this+12 */ private: HANDLE m_hSaveDatabase;

	public: void CLogRecorder::Add(void* pDatabaseLog);
	public: void CLogRecorder::BeginSaveToDatabase(void);
	public: void CLogRecorder::EndSaveToDatabase(void);
	public: static void CLogRecorder::threadLogRecorder(void* lpParam);

private:
	static hook_method<void (CLogRecorder::*)(void* pDatabaseLog)> CLogRecorder::_Add;
	static hook_method<void (CLogRecorder::*)(void)> CLogRecorder::_BeginSaveToDatabase;
	static hook_method<void (CLogRecorder::*)(void)> CLogRecorder::_EndSaveToDatabase;
	static hook_method<static void (__cdecl *)(void* lpParam)> CLogRecorder::_threadLogRecorder;
};
