#pragma once
#include "N2System/FTA(Formated Text Analyzer)/N2FTAFile.h"
#include "N2System/FTA(Formated Text Analyzer)/N2FTALexicalAnalyzer.h"
#include "N2System/FTA(Formated Text Analyzer)/N2FTAToken.h"
#include "std/map"


class CFontShopMgr
{
public:
	/* this+0x0  */ //const CFontShopMgr::`vftable'
	/* static    */ private: static hook_ptr<CFontShopMgr *> m_cpSelf;
	/* this+0x4  */ private: bool m_bOK;
	/* this+0x8  */ private: mystd::map<int,int> m_FontListMap;
	/* this+0x14 */ private: mystd::map<int,int> m_Font2ITIDMap;

	private: CFontShopMgr::CFontShopMgr(void);
	private: virtual CFontShopMgr::~CFontShopMgr(void);
	public: static bool __cdecl CFontShopMgr::CreateInstance(void);
	public: static void __cdecl CFontShopMgr::DestroyInstance(void);
	//private: void CFontShopMgr::ErrorMessageBox(const char *, <NoType>);
	//private: mystd::string CFontShopMgr::GetTokenInfoStr(N2FTAToken &, N2FTAFile &);
	//private: bool CFontShopMgr::GetFTAToken(N2FTALexicalAnalyzer &, N2FTALexicalAnalyzer::FTARet &, enum N2FTAToken::enumTYPE);
	//private: bool CFontShopMgr::PeekFTAToken(N2FTALexicalAnalyzer &, N2FTALexicalAnalyzer::FTARet &, enum N2FTAToken::enumTYPE);
	//private: bool CFontShopMgr::Anaysis(const mystd::string);
	private: bool CFontShopMgr::Create(void);
	//public: bool CFontShopMgr::isOK();
	//public: bool CFontShopMgr::Change(CPC *, const int);
	//public: void CFontShopMgr::Expire(CPC *, const int);
	//public: short CFontShopMgr::GetValidFont(CPC *, const short);

private:
	static hook_method<static bool (__cdecl *)(void)> CFontShopMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CFontShopMgr::_DestroyInstance;
	static hook_method<bool (CFontShopMgr::*)(void)> CFontShopMgr::_Create;
};
