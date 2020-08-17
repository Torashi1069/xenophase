#include "MonParameterMgr.h"
#include "QuestEventMgr.h"
#include "QuestTFSector.h"
#include "ZoneProcess.h"


CQuestTFSector::CQuestTFSector()
{
	m_buff = NULL;
	m_size = 0;
//	m_pos = 0;
	m_questMission.questID = 0;
	m_questMission.hunt_count = 0;
	m_questMission.time = 0;
	memset(m_questMission.questName, '\0', sizeof(m_questMission.questName));
	for( int i = 0; i < countof(m_questMission.hunt); ++i )
	{
//		m_questMission.hunt[i].huntIdent = 0;
		m_questMission.hunt[i].max_huntCount = 0;
		m_questMission.hunt[i].mobIdent = 0;
		memset(m_questMission.hunt[i].mobName, '\0', sizeof(m_questMission.hunt[i].mobName));
	}
}


CQuestTFSector::~CQuestTFSector()
{
	if( m_buff != NULL )
		delete[] m_buff;
	m_buff = NULL;
	m_size = 0;
}


bool CQuestTFSector::SetData(const char* buff, int len)
{
	if( buff == NULL || len < 1 )
		return false;

	m_var = buff;
	return true;
}


bool CQuestTFSector::Parse()
{
	m_var.CQVar::Replace("\n", ";");

	while( m_var.CQVar::length() > 0 )
	{
		CQVar value = m_var.CQVar::SpanExcluding(";");
		m_var.CQVar::Delete(value.CQVar::length() + 1);

		if( this->CQuestTFSector::LineComfile(value.CQVar::o_str(), value.CQVar::length()) == -1 )
			return false;
	}

	if( m_questMission.questID < 1 )
	{
		MessageBoxA(NULL, "Have No QuestID", "ERROR", MB_OK);
		return false;
	}

	return g_questEventMgr.CQuestEventMgr::AddQuest(m_questMission.questID, &m_questMission);
}


int CQuestTFSector::LineComfile(const char* buff, int size)
{
	CQVar var = buff;

	CQVar value[5] = { 0 }; //FIXME: initializes to integer
	int num_value = 0;

	int startPos = var.CQVar::FindToken('(');
	if( startPos < 1 )
		return 0;

	CQVar cmd = var.CQVar::SubStr(startPos);
	cmd.CQVar::Replace(" ", "");
	cmd.CQVar::Replace("\t", "");
	var.CQVar::Delete(startPos + 1);

	while( var.CQVar::length() > 0 )
	{
		int cutPos = var.CQVar::FindToken(',');
		if( cutPos == -1 )
			cutPos = var.CQVar::FindToken(')');

		if( cutPos == -1 )
		{
			std::string tok = var.CQVar::SubStr(1);
			if( tok == ";" )
				break;

			var.CQVar::Delete(1);
			continue;
		}

		CQVar temp = var.CQVar::SubStr(cutPos);
		int strPos = temp.CQVar::FindToken('"');
		if( strPos == -1 )
		{
			temp.CQVar::Replace("\t", "");
			temp.CQVar::Replace(" ", "");
			value[num_value] = atoi(temp.CQVar::o_str());
		}
		else
		{
			temp.CQVar::Delete(strPos + 1);
			value[num_value] = temp.CQVar::SubStr(temp.CQVar::FindToken('"'));
		}

		var.CQVar::Delete(cutPos + 1);
		++num_value;
	}

	if( this->CQuestTFSector::OnFunc(cmd.CQVar::o_str(), value) == -1 )
		return -1;

	return 1;
}


int CQuestTFSector::OnFunc(const char* cmd, CQVar* par)
{
	if( strcmp(cmd, "quest_info") == 0 )
		return this->CQuestTFSector::OnFuncQuest(par[0].CQVar::o_dword(), par[1].CQVar::o_str());
	else
	if( strcmp(cmd, "hunt") == 0 )
		return this->CQuestTFSector::OnFuncHunt(par[0].CQVar::o_str(), par[1].CQVar::o_num());
	else
	if( strcmp(cmd, "time") == 0 )
		return this->CQuestTFSector::OnFuncTime(par[0].CQVar::o_dword());
	else
	{
		return -1;
	}
}


int CQuestTFSector::OnFuncQuest(unsigned long questID, const char* questName)
{
	if( questID < 1 || questName == NULL || questName == "" ) //FIXME: pointer comparison
		return -1;

	if( strlen(questName) > 63 )
	{
		char errLog[256] = {};
		wsprintfA(errLog, "Over Size QuestName = %s \n", questName); //FIXME: deprecated API
		MessageBoxA(NULL, errLog, "QuestMission Error", MB_OK);
		return -1;
	}

	m_questMission.questID = questID;
	strcpy(m_questMission.questName, questName);
	return 1;
}


int CQuestTFSector::OnFuncHunt(const char* spriteName, int maxCount)
{
	if( strcmp(spriteName, "") == 0 || maxCount < 1 )
		return -1;

	unsigned long spriteID = g_monParameter.CMonParameterMgr::SearchKeyword(spriteName);
	const char* mobName = g_monParameter.CMonParameterMgr::GetMonsterName(spriteID);

	if( mobName == NULL )
	{
		char buff[256] = {};
		wsprintfA(buff, "Monster Name Is NULL, questID = %d, SpriteName = %s, SptiteID = %d \n", m_questMission.questID, spriteName, spriteID); //FIXME: deprecated API
		MessageBoxA(NULL, buff, "ERROR", MB_OK);
		return -1;
	}

	if( strcmp(mobName, "") == 0 )
	{
		char buff[256] = {};
		wsprintfA(buff, "Mob Name Is , questID = %d, SpriteName = %s, SptiteID = %d \n", m_questMission.questID, spriteName, spriteID); //FIXME: deprecated API
		MessageBoxA(NULL, buff, "ERROR", MB_OK);
		return -1;
	}

	if( m_questMission.questID < 1 )
	{
		char buff[256] = {};
		wsprintfA(buff, "This Mission Have No QuestID, SpriteName = %s, SptiteID = %d \n", spriteName, spriteID); //FIXME: deprecated API
		MessageBoxA(NULL, buff, "ERROR", MB_OK);
		return -1;
	}

	if( spriteID <= 0 && m_questMission.hunt_count >= 3 )
		return -1;

	m_questMission.hunt[m_questMission.hunt_count].huntIdent = m_questMission.hunt_count + 100000 * m_questMission.questID;
	m_questMission.hunt[m_questMission.hunt_count].mobIdent = spriteID;
	strcpy(m_questMission.hunt[m_questMission.hunt_count].mobName, mobName);
	m_questMission.hunt[m_questMission.hunt_count].max_huntCount = maxCount;
	++m_questMission.hunt_count;
	return 1;
}


int CQuestTFSector::OnFuncTime(unsigned long playTime)
{
	if( playTime < 1 )
		return -1;

	if( m_questMission.questID < 1 )
	{
		char buff[128] = {};
		wsprintfA(buff, "This Mission Have No QuestID, time = %d \n", playTime); //FIXME: deprecated API
		MessageBoxA(NULL, buff, "ERROR", MB_OK);
		return -1;
	}

	m_questMission.time = playTime;
	return 1;
}


int CQuestTFSector::FindToken(const char& p)
{
	if( p == '\0' )
		return -1;

	const char* pos = (char*)memchr(m_buff, p, m_size);
	if( pos == NULL )
		return -1;

	return (int)(pos - m_buff);
}


int CQuestTFSector::FindString(const char* ptr)
{
	if( ptr == NULL )
		return -1;
	
	const char* pos = strstr(m_buff, ptr);
	if( pos == NULL )
		return -1;

	return (int)(pos - m_buff);
}


int CQuestTFSector::Replace(const char* strOld, const char* strNew)
{
	if( strOld == NULL || strNew == NULL )
		return -1;

	if( m_buff == NULL || m_size < 1 )
		return -1;

	int iOld = strlen(strOld);
	int iNew = strlen(strNew);

	int count = 0;
	int pos = 0;
	while( pos < m_size )
	{
		char* p = strstr(m_buff + pos, strOld);
		if( p == NULL )
			break;

		pos = iOld + p - m_buff;
		++count;
	}

	if( count <= 0 )
		return 0;

	int size = m_size + count * (iNew - iOld) + 1;
	char* buff = new(std::nothrow) char[size];
	if( buff == NULL )
	{
		MessageBoxA(NULL, "Quest MemAlloc", NULL, MB_OK);
		return 0;
	}

	memset(buff, '\0', size);
	memcpy(buff, m_buff, m_size);

	for( ; ; )
	{
		char* p = strstr(buff, strOld);
		if( p == NULL )
			break;

		memmove(buff + iNew + (p - buff), buff + iOld + (p - buff), m_size - (p - buff) - iOld);
		memcpy(buff + (p - buff), strNew, iNew);
		m_size += iNew - iOld;
	}

	if( m_buff != NULL )
		delete[] m_buff;

	m_buff = buff;
	return count;
}


int CQuestTFSector::DelteBuff(int pos)
{
	int count = m_size - pos;
	char* buff = new(std::nothrow) char[count + 1];
	if( buff == NULL )
		return -1;

	memset(buff, '\0', count + 1);
	memcpy(buff, m_buff + pos, count);

	if( m_buff != NULL )
		delete[] m_buff;

	m_buff = buff;
	return count;
}


char* CQuestTFSector::SubStr(int pos)
{
	return NULL; // commented out?
}
