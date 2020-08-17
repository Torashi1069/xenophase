#include "SSIListBase.h"


/// globals
CMemoryAllocator<SSIListInfo>& gAllocatorSSIListInfo = VTOR<CMemoryAllocator<SSIListInfo>>(DetourFindFunction(EXEPATH(), "gAllocatorSSIListInfo"));


AllocSSIListInfoData::AllocSSIListInfoData()
: m_pData(NULL)
{
	m_pData = gAllocatorSSIListInfo.CMemoryAllocator<SSIListInfo>::Alloc();
	if( m_pData != NULL )
		m_pData->SSIListInfo::Clear();
}


AllocSSIListInfoData::~AllocSSIListInfoData()
{
	if( m_pData != NULL )
	{
		m_pData->SSIListInfo::Clear();
		gAllocatorSSIListInfo.CMemoryAllocator<SSIListInfo>::Free(m_pData);
		m_pData = NULL;
	}
}
