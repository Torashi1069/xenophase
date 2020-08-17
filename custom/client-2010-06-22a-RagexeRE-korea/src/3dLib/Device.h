#pragma once
#include <ddraw.h>
class CDC;
class CRenderer;
class CSurface;


class C3dDevice
{
	/* this+  0 */ BYTE dummy_0[4];
	/* this+  4 */ DWORD m_dwRenderWidth;
	/* this+  8 */ DWORD m_dwRenderHeight;
	/* this+ 12 */ BYTE dummy_12[456];
	/* this+468 */ private: int m_bIsFullscreen;
	/* this+472 */ //TODO

	public: HRESULT C3dDevice::Init(HWND hwnd, GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags);
	public: CRenderer* C3dDevice::CreateRenderer(void);
	public: void C3dDevice::DestroyRenderer(CRenderer* rc);
	public: CDC* C3dDevice::CreateDCBuffer(unsigned long w, unsigned long h);
	public: CSurface* C3dDevice::CreateWallPaper(unsigned int w, unsigned int h);
	public: long C3dDevice::DestroyObjects(void);
	public: int C3dDevice::IsFullscreen(void);
	public: int C3dDevice::GetWidth(void);
	public: int C3dDevice::GetHeight(void);

public:
	static hook_func<HRESULT (C3dDevice::*)(HWND hwnd, GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags)> C3dDevice::_Init;
	static hook_func<CRenderer* (C3dDevice::*)(void)> C3dDevice::_CreateRenderer;
	static hook_func<void (C3dDevice::*)(CRenderer* rc)> C3dDevice::_DestroyRenderer;
	static hook_func<CDC* (C3dDevice::*)(unsigned long w, unsigned long h)> C3dDevice::_CreateDCBuffer;
	static hook_func<CSurface* (C3dDevice::*)(unsigned int w, unsigned int h)> C3dDevice::_CreateWallPaper;
	static hook_func<long (C3dDevice::*)(void)> C3dDevice::_DestroyObjects;
	static hook_func<int (C3dDevice::*)(void)> C3dDevice::_IsFullscreen;
	static hook_func<int (C3dDevice::*)(void)> C3dDevice::_GetWidth;
	static hook_func<int (C3dDevice::*)(void)> C3dDevice::_GetHeight;
};


extern C3dDevice& g_3dDevice;
