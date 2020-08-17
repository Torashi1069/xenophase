#pragma once
#include "std/map"
#include "std/stack"


class CBlock
{
	/* this+ 0 */ private: int m_alloc;
	/* this+ 4 */ private: int m_pos;
	/* this+ 8 */ private: int m_step;
	/* this+12 */ private: int m_depth;
	/* this+16 */ private: mystd::stack<int> m_posStack;
	/* this+48 */ private: mystd::stack<int> m_stepStack;
	/* this+80 */ private: mystd::map<int,int> m_infoMap;

	public: CBlock::CBlock(void);
	public: CBlock::~CBlock(void);
	public: bool CBlock::Start(int info);
	public: bool CBlock::Link(int info);
	public: bool CBlock::End(int info);
	public: int CBlock::GetStartId(void);
	public: int CBlock::GetCurId(void);
	public: int CBlock::GetNextId(void);
	public: int CBlock::GetEndId(void);
	public: bool CBlock::GetInfo(int id, int& info);
	public: void CBlock::GetStrInfo(char* buf);
	public: bool CBlock::IsComplete(void);
	private: void CBlock::Label(int id, int info);

private:
	static hook_method<void (CBlock::*)(void)> CBlock::_CBlock;
	static hook_method<void (CBlock::*)(void)> CBlock::__CBlock;
	static hook_method<bool (CBlock::*)(int info)> CBlock::_Start;
	static hook_method<bool (CBlock::*)(int info)> CBlock::_Link;
	static hook_method<bool (CBlock::*)(int info)> CBlock::_End;
	static hook_method<int (CBlock::*)(void)> CBlock::_GetStartId;
	static hook_method<int (CBlock::*)(void)> CBlock::_GetCurId;
	static hook_method<int (CBlock::*)(void)> CBlock::_GetNextId;
	static hook_method<int (CBlock::*)(void)> CBlock::_GetEndId;
	static hook_method<bool (CBlock::*)(int id, int& info)> CBlock::_GetInfo;
	static hook_method<void (CBlock::*)(char* buf)> CBlock::_GetStrInfo;
	static hook_method<bool (CBlock::*)(void)> CBlock::_IsComplete;
	static hook_method<void (CBlock::*)(int id, int info)> CBlock::_Label;
};
