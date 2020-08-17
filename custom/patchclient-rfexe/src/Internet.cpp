#include "Internet.h"
////////////////////////////////////////


Download::Download(HINTERNET hUrl)
{
	m_inet = hUrl;
}


Download::~Download()
{
	InternetCloseHandle(m_inet);
}


bool Download::isOK()
{
	if( m_inet == NULL )
		return false; 

	DWORD statusCode;
	if( !this->statusCode(&statusCode) || statusCode != HTTP_STATUS_OK )
		return false;

	return true;
}


DWORD Download::size()
{
	DWORD size;

	if( !this->contentSize(&size) )
		return UNKNOWN_SIZE;

	return size;
}


bool Download::FetchOnce(std::vector<char>& output, DWORD maxBytes, DWORD* outBytes)
{
	DWORD tmpBytes; if( outBytes == NULL ) outBytes = &tmpBytes; // simplify
	*outBytes = 0; // always initialize

	if( maxBytes == 0 )
		return false; // reject corner-case

	DWORD oldSize = output.size();
	output.resize(oldSize + maxBytes);

	DWORD readBytes;
	if( InternetReadFile(m_inet, &output[oldSize], maxBytes, &readBytes) == FALSE )
	{
		output.resize(oldSize); // undo resize
		return false; // download error
	}

	output.resize(oldSize + readBytes);
	*outBytes = readBytes;
	return true;
}


bool Download::FetchAll(std::vector<char>& output)
{
	DWORD size = this->size();
	if( size != UNKNOWN_SIZE )
	{
		//NOTE: Adding a +1 byte overhead to avoid an extra realloc later.
		//      This also avoids zero-sized vectors when fetching zero-length files.
		if( !this->FetchOnce(output, size+1) )
			return false; // download error

		if( output.size() != size )
			return false; // size mismatch (should not happen)

		//NOTE: To cache the download, an extra InternetReadFile() of zero length is required.
		//      However, when passing '0' the file isn't cached, even though the call succeeds.
		//      So we use a buffer of size '1', but expect that nothing will be written to it.
		DWORD s;
		if( !this->FetchOnce(output, 1, &s) || s != 0 )
			return false; // unexpected behavior
	}
	else
	{
		DWORD s;
		do
		{
			if( !this->FetchOnce(output, 16*1024, &s) )
				return false; // download error
		}
		while( s != 0 );
	}

	return true;
}


std::vector<char> Download::FetchToMem()
{
	std::vector<char> result;
	this->FetchAll(result);
	return result;
}


std::string Download::FetchToStr()
{
	std::string result;

	std::vector<char> tmp;
	this->FetchAll(tmp);
	result.assign(tmp.begin(), tmp.end());

	return result;
}


bool Download::statusCode(DWORD* output)
{
	DWORD statusCode = 0;
	DWORD statusCodeLen = sizeof(statusCode);

	if( HttpQueryInfoA(m_inet, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &statusCode, &statusCodeLen, NULL) == FALSE )
		return false;

	*output = statusCode;
	return true;
}


bool Download::contentSize(DWORD* output)
{
	DWORD contentSize = 0;
	DWORD contentSizeLen = sizeof(contentSize);

	if( HttpQueryInfoA(m_inet, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &contentSize, &contentSizeLen, NULL) == FALSE )
		return false;

	*output = contentSize;
	return true;
}


////////////////////////////////////////


Internet::Internet()
{
	m_inet = NULL;
}


Internet::~Internet()
{
	this->Close();
}


/// Starts a new WinINet session.
bool Internet::Open(const char* szUserAgent)
{
	this->Close();

	m_inet = InternetOpenA(szUserAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if( m_inet == NULL )
		return false;

	return true;
}


/// Ends the current WinINet session.
void Internet::Close()
{
	if( m_inet != NULL )
	{
		InternetCloseHandle(m_inet);
		m_inet = NULL;
	}
}


/// Initializes the download of the selected url.
Download Internet::Get(const char* szUrlFmt, ...)
{
	va_list args;
	va_start(args, szUrlFmt);

	char url[1023+1];
	vsnprintf(url, sizeof(url), szUrlFmt, args);

	va_end(args);

	HINTERNET hUrl = InternetOpenUrlA(m_inet, url, NULL, NULL, INTERNET_FLAG_RESYNCHRONIZE, NULL);
	return Download(hUrl);
}


////////////////////////////////////////
