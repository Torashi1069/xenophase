#include "shared/N2System/FTA(Formated Text Analyzer)/N2FTAFile.h"


N2FTAFile::N2FTAFile(const int in_TABSIZE)
: m_TABSIZE(in_TABSIZE), m_pBuffer(NULL), m_TotalBytes(0), m_strFileName("")
{
	this->N2FTAFile::Clear();
}


N2FTAFile::~N2FTAFile()
{
	this->N2FTAFile::Clear();
}


const std::string N2FTAFile::GetFileName() const
{
	return m_strFileName;
}


const int N2FTAFile::GetCurIdx() const
{
	return m_Cur.Idx;
}


const int N2FTAFile::GetLine() const
{
	return m_Cur.Line;
}


const int N2FTAFile::GetCol() const
{
	return m_Cur.Col;
}


bool N2FTAFile::ParseLine()
{
	m_LineInfoContainer.clear();

	BYTE* pBuffer = m_pBuffer;
	int Line = 1;
	int LineOffset = 1;
	int ParseBytes = 1;

	while( ParseBytes <= m_TotalBytes )
	{
		if( IsDBCSLeadByte(pBuffer[LineOffset - 1]) )
		{
			LineOffset += 2;
			ParseBytes += 2;
		}
		else
		if( strchr("\r\n", pBuffer[LineOffset - 1]) != NULL )
		{// newline character
			++LineOffset;
			++ParseBytes;

			if( ParseBytes <= m_TotalBytes ) //FIXME: on non-CRLF files, omits last line
			{
				if( strchr("\r\n", pBuffer[LineOffset - 1]) != NULL ) //FIXME: on non-CRLF files, will consume consecutive LFs
				{
					++LineOffset;
					++ParseBytes;
				}

				if( !m_LineInfoContainer.insert(std::make_pair(Line, CLineInfo(pBuffer, LineOffset - 1))).second )
					return false;

				++Line;
				pBuffer = &m_pBuffer[ParseBytes - 1];
				LineOffset = 1;
			}
		}
		else
		{// normal character
			++LineOffset;
			++ParseBytes;
		}
	}

	if( LineOffset > 1 )
	{// process remaining data on last line
		if( !m_LineInfoContainer.insert(std::make_pair(Line, CLineInfo(pBuffer, LineOffset - 1))).second )
			return false;
	}

	return true;
}


bool N2FTAFile::Load(const std::string in_strFileName)
{
	this->N2FTAFile::Clear();

	FILE* fp = fopen(in_strFileName.c_str(), "rb");
	if( fp == NULL )
		return false;

	fseek(fp, 0, SEEK_END);
	m_TotalBytes = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	m_pBuffer = new BYTE[m_TotalBytes];
	if( m_pBuffer == NULL )
	{
		fclose(fp);
		return false;
	}

	fread(m_pBuffer, 1, m_TotalBytes, fp);
	fclose(fp);

	this->N2FTAFile::ParseLine();

	LINEINFOCONTAINERITER iter = m_LineInfoContainer.find(1);
	if( iter == m_LineInfoContainer.end() )
		return false;

	m_strFileName = in_strFileName;
	m_Cur.Idx = 0;
	m_Cur.Line = 1;
	m_Cur.Col = 1;
	return true;
}


void N2FTAFile::Clear()
{
	if( m_pBuffer != NULL )
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}

	m_TotalBytes = 0;
	m_Cur.Idx = 0;
	m_Cur.Line = 1;
	m_Cur.Col = 1;
}


bool N2FTAFile::Write(const std::string in_strFileName)
{
	FILE* fp = fopen(in_strFileName.c_str(), "wb");
	if( fp == NULL )
		return false;

	for( LINEINFOCONTAINERITER iter = m_LineInfoContainer.begin(); iter != m_LineInfoContainer.end(); ++iter )
		fwrite(iter->second.m_pBuffer, 1, iter->second.m_Bytes, fp);

	fclose(fp);
	return true;
}


bool N2FTAFile::isEOF()
{
	return ( m_Cur.Idx >= m_TotalBytes );
}


const bool N2FTAFile::ViewByte(char& out_ch, const int in_Idx) const
{
	if( in_Idx < 0 || in_Idx >= m_TotalBytes )
		return false;

	out_ch = m_pBuffer[in_Idx];
	return true;
}


const bool N2FTAFile::ViewByte(char& out_ch) const
{
	return this->N2FTAFile::ViewByte(out_ch, m_Cur.Idx);
}


bool N2FTAFile::GetByte(char& out_ch)
{
	if( m_Cur.Idx < 0 || m_Cur.Idx >= m_TotalBytes )
		return false;

	out_ch = m_pBuffer[m_Cur.Idx];
	++m_Cur.Idx;

	switch( out_ch )
	{
	case '\t':
		m_Cur.Col += m_TABSIZE;
	break;
	case '\n':
		++m_Cur.Line;
	break;
	case '\r':
		m_Cur.Col = 1;
	break;
	default:
		++m_Cur.Col;
	break;
	};

	return true;
}


const std::string N2FTAFile::GetLineStr(const int in_Line)
{
	LINEINFOCONTAINERITER iter = m_LineInfoContainer.find(in_Line);
	if( iter == m_LineInfoContainer.end() )
		return std::string("");

	char* buf = new char[iter->second.m_Bytes + 1];
	if( buf == NULL )
		return std::string(NULL); //FIXME

	memcpy(buf, iter->second.m_pBuffer, iter->second.m_Bytes);
	buf[iter->second.m_Bytes] = '\0';

	if( strchr(buf, '\n') != NULL )
		*strchr(buf, '\n') = '\0';

	if( strchr(buf, '\r') != NULL )
		*strchr(buf, '\r') = '\0';

	std::string strTemp = buf;
	delete[] buf;
	return strTemp;
}
