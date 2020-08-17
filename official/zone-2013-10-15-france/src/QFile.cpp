#include "QFile.h"


CQFile::CQFile()
: m_fp(NULL)
{
}


CQFile::~CQFile()
{
	this->CQFile::Close();
}


void CQFile::Close()
{
	if( m_fp != NULL )
	{
		fclose(m_fp);
		m_fp = NULL;
	}
}


std::pair<bool,int> CQFile::Open(const std::string in_filename)
{
	if( in_filename.size() == 0 )
		return std::pair<bool,int>(false, 0);

	this->CQFile::Close();

	m_fp = fopen(in_filename.c_str(), "rb");
	if( m_fp == NULL )
		return std::pair<bool,int>(false, 0);

	fseek(m_fp, 0, SEEK_END);
	int filesize = (int)ftell(m_fp);
	fseek(m_fp, 0, SEEK_SET);

	return std::pair<bool,int>(true, filesize);
}


int CQFile::Read(char* out_pBuffer, const int in_ReadBytes)
{
	if( m_fp == NULL )
		return 0;

	return (int)fread(out_pBuffer, 1, in_ReadBytes, m_fp);
}
