#pragma once
#include <dx9sdk/Include/ddraw.h>
#include <dx9sdk/Include/d3dtypes.h>


void __cdecl D3DUtil_InitSurfaceDesc(DDSURFACEDESC2& ddsd, DWORD dwFlags, DWORD dwCaps);
void __cdecl D3DUtil_InitViewport(D3DVIEWPORT7& vp, DWORD dwWidth, DWORD dwHeight);
HRESULT __cdecl D3DUtil_SetProjectionMatrix(D3DMATRIX& mat, float fFOV, float fAspect, float fNearPlane, float fFarPlane);
