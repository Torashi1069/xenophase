#include "SectionMgr.h"
#include "ErrorLog.h"
#include "MapRes.h"
#include "globals.hpp"


CSectionMgr::CSectionMgr(void) // line 15
{
	m_scale = 0;
	m_w = 0;
	m_h = 0;
	m_mapRes = NULL;
	m_sectionList = NULL;
}


CSectionMgr::~CSectionMgr(void) // line 24
{
	if( m_sectionList != NULL )
	{
		for( int i = 0; i < m_h * m_w; ++i )
		{
			if( m_sectionList[i] != NULL )
			{
				delete m_sectionList[i];
				m_sectionList[i] = NULL;
			}
		}

		delete[] m_sectionList;
		m_sectionList = NULL;
	}
}


hook_method<void (CSectionMgr::*)(const char* mapName, int w, int h, int scale, const CMapRes* mapRes)> CSectionMgr::_Init(SERVER, "CSectionMgr::Init");
void CSectionMgr::Init(const char* mapName, int w, int h, int scale, const CMapRes* mapRes) // line 41
{
	return (this->*_Init)(mapName, w, h, scale, mapRes);

	//TODO
}


hook_method<mystd::vector<CCharacter*>* (CSectionMgr::*)(int x, int y)> CSectionMgr::_GetSectionByCellPos(SERVER, "CSectionMgr::GetSectionByCellPos");
mystd::vector<CCharacter*>* CSectionMgr::GetSectionByCellPos(int x, int y) // line 66
{
	return (this->*_GetSectionByCellPos)(x, y);

	//TODO
}


hook_method<int (CSectionMgr::*)(unsigned long AID, int& xPos, int& yPos)> CSectionMgr::_GetEmptyPosition(SERVER, "CSectionMgr::GetEmptyPosition");
int CSectionMgr::GetEmptyPosition(unsigned long AID, int& xPos, int& yPos) // line 218
{
	return (this->*_GetEmptyPosition)(AID, xPos, yPos);

	//TODO
}


hook_method<int (CSectionMgr::*)(int x, int y, CCharacter* ch)> CSectionMgr::_AddCharacter(SERVER, "CSectionMgr::AddCharacter");
int CSectionMgr::AddCharacter(int x, int y, CCharacter* ch) // line 108
{
	return (this->*_AddCharacter)(x, y, ch);

	//TODO
}


hook_method<void (CSectionMgr::*)(CCharacter* ch)> CSectionMgr::_RemoveCharacter(SERVER, "CSectionMgr::RemoveCharacter");
void CSectionMgr::RemoveCharacter(CCharacter* ch) // line 191
{
	return (this->*_RemoveCharacter)(ch);

	//TODO
}


hook_method<int (CSectionMgr::*)(void)> CSectionMgr::_GetTotalSectionSize(SERVER, "CSectionMgr::GetTotalSectionSize");
int CSectionMgr::GetTotalSectionSize(void) // line 304
{
	return (this->*_GetTotalSectionSize)();

	//TODO
}


hook_method<int (CSectionMgr::*)(mystd::vector<CCharacter*>* src, mystd::vector<CCharacter*>* dst, CCharacter* ch)> CSectionMgr::_MoveCharacter(SERVER, "CSectionMgr::MoveCharacter");
int CSectionMgr::MoveCharacter(mystd::vector<CCharacter*>* src, mystd::vector<CCharacter*>* dst, CCharacter* ch) // line 126
{
	return (this->*_MoveCharacter)(src, dst, ch);

	//TODO
}


hook_method<void (CSectionMgr::*)(int x, int y, int range, NEIGHBORHOOD_SECTION* result)> CSectionMgr::_GetNeighborhoodSections(SERVER, "CSectionMgr::GetNeighborhoodSections");
void CSectionMgr::GetNeighborhoodSections(int x, int y, int range, NEIGHBORHOOD_SECTION* result) // line 384
{
	return (this->*_GetNeighborhoodSections)(x, y, range, result);

	if( result == NULL )
		return;

	result->section[0] = NULL;
	result->section[1] = NULL;
	result->section[2] = NULL;
	result->section[3] = NULL;

	if( range > 25 )
		return;

	RECT rcRange;
	rcRange.left = x - range;
	rcRange.right = x + range;
	rcRange.top = y - range;
	rcRange.bottom = y + range;

	RECT rcMap;
	rcMap.left = 0;
	rcMap.top = 0;
	rcMap.right = m_mapRes->CMapRes::GetWidth() - 1;
	rcMap.bottom = m_mapRes->CMapRes::GetHeight() - 1;

	RECT rcResult;
	if( IntersectRect(&rcResult, &rcRange, &rcMap) == 0 )
		return; // they do not intersect.

	int startIdx = rcResult.left / m_scale + rcResult.top / m_scale * m_w;
	int endIdx = rcResult.right / m_scale + rcResult.bottom / m_scale * m_w;

	if( endIdx == startIdx + m_w + 1 )
	{// 4-way overlap
		result->section[0] = this->CSectionMgr::GetSectionListPtr(x, y, range, startIdx);
		result->section[1] = this->CSectionMgr::GetSectionListPtr(x, y, range, startIdx + 1);
		result->section[2] = this->CSectionMgr::GetSectionListPtr(x, y, range, startIdx + m_w);
		result->section[3] = this->CSectionMgr::GetSectionListPtr(x, y, range, startIdx + m_w + 1);
	}
	else
	if( endIdx != startIdx )
	{// 2-way overlap
		result->section[0] = this->CSectionMgr::GetSectionListPtr(x, y, range, startIdx);
		result->section[1] = this->CSectionMgr::GetSectionListPtr(x, y, range, endIdx);
	}
	else
	{// single section
		result->section[0] = this->CSectionMgr::GetSectionListPtr(x, y, range, startIdx);
	}
}


hook_method<int (CSectionMgr::*)(void)> CSectionMgr::_GetSectionSize(SERVER, "CSectionMgr::GetSectionSize");
int CSectionMgr::GetSectionSize(void) // line 57
{
	return (this->*_GetSectionSize)();

	return m_w * m_h;
}


//hook_method<mystd::vector<CCharacter*>** (CSectionMgr::*)(void)> CSectionMgr::_GetSectionList(SERVER, "CSectionMgr::GetSectionList");
mystd::vector<CCharacter*>** CSectionMgr::GetSectionList(void) // line ??? (aliased)
{
//	return (this->*_GetSectionList)();

	return m_sectionList;
}


hook_method<int (CSectionMgr::*)(unsigned long AID, int xPos, int yPos)> CSectionMgr::_IsEmptyPos(SERVER, "CSectionMgr::IsEmptyPos");
int CSectionMgr::IsEmptyPos(unsigned long AID, int xPos, int yPos) // line 265
{
	return (this->*_IsEmptyPos)(AID, xPos, yPos);

	//TODO
}


hook_method<mystd::vector<CCharacter*>* (CSectionMgr::*)(const int in_X, const int in_Y, const int in_Range, const int in_Idx)> CSectionMgr::_GetSectionListPtr(SERVER, "CSectionMgr::GetSectionListPtr");
mystd::vector<CCharacter*>* CSectionMgr::GetSectionListPtr(const int in_X, const int in_Y, const int in_Range, const int in_Idx) // line 365
{
	return (this->*_GetSectionListPtr)(in_X, in_Y, in_Range, in_Idx);

	if( in_Idx < 0 )
	{
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\SectionMgr.cpp", 366, "x(%d) y(%d) Range(%d) Index(%d) mapname(%s)", in_X, in_Y, in_Range, in_Idx, m_mapRes->CMapRes::GetName());
		return NULL;
	}

	if( in_Idx >= m_MaxSectionList )
	{
		g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\SectionMgr.cpp", 370, "x(%d) y(%d) Range(%d) Index(%d) mapname(%s)", in_X, in_Y, in_Range, in_Idx, m_mapRes->CMapRes::GetName());
		return NULL;
	}

	return m_sectionList[in_Idx];
}
