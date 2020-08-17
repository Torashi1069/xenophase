#include "globals.hpp"
#include "ErrorLog.h"
#include "CGVar.hpp"
#include <psapi.h>


hook_ptr<CGVar*> CGVar::m_cpSelf(SERVER, "CGVar::m_cpSelf"); // = ?


CGVar::CGVar(void)
{
	m_DBColumnSizeBodyItem = 4000;
	m_DBColumnSizeStoreItem = 4000;
	m_DBColumnSizeCartItem = 4000;
	m_character_data_save_interval_minute = 12;
	m_AsyncDBThreadNum = 20;
	m_bOK = false;
	if( this->CGVar::Create() )
		m_bOK = true;
}


CGVar::~CGVar(void)
{
}


hook_method<bool (CGVar::*)(void)> CGVar::_Create(SERVER, "CGVar::Create");
bool CGVar::Create(void)
{
	return (this->*_Create)();

	m_DBColumnSizeBodyItem = GetPrivateProfileIntA("CHECK", "DATABASE_COLUMN_SIZE_BODYITEM", 4000, ".\\RO.inf");
	m_DBColumnSizeStoreItem = GetPrivateProfileIntA("CHECK", "DATABASE_COLUMN_SIZE_STOREITEM", 4000, ".\\RO.inf");
	m_DBColumnSizeCartItem = GetPrivateProfileIntA("CHECK", "DATABASE_COLUMN_SIZE_CARTITEM", 4000, ".\\RO.inf");
	m_character_data_save_interval_minute = GetPrivateProfileIntA("SETTING", "character data save interval minute", 12, ".\\RO.inf");
	g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\GVar.cpp", 88, "character data save interval minute=%d", m_character_data_save_interval_minute);
	m_AsyncDBThreadNum = GetPrivateProfileIntA("SETTING", "asynchronous database thread number", 20, ".\\RO.inf");
	if( m_AsyncDBThreadNum < 40 )
		m_AsyncDBThreadNum = 40;
	m_valid_client_file_length = GetPrivateProfileIntA("SETTING", "valid client file length", 0, ".\\RO.inf");

	return true;
}


//hook_method<void (CGVar::*)(void)> CGVar::_Destroy(SERVER, "CGVar::Destroy");
void CGVar::Destroy(void)
{
//	return (this->*_Destroy)();

	;
}


hook_method<const bool (CGVar::*)(void)> CGVar::_isOK(SERVER, "CGVar::isOK");
const bool CGVar::isOK(void)
{
	return (this->*_isOK)();

	return m_bOK;
}


//hook_method<int (CGVar::*)(void)> CGVar::_GetDBColumnSizeBodyItem(SERVER, "CGVar::GetDBColumnSizeBodyItem");
int CGVar::GetDBColumnSizeBodyItem(void)
{
//	return (this->*_GetDBColumnSizeBodyItem)();

	return m_DBColumnSizeBodyItem;
}


//hook_method<int (CGVar::*)(void)> CGVar::_GetDBColumnSizeStoreItem(SERVER, "CGVar::GetDBColumnSizeStoreItem");
int CGVar::GetDBColumnSizeStoreItem(void)
{
//	return (this->*_GetDBColumnSizeStoreItem)();

	return m_DBColumnSizeStoreItem;
}


//hook_method<int (CGVar::*)(void)> CGVar::_GetDBColumnSizeCartItem(SERVER, "CGVar::GetDBColumnSizeCartItem");
int CGVar::GetDBColumnSizeCartItem(void)
{
//	return (this->*_GetDBColumnSizeCartItem)();

	return m_DBColumnSizeCartItem;
}


//hook_method<int (CGVar::*)(void)> CGVar::_GetCharacterDataSaveIntervalMinute(SERVER, "CGVar::GetCharacterDataSaveIntervalMinute");
int CGVar::GetCharacterDataSaveIntervalMinute(void)
{
//	return (this->*_GetCharacterDataSaveIntervalMinute)();

	return m_character_data_save_interval_minute;
}


//hook_method<int (CGVar::*)(void)> CGVar::_GetAsyncDBThreadNum(SERVER, "CGVar::GetAsyncDBThreadNum");
int CGVar::GetAsyncDBThreadNum(void)
{
//	return (this->*_GetAsyncDBThreadNum)();

	return m_AsyncDBThreadNum;
}


//hook_method<unsigned int (CGVar::*)(void)> CGVar::_get_valid_client_file_length(SERVER, "CGVar::get_valid_client_file_length");
unsigned int CGVar::get_valid_client_file_length(void)
{
//	return (this->*_get_valid_client_file_length)();

	return m_valid_client_file_length;
}


hook_method<unsigned int (CGVar::*)(void)> CGVar::_GetUsedMemoryBytes(SERVER, "CGVar::GetUsedMemoryBytes");
unsigned int CGVar::GetUsedMemoryBytes(void)
{
	return (this->*_GetUsedMemoryBytes)();

	PROCESS_MEMORY_COUNTERS pmc;
	pmc.cb = 0;
	pmc.PageFaultCount = 0;
	pmc.PeakWorkingSetSize = 0;
	pmc.WorkingSetSize = 0;
	pmc.QuotaPeakPagedPoolUsage = 0;
	pmc.QuotaPagedPoolUsage = 0;
	pmc.QuotaPeakNonPagedPoolUsage = 0;
	pmc.QuotaNonPagedPoolUsage = 0;
	pmc.PagefileUsage = 0;
	pmc.PeakPagefileUsage = 0;

	HANDLE v1 = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, false, GetCurrentProcessId());
	if( v1 == NULL )
		return 0;

	if( GetProcessMemoryInfo(v1, &pmc, sizeof(pmc)) == 0 )
	{
		CloseHandle(v1);
		return 0;
	}

	CloseHandle(v1);
	return pmc.PagefileUsage;
}


hook_method<CGVar* (__cdecl *)(void)> CGVar::_GetObj(SERVER, "CGVar::GetObj");
CGVar* CGVar::GetObj(void)
{
	return (_GetObj)();

	return CGVar::m_cpSelf;
}


hook_method<static bool (__cdecl *)(void)> CGVar::_CreateInstance(SERVER, "CGVar::CreateInstance");
bool CGVar::CreateInstance(void)
{
	return (_CreateInstance)();

	if( CGVar::m_cpSelf != NULL )
		return false; // already exists

	CGVar::m_cpSelf = new CGVar();
	if( CGVar::m_cpSelf == NULL )
		return false; // alloc failed

	if( !CGVar::m_cpSelf->CGVar::isOK() )
	{
		delete CGVar::m_cpSelf;
		CGVar::m_cpSelf = (CGVar*)NULL;
		return false;
	}

	return true;
}


//hook_method<static void (__cdecl *)(void)> CGVar::_DestroyInstance(SERVER, "CGVar::DestroyInstance");
void CGVar::DestroyInstance(void)
{
//	return (_DestroyInstance)();

	if( CGVar::m_cpSelf != NULL )
	{
		delete CGVar::m_cpSelf;
		CGVar::m_cpSelf = (CGVar*)NULL;
	}
}
