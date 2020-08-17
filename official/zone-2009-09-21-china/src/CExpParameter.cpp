#include "CExpParameter.hpp"


CExpParameter::CExpParameter(void)
{
}


CExpParameter::~CExpParameter(void)
{
}


hook_method<void (CExpParameter::*)(const char* Script)> CExpParameter::_Init(SERVER, "CExpParameter::Init");
void CExpParameter::Init(const char* Script)
{
	return (this->*_Init)(Script);

	//TODO
}


hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetExpParameter(SERVER, "CExpParameter::GetExpParameter");
void CExpParameter::GetExpParameter(void)
{
	return (this->*_GetExpParameter)();

	//TODO
}


hook_method<int (CExpParameter::*)(short level, short job)> CExpParameter::_GetNextExp(SERVER, "?GetNextExp@CExpParameter@@QAEHFF@Z");
int CExpParameter::GetNextExp(short level, short job)
{
	return (this->*_GetNextExp)(level, job);

	//TODO
}


hook_method<int (CExpParameter::*)(short level)> CExpParameter::_GetNextExp2(SERVER, "?GetNextExp@CExpParameter@@QAEHF@Z");
int CExpParameter::GetNextExp(short level)
{
	return (this->*_GetNextExp2)(level);

	//TODO
}


hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetNoviceExpParameter(SERVER, "CExpParameter::GetNoviceExpParameter");
void CExpParameter::GetNoviceExpParameter(void)
{
	return (this->*_GetNoviceExpParameter)();

	//TODO
}


hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetSecondExpParameter(SERVER, "CExpParameter::GetSecondExpParameter");
void CExpParameter::GetSecondExpParameter(void)
{
	return (this->*_GetSecondExpParameter)();

	//TODO
}


hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetFirstJobExpParameter(SERVER, "CExpParameter::GetFirstJobExpParameter");
void CExpParameter::GetFirstJobExpParameter(void)
{
	return (this->*_GetFirstJobExpParameter)();

	//TODO
}


hook_method<int (CExpParameter::*)(short level, short job)> CExpParameter::_GetNextJobExp(SERVER, "CExpParameter::GetNextJobExp");
int CExpParameter::GetNextJobExp(short level, short job)
{
	return (this->*_GetNextJobExp)(level, job);

	//TODO
}


hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetGuildExpParameter(SERVER, "CExpParameter::GetGuildExpParameter");
void CExpParameter::GetGuildExpParameter(void)
{
	return (this->*_GetGuildExpParameter)();

	//TODO
}


hook_method<int (CExpParameter::*)(short level)> CExpParameter::_GetGuildNextExp(SERVER, "CExpParameter::GetGuildNextExp");
int CExpParameter::GetGuildNextExp(short level)
{
	return (this->*_GetGuildNextExp)(level);

	//TODO
}


hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetExpParameter2(SERVER, "CExpParameter::GetExpParameter2");
void CExpParameter::GetExpParameter2(void)
{
	return (this->*_GetExpParameter2)();

	//TODO
}


hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetNoviceExpParameter2(SERVER, "CExpParameter::GetNoviceExpParameter2");
void CExpParameter::GetNoviceExpParameter2(void)
{
	return (this->*_GetNoviceExpParameter2)();

	//TODO
}


hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetFirstJobExpParameter2(SERVER, "CExpParameter::GetFirstJobExpParameter2");
void CExpParameter::GetFirstJobExpParameter2(void)
{
	return (this->*_GetFirstJobExpParameter2)();

	//TODO
}


hook_method<void (CExpParameter::*)(void)> CExpParameter::_Get_Ninja_Gunner_JobExpParameter(SERVER, "CExpParameter::Get_Ninja_Gunner_JobExpParameter");
void CExpParameter::Get_Ninja_Gunner_JobExpParameter(void)
{
	return (this->*_Get_Ninja_Gunner_JobExpParameter)();

	//TODO
}


hook_method<void (CExpParameter::*)(void)> CExpParameter::_GetSecondJobExpParameter2(SERVER, "CExpParameter::GetSecondJobExpParameter2");
void CExpParameter::GetSecondJobExpParameter2(void)
{
	return (this->*_GetSecondJobExpParameter2)();

	//TODO
}


hook_method<void (CExpParameter::*)(char* fileName)> CExpParameter::_InitExpTable_Homun(SERVER, "CExpParameter::InitExpTable_Homun");
void CExpParameter::InitExpTable_Homun(char* fileName)
{
	return (this->*_InitExpTable_Homun)(fileName);

	//TODO
}


hook_method<int (CExpParameter::*)(short level)> CExpParameter::_GetNextExp_Homun(SERVER, "CExpParameter::GetNextExp_Homun");
int CExpParameter::GetNextExp_Homun(short level)
{
	return (this->*_GetNextExp_Homun)(level);

	//TODO
}
