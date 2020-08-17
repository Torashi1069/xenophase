#include "QFile.h"
#include "QuestTFile.h"


CQuestTFile::CQuestTFile()
{
	m_buff = new char[1024];
	m_size = 0;
	m_pos = 0;
	m_note = false;
}


CQuestTFile::~CQuestTFile()
{
	this->CQuestTFile::Clear();
}


void CQuestTFile::Clear()
{
	if( m_buff != NULL )
	{
		delete[] m_buff;
		m_buff = NULL;
	}

	m_size = 0;
	m_pos = 0;
	m_note = false;

	while( m_lsSector.size() != 0 )
	{
		CQuestTFSector* sector = m_lsSector.front();
		m_lsSector.pop_front();
		delete sector;
	}
}


bool CQuestTFile::Load(const char* filename)
{
	CQFile file;

	std::pair<bool,int> ret = file.CQFile::Open(filename);
	if( !ret.first )
		return false;

	int count = ret.second;
	char* buf = (char*)_malloca(count + 1);

	if( count != file.CQFile::Read(buf, count) )
	{
		if( buf != NULL )
			_freea(buf);

		return false;
	}

	buf[count] = '\0';
	m_var = buf;

	if( buf != NULL )
		_freea(buf);

	return true;
}


bool CQuestTFile::CuttingNote() // 97-119
{
	m_var.CQVar::Trim_Left();
	m_var.CQVar::Trim_Left();

	for( ; ; )
	{
		int pos = m_var.CQVar::FindToken("/*");
		int endpos = m_var.CQVar::FindToken("*/");

		if( pos < 0 )
			break;

		if( pos > endpos )
			return 0;

		m_var.CQVar::Delete(pos, endpos - pos + 2);
		m_var.CQVar::Trim_Left();
	}

	m_var.CQVar::Trim_Left();

	for( ; ; )
	{
		int pos = m_var.CQVar::FindToken("//");
		if( pos == -1 )
			break;

		int endpos = m_var.CQVar::FindToken(pos, "\n");
		if( endpos == -1 )
			endpos = m_var.CQVar::length();

		m_var.CQVar::Delete(pos, endpos - pos + 1);
	}

	m_var.CQVar::Trim_Right();

	return true;
}


bool CQuestTFile::BlockCutting()
{
	if( !this->CQuestTFile::CuttingNote() )
		return false;

	while( m_var.CQVar::length() > 1 )
	{
		if( m_var.CQVar::FindToken("quest") == -1 )
			break;

		int startpos = m_var.CQVar::FindToken("{");
		int endpos = m_var.CQVar::FindToken("}");
		if( startpos == -1 && endpos == -1 )
			return false;
				
		if( startpos > endpos )
		{
			MessageBoxA(NULL, "QuestMission.txt File have to get { or } Block", "ERROR", MB_OK);
			return false;
		}

		CQVar temp = m_var.CQVar::SubStr(startpos + 1, endpos - startpos - 1);
		m_var.CQVar::Delete(endpos + 1);

		CQuestTFSector* sector = new(std::nothrow) CQuestTFSector();
		if( sector == NULL )
		{
			MessageBoxA(NULL, "Memory Alloc Fail!!(q_2)", "ERROR", MB_OK);
			return false;
		}

		sector->CQuestTFSector::SetData(temp.CQVar::o_str(), temp.CQVar::length());
		m_lsSector.push_back(sector);
	}

	m_var.CQVar::Delete(0, m_var.CQVar::length());
	return true;
}


int CQuestTFile::FindString(const char* ptr)
{
	if( ptr == NULL )
		return -1;
	
	char* p = strstr(m_buff + m_pos, ptr);
	if( p == NULL )
		return -1;

	return (int)(p - m_buff);
}


bool CQuestTFile::GeneratorSector()
{
	while( m_lsSector.size() != 0 )
	{
		CQuestTFSector* sector = m_lsSector.front();
		m_lsSector.pop_front();

		if( sector == NULL )
			continue;

		if( !sector->CQuestTFSector::Parse() )
		{
			MessageBoxA(NULL, "Sector Parsing Error!!", "ERROR", MB_OK);
			return false;
		}

		delete sector;
	}

	return true;
}
