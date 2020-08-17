#include "Picker.h"


hook_func<CActorPickInfo* (CActorPickNode::*)(vector2d pos)> CActorPickNode::_FindPickInfo("CActorPickNode::FindPickInfo");
CActorPickInfo* CActorPickNode::FindPickInfo(vector2d pos)
{
	return (this->*_FindPickInfo)(pos);
}
