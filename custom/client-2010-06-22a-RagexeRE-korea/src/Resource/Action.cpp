#include "Globals.h"
#include "Resource/Action.h"
////////////////////////////////////////


hook_func<void (CMotion::*)(unsigned int clip_count)> CMotion::_Create("CMotion::Create");
void CMotion::Create(unsigned int clip_count)
{
	return (this->*_Create)(clip_count);
}


hook_func<CSprClip* (CMotion::*)(unsigned int clip_number)> CMotion::_GetClip("CMotion::GetClip");
CSprClip* CMotion::GetClip(unsigned int clip_number)
{
	return (this->*_GetClip)(clip_number);
}


////////////////////////////////////////


hook_func<void (CAction::*)(unsigned int motion_count)> CAction::_Create("CAction::Create");
void CAction::Create(unsigned int motion_count)
{
	return (this->*_Create)(motion_count);
}


hook_func<CMotion* (CAction::*)(unsigned int motion_number)> CAction::_GetMotion("CAction::GetMotion");
CMotion* CAction::GetMotion(unsigned int motion_number)
{
	return (this->*_GetMotion)(motion_number);
}


////////////////////////////////////////


hook_func<bool (CActRes::*)(const char *fName)> CActRes::_Load("CActRes::Load");
bool CActRes::Load(const char *fName)
{
	return (this->*_Load)(fName);
}


hook_func<CMotion* (CActRes::*)(unsigned int actIndex, unsigned int motIndex)> CActRes::_GetMotion("CActRes::GetMotion");
CMotion* CActRes::GetMotion(unsigned int actIndex, unsigned int motIndex)
{
	return (this->*_GetMotion)(actIndex, motIndex);
}


hook_func<int (CActRes::*)(unsigned int actIndex)> CActRes::_GetMotionCount("CActRes::GetMotionCount");
int CActRes::GetMotionCount(unsigned int actIndex)
{
	return (this->*_GetMotionCount)(actIndex);
}


hook_func<float (CActRes::*)(unsigned int actIndex)> CActRes::_GetDelay("CActRes::GetDelay");
float CActRes::GetDelay(unsigned int actIndex)
{
	return (this->*_GetDelay)(actIndex);
}


hook_func<const char* (CActRes::*)(int eventId)> CActRes::_GetEventName("CActRes::GetEventName");
const char* CActRes::GetEventName(int eventId)
{
	return (this->*_GetEventName)(eventId);
}


////////////////////////////////////////
