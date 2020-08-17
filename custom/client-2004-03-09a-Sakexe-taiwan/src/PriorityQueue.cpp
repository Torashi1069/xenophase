#include "PriorityQueue.h"


void CPriorityQueue::Reset()
{
	this->heap.clear();
}


void CPriorityQueue::Push(PathNode* node)
{
	this->heap.push_back(node);
	mystd::push_heap(this->heap.begin(), this->heap.end(), CPriorityQueue::NodeTotalGreater());
}


PathNode* CPriorityQueue::Pop()
{
	PathNode* node = this->heap.front();
	mystd::pop_heap(this->heap.begin(), this->heap.end(), CPriorityQueue::NodeTotalGreater());
	this->heap.pop_back();
	return node;
}


void CPriorityQueue::UpdateNode(PathNode* node)
{
	for( mystd::vector<PathNode*>::iterator it = this->heap.begin(); it != this->heap.end(); ++it )
	{
		if( (*it)->x == node->x && (*it)->y == node->y )
		{
			mystd::push_heap(this->heap.begin(), it + 1, CPriorityQueue::NodeTotalGreater());
			break;
		}
	}
}


bool CPriorityQueue::IsEmpty()
{
	return ( this->heap.size() == 0 );
}
