#include "Device.h"
#include "Globals.h"


void __cdecl GDIFlip(void) // line 46
{
	if( g_3dDevice.C3dDevice::GetDirectDraw() == NULL )
		return;

	g_3dDevice.C3dDevice::GetBackBuffer()->Unlock(NULL);
	g_3dDevice.C3dDevice::GetFrontBuffer()->Unlock(NULL);
	g_3dDevice.C3dDevice::GetDirectDraw()->FlipToGDISurface();
}


C3dDevice::C3dDevice(void) // line 57
{
	m_hWnd = NULL;
	m_dwRenderWidth = 0;
	m_dwRenderHeight = 0;
	//m_rcScreenRect
	//m_rcViewportRect
	m_pddsFrontBuffer = NULL;
	m_pddsBackBuffer = NULL;
	m_pddsRenderTarget = NULL;
	m_pddsZBuffer = NULL;
	m_pd3dDevice = NULL;
	m_pDD = NULL;
	m_pD3D = NULL;
	//m_ddDeviceDesc
	m_dwDeviceMemType = 0;
	//m_ddpfZBuffer
	//m_ddsdFrameBuffer
	m_bIsFullscreen = 0;
	m_bIsGDIObject = 0;
	//m_windowBitCount
	m_pddsRenderBackup = NULL;
	m_pfRShiftR = 0;
	m_pfRShiftL = 8;
	m_pfGShiftR = 0;
	m_pfGShiftL = 8;
	m_pfBShiftR = 0;
	m_pfBShiftL = 8;
	m_pfAShiftR = 0;
	m_pfAShiftL = 8;
	m_pfBitCount = 0;
	m_pfRBitMask = 0;
	m_pfGBitMask = 0;
	m_pfBBitMask = 0;
	m_pfABitMask = 0;
	//m_dwMinTextureWidth
	//m_dwMinTextureHeight
	//m_dwMaxTextureWidth
	//m_dwMaxTextureHeight
	//m_dwMaxTextureAspectRatio
	//m_bSupportBltStretch
	//m_bSupportTextureSurface
	//m_fMaterialDiffuseR
	//m_fMaterialDiffuseG
	//m_fMaterialDiffuseB
	//m_fMaterialAmbientR
	//m_fMaterialAmbientG
	//m_fMaterialAmbientB
}


C3dDevice::~C3dDevice(void) // line 86
{
}


hook_method<HRESULT (C3dDevice::*)(HWND hwnd, GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags)> C3dDevice::_Init(SAKEXE, "C3dDevice::Init");
HRESULT C3dDevice::Init(HWND hwnd, GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags) // line 128
{
	return (this->*_Init)(hwnd, pDriverGUID, pDeviceGUID, pMode, dwFlags);

	m_hWnd = hwnd;

	if( hwnd == NULL || pDeviceGUID == NULL || (pMode == NULL && (dwFlags & 1)) )
		return E_INVALIDARG;

	m_bIsFullscreen = dwFlags & 1;
	if( dwFlags & 1 )
	{
		SetWindowLongA(g_hMainWnd, GWL_STYLE, WS_POPUP);
		ShowWindow(g_hMainWnd, SW_MAXIMIZE);
	}

	HRESULT hr = this->C3dDevice::CreateEnvironment(pDriverGUID, pDeviceGUID, pMode, dwFlags);
	if( hr < 0 )
		return 0x82000000;

	this->C3dDevice::DestroyObjects();
	if( hr == E_FAIL )
		return 0x82000000;

	if( m_pd3dDevice == NULL )
		return hr;

	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_ZFUNC, D3DCMP_LESSEQUAL);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_TEXTUREPERSPECTIVE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_ALPHAREF, 240);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_COLORKEYENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pd3dDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATEALPHA_ADDCOLOR);
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_pd3dDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	m_pd3dDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTFN_LINEAR);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_MINFILTER, D3DTFN_LINEAR);
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_MAGFILTER, D3DTFG_LINEAR);
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_ADDRESS, D3DTADDRESS_CLAMP);
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_ADDRESS, D3DTADDRESS_BORDER);
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_BORDERCOLOR, 0xFF000000);
	return hr;
}


hook_method<HRESULT (C3dDevice::*)(void)> C3dDevice::_DestroyObjects(SAKEXE, "C3dDevice::DestroyObjects");
HRESULT C3dDevice::DestroyObjects(void) // line 89
{
	return (this->*_DestroyObjects)();

	int nDD = 0;
	int nD3D = 0;

	if( m_pd3dDevice )
	{
		nD3D = m_pd3dDevice->Release();
		m_pd3dDevice = NULL;

		if( nD3D > 0 )
		{
			char tmp[80];
			sprintf(tmp, " : D3D object is still referenced %d times", nD3D);
			MessageBoxA(g_hMainWnd, tmp, "Error", MB_OK);
		}
	}

	if( !m_bIsFullscreen && m_pddsBackBuffer )
	{
		m_pddsBackBuffer->Release();
		m_pddsBackBuffer = NULL;
	}

	if( m_pddsZBuffer )
	{
		m_pddsZBuffer->Release();
		m_pddsZBuffer = NULL;
	}

	if( m_pddsRenderTarget )
	{
		m_pddsRenderTarget->Release();
		m_pddsRenderTarget = NULL;
	}

	if( m_pddsFrontBuffer )
	{
		m_pddsFrontBuffer->Release();
		m_pddsFrontBuffer = NULL;
	}

	if( m_pD3D )
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	if( m_pddsRenderBackup )
	{
		m_pddsRenderBackup->Release();
		m_pddsRenderBackup = NULL;
	}

	if( m_pDD )
	{
		m_pDD->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL);
		nDD = m_pDD->Release();
		m_pDD = NULL;

		if( nDD > 0 )
		{
			char tmp[80];
			sprintf(tmp, " : DDraw object is still referenced %d times", nDD);
			MessageBoxA(g_hMainWnd, tmp, "Error", MB_OK);
		}
	}

	if( nDD != 0 || nD3D != 0 )
		return 0x8200000B;

	return S_OK;
}


//hook_method<int (C3dDevice::*)(void)> C3dDevice::_IsFullscreen(SAKEXE, "C3dDevice::IsFullscreen");
int C3dDevice::IsFullscreen(void) // line ???
{
	//return (this->*_IsFullScreen)();

	return m_bIsFullscreen;
}


hook_method<void (C3dDevice::*)(int bEnable)> C3dDevice::_EnableClipper(SAKEXE, "C3dDevice::EnableClipper");
void C3dDevice::EnableClipper(int bEnable) // line 199
{
	return (this->*_EnableClipper)(bEnable);

	//TODO
}


hook_method<bool (C3dDevice::*)(void)> C3dDevice::_TestScreen(SAKEXE, "C3dDevice::TestScreen");
bool C3dDevice::TestScreen(void) // line 812
{
	return (this->*_TestScreen)();

	//TODO
}


hook_method<CRenderer* (C3dDevice::*)(void)> C3dDevice::_CreateRenderer(SAKEXE, "C3dDevice::CreateRenderer");
CRenderer* C3dDevice::CreateRenderer(void) // line 724
{
	return (this->*_CreateRenderer)();

	//TODO
}


hook_method<void (C3dDevice::*)(CRenderer* rc)> C3dDevice::_DestroyRenderer(SAKEXE, "C3dDevice::DestroyRenderer");
void C3dDevice::DestroyRenderer(CRenderer* rc) // line 555
{
	return (this->*_DestroyRenderer)(rc);

	//TODO
}


hook_method<CDC* (C3dDevice::*)(unsigned long w, unsigned long h)> C3dDevice::_CreateDCBuffer(SAKEXE, "C3dDevice::CreateDCBuffer");
CDC* C3dDevice::CreateDCBuffer(unsigned long w, unsigned long h) // line 682
{
	return (this->*_CreateDCBuffer)(w, h);

	//TODO
}


hook_method<void (C3dDevice::*)(unsigned long* destPal, const PALETTEENTRY* srcPal, int palCnt)> C3dDevice::_ConvertPalette(SAKEXE, "C3dDevice::ConvertPalette");
void C3dDevice::ConvertPalette(unsigned long* destPal, const PALETTEENTRY* srcPal, int palCnt) // line 706
{
	return (this->*_ConvertPalette)(destPal, srcPal, palCnt);

	//TODO
}


hook_method<HRESULT (C3dDevice::*)(void)> C3dDevice::_RestoreSurfaces(SAKEXE, "C3dDevice::RestoreSurfaces");
HRESULT C3dDevice::RestoreSurfaces(void) // line 654
{
	return (this->*_RestoreSurfaces)();

	//TODO
}


hook_method<HRESULT (C3dDevice::*)(bool vertSync)> C3dDevice::_ShowFrame(SAKEXE, "C3dDevice::ShowFrame");
HRESULT C3dDevice::ShowFrame(bool vertSync) // line 597
{
	return (this->*_ShowFrame)(vertSync);

	if( m_pddsFrontBuffer == NULL )
		return 0x8200000E;

	if( m_pddsBackBuffer == NULL )
		return m_pddsFrontBuffer->IsLost();

	if( !vertSync )
	{
		GetClientRect(m_hWnd, &m_rcScreenRect);
		ClientToScreen(m_hWnd, (LPPOINT)&m_rcScreenRect.left);
		ClientToScreen(m_hWnd, (LPPOINT)&m_rcScreenRect.right);
		return m_pddsFrontBuffer->Blt(&m_rcScreenRect, m_pddsBackBuffer, &m_rcViewportRect, DDBLT_WAIT, NULL);
	}
	else
	if( !m_bIsFullscreen || m_bIsGDIObject )
	{
		GetClientRect(m_hWnd, &m_rcScreenRect);
		ClientToScreen(m_hWnd, (LPPOINT)&m_rcScreenRect.left);
		ClientToScreen(m_hWnd, (LPPOINT)&m_rcScreenRect.right);
		m_pDD->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, NULL);
		return m_pddsFrontBuffer->Blt(&m_rcScreenRect, m_pddsBackBuffer, &m_rcViewportRect, DDBLT_WAIT, NULL);
	}
	else
	{
		return m_pddsFrontBuffer->Flip(NULL, DDFLIP_WAIT);
	}
}


//hook_method<int (C3dDevice::*)(void)> C3dDevice::_GetWidth(SAKEXE, "C3dDevice::GetWidth");
int C3dDevice::GetWidth(void)
{
//	return (this->*_GetWidth)();

	return static_cast<int>(m_dwRenderWidth);
}


//hook_method<int (C3dDevice::*)(void)> C3dDevice::_GetHeight(SAKEXE, "C3dDevice::GetHeight");
int C3dDevice::GetHeight(void)
{
//	return (this->*_GetHeight)();

	return static_cast<int>(m_dwRenderHeight);
}


//hook_method<LPDIRECTDRAW7 (C3dDevice::*)(void)> C3dDevice::_GetDirectDraw(SAKEXE, "C3dDevice::GetDirectDraw");
LPDIRECTDRAW7 C3dDevice::GetDirectDraw(void) // line ???
{
//	return (this->*_GetDirectDraw)();

	return m_pDD;
}


//hook_method<LPDIRECT3D7 (C3dDevice::*)(void)> C3dDevice::_GetDirect3D(SAKEXE, "C3dDevice::GetDirect3D");
LPDIRECT3D7 C3dDevice::GetDirect3D(void) // line ???
{
//	return (this->*_GetDirect3D)();

	return m_pD3D;
}


//hook_method<LPDIRECT3DDEVICE7 (C3dDevice::*)(void)> C3dDevice::_GetD3DDevice(SAKEXE, "C3dDevice::GetD3DDevice");
LPDIRECT3DDEVICE7 C3dDevice::GetD3DDevice(void) // line ???
{
//	return (this->*_GetD3DDevice)();

	return m_pd3dDevice;
}


//hook_method<LPDIRECTDRAWSURFACE7 (C3dDevice::*)(void)> C3dDevice::_GetFrontBuffer(SAKEXE, "C3dDevice::GetFrontBuffer");
LPDIRECTDRAWSURFACE7 C3dDevice::GetFrontBuffer(void) // line ???
{
//	return (this->*_GetFrontBuffer)();

	return m_pddsFrontBuffer;
}


//hook_method<LPDIRECTDRAWSURFACE7 (C3dDevice::*)(void)> C3dDevice::_GetBackBuffer(SAKEXE, "C3dDevice::GetBackBuffer");
LPDIRECTDRAWSURFACE7 C3dDevice::GetBackBuffer(void) // line ???
{
//	return (this->*_GetBackBuffer)();

	return m_pddsBackBuffer;
}


//hook_method<LPDIRECTDRAWSURFACE7 (C3dDevice::*)(void)> C3dDevice::_GetRenderSurface(SAKEXE, "C3dDevice::GetRenderSurface");
LPDIRECTDRAWSURFACE7 C3dDevice::GetRenderSurface(void) // line ???
{
//	return (this->*_GetRenderSurface)();

	return m_pddsRenderTarget;
}


//hook_method<D3DDEVICEDESC7 (C3dDevice::*)(void)> C3dDevice::_GetDeviceDesc(SAKEXE, "C3dDevice::GetDeviceDesc");
D3DDEVICEDESC7 C3dDevice::GetDeviceDesc(void) // line ???
{
//	return (this->*_GetDeviceDesc)();

	return m_ddDeviceDesc;
}


//hook_method<DDSURFACEDESC2* (C3dDevice::*)(void)> C3dDevice::_GetFrameBufferDesc(SAKEXE, "C3dDevice::GetFrameBufferDesc");
DDSURFACEDESC2* C3dDevice::GetFrameBufferDesc(void) // line ???
{
//	return (this->*_GetFrameBufferDesc)();

	return &m_ddsdFrameBuffer;
}


hook_method<HRESULT (C3dDevice::*)(GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags)> C3dDevice::_CreateEnvironment(SAKEXE, "C3dDevice::CreateEnvironment");
HRESULT C3dDevice::CreateEnvironment(GUID* pDriverGUID, GUID* pDeviceGUID, DDSURFACEDESC2* pMode, DWORD dwFlags) // line 215
{
	return (this->*_CreateEnvironment)(pDriverGUID, pDeviceGUID, pMode, dwFlags);

	//TODO
}


////////////////////////////////////////


CDynamicVB::CDynamicVB(void) // line 987
: m_vertCount(0), m_vertOffset(0), m_pVB(NULL)
{
}


CDynamicVB::~CDynamicVB(void) // line 991
{
	this->CDynamicVB::Release();
}


hook_method<bool (CDynamicVB::*)(const unsigned long theFVF, unsigned long theVertexCount, unsigned long theVertexSize)> CDynamicVB::_Init(SAKEXE, "CDynamicVB::Init");
bool CDynamicVB::Init(const unsigned long theFVF, unsigned long theVertexCount, unsigned long theVertexSize) // line 1002
{
	return (this->*_Init)(theFVF, theVertexCount, theVertexSize);

	this->CDynamicVB::Release();

	m_vertSize = theVertexSize;
	m_vertCount = theVertexCount;
	m_vertOffset = 0;

	D3DVERTEXBUFFERDESC aDesc;
	aDesc.dwSize = sizeof(aDesc);
	aDesc.dwCaps = D3DVBCAPS_WRITEONLY;
	aDesc.dwFVF = theFVF;
	aDesc.dwNumVertices = theVertexCount;

	return ( g_3dDevice.C3dDevice::GetDirect3D()->CreateVertexBuffer(&aDesc, &m_pVB, 0) == D3D_OK );
}


hook_method<void (CDynamicVB::*)(void)> CDynamicVB::_Release(SAKEXE, "CDynamicVB::Release");
void CDynamicVB::Release(void) // line 996
{
	return (this->*_Release)();

	if( m_pVB != NULL )
		m_pVB->Unlock();

	if( m_pVB != NULL )
	{
		m_pVB->Release();
		m_pVB = NULL;
	}
}


hook_method<bool (CDynamicVB::*)(unsigned long vertCount, void** ppLockedData)> CDynamicVB::_Lock(SAKEXE, "CDynamicVB::Lock");
bool CDynamicVB::Lock(unsigned long vertCount, void** ppLockedData) // line 1022
{
	return (this->*_Lock)(vertCount, ppLockedData);

	if( m_pVB == NULL )
		return false;

	if( vertCount > m_vertCount )
		return false;

	if( m_pVB->Lock(DDLOCK_DISCARDCONTENTS|DDLOCK_NOSYSLOCK|DDLOCK_WRITEONLY, ppLockedData, NULL) )
		return false;

	if( vertCount + m_vertOffset <= m_vertCount )
	{
		*ppLockedData = (char *)*ppLockedData + m_vertOffset * m_vertSize;
		m_vertOffset += vertCount;
	}
	else
	{
		m_vertOffset = vertCount;
	}

	return true;
}


hook_method<void (CDynamicVB::*)(void)> CDynamicVB::_Unlock(SAKEXE, "CDynamicVB::Unlock");
void CDynamicVB::Unlock(void) // line 1045
{
	return (this->*_Unlock)();

  if( m_pVB != NULL )
      m_pVB->Unlock();
}


//hook_method<LPDIRECT3DVERTEXBUFFER7 (CDynamicVB::*)(void)> CDynamicVB::_GetInterface(SAKEXE, "CDynamicVB::GetInterface");
LPDIRECT3DVERTEXBUFFER7 CDynamicVB::GetInterface(void) // line ????
{
//	return (this->*_GetInterface)();

	return m_pVB;
}


//hook_method<unsigned long (CDynamicVB::*)(void)> CDynamicVB::_GetSize(SAKEXE, "CDynamicVB::GetSize");
unsigned long CDynamicVB::GetSize(void) // line ????
{
//	return (this->*_GetSize)();

	return m_vertSize;
}


hook_method<void (CDynamicVB::*)(LPDIRECT3DDEVICE7 device, unsigned long vertCount)> CDynamicVB::_DrawPri(SAKEXE, "CDynamicVB::DrawPri");
void CDynamicVB::DrawPri(LPDIRECT3DDEVICE7 device, unsigned long vertCount) // line 1049
{
	return (this->*_DrawPri)(device, vertCount);

	device->DrawPrimitiveVB(D3DPT_TRIANGLELIST, m_pVB, m_vertOffset - vertCount, vertCount, 0);
}
