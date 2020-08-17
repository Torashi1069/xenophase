#include "QuestTFile.h"


CQuestTFile::CQuestTFile(void) // line 9
{
	m_buff = new char[1024];
	m_size = 0;
	m_pos = 0;
	m_note = false;
}


CQuestTFile::~CQuestTFile(void) // line 18
{
	this->CQuestTFile::Clear();
}


hook_method<void (CQuestTFile::*)(void)> CQuestTFile::_Clear(SERVER, "CQuestTFile::Clear");
void CQuestTFile::Clear(void) // line 23
{
	return (this->*_Clear)();

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
		CQuestTFSector* p = m_lsSector.front();
		m_lsSector.pop_front();
		delete p;
	}
}


hook_method<bool (CQuestTFile::*)(const char* filename)> CQuestTFile::_Load(SERVER, "CQuestTFile::Load");
bool CQuestTFile::Load(const char* filename) // line 45
{
	return (this->*_Load)(filename);

	//TODO
}


hook_method<bool (CQuestTFile::*)(void)> CQuestTFile::_BlockCutting(SERVER, "CQuestTFile::BlockCutting");
bool CQuestTFile::BlockCutting(void) // line 95
{
	return (this->*_BlockCutting)();

	//TODO
}


hook_method<bool (CQuestTFile::*)(void)> CQuestTFile::_GeneratorSector(SERVER, "CQuestTFile::GeneratorSector");
bool CQuestTFile::GeneratorSector(void) // line 132
{
	return (this->*_GeneratorSector)();

	//TODO
}


hook_method<bool (CQuestTFile::*)(void)> CQuestTFile::_CuttingNote(SERVER, "CQuestTFile::CuttingNote");
bool CQuestTFile::CuttingNote(void) // line 70
{
	return (this->*_CuttingNote)();

	//TODO
}
