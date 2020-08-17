#include "PriorityQueue.h"


void CPriorityQueue::Reset()
{
	this->heap.clear();
}


void CPriorityQueue::Push(PathNode* node)
{
	this->heap.push_back(node);
	mystd::push_heap(this->heap.begin(), this->heap.end(), NodeTotalGreater());
}


PathNode* CPriorityQueue::Pop()
{
	PathNode* node = this->heap.front();
	mystd::pop_heap(this->heap.begin(), this->heap.end(), NodeTotalGreater());
	this->heap.pop_back();
	return node;
}


void CPriorityQueue::UpdateNode(PathNode* node)
{
	for( mystd::vector<PathNode*>::iterator i = this->heap.begin(); i != this->heap.end(); ++i )
	{
		if( (*i)->x == node->x && (*i)->y == node->y )
		{
			mystd::push_heap(this->heap.begin(), i + 1, NodeTotalGreater());
			break;
		}
	}
}


bool CPriorityQueue::IsEmpty()
{
	return ( this->heap.empty() );
}
