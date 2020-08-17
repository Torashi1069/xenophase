#include "FuncExtraction.h"
#include "ITPMgr.h"
#include "MonParameterMgr.h"
#include "QuestArlimiTxt.h"
#include "QuestEventMgr.h"
#include "QuestProviso.h"
#include "ZoneProcess.h"
#include "shared/NCriticalErrorLog.h"


CQuestProviso::CQuestProviso()
{
	m_pool.CMemoryMgr<TPROVISO>::Init(1000);
}


CQuestProviso::~CQuestProviso()
{
	this->CQuestProviso::Filnalize();
}


bool CQuestProviso::Init()
{
	return this->CQuestProviso::LoadQuestProviso("QuestProviso.txt");
}


void CQuestProviso::Filnalize()
{
	m_pool.CMemoryMgr<TPROVISO>::Reset();
	m_proviso_map.clear();
}


bool CQuestProviso::LoadQuestProviso(const char* file_name)
{
	CQuestArlimiTxt provisoFile;
	if( !provisoFile.CQuestArlimiTxt::LoadTxt("QuestProviso.txt") )
		return false;

	if( !provisoFile.CQuestArlimiTxt::DeleteComment() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "QuestProvios LoadQuestProvoiso Txt");
		return false;
	}

	provisoFile.CQuestArlimiTxt::ExtractionFuncPositonList("quest_proviso");

	for( ; ; )
	{
		CQVar data = provisoFile.CQuestArlimiTxt::GetNextFuncData();
		data.CQVar::Trim_Left();
		data.CQVar::Trim_Right();

		if( data.CQVar::length() < 1 )
			return true;

		CFuncExtraction func;
		func.CFuncExtraction::SetData(data.CQVar::o_str());

		std::vector<CQVar> value;

		if( !func.CFuncExtraction::GetFuncValue("quest_proviso", value) )
			return true;

		unsigned long questID = atoi(value[0].CQVar::o_str());
		if( !this->CQuestProviso::AddProviso(questID) )
			return false;

		if( func.CFuncExtraction::GetFuncValue("type", value) )
		{
			short type = (short)atoi(value[0].CQVar::o_str());
			this->CQuestProviso::InsertQuestType(questID, type);
		}

		if( func.CFuncExtraction::GetFuncValue("sex", value) )
		{
			short sex = (short)atoi(value[0].CQVar::o_str());
			this->CQuestProviso::InsertSex(questID, sex);
		}

		if( func.CFuncExtraction::GetFuncValue("level", value) )
		{
			if( value.size() != 2 )
			{
				MessageBoxA(NULL, "CQuestProviso::LoadQuestProviso Level 파라미터 부족", "NOTIFYQUEST ERROR", MB_OK);
				return false;
			}

			unsigned long lowLv = (unsigned long)atoi(value[0].CQVar::o_str());
			unsigned long hiLv = (unsigned long)atoi(value[1].CQVar::o_str());
			this->CQuestProviso::InsertLevel(questID, lowLv, hiLv);
		}

		func.CFuncExtraction::GetFuncValue("joblist", value);
		this->CQuestProviso::InsertJobList(questID, value);

		func.CFuncExtraction::GetFuncValue("itemlist", value);
		this->CQuestProviso::InsertItem(questID, value);

		func.CFuncExtraction::GetFuncValue("completeItemlist", value);
		this->CQuestProviso::InsertCompleteItem(questID, value);

		func.CFuncExtraction::GetFuncValue("HomunLevel", value);
		if( value.size() == 2 )
		{
			int minLv = (int)atoi(value[0].CQVar::o_str());
			int maxLv = (int)atoi(value[1].CQVar::o_str());
			this->CQuestProviso::InsertHomunLevel(questID, minLv, maxLv);
		}

		func.CFuncExtraction::GetFuncValue("HomunMutation", value);
		if( value.size() != 0 )
		{
			int type = (int)atoi(value[0].CQVar::o_str());
			this->CQuestProviso::InsertEvolution(questID, type);
		}
	}
}


bool CQuestProviso::AddProviso(unsigned long qid)
{
	if( !g_questEventMgr.CQuestEventMgr::IsQuest(qid) )
	{
		char error[128] = {};
		sprintf_s(error, countof(error), "Not Exist Quest %d", qid);
		MessageBoxA(NULL, error, "NOTIFYQUEST ERROR", MB_OK);
		return false;
	}

	if( this->CQuestProviso::SelectProviso(qid) )
	{
		char error[128] = {};
		sprintf_s(error, countof(error), "%d Quest is registered as the QuestProviso", qid);
		MessageBoxA(NULL, error, "NOTIFYQUEST ERROR", MB_OK);
		return false;
	}

	TPROVISO* p = m_pool.CMemoryMgr<TPROVISO>::Alloc();
	if( p == NULL )
	{
		MessageBoxA(NULL, "CQuestArlimiTxt::AddProviso Memory Alloc Fail", "NOTIFYQUEST ERROR", MB_OK);
		return false;
	}

	p->t_qid = qid;
	p->t_questType = 0;
	p->t_sex = 0;
	p->t_hiLV = 150;
	p->t_lowLV = 0;
	p->t_itemList.clear();
	p->t_jobList.clear();
	p->t_completeItemList.clear();
	p->t_homun_evolution = -1;
	p->t_homun_maxLv = -1;
	p->t_homun_minLv = -1;

	m_proviso_map.insert(std::pair<unsigned long,TPROVISO*>(qid, p));
	return true;
}


bool CQuestProviso::InsertQuestType(unsigned long qid, short type)
{
	TPROVISO* p = this->CQuestProviso::SelectProviso(qid);
	if( p == NULL )
	{
		char error[128] = {};
		sprintf_s(error, countof(error), "CQuestProviso::InsertQuestType Find not Found %d", qid);
		MessageBoxA(NULL, error, "NOTIFYQUEST ERROR", MB_OK);
		return false;
	}

	p->t_questType = type;
	return true;
}


bool CQuestProviso::InsertSex(unsigned long qid, short sex)
{
	TPROVISO* p = this->CQuestProviso::SelectProviso(qid);
	if( p == NULL )
	{
		char error[128] = {};
		sprintf_s(error, countof(error), "CQuestProviso::InsertSex Find not Found %d", qid);
		MessageBoxA(NULL, error, "NOTIFYQUEST ERROR", MB_OK);
		return false;
	}

	p->t_sex = sex;
	return true;
}


bool CQuestProviso::InsertLevel(unsigned long qid, unsigned long lowLv, unsigned long hiLv)
{
	TPROVISO* p = this->CQuestProviso::SelectProviso(qid);
	if( p == NULL )
	{
		char error[128] = {};
		sprintf_s(error, countof(error), "CQuestProviso::InsertLevel Find not Found %d", qid);
		MessageBoxA(NULL, error, "NOTIFYQUEST ERROR", MB_OK);
		return false;
	}

	p->t_hiLV = hiLv;
	p->t_lowLV = lowLv;
	return true;
}


bool CQuestProviso::InsertJobList(unsigned long qid, std::vector<CQVar> data)
{
	TPROVISO* p = this->CQuestProviso::SelectProviso(qid);
	if( p == NULL )
	{
		char error[128] = {};
		sprintf_s(error, countof(error), "CQuestProviso::InsertJobList Find not Found %d", qid);
		MessageBoxA(NULL, error, "NOTIFYQUEST ERROR", MB_OK);
		return false;
	}

	for( size_t i = 0; i < data.size(); ++i )
	{
		const char* spriteName = data[i].CQVar::o_str();
		unsigned long sprite = g_monParameter.CMonParameterMgr::SearchKeyword(spriteName);
		p->t_jobList.push_back(sprite);
	}

	return true;
}


bool CQuestProviso::InsertItem(unsigned long qid, std::vector<CQVar> data)
{
	TPROVISO* p = this->CQuestProviso::SelectProviso(qid);
	if( p == NULL )
	{
		char error[128] = {};
		sprintf_s(error, countof(error), "CQuestProviso::InsertItem Find not Found %d", qid);
		MessageBoxA(NULL, error, "NOTIFYQUEST ERROR", MB_OK);
		return false;
	}

	for( size_t i = 0; i < data.size(); i += 2 )
	{
		int ITID = g_itpMgr.CITPMgr::GetITID(data[i].CQVar::o_str());
		if( ITID <= 1 )
		{
			char error[128] = {};
			sprintf_s(error, countof(error), "CQuestProviso::InsertItem Not Exist item %s", data[i].CQVar::o_str());
			MessageBoxA(NULL, error, "NOTIFYQUEST ERROR", MB_OK);
			return false;
		}

		p->t_itemList.insert(std::pair<const unsigned long,int>(ITID, atoi(data[i + 1].CQVar::o_str())));
	}

	return true;
}


bool CQuestProviso::InsertCompleteItem(unsigned long qid, std::vector<CQVar> data)
{
	TPROVISO* p = this->CQuestProviso::SelectProviso(qid);
	if( p == NULL )
	{
		char error[128] = {};
		sprintf_s(error, countof(error), "CQuestProviso::InsertItem Find not Found %d", qid);
		MessageBoxA(NULL, error, "NOTIFYQUEST ERROR", MB_OK);
		return false;
	}

	for( size_t i = 0; i < data.size(); i += 2 )
	{
		int ITID = g_itpMgr.CITPMgr::GetITID(data[i].CQVar::o_str());
		if( ITID <= 1 )
		{
			char error[128] = {};
			sprintf_s(error, countof(error), "CQuestProviso::InsertCompleteItem Not Exist item %s", data[i].CQVar::o_str());
			MessageBoxA(NULL, error, "NOTIFYQUEST ERROR", MB_OK);
			return false;
		}

		p->t_completeItemList.insert(std::pair<const unsigned long,int>(ITID, atoi(data[i + 1].CQVar::o_str())));
	}

	return true;
}


TPROVISO* CQuestProviso::SelectProviso(unsigned long qid)
{
	TPROVISO_MAP::iterator iter = m_proviso_map.find(qid);
	if( iter == m_proviso_map.end() )
		return NULL;

	return iter->second;
}


bool CQuestProviso::InsertHomunLevel(const unsigned long qid, const int minLv, const int max_lv)
{
	TPROVISO* p = this->CQuestProviso::SelectProviso(qid);
	if( p == NULL )
		return false;

	p->t_homun_maxLv = max_lv;
	p->t_homun_minLv = minLv;
	return true;
}


bool CQuestProviso::InsertEvolution(const unsigned long qid, const int type)
{
	TPROVISO* p = this->CQuestProviso::SelectProviso(qid);
	if( p == NULL )
		return false;

	p->t_homun_evolution = type;
	return true;
}
