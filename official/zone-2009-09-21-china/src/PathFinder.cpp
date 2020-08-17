#include "ErrorLog.h"
#include "globals.hpp"
#include "MapRes.h"
#include "PathFinder.h"
#include "shared/shared.h" // Trace()
#include <math.h> // sqrt()
////////////////////////////////////////


CPathFinder::CPathFinder()
{
}


CPathFinder::~CPathFinder()
{
	this->CPathFinder::Reset();
}


void CPathFinder::Reset()
{
	m_masterNodes.clear();
	m_openNodes.CPriorityQueue::Reset();
}


BOOL CPathFinder::FindPath(DWORD startTime, int sx, int sy, int xM, int yM, int dx, int dy, int speedFactor, CPathInfo* pathInfo)
{
	m_destX = dx;
	m_destY = dy;

	if( sx == dx && sy == dy )
		return FALSE;

	if( abs(dx - sx) + abs(dy - sy) > 24 )
		return FALSE;

	pathInfo->CPathInfo::ResetStartCell();
	this->CPathFinder::Reset();
	m_poolCount = 0;

	PathNode* startNode = this->CPathFinder::GetNode(sx, sy);
	startNode->type = PathNode::OPEN;
	startNode->parent = NULL;
	startNode->cost = 0;
	startNode->total = this->CPathFinder::GetHeuristicCost(sx, sy);
	m_openNodes.CPriorityQueue::Push(startNode);

	int nIterMax = 0;
	PathNode* node;
	while( 1 )
	{
		if( nIterMax > 600 )
			return FALSE;

		if( m_openNodes.CPriorityQueue::IsEmpty() )
			return FALSE;

		node = m_openNodes.CPriorityQueue::Pop();
		if( node->x == dx && node->y == dy )
			break; // path found.

		if( this->CPathFinder::IsConnected(node->x, node->y, node->x + 1, node->y - 1) && !this->CPathFinder::ProcessNode(node, 14, node->x + 1, node->y - 1, 5)
		||  this->CPathFinder::IsConnected(node->x, node->y, node->x + 1, node->y    ) && !this->CPathFinder::ProcessNode(node, 10, node->x + 1, node->y    , 6)
		||  this->CPathFinder::IsConnected(node->x, node->y, node->x + 1, node->y + 1) && !this->CPathFinder::ProcessNode(node, 14, node->x + 1, node->y + 1, 7)
		||  this->CPathFinder::IsConnected(node->x, node->y, node->x    , node->y + 1) && !this->CPathFinder::ProcessNode(node, 10, node->x    , node->y + 1, 0)
		||  this->CPathFinder::IsConnected(node->x, node->y, node->x - 1, node->y + 1) && !this->CPathFinder::ProcessNode(node, 14, node->x - 1, node->y + 1, 1)
		||  this->CPathFinder::IsConnected(node->x, node->y, node->x - 1, node->y    ) && !this->CPathFinder::ProcessNode(node, 10, node->x - 1, node->y    , 2)
		||  this->CPathFinder::IsConnected(node->x, node->y, node->x - 1, node->y - 1) && !this->CPathFinder::ProcessNode(node, 14, node->x - 1, node->y - 1, 3)
		||  this->CPathFinder::IsConnected(node->x, node->y, node->x    , node->y - 1) && !this->CPathFinder::ProcessNode(node, 10, node->x    , node->y - 1, 4) )
		{
			return FALSE;
		}

		node->type = PathNode::CLOSED;
		++nIterMax;
	}

	float x;
	TransformCellPosFloatPos(x, sx, xM);
	pathInfo->CPathInfo::SetStartPointX(x);

	float y;
	TransformCellPosFloatPos(y, sy, yM);
	pathInfo->CPathInfo::SetStartPointY(y);

	this->CPathFinder::BuildResultPath(startTime, node, speedFactor, pathInfo);
	return TRUE;
}


BOOL CPathFinder::ProcessNode(PathNode* parent, int traverseCost, int x, int y, int dir)
{
	int cost = traverseCost + parent->cost;

	PathNode* node = this->CPathFinder::GetNode(x, y);
	if( node == NULL )
		return FALSE;

	if( node->type == PathNode::UNEXPLORED )
	{
		node->type = PathNode::OPEN;
		node->parent = parent;
		node->cost = cost;
		node->dir = dir;
		node->total = cost + this->CPathFinder::GetHeuristicCost(x, y);

		m_openNodes.CPriorityQueue::Push(node);
	}
	else
	if( cost < node->cost )
	{// better path found, update and recalc
		node->parent = parent;
		node->cost = cost;
		node->dir = dir;
		node->total = cost + this->CPathFinder::GetHeuristicCost(x, y);

		if( node->type == PathNode::OPEN )
			m_openNodes.CPriorityQueue::UpdateNode(node);
		else
		if( node->type == PathNode::CLOSED )
			node->type = PathNode::OPEN;
	}

	return TRUE;
}


PathNode* CPathFinder::GetNewNode()
{
	if( m_poolCount >= countof(m_nodePool) - 1 )
		return NULL;

	return &m_nodePool[m_poolCount++];
}


PathNode* CPathFinder::GetNode(int x, int y)
{
	PathNode* node = this->CPathFinder::FindNode(x, y);
	if( node == NULL )
	{
		node = this->CPathFinder::GetNewNode();
		if( node == NULL )
			return NULL;

		node->type = PathNode::UNEXPLORED;
		node->x = x;
		node->y = y;
		this->CPathFinder::AddNode(node);
	}

	return node;
}


PathNode* CPathFinder::FindNode(int x, int y)
{
	int pos = x + y * this->CPathFinder::GetMapWidth();
	mystd::map<int,PathNode*>::iterator i = m_masterNodes.find(pos);
	return ( i != m_masterNodes.end() ) ? i->second : NULL;
}


void CPathFinder::AddNode(PathNode* node)
{
	int pos = node->x + node->y * this->CPathFinder::GetMapWidth();
	m_masterNodes[pos] = node;
}


void CPathFinder::SetMap(CMapRes* newMap)
{
	m_mapData = newMap;
}


int CPathFinder::GetMapWidth()
{
	__try
	{
	return m_mapData->CMapRes::GetWidth();
	}
	__except(true)
	{
	SYSTEMTIME st;
	GetLocalTime(&st);

	char str[128];
	sprintf(str, "::%u일_%u:%u:%u", st.wDay, st.wHour, st.wMinute, st.wSecond);

	char temp[256];
	strcpy(temp, "GetMapWidth Exception :");
	strcat(temp, str);

	g_errorLogs->CErrorLog::CriticalErrorLog(temp, __LINE__, __FILE__);
	return 0;
	}
}


int CPathFinder::GetMapHeight()
{
	return m_mapData->CMapRes::GetHeight();
}


int CPathFinder::GetHeuristicCost(int sx, int sy)
{
	return 10 * (abs(sx - m_destX) + abs(sy - m_destY));
}


/// Is there a walkable path from 's' to its neighbouring cell 'd'?
BOOL CPathFinder::IsConnected(int sx, int sy, int dx, int dy) /// @client
{
	return m_mapData->CMapRes::IsConnected(sx, sy, dx, dy);
}


void CPathFinder::BuildResultPath(DWORD startTime, PathNode* goalNode, int speedFactor, CPathInfo* path)
{
	int numNodes = 0;
	for( PathNode* node = goalNode; node != NULL; node = node->parent )
		++numNodes;

	path->m_pathData.resize(numNodes);
	if( numNodes <= 1 )
		return;

	PathNode* node = goalNode;
	for( int i = numNodes; i > 0; --i )
	{
		path->m_pathData[i - 1].x = node->x;
		path->m_pathData[i - 1].y = node->y;
		path->m_pathData[i - 1].dir = node->dir;
		node = node->parent;
	}

	path->m_pathData[0].dir = path->m_pathData[1].dir;
	path->m_pathData[numNodes - 1].dir = path->m_pathData[numNodes - 2].dir;

	int diagonalMoveFactor = int(speedFactor * 1.414f);

	path->m_pathData[0].time = startTime;
	path->m_pathData[1].time = this->CPathFinder::GetSecondNodeArrivalTime(startTime, path, speedFactor);

	for( int i = 1; i < numNodes - 1; ++i )
	{
		if( path->m_pathData[i + 1].dir % 2 == 0 )
			path->m_pathData[i + 1].time = path->m_pathData[i].time + speedFactor;
		else
			path->m_pathData[i + 1].time = path->m_pathData[i].time + diagonalMoveFactor;
	}
}


DWORD CPathFinder::GetSecondNodeArrivalTime(DWORD startTime, CPathInfo* path, int speedFactor)
{
	float xlen = float(path->m_pathData[1].x - path->m_startPointX);
	float ylen = float(path->m_pathData[1].y - path->m_startPointY);
	float dist = sqrt(xlen * xlen + ylen * ylen);

	return startTime + DWORD(dist * speedFactor);
}


////////////////////////////////////////


CPathInfo::CPathInfo()
{
	this->CPathInfo::ResetStartCell();
	m_pathData.reserve(120);
}


void CPathInfo::ResetStartCell()
{
	m_startCell = 0;
}


int CPathInfo::GetPos(int speedFactor, int time, float& xPos, float& yPos, int& dir)
{
	if( m_pathData.size() == 0 || (DWORD)time < m_pathData[0].time )
	{
		xPos = float(m_pathData[0].x);
		yPos = float(m_pathData[0].y);
		dir = m_pathData[1].dir;
		return -2;
	}

	int index;
	for( index = m_startCell; (size_t)index < m_pathData.size() - 1; ++index )
		if( (DWORD)time >= m_pathData[index].time && (DWORD)time < m_pathData[index + 1].time )
			break; // found.

	if( (size_t)index >= m_pathData.size() - 1 )
	{// not found.
		xPos = float(m_pathData[index].x);
		yPos = float(m_pathData[index].y);
		dir = m_pathData[index].dir;
		this->CPathInfo::ResetStartCell();
		return -1;
	}

	int movingTime = time - m_pathData[index].time;

	float xlen, ylen;
	if( index != 0 )
	{
		xlen = float(m_pathData[index + 1].x - m_pathData[index].x);
		ylen = float(m_pathData[index + 1].y - m_pathData[index].y);
	}
	else
	{
		xlen = float(m_pathData[1].x - m_startPointX);
		ylen = float(m_pathData[1].y - m_startPointY);
	}

	float xStartPos = ( index == 0 ) ? m_startPointX : float(m_pathData[index].x);
	float xMovingDistance = xlen * movingTime / (m_pathData[index + 1].time - m_pathData[index].time);
	xPos = xStartPos + xMovingDistance;

	float yStartPos = ( index == 0 ) ? m_startPointY : float(m_pathData[index].y);
	float yMovingDistance = ylen * movingTime / (m_pathData[index + 1].time - m_pathData[index].time);
	yPos = yStartPos + yMovingDistance;

	if( (DWORD)time < m_pathData[index].time + (m_pathData[index + 1].time - m_pathData[index].time) / 2 )
		dir = m_pathData[index].dir;
	else
		dir = m_pathData[index + 1].dir;

	m_startCell = index;
	return index;
}


BOOL CPathInfo::IsBackDestination()
{
	int backPos = int(m_pathData.size() - 1);
	if( backPos < 1 )
		return TRUE;

	return ( timeGetTime() >= m_pathData[backPos - 1].time );
}


int CPathInfo::GetNextPos(DWORD time, int& x, int& y)
{
	if( (size_t)m_startCell + 2 >= m_pathData.size() )
		return 0;
	
	if( time < m_pathData[m_startCell].time || time >= m_pathData[m_startCell + 1].time )
		return 0;

	x = m_pathData[m_startCell + 2].x;
	y = m_pathData[m_startCell + 2].y;
	return m_startCell + 2;
}


int CPathInfo::GetStartCellNumber()
{
	return m_startCell;
}


void CPathInfo::SetStartPointX(float x)
{
	m_startPointX = x;
}


void CPathInfo::SetStartPointY(float y)
{
	m_startPointY = y;
}


void CPathInfo::SetStartCellNumber(int num)
{
	m_startCell = num;
}


float CPathInfo::GetStartPointX()
{
	return m_startPointX;
}


float CPathInfo::GetStartPointY()
{
	return m_startPointY;
}


DWORD CPathInfo::GetTotalExpectedMovingTime()
{
	return m_pathData.back().time - m_pathData.front().time;
}


int CPathInfo::GetNextCellInfo(DWORD currentTime, DWORD& Time, float& x, float& y)
{
	if( currentTime < m_pathData[0].time )
	{
		Time = m_pathData[1].time;
		x = float(m_pathData[1].x);
		y = float(m_pathData[1].y);
		return 1;
	}

	size_t i;
	for( i = 0; i < m_pathData.size() - 1; ++i )
		if( currentTime >= m_pathData[i].time && currentTime < m_pathData[i + 1].time )
			break; // found.

	if( i >= m_pathData.size() - 1 )
	{// not found.
		Time = m_pathData[i].time;
		x = float(m_pathData[i].x);
		y = float(m_pathData[i].y);
		return -1;
	}

	Time = m_pathData[i + 1].time;
	x = float(m_pathData[i + 1].x);
	y = float(m_pathData[i + 1].y);
	return i;
}


void CPathInfo::Reset()
{
	m_pathData.clear();
}


void CPathInfo::Delay(DWORD curTime, DWORD delay)
{
	Trace("path size:%d\n", m_pathData.size());

	for( size_t i = 0; i < m_pathData.size(); ++i )
		if( m_pathData[i].time > curTime )
			m_pathData[i].time += delay;
}


////////////////////////////////////////
