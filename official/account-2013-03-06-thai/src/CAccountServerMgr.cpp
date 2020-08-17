#include "Account.h"
#include "AccountDB.h"
#include "CAccountServerMgr.h"
#include "CharacterServerInfo.h"
#include "CharSvrProcess.h"
#include "DES.h"
#include "MonitorPacket.h"
#include "PCBangBillingDB.h"
#include "UserProcess.h"
#include "Common/EnterTraceLog.h"
#include "Common/GlobalInfoDB.h"
#include "Common/InfoScript.h"
#include "Common/Network.h"
#include "Common/NOutputTextMgr.h"
#include "Common/Packet.h"
#include "Common/ScriptParser.h"
#include "Common/ServerInfoList.h"
#include "Common/NSystem/NMessageMgr.h"
#include "Network3/AsyncProcessMgr.h"
#include "Network3/CompletionPort.h"
#include "Network3/ProcessFactory.h"
#include "Network3/StreamManager.h"


/// singleton instance
CAccountServerMgr* CAccountServerMgr::m_cpSelf;

/// locals
static CProcessFactory<CCharSvrProcess> g_CharSvrProcessFactory;
static CProcessFactory<CUserProcess> g_UserProcessFactory;


void Decrypt(const char* encBuf, unsigned char* decBuf)
{
	unsigned char key[7] = { 0x78, 0x11, 0x23, 0x2A, 0xF1, 0xED, 0x07 };

	DES des(key);

	size_t size = strlen(encBuf) / 2;
	for( size_t i = 0; i < size; ++i )
	{
		char szString[2+1];
		szString[0] = encBuf[2 * i + 0];
		szString[1] = encBuf[2 * i + 1];
		sscanf_s(szString, "%02X", &decBuf[i], sizeof(szString));
	}

	des.DES::decrypt(decBuf, size);
};


CAccountServerMgr::CAccountServerMgr()
: NThread("AccountServer")
{
	m_bOK = false;
	NMessageMgr::GetObj()->NMessageMgr::Insert(GetMyID(), this);
	m_bOK = true;
}


CAccountServerMgr::~CAccountServerMgr()
{
	NMessageMgr::GetObj()->NMessageMgr::Remove(GetMyID(), this);
}


bool CAccountServerMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) CAccountServerMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->m_bOK )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CAccountServerMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


/// @custom
CAccountServerMgr* CAccountServerMgr::GetObj()
{
	return m_cpSelf;
}


bool CAccountServerMgr::isOK() const
{
	return m_bOK;
}


void CAccountServerMgr::Cleanup()
{
	if( gbUpdateThreadRun )
	{
		gbUpdateThreadRun = false;

		while( !gbUpdateThreadEnd )
			Sleep(100);
	}

	NOutputTextMgr::GetObj()->NOutputTextMgr::Insert("CAccountServerMgr::Cleanup");

	MMRESULT ret = timeEndPeriod(1);
	if( ret != TIMERR_NOERROR )
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "timeEndPeriod failed, ret %u\n", ret);

	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "server terminated -------------------");

	g_bProcessPermit = false;

	Sleep(300);

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("g_UserStreamMgr.Destroy()...");
	g_UserStreamMgr.CStreamManager::Destroy();

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("g_CharSvrStreamMgr.Destroy()...");
	g_CharSvrStreamMgr.CStreamManager::Destroy();

	Sleep(1000);

	NOutputTextMgr::GetObj()->NOutputTextMgr::InsertFmt("g_compltport.Destroy()...");
	g_compltport.CCompletionPort::Destroy();

	CNetwork::GetObj()->CNetwork::CleanupNetwork();
}


unsigned int CAccountServerMgr::ThreadFunction()
{
	std::pair<bool,std::string> ret = this->CAccountServerMgr::Startup1st();
	if( ret.first )
	{
		NOutputTextMgr::GetObj()->NOutputTextMgr::Insert("CAccountServerMgr::Startup1st() complete...");

		while( 1 )
		{
			while( WaitForSingleObject(m_MessageQueue.NMessageQueue::GetEventObj(), INFINITE) != WAIT_OBJECT_0 )
				;

			NMessageQueue::RETG mRet = m_MessageQueue.NMessageQueue::Get();
			if( std::tr1::get<0>(mRet) == true && std::tr1::get<1>(mRet) == MSG_THREAD_QUIT )
				break; // received shutdown signal.
		}

		this->CAccountServerMgr::Cleanup();
	}
	else
	{
		NOutputTextMgr::GetObj()->NOutputTextMgr::Insert(ret.second);
		NOutputTextMgr::GetObj()->NOutputTextMgr::Insert("error CAccountServerMgr::Startup1st()");
	}

	return 0;
}


void CAccountServerMgr::PostThreadQuitMessage()
{
	m_MessageQueue.NMessageQueue::Put(MSG_THREAD_QUIT, 0, 0);
}


bool CAccountServerMgr::Start()
{
	return this->NThread::Begin();
}


void CAccountServerMgr::Stop()
{
	this->NThread::End();
}


std::pair<bool,std::string> CAccountServerMgr::Startup1st()
{
	memset(g_szModuleFileName, '\0', sizeof(g_szModuleFileName));
	GetModuleFileNameA(NULL, g_szModuleFileName, sizeof(g_szModuleFileName)-1);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "build date(%s %s) \nModuleFileName - %s \n", __DATE__, __TIME__, g_szModuleFileName);

	InitPacketLen();
	InitMonitorPktLenMap();

	g_scrptConfig.CInfoScript::Open("account.config.txt");

	const char* szVersionTHAI = g_scrptConfig.CInfoScript::GetInfo("THAI");
	if( szVersionTHAI == NULL )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "cannot read the version of THAI");
	g_nVersion[CLIENTTYPE_THAI] = atoi(szVersionTHAI);

	const char* szVersionTHAISAKRAY = g_scrptConfig.CInfoScript::GetInfo("THAI_SAKRAY");
	if( szVersionTHAISAKRAY == NULL )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "cannot read the version of THAI_SAKRAY");
	g_nVersion[CLIENTTYPE_THAI_SAKRAY] = atoi(szVersionTHAISAKRAY);

	const char* szCLIENTCUTLINE = g_scrptConfig.CInfoScript::GetInfo("CLIENTCUTLINE");
	int clientcutline = ( szCLIENTCUTLINE != NULL ) ? atoi(szCLIENTCUTLINE) : 0;

	const char* szTIMEINTERVAL = g_scrptConfig.CInfoScript::GetInfo("TIMEINTERVAL");
	int timeinterval = ( szTIMEINTERVAL != NULL ) ? atoi(szTIMEINTERVAL) : 0;

	if( clientcutline != 0 && timeinterval != 0 )
		g_UserStreamMgr.CStreamManager::SetDOSCheck(clientcutline, timeinterval);

	g_scriptRestriction.CInfoScript::Open("account.connectionRestriction.txt");

	g_xmlFileUser.CInfoScript::Open("account.xmlFileUser.txt");

	const char* szXMLUSERCHECK = g_scrptConfig.CInfoScript::GetInfo("XML_FILE_USER_CHECK");
	bool g_bXmlFileUserCheck = ( szXMLUSERCHECK != NULL ) ? ( atoi(szXMLUSERCHECK) != 0 ) : false;

	const char* szDBPW = g_scrptConfig.CInfoScript::GetInfo("DBPW");
	if( szDBPW == NULL )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "Set Database Password! - DBPW Field(account.config.txt)");

	char dbpw[256] = {};
	Decrypt(szDBPW, (unsigned char*)dbpw);

	for( int i = 0; i < countof(g_AccountDB); ++i )
	{
		if( !g_AccountDB[i].CDatabase::Connect("account.dsn", dbpw) )
			CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "Not Connect AccountDB[%d]", i + 1);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "account DB %d connected", i + 1);
	}

	const char* szPCBANGDBPWD = g_scrptConfig.CInfoScript::GetInfo("PCBANGDB_PWD");
	if( szPCBANGDBPWD == NULL )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "%s(%d)\n (NULL == encrypt_pcbonuspw)", __FILE__, __LINE__);

	char pcbonuspw[256] = {};
	Decrypt(szPCBANGDBPWD, (unsigned char*)pcbonuspw);

	for( int i = 0; i < 5; ++i )
	{
		if( !CPCBangBillingDB::GetObj()->CDatabase::Connect("pcbonus.dsn", dbpw) ) //FIXME: using wrong password variable
			CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "Not Connect PCBang BillingDB[%d]", i + 1);
		CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "PCBONUS DB %d connected", i + 1);
	}

	if( !CGlobalInfoDB::GetObj()->CDatabase::Connect("global.dsn", dbpw) )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "Not Connect GlobalInfo");

	CGlobalInfoDB::GetObj()->CGlobalInfoDB::InitServerInfoList(false);

	CServerInfoList* pServerInfoList = CSingleton<CServerInfoList>::getSingletonPtr();
	int localSID = pServerInfoList->CServerInfoList::GetSID(CNetwork::GetObj()->CNetwork::GetLocalIP(true), SERVERTYPE_ACCOUNT);

	char szIP[100] = {};
	CNetwork::GetObj()->CNetwork::GetTextIP(CNetwork::GetObj()->CNetwork::GetLocalIP(true), szIP);
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s local SID - %d\n", szIP, localSID);

	g_LocalSID = localSID;

	SSERVERINFO serverInfo[20] = {};

	if( !CharServerInfo.CScriptParser::LoadFile("account.charserverset.txt") )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "Can't load account.charserverset.txt");

	int nCount = atoi(CharServerInfo.CScriptParser::GetItem("ServerCount", 0));
	for( int i = 0; i < nCount; ++i )
	{
		char buf[5];
		_snprintf_s(buf, sizeof(buf), _TRUNCATE, "SID%d", i);

		int nSID = atoi(CharServerInfo.CScriptParser::GetItem(buf, 1));
		pServerInfoList->CServerInfoList::GetServerInfo(&serverInfo[i], nSID);

		int nType = atoi(CharServerInfo.CScriptParser::GetItem(buf, 2));
		if( nType == 0 )
		{// free server
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[CLIENTTYPE_THAI]### %s", serverInfo[i].m_szName);
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[CLIENTTYPE_THAI_FREE]### %s", serverInfo[i].m_szName);
			g_characterServerInfo[CLIENTTYPE_THAI].CCharacterServerInfo::AddCharacterServerInfo(&serverInfo[i], SERVERSTATE_FREE);
			g_characterServerInfo[CLIENTTYPE_THAI_FREE].CCharacterServerInfo::AddCharacterServerInfo(&serverInfo[i], SERVERSTATE_FREE);
		}
		else
		{// normal server
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[CLIENTTYPE_THAI]### %s", serverInfo[i].m_szName);
			g_characterServerInfo[CLIENTTYPE_THAI].CCharacterServerInfo::AddCharacterServerInfo(&serverInfo[i], SERVERSTATE_NORMAL);
		}
	}

	GAME_ID = atoi(CharServerInfo.CScriptParser::GetItem("GAME_ID", 0));
	CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "GAME_ID %d", GAME_ID);

	Sleep(1000);

	/////////////////////////////////////////////////////////////////////////////
	const int ASYNCPROCESS_THREADS = 4;
	const int ASYNCPROCESS_POOL_COUNT = 100000;
	const int COMPLETIONPORT_THREADS = 3;

	g_AsyncProcessMgr.CAsyncProcessMgr::Create(ASYNCPROCESS_THREADS, ASYNCPROCESS_POOL_COUNT);
	g_compltport.CCompletionPort::Create(COMPLETIONPORT_THREADS);
	/////////////////////////////////////////////////////////////////////////////
	std::list<CProcess*> process_list;
	/////////////////////////////////////////////////////////////////////////////
	const int USER_NETWORK_BUFSIZE = 10000;
	const int USER_PROCESS_OBJ_NUM = 5000;

	if( !g_UserProcessFactory.CProcessFactory<CUserProcess>::CreateProcessList(&process_list, USER_PROCESS_OBJ_NUM) )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "g_UserProcessFactory.CreateProcessList failed");

	if( !g_UserStreamMgr.CStreamManager::Create(process_list, USER_NETWORK_BUFSIZE, USER_NETWORK_BUFSIZE, &g_compltport, false) )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "user stream mgr create error");
	/////////////////////////////////////////////////////////////////////////////
	process_list.clear();
	/////////////////////////////////////////////////////////////////////////////
	const int CHAR_NETWORK_BUFSIZE = 3000000;
	const int CHAR_PROCESS_OBJ_NUM = 30;

	if( !g_CharSvrProcessFactory.CProcessFactory<CCharSvrProcess>::CreateProcessList(&process_list, CHAR_PROCESS_OBJ_NUM) )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "g_CharSvrProcessFactory.CreateProcessList failed");

	if( !g_CharSvrStreamMgr.CStreamManager::Create(process_list, CHAR_NETWORK_BUFSIZE, CHAR_NETWORK_BUFSIZE, &g_compltport, true) )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "char stream mgr create failed");
	/////////////////////////////////////////////////////////////////////////////
	process_list.clear();
	/////////////////////////////////////////////////////////////////////////////
	const DWORD USER_IP = inet_addr("0.0.0.0");
	const WORD USER_PORT = 6900;

	if( !g_UserStreamMgr.CStreamManager::Listen(USER_PORT, 100, 60000, USER_IP) )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "user stream mgr listen error");

	const DWORD CHAR_IP = inet_addr("0.0.0.0");
	const WORD CHAR_PORT = 6800;

	if( !g_CharSvrStreamMgr.CStreamManager::Listen(CHAR_PORT, 10, 3600000, CHAR_IP) )
		CEnterTraceLog::GetObj()->CEnterTraceLog::FatalError(__FILE__, __LINE__, "char stream mgr listen failed");
	/////////////////////////////////////////////////////////////////////////////

	puts("## [Account] ready to accept clients ##");

	gbUpdateThreadRun = true;
	gbUpdateThreadEnd = false;
	_beginthread(&UpdateInfoThread, 0, NULL);

	return std::pair<bool,std::string>(true, "good");

}


void CAccountServerMgr::Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam)
{
	m_MessageQueue.NMessageQueue::Put(in_Msg, in_wParam, in_lParam);
}
