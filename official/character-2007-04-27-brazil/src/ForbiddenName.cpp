#include "ForbiddenName.h"
#include <iostream>
#include <fstream>
#include <sstream>


/// singleton instance
static CForbiddenName g_ForbiddenName;
CForbiddenName* CSingleton<CForbiddenName>::ms_Singleton;


static bool fileToStream(const char* filename, std::ostringstream& filestrm, const char delimiter)
{
	std::ifstream file(filename);
	if( !file.is_open() )
		return false;

	while( !file.eof() )
	{
		std::string line;
		std::getline(file, line);

		size_t pos = line.find_first_of("//");
		if( pos != std::string::npos )
			line.erase(pos);

		filestrm << line << delimiter;
	}

	file.close();
	return true;
}


static size_t tokenize(const std::string& data, std::vector<std::string>& tokens, const std::string& delimiters)
{
	int old_size = tokens.size();

	size_t start, end;
	end = 0;

	while( 1 )
	{
		start = data.find_first_not_of(delimiters.c_str(), end, delimiters.size());
		end = data.find_first_of(delimiters.c_str(), start, delimiters.size());

		if( start == std::string::npos && end == std::string::npos )
			break;

		tokens.push_back(data.substr(start, end - start));

	}

	return tokens.size() - old_size;
}


CForbiddenName::CForbiddenName()
{
	m_useAscii = true;
	memset(m_asciiTable, ALLOWED, sizeof(m_asciiTable));
}


CForbiddenName::~CForbiddenName()
{
	for( std::vector<char*>::iterator it = m_forbiddenWords.begin(); it != m_forbiddenWords.end(); ++it )
		delete[] *it;

	m_forbiddenWords.clear();
}


void CForbiddenName::setForbiddenWord(const char* word)
{
	size_t length = strlen(word);
	char* buffer = new char[length + 1];

	for( size_t i = 0; i < length; ++i )
		buffer[i] = tolower((int)word[i]);
	buffer[length] = '\0';

	m_forbiddenWords.push_back(buffer);
}


bool CForbiddenName::isIncludedForbiddenWord(const char* word)
{
	for( std::vector<char*>::const_iterator it = m_forbiddenWords.begin(); it != m_forbiddenWords.end(); ++it )
		if( strstr(word, *it) != NULL )
			return true; // found.

	return false;
}


bool CForbiddenName::readForbiddenWordFile(const char* file)
{
	std::ostringstream ost;
	if( !fileToStream(file, ost, ' ') )
		return false;

	std::vector<std::string> wordarray;
	if( tokenize(ost.str(), wordarray, " \t\n\r") != 0 )
	{
		for( std::vector<std::string>::iterator it = wordarray.begin(); it != wordarray.end(); ++it )
			this->CForbiddenName::setForbiddenWord(it->c_str());

		this->CForbiddenName::sortForbiddenWordBySize();
	}

	return true;
}


static bool lessThanByStrSize(char* left, char* right)
{
	return strlen(left) < strlen(right);
}


void CForbiddenName::sortForbiddenWordBySize()
{
	std::sort(m_forbiddenWords.begin(), m_forbiddenWords.end(), lessThanByStrSize);
	std::unique(m_forbiddenWords.begin(), m_forbiddenWords.end());

	for( std::vector<char*>::iterator it = m_forbiddenWords.begin(); it != m_forbiddenWords.end(); ++it )
		std::cout << "Forbidden Word : " << *it << std::endl << std::flush;
}


bool CForbiddenName::readAsciiTableFile(const char* file)
{
	std::ostringstream ost;
	if( !fileToStream(file, ost, ' ') )
	{
		m_useAscii = false;
		return false;
	}

	std::vector<std::string> asciiarray;
	if( tokenize(ost.str(), asciiarray, " ,\t\n\r") != ASCIINUM )
		return false;

	for( size_t i = 0; i < ASCIINUM; ++i )
	{
		char c = asciiarray[i][0];

		if( c == '0' )
			m_asciiTable[i] = ALLOWED;
		else
		if( c == '1' )
			m_asciiTable[i] = IGNORED;
		else
		if( c == '2' )
			m_asciiTable[i] = FORBIDDEN;
		else
			return false;
	}

	return true;
}


bool CForbiddenName::isForbidden(const char* name)
{
	std::string buf;

	if( m_useAscii == true )
	{
		for( size_t i = 0; i < strlen(name); ++i )
		{
			char type = m_asciiTable[(BYTE)name[i]];

			if( type == FORBIDDEN )
				return true;

			if( type == IGNORED )
				continue;

			if( type == ALLOWED )
				buf.append(1, tolower(name[i]));
		}
	}
	else
	{
		for( size_t i = 0; i < strlen(name); ++i )
			buf.append(1, tolower(name[i]));
	}

	if( buf.size() == 0 )
		return true;

	return this->CForbiddenName::isIncludedForbiddenWord(buf.c_str());
}
