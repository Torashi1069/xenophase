#include "CommonObject.h"


CommonObject::CommonObject(void)
{
	this->CommonObject::Clear();
}


CommonObject::~CommonObject(void)
{
	this->CommonObject::Clear();
}


hook_func<void (CommonObject::*)(void)> CommonObject::_Clear("CommonObject::Clear");
void CommonObject::Clear(void)
{
	return (this->*_Clear)();

	for( mystd::vector<char*>::iterator i = m_deleteList.begin(); i != m_deleteList.end(); ++i )
	{
		if( *i )
			delete *i;
		*i = NULL;
	}

	m_deleteList.clear();
}


hook_func<bool (CommonObject::*)(mystd::vector<const char*>& pCharList, const char* fName, int type)> CommonObject::_TokenFileToPCharList("CommonObject::TokenFileToPCharList");
bool CommonObject::TokenFileToPCharList(mystd::vector<const char*>& pCharList, const char* fName, int type)
{
	return (this->*_TokenFileToPCharList)(pCharList, fName, type);

	//TODO
}
