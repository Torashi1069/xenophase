#include "3dLib/Device.h"


hook_func<HRESULT (C3dDevice::*)(HWND hwnd, GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags)> C3dDevice::_Init("C3dDevice::Init");
HRESULT C3dDevice::Init(HWND hwnd, GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags)
{
	return (this->*_Init)(hwnd, pDriverGUID, pDeviceGUID, pMode, dwFlags);

	//TODO
}


hook_func<CRenderer* (C3dDevice::*)(void)> C3dDevice::_CreateRenderer("C3dDevice::CreateRenderer");
CRenderer* C3dDevice::CreateRenderer(void)
{
	return (this->*_CreateRenderer)();

	//TODO
}


hook_func<void (C3dDevice::*)(CRenderer* rc)> C3dDevice::_DestroyRenderer("C3dDevice::DestroyRenderer");
void C3dDevice::DestroyRenderer(CRenderer* rc)
{
	return (this->*_DestroyRenderer)(rc);

	//TODO
}


hook_func<CDC* (C3dDevice::*)(unsigned long w, unsigned long h)> C3dDevice::_CreateDCBuffer("C3dDevice::CreateDCBuffer");
CDC* C3dDevice::CreateDCBuffer(unsigned long w, unsigned long h)
{
	return (this->*_CreateDCBuffer)(w, h);

	//TODO
}


hook_func<CSurface* (C3dDevice::*)(unsigned int w, unsigned int h)> C3dDevice::_CreateWallPaper("C3dDevice::CreateWallPaper");
CSurface* C3dDevice::CreateWallPaper(unsigned int w, unsigned int h)
{
	return (this->*_CreateWallPaper)(w, h);

	//TODO
}


hook_func<long (C3dDevice::*)(void)> C3dDevice::_DestroyObjects("C3dDevice::DestroyObjects");
long C3dDevice::DestroyObjects(void)
{
	return (this->*_DestroyObjects)();

	//TODO
}


//hook_func<int (C3dDevice::*)(void)> C3dDevice::_IsFullscreen("C3dDevice::IsFullscreen");
int C3dDevice::IsFullscreen(void)
{
	//return (this->*_IsFullScreen)();

	return m_bIsFullscreen;
}


//hook_func<int (C3dDevice::*)(void)> C3dDevice::_GetWidth("C3dDevice::GetWidth");
int C3dDevice::GetWidth(void)
{
//	return (this->*_GetWidth)();

	return static_cast<int>(m_dwRenderWidth);
}


//hook_func<int (C3dDevice::*)(void)> C3dDevice::_GetHeight("C3dDevice::GetHeight");
int C3dDevice::GetHeight(void)
{
//	return (this->*_GetHeight)();

	return static_cast<int>(m_dwRenderHeight);
}


C3dDevice& g_3dDevice = VTOR<C3dDevice>(SymDB::Find("g_3dDevice"));
