#pragma once
struct IDiaSymbol;


class CDiaClassMember
{
public:
	CDiaClassMember::~CDiaClassMember(void);
	int CDiaClassMember::offset(void) const;

private:
	CDiaClassMember::CDiaClassMember(IDiaSymbol* symbol);

private:
	IDiaSymbol* m_symbol;
	friend class CDiaClass;
};
