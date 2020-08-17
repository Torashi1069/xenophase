#include "MapTypePropertyMgr.h"
#include "Path.h"
#include "globals.hpp"


hook_ptr<CMapTypePropertyMgr*> CMapTypePropertyMgr::m_cpSelf(SERVER, "CMapTypePropertyMgr::m_cpSelf"); // = ?
hook_val<const mystd::string> CMapTypePropertyMgr::m_MapTypePropertyFileName(SERVER, "CMapTypePropertyMgr::m_MapTypePropertyFileName"); // = "MapTypeProperty.txt";


CMapTypePropertyMgr::CMapTypePropertyMgr(void) : m_DefaultProperty(-1)
{
	m_bOK = false;
	if( this->CMapTypePropertyMgr::Create() )
		m_bOK = true;
}


CMapTypePropertyMgr::~CMapTypePropertyMgr(void)
{
}


hook_method<bool (CMapTypePropertyMgr::*)(void)> CMapTypePropertyMgr::_Create(SERVER, "CMapTypePropertyMgr::Create");
HOOKED bool CMapTypePropertyMgr::Create(void)
{
//	return (this->*_Create)();

	char buf[256];
	GetPrivateProfileStringA("ZONE_PATH", "DATA_PATH", ".", buf, sizeof(buf), g_infFile);
	CPathData path;
	path.Init(buf);
	path.SetFileName(CMapTypePropertyMgr::m_MapTypePropertyFileName->c_str());

	return this->CMapTypePropertyMgr::Anaysis(path);
}


//hook_method<void (CMapTypePropertyMgr::*)(void)> CMapTypePropertyMgr::_Destroy(SERVER, "CMapTypePropertyMgr::Destroy");
void CMapTypePropertyMgr::Destroy(void)
{
//	return (this->*_Destroy)();

	;
}


hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, enum N2FTAToken::enumTYPE in_ReqType)> CMapTypePropertyMgr::_GetFTAToken(SERVER, "CMapTypePropertyMgr::GetFTAToken");
bool CMapTypePropertyMgr::GetFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, enum N2FTAToken::enumTYPE in_ReqType)
{
	return (this->*_GetFTAToken)(io_LexicalAnalyzer, io_Ret, in_ReqType);

	//TODO
}


hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, enum N2FTAToken::enumTYPE in_ReqType)> CMapTypePropertyMgr::_PeekFTAToken(SERVER, "CMapTypePropertyMgr::PeekFTAToken");
bool CMapTypePropertyMgr::PeekFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, enum N2FTAToken::enumTYPE in_ReqType)
{
	return (this->*_PeekFTAToken)(io_LexicalAnalyzer, io_Ret, in_ReqType);

	io_Ret = io_LexicalAnalyzer.N2FTALexicalAnalyzer::ViewToken();
	return( io_Ret.GetResult() == N2FTALexicalAnalyzer::FTARet::RETURNCODE_SUCCESS && io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken().GetType() == in_ReqType );
}


hook_method<bool (CMapTypePropertyMgr::*)(const mystd::string in_strFileName)> CMapTypePropertyMgr::_Anaysis(SERVER, "CMapTypePropertyMgr::Anaysis");
bool CMapTypePropertyMgr::Anaysis(const mystd::string in_strFileName)
{
	return (this->*_Anaysis)(in_strFileName);

	N2FTAFile ftFile(4);
	if( !ftFile.N2FTAFile::Load(in_strFileName) )
	{
		this->CMapTypePropertyMgr::ErrorMessageBox(in_strFileName, "Loading Error : %s", in_strFileName.c_str());
		return false;
	}

	N2FTALexicalAnalyzer LexicalAnalyzer(ftFile);
	if( !LexicalAnalyzer.N2FTALexicalAnalyzer::isOK() )
	{
		this->CMapTypePropertyMgr::ErrorMessageBox(in_strFileName, "Lexical Analyzer Initialize Error \n %s", in_strFileName.c_str());
		return false;
	}

	N2FTALexicalAnalyzer::FTARet Ret;
	while( !this->CMapTypePropertyMgr::PeekFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_EOF) )
	{
		if( !this->CMapTypePropertyMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_SYMBOL) )
			break;

		if( Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue() != N2FTAVar("MAPTYPE") )
			break;

		if( !this->CMapTypePropertyMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_NUMBER) )
			break;

		int value = Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();

		if( !this->CMapTypePropertyMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_LEFT_BRACE) )
			break;

		mystd::pair<mystd::map<int,CMapTypeProperty>::iterator, bool> insert_ret = m_MapTypePropertyContainer.insert(mystd::pair<int,CMapTypeProperty>(value, CMapTypeProperty(value)));
		if( !insert_ret.second )
		{// already in db
			this->CMapTypePropertyMgr::ErrorMessageBox(Ret.N2FTALexicalAnalyzer::FTARet::GetSourceFileName(), "insert container error");
			return false;
		}

		CMapTypeProperty& MapTypeProperty = insert_ret.first->second;

		while( !this->CMapTypePropertyMgr::PeekFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_RIGHT_BRACE) )
		{
			if( !this->CMapTypePropertyMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_SYMBOL) )
				break;

			bool retcode;

			if( Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue() == N2FTAVar("ADD_BLOCK_SKILL") )
				retcode = this->CMapTypePropertyMgr::Anaysis_ADD_BLOCK_SKILL(LexicalAnalyzer, MapTypeProperty, Ret);
			else
			if( Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue() == N2FTAVar("ADD_BLOCK_ITEM") )
				retcode = this->CMapTypePropertyMgr::Anaysis_ADD_BLOCK_ITEM(LexicalAnalyzer, MapTypeProperty, Ret);
			else
			if ( Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue() == N2FTAVar("ADD_PROPERTY") )
				retcode = this->CMapTypePropertyMgr::Anaysis_ADD_PROPERTY(LexicalAnalyzer, MapTypeProperty, Ret);
			else
			if ( Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue() == N2FTAVar("ADD_PROPERTY_VALUE") )
				retcode = this->CMapTypePropertyMgr::Anaysis_ADD_PROPERTY_VALUE(LexicalAnalyzer, MapTypeProperty, Ret);
			else
			if ( Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue() == N2FTAVar("ADJUST_TRAP_DURATION") )
				retcode = this->CMapTypePropertyMgr::Anaysis_ADJUST_TRAP_DURATION(LexicalAnalyzer, MapTypeProperty, Ret);
			else
			if ( Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue() == N2FTAVar("ADJUST_SKILL_DAMAGE") )
				retcode = this->CMapTypePropertyMgr::Anaysis_ADJUST_SKILL_DAMAGE(LexicalAnalyzer, MapTypeProperty, Ret);
			else
			if ( Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue() == N2FTAVar("ADD_BLOCK_EQUIPITEM") )
				retcode = this->CMapTypePropertyMgr::Anaysis_ADD_BLOCK_EQUIPITEM(LexicalAnalyzer, MapTypeProperty, Ret);
			else
			if ( Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue() == N2FTAVar("ADD_BLOCK_BUFF") )
				retcode = this->CMapTypePropertyMgr::Anaysis_ADD_BLOCK_BUFF(LexicalAnalyzer, MapTypeProperty, Ret);
			else
				break;

			if( !retcode )
				break;
		}

		if( !this->CMapTypePropertyMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_RIGHT_BRACE) )
			break;
	}

	if( !this->CMapTypePropertyMgr::PeekFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_EOF) )
	{
		N2FTAToken token = Ret.N2FTALexicalAnalyzer::FTARet::GetToken();
		const char* str = this->CMapTypePropertyMgr::GetTokenInfoStr(token, ftFile).c_str();
		this->CMapTypePropertyMgr::ErrorMessageBox(Ret.N2FTALexicalAnalyzer::FTARet::GetSourceFileName(), "syntax error \n %s", str);
		return false;
	}

	return true;
}


hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_BLOCK_SKILL(SERVER, "CMapTypePropertyMgr::Anaysis_ADD_BLOCK_SKILL");
bool CMapTypePropertyMgr::Anaysis_ADD_BLOCK_SKILL(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)
{
	return (this->*_Anaysis_ADD_BLOCK_SKILL)(io_LexicalAnalyzer, io_MapTypeProperty, io_Ret);

	//TODO
}


hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_BLOCK_ITEM(SERVER, "CMapTypePropertyMgr::Anaysis_ADD_BLOCK_ITEM");
bool CMapTypePropertyMgr::Anaysis_ADD_BLOCK_ITEM(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)
{
	return (this->*_Anaysis_ADD_BLOCK_ITEM)(io_LexicalAnalyzer, io_MapTypeProperty, io_Ret);

	//TODO
}


hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_PROPERTY(SERVER, "CMapTypePropertyMgr::Anaysis_ADD_PROPERTY");
bool CMapTypePropertyMgr::Anaysis_ADD_PROPERTY(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)
{
	return (this->*_Anaysis_ADD_PROPERTY)(io_LexicalAnalyzer, io_MapTypeProperty, io_Ret);

	//TODO
}


hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_PROPERTY_VALUE(SERVER, "CMapTypePropertyMgr::Anaysis_ADD_PROPERTY_VALUE");
bool CMapTypePropertyMgr::Anaysis_ADD_PROPERTY_VALUE(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)
{
	return (this->*_Anaysis_ADD_PROPERTY_VALUE)(io_LexicalAnalyzer, io_MapTypeProperty, io_Ret);

	//TODO
}


hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADJUST_TRAP_DURATION(SERVER, "CMapTypePropertyMgr::Anaysis_ADJUST_TRAP_DURATION");
bool CMapTypePropertyMgr::Anaysis_ADJUST_TRAP_DURATION(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)
{
	return (this->*_Anaysis_ADJUST_TRAP_DURATION)(io_LexicalAnalyzer, io_MapTypeProperty, io_Ret);

	//TODO
}


hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADJUST_SKILL_DAMAGE(SERVER, "CMapTypePropertyMgr::Anaysis_ADJUST_SKILL_DAMAGE");
bool CMapTypePropertyMgr::Anaysis_ADJUST_SKILL_DAMAGE(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)
{
	return (this->*_Anaysis_ADJUST_SKILL_DAMAGE)(io_LexicalAnalyzer, io_MapTypeProperty, io_Ret);

	//TODO
}


hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_BLOCK_EQUIPITEM(SERVER, "CMapTypePropertyMgr::Anaysis_ADD_BLOCK_EQUIPITEM");
bool CMapTypePropertyMgr::Anaysis_ADD_BLOCK_EQUIPITEM(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)
{
	return (this->*_Anaysis_ADD_BLOCK_EQUIPITEM)(io_LexicalAnalyzer, io_MapTypeProperty, io_Ret);

	//TODO
}


hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_BLOCK_BUFF(SERVER, "CMapTypePropertyMgr::Anaysis_ADD_BLOCK_BUFF");
bool CMapTypePropertyMgr::Anaysis_ADD_BLOCK_BUFF(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)
{
	return (this->*_Anaysis_ADD_BLOCK_BUFF)(io_LexicalAnalyzer, io_MapTypeProperty, io_Ret);

	//TODO
}


hook_method<void (CMapTypePropertyMgr::*)(mystd::string, const char *, ...)> CMapTypePropertyMgr::_ErrorMessageBox(SERVER, "CMapTypePropertyMgr::ErrorMessageBox");
void CMapTypePropertyMgr::ErrorMessageBox(mystd::string in_Title, const char* in_pFmt, ...)
{
//	return (this->*_ErrorMessageBox)(in_Title, in_pFmt, ...);

	va_list ap;
	va_start(ap, in_pFmt);

	char Buffer[2049];
	memset(Buffer, 0, sizeof(Buffer)-1);
	_vsnprintf(Buffer, sizeof(Buffer)-1, in_pFmt, ap);

	MessageBoxA(0, Buffer, in_Title.c_str(), 0);
}


hook_method<mystd::string (CMapTypePropertyMgr::*)(N2FTAToken& in_Token, N2FTAFile& in_ftFile)> CMapTypePropertyMgr::_GetTokenInfoStr(SERVER, "CMapTypePropertyMgr::GetTokenInfoStr");
mystd::string CMapTypePropertyMgr::GetTokenInfoStr(N2FTAToken& in_Token, N2FTAFile& in_ftFile)
{
	return (this->*_GetTokenInfoStr)(in_Token, in_ftFile);

	//TODO
}


hook_method<int (CMapTypePropertyMgr::*)(mystd::string in_SkillName)> CMapTypePropertyMgr::_GetSKID(SERVER, "CMapTypePropertyMgr::GetSKID");
int CMapTypePropertyMgr::GetSKID(mystd::string in_SkillName)
{
	return (this->*_GetSKID)(in_SkillName);

	//TODO
}


//hook_method<bool (CMapTypePropertyMgr::*)(void)> CMapTypePropertyMgr::_isOK(SERVER, "CMapTypePropertyMgr::isOK");
bool CMapTypePropertyMgr::isOK(void)
{
//	return (this->*_isOK)();

	return m_bOK;
}


hook_method<CMapTypeProperty& (CMapTypePropertyMgr::*)(const int in_MapType)> CMapTypePropertyMgr::_GetProperty(SERVER, "CMapTypePropertyMgr::GetProperty");
CMapTypeProperty& CMapTypePropertyMgr::GetProperty(const int in_MapType)
{
	return (this->*_GetProperty)(in_MapType);

	//TODO
}


hook_method<static bool (__cdecl *)(void)> CMapTypePropertyMgr::_CreateInstance(SERVER, "CMapTypePropertyMgr::CreateInstance");
bool CMapTypePropertyMgr::CreateInstance(void)
{
	return (CMapTypePropertyMgr::_CreateInstance)();

	//TODO
}


hook_method<static void (__cdecl *)(void)> CMapTypePropertyMgr::_DestroyInstance(SERVER, "CMapTypePropertyMgr::DestroyInstance");
void CMapTypePropertyMgr::DestroyInstance(void)
{
	return (CMapTypePropertyMgr::_DestroyInstance)();

	//TODO
}


/// @custom
CMapTypePropertyMgr* CMapTypePropertyMgr::GetObj(void)
{
	return m_cpSelf;
}
