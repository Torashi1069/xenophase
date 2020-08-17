#pragma once
#include "MapTypeProperty.h"


class CMapTypePropertyMgr
{
private:
	/* static  */ static CMapTypePropertyMgr*& m_cpSelf; //TODO
	/* static  */ static const std::string& m_MapTypePropertyFileName; //TODO
	/* this+ 0 */ //const CMapTypePropertyMgr::`vftable';
	/* this+ 4 */ bool m_bOK;
	typedef std::map<int,CMapTypeProperty> MAPTYPEPROPERTY_CONTAINER;
	typedef std::map<int,CMapTypeProperty>::iterator MAPTYPEPROPERTY_CONTAINER_ITER;
	/* this+ 8 */ MAPTYPEPROPERTY_CONTAINER m_MapTypePropertyContainer;
	/* this+24 */ CMapTypeProperty m_DefaultProperty;

private:
	bool Create();
	void Destroy();

private:
//	bool GetFTAToken(N2FTALexicalAnalyzer& , N2FTALexicalAnalyzer::FTARet& , N2FTAToken::enumTYPE );
//	bool PeekFTAToken(N2FTALexicalAnalyzer& , N2FTALexicalAnalyzer::FTARet& , N2FTAToken::enumTYPE );
	bool Anaysis(const std::string in_strFileName);
//	bool Anaysis_ADD_BLOCK_SKILL(N2FTALexicalAnalyzer& , CMapTypeProperty& , N2FTALexicalAnalyzer::FTARet& );
//	bool Anaysis_ADD_BLOCK_ITEM(N2FTALexicalAnalyzer& , CMapTypeProperty& , N2FTALexicalAnalyzer::FTARet& );
//	bool Anaysis_ADD_PROPERTY(N2FTALexicalAnalyzer& , CMapTypeProperty& , N2FTALexicalAnalyzer::FTARet& );
//	bool Anaysis_ADD_PROPERTY_VALUE(N2FTALexicalAnalyzer& , CMapTypeProperty& , N2FTALexicalAnalyzer::FTARet& );
//	bool Anaysis_ADJUST_TRAP_DURATION(N2FTALexicalAnalyzer& , CMapTypeProperty& , N2FTALexicalAnalyzer::FTARet& );
//	bool Anaysis_ADJUST_SKILL_DAMAGE(N2FTALexicalAnalyzer& , CMapTypeProperty& , N2FTALexicalAnalyzer::FTARet& );
//	bool Anaysis_ADD_BLOCK_EQUIPITEM(N2FTALexicalAnalyzer& , CMapTypeProperty& , N2FTALexicalAnalyzer::FTARet& );
//	bool Anaysis_ADD_BLOCK_BUFF(N2FTALexicalAnalyzer& , CMapTypeProperty& , N2FTALexicalAnalyzer::FTARet& );
//	void ErrorMessageBox(std::string , const char* , ...);
//	std::string GetTokenInfoStr(N2FTAToken& , N2FTAFile& );
//	int GetSKID(std::string );

public:
	bool isOK() const;
	CMapTypeProperty& GetProperty(const int in_MapType);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CMapTypePropertyMgr* GetObj(); /// @custom

private:
	CMapTypePropertyMgr();
	virtual ~CMapTypePropertyMgr();
};
