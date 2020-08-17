#include "Globals.h" // Trace(), ErrorMsg()
#include "Util.h"
////////////////////////////////////////


CTokenizer::CTokenizer(const mystd::string& a)
{
	this->CTokenizer::SetString(a);
}


void CTokenizer::SetString(const mystd::string& a)
{
	char buffer[1024];
	int curOffset = 0;
	int curMode = 1;
	m_token.clear();

	size_t i;
	for( i = 0; i < a.size(); ++i )
	{
		if( curMode == 0 )
		{// parse quoted string
			if( a[i] == '"' )
			{// end of a string
				buffer[curOffset] = '\0';
				m_token.push_back(buffer);
				curMode = 2;
				curOffset = 0;
			}
			else
			{// string continues
				buffer[curOffset] = a[i];
				++curOffset;
			}
		}
		else
		if( curMode == 1 )
		{// parse normal text
			if( a[i] == '/' && a[i + 1] == '/' )
				return;

			if( !isspace(a[i]) || a[i] < 0 )
			{// text
				if( a[i] == '"' )
				{// start of quoted string
					curOffset = 0;
					curMode = 0;
				}
				else
				{// normal
					buffer[curOffset] = a[i];
					++curOffset;
				}
			}
			else
			{// whitespace
				if( i != 0 )
				{// end of a token
					buffer[curOffset] = '\0';
					m_token.push_back(buffer);
					curOffset = 0;
				}

				curMode = 2;
			}
		}
		else
		if( curMode == 2 )
		{// skip whitespace
			if( !isspace(a[i]) || a[i] < 0 )
			{
				curMode = 1;
				--i;
			}
		}
	}

	if( curMode != 2 && i != 0 )
	{// finish last remaining token
		buffer[curOffset] = '\0';
		m_token.push_back(buffer);
	}
}


void CTokenizer::MakeLower()
{
	for( int a = 0; a < (int)m_token.size(); ++a )
	{
		mystd::string& s = m_token[a];

		for( size_t i = 0; i < s.size(); ++i )
		{
			if( s[i] > 0 && isupper(s[i]) )
				tolower(s[i]);
		}
	}
}


void CTokenizer::MakeUpper()
{
	for( int a = 0; a < (int)m_token.size(); ++a )
	{
		mystd::string& s = m_token[a];

		for( size_t i = 0; i < s.size(); ++i )
		{
			if( s[i] > 0 && islower(s[i]) )
				toupper(s[i]);
		}
	}
}


mystd::string& CTokenizer::operator[](int a)
{
	if( a < 0 || a >= (int)m_token.size() )
	{
		ErrorMsg("Error in CTokenizer :: operator []");
		for( size_t i = 0; i < m_token.size(); ++i )
			ErrorMsg(m_token[i].c_str());
	}

	return m_token[a];
}


int CTokenizer::NumTokens()
{
	return m_token.size();
}


/*
void CTokenizer::GetLine(mystd::istrstream& stream)
{
	char buf[1024];
	stream.getline(buf, countof(buf));
	this->CTokenizer::SetString(buf);
}
*/


////////////////////////////////////////


void MakeStringLower(mystd::string& s)
{
	for( size_t i = 0; i < s.size(); ++i )
	{
		if( s[i] > 0 && isupper(s[i]) )
			tolower(s[i]);
	}
}


/// Formats an integer using three-digit grouping, with comma as the separator.
char* GetNumberText(int number, char* buf)
{
	sprintf(buf, "%d", number);
	int size = strlen(buf);

	if( size > 3 )
	{
		mystd::string numTxt = "";
		int pos = 0;

		// process leading digits
		while( pos < size % 3 )
		{
			numTxt += buf[pos];
			++pos;
		}

		// process remaining digits
		while( pos < size )
		{
			if( (size - pos) % 3 == 0 && pos != 0 )
				numTxt += ',';

			numTxt += buf[pos];
			++pos;
		}

		// write output
		sprintf(buf, "%s", numTxt.c_str());
	}

	return buf;
}


const char* StrChrBackward(const char* strName, char c)
{
	for( const char* p = strName + strlen(strName) - 1; p >= strName; --p )
		if( *p == c )
			return p;

	return NULL;
}


DWORD aToDW_HEX(const char* hexNumber)
{
	DWORD result = 0;
	int shift = 0;

	for( int i = strlen(hexNumber) - 1; i >= 2; --i )
	{
		char c = hexNumber[i];

		switch( c )
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			result += (c - '0') << shift;
			shift += 4;
		break;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
			result += (c - 'A' + 10) << shift;
			shift += 4;
		break;
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
			result += (c - 'a' + 10) << shift;
			shift += 4;
		break;
		default:
		break;
		};
	}

	return result;
}


void GetFileNames(mystd::list<mystd::string>& fileNameList, const char* path, const char* szFileName_wildcard)
{
	mystd::string pathWildcard;
	pathWildcard.assign(path);
	pathWildcard.append(szFileName_wildcard);

	WIN32_FIND_DATAA wfd = {};

	HANDLE hFile = FindFirstFileA(pathWildcard.c_str(), &wfd);
	if( hFile == INVALID_HANDLE_VALUE )
	{
		Trace("INVALID_HANDLE_VALUE");
		FindClose(hFile);
		return;
	}

	mystd::string cur0 = ".";
	mystd::string cur1 = "..";

	if( wfd.cFileName != cur0 && wfd.cFileName != cur1 )
	{
		fileNameList.push_back(wfd.cFileName);
	}

	while( FindNextFileA(hFile, &wfd) )
	{
		if( wfd.cFileName != cur0 && wfd.cFileName != cur1 )
		{
			fileNameList.push_back(wfd.cFileName);
		}
	}

	FindClose(hFile);
}


void DeleteDirectory(const char* dirName)
{
	mystd::list<mystd::string> fileNameList;
	mystd::list<mystd::string> dirNameList;

	WIN32_FIND_DATAA wfd = {};
	char szPath[2048];

	// starting directory
	strcpy(szPath, dirName);
	strcat(szPath, "\\*.*");

	// build a list of items to delete
	HANDLE hFile = FindFirstFileA(szPath, &wfd);
	if( hFile == INVALID_HANDLE_VALUE )
	{
		FindClose(hFile);
		_rmdir(dirName);
		return;
	}

	mystd::string cur0 = ".";
	mystd::string cur1 = "..";

	if( wfd.cFileName != cur0 && wfd.cFileName != cur1 )
	{
		if( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			dirNameList.push_back(wfd.cFileName);
		else
			fileNameList.push_back(wfd.cFileName);
	}

	while( FindNextFileA(hFile, &wfd) )
	{
		if( wfd.cFileName != cur0 && wfd.cFileName != cur1 )
		{
			if( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				dirNameList.push_back(wfd.cFileName);
			else
				fileNameList.push_back(wfd.cFileName);
		}
	}

	FindClose(hFile);

	// starting directory
	strcpy(szPath, dirName);
	strcat(szPath, "\\");

	// delete all files in list
	for( mystd::list<mystd::string>::iterator it = fileNameList.begin(); it != fileNameList.end(); ++it )
	{
		chmod((szPath + *it).c_str(), _S_IWRITE);
		unlink((szPath + *it).c_str());
	}

	// recursively delete all directories in list
	for( mystd::list<mystd::string>::iterator it = dirNameList.begin(); it != dirNameList.end(); ++it )
	{
		DeleteDirectory((szPath + *it).c_str());
	}

	_rmdir(dirName);
}


////////////////////////////////////////
