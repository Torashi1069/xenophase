#include "3dLib/D3dutil.h"
#include "3dLib/Prim.h"
#include <math.h>


hook_func<void (__cdecl *)(DDSURFACEDESC2& ddsd, DWORD dwFlags, DWORD dwCaps)> _D3DUtil_InitSurfaceDesc(SAKEXE, "D3DUtil_InitSurfaceDesc");
void __cdecl D3DUtil_InitSurfaceDesc(DDSURFACEDESC2& ddsd, DWORD dwFlags, DWORD dwCaps) // line 21
{
	return (_D3DUtil_InitSurfaceDesc)(ddsd, dwFlags, dwCaps);

	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = dwFlags;
	ddsd.ddsCaps.dwCaps = dwCaps;
	ddsd.ddpfPixelFormat.dwSize = 32;
}


hook_func<void (__cdecl *)(D3DVIEWPORT7& vp, DWORD dwWidth, DWORD dwHeight)> _D3DUtil_InitViewport(SAKEXE, "D3DUtil_InitViewport");
void __cdecl D3DUtil_InitViewport(D3DVIEWPORT7& vp, DWORD dwWidth, DWORD dwHeight) // line 34
{
	return (_D3DUtil_InitViewport)(vp, dwWidth, dwHeight);

	memset(&vp, 0, sizeof(vp));
	vp.dwWidth = dwWidth;
	vp.dwHeight = dwHeight;
	vp.dvMaxZ = 1.0f;
}


hook_func<HRESULT (__cdecl *)(D3DMATRIX& mat, float fFOV, float fAspect, float fNearPlane, float fFarPlane)> _D3DUtil_SetProjectionMatrix(SAKEXE, "D3DUtil_SetProjectionMatrix");
HRESULT __cdecl D3DUtil_SetProjectionMatrix(D3DMATRIX& mat, float fFOV, float fAspect, float fNearPlane, float fFarPlane) // line 46
{
	return (_D3DUtil_SetProjectionMatrix)(mat, fFOV, fAspect, fNearPlane, fFarPlane);

	//TODO: clean this up

	double v5 = fFarPlane - fNearPlane;
	if( fabs(v5) < 0.01f )
		return E_INVALIDARG;

	float v12 = fFOV * 0.5f;
	if( fabs(_sin(v12)) < 0.01f )
		return E_INVALIDARG;

	double v15 = _cos(v12) / _sin(v12) * fAspect;
	double v8 = _cos(v12) / _sin(v12);
	double v10 = fFarPlane / v5;

	memset(&mat, 0, sizeof(mat));
	mat._11 = (float)v15;
	mat._22 = (float)v8;
	mat._33 = (float)v10;
	mat._43 = (float)-(v10 * fNearPlane);
	mat._34 = 1.0f;

	return S_OK;
}
