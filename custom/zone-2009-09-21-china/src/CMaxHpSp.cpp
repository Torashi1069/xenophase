#include "CMaxHpSp.hpp"


CMaxHpSp::CMaxHpSp(void) // line 23
{
}


CMaxHpSp::~CMaxHpSp(void) // line 27
{
}


hook_method<void (CMaxHpSp::*)(void)> CMaxHpSp::_Init(SERVER, "CMaxHpSp::Init");
void CMaxHpSp::Init(void) // line 157
{
	return (this->*_Init)();

	//TODO
}


hook_method<int (CMaxHpSp::*)(void)> CMaxHpSp::_LoadSp(SERVER, "CMaxHpSp::LoadSp");
int CMaxHpSp::LoadSp(void) // line 93
{
	return (this->*_LoadSp)();

	//TODO
}


hook_method<int (CMaxHpSp::*)(void)> CMaxHpSp::_LoadHp(SERVER, "CMaxHpSp::LoadHp");
int CMaxHpSp::LoadHp(void) // line 31
{
	return (this->*_LoadHp)();

	//TODO
}


//hook_method<int (CMaxHpSp::*)(int nJob, int nLevel)> CMaxHpSp::_GetSp(SERVER, "CMaxHpSp::GetSp");
int CMaxHpSp::GetSp(int nJob, int nLevel)
{
//	return (this->*_GetSp)(nJob, nLevel);

	return CMaxHpSp::GetSp2(nJob, nLevel);
}


//hook_method<int (CMaxHpSp::*)(int nJob, int nLevel)> CMaxHpSp::_GetHp(SERVER, "CMaxHpSp::GetHp");
int CMaxHpSp::GetHp(int nJob, int nLevel)
{
//	return (this->*_GetHp)(nJob, nLevel);

	return CMaxHpSp::GetHp2(nJob, nLevel);
}


hook_method<int (CMaxHpSp::*)(void)> CMaxHpSp::_LoadMaxHPSP(SERVER, "CMaxHpSp::LoadMaxHPSP");
int CMaxHpSp::LoadMaxHPSP(void) // lind 174
{
	return (this->*_LoadMaxHPSP)();

	//TODO
}


hook_method<int (CMaxHpSp::*)(void)> CMaxHpSp::_LoadSp2(SERVER, "CMaxHpSp::LoadSp2");
int CMaxHpSp::LoadSp2(void)
{
	return (this->*_LoadSp2)();

	//TODO
}


hook_method<int (CMaxHpSp::*)(void)> CMaxHpSp::_LoadHp2(SERVER, "CMaxHpSp::LoadHp2");
int CMaxHpSp::LoadHp2(void)
{
	return (this->*_LoadHp2)();

	//TODO
}


hook_method<int (CMaxHpSp::*)(int nJob, int nLevel)> CMaxHpSp::_GetSp2(SERVER, "CMaxHpSp::GetSp2");
int CMaxHpSp::GetSp2(int nJob, int nLevel)
{
	return (this->*_GetSp2)(nJob, nLevel);

	//TODO
}


hook_method<int (CMaxHpSp::*)(int nJob, int nLevel)> CMaxHpSp::_GetHp2(SERVER, "CMaxHpSp::GetHp2");
int CMaxHpSp::GetHp2(int nJob, int nLevel)
{
	return (this->*_GetHp2)(nJob, nLevel);

	//TODO
}
