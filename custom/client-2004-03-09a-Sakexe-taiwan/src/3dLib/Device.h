#pragma once
#include <dx9sdk/Include/ddraw.h>
#include <dx9sdk/Include/d3d.h>
class CDC;
class CRenderer; // 3dLib/Renderer_h


class C3dDevice
{
	/* this+  0 */ private: HWND m_hWnd;
	/* this+  4 */ private: DWORD m_dwRenderWidth;
	/* this+  8 */ private: DWORD m_dwRenderHeight;
	/* this+ 12 */ private: RECT m_rcScreenRect;
	/* this+ 28 */ private: RECT m_rcViewportRect;
	/* this+ 44 */ private: LPDIRECTDRAWSURFACE7 m_pddsFrontBuffer;
	/* this+ 48 */ private: LPDIRECTDRAWSURFACE7 m_pddsBackBuffer;
	/* this+ 52 */ private: LPDIRECTDRAWSURFACE7 m_pddsRenderTarget;
	/* this+ 56 */ private: LPDIRECTDRAWSURFACE7 m_pddsZBuffer;
	/* this+ 60 */ private: LPDIRECT3DDEVICE7 m_pd3dDevice;
	/* this+ 64 */ private: LPDIRECTDRAW7 m_pDD;
	/* this+ 68 */ private: LPDIRECT3D7 m_pD3D;
	/* this+ 72 */ private: D3DDEVICEDESC7 m_ddDeviceDesc;
	/* this+308 */ private: DWORD m_dwDeviceMemType;
	/* this+312 */ private: DDPIXELFORMAT m_ddpfZBuffer;
	/* this+344 */ private: DDSURFACEDESC2 m_ddsdFrameBuffer;
	/* this+468 */ private: int m_bIsFullscreen;
	/* this+472 */ private: int m_bIsGDIObject;
	/* this+476 */ private: int m_windowBitCount;
	/* this+480 */ private: LPDIRECTDRAWSURFACE7 m_pddsRenderBackup;
	/* this+484 */ private: int m_pfRShiftR;
	/* this+488 */ private: int m_pfRShiftL;
	/* this+492 */ private: int m_pfGShiftR;
	/* this+496 */ private: int m_pfGShiftL;
	/* this+500 */ private: int m_pfBShiftR;
	/* this+504 */ private: int m_pfBShiftL;
	/* this+508 */ private: int m_pfAShiftR;
	/* this+512 */ private: int m_pfAShiftL;
	/* this+516 */ private: unsigned long m_pfBitCount;
	/* this+520 */ private: unsigned long m_pfRBitMask;
	/* this+524 */ private: unsigned long m_pfGBitMask;
	/* this+528 */ private: unsigned long m_pfBBitMask;
	/* this+532 */ private: unsigned long m_pfABitMask;
	/* this+536 */ private: DWORD m_dwMinTextureWidth;
	/* this+540 */ private: DWORD m_dwMinTextureHeight;
	/* this+544 */ private: DWORD m_dwMaxTextureWidth;
	/* this+548 */ private: DWORD m_dwMaxTextureHeight;
	/* this+552 */ private: DWORD m_dwMaxTextureAspectRatio;
	/* this+556 */ private: bool m_bSupportBltStretch;
	/* this+557 */ private: bool m_bSupportTextureSurface;
	/* this+560 */ private: float m_fMaterialDiffuseR;
	/* this+564 */ private: float m_fMaterialDiffuseG;
	/* this+568 */ private: float m_fMaterialDiffuseB;
	/* this+572 */ private: float m_fMaterialAmbientR;
	/* this+576 */ private: float m_fMaterialAmbientG;
	/* this+580 */ private: float m_fMaterialAmbientB;

	public: C3dDevice::C3dDevice(void);
	public: C3dDevice::~C3dDevice(void);
	public: HRESULT C3dDevice::Init(HWND hwnd, GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags);
	public: HRESULT C3dDevice::DestroyObjects(void);
	public: int C3dDevice::IsFullscreen(void);
	public: void C3dDevice::EnableClipper(int bEnable);
	public: bool C3dDevice::TestScreen(void);
	public: CRenderer* C3dDevice::CreateRenderer(void);
	public: void C3dDevice::DestroyRenderer(CRenderer* rc);
	public: CDC* C3dDevice::CreateDCBuffer(unsigned long w, unsigned long h);
	//public: CSurface* C3dDevice::CreateWallPaper(unsigned long, unsigned long);
	public: void C3dDevice::ConvertPalette(unsigned long* destPal, const PALETTEENTRY* srcPal, int palCnt);
	//public: long C3dDevice::Clear(unsigned long);
	//public: long C3dDevice::ClearZBuffer();
	public: HRESULT C3dDevice::RestoreSurfaces(void);
	public: HRESULT C3dDevice::ShowFrame(bool vertSync);
	//public: long C3dDevice::CloneFrame();
	//public: unsigned short EncodePixel(int, int, int);
	//public: int C3dDevice::DecodePixelR(unsigned short);
	//public: int C3dDevice::DecodePixelG(unsigned short);
	//public: int C3dDevice::DecodePixelB(unsigned short);
	public: int C3dDevice::GetWidth(void);
	public: int C3dDevice::GetHeight(void);
	//public: int GetWindowBitCount();
	//public: int EnableGDIObject(int);
	//public: void C3dDevice::EnableMipmap();
	//public: void C3dDevice::AdjustTextureSize(unsigned long *, unsigned long *);
	public: LPDIRECTDRAW7 C3dDevice::GetDirectDraw(void);
	public: LPDIRECT3D7 C3dDevice::GetDirect3D(void);
	public: LPDIRECT3DDEVICE7 C3dDevice::GetD3DDevice(void);
	public: LPDIRECTDRAWSURFACE7 C3dDevice::GetFrontBuffer(void);
	public: LPDIRECTDRAWSURFACE7 C3dDevice::GetBackBuffer(void);
	public: LPDIRECTDRAWSURFACE7 C3dDevice::GetRenderSurface(void);
	public: D3DDEVICEDESC7 C3dDevice::GetDeviceDesc(void);
	public: DDSURFACEDESC2* C3dDevice::GetFrameBufferDesc(void);
	//public: unsigned char GetBltStretchState();
	//public: unsigned long GetRBitMask();
	//public: unsigned long GetGBitMask();
	//public: unsigned long GetBBitMask();
	//public: int GetRShiftR();
	//public: int GetGShiftR();
	//public: int GetBShiftR();
	//public: int GetRShiftL();
	//public: int GetGShiftL();
	//public: int GetBShiftL();
	//public: void C3dDevice::BackupFrame();
	//public: void C3dDevice::RestoreFrame();
	//public: void SetMaterialDiffuse(float, float, float);
	//public: void SetMaterialAmbient(float, float, float);
	//public: void GetMaterialDiffuse(float *, float *, float *);
	//public: void GetMaterialAmbient(float *, float *, float *);
	//private: long C3dDevice::CreateZBuffer();
	//private: long C3dDevice::CreateBuffers(struct _DDSURFACEDESC2 *, unsigned long);
	//private: long C3dDevice::CreateDirectDraw(struct _GUID *, unsigned long);
	//private: long C3dDevice::CreateDirect3D(struct _GUID *, unsigned long);
	private: HRESULT C3dDevice::CreateEnvironment(GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags);
	//private: long C3dDevice::FlipToGDISurface(int);

private:
	static hook_method<HRESULT (C3dDevice::*)(HWND hwnd, GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags)> C3dDevice::_Init;
	static hook_method<HRESULT (C3dDevice::*)(void)> C3dDevice::_DestroyObjects;
	static hook_method<int (C3dDevice::*)(void)> C3dDevice::_IsFullscreen;
	static hook_method<void (C3dDevice::*)(int bEnable)> C3dDevice::_EnableClipper;
	static hook_method<bool (C3dDevice::*)(void)> C3dDevice::_TestScreen;
	static hook_method<CRenderer* (C3dDevice::*)(void)> C3dDevice::_CreateRenderer;
	static hook_method<void (C3dDevice::*)(CRenderer* rc)> C3dDevice::_DestroyRenderer;
	static hook_method<CDC* (C3dDevice::*)(unsigned long w, unsigned long h)> C3dDevice::_CreateDCBuffer;
	static hook_method<void (C3dDevice::*)(unsigned long* destPal, const PALETTEENTRY* srcPal, int palCnt)> C3dDevice::_ConvertPalette;
	static hook_method<HRESULT (C3dDevice::*)(void)> C3dDevice::_RestoreSurfaces;
	static hook_method<HRESULT (C3dDevice::*)(bool vertSync)> C3dDevice::_ShowFrame;
	static hook_method<int (C3dDevice::*)(void)> C3dDevice::_GetWidth;
	static hook_method<int (C3dDevice::*)(void)> C3dDevice::_GetHeight;
	static hook_method<LPDIRECTDRAW7 (C3dDevice::*)(void)> C3dDevice::_GetDirectDraw;
	static hook_method<LPDIRECT3D7 (C3dDevice::*)(void)> C3dDevice::_GetDirect3D;
	static hook_method<LPDIRECT3DDEVICE7 (C3dDevice::*)(void)> C3dDevice::_GetD3DDevice;
	static hook_method<LPDIRECTDRAWSURFACE7 (C3dDevice::*)(void)> C3dDevice::_GetFrontBuffer;
	static hook_method<LPDIRECTDRAWSURFACE7 (C3dDevice::*)(void)> C3dDevice::_GetBackBuffer;
	static hook_method<LPDIRECTDRAWSURFACE7 (C3dDevice::*)(void)> C3dDevice::_GetRenderSurface;
	static hook_method<D3DDEVICEDESC7 (C3dDevice::*)(void)> C3dDevice::_GetDeviceDesc;
	static hook_method<DDSURFACEDESC2* (C3dDevice::*)(void)> C3dDevice::_GetFrameBufferDesc;
	static hook_method<HRESULT (C3dDevice::*)(GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags)> C3dDevice::_CreateEnvironment;
};


class CDynamicVB
{
	/* this+ 0 */ private: unsigned long m_vertCount;
	/* this+ 4 */ private: unsigned long m_vertSize;
	/* this+ 8 */ private: unsigned long m_vertOffset;
	/* this+12 */ private: LPDIRECT3DVERTEXBUFFER7 m_pVB;

	public: CDynamicVB::CDynamicVB(void);
	public: CDynamicVB::~CDynamicVB(void);
	public: bool CDynamicVB::Init(const unsigned long theFVF, unsigned long theVertexCount, unsigned long theVertexSize);
	public: void CDynamicVB::Release(void);
	public: bool CDynamicVB::Lock(unsigned long vertCount, void** ppLockedData);
	public: void CDynamicVB::Unlock(void);
	public: LPDIRECT3DVERTEXBUFFER7 CDynamicVB::GetInterface(void);
	public: unsigned long CDynamicVB::GetSize(void);
	public: void CDynamicVB::DrawPri(LPDIRECT3DDEVICE7 device, unsigned long vertCount);

private:
	static hook_method<bool (CDynamicVB::*)(const unsigned long theFVF, unsigned long theVertexCount, unsigned long theVertexSize)> CDynamicVB::_Init;
	static hook_method<void (CDynamicVB::*)(void)> CDynamicVB::_Release;
	static hook_method<bool (CDynamicVB::*)(unsigned long vertCount, void** ppLockedData)> CDynamicVB::_Lock;
	static hook_method<void (CDynamicVB::*)(void)> CDynamicVB::_Unlock;
	static hook_method<LPDIRECT3DVERTEXBUFFER7 (CDynamicVB::*)(void)> CDynamicVB::_GetInterface;
	static hook_method<unsigned long (CDynamicVB::*)(void)> CDynamicVB::_GetSize;
	static hook_method<void (CDynamicVB::*)(LPDIRECT3DDEVICE7 device, unsigned long vertCount)> CDynamicVB::_DrawPri;
};


void __cdecl GDIFlip(void);
