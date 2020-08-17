#pragma once
#include "3dLib/Prim.h"
class CSkyBoxEllipse;
class CWorld;


struct ViewInfo3d
{
	/* this+ 0 */ float latitude;
	/* this+ 4 */ float longitude;
	/* this+ 8 */ float distance;
	/* this+12 */ vector3d at;
};
C_ASSERT( sizeof ViewInfo3d == 24 );


class CViewFrustum
{
	BYTE dummy[192];
};
C_ASSERT( sizeof CViewFrustum == 192 );


class CView
{
public:
	float CView::GetDestDistance();
	vector3d CView::GetFrom();
	matrix CView::GetViewMatrix();
	float CView::GetCurLongitude();

protected:
	/* this+  0 */ void* vtable; //const CView::`vftable';
	/* this+  4 */ float m_sideQuake;
	/* this+  8 */ float m_frontQuake;
	/* this+ 12 */ float m_latitudeQuake;
	/* this+ 16 */ bool m_isFPSmode;
	/* this+ 20 */ int m_isQuake;
	/* this+ 24 */ DWORD m_quakeStartTick;
	/* this+ 28 */ DWORD m_QuakeTime;
	/* this+ 32 */ vector3d m_cur_at;
	/* this+ 44 */ ViewInfo3d m_cur;
	/* this+ 68 */ ViewInfo3d m_dest;
	/* this+ 92 */ BYTE dummy[36]; //TODO
	/* this+128 */ vector3d m_from;
	/* this+140 */ vector3d m_up;
	/* this+152 */ matrix m_viewMatrix;
	/* this+200 */ matrix m_invViewMatrix;
	/* this+248 */ CViewFrustum m_viewFrustum;
	/* this+440 */ CWorld* m_world;
	/* this+444 */ CSkyBoxEllipse* m_skyBox;
};
C_ASSERT( sizeof CView == 448 );
