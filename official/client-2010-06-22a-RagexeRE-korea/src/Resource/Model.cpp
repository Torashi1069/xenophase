#include "Resource/Model.h"


hook_func<void (C3dGrannyBoneRes::*)(void)> C3dGrannyBoneRes::_Init("C3dGrannyBoneRes::Init");
void C3dGrannyBoneRes::Init(void)
{
	return (this->*_Init)();
}


hook_func<bool (C3dGrannyBoneRes::*)(const char* fName, int nType, int nAniIdx)> C3dGrannyBoneRes::_AddBone("C3dGrannyBoneRes::AddBone");
bool C3dGrannyBoneRes::AddBone(const char* fName, int nType, int nAniIdx)
{
	return (this->*_AddBone)(fName, nType, nAniIdx);
}


C3dGrannyBoneRes& g_GrannyBoneRes = VTOR<C3dGrannyBoneRes>(SymDB::Find("g_GrannyBoneRes"));
