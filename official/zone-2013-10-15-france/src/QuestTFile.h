#pragma once
#include "QuestTFSector.h"
#include "QVar.h"


class CQuestTFile
{
public:
	CQuestTFile();
	virtual ~CQuestTFile();

private:
	enum
	{
		TOKEN_TYPE_UNKONOW        = 0,
		TOKEN_TYPE_SPACE          = 1,
		TOKEN_TYPE_NOTE           = 2,
		TOKEN_TYPE_NOTE_END       = 3,
		TOKEN_TYPE_QUOTATION_MARK = 4,
		TOKEN_TYPE_APOSTEROPHE    = 5,
		TOKEN_TYPE_LEFT_BRACE     = 6,
		TOKEN_TYPE_RIGHT_BRACE    = 7,
		TOKEN_TYPE_LEFT_BRACKET   = 8,
		TOKEN_TYPE_RIGHT_BRACKET  = 9,
		TOKEN_TYPE_LINE           = 10,
		TOKEN_TYPE_RETURN         = 11,
		TOKEN_TYPE_TAB            = 12,
		TOKEN_TYPE_END            = 13,
		TOKEN_TYPE_SLASH          = 14,
		TOKEN_TYPE_ASTERISK       = 15,
	};

private:
	/* this+ 0 */ //const CQuestTFile::`vftable';
	/* this+ 4 */ char* m_buff;
	/* this+ 8 */ CQVar m_var;
	/* this+52 */ int m_size;
	/* this+56 */ int m_pos;
	/* this+60 */ std::list<CQVar> m_list;
	/* this+72 */ std::list<CQuestTFSector*> m_lsSector;
	/* this+84 */ bool m_note;

public:
	void Clear();
	bool Load(const char* filename);
	bool BlockCutting();
	bool GeneratorSector();

private:
	bool CuttingNote();
	int FindString(const char* ptr);
};
