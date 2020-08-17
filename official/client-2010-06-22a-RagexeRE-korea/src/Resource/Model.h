#pragma once


class C3dGrannyBoneRes
{
	public: void C3dGrannyBoneRes::Init(void);
	public: bool C3dGrannyBoneRes::AddBone(const char* fName, int nType, int nAniIdx);

public:
	static hook_func<void (C3dGrannyBoneRes::*)(void)> C3dGrannyBoneRes::_Init;
	static hook_func<bool (C3dGrannyBoneRes::*)(const char* fName, int nType, int nAniIdx)> C3dGrannyBoneRes::_AddBone;
};


extern C3dGrannyBoneRes& g_GrannyBoneRes;
