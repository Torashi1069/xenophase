#include "CPCMCStoreItemIV.hpp"


hook_method<IVItItem* (CPCMCStoreItemIV::*)(short index, short count)> CPCMCStoreItemIV::_Remove(SERVER, "CPCMCStoreItemIV::Remove");
hook_method<int (CPCMCStoreItemIV::*)(short index)> CPCMCStoreItemIV::_GetPrice(SERVER, "CPCMCStoreItemIV::GetPrice");


IVItItem* CPCMCStoreItemIV::Remove(short index, short count)
{
	return (this->*_Remove)(index, count);

	//TODO
}


int CPCMCStoreItemIV::GetPrice(short index)
{
	return (this->*_GetPrice)(index);

	//TODO
}
