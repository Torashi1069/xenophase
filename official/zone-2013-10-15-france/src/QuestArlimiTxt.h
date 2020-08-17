#pragma once
#include "QVar.h"


class CQuestArlimiTxt
{
public:
	CQuestArlimiTxt();
	~CQuestArlimiTxt();

private:
	/* this+ 0 */ //const CQuestArlimiTxt::`vftable';
	/* this+ 4 */ std::list<int> m_funcStartPosList;
	/* this+16 */ CQVar m_buff;

public:
	bool LoadTxt(const char* file_name);
	bool DeleteComment();
	void ExtractionFuncPositonList(const char* funcName);
	CQVar GetNextFuncData();
	int GetFuncSize();
};
