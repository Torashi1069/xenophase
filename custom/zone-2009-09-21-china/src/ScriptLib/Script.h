#pragma once
#include "ScriptLib/TokenInfo.h"
#include "std/deque"


class CScriptLine
{
	/* this+0 */ private: char* m_line;
	/* this+4 */ private: char* m_cur;

	public: CScriptLine::CScriptLine(char* line);
	public: CScriptLine::~CScriptLine(void);
	//public: bool CScriptLine::IsEmpty();
	//public: bool CScriptLine::GetWord(char *, char *);
	//public: bool CScriptLine::GetNum(int &, char *);
	//public: bool CScriptLine::GetFloat(float &, char *);
	//public: bool CScriptLine::GetOperator(char *, char *);
	//public: bool CScriptLine::GetParse(char *, char);
	//public: bool CScriptLine::GetParse(char *, char, char);
	//public: void CScriptLine::Skip(char *);
	//public: char* CScriptLine::GetCur();
	//public: char* CScriptLine::GetBase();
};


class CScriptHandler
{
	struct vtable_t
	{
		bool CScriptHandler::OnControl(CScriptLine& line, int cmd); // __purecall
		bool CScriptHandler::OnCommand(CScriptLine& line, int cmd); // __purecall
		bool CScriptHandler::OnFunc(CScriptLine& line, int cmd, char* parm); // __purecall
		bool CScriptHandler::OnVar(CScriptLine& line, char* name); // __purecall
		void CScriptHandler::Error(char* str, ...); // __purecall
	};

	/* this+0 */ public: // const CScriptHandler::`vftable';
	/* this+4 */ protected: CTokenMap* m_tokenMap;

	//public: CScriptHandler::CScriptHandler(void);
	//public: CScriptHandler::~CScriptHandler(void);
	public: virtual bool CScriptHandler::OnControl(CScriptLine& line, int cmd) = 0;
	public: virtual bool CScriptHandler::OnCommand(CScriptLine& line, int cmd) = 0;
	public: virtual bool CScriptHandler::OnFunc(CScriptLine& line, int cmd, char* parm) = 0;
	public: virtual bool CScriptHandler::OnVar(CScriptLine& line, char* name) = 0;
	//public: void CScriptHandler::SetTokenMap(class CTokenMap *);
	//public: bool CScriptHandler::AnalyzeLine(char *);
	//protected: bool CScriptHandler::AnalyzeParse(char *);
	protected: virtual void CScriptHandler::Error(char* str, ...) = 0;
};


class CScript
{
	/* this+ 0 */ private: char* m_buf;
	/* this+ 4 */ private: int m_bufSize;
	/* this+ 8 */ private: bool m_comment;
	/* this+12 */ private: mystd::deque<char*> m_line;
	/* this+44 */ private: CTokenMap m_tokenMap;
	/* this+56 */ private: CScriptHandler* m_handler;

	//public: void CScript::CScript();
	//public: void CScript::~CScript();
	//public: void CScript::Clear();
	//public: bool CScript::Load(const char *, int);
	//public: bool CScript::Analyze(int);
	public: void CScript::RegisterHandler(CScriptHandler* handler);
	//public: int CScript::GetLineNum();
	//public: char * CScript::GetLine(int);
	//private: void CScript::DivideLine();
	//private: void CScript::RemoveComment();

private:
	static hook_method<void (CScript::*)(CScriptHandler* handler)> CScript::_RegisterHandler;
};

