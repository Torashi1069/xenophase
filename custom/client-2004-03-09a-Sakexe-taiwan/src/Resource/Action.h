#pragma once
#include "Struct.h"
#include "Base/Res.h"


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


struct CAttachPointInfo
{
	/* this+0 */ int x;
	/* this+4 */ int y;
	/* this+8 */ int m_attr;
};


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
	static hook_method<void (CMotion::*)(unsigned int clip_count)> CMotion::_Create;
	static hook_method<CSprClip* (CMotion::*)(unsigned int clip_number)> CMotion::_GetClip;
};


struct CAction
{
	/* this+0 */ mystd::vector<CMotion> motions;

	public: void CAction::Create(unsigned int motion_count);
	public: CMotion* CAction::GetMotion(unsigned int motion_number);

private:
	static hook_method<void (CAction::*)(unsigned int motion_count)> CAction::_Create;
	static hook_method<CMotion* (CAction::*)(unsigned int motion_number)> CAction::_GetMotion;
};


class CActRes : public CRes
{
	struct vtable_t
	{
		void* (CActRes::* scalar_deleting_destructor)(unsigned int flags);
		bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (CActRes::* Clone)(void) const;
		bool (CActRes::* Load)(const char* fName);
		void (CActRes::* Reset)(void);
		void (CRes::* OnLoadError)(const char* fName);
	};

	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ private: mystd::vector<CAction> actions;
	/* this+288 */ private: int numMaxClipPerMotion;
	/* this+292 */ private: mystd::vector<mystd::string> m_events;
	/* this+308 */ private: mystd::vector<float> m_delay;

	public: CActRes::CActRes(Exemplar __formal, const char* resid, const char* baseDir);
	public: CActRes::CActRes(void);
	public: virtual CRes* CActRes::Clone(void) const;
	public: virtual bool CActRes::Load(const char* fName);
	public: virtual void CActRes::Reset(void);
	public: void CActRes::Create(unsigned int action_count);
	public: CAction* CActRes::GetAction(unsigned int action_number);
	public: CMotion* CActRes::GetMotion(unsigned int actIndex, unsigned int motIndex);
	public: int CActRes::GetMotionCount(unsigned int actIndex);
	//public: int GetActionCount();
	public: float CActRes::GetDelay(unsigned int actIndex);
	public: const char* CActRes::GetEventName(int eventId);
	public: void CActRes::ReCalcClipXY(CSprClip* clip, int cx, int cy, int isHalfW, int isHalfH);
	public: int CActRes::GetNumMaxClipPerMotion(void);

private:
	static hook_method<CRes* (CActRes::*)(void) const> CActRes::_Clone;
	static hook_method<bool (CActRes::*)(const char* fName)> CActRes::_Load;
	static hook_method<void (CActRes::*)(void)> CActRes::_Reset;
	static hook_method<void (CActRes::*)(unsigned int action_count)> CActRes::_Create;
	static hook_method<CAction* (CActRes::*)(unsigned int action_number)> CActRes::_GetAction;
	static hook_method<CMotion* (CActRes::*)(unsigned int actIndex, unsigned int motIndex)> CActRes::_GetMotion;
	static hook_method<int (CActRes::*)(unsigned int actIndex)> CActRes::_GetMotionCount;
	static hook_method<float (CActRes::*)(unsigned int actIndex)> CActRes::_GetDelay;
	static hook_method<const char* (CActRes::*)(int eventId)> CActRes::_GetEventName;
	static hook_method<void (CActRes::*)(CSprClip* clip, int cx, int cy, int isHalfW, int isHalfH)> CActRes::_ReCalcClipXY;
	static hook_method<int (CActRes::*)(void)> CActRes::_GetNumMaxClipPerMotion;
};
