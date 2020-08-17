#include "N2IDAllocator.h"


hook_ptr<N2IDAllocator*> N2IDAllocator::m_cpSelf(SERVER, "N2IDAllocator::m_cpSelf");


hook_method<unsigned int (N2IDAllocator::*)(const unsigned short in_GroupID)> N2IDAllocator::_Alloc(SERVER, "N2IDAllocator::Alloc");
unsigned int N2IDAllocator::Alloc(const unsigned short in_GroupID)
{
	return (this->*_Alloc)(in_GroupID);

	//TODO
}


hook_method<void (N2IDAllocator::*)(const unsigned int in_ID)> N2IDAllocator::_Free(SERVER, "N2IDAllocator::Free");
void N2IDAllocator::Free(const unsigned int in_ID)
{
	return (this->*_Free)(in_ID);

	//TODO
}


/// @custom
N2IDAllocator* N2IDAllocator::GetObj(void)
{
	return m_cpSelf;
}
