#include "ScriptLib/Block.h"


hook_method<void (CBlock::*)(void)> CBlock::_CBlock(SERVER, "CBlock::CBlock");
CBlock::CBlock(void) // line 87
{
	m_alloc = 0;
	m_pos = 0;
	m_step = 0;
	m_depth = 0;
}


hook_method<void (CBlock::*)(void)> CBlock::__CBlock(SERVER, "CBlock::~CBlock");
CBlock::~CBlock(void) // line 95
{
}


hook_method<bool (CBlock::*)(int info)> CBlock::_Start(SERVER, "CBlock::Start");
bool CBlock::Start(int info) // line 51
{
	return (this->*_Start)(info);

	if( m_alloc >= 0xFFFFFF )
		return false;

	m_stepStack.push(m_step);
	m_posStack.push(m_pos);
	++m_depth;
	m_pos = m_alloc;
	++m_alloc;
	m_step = 0;

	this->CBlock::Label(this->CBlock::GetCurId(), info);
	return true;
}


hook_method<bool (CBlock::*)(int info)> CBlock::_Link(SERVER, "CBlock::Link");
bool CBlock::Link(int info) // line 67
{
	return (this->*_Link)(info);

	if( m_step >= 0xFF )
		return false;

	++m_step;

	this->CBlock::Label(this->CBlock::GetCurId(), info);
	return true;
}


hook_method<bool (CBlock::*)(int info)> CBlock::_End(SERVER, "CBlock::End");
bool CBlock::End(int info) // line 76
{
	return (this->*_End)(info);

	//TODO
}


hook_method<int (CBlock::*)(void)> CBlock::_GetStartId(SERVER, "CBlock::GetStartId");
int CBlock::GetStartId(void) // line 27
{
	return (this->*_GetStartId)();

	return m_pos << 8;
}


hook_method<int (CBlock::*)(void)> CBlock::_GetCurId(SERVER, "CBlock::GetCurId");
int CBlock::GetCurId(void) // line 32
{
	return (this->*_GetCurId)();

	return m_step | (m_pos << 8);
}


hook_method<int (CBlock::*)(void)> CBlock::_GetNextId(SERVER, "CBlock::GetNextId");
int CBlock::GetNextId(void) // line 37
{
	return (this->*_GetNextId)();

	return (m_step + 1) | (m_pos << 8);
}


hook_method<int (CBlock::*)(void)> CBlock::_GetEndId(SERVER, "CBlock::GetEndId");
int CBlock::GetEndId(void) // line 42
{
	return (this->*_GetEndId)();

	return 0xFF | (m_pos << 8);
}


hook_method<bool (CBlock::*)(int id, int& info)> CBlock::_GetInfo(SERVER, "CBlock::GetInfo");
bool CBlock::GetInfo(int id, int& info) // line 17
{
	return (this->*_GetInfo)(id, info);

	//TODO
}


hook_method<void (CBlock::*)(char* buf)> CBlock::_GetStrInfo(SERVER, "CBlock::GetStrInfo");
void CBlock::GetStrInfo(char* buf) // line 13
{
	return (this->*_GetStrInfo)(buf);

	//TODO
}


hook_method<bool (CBlock::*)(void)> CBlock::_IsComplete(SERVER, "CBlock::IsComplete");
bool CBlock::IsComplete(void) // line 7
{
	return (this->*_IsComplete)();

	return ( m_depth == 0 );
}


hook_method<void (CBlock::*)(int id, int info)> CBlock::_Label(SERVER, "CBlock::Label");
void CBlock::Label(int id, int info) // line 47
{
	return (this->*_Label)(id, info);

	//TODO
}
