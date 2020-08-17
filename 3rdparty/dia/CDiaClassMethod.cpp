#include "CDiaClassMethod.hpp"
#include "dia2.h"


CDiaClassMethod::CDiaClassMethod(IDiaSymbol* symbol)
{
	m_symbol = symbol;
}


CDiaClassMethod::~CDiaClassMethod(void)
{
	m_symbol->Release();
}


int CDiaClassMethod::voffset(void) const
{
	BOOL bIsVirtual;
	DWORD dwOffset;
	return( m_symbol->get_virtual(&bIsVirtual) == S_OK && bIsVirtual && m_symbol->get_virtualBaseOffset(&dwOffset) == S_OK ) ? dwOffset : -1;
}
