#pragma once
#include "MapTypeProperty.h"
#include "N2System/FTA(Formated Text Analyzer)/N2FTAFile.h"
#include "N2System/FTA(Formated Text Analyzer)/N2FTALexicalAnalyzer.h"
#include "N2System/FTA(Formated Text Analyzer)/N2FTAToken.h"
#include "N2System/FTA(Formated Text Analyzer)/N2FTAVar.h"
#include "std/map"
#include "std/string"


class CMapTypePropertyMgr
{
public:
	/* this+ 0 */ public: //const CMapTypePropertyMgr::`vftable';
	/* static  */ private: static hook_ptr<CMapTypePropertyMgr *> m_cpSelf;
	/* static  */ private: static hook_val<const mystd::string> m_MapTypePropertyFileName;
	/* this+ 4 */ private: bool m_bOK;
	/* this+ 8 */ private: mystd::map<int,CMapTypeProperty> m_MapTypePropertyContainer;
	/* this+20 */ private: CMapTypeProperty m_DefaultProperty;

	private: CMapTypePropertyMgr::CMapTypePropertyMgr(void);
	private: virtual CMapTypePropertyMgr::~CMapTypePropertyMgr(void);
	private: bool CMapTypePropertyMgr::Create(void);
	private: void CMapTypePropertyMgr::Destroy(void);
	private: bool CMapTypePropertyMgr::GetFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, enum N2FTAToken::enumTYPE in_ReqType);
	private: bool CMapTypePropertyMgr::PeekFTAToken(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, enum N2FTAToken::enumTYPE in_ReqType);
	private: bool CMapTypePropertyMgr::Anaysis(const mystd::string in_strFileName);
	private: bool CMapTypePropertyMgr::Anaysis_ADD_BLOCK_SKILL(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret);
	private: bool CMapTypePropertyMgr::Anaysis_ADD_BLOCK_ITEM(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret);
	private: bool CMapTypePropertyMgr::Anaysis_ADD_PROPERTY(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret);
	private: bool CMapTypePropertyMgr::Anaysis_ADD_PROPERTY_VALUE(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret);
	private: bool CMapTypePropertyMgr::Anaysis_ADJUST_TRAP_DURATION(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret);
	private: bool CMapTypePropertyMgr::Anaysis_ADJUST_SKILL_DAMAGE(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret);
	private: bool CMapTypePropertyMgr::Anaysis_ADD_BLOCK_EQUIPITEM(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret);
	private: bool CMapTypePropertyMgr::Anaysis_ADD_BLOCK_BUFF(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret);
	private: void CMapTypePropertyMgr::ErrorMessageBox(mystd::string, const char *, ...);
	private: mystd::string CMapTypePropertyMgr::GetTokenInfoStr(N2FTAToken& in_Token, N2FTAFile& in_ftFile);
	private: int CMapTypePropertyMgr::GetSKID(mystd::string in_SkillName);
	public: bool CMapTypePropertyMgr::isOK(void);
	public: CMapTypeProperty& CMapTypePropertyMgr::GetProperty(const int in_MapType);
	public: static bool CMapTypePropertyMgr::CreateInstance(void);
	public: static void CMapTypePropertyMgr::DestroyInstance(void);
	public: static CMapTypePropertyMgr* CMapTypePropertyMgr::GetObj(void);

private:
	static hook_method<bool (CMapTypePropertyMgr::*)(void)> CMapTypePropertyMgr::_Create;
	static hook_method<void (CMapTypePropertyMgr::*)(void)> CMapTypePropertyMgr::_Destroy;
	static hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, enum N2FTAToken::enumTYPE in_ReqType)> CMapTypePropertyMgr::_GetFTAToken;
	static hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, N2FTALexicalAnalyzer::FTARet& io_Ret, enum N2FTAToken::enumTYPE in_ReqType)> CMapTypePropertyMgr::_PeekFTAToken;
	static hook_method<bool (CMapTypePropertyMgr::*)(const mystd::string in_strFileName)> CMapTypePropertyMgr::_Anaysis;
	static hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_BLOCK_SKILL;
	static hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_BLOCK_ITEM;
	static hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_PROPERTY;
	static hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_PROPERTY_VALUE;
	static hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADJUST_TRAP_DURATION;
	static hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADJUST_SKILL_DAMAGE;
	static hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_BLOCK_EQUIPITEM;
	static hook_method<bool (CMapTypePropertyMgr::*)(N2FTALexicalAnalyzer& io_LexicalAnalyzer, CMapTypeProperty& io_MapTypeProperty, N2FTALexicalAnalyzer::FTARet& io_Ret)> CMapTypePropertyMgr::_Anaysis_ADD_BLOCK_BUFF;
	static hook_method<void (CMapTypePropertyMgr::*)(mystd::string, const char *, ...)> CMapTypePropertyMgr::_ErrorMessageBox;
	static hook_method<mystd::string (CMapTypePropertyMgr::*)(N2FTAToken& in_Token, N2FTAFile& in_ftFile)> CMapTypePropertyMgr::_GetTokenInfoStr;
	static hook_method<int (CMapTypePropertyMgr::*)(mystd::string in_SkillName)> CMapTypePropertyMgr::_GetSKID;
	static hook_method<bool (CMapTypePropertyMgr::*)(void)> CMapTypePropertyMgr::_isOK;
	static hook_method<CMapTypeProperty& (CMapTypePropertyMgr::*)(const int in_MapType)> CMapTypePropertyMgr::_GetProperty;
	static hook_method<static bool (__cdecl *)(void)> CMapTypePropertyMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CMapTypePropertyMgr::_DestroyInstance;
};
