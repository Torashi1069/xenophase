#pragma once
#include "CDiaClassMember.hpp"
#include "CDiaClassMethod.hpp"
struct IDiaSymbol;


class CDiaClass
{
public:
	CDiaClass::~CDiaClass(void);

	CDiaClassMember CDiaClass::findMember(wchar_t memberName[]) const;
	CDiaClassMethod CDiaClass::findMethod(wchar_t methodName[]) const;
	int CDiaClass::size(void) const;

private:
	CDiaClass::CDiaClass(IDiaSymbol* symbol);

private:
	IDiaSymbol* m_symbol;
	friend class CDia;
};
