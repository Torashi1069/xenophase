#include "Picker.h"


hook_method<void (CActorPickNode::*)(int level, RECT region)> CActorPickNode::_MakeQuardTree(SAKEXE, "CActorPickNode::MakeQuardTree");
void CActorPickNode::MakeQuardTree(int level, RECT region)
{
	return (this->*_MakeQuardTree)(level, region);

	//TODO
}


hook_method<void (CActorPickNode::*)(void)> CActorPickNode::_DeleteSubNode(SAKEXE, "CActorPickNode::DeleteSubNode");
void CActorPickNode::DeleteSubNode(void) // line 86
{
	return (this->*_DeleteSubNode)();

	//TODO
}


hook_method<void (CActorPickNode::*)(CActorPickInfo* pickInfo)> CActorPickNode::_AddPickInfo(SAKEXE, "CActorPickNode::AddPickInfo");
void CActorPickNode::AddPickInfo(CActorPickInfo* pickInfo)
{
	return (this->*_AddPickInfo)(pickInfo);

	//TODO
}


hook_method<CActorPickInfo* (CActorPickNode::*)(vector2d pos)> CActorPickNode::_FindPickInfo(SAKEXE, "CActorPickNode::FindPickInfo");
CActorPickInfo* CActorPickNode::FindPickInfo(vector2d pos) // line 35
{
	return (this->*_FindPickInfo)(pos);

	//TODO
}
