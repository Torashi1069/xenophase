#pragma once
struct IDiaSymbol;


class CDiaClassMethod
{
public:
	CDiaClassMethod::~CDiaClassMethod(void);
	int CDiaClassMethod::voffset(void) const;


private:
	CDiaClassMethod::CDiaClassMethod(IDiaSymbol* symbol);

//private:
public:
	IDiaSymbol* m_symbol;
	friend class CDiaClass;
};
