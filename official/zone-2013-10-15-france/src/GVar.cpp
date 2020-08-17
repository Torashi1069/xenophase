#include "GVar.h"
#include "ZoneProcess.h"
#include "shared/NCriticalErrorLog.h"
#include <Psapi.h>


/// singleton instance
CGVar*& CGVar::m_cpSelf = VTOR<CGVar*>(DetourFindFunction(EXEPATH(), "CGVar::m_cpSelf"));


CGVar::CGVar()
{
	m_DBColumnSizeBodyItem = 4000;
	m_DenominatorData = 100.0;
	m_DBColumnSizeStoreItem = 4000;
	m_DBColumnSizeCartItem = 4000;
//	m_valid_client_file_length = 0;
	m_bAgainstServerSiegeWarfare = 0;
//	m_UserBlock = {};
	m_HSID = 0;
	m_bOK = false;

	m_character_data_save_interval_minute = 12;
	m_bIsMaskPlayerNameBSI = true;
	m_bFreeServer_Always_PK_in_Agit_Map = true;
	m_AsyncDBThreadNum = 20;
	m_IrMailExpireDay = 31;
	m_MIN_ZENY_ITEMLOG_EXECEXCHANGEITEM = 5000;

	if( this->CGVar::Create() )
		m_bOK = true;
}


CGVar::~CGVar()
{
	this->CGVar::Destory();
}


const bool CGVar::isOK() const
{
	return m_bOK;
}


bool CGVar::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;
	
	m_cpSelf = new CGVar();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CGVar::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CGVar::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CGVar* CGVar::GetObj() /// @custom
{
	return m_cpSelf;
}


bool CGVar::Create()
{
	m_DBColumnSizeBodyItem = GetPrivateProfileIntA("CHECK", "DATABASE_COLUMN_SIZE_BODYITEM", 4000, g_infFile);
	m_DBColumnSizeStoreItem = GetPrivateProfileIntA("CHECK", "DATABASE_COLUMN_SIZE_STOREITEM", 4000, g_infFile);
	m_DBColumnSizeCartItem = GetPrivateProfileIntA("CHECK", "DATABASE_COLUMN_SIZE_CARTITEM", 4000, g_infFile);

	m_character_data_save_interval_minute = GetPrivateProfileIntA("SETTING", "character data save interval minute", 12, g_infFile);
	NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "character data save interval minute=%d", m_character_data_save_interval_minute);

	m_UserBlock.when_reassembly_time_out = GetPrivateProfileIntA("user block", "when reassembly time out", 1800, g_infFile);
	m_UserBlock.when_reassembly_invalid = GetPrivateProfileIntA("user block", "when reassembly invalid", 1800, g_infFile);
	m_UserBlock.when_reassembly_modifyIMT_winsock = GetPrivateProfileIntA("user block", "when reassembly modify", 1800, g_infFile);
	m_UserBlock.when_reassembly_modifyIMT_gdi32 = GetPrivateProfileIntA("user block", "when reassembly modify", 9000, g_infFile);
	m_UserBlock.when_reassembly_hackshield = GetPrivateProfileIntA("user block", "when reassembly hackshield", 0, g_infFile);
	m_UserBlock.when_found_unknown_packet = GetPrivateProfileIntA("user block", "when found unknown packet", 1800, g_infFile);

	m_AsyncDBThreadNum = GetPrivateProfileIntA("SETTING", "asynchronous database thread number", 20, g_infFile);
	if( m_AsyncDBThreadNum < 40 )
		m_AsyncDBThreadNum = 40;

	m_valid_client_file_length = GetPrivateProfileIntA("SETTING", "valid client file length", 0, g_infFile);
	m_bIsMaskPlayerNameBSI = GetPrivateProfileIntA("SETTING", "mask player name when special item obtain", true, g_infFile) != 0;
	m_bFreeServer_Always_PK_in_Agit_Map = GetPrivateProfileIntA("ETC", "free server always pk in agit map", true, g_infFile) != 0;
	m_bAgainstServerSiegeWarfare = GetPrivateProfileIntA("SIEGE", "against server", false, g_infFile) != 0;

	m_MIN_ZENY_ITEMLOG_EXECEXCHANGEITEM = GetPrivateProfileIntA("ETC", "minimum zeny amount when output zeny log", 10000, g_infFile);

	if( m_MIN_ZENY_ITEMLOG_EXECEXCHANGEITEM < 0 )
		m_MIN_ZENY_ITEMLOG_EXECEXCHANGEITEM = 0;
	if( m_MIN_ZENY_ITEMLOG_EXECEXCHANGEITEM > 10000 )
		m_MIN_ZENY_ITEMLOG_EXECEXCHANGEITEM = 10000;

	return true;
}


void CGVar::Destory()
{
}


int CGVar::GetDBColumnSizeBodyItem()
{
	return m_DBColumnSizeBodyItem;
}


int CGVar::GetDBColumnSizeStoreItem()
{
	return m_DBColumnSizeStoreItem;
}


int CGVar::GetDBColumnSizeCartItem()
{
	return m_DBColumnSizeCartItem;
}


int CGVar::GetUserBlockSecond_when_reassembly_time_out()
{
	return m_UserBlock.when_reassembly_time_out;
}


int CGVar::GetUserBlockSecond_when_reassembly_invalid()
{
	return m_UserBlock.when_reassembly_invalid;
}


int CGVar::GetUserBlockSecond_when_reassembly_modifyIMT_winsock()
{
	return m_UserBlock.when_reassembly_modifyIMT_winsock;
}


int CGVar::GetUserBlockSecond_when_reassembly_modifyIMT_gdi32()
{
	return m_UserBlock.when_reassembly_modifyIMT_gdi32;
}


int CGVar::GetUserBlockSecond_when_reassembly_hackshield()
{
	return m_UserBlock.when_reassembly_hackshield;
}


int CGVar::GetUserBlockSecond_when_found_unknown_packet()
{
	return m_UserBlock.when_found_unknown_packet;
}


int CGVar::GetCharacterDataSaveIntervalMinute()
{
	return m_character_data_save_interval_minute;
}


int CGVar::GetAsyncDBThreadNum()
{
	return m_AsyncDBThreadNum;
}


unsigned int CGVar::get_valid_client_file_length()
{
	return m_valid_client_file_length;
}


unsigned int CGVar::GetUsedMemoryBytes()
{
	PROCESS_MEMORY_COUNTERS pmc = {};

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
	if( hProcess == NULL )
		return 0;

	if( !GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)) )
	{
		CloseHandle(hProcess);
		return 0;
	}

	CloseHandle(hProcess);
	return pmc.PagefileUsage;
}


bool CGVar::IsMaskPlayerNameBSI()
{
	return m_bIsMaskPlayerNameBSI;
}


bool CGVar::IsFreeServerAlwaysPKinAgitMap()
{
	return m_bFreeServer_Always_PK_in_Agit_Map;
}


bool CGVar::IsAgainstServerSiegeWarfare()
{
	return m_bAgainstServerSiegeWarfare;
}


int CGVar::GetHSID()
{
	return m_HSID;
}


void CGVar::SetHSID(const int in_HSID)
{
	m_HSID = in_HSID;
}


int CGVar::GetIrMailExpireDay()
{
	return m_IrMailExpireDay;
}


int CGVar::GetMIN_ZENY_ITEMLOG_EXECEXCHANGEITEM()
{
	return m_MIN_ZENY_ITEMLOG_EXECEXCHANGEITEM;
}


int CGVar::GetMaxCharacterCount() const
{
	return 1500;
}


float CGVar::GetDenominatorData()
{
	return m_DenominatorData;
}