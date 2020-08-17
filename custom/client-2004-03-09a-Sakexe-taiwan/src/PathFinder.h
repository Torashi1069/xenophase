#pragma once
#include "PriorityQueue.h"
class C3dAttr; // #include "Resource/Attr.h"


struct PathCell
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int dir;
	/* this+12 */ DWORD time;
};


class CPathInfo
{
public:
	CPathInfo();
	int GetPos(int speedFactor, int time, float& xPos, float& yPos, int& dir);
	int GetStartCellNumber();
	void SetStartCellNumber(int num);
	void SetStartPointX(float x);
	void SetStartPointY(float y);
	float GetStartPointX();
	float GetStartPointY();
	DWORD GetTotalExpectedMovingTime();
	int GetNextCellInfo(DWORD currentTime, DWORD& Time, float& x, float& y);
	void GetLastCellTime(DWORD& lastCellTime);

protected:
	/* this+ 0 */ mystd::vector<PathCell> m_pathData;
	friend class CPathFinder;

protected:
	void ResetStartCell();

protected:
	/* this+16 */ int m_startCell;
	/* this+20 */ float m_startPointX;
	/* this+24 */ float m_startPointY;
};


class CPathFinder
{
public:
	CPathFinder();
	~CPathFinder();

public:
	void Reset();
	void SetMap(C3dAttr* newMap);
	bool FindPath(DWORD startTime, int sx, int sy, int xM, int yM, int dx, int dy, int speedFactor, CPathInfo* pathInfo);

private:
	int GetMapWidth();
	int GetMapHeight();
	int GetHeuristicCost(int sx, int sy);
	bool IsConnected(int sx, int sy, int dx, int dy);

private:
	/* this+   0 */ C3dAttr* m_mapData;
	/* this+   4 */ int m_destX;
	/* this+   8 */ int m_destY;

private:
	bool ProcessNode(PathNode* parent, int traverseCost, int x, int y, int dir);
	void BuildResultPath(DWORD startTime, PathNode* goalNode, int speedFactor, CPathInfo* path);
	DWORD GetSecondNodeArrivalTime(DWORD startTime, CPathInfo* path, int speedFactor);

private:
	PathNode* GetNewNode();

private:
	/* this+  12 */ int m_poolCount;
	/* this+  16 */ PathNode m_nodePool[150];

private:
	PathNode* GetNode(int x, int y);
	PathNode* FindNode(int x, int y);
	void AddNode(PathNode* node);

private:
	/* this+4216 */ mystd::map<int,PathNode*> m_masterNodes;
	/* this+4232 */ CPriorityQueue m_openNodes;
};


inline void TransformFloatPosCellPos(float fPos, int& cell, int& subcell)
{
	if( fPos > 0.0 )
	{
		double pos = fPos + 0.5;
		float frac = float(pos - int(pos));

		cell = int(pos);
		subcell = int(frac * 16.0);
	}
	else
	{
		cell = 0;
		subcell = 0;
	}
}


inline void TransformCellPosFloatPos(float& fPos, int cell, int subcell)
{
	if( cell > 0 )
		fPos = float(cell - 0.5 + subcell / 16.0);
	else
		fPos = float(             subcell / 16.0);
}
