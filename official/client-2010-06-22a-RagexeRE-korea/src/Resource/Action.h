#pragma once
#include "Base/Res.h"
#include "std/string"
#include "std/vector"


struct CSprClip
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int sprIndex;
	/* this+12 */ int flags;
	/* this+16 */ unsigned char r;
	/* this+17 */ unsigned char g;
	/* this+18 */ unsigned char b;
	/* this+19 */ unsigned char a;
	/* this+20 */ float zoomx;
	/* this+24 */ float zoomy;
	/* this+28 */ int angle;
	/* this+32 */ int clipType;
};
C_ASSERT( sizeof CSprClip == 36 );


struct CAttachPointInfo
{
	/* this+0 */ int x;
	/* this+4 */ int y;
	/* this+8 */ int m_attr;
};
C_ASSERT( sizeof CAttachPointInfo == 12 );


struct CMotion
{
	/* this+ 0 */ RECT range1;
	/* this+16 */ RECT range2;
	/* this+32 */ mystd::vector<CSprClip> sprClips;
	/* this+48 */ int numClips;
	/* this+52 */ int m_eventId;
	/* this+56 */ mystd::vector<CAttachPointInfo> attachInfo;
	/* this+72 */ int attachCnt;

	public: void CMotion::Create(unsigned int clip_count);
	public: CSprClip* CMotion::GetClip(unsigned int clip_number);

private:
	static hook_func<void (CMotion::*)(unsigned int clip_count)> CMotion::_Create;
	static hook_func<CSprClip* (CMotion::*)(unsigned int clip_number)> CMotion::_GetClip;
};
C_ASSERT( sizeof CMotion == 76 );


class CAction
{
	/* this+0 */ mystd::vector<CMotion> motions;

	public: void CAction::Create(unsigned int motion_count);
	public: CMotion* CAction::GetMotion(unsigned int motion_number);

public:
	static hook_func<void (CAction::*)(unsigned int motion_count)> CAction::_Create;
	static hook_func<CMotion* (CAction::*)(unsigned int motion_number)> CAction::_GetMotion;
};
C_ASSERT( sizeof CAction == 16 );


class CActRes : public CRes
{
	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ private: mystd::vector<CAction> actions;
	/* this+288 */ private: int numMaxClipPerMotion;
	/* this+292 */ private: mystd::vector<mystd::string> m_events;
	/* this+308 */ private: mystd::vector<float> m_delay;

	public: bool CActRes::Load(const char *fName);
	public: CMotion* CActRes::GetMotion(unsigned int actIndex, unsigned int motIndex);
	public: int CActRes::GetMotionCount(unsigned int actIndex);
	public: float CActRes::GetDelay(unsigned int actIndex);
	public: const char* CActRes::GetEventName(int eventId);

private:
	static hook_func<bool (CActRes::*)(const char *fName)> CActRes::_Load;
	static hook_func<CMotion* (CActRes::*)(unsigned int actIndex, unsigned int motIndex)> CActRes::_GetMotion;
	static hook_func<int (CActRes::*)(unsigned int actIndex)> CActRes::_GetMotionCount;
	static hook_func<float (CActRes::*)(unsigned int actIndex)> CActRes::_GetDelay;
	static hook_func<const char* (CActRes::*)(int eventId)> CActRes::_GetEventName;
};
C_ASSERT( sizeof CActRes == 324 );
