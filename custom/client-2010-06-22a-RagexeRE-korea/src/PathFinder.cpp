#include "Globals.h" // Trace()
#include "PathFinder.h"
#include "PriorityQueue.h"
#include "Resource/Attr.h"
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


bool CPathFinder::FindPath(DWORD startTime, int sx, int sy, int xM, int yM, int dx, int dy, int speedFactor, CPathInfo* pathInfo)
{
	m_destX = dx;
	m_destY = dy;

	if( sx == dx && sy == dy )
		return false;

	pathInfo->CPathInfo::ResetStartCell();
	this->CPathFinder::Reset();
	m_poolCount = 0;

	PathNode* startnode = this->CPathFinder::GetNode(sx, sy);
	startnode->type = PathNode::OPEN;
	startnode->parent = NULL;
	startnode->cost = 0;
	startnode->total = this->CPathFinder::GetHeuristicCost(sx, sy);
	m_openNodes.CPriorityQueue::Push(startnode);

	PathNode* node;
	while( 1 )
	{
		if( m_openNodes.CPriorityQueue::IsEmpty() )
		{
			Trace("find path failed : no path found");
			return false;
		}

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
			Trace("find path aborted : buffer overflow");
			return false;
		}

		node->type = PathNode::CLOSED;
	}

	float x;
	TransformCellPosFloatPos(x, sx, xM);
	pathInfo->CPathInfo::SetStartPointX(x);

	float y;
	TransformCellPosFloatPos(y, sy, yM);
	pathInfo->CPathInfo::SetStartPointY(y);

	this->CPathFinder::BuildResultPath(startTime, node, speedFactor, pathInfo);
	return true;
}


bool CPathFinder::ProcessNode(PathNode* parent, int traverseCost, int x, int y, int dir)
{
	int cost = traverseCost + parent->cost;

	PathNode* node = this->CPathFinder::GetNode(x, y);
	if( node == NULL )
		return false;

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

	return true;
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

		node->x = x;
		node->y = y;
		node->type = PathNode::UNEXPLORED;
		this->CPathFinder::AddNode(node);
	}

	return node;
}


PathNode* CPathFinder::FindNode(int x, int y)
{
	int pos = x + y * this->CPathFinder::GetMapWidth();
	mystd::map<int,PathNode*>::iterator it = m_masterNodes.find(pos);
	return ( it != m_masterNodes.end() ) ? it->second : NULL;
}


void CPathFinder::AddNode(PathNode* node)
{
	int pos = node->x + node->y * this->CPathFinder::GetMapWidth();
	m_masterNodes[pos] = node;
}


void CPathFinder::SetMap(C3dAttr* newMap)
{
	m_mapData = newMap;
}


int CPathFinder::GetMapWidth()
{
	return m_mapData->m_width;
}


int CPathFinder::GetMapHeight()
{
	return m_mapData->m_height;
}


int CPathFinder::GetHeuristicCost(int sx, int sy)
{
	return 10 * (abs(sx - m_destX) + abs(sy - m_destY));
}


/// Is there a walkable path from 's' to its neighbouring cell 'd'?
bool CPathFinder::IsConnected(int sx, int sy, int dx, int dy)
{
	CAttrCell* p;

	if( dx < 0 || dy < 0 || dx >= m_mapData->m_width || dy >= m_mapData->m_height )
		return false;

	p = m_mapData->C3dAttr::GetCell(dx, dy);
	if( p == NULL || p->flag == 1 || p->flag == 5 )
		return false;

	if( sx != dx && sy != dy )
	{// diagonal
		p = m_mapData->C3dAttr::GetCell(sx, dy);
		if( p == NULL || p->flag == 1 || p->flag == 5 )
			return false;

		p = m_mapData->C3dAttr::GetCell(dx, sy);
		if( p == NULL || p->flag == 1 || p->flag == 5 )
			return false;
	}

	return true;
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
	float xlen = path->m_pathData[1].x - path->m_startPointX;
	float ylen = path->m_pathData[1].y - path->m_startPointY;
	float dist = sqrt(xlen * xlen + ylen * ylen);

	return startTime + DWORD(dist * speedFactor);
}


class hook_ptr<struct mystd::_Tree<int,struct mystd::pair<int const ,struct PathNode *>,struct mystd::map<int,struct PathNode *,struct mystd::less<int>,class mystd::allocator<struct PathNode *> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct PathNode *> >::_Node *> mystd::_Tree<int,struct mystd::pair<int const ,struct PathNode *>,struct mystd::map<int,struct PathNode *,struct mystd::less<int>,class mystd::allocator<struct PathNode *> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct PathNode *> >::_Nil("?_Nil@?$_Tree@HU?$pair@$$CBHPAUPathNode@@@std@@U_Kfn@?$map@HPAUPathNode@@U?$less@H@std@@V?$allocator@PAUPathNode@@@3@@2@U?$less@H@2@V?$allocator@PAUPathNode@@@2@@std@@1PAU_Node@12@A");
class hook_val<unsigned int> mystd::_Tree<int,struct mystd::pair<int const ,struct PathNode *>,struct mystd::map<int,struct PathNode *,struct mystd::less<int>,class mystd::allocator<struct PathNode *> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct PathNode *> >::_Nilrefs("?_Nilrefs@?$_Tree@HU?$pair@$$CBHPAUPathNode@@@std@@U_Kfn@?$map@HPAUPathNode@@U?$less@H@std@@V?$allocator@PAUPathNode@@@3@@2@U?$less@H@2@V?$allocator@PAUPathNode@@@2@@std@@1IA");


////////////////////////////////////////


CPathInfo::CPathInfo()
{
	this->CPathInfo::ResetStartCell();
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
		return 0;
	}

	int i;
	for( i = m_startCell; size_t(i) < m_pathData.size() - 1; ++i )
		if( m_pathData[i].time <= (DWORD)time && (DWORD)time < m_pathData[i + 1].time )
			break; // found.

	if( size_t(i) >= m_pathData.size() - 1 )
	{// not found.
		xPos = float(m_pathData[i].x);
		yPos = float(m_pathData[i].y);
		dir = m_pathData[i].dir;
		return -1;
	}

	float xMovingDistance, yMovingDistance;
	if( i != 0 )
	{
		xMovingDistance = float(m_pathData[i + 1].x - m_pathData[i].x);
		yMovingDistance = float(m_pathData[i + 1].y - m_pathData[i].y);
	}
	else
	{
		xMovingDistance = float(m_pathData[1].x - m_startPointX);
		yMovingDistance = float(m_pathData[1].y - m_startPointY);
	}

	float xlen = xMovingDistance * (time - m_pathData[i].time) / (m_pathData[i + 1].time - m_pathData[i].time);
	if( i != 0 )
		xPos = m_pathData[i].x + xlen;
	else
		xPos = m_startPointX + xlen;

	float ylen = yMovingDistance * (time - m_pathData[i].time) / (m_pathData[i + 1].time - m_pathData[i].time);
	if( i != 0 )
		yPos = m_pathData[i].y + ylen;
	else
		yPos = m_startPointY + ylen;

	if( (DWORD)time >= m_pathData[i].time + (m_pathData[i + 1].time - m_pathData[i].time) / 2 )
		dir = m_pathData[i + 1].dir;
	else
		dir = m_pathData[i].dir;

	m_startCell = i;
	return i;
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


void CPathInfo::GetLastCellTime(DWORD& lastCellTime)
{
	lastCellTime = m_pathData.back().time;
}


int CPathInfo::GetNextCellInfo(DWORD currentTime, DWORD& Time, float& x, float& y)
{
	if( m_pathData.size() == 0 || m_pathData[0].time == 0 )
		return -1;

	if( currentTime < m_pathData[0].time )
	{
		Time = m_pathData[1].time;
		x = float(m_pathData[1].x);
		y = float(m_pathData[1].y);
		return 0;
	}

	int i;
	for( i = 0; size_t(i) < m_pathData.size() - 1; ++i )
		if( currentTime >= m_pathData[i].time && currentTime < m_pathData[i + 1].time )
			break; // found.

	if( size_t(i) >= m_pathData.size() - 1 )
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


////////////////////////////////////////
