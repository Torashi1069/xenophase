#include "FTFile.h"


CFTFile::CFTFile(const std::string in_strFileName)
: m_strFileName(in_strFileName), m_pBuffer(NULL), m_TotalBytes(0), m_bOK(false), m_ReadPositionIdx(-1), m_Line(1), m_Col(1)
{
	if( this->CFTFile::Load() )
		m_bOK = true;
}


CFTFile::~CFTFile()
{
	if( m_pBuffer != NULL )
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
}


bool CFTFile::Load()
{
	if( m_pBuffer != NULL )
		return false;
	
	m_TotalBytes = this->CFTFile::GetLength();
	if( m_TotalBytes <= 0 )
		return false;

	m_pBuffer = new(std::nothrow) char[m_TotalBytes];
	if( m_pBuffer == NULL )
	{
		m_TotalBytes = 0;
		return false;
	}

	FILE* fp = fopen(m_strFileName.c_str(), "rb");
	if( fp == NULL )
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		m_TotalBytes = 0;
		return false;
	}

	if( fread(m_pBuffer, m_TotalBytes, 1, fp) != 1 )
	{
		fclose(fp);
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		m_TotalBytes = 0;
		return false;
	}

	fclose(fp);
	m_ReadPositionIdx = 0;
	return true;
}


bool CFTFile::ViewByte(char& out_ch)
{
	if( m_ReadPositionIdx < 0 || m_ReadPositionIdx >= m_TotalBytes )
		return false;

	out_ch = m_pBuffer[m_ReadPositionIdx];
	return true;
}


int CFTFile::GetCurLine()
{
	return m_Line;
}


int CFTFile::GetCurCol()
{
	return m_Col;
}


bool CFTFile::isEOF()
{
	return ( m_ReadPositionIdx >= m_TotalBytes );
}


const std::string CFTFile::GetFileName() const
{
	return m_strFileName;
}


bool CFTFile::ReadByte(char& out_ch)
{
	if( m_ReadPositionIdx < 0 || m_ReadPositionIdx >= m_TotalBytes )
		return false;

	out_ch = m_pBuffer[m_ReadPositionIdx];
	++m_ReadPositionIdx;

	switch( out_ch )
	{
	case '\t':
		m_Col += 4;
	break;
	case '\n':
		++m_Line;
	break;
	case '\r':
		m_Col = 1;
	break;
	default:
		++m_Col;
	break;
	}

	return true;
}


void CFTFile::UndoByte()
{
	if( m_ReadPositionIdx <= 0 )
		return;

	--m_ReadPositionIdx;
}


bool CFTFile::isOK() const
{
	return m_bOK;
}


long CFTFile::GetLength() const
{
	struct stat state;
	if( stat(m_strFileName.c_str(), &state) )
		return -1;

	return state.st_size;
}
