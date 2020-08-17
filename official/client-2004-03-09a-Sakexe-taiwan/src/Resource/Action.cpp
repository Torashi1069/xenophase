#include "Globals.h"
#include "Base/ResMgr.h"
#include "Resource/Action.h"
////////////////////////////////////////


hook_method<void (CMotion::*)(unsigned int clip_count)> CMotion::_Create(SAKEXE, "CMotion::Create");
void CMotion::Create(unsigned int clip_count) // line 21 (Action.h)
{
	return (this->*_Create)(clip_count);

	//TODO
}


hook_method<CSprClip* (CMotion::*)(unsigned int clip_number)> CMotion::_GetClip(SAKEXE, "CMotion::GetClip");
CSprClip* CMotion::GetClip(unsigned int clip_number) // line 32
{
	return (this->*_GetClip)(clip_number);

	//TODO
}


////////////////////////////////////////


hook_method<void (CAction::*)(unsigned int motion_count)> CAction::_Create(SAKEXE, "CAction::Create");
void CAction::Create(unsigned int motion_count) // line 49
{
	return (this->*_Create)(motion_count);

	//TODO
}


hook_method<CMotion* (CAction::*)(unsigned int motion_number)> CAction::_GetMotion(SAKEXE, "CAction::GetMotion");
CMotion* CAction::GetMotion(unsigned int motion_number) // line 54
{
	return (this->*_GetMotion)(motion_number);

	//TODO
}


////////////////////////////////////////


CActRes::CActRes(Exemplar __formal, const char* resid, const char* baseDir) // line 64 (Action.h)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


CActRes::CActRes(void) // line 73
: numMaxClipPerMotion(0)
{
}


hook_method<CRes* (CActRes::*)(void) const> CActRes::_Clone(SAKEXE, "CActRes::Clone");
CRes* CActRes::Clone(void) const // line 64 (Action.h)
{
	return (this->*_Clone)();

	return new CActRes();
}


hook_method<bool (CActRes::*)(const char* fName)> CActRes::_Load(SAKEXE, "CActRes::Load");
bool CActRes::Load(const char* fName) // line 116
{
	return (this->*_Load)(fName);

	//TODO
}


hook_method<void (CActRes::*)(void)> CActRes::_Reset(SAKEXE, "CActRes::Reset");
void CActRes::Reset(void) // line 85
{
	return (this->*_Reset)();

	//TODO
}


hook_method<void (CActRes::*)(unsigned int action_count)> CActRes::_Create(SAKEXE, "CActRes::Create");
void CActRes::Create(unsigned int action_count) // line 78
{
	return (this->*_Create)(action_count);

	//TODO
}


hook_method<CAction* (CActRes::*)(unsigned int action_number)> CActRes::_GetAction(SAKEXE, "CActRes::GetAction");
CAction* CActRes::GetAction(unsigned int action_number) // line 304
{
	return (this->*_GetAction)(action_number);

	if( action_number < actions.size() )
	{
		return &actions[action_number];
	}
	else
	{
		static CAction dummy_action;
		return &dummy_action;
	}
}


hook_method<CMotion* (CActRes::*)(unsigned int actIndex, unsigned int motIndex)> CActRes::_GetMotion(SAKEXE, "CActRes::GetMotion");
CMotion* CActRes::GetMotion(unsigned int actIndex, unsigned int motIndex) // line 317
{
	return (this->*_GetMotion)(actIndex, motIndex);

	CAction* action = this->CActRes::GetAction(actIndex);

	if( motIndex < action->motions.size() )
	{
		return &action->motions[motIndex];
	}
	else
	{
		static CMotion dummy_motion;
		return &dummy_motion;
	}
}


hook_method<int (CActRes::*)(unsigned int actIndex)> CActRes::_GetMotionCount(SAKEXE, "CActRes::GetMotionCount");
int CActRes::GetMotionCount(unsigned int actIndex) // line 322
{
	return (this->*_GetMotionCount)(actIndex);

	return max(1, this->CActRes::GetAction(actIndex)->motions.size());
}


hook_method<float (CActRes::*)(unsigned int actIndex)> CActRes::_GetDelay(SAKEXE, "CActRes::GetDelay");
float CActRes::GetDelay(unsigned int actIndex) // line 296
{
	return (this->*_GetDelay)(actIndex);

	return ( actIndex < m_delay.size() ) ? m_delay[actIndex] : 4.0f;
}


hook_method<const char* (CActRes::*)(int eventId)> CActRes::_GetEventName(SAKEXE, "CActRes::GetEventName");
const char* CActRes::GetEventName(int eventId) // line 106
{
	return (this->*_GetEventName)(eventId);

	return ( eventId < (int)m_events.size() ) ? m_events[eventId].c_str() : "";
}


hook_method<void (CActRes::*)(CSprClip* clip, int cx, int cy, int isHalfW, int isHalfH)> CActRes::_ReCalcClipXY(SAKEXE, "CActRes::ReCalcClipXY");
void CActRes::ReCalcClipXY(CSprClip* clip, int cx, int cy, int isHalfW, int isHalfH) // line 91
{
	return (this->*_ReCalcClipXY)(clip, cx, cy, isHalfW, isHalfH);

	//TODO
}


//hook_method<int (CActRes::*)(void)> CActRes::_GetNumMaxClipPerMotion(SAKEXE, "CActRes::GetNumMaxClipPerMotion");
int CActRes::GetNumMaxClipPerMotion(void) // line ??
{
//	return (this->*_GetNumMaxClipPerMotion)();

	return numMaxClipPerMotion;
}


////////////////////////////////////////
