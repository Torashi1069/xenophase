#include "QFile.h"
#include "QuestArlimiTxt.h"


CQuestArlimiTxt::CQuestArlimiTxt()
{
}


CQuestArlimiTxt::~CQuestArlimiTxt()
{
	m_buff.CQVar::Delete(0, m_buff.CQVar::length());
}


bool CQuestArlimiTxt::LoadTxt(const char* file_name)
{
	CQFile file;

	std::pair<bool,int> ret = file.CQFile::Open(file_name);
	if( !ret.first )
	{
		char error[256] = {};
		_snprintf_s(error, countof(error), _TRUNCATE, "CQuestArlimiTxt::LoadTxt File Not Found filename = %s", file_name);
		MessageBoxA(NULL, error, "NOTIFYQUEST ERROR", MB_OK);
		return false;
	}

	int txtLen = ret.second;
	char* txt = (char*)_malloca(txtLen + 1);

	if( file.CQFile::Read(txt, txtLen) != txtLen )
	{
		if( txt != NULL )
			_freea(txt);

		return false;
	}

	txt[txtLen] = '\0';
	m_buff = txt;

	if( txt != NULL )
		_freea(txt);

	return true;
}


bool CQuestArlimiTxt::DeleteComment()
{
	for( ; ; )
	{
		int cPos = m_buff.CQVar::FindToken("/*");
		int dPos = m_buff.CQVar::FindToken(cPos, "*/");
		if( cPos < 1 )
			break;
		if( dPos < 1 )
		{
			MessageBoxA(NULL, " CQuestArlimiTxt::DeleteComment Comment Error", "NOTIFYQUEST ERROR", MB_OK);
			return false;
		}

		m_buff.CQVar::Delete(cPos, dPos - cPos + 2);
	}

	for( ; ; )
	{
		int cPos = m_buff.CQVar::FindToken("//");
		if( cPos == -1 )
			break;
		int dPos = m_buff.CQVar::FindToken(cPos, "\n");
		if( dPos == -1 )
			dPos = m_buff.CQVar::length();

		m_buff.CQVar::Delete(cPos, dPos - cPos + 1);
	}

	return true;
}


void CQuestArlimiTxt::ExtractionFuncPositonList(const char* funcName)
{
	int funcPos = m_buff.CQVar::FindToken(funcName);
	m_funcStartPosList.push_back(funcPos);
	if( funcPos == -1 )
		return;

	for( ; ; )
	{
		int pos = m_buff.CQVar::FindToken(funcPos + strlen(funcName), funcName);
		if( pos == -1 )
			break;

		funcPos = pos;
		m_funcStartPosList.push_back(pos);
	}

	m_buff.CQVar::Trim_Right();
	m_funcStartPosList.push_back(m_buff.CQVar::length());
}


CQVar CQuestArlimiTxt::GetNextFuncData()
{
	if( m_funcStartPosList.size() <= 1 )
	{
		m_funcStartPosList.clear();
		return NULL; //FIXME: integer type
	}

	int stPos = m_funcStartPosList.front();
	m_funcStartPosList.pop_front();
	int edPos = m_funcStartPosList.front() - stPos;

	CQVar func = m_buff.CQVar::SubStr(stPos, edPos);
	return func.CQVar::o_str();
}


int CQuestArlimiTxt::GetFuncSize()
{
	return (int)m_funcStartPosList.size();
}
