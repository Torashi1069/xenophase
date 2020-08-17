#include "Resource/Emblem.h"


hook_func<bool (CEmblemRes::*)(const char* fName)> CEmblemRes::_Load("CEmblemRes::Load");
bool CEmblemRes::Load(const char* fName)
{
	return (this->*_Load)(fName);
}
