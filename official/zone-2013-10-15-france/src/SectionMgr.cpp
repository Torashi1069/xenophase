#include "Character.h"
#include "Enum.h"
#include "MapRes.h"
#include "NPC.h"
#include "PC.h"
#include "Rect.h"
#include "SectionMgr.h"
#include "StackDumpLog.h"
#include "ZoneProcess.h"
#include "shared/NCriticalErrorLog.h"


/// globals
int& g_sectionCounter = VTOR<int>(DetourFindFunction(EXEPATH(), "g_sectionCounter"));


CSectionMgr::CSectionMgr()
{
	m_scale = 0;
	m_w = 0;
	m_h = 0;
	m_mapRes = NULL;
	m_sectionList = NULL;
}


CSectionMgr::~CSectionMgr()
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


void CSectionMgr::Init(const char* mapName, int w, int h, int scale, const CMapRes* mapRes)
{
	m_w = (w + scale - 1) / scale;
	m_h = (h + scale - 1) / scale;
	m_scale = scale;
	m_mapRes = mapRes;

	m_sectionList = new std::vector<CCharacter*>*[m_w * m_h];
	for( int i = 0; i < m_w * m_h; ++i )
		m_sectionList[i] = new std::vector<CCharacter*>();

	strcpy(m_mapName, mapName);
	m_MaxSectionList = m_w * m_h;
}


int CSectionMgr::GetSectionSize()
{
	return m_w * m_h;
}


std::vector<CCharacter*>** CSectionMgr::GetSectionList()
{
	return m_sectionList;
}


std::vector<CCharacter*>* CSectionMgr::GetSectionByCellPos(int x, int y)
{
	if( m_sectionList == NULL )
	{
		g_stackdumpLog.CStackDumpLog::WriteFmt(__FILE__, __LINE__, "=====> critical error must be report to program team... <=======");
		return NULL;
	}

	if( m_mapRes == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CSectionMgr::GetSectionByCellPos, mapRes=NULL, mapName=%s, x=%d, y=%d", m_mapName, x, y);
		return NULL;
	}

	if( x < 0 || y < 0 || x >= m_mapRes->CMapRes::GetWidth() || y >= m_mapRes->CMapRes::GetHeight() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "NULL Return => CSectionMgr :: GetSectionByCellPos %d %d , MapName = %s, Max Size %d %d", x, y, m_mapName, m_scale * m_w, m_scale * m_h);
		return NULL;
	}

	int i = x / m_scale + m_w * y / m_scale;
	if( i < 0 || i >= m_w * m_h )
		return NULL;

	return m_sectionList[i];
}


BOOL CSectionMgr::AddCharacter(int x, int y, CCharacter* ch)
{
	if( ch == NULL )
		return FALSE;

	std::vector<CCharacter*>* sl = this->CSectionMgr::GetSectionByCellPos(x, y);
	if( sl == NULL )
		return FALSE;
	
	if( ch->CCharacter::GetSectionList() != NULL )
		return FALSE;

	++g_sectionCounter;

	sl->push_back(ch);
	ch->CCharacter::SetSectionList(sl);

	return TRUE;
}


BOOL CSectionMgr::MoveCharacter(std::vector<CCharacter*>* src, std::vector<CCharacter*>* dst, CCharacter* ch)
{
	if( src == NULL || dst == NULL || ch == NULL )
		return FALSE;

	std::vector<CCharacter*>* sl = ch->CCharacter::GetSectionList();
	if( sl == NULL || sl != src || src == dst )
		return FALSE;

	for( std::vector<CCharacter*>::iterator iter = src->begin(); iter != src->end(); ++iter )
	{
		if( *iter == ch )
		{
			src->erase(iter);
			dst->push_back(ch);
			ch->CCharacter::SetSectionList(dst);
			return TRUE; // found.
		}
	}

	return FALSE; // not found.
}


int CSectionMgr::MoveChracter(std::vector<CCharacter*>* src, std::vector<CCharacter*>::iterator& iter, int x, int y, CCharacter* ch)
{
	if( src == NULL || ch == NULL )
		return -1;

	std::vector<CCharacter*>* sl = ch->CCharacter::GetSectionList();
	if( sl == NULL || src != sl )
		return -1;

	std::vector<CCharacter*>* sl2 = this->CSectionMgr::GetSectionByCellPos(x, y);
	if( sl2 == NULL )
		return -1;

	if( src == sl2 )
		return 0;

	src->erase(iter);
	sl2->push_back(ch);
	ch->CCharacter::SetSectionList(sl2);
	return 1;
}


void CSectionMgr::RemoveCharacter(CCharacter* ch)
{
	if( ch == NULL )
		return;

	std::vector<CCharacter*>* sl = ch->CCharacter::GetSectionList();
	if( sl == NULL )
		return;

	std::vector<CCharacter*>::iterator iter;
	for( iter = sl->begin(); iter != sl->end(); ++iter )
		if( *iter == ch )
			break;

	if( iter == sl->end() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "not find from section list");
	}
	else
	{
		sl->erase(iter);
		--g_sectionCounter;
	}

	ch->CCharacter::SetSectionList(NULL);
}


BOOL CSectionMgr::GetEmptyPosition(unsigned long AID, int& xPos, int& yPos)
{
	if( this->CSectionMgr::IsEmptyPos(AID, xPos, yPos) == TRUE )
		return 1; // no movement needed.

	std::vector<CMyPoint> vFindEmptyPos;
	vFindEmptyPos.reserve(10);
	vFindEmptyPos.push_back(CMyPoint( 1,  0));
	vFindEmptyPos.push_back(CMyPoint( 0,  1));
	vFindEmptyPos.push_back(CMyPoint(-1,  0));
	vFindEmptyPos.push_back(CMyPoint( 0, -1));
	vFindEmptyPos.push_back(CMyPoint( 1,  1));
	vFindEmptyPos.push_back(CMyPoint(-1,  1));
	vFindEmptyPos.push_back(CMyPoint(-1, -1));
	vFindEmptyPos.push_back(CMyPoint( 1, -1));

	for( int i = 1; i <= 10; ++i )
	{
		for( std::vector<CMyPoint>::const_iterator iter = vFindEmptyPos.begin(); iter != vFindEmptyPos.end(); ++iter )
		{
			int nIncX = i * iter->CMyPoint::x();
			int nIncY = i * iter->CMyPoint::y();

			if( this->CSectionMgr::IsEmptyPos(AID, xPos + nIncX, yPos + nIncY) == TRUE )
			{
				xPos += nIncX;
				yPos += nIncY;
				return 0; // found.
			}
		}
	}

	return 1; // none found.
}


BOOL CSectionMgr::IsEmptyPos(unsigned long AID, int xPos, int yPos)
{
	if( !m_mapRes->CMapRes::IsMovableCell(xPos, yPos) )
		return FALSE;

	std::vector<CCharacter*>* section = this->CSectionMgr::GetSectionByCellPos(xPos, yPos);
	if( section == NULL )
		return FALSE;

	for( std::vector<CCharacter*>::iterator iter = section->begin(); iter != section->end(); ++iter )
	{
		CCharacter* ch = *iter;

		if( AID == ch->GetAccountID() )
			continue; // skip self

		switch( ch->GetType() )
		{
		case PC_TYPE:
		{
			CPC* pc = static_cast<CPC*>(ch);
			if( pc->CPC::GetState() == CHARACTER_STATE_STAND || pc->CPC::GetState() == CHARACTER_STATE_ENTER || pc->CPC::GetState() == CHARACTER_STATE_SIT )
				if( pc->m_pathInfo.m_moveInfo.xPos == xPos && pc->m_pathInfo.m_moveInfo.yPos == yPos )
					return FALSE;
		}
		break;
		case NPC_TYPE:
		case NPC_EVT_TYPE:
		case NPC_MOB_TYPE:
		case NPC_PET_TYPE:
		{
			CNPC* npc = static_cast<CNPC*>(ch);
			if( npc->CNPC::GetJobType() == JT_WARPNPC || npc->CNPC::GetJobType() == JT_EFFECTLAUNCHER )
				continue; // ignore these
			if( npc->CNPC::GetState() == CHARACTER_STATE_STAND || npc->CNPC::GetState() == CHARACTER_STATE_ENTER )
				if( npc->m_pathInfo.m_moveInfo.xPos == xPos && npc->m_pathInfo.m_moveInfo.yPos == yPos )
					return FALSE;
		}
		break;
		};
	}

	return TRUE;
}


int CSectionMgr::GetTotalSectionSize()
{
	int result = 0;

	if( m_sectionList != NULL )
	{
		for( int i = 0; i < m_w * m_h; ++i )
		{
			result += m_sectionList[i]->size();
		}
	}

	return result;
}


std::vector<CCharacter*>* CSectionMgr::GetSectionListPtr(const int in_X, const int in_Y, const int in_Range, const int in_Idx)
{
	if( in_Idx < 0 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "x(%d) y(%d) Range(%d) Index(%d) mapname(%s)", in_X, in_Y, in_Range, in_Idx, m_mapRes->CMapRes::GetName());
		return NULL;
	}

	if( in_Idx >= m_MaxSectionList )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "x(%d) y(%d) Range(%d) Index(%d) mapname(%s)", in_X, in_Y, in_Range, in_Idx, m_mapRes->CMapRes::GetName());
		return NULL;
	}

	return m_sectionList[in_Idx];
}


void CSectionMgr::GetNeighborhoodSections(int x, int y, int range, NEIGHBORHOOD_SECTION* result)
{
	if( result == NULL )
		return;

	result->section[0] = NULL;
	result->section[1] = NULL;
	result->section[2] = NULL;
	result->section[3] = NULL;

	if( range < 1 || range > 25 )
		return;

	RECT rcRange = { x - range, y - range, x + range, y + range };
	RECT rcMap = { 0, 0, m_mapRes->CMapRes::GetWidth() - 1, m_mapRes->CMapRes::GetHeight() - 1 };
	RECT rcResult;
	if( !IntersectRect(&rcResult, &rcRange, &rcMap) )
		return;

	const int ra = rcResult.left / m_scale + m_w * rcResult.top / m_scale;
	const int rb = rcResult.right / m_scale + m_w * rcResult.bottom / m_scale;

	if( rb - ra == m_w + 1 )
	{// 4-way overlap
		result->section[0] = this->CSectionMgr::GetSectionListPtr(x, y, range, ra);
		result->section[1] = this->CSectionMgr::GetSectionListPtr(x, y, range, ra + 1);
		result->section[2] = this->CSectionMgr::GetSectionListPtr(x, y, range, ra + m_w);
		result->section[3] = this->CSectionMgr::GetSectionListPtr(x, y, range, ra + m_w + 1);
	}
	else
	if( rb != ra )
	{// 2-way overlap
		result->section[0] = this->CSectionMgr::GetSectionListPtr(x, y, range, ra);
		result->section[1] = this->CSectionMgr::GetSectionListPtr(x, y, range, rb);
	}
	else
	{// single section
		result->section[0] = this->CSectionMgr::GetSectionListPtr(x, y, range, ra);
	}
}
