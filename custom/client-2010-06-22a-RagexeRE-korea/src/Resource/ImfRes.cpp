#include "Resource/ImfRes.h"


hook_func<int (CImfRes::*)(int Priority, int Act, int Mot)> CImfRes::_GetLayer("CImfRes::GetLayer");
int CImfRes::GetLayer(int Priority, int Act, int Mot)
{
	return (this->*_GetLayer)(Priority, Act, Mot);
}
