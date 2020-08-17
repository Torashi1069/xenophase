#include "granny.h"


hook_func<granny_model_instance* (__stdcall *)(granny_model const* Model)> _GrannyInstantiateModel("granny2.dll", "_GrannyInstantiateModel@4");
granny_model_instance* __stdcall GrannyInstantiateModel(granny_model const* Model)
{
	return _GrannyInstantiateModel(Model);
}


hook_func<granny_skeleton* (__stdcall *)(granny_model_instance const* Model)> _GrannyGetSourceSkeleton("granny2.dll", "_GrannyGetSourceSkeleton@4");
granny_skeleton* __stdcall GrannyGetSourceSkeleton(granny_model_instance const* Model)
{
	return _GrannyGetSourceSkeleton(Model);
}


hook_func<void (__stdcall *)(granny_model_instance const* ModelInstance, granny_real32 NewClock)> _GrannySetModelClock("granny2.dll", "_GrannySetModelClock@8");
void __stdcall GrannySetModelClock(granny_model_instance const* ModelInstance, granny_real32 NewClock)
{
	return _GrannySetModelClock(ModelInstance, NewClock);
}


hook_func<void (__stdcall *)(granny_model_instance const* ModelInstance)> _GrannyFreeCompletedModelControls("granny2.dll", "_GrannyFreeCompletedModelControls@4");
void __stdcall GrannyFreeCompletedModelControls(granny_model_instance const* ModelInstance)
{
	return _GrannyFreeCompletedModelControls(ModelInstance);
}


hook_func<void (__stdcall *)(granny_model_instance const* ModelInstance, granny_int32x FirstBone, granny_int32x BoneCount, granny_local_pose* Result)> _GrannySampleModelAnimations("granny2.dll", "_GrannySampleModelAnimations@16");
void __stdcall GrannySampleModelAnimations(granny_model_instance const* ModelInstance, granny_int32x FirstBone, granny_int32x BoneCount, granny_local_pose* Result)
{
	return _GrannySampleModelAnimations(ModelInstance, FirstBone, BoneCount, Result);
}


hook_func<void (__stdcall *)(granny_control* Control)> _GrannyFreeControl("granny2.dll", "_GrannyFreeControl@4");
void __stdcall GrannyFreeControl(granny_control* Control)
{
	return _GrannyFreeControl(Control);
}


hook_func<float (__stdcall *)(granny_control* Control)> _GrannyGetControlDurationLeft("granny2.dll", "_GrannyGetControlDurationLeft@4");
float __stdcall GrannyGetControlDurationLeft(granny_control* Control)
{
	return _GrannyGetControlDurationLeft(Control);
}


hook_func<bool (__stdcall *)(granny_control const* Control)> _GrannyControlIsActive("granny2.dll", "_GrannyControlIsActive@4");
bool __stdcall GrannyControlIsActive(granny_control const* Control)
{
	return _GrannyControlIsActive(Control);
}


hook_func<void (__stdcall *)(granny_control* Control, bool Active)> _GrannySetControlActive("granny2.dll", "_GrannySetControlActive@8");
void __stdcall GrannySetControlActive(granny_control* Control, bool Active)
{
	return _GrannySetControlActive(Control, Active);
}


hook_func<granny_int32x (__stdcall *)(granny_mesh const* Mesh)> _GrannyGetMeshIndexCount("granny2.dll", "_GrannyGetMeshIndexCount@4");
granny_int32x __stdcall GrannyGetMeshIndexCount(granny_mesh const* Mesh)
{
	return _GrannyGetMeshIndexCount(Mesh);
}


hook_func<granny_system_clock (__stdcall *)()> _GrannyGetSystemSeconds("granny2.dll", "_GrannyGetSystemSeconds@0");
granny_system_clock __stdcall GrannyGetSystemSeconds()
{
	return _GrannyGetSystemSeconds();
}


hook_func<float (__stdcall *)(const granny_system_clock* StartClock, const granny_system_clock* EndClock)> _GrannyGetSecondsElapsed("granny2.dll", "_GrannyGetSecondsElapsed@8");
float __stdcall GrannyGetSecondsElapsed(const granny_system_clock* StartClock, const granny_system_clock* EndClock)
{
	return _GrannyGetSecondsElapsed(StartClock, EndClock);
}


hook_func<void (__stdcall *)(granny_skeleton const* Skeleton, granny_int32x FirstBone, granny_int32x BoneCount, granny_local_pose const* LocalPose, granny_real32 const* Offset4x4, granny_world_pose* Result)> _GrannyBuildWorldPose("granny2.dll", "_GrannyBuildWorldPose@24");
void __stdcall GrannyBuildWorldPose(granny_skeleton const* Skeleton, granny_int32x FirstBone, granny_int32x BoneCount, granny_local_pose const* LocalPose, granny_real32 const* Offset4x4, granny_world_pose* Result)
{
	return _GrannyBuildWorldPose(Skeleton, FirstBone, BoneCount, LocalPose, Offset4x4, Result);
}
