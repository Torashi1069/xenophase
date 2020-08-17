#include "Globals.h" // g_fileMgr, ErrorMsg()
#include "WinMain.h" // g_baseDir
#include "Base/File.h"
#include "Base/FileMgr.h"


CFile::CFile()
{
	m_hFile = NULL;
	m_buf = NULL;
//	m_cursor = 0;
//	m_size = 0;
//	memset(m_fileName, '\0', sizeof(m_fileName));
}


CFile::~CFile()
{
	this->CFile::Close();
}


bool CFile::Open(const char* fName, unsigned int nOpenFlags)
{
	if( nOpenFlags == 0 )
	{
		CFile::MakeFileName(m_fileName, fName);

		m_cursor = 0;
		m_buf = (char*)g_fileMgr.CFileMgr::GetData(m_fileName, &m_size);
		if( m_buf == NULL )
			return false;

		return true;
	}
	else
	if( nOpenFlags & modeWrite )
	{
		strcpy(m_fileName, fName);

		m_hFile = CreateFileA(m_fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if( m_hFile == INVALID_HANDLE_VALUE )
		{
			ErrorMsg(m_fileName);
			return false;
		}

		m_size = GetFileSize(m_hFile, NULL);

		return true;
	}
	else
	{// not supported
		return false;
	}
}


bool CFile::Read(void* lpBuf, size_t nCount)
{
	if( m_hFile != NULL )
	{// file read
		if( ReadFile(m_hFile, lpBuf, nCount, (LPDWORD)&nCount, NULL) == FALSE )
			return false;

		return true;
	}
	else
	if( m_buf != NULL )
	{// memory read
		if( m_cursor + nCount > m_size )
			return false;

		memcpy(lpBuf, &m_buf[m_cursor], nCount);
		m_cursor += nCount;

		return true;
	}
	else
	{// not initialized
		return false;
	}
}


bool CFile::Write(const void* lpBuf, size_t nCount)
{
	if( m_hFile != NULL )
	{// file write
		if( WriteFile(m_hFile, lpBuf, nCount, (LPDWORD)&nCount, NULL) == FALSE )
			return false;

		return true;
	}
	else
	{// not initialized
		return false;
	}
}


bool CFile::Seek(off_t lOff, size_t nFrom)
{
	if( m_hFile != NULL )
	{// file seek
		SetFilePointer(m_hFile, lOff, NULL, nFrom);
		return true;
	}
	else
	if( m_buf != NULL )
	{// memory seek
		if( nFrom == CFile::begin )
			m_cursor = lOff;
		else
		if( nFrom == CFile::current )
			m_cursor = lOff + m_cursor;
		else
		if( nFrom == CFile::end )
			m_cursor = lOff + m_size;

		if( m_cursor > m_size )
		{// stop at end of file
			m_cursor = m_size;
			return false;
		}

		return true;
	}
	else
	{// not initialized
		return false;
	}
}


void CFile::Close()
{
	if( m_hFile != NULL )
	{
		CloseHandle(m_hFile);
		m_hFile = NULL;
	}
	else
	if( m_buf != NULL )
	{
		VirtualFree(m_buf, 0, MEM_RELEASE);
		m_buf = NULL;
	}
}


char* CFile::GetFileName()
{
	return m_fileName;
}


DWORD CFile::GetLength()
{
	return m_size;
}


const unsigned char* CFile::GetBuf()
{
	return (unsigned char*)&m_buf[m_cursor];
}


const void* CFile::GetCurBuf(int nOffset)
{
	return (void*)&m_buf[nOffset];
}


bool CFile::IsFileExist(const char* fName)
{
	char fullName[256];
	CFile::MakeFileName(fullName, fName);

	return g_fileMgr.CFileMgr::IsDataExist(fullName);
}


void CFile::MakeFileName(char* output, const char* input)
{
	strcpy(output, g_baseDir);
	strcat(output, input);

	if( strstr(output, ":") != NULL )
	{// input was a full path, shift it to the beginning
		ptrdiff_t pos = strstr(output, ":") - output - 1;
		char temp[1024];
		memcpy(temp, output + pos, strlen(output) - pos + 1);
		strcpy(output, temp);
	}

	while( strstr(output, "//") != NULL )
	{// path contains doubled slash, convert into single slash
		ptrdiff_t pos = strstr(output, "//") - output;
		char temp[1024];
		memcpy(temp, output, pos);
		strcpy(temp + pos, output + pos + 1);
		strcpy(output, temp);
	}
}
