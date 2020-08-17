#include "FTLexicalAnaysis.h"


CFTLexicalAnaysis::CFTLexicalAnaysis(const std::string in_strFileName)
: CFTFile(in_strFileName), m_bOK(false), m_TokenList(), m_CurReadyTokenItor()
{
	if( this->CFTFile::isOK() && this->CFTLexicalAnaysis::Init() )
		m_bOK = true;
}


CFTLexicalAnaysis::~CFTLexicalAnaysis()
{
}


bool CFTLexicalAnaysis::isOK() const
{
	return m_bOK;
}


CFTLexicalAnaysis::FTLARETURN CFTLexicalAnaysis::StringAnaysisV2()
{
	char ch = ' ';
	char PreviousReadCh = ' ';

	if( !this->CFTFile::ReadByte(ch) )
		return FTLARETURN(FTLARETURN::RETURNCODE_ERROR);

	if( ch != '"' )
		return FTLARETURN(FTLARETURN::RETURNCODE_ERROR);

	std::string Value = "";

	for( ; ; )
	{
		if( !this->CFTFile::ReadByte(ch) )
		{
			if( Value.size() == 0 )
				return FTLARETURN(FTLARETURN::RETURNCODE_ERROR);

			return FTLARETURN(FTLARETURN::RETURNCODE_SUCCESS, CFTToken(CFTToken::STRING, Value, this->CFTFile::GetCurLine(), this->CFTFile::GetCurCol()));
		}

		if( this->CFTLexicalAnaysis::isLetter(ch) == 2 )
		{
			Value += ch;

			if( !this->CFTFile::ReadByte(ch) )
				return FTLARETURN(FTLARETURN::RETURNCODE_ERROR);

			Value += ch;
			PreviousReadCh = ' ';
		}
		else
		if( ch == '"' )
		{
			if( PreviousReadCh != '\\' )
			{
				if( Value.size() == 0 )
					return FTLARETURN(FTLARETURN::RETURNCODE_ERROR);

				return FTLARETURN(FTLARETURN::RETURNCODE_SUCCESS, CFTToken(CFTToken::STRING, Value, this->CFTFile::GetCurLine(), this->CFTFile::GetCurCol()));
			}

			Value.erase(Value.size() - 1, 1);
			Value += ch;
			PreviousReadCh = ch;
		}
		else
		{
			Value += ch;
			PreviousReadCh = ch;
		}
	}
}


CFTLexicalAnaysis::FTLARETURN CFTLexicalAnaysis::SymbolAnaysisV2()
{
	std::string Value = "";
	char ch = ' ';

	for( ; ; )
	{
		if( !this->CFTFile::ReadByte(ch) )
		{
			break;
		}

		if( this->CFTLexicalAnaysis::isDelimiter(ch) )
		{
			this->CFTFile::UndoByte();
			break;
		}

		if( !this->CFTLexicalAnaysis::isNumeric(ch) && !this->CFTLexicalAnaysis::isAlpha(ch) )
		{
			this->CFTFile::UndoByte();
			break;
		}

		Value += ch;
	}

	if( Value.size() == 0 )
		return FTLARETURN(FTLARETURN::RETURNCODE_ERROR);

	return FTLARETURN(FTLARETURN::RETURNCODE_SUCCESS, CFTToken(CFTToken::SYMBOL, Value, this->CFTFile::GetCurLine(), this->CFTFile::GetCurCol()));
}


CFTLexicalAnaysis::FTLARETURN CFTLexicalAnaysis::NumberAnaysisV2()
{
	std::string Value = "";
	char ch = ' ';

	for( ; ; )
	{
		if( !this->CFTFile::ReadByte(ch) )
		{
			break;
		}

		if( this->CFTLexicalAnaysis::isDelimiter(ch) )
		{
			this->CFTFile::UndoByte();
			break;
		}

		if( !this->CFTLexicalAnaysis::isNumeric(ch) )
		{
			this->CFTFile::UndoByte();
			break;
		}

		Value += ch;
	}

	if( Value.size() == 0 )
		return FTLARETURN(FTLARETURN::RETURNCODE_ERROR);

	return FTLARETURN(FTLARETURN::RETURNCODE_SUCCESS, CFTToken(CFTToken::NUMBER, Value, this->CFTFile::GetCurLine(), this->CFTFile::GetCurCol()));
}


bool CFTLexicalAnaysis::Init()
{
	for( ; ; )
	{
		FTLARETURN Ret = this->CFTLexicalAnaysis::Anaysis();
		if( Ret.m_Code != FTLARETURN::RETURNCODE_SUCCESS )
		{
			if( m_TokenList.size() == 0 )
			{
				MessageBoxA(NULL, "\n==> found unknown token at first character <==", this->CFTFile::GetFileName().c_str(), MB_OK);
				return false;
			}

			std::vector<CFTToken> tempList;
			TOKENLISTITOR iter;
			int count;

			for( iter = m_TokenList.end(), count = 0; iter != m_TokenList.begin() && count < 10; --iter, ++count )
				tempList.push_back(*(iter - 1));

			std::string msg;
			for( TOKENLISTITOR iter = tempList.end(); iter != tempList.begin(); --iter )
			{
				CFTToken Token = *(iter - 1);

				char buffer[260] = {};
				_snprintf(buffer, countof(buffer), "\n%s(Line:%d,Col:%d)", Token.CFTToken::GetSTRING().c_str(), Token.CFTToken::GetLine(), Token.CFTToken::GetCol());

				msg += buffer;
			}

			msg += "\n==> found unknown token at next character <==";
			MessageBoxA(NULL, msg.c_str(), this->CFTFile::GetFileName().c_str(), MB_OK);
			return false;
		}

		m_TokenList.push_back(Ret.m_Token);

		if( Ret.m_Token.CFTToken::GetType() == CFTToken::EOF_ )
			break; // done.
	}

	m_CurReadyTokenItor = m_TokenList.begin();
	return true;
}


int CFTLexicalAnaysis::RemoveGarbage()
{
	static std::string SkipCharTable = " \r\n\t";

	char ch = ' ';
	if( !this->CFTFile::ReadByte(ch) )
		return -1;

	if( this->CFTLexicalAnaysis::isLetter(ch) || SkipCharTable.find(ch) == SkipCharTable.npos )
	{
		this->CFTFile::UndoByte();
		return 0;
	}

	return 1;
}


CFTLexicalAnaysis::FTLARETURN CFTLexicalAnaysis::Anaysis()
{
	for( ; ; )
	{
		if( this->CFTFile::isEOF() )
			return FTLARETURN(FTLARETURN::RETURNCODE_SUCCESS, CFTToken(CFTToken::EOF_, "EOF", this->CFTFile::GetCurLine(), this->CFTFile::GetCurCol()));

		int ret = this->CFTLexicalAnaysis::RemoveGarbage();
		if( ret == 0 )
		{
			ret = this->CFTLexicalAnaysis::RemoveComment();
			if( ret == 0 )
				break;
		}

		if( ret != 1 )
			return FTLARETURN(FTLARETURN::RETURNCODE_ERROR);
	}

	if( this->CFTFile::isEOF() )
		return FTLARETURN(FTLARETURN::RETURNCODE_SUCCESS, CFTToken(CFTToken::EOF_, "EOF", this->CFTFile::GetCurLine(), this->CFTFile::GetCurCol()));

	char ch = ' ';
	if( !this->CFTFile::ViewByte(ch) )
		return FTLARETURN(FTLARETURN::RETURNCODE_ERROR);

	if( ch == '"' )
		return this->CFTLexicalAnaysis::StringAnaysisV2();

	if( this->CFTLexicalAnaysis::isAlpha(ch) )
		return this->CFTLexicalAnaysis::SymbolAnaysisV2();

	if( this->CFTLexicalAnaysis::isNumeric(ch) )
		return this->CFTLexicalAnaysis::NumberAnaysisV2();

	if( IsDBCSLeadByte(ch) )
		return FTLARETURN(FTLARETURN::RETURNCODE_ERROR);

	if( ch == ',' )
	{
		this->CFTFile::ReadByte(ch);
		return FTLARETURN(FTLARETURN::RETURNCODE_SUCCESS, CFTToken(CFTToken::COMMA, ",", this->CFTFile::GetCurLine(), this->CFTFile::GetCurCol()));
	}
	else
	if( ch == '{' )
	{
		this->CFTFile::ReadByte(ch);
		return FTLARETURN(FTLARETURN::RETURNCODE_SUCCESS, CFTToken(CFTToken::LEFT_BRACE, "{", this->CFTFile::GetCurLine(), this->CFTFile::GetCurCol()));
	}
	else
	if( ch == '}' )
	{
		this->CFTFile::ReadByte(ch);
		return FTLARETURN(FTLARETURN::RETURNCODE_SUCCESS, CFTToken(CFTToken::RIGHT_BRACE, "}", this->CFTFile::GetCurLine(), this->CFTFile::GetCurCol()));
	}
	else
	{
		return FTLARETURN(FTLARETURN::RETURNCODE_ERROR);
	}
}


bool CFTLexicalAnaysis::ViewToken(CFTToken& out_Token)
{
	if( m_CurReadyTokenItor == m_TokenList.end() )
		return false;

	out_Token = *m_CurReadyTokenItor;
	return true;
}


bool CFTLexicalAnaysis::GetToken(CFTToken& out_Token)
{
	if( m_CurReadyTokenItor == m_TokenList.end() )
		return false;

	++m_CurReadyTokenItor;

	out_Token = *m_CurReadyTokenItor;
	return true;
}


bool CFTLexicalAnaysis::isDelimiter(const char in_ch)
{
	static std::string DelimiterTable = " \r\n\t";

	if( IsDBCSLeadByte(in_ch) )
		return false;

	return ( DelimiterTable.find(in_ch) != DelimiterTable.npos );
}


bool CFTLexicalAnaysis::isNumeric(const char in_ch)
{
	static std::string NumericTable = "0123456789.+-";

	if( IsDBCSLeadByte(in_ch) )
		return false;

	return ( NumericTable.find(in_ch) != NumericTable.npos );
}


int CFTLexicalAnaysis::isLetter(const char in_ch)
{
	if( IsDBCSLeadByte(in_ch) )
		return 2;

	return ( this->CFTLexicalAnaysis::isAlpha(in_ch) );
}


bool CFTLexicalAnaysis::isAlpha(const char in_ch)
{
	static std::string AlphaTable = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

	if( IsDBCSLeadByte(in_ch) )
		return false;

	return ( AlphaTable.find(in_ch) != AlphaTable.npos );
}


int CFTLexicalAnaysis::RemoveComment()
{
	char ch = ' ';
	if( !this->CFTFile::ReadByte(ch) )
		return -1;

	if( IsDBCSLeadByte(ch) || ch != '/' || !this->CFTFile::ReadByte(ch) )
	{
		this->CFTFile::UndoByte();
		return 0;
	}

	if( this->CFTLexicalAnaysis::isLetter(ch) )
	{
		this->CFTFile::UndoByte();
		this->CFTFile::UndoByte();
		return 0;
	}

	if( ch == '/' )
	{
		while( !this->CFTFile::isEOF() )
		{
			if( !this->CFTFile::ReadByte(ch) )
				return -1;

			if( IsDBCSLeadByte(ch) )
			{
				if( !this->CFTFile::ReadByte(ch) )
					return -1;
			}
			else
			{
				if( ch == '\r' || ch == '\n' )
					return 1;
			}
		}

		return 1;
	}
	else
	if( ch == '*' )
	{
		bool bCloseStart = false;
		while( this->CFTFile::ReadByte(ch) )
		{
			if( IsDBCSLeadByte(ch) )
			{
				bCloseStart = false;
				if( !this->CFTFile::ReadByte(ch) )
					return -1;
			}
			else
			{
				if( ch == '*' )
				{
					bCloseStart = true;
				}
				else
				if( ch == '/' )
				{
					if( bCloseStart == true )
						return 1;
				}
			}
		}

		return -1;
	}
	else
	{
		this->CFTFile::UndoByte();
		return 0;
	}
}
