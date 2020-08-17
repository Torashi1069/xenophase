#include "CInterpretHandler.hpp"


CInterpretHandler::CInterpretHandler(void)
{
}


CInterpretHandler::~CInterpretHandler(void)
{
}


hook_method<void (CInterpretHandler::*)(VarMap* varMap)> CInterpretHandler::_SetVarMap(SERVER, "CInterpretHandler::SetVarMap");
void CInterpretHandler::SetVarMap(VarMap* varMap)
{
	return (this->*_SetVarMap)(varMap);

	m_varMap = varMap;
}
