#pragma once
#include "QuestTFSector.h"
#include "QVar.h"
#include "std/list"


class CQuestTFile
{
	/* this+ 0 */ public: // const CQuestTFile::`vftable';
	/* this+ 4 */ private: char* m_buff;
	/* this+ 8 */ private: CQVar m_var;
	/* this+52 */ private: int m_size;
	/* this+56 */ private: int m_pos;
	/* this+60 */ private: mystd::list<CQVar> m_list;
	/* this+72 */ private: mystd::list<CQuestTFSector*> m_lsSector;
	/* this+84 */ private: bool m_note;

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

	public: CQuestTFile::CQuestTFile(void);
	public: virtual CQuestTFile::~CQuestTFile(void);
	public: void CQuestTFile::Clear(void);
	public: bool CQuestTFile::Load(const char* filename);
	public: bool CQuestTFile::BlockCutting(void);
	public: bool CQuestTFile::GeneratorSector(void);
	private: bool CQuestTFile::CuttingNote(void);
	//private: int CQuestTFile::FindString(const char *);

private:
	static hook_method<void (CQuestTFile::*)(void)> CQuestTFile::_Clear;
	static hook_method<bool (CQuestTFile::*)(const char* filename)> CQuestTFile::_Load;
	static hook_method<bool (CQuestTFile::*)(void)> CQuestTFile::_BlockCutting;
	static hook_method<bool (CQuestTFile::*)(void)> CQuestTFile::_GeneratorSector;
	static hook_method<bool (CQuestTFile::*)(void)> CQuestTFile::_CuttingNote;
};
