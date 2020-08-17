#include "N2System/FTA(Formated Text Analyzer)/N2FTAFile.h"


N2FTAFile::N2FTAFile(const int in_TABSIZE) : m_TABSIZE(in_TABSIZE), m_pBuffer(NULL), m_TotalBytes(0), m_strFileName("")
{
	this->N2FTAFile::Clear();
}


N2FTAFile::~N2FTAFile(void)
{
	this->N2FTAFile::Clear();
}


hook_method<void (N2FTAFile::*)(void)> N2FTAFile::_Clear(SERVER, "N2FTAFile::Clear");
void N2FTAFile::Clear(void)
{
	return (this->*_Clear)();

	if( m_pBuffer )
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}

	m_TotalBytes = 0;
	m_Cur.Idx = 0;
	m_Cur.Line = 1;
	m_Cur.Col = 1;
}


hook_method<bool (N2FTAFile::*)(void)> N2FTAFile::_ParseLine(SERVER, "N2FTAFile::ParseLine");
bool N2FTAFile::ParseLine(void)
{
	return (this->*_ParseLine)();

	//TODO
}


hook_method<bool (N2FTAFile::*)(const mystd::string in_strFileName)> N2FTAFile::_Load(SERVER, "N2FTAFile::Load");
bool N2FTAFile::Load(const mystd::string in_strFileName)
{
	return (this->*_Load)(in_strFileName);

	this->N2FTAFile::Clear();

	FILE* v5 = fopen(in_strFileName.c_str(), "rb");
	if ( !v5 )
		return false;

	fseek(v5, 0, SEEK_END);
	m_TotalBytes = ftell(v5);
	fseek(v5, 0, SEEK_SET);

	m_pBuffer = new unsigned char[m_TotalBytes];
	if( !m_pBuffer )
	{
		fclose(v5);
		return false;
	}

	fread(m_pBuffer, 1, m_TotalBytes, v5);
	fclose(v5);

	this->N2FTAFile::ParseLine();

	int _Keyval = 1;
	if( m_LineInfoContainer.find(_Keyval) == m_LineInfoContainer.end() )
		return false;

	m_strFileName = in_strFileName;
	m_Cur.Idx = 0;
	m_Cur.Line = 1;
	m_Cur.Col = 1;

	return true;
}
