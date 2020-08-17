#include "Path.h"
#include "CreatePackageScript.h"
#include "shared.h" // Trace()
#include "globals.hpp"


CCreatePackageScript*& CCreatePackageScript::m_cpSelf = *(CCreatePackageScript**)DetourFindFunction(SERVER, "CCreatePackageScript::m_cpSelf"); // = ?


CCreatePackageScript::CCreatePackageScript(void) // line 18
{
	m_bOK = true;
}


CCreatePackageScript::~CCreatePackageScript(void) // line 25
{
}


hook_method<static CCreatePackageScript* (__cdecl *)(void)> CCreatePackageScript::_GetObj(SERVER, "CCreatePackageScript::GetObj");
CCreatePackageScript* CCreatePackageScript::GetObj(void) // line 36
{
	return (CCreatePackageScript::_GetObj)();

	if( m_cpSelf == NULL )
		m_cpSelf = new CCreatePackageScript();

	return m_cpSelf;
}


//hook_method<bool (CCreatePackageScript::*)(void)> CCreatePackageScript::_isOK(SERVER, "CCreatePackageScript::isOK");
bool CCreatePackageScript::isOK(void) // line ??
{
//	return (this->*_isOK)();

	return m_bOK;
}


hook_method<bool (CCreatePackageScript::*)(void)> CCreatePackageScript::_Init(SERVER, "CCreatePackageScript::Init");
bool CCreatePackageScript::Init(void) // line 120
{
	return (this->*_Init)();

	char buffer[260];

	CCreatePackageScript::ANAYSISRET Ret = this->CCreatePackageScript::Anaysis(g_pathData->CPathData::SetFileName("CreatePackage.txt"));
	switch( Ret.Code )
	{
	case 0:
		return true;
	case 1:
		_snprintf(buffer, sizeof(buffer), "error found\n \"%s\"(Line:%d,Col:%d)", Ret.Token.CFTToken::GetSTRING().c_str(), Ret.Token.CFTToken::GetLine(), Ret.Token.CFTToken::GetCol());
		break;
	case 2:
		_snprintf(buffer, sizeof(buffer), "lexical anaysis initialize error");
		break;
	case 3:
		_snprintf(buffer, sizeof(buffer), "can't get token\n \"%s\"(Line:%d,Col:%d)", Ret.Token.CFTToken::GetSTRING().c_str(), Ret.Token.CFTToken::GetLine(), Ret.Token.CFTToken::GetCol());
		break;
	case 4:
		_snprintf(buffer, sizeof(buffer), "syntax error\n \"%s\"(Line:%d,Col:%d)", Ret.Token.CFTToken::GetSTRING().c_str(), Ret.Token.CFTToken::GetLine(), Ret.Token.CFTToken::GetCol());
		break;
	case 6:
		_snprintf(buffer, sizeof(buffer), "insert package error");
		break;
	case 7:
		_snprintf(buffer, sizeof(buffer), "insert box error");
		break;
	case 8:
		_snprintf(buffer, sizeof(buffer), "unknown item id\n \"%s\"(Line:%d,Col:%d)", Ret.Token.CFTToken::GetSTRING().c_str(), Ret.Token.CFTToken::GetLine(), Ret.Token.CFTToken::GetCol());
		break;
	case 9:
		Trace("CCreatePackageScript::Init, Not Existed CreatePackage.txt\n");
		return true;
	case 10:
		_snprintf(buffer, sizeof(buffer), "equip item must have count is one\n \"%s\"(Line:%d,Col:%d)", Ret.Token.CFTToken::GetSTRING().c_str(), Ret.Token.CFTToken::GetLine(), Ret.Token.CFTToken::GetCol());
		break;
	default:
		_snprintf(buffer, sizeof(buffer), "unknown syntex error");
		break;
	}

	MessageBoxA(NULL, buffer, "CreatePackage.txt", MB_OK);
	return false;
}


hook_method<CCreatePackageScript::ANAYSISRET (CCreatePackageScript::*)(const mystd::string in_strFileName)> CCreatePackageScript::_Anaysis(SERVER, "CCreatePackageScript::Anaysis");
CCreatePackageScript::ANAYSISRET CCreatePackageScript::Anaysis(const mystd::string in_strFileName) // line 321
{
	return (this->*_Anaysis)(in_strFileName);

	//TODO
}
