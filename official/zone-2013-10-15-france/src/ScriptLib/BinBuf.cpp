#include "ScriptLib/BinBuf.h"


char* CBinBuf::GetBase()
{
	return m_buf;
}


int CBinBuf::GetSize()
{
	return m_bufSize;
}


void CBinBuf::Clear()
{
	if( m_buf != NULL )
	{
		delete[] m_buf;
		m_buf = NULL;
	}

	m_bufSize = 0;
}


bool CBinBuf::Load(char* fName)
{
	FILE* fp = fopen(fName, "rb");
	if( fp == NULL )
		return false;

	fseek(fp, 0, SEEK_END);
	m_bufSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	m_buf = new char[m_bufSize];
	fread(fp, m_bufSize, 1, fp);

	fclose(fp);
	return true;
}


CBinBuf::CBinBuf()
{
	m_buf = NULL;
//	m_bufSize = 0;
	this->CBinBuf::Clear();
}


CBinBuf::~CBinBuf()
{
	this->CBinBuf::Clear();
}
