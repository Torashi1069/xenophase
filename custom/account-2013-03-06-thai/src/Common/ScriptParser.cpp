#include "Common/ScriptParser.h"
char* COM_Parse(char** data_p);


CScriptParser::CScriptParser()
{
	m_data.clear();
}


CScriptParser::~CScriptParser()
{
}


size_t CScriptParser::size()
{
	return m_data.size();
}


void CScriptParser::clear()
{
	m_data.clear();
}


bool CScriptParser::LoadFile(const char* szFileName)
{
	m_data.clear();

	FILE* fp = fopen(szFileName, "r");
	if( fp == NULL )
		return false;

	while( !feof(fp) )
	{
		char buf[1024] = {};
		char* pbuf = buf;

		if( fgets(buf, sizeof(buf), fp) == NULL )
			continue;

		std::string key = COM_Parse(&pbuf);
		if( key == "" )
			continue;

		std::vector<std::string> data;
		while( 1 )
		{
			std::string token = COM_Parse(&pbuf);
			if( token.size() == 0 )
				break;

			data.push_back(token);
		}

		m_data[key] = data;
	}

	fclose(fp);
	return true;
}


const char* CScriptParser::GetItem(const char* szKey, DWORD dwColumn)
{
	std::map<std::string,std::vector<std::string>>::const_iterator iObject;

	iObject = m_data.find(szKey);
	if( iObject == m_data.end() )
		return NULL; // not found.

	return iObject->second[dwColumn].c_str();
}


const char* CScriptParser::GetItem(DWORD dwRow, DWORD dwColumn)
{
	std::map<std::string,std::vector<std::string>>::const_iterator iObject;
	DWORD i;

	for( i = 0, iObject = m_data.begin(); i < dwRow && iObject != m_data.end(); ++i, ++iObject )
		continue; // keep iterating

	if( iObject == m_data.end() )
		return NULL; // row not found.

	if( dwColumn >= iObject->second.size() )
		return NULL; // column out of range.

	return iObject->second[dwColumn].c_str();
}


/// Parse a token out of a string.
/// @source https://github.com/id-Software/Quake-2/blob/master/game/q_shared.c
/// @source https://code.google.com/p/cleancodequake2/source/browse/trunk/shared/shared.cpp?r=399
#define	MAX_TOKEN_CHARS 128 // max length of an individual token
static char com_token[MAX_TOKEN_CHARS];
char* COM_Parse(char** data_p)
{
	int c;
	int len;
	char* data;

	data = *data_p;
	len = 0;
	com_token[0] = '\0';

	if( data == NULL )
	{
		*data_p = NULL;
		return "";
	}

	// skip whitespace
	while( true )
	{
		while( (c = *data) <= ' ' )
		{
			if( c == '\0' )
			{
				*data_p = NULL;
				return "";
			}

			data++;
		}

		// skip // comments
		if( c == '/' && data[1] == '/' )
		{
			while( *data != '\0' && *data != '\n' )
				data++;
			continue;
		}

		// end of whitespace
		break;
	}

	// handle quoted strings specially
	if( c == '\"' )
	{
		data++;

		while( true )
		{
			c = *data++;
			if( c == '\"' || c == '\0' )
			{
				com_token[len] = '\0';
				*data_p = data;
				return com_token;
			}

			if( len < MAX_TOKEN_CHARS )
			{
				com_token[len] = c;
				len++;
			}
		}
	}

	// parse a regular word
	do
	{
		if( len < MAX_TOKEN_CHARS )
		{
			com_token[len] = c;
			len++;
		}

		data++;
		c = *data;
	}
	while( c > ' ' );

	if( len >= MAX_TOKEN_CHARS )
		len = 0; // too long, fail.
	com_token[len] = '\0';

	*data_p = data;
	return com_token;
}
