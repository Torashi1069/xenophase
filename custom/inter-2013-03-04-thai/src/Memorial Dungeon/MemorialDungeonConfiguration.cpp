#include "InterServer.h" // g_infFile
#include "Instant Map/InstantMapConfiguration.h"
#include "Memorial Dungeon/MemorialDungeonConfiguration.h"


/// singleton instance
CMemorialDungeonConfiguration*& CMemorialDungeonConfiguration::m_cpSelf = VTOR<CMemorialDungeonConfiguration*>(DetourFindFunction(EXEPATH(), "CMemorialDungeonConfiguration::m_cpSelf"));
const std::string& CMemorialDungeonConfiguration::m_szConfigFileName = VTOR<const std::string>(DetourFindFunction(EXEPATH(), "CMemorialDungeonConfiguration::m_szConfigFileName")); // = "MemorialDungeonConfiguration.txt";


CMemorialDungeonConfiguration::CMemorialDungeonConfiguration()
: m_MemorialDungeonContainer(),
  m_EnterLimitMinute(5),
  m_bDataBaseLogOutput(false),
  m_SubscriptionMinimumDelaySecond(60),
  m_under_zsvr_memory_mbytes(1800),
  m_bOpen(true)
{
	m_bOK = false;

	if( this->CMemorialDungeonConfiguration::Create() )
		m_bOK = true;
}


CMemorialDungeonConfiguration::~CMemorialDungeonConfiguration()
{
	this->CMemorialDungeonConfiguration::Destroy();
}


bool CMemorialDungeonConfiguration::Create()
{
	m_EnterLimitMinute = GetPrivateProfileIntA("MEMORIAL DUNGEON", "enter limit minute", 5, g_infFile);
	m_SubscriptionMinimumDelaySecond = GetPrivateProfileIntA("MEMORIAL DUNGEON", "subscription minimum delay second", 60, g_infFile);
	m_bDataBaseLogOutput = ( GetPrivateProfileIntA("MEMORIAL DUNGEON", "database log output", 0, g_infFile) != 0 );
	m_bOpen = ( GetPrivateProfileIntA("MEMORIAL DUNGEON", "open", 1, g_infFile) != 0 );
	m_under_zsvr_memory_mbytes = GetPrivateProfileIntA("MEMORIAL DUNGEON", "under zone server memory(Mbytes)", 1800, g_infFile);

	return this->CMemorialDungeonConfiguration::Anaysis(m_szConfigFileName);
}


bool CMemorialDungeonConfiguration::IsOpen()
{
	return ( m_bOpen && CInstantMapConfiguration::GetObj()->CInstantMapConfiguration::IsOpen() );
}


bool CMemorialDungeonConfiguration::Anaysis_Dungeon(N2FTAFile& in_ftFile, N2FTALexicalAnalyzer& in_LexicalAnalyzer, LCMemorialDungeon& io_Dungeon, N2FTALexicalAnalyzer::FTARet& io_Ret)
{
	while( !this->CMemorialDungeonConfiguration::PeekFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_RIGHT_BRACE) )
	{
		if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_SYMBOL) )
			return false;

		N2FTAVar Var = io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();

		if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_EQUAL) )
			return false;

		if( Var == std::string("map") )
		{
			if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_STRING) )
				return false;

			N2FTAVar MapName = io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();

			if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_COMMA) )
				return false;

			if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_NUMBER) )
				return false;

			N2FTAVar Type = io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();

			io_Dungeon.m_MapList.push_back(CMemorialDungeonConfiguration::LCMemorialDungeon::lcInstantMap(MapName, Type));
		}
		else
		if( Var == std::string("live_time_minute") )
		{
			if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_NUMBER) )
				return false;

			io_Dungeon.m_LiveTimeMinute = io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();
		}
		else
		if( Var == std::string("place_with_map") )
		{
			if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_STRING) )
				return false;

			io_Dungeon.m_strPlaceWithMap = io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();
		}
		else
		if( Var == std::string("enter") )
		{
			if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_STRING) )
				return false;

			N2FTAVar EnterMapName = io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();

			if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_COMMA) )
				return false;

			if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_NUMBER) )
				return false;

			N2FTAVar EnterXPos = io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();

			if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_COMMA) )
				return false;

			if( !this->CMemorialDungeonConfiguration::GetFTAToken(in_LexicalAnalyzer, io_Ret, N2FTAToken::TYPE_NUMBER) )
				return false;

			N2FTAVar EnterYPos = io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();

			io_Dungeon.m_Enter.PhysicalMapName = EnterMapName;
			io_Dungeon.m_Enter.X = EnterXPos;
			io_Dungeon.m_Enter.Y = EnterYPos;
		}
		else
		{
			return false;
		}
	}

	return true;
}


void CMemorialDungeonConfiguration::ErrorMessageBox(const char* in_pFmt, ...)
{
	va_list va;
	va_start(va, in_pFmt);

	char Buffer[2048+1] = {};
	_vsnprintf(Buffer, countof(Buffer) - 1, in_pFmt, va);

	printf("Memorial Dungeon : %s", Buffer);
}


std::string CMemorialDungeonConfiguration::GetTokenInfoStr(N2FTAToken& in_Token, N2FTAFile& in_ftFile)
{
	char buffer[2048+1] = {};
	_snprintf(buffer, countof(buffer) - 1, "file:%s(line:%d Col:%d)\n\n\n%3d:%s\n%3d:%s\n%3d:%s\n%3d:%s\n%3d:%s\n",
		in_Token.N2FTAToken::GetSourceFileName().c_str(), in_Token.N2FTAToken::GetSourceFileLine(), in_Token.N2FTAToken::GetSourceFileCol(),
		in_Token.N2FTAToken::GetSourceFileLine() - 2, in_ftFile.N2FTAFile::GetLineStr(in_Token.N2FTAToken::GetSourceFileLine() - 2).c_str(),
		in_Token.N2FTAToken::GetSourceFileLine() - 1, in_ftFile.N2FTAFile::GetLineStr(in_Token.N2FTAToken::GetSourceFileLine() - 1).c_str(),
		in_Token.N2FTAToken::GetSourceFileLine()    , in_ftFile.N2FTAFile::GetLineStr(in_Token.N2FTAToken::GetSourceFileLine()    ).c_str(),
		in_Token.N2FTAToken::GetSourceFileLine() + 1, in_ftFile.N2FTAFile::GetLineStr(in_Token.N2FTAToken::GetSourceFileLine() + 1).c_str(),
		in_Token.N2FTAToken::GetSourceFileLine() + 2, in_ftFile.N2FTAFile::GetLineStr(in_Token.N2FTAToken::GetSourceFileLine() + 2).c_str());
	return buffer;
}


bool CMemorialDungeonConfiguration::GetFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, N2FTAToken::enumTYPE in_ReqType)
{
	io_Ret = io_LexicalAnalyzer.N2FTALexicalAnalyzer::GetToken();
	if( io_Ret.N2FTALexicalAnalyzer::FTARet::GetResult() != N2FTALexicalAnalyzer::FTARet::RETURNCODE_SUCCESS )
		return false;

	N2FTAToken Token = io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken();
	if( Token.N2FTAToken::GetType() != in_ReqType )
		return false;

	return true;
}


bool CMemorialDungeonConfiguration::PeekFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, N2FTAToken::enumTYPE in_ReqType)
{
	io_Ret = io_LexicalAnalyzer.N2FTALexicalAnalyzer::ViewToken();
	if( io_Ret.N2FTALexicalAnalyzer::FTARet::GetResult() != N2FTALexicalAnalyzer::FTARet::RETURNCODE_SUCCESS )
		return false;

	N2FTAToken Token = io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken();
	if( Token.N2FTAToken::GetType() != in_ReqType )
		return false;

	return true;
}


bool CMemorialDungeonConfiguration::Anaysis(const std::string in_strFileName)
{
	N2FTAFile ftFile(4);
	if( !ftFile.N2FTAFile::Load(m_szConfigFileName) )
	{
		this->CMemorialDungeonConfiguration::ErrorMessageBox("Loading Error : %s", m_szConfigFileName.c_str());
		return false;
	}

	N2FTALexicalAnalyzer io_LexicalAnalyzer(ftFile);
	if( !io_LexicalAnalyzer.N2FTALexicalAnalyzer::isOK() )
	{
		this->CMemorialDungeonConfiguration::ErrorMessageBox("Lexical Analyzer Initialize Error \n %s", m_szConfigFileName.c_str());
		return false;
	}

	N2FTALexicalAnalyzer::FTARet Ret;
	while( !this->CMemorialDungeonConfiguration::PeekFTAToken(io_LexicalAnalyzer, Ret, N2FTAToken::TYPE_EOF) )
	{
		if( !this->CMemorialDungeonConfiguration::GetFTAToken(io_LexicalAnalyzer, Ret, N2FTAToken::TYPE_STRING) )
		{
			this->CMemorialDungeonConfiguration::ErrorMessageBox("syntax error \n %s", this->CMemorialDungeonConfiguration::GetTokenInfoStr(Ret.N2FTALexicalAnalyzer::FTARet::GetToken(), ftFile).c_str());
			return false;
		}

		LCMemorialDungeon TempMemorialDungeon(Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue());
		if( !this->CMemorialDungeonConfiguration::GetFTAToken(io_LexicalAnalyzer, Ret, N2FTAToken::TYPE_LEFT_BRACE)
		 || !this->CMemorialDungeonConfiguration::Anaysis_Dungeon(ftFile, io_LexicalAnalyzer, TempMemorialDungeon, Ret)
		 || !this->CMemorialDungeonConfiguration::GetFTAToken(io_LexicalAnalyzer, Ret, N2FTAToken::TYPE_RIGHT_BRACE) )
		{
			this->CMemorialDungeonConfiguration::ErrorMessageBox("syntax error \n %s", this->CMemorialDungeonConfiguration::GetTokenInfoStr(Ret.N2FTALexicalAnalyzer::FTARet::GetToken(), ftFile).c_str());
			return false;
		}

		std::pair<MEMORIAL_DUNGEON_CONTAINER_ITER,bool> insert_ret = m_MemorialDungeonContainer.insert(std::make_pair(TempMemorialDungeon.m_strName, TempMemorialDungeon));
		if( !insert_ret.second )
		{
			this->CMemorialDungeonConfiguration::ErrorMessageBox("memorial dungeon container insert error");
			return false;
		}
	}

	return true;
}


void CMemorialDungeonConfiguration::Destroy()
{
}


bool CMemorialDungeonConfiguration::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new CMemorialDungeonConfiguration();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CMemorialDungeonConfiguration::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CMemorialDungeonConfiguration::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CMemorialDungeonConfiguration* CMemorialDungeonConfiguration::GetObj() /// @custom
{
	return m_cpSelf;
}


const bool CMemorialDungeonConfiguration::isOK() const
{
	return m_bOK;
}


CMemorialDungeonConfiguration::LCMemorialDungeon* CMemorialDungeonConfiguration::GetConfigurationPtr(const std::string in_Name)
{
	MEMORIAL_DUNGEON_CONTAINER_ITER iter = m_MemorialDungeonContainer.find(in_Name);
	return ( iter != m_MemorialDungeonContainer.end() ) ? &iter->second : NULL;
}


unsigned long CMemorialDungeonConfiguration::GetEnterLimitMinute() const
{
	return m_EnterLimitMinute;
}


unsigned long CMemorialDungeonConfiguration::GetSubscriptionMinimumDelaySecond() const
{
	return m_SubscriptionMinimumDelaySecond;
}


unsigned int CMemorialDungeonConfiguration::Get_under_zsvr_memory_mbytes() const
{
	return m_under_zsvr_memory_mbytes;
}


bool CMemorialDungeonConfiguration::IsDBLogOutput() const
{
	return m_bDataBaseLogOutput;
}
