#include "CDiaClassMember.hpp"
#include "dia2.h"


CDiaClassMember::CDiaClassMember(IDiaSymbol* symbol)
{
	m_symbol = symbol;
}


CDiaClassMember::~CDiaClassMember(void)
{
	m_symbol->Release();
}


int CDiaClassMember::offset(void) const
{
	LONG lOffset;
	return( m_symbol->get_offset(&lOffset) == S_OK ) ? (int)lOffset : -1;
}
