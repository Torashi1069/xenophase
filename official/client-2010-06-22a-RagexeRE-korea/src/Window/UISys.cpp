#include "Window/UISys.h"


hook_func<void (__cdecl *)(const char* msg, mystd::vector<mystd::string>& strings, int maxNumCharLine)> _CutString("CutString");
void __cdecl CutString(const char* msg, mystd::vector<mystd::string>& strings, int maxNumCharLine)
{
	return _CutString(msg, strings, maxNumCharLine);

	//TODO
}
