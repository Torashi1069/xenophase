#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTALexicalAnalyzer.h"


N2FTALexicalAnalyzer::N2FTALexicalAnalyzer(N2FTAFile& in_SourceFile)
: m_SourceFile(in_SourceFile)
{
	m_bOK = true;
}


N2FTALexicalAnalyzer::~N2FTALexicalAnalyzer()
{
}


const bool N2FTALexicalAnalyzer::isOK() const
{
	return m_bOK;
}


N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::GetToken()
{
	if( m_Container.size() != 0 )
	{
		FTARet ret = m_Container.front();
		m_Container.pop_front();
		return ret;
	}
	else
	{
		return this->N2FTALexicalAnalyzer::Anaysis();
	}
}


N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::ViewToken()
{
	if( m_Container.size() == 0 )
	{
		FTARet ret = this->N2FTALexicalAnalyzer::Anaysis();
		m_Container.push_back(ret);
	}

	return m_Container.front();
}


const int N2FTALexicalAnalyzer::GetLine()
{
	return m_SourceFile.N2FTAFile::GetLine();
}


const std::string N2FTALexicalAnalyzer::GetLineStr(const int in_Line)
{
	return m_SourceFile.N2FTAFile::GetLineStr(in_Line);
}


int N2FTALexicalAnalyzer::isLetter(const char in_ch)
{
	if( IsDBCSLeadByte(in_ch) == TRUE )
		return 2;

	return ( this->N2FTALexicalAnalyzer::isAlpha(in_ch) == true );
}


bool N2FTALexicalAnalyzer::isAlpha(const char in_ch)
{
	static std::string AlphaTable = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	if( IsDBCSLeadByte(in_ch) )
		return false;

	return ( AlphaTable.find(in_ch) != AlphaTable.npos );
}


bool N2FTALexicalAnalyzer::isDelimiter(const char in_ch)
{
	static std::string DelimiterTable = " \r\n\t";
	if( IsDBCSLeadByte(in_ch) )
		return false;

	return ( DelimiterTable.find(in_ch) != DelimiterTable.npos );
}


bool N2FTALexicalAnalyzer::isNumeric(const char in_ch)
{
	static std::string NumericTable = "0123456789.+-";
	if( IsDBCSLeadByte(in_ch) )
		return false;

	return ( NumericTable.find(in_ch) != NumericTable.npos );
}


int N2FTALexicalAnalyzer::RemoveGarbage()
{
	static std::string SkipCharTable = " \r\n\t";

	char ch = ' ';
	if( !m_SourceFile.N2FTAFile::ViewByte(ch) )
		return -1;

	if( this->N2FTALexicalAnalyzer::isLetter(ch) || SkipCharTable.find(ch) == SkipCharTable.npos )
		return 0;

	m_SourceFile.N2FTAFile::GetByte(ch);
	return 1;
}


int N2FTALexicalAnalyzer::RemoveComment()
{
	char ch = ' ';
	if( !m_SourceFile.N2FTAFile::ViewByte(ch) )
		return -1;

	if( this->N2FTALexicalAnalyzer::isLetter(ch) )
		return 0;

	if( ch != '/' )
		return 0;

	if( !m_SourceFile.N2FTAFile::ViewByte(ch, m_SourceFile.N2FTAFile::GetCurIdx() + 1) )
		return 0; // no more data

	if( this->N2FTALexicalAnalyzer::isLetter(ch) )
		return 0;

	if( ch == '/' )
	{// parse single-line comment
		if( !m_SourceFile.N2FTAFile::GetByte(ch) )
			return -1;
		if( !m_SourceFile.N2FTAFile::GetByte(ch) )
			return -1;

		while( 1 )
		{
			if( m_SourceFile.N2FTAFile::isEOF() == true )
				break;

			if( !m_SourceFile.N2FTAFile::GetByte(ch) )
				return -1;

			if( IsDBCSLeadByte(ch) )
			{
				if( !m_SourceFile.N2FTAFile::GetByte(ch) )
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
	{// parse multi-line comment
		if( !m_SourceFile.N2FTAFile::GetByte(ch) )
			return -1;
		if( !m_SourceFile.N2FTAFile::GetByte(ch) )
			return -1;

		bool bClosingTag = false;
		while( 1 )
		{
			if( !m_SourceFile.N2FTAFile::GetByte(ch) )
				return -1;

			if( IsDBCSLeadByte(ch) )
			{
				bClosingTag = false;

				if( !m_SourceFile.N2FTAFile::GetByte(ch) )
					return -1;
				if( !m_SourceFile.N2FTAFile::GetByte(ch) )
					return -1;
			}
			else
			if( ch == '*' )
			{
				bClosingTag = true;
			}
			else
			if( ch == '/' )
			{
				if( bClosingTag == true )
					break;
			}
		}

		return 1;
	}
	else
	{
		return -1;
	}
}


N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::Anaysis()
{
	while( 1 )
	{
		if( m_SourceFile.N2FTAFile::isEOF() == true )
			return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_EOF, N2FTAVar("EOF"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));

		int retG = this->N2FTALexicalAnalyzer::RemoveGarbage();
		if( retG != 0 )
		{
			if( retG != 1 )
				return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());

			continue;
		}

		int retC = this->N2FTALexicalAnalyzer::RemoveComment();
		if( retC != 0 )
		{
			if( retC != 1 )
				return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());

			continue;
		}

		break;
	};
	
	if( m_SourceFile.N2FTAFile::isEOF() == true )
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_EOF, N2FTAVar("EOF"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));

	char ch = ' ';
	if( !m_SourceFile.N2FTAFile::ViewByte(ch) )
		return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());

	if( ch == '"' )
		return this->N2FTALexicalAnalyzer::StringAnaysis();

	if( this->N2FTALexicalAnalyzer::isAlpha(ch) == true )
		return this->N2FTALexicalAnalyzer::SymbolAnaysis();

	if( this->N2FTALexicalAnalyzer::isNumeric(ch) == true )
		return this->N2FTALexicalAnalyzer::NumberAnaysis();

	if( IsDBCSLeadByte(ch) )
		return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());

	switch( ch )
	{
	case '=':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_EQUAL, N2FTAVar("="), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '!':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_NOT, N2FTAVar("!"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '&':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_AND, N2FTAVar("&"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '|':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_OR, N2FTAVar("|"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '+':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_ADD, N2FTAVar("+"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '-':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_SUB, N2FTAVar("-"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '*':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_MUL, N2FTAVar("*"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '/':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_DIV, N2FTAVar("/"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '(':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_LEFT_PARENTHESIS, N2FTAVar("("), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case ')':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_RIGHT_PARENTHESIS, N2FTAVar(")"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '[':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_LEFT_BRACKETS, N2FTAVar("["), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case ']':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_RIGHT_BRACKETS, N2FTAVar("]"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case ':':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_COLON, N2FTAVar(":"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case ';':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_SEMICOLON, N2FTAVar(";"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '#':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_SHARP, N2FTAVar("#"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '{':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_LEFT_BRACE, N2FTAVar("{"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case '}':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_RIGHT_BRACE, N2FTAVar("}"), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	case ',':
		m_SourceFile.N2FTAFile::GetByte(ch);
		return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_COMMA, N2FTAVar(","), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
	break;
	default:
		return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());
	break;
	};
}


N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::StringAnaysis()
{
	char ch = ' ';
	if( !m_SourceFile.N2FTAFile::GetByte(ch) || ch != '"' )
		return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());

	std::string Value = "";

	while( 1 )
	{
		if( !m_SourceFile.N2FTAFile::GetByte(ch) )
			return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());

		if( this->N2FTALexicalAnalyzer::isLetter(ch) != 2 )
		{
			if( ch == '"' )
			{
				char prev = ' ';
				if( m_SourceFile.N2FTAFile::ViewByte(prev, m_SourceFile.N2FTAFile::GetCurIdx() - 1) == true && prev == '\\' )
				{
					Value.erase(Value.size() - 1, 1);
				}
				else
				{
					return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_STRING, N2FTAVar(Value), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
				}
			}

			Value += ch;
		}
		else
		{
			Value += ch;

			if( !m_SourceFile.N2FTAFile::GetByte(ch) )
				return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());

			Value += ch;
		}
	}
}


N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::SymbolAnaysis()
{
	std::string Value = "";
	char ch = ' ';

	while( m_SourceFile.N2FTAFile::ViewByte(ch)
	    && this->N2FTALexicalAnalyzer::isDelimiter(ch) != true
	    && (this->N2FTALexicalAnalyzer::isNumeric(ch) || this->N2FTALexicalAnalyzer::isAlpha(ch)) )
	{
		Value += ch;

		if( !m_SourceFile.N2FTAFile::GetByte(ch) )
			return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());
	}

	if( Value.size() == 0 )
		return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());

	return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_SYMBOL, N2FTAVar(Value), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
}


N2FTALexicalAnalyzer::FTARet N2FTALexicalAnalyzer::NumberAnaysis()
{
	std::string Value = "";
	char ch = ' ';

	while( m_SourceFile.N2FTAFile::ViewByte(ch)
	    && this->N2FTALexicalAnalyzer::isDelimiter(ch) != true
	    && this->N2FTALexicalAnalyzer::isNumeric(ch) )
	{
		Value += ch;

		if( !m_SourceFile.N2FTAFile::GetByte(ch) )
			return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());
	}

	if( Value.size() == 0 )
		return FTARet(FTARet::RETURNCODE_ERROR, m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol());

	return FTARet(FTARet::RETURNCODE_SUCCESS, N2FTAToken(N2FTAToken::TYPE_NUMBER, N2FTAVar::N2FTAVar(Value), m_SourceFile.N2FTAFile::GetFileName(), m_SourceFile.N2FTAFile::GetLine(), m_SourceFile.N2FTAFile::GetCol()));
}


N2FTALexicalAnalyzer::FTARet::FTARet()
: m_Code(RETURNCODE_SUCCESS), m_Token(), m_SourceFileLine(0), m_SourceFileCol(0), m_SourceFileName("")
{
}


N2FTALexicalAnalyzer::FTARet::FTARet(const enumReturnCode in_Code, N2FTAToken in_Token)
: m_Code(in_Code), m_Token(in_Token), m_SourceFileLine(m_Token.N2FTAToken::GetSourceFileLine()), m_SourceFileCol(m_Token.N2FTAToken::GetSourceFileCol()), m_SourceFileName(m_Token.N2FTAToken::GetSourceFileName())
{
}


N2FTALexicalAnalyzer::FTARet::FTARet(const enumReturnCode in_Code, const std::string in_SourceFileName, const int in_SourceFileLine, const int in_SourceFileCol)
: m_Code(in_Code), m_Token(), m_SourceFileLine(in_SourceFileLine), m_SourceFileCol(in_SourceFileCol), m_SourceFileName(in_SourceFileName)
{
}


const N2FTALexicalAnalyzer::FTARet::enumReturnCode N2FTALexicalAnalyzer::FTARet::GetResult()
{
	return m_Code;
}


N2FTAToken N2FTALexicalAnalyzer::FTARet::GetToken()
{
	return m_Token;
}


const std::string N2FTALexicalAnalyzer::FTARet::GetSourceFileName()
{
	return m_SourceFileName;
}
