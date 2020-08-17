#include "Movie/CBink.h"


hook_func<void (CBink::*)(int flag)> CBink::_OpenningMain("CBink::OpenningMain");
void CBink::OpenningMain(int flag)
{
	return (this->*_OpenningMain)(flag);
}


CBink& g_Bink = VTOR<CBink>(SymDB::Find("g_Bink"));
