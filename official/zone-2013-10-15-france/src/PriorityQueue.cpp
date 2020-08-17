#include "PriorityQueue.h"


void CPriorityQueue::Reset()
{
	this->heap.clear();
}


void CPriorityQueue::Push(PathNode* node)
{
	this->heap.push_back(node);
	std::push_heap(this->heap.begin(), this->heap.end(), NodeTotalGreater());
}


PathNode* CPriorityQueue::Pop()
{
	PathNode* node = this->heap.front();
	std::pop_heap(this->heap.begin(), this->heap.end(), NodeTotalGreater());
	this->heap.pop_back();
	return node;
}


void CPriorityQueue::UpdateNode(PathNode* node)
{
	for( std::vector<PathNode*>::iterator i = this->heap.begin(); i != this->heap.end(); ++i )
	{
		if( (*i)->x == node->x && (*i)->y == node->y )
		{
			std::push_heap(this->heap.begin(), i + 1, NodeTotalGreater());
			break;
		}
	}
}


BOOL CPriorityQueue::IsEmpty()
{
	return ( this->heap.empty() );
}
