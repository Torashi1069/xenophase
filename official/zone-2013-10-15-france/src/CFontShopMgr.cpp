#include "CFontShopMgr.h"
#include "ITPMgr.h"
#include "Path.h"
#include "PC.h"
#include "Common/Packet.h"


/// singleton instance
CFontShopMgr*& CFontShopMgr::m_cpSelf = VTOR<CFontShopMgr*>(DetourFindFunction(EXEPATH(), "CFontShopMgr::m_cpSelf"));


CFontShopMgr::CFontShopMgr()
{
	m_bOK = false;

	if( this->CFontShopMgr::Create() )
		m_bOK = true;
}


CFontShopMgr::~CFontShopMgr()
{
}


bool CFontShopMgr::Create()
{
	if( !this->CFontShopMgr::Anaysis("FontShop.txt") )
		return false;

	return true;
}


bool CFontShopMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;
	
	m_cpSelf = new(std::nothrow) CFontShopMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->CFontShopMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void CFontShopMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


CFontShopMgr* CFontShopMgr::GetObj() ///@custom
{
	return m_cpSelf;
}


bool CFontShopMgr::isOK() const
{
	return m_bOK;
}


bool CFontShopMgr::Anaysis(const std::string in_strFileName)
{
	N2FTAFile ftFile(4);
	if( !ftFile.N2FTAFile::Load(g_pathData.CPathData::SetFileName(in_strFileName.c_str())) )
	{
		this->CFontShopMgr::ErrorMessageBox("Loading Error : %s", in_strFileName.c_str());
		return false;
	}

	N2FTALexicalAnalyzer LexicalAnalyzer(ftFile);
	if( !LexicalAnalyzer.N2FTALexicalAnalyzer::isOK() )
	{
		this->CFontShopMgr::ErrorMessageBox("Lexical Analyzer Initialize Error \n %s", in_strFileName.c_str());
		return false;
	}

	N2FTALexicalAnalyzer::FTARet Ret;
	while( 1 )
	{
		Ret = LexicalAnalyzer.N2FTALexicalAnalyzer::ViewToken();

		if( Ret.N2FTALexicalAnalyzer::FTARet::GetResult() == N2FTALexicalAnalyzer::FTARet::RETURNCODE_SUCCESS
		 && Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetType() == N2FTAToken::TYPE_EOF )
			return true; // done.

		if( !this->CFontShopMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_NUMBER) )
			break;

		int font_identity = Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();

		if( !this->CFontShopMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_COMMA) )
			break;

		if( !this->CFontShopMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_STRING) )
			break;

		std::string font_name = Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();

		if( !this->CFontShopMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_COMMA) )
			break;

		if( !this->CFontShopMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_NUMBER) )
			break;

		int item_id = Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();

		if( !this->CFontShopMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_COMMA) )
			break;

		if( !this->CFontShopMgr::GetFTAToken(LexicalAnalyzer, Ret, N2FTAToken::TYPE_STRING) )
			break;

		std::string item_name = Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetValue();

		CITP* itp = g_itpMgr.CITPMgr::GetITP(item_id);
		if( itp == NULL || strcmp(itp->m_name, item_name.c_str()) != 0 )
			break;

		std::pair<FONTLISTMAP_ITER,bool> insert_ret = m_FontListMap.insert(std::make_pair(item_id, font_identity));
		if( !insert_ret.second )
			break;

		std::pair<FONT2ITIDMAP_ITER,bool> f2i_insert_ret = m_Font2ITIDMap.insert(std::make_pair(font_identity, item_id));
		if( !f2i_insert_ret.second )
			break;
	}

	// error case
	this->CFontShopMgr::ErrorMessageBox("syntax error \n %s", this->CFontShopMgr::GetTokenInfoStr(Ret.N2FTALexicalAnalyzer::FTARet::GetToken(), ftFile).c_str());
	return false;
}


std::string CFontShopMgr::GetTokenInfoStr(N2FTAToken& in_Token, N2FTAFile& in_ftFile)
{
	char buffer[2048+1] = {};
	int numLine = in_Token.N2FTAToken::GetSourceFileLine();
	int numCol = in_Token.N2FTAToken::GetSourceFileCol();
	_snprintf(buffer, countof(buffer)-1, "file:%s(line:%d Col:%d)\n\n\n%3d:%s\n%3d:%s\n%3d:%s\n%3d:%s\n%3d:%s\n",
		in_Token.N2FTAToken::GetSourceFileName().c_str(), numLine, numCol,
		numLine - 2, in_ftFile.N2FTAFile::GetLineStr(numLine - 2).c_str(),
		numLine - 1, in_ftFile.N2FTAFile::GetLineStr(numLine - 1).c_str(),
		numLine    , in_ftFile.N2FTAFile::GetLineStr(numLine    ).c_str(),
		numLine + 1, in_ftFile.N2FTAFile::GetLineStr(numLine + 1).c_str(),
		numLine + 2, in_ftFile.N2FTAFile::GetLineStr(numLine + 2).c_str());
	return buffer;
}


bool CFontShopMgr::GetFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, N2FTAToken::enumTYPE in_ReqType)
{
	io_Ret = io_LexicalAnalyzer.N2FTALexicalAnalyzer::GetToken();

	if( io_Ret.N2FTALexicalAnalyzer::FTARet::GetResult() != N2FTALexicalAnalyzer::FTARet::RETURNCODE_SUCCESS )
		return false;

	if( io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetType() != in_ReqType )
		return false;

	return true;
}


bool CFontShopMgr::PeekFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, N2FTAToken::enumTYPE in_ReqType)
{
	io_Ret = io_LexicalAnalyzer.N2FTALexicalAnalyzer::ViewToken();

	if( io_Ret.N2FTALexicalAnalyzer::FTARet::GetResult() != N2FTALexicalAnalyzer::FTARet::RETURNCODE_SUCCESS )
		return false;

	if( io_Ret.N2FTALexicalAnalyzer::FTARet::GetToken().N2FTAToken::GetType() != in_ReqType )
		return false;

	return true;
}


void CFontShopMgr::ErrorMessageBox(const char* in_pFmt, ...)
{
	va_list va;
	va_start(va, in_pFmt);

	char Buffer[2048+1] = {};
	_vsnprintf(Buffer, countof(Buffer), in_pFmt, va);

	MessageBoxA(NULL, Buffer, "Font Shop", MB_OK);
}


bool CFontShopMgr::Change(CPC* in_cpPlayer, const int in_ITID)
{
	FONTLISTMAP_ITER iter = m_FontListMap.find(in_ITID);
	if( iter == m_FontListMap.end() )
		return false;

	short font = iter->second;
	if( font == in_cpPlayer->m_characterInfo.font )
		font = 0;

	in_cpPlayer->m_characterInfo.font = font;

	PACKET_ZC_NOTIFY_FONT packet = {};
	packet.PacketType = HEADER_ZC_NOTIFY_FONT;
	packet.AID = in_cpPlayer->GetAccountID();
	packet.font = in_cpPlayer->m_characterInfo.font;
	in_cpPlayer->Send(sizeof(packet), (char*)&packet);
	in_cpPlayer->CCharacter::MultiCast((char*)&packet, sizeof(packet));

	return true;
}


hook_func<void (__stdcall *)()> CFontShopMgr__Expire(EXEPATH(), "CFontShopMgr::Expire");
void CFontShopMgr::Expire(CPC* in_cpPlayer, const int in_ITID)
{
	void* hookptr = CFontShopMgr__Expire;
	__asm push in_ITID
	__asm push in_cpPlayer
	__asm push this
	__asm call hookptr
	return; //TODO
/*
	FONTLISTMAP_ITER iter = m_FontListMap.find(in_ITID);
	if( iter == m_FontListMap.end() )
		return;

	if( in_cpPlayer->m_characterInfo.font != iter->second )
		return;

	if( in_cpPlayer->m_pcitemInventoryMgr.CPCItemInventoryMgr::SearchItemByID(BODY, in_ITID) != NULL )
		return;

	in_cpPlayer->m_characterInfo.font = 0;

	PACKET_ZC_NOTIFY_FONT packet = {};
	packet.PacketType = HEADER_ZC_NOTIFY_FONT;
	packet.AID = in_cpPlayer->GetAccountID();
	packet.font = in_cpPlayer->m_characterInfo.font;
	in_cpPlayer->Send(sizeof(packet), (char*)&packet);
	in_cpPlayer->CCharacter::MultiCast((char*)&packet, sizeof(packet));
*/
}


hook_func<void (__stdcall *)()> CFontShopMgr__GetValidFont(EXEPATH(), "CFontShopMgr::GetValidFont");
short CFontShopMgr::GetValidFont(CPC* in_cpPlayer, const short in_font)
{
	short result;
	void* hookptr = CFontShopMgr__GetValidFont;
	__asm push in_font
	__asm push in_cpPlayer
	__asm push this
	__asm call hookptr
	__asm mov result, ax
	return result; //TODO
/*
	if( in_font == 0 )
		return 0;

	FONT2ITIDMAP_ITER iter = m_Font2ITIDMap.find(in_font);
	if( iter == m_Font2ITIDMap.end() )
		return 0;

	unsigned short ITID = iter->second;
	if( in_cpPlayer->m_pcitemInventoryMgr.CPCItemInventoryMgr::SearchItemByID(BODY, ITID) == NULL )
		return 0;

	return in_font;
*/
}
