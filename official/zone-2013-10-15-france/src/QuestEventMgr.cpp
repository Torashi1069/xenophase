#include "Path.h"
#include "QuestEventMgr.h"
#include "QuestTFile.h"
#include "ZoneProcess.h"


CQuestEventMgr::CQuestEventMgr() // 11-12
{
}


CQuestEventMgr::~CQuestEventMgr() // 15-17
{
	this->CQuestEventMgr::Filnalize();
}


void CQuestEventMgr::Filnalize() // 20-34
{
	for( TQUEST::iterator iter = m_map.begin(); iter != m_map.end(); ++iter )
		delete iter->second;

	m_map.clear();
}


bool CQuestEventMgr::Initialize() // 37-50
{
	CQuestTFile qFile;
	std::string fileName = g_pathData.CPathData::SetFileName("QuestMission.txt");

	if( qFile.CQuestTFile::Load(fileName.c_str()) != 1 || qFile.CQuestTFile::BlockCutting() != 1 || qFile.CQuestTFile::GeneratorSector() != 1 )
	{
		qFile.CQuestTFile::Clear();
		return false;
	}

	return true;
}


bool CQuestEventMgr::AddQuest(unsigned long questID, TQUEST_MISSION* data) // 65-91
{
	if( questID < 1 || data == NULL )
		return false;

	if( m_map.find(questID) != m_map.end() )
	{
		char szErrMsg[256];
		sprintf_s(szErrMsg, countof(szErrMsg), "DUPLICATE QuestMission.txt !!!  QID : %d   -CQuestEventMgr::AddQuest()", questID);
		MessageBoxA(NULL, szErrMsg, "ERROR", MB_OK);
		return false;
	}

	CQuestMission* mission = new(std::nothrow) CQuestMission();
	if( mission == NULL || mission->CQuestMission::SetQuest(questID, data) != 1 )
	{
		MessageBoxA(NULL, "Memory Alloc Fail!!(q_5)", "ERROR", MB_OK);
		return false;
	}

	m_map.insert(std::pair<const unsigned long,CQuestMission*>(data->questID, mission));
	return true;
}


bool CQuestEventMgr::IsQuest(unsigned long questID) // 179-187
{
	return ( m_map.find(questID) != m_map.end() );
}
