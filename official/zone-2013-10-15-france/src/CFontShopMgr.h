#pragma once
#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTAFile.h"
#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTALexicalAnalyzer.h"
#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTAToken.h"
class CPC;


class CFontShopMgr
{
private:
	/* static  */ static CFontShopMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //const CFontShopMgr::`vftable';
	/* this+ 4 */ bool m_bOK;
	typedef std::map<int,int> FONTLISTMAP;
	typedef std::map<int,int>::iterator FONTLISTMAP_ITER;
	/* this+ 8 */ FONTLISTMAP m_FontListMap;
	typedef std::map<int,int> FONT2ITIDMAP;
	typedef std::map<int,int>::iterator FONT2ITIDMAP_ITER;
	/* this+24 */ FONT2ITIDMAP m_Font2ITIDMap;

private:
	void ErrorMessageBox(const char* in_pFmt, ...);
	std::string GetTokenInfoStr(N2FTAToken& in_Token, N2FTAFile& in_ftFile);
	bool GetFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, N2FTAToken::enumTYPE in_ReqType);
	bool PeekFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, N2FTAToken::enumTYPE in_ReqType);
	bool Anaysis(const std::string in_strFileName);
	bool Create();

public:
	bool isOK() const;
	bool Change(CPC* in_cpPlayer, const int in_ITID);
	void Expire(CPC* in_cpPlayer, const int in_ITID);
	short GetValidFont(CPC* in_cpPlayer, const short in_font);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CFontShopMgr* GetObj(); ///@custom

private:
	CFontShopMgr();
	virtual ~CFontShopMgr();
};
