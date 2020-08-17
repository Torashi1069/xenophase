#pragma once


struct PathNode
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ PathNode* parent;
	/* this+12 */ int cost;
	/* this+16 */ int total;
	/* this+20 */ int type; // enum
	/* this+24 */ int dir;

	enum
	{
		UNEXPLORED = 0,
		OPEN       = 1,
		CLOSED     = 2,
	};
};


class CPriorityQueue
{
public:
	void Reset();
	PathNode* Pop();
	void Push(PathNode* node);
	void UpdateNode(PathNode* node);
	bool IsEmpty();

private:
	/* this+0 */ mystd::vector<PathNode*> heap;

private:
	class NodeTotalGreater
	{
	public:
		bool operator()(PathNode* l, PathNode* r)
		{
			return ( l->total > r->total );
		}
	};
};
