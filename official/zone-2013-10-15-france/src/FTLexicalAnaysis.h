#pragma once
#include "FTFile.h"
#include "FTToken.h"


class CFTLexicalAnaysis : public CFTFile
{
private:
	/* this+ 0 */ //CFTfile baseclass_0;
	/* this+56 */ bool m_bOK;
	typedef std::vector<CFTToken> TOKENLIST;
	typedef std::vector<CFTToken>::iterator TOKENLISTITOR;
	/* this+60 */ TOKENLIST m_TokenList;
	/* this+76 */ TOKENLISTITOR m_CurReadyTokenItor;

private:
	class FTLARETURN
	{
	public:
		enum enumReturnCode
		{
			RETURNCODE_SUCCESS = 0,
			RETURNCODE_ERROR   = 1,
		};

	public:
		/* this+0 */ enumReturnCode m_Code;
		/* this+4 */ CFTToken m_Token;

	public:
		FTLARETURN(const enumReturnCode in_Code, CFTToken in_Token) : m_Code(in_Code), m_Token(in_Token) { }
		FTLARETURN(const enumReturnCode in_Code) : m_Code(in_Code) { }
	};

private:
	bool isNumeric(const char in_ch);
	bool isDelimiter(const char in_ch);
	int isLetter(const char in_ch);
	bool isAlpha(const char in_ch);

private:
	bool Init();
	FTLARETURN StringAnaysisV2();
	FTLARETURN SymbolAnaysisV2();
	FTLARETURN NumberAnaysisV2();
	FTLARETURN Anaysis();
	int RemoveComment();
	int RemoveGarbage();

public:
	bool isOK() const;
	bool GetToken(CFTToken& out_Token);
	bool ViewToken(CFTToken& out_Token);

public:
	CFTLexicalAnaysis(const std::string in_strFileName);
	virtual ~CFTLexicalAnaysis();
};
