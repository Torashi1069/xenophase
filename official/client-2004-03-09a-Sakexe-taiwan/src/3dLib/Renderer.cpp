#include "Globals.h"
#include "Renderer.h"


hook_val<CTexture> CTexMgr::s_dummy_texture(SAKEXE, "CTexMgr::s_dummy_texture"); // = ?


////////////////////////////////////////


hook_method<void (RPRaw::*)(LPDIRECT3DDEVICE7 device)> RPRaw::_DrawPri(SAKEXE, "RPRaw::DrawPri");
void RPRaw::DrawPri(LPDIRECT3DDEVICE7 device) // line 37-47
{
	return (this->*_DrawPri)(device);

	if( this->numVerts == 0 )
		return;

	D3DMATRIX d3dWorld;
	d3dWorld._11 = this->world.v11;
	d3dWorld._12 = this->world.v12;
	d3dWorld._13 = this->world.v13;
	d3dWorld._21 = this->world.v21;
	d3dWorld._22 = this->world.v22;
	d3dWorld._23 = this->world.v23;
	d3dWorld._31 = this->world.v31;
	d3dWorld._32 = this->world.v32;
	d3dWorld._33 = this->world.v33;
	d3dWorld._41 = this->world.v41;
	d3dWorld._42 = this->world.v42;
	d3dWorld._43 = this->world.v43;
	d3dWorld._14 = 0.0;
	d3dWorld._24 = 0.0;
	d3dWorld._34 = 0.0;
	d3dWorld._44 = 1.0;

	device->SetTransform(D3DTRANSFORMSTATE_WORLD, &d3dWorld);
	device->DrawPrimitiveVB(D3DPT_TRIANGLELIST, this->vb->CDynamicVB::GetInterface(), this->vertStart, this->numVerts, 0);
}


hook_method<void (RPRaw::*)(LPDIRECT3DDEVICE7 device)> RPRaw::_DrawPriIndexed(SAKEXE, "RPRaw::DrawPriIndexed");
void RPRaw::DrawPriIndexed(LPDIRECT3DDEVICE7 device) // line 50-60
{
	return (this->*_DrawPriIndexed)(device);

	if( this->numIndices == 0 )
		return;

	D3DMATRIX d3dWorld;
	d3dWorld._11 = this->world.v11;
	d3dWorld._12 = this->world.v12;
	d3dWorld._13 = this->world.v13;
	d3dWorld._21 = this->world.v21;
	d3dWorld._22 = this->world.v22;
	d3dWorld._23 = this->world.v23;
	d3dWorld._31 = this->world.v31;
	d3dWorld._32 = this->world.v32;
	d3dWorld._33 = this->world.v33;
	d3dWorld._41 = this->world.v41;
	d3dWorld._42 = this->world.v42;
	d3dWorld._43 = this->world.v43;
	d3dWorld._14 = 0.0;
	d3dWorld._24 = 0.0;
	d3dWorld._34 = 0.0;
	d3dWorld._44 = 1.0;

	device->SetTransform(D3DTRANSFORMSTATE_WORLD, &d3dWorld);
	device->DrawIndexedPrimitiveVB(D3DPT_TRIANGLELIST, this->vb->CDynamicVB::GetInterface(), 0, this->numVerts, this->indices, this->numIndices, 0);
}


////////////////////////////////////////


RPFace::RPFace(tlvertex3d* vert, int numVert) // line 69
{
	this->verts = vert;
	this->numVerts = numVert;
	this->numIndices = 0;
	this->primType = D3DPT_TRIANGLELIST;
}


hook_method<void (RPFace::*)(int vertId, const tlvertex3d& src)> RPFace::_SetGeomInfo(SAKEXE, "?SetGeomInfo@RPFace@@QAEXHABUtlvertex3d@@@Z");
void RPFace::SetGeomInfo(int vertId, const tlvertex3d& src) // line 74
{
	return (this->*_SetGeomInfo)(vertId, src);

	this->verts[vertId].x = src.x;
	this->verts[vertId].y = src.y;
	this->verts[vertId].z = src.z;
	this->verts[vertId].oow = src.oow;
}


hook_method<void (RPFace::*)(int vertId, const vector4d& src)> RPFace::_SetGeomInfo2(SAKEXE, "?SetGeomInfo@RPFace@@QAEXHABUvector4d@@@Z");
void RPFace::SetGeomInfo(int vertId, const vector4d& src) // line 83
{
	return (this->*_SetGeomInfo2)(vertId, src);

	this->verts[vertId].x = src.x;
	this->verts[vertId].y = src.y;
	this->verts[vertId].z = src.z;
	this->verts[vertId].oow = src.oow;
}


hook_method<void (RPFace::*)(void)> RPFace::_InitSpecular(SAKEXE, "RPFace::InitSpecular");
void RPFace::InitSpecular(void) // line 92
{
	return (this->*_InitSpecular)();

	//TODO
}


hook_method<void (RPFace::*)(LPDIRECT3DDEVICE7 device)> RPFace::_DrawPri(SAKEXE, "RPFace::DrawPri");
void RPFace::DrawPri(LPDIRECT3DDEVICE7 device) // line 101
{
	return (this->*_DrawPri)(device);

	if( this->numVerts != 0 )
	{
		if( this->numIndices == 0 )
			device->DrawPrimitive(this->primType, 452, this->verts, this->numVerts, 0);
		else
			device->DrawIndexedPrimitive(this->primType, 452, this->verts, this->numVerts, this->indices, this->numIndices, 0);
	}
}


////////////////////////////////////////


RPQuadFace::RPQuadFace(void) // line 116
: RPFace(m_verts, countof(m_verts))
{
	for( int i = 0; i < countof(m_verts); ++i )
		m_verts[i].specular = 0xFF000000;

	this->primType = D3DPT_TRIANGLESTRIP;
}


RPQuadFace::RPQuadFace(const RPQuadFace& rp) // line 122
: RPFace(m_verts, countof(m_verts))
{
	for( int i = 0; i < countof(m_verts); ++i )
		m_verts[i].specular = 0xFF000000;

	this->primType = D3DPT_TRIANGLESTRIP;
	memcpy(m_verts, rp.m_verts, sizeof(m_verts));
}


const RPQuadFace& RPQuadFace::operator=(const RPQuadFace& rp) // line 129
{
	memcpy(m_verts, rp.m_verts, sizeof(m_verts));
	return *this;
}


////////////////////////////////////////


hook_method<void (RPLmFace::*)(void)> RPLmFace::_InitSpecular(SAKEXE, "RPLmFace::InitSpecular");
void RPLmFace::InitSpecular(void) // line 138-143
{
	return (this->*_InitSpecular)();

	//TODO
}


hook_method<void (RPLmFace::*)(LPDIRECT3DDEVICE7 device)> RPLmFace::_DrawPri(SAKEXE, "RPLmFace::DrawPri");
void RPLmFace::DrawPri(LPDIRECT3DDEVICE7 device) // line 146-155
{
	return (this->*_DrawPri)(device);

	//TODO
}


////////////////////////////////////////


RPLmQuadFace::RPLmQuadFace(void) // line 161-167
{
	this->lmverts = m_lmverts;
	this->numVerts = countof(m_lmverts);
	this->indices = 0;
	this->numIndices = 0;
	this->primType = D3DPT_TRIANGLESTRIP;
}


RPLmQuadFace::RPLmQuadFace(const RPLmQuadFace& rp) // line 170-178
{
	this->lmverts = m_lmverts;
	this->numVerts = countof(m_lmverts);
	this->indices = 0;
	this->numIndices = 0;
	this->primType = D3DPT_TRIANGLESTRIP;
	
    memcpy(m_lmverts, rp.m_lmverts, sizeof(m_lmverts));
}


const RPLmQuadFace& RPLmQuadFace::operator=(const RPLmQuadFace& rp) // line 181-185
{
    memcpy(m_lmverts, rp.m_lmverts, sizeof(m_lmverts));
	return *this;
}


////////////////////////////////////////


RPMesh::RPMesh() : RPFace(0, 0) // line 192-193
{
}


RPMesh::~RPMesh() // line 196-201
{
	if( this->verts != NULL )
	{
		delete this->verts;
		this->verts = NULL;
	}
}


void RPMesh::AllocVerts(int numVerts) // line 204-206
{
	this->verts = new tlvertex3d[3 * numVerts];
}


////////////////////////////////////////


hook_method<void (CRenderer::*)(CTexture* tex)> CRenderer::_SetTexture(SAKEXE, "CRenderer::SetTexture");
void CRenderer::SetTexture(CTexture* tex) // line 1983-1992
{
	return (this->*_SetTexture)(tex);

	//TODO
}


hook_method<void (CRenderer::*)(CTexture* tex)> CRenderer::_SetLmapTexture(SAKEXE, "CRenderer::SetLmapTexture");
void CRenderer::SetLmapTexture(CTexture* tex) // line 1995-2004
{
	return (this->*_SetLmapTexture)(tex);

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_ReleaseCacheSurfaces(SAKEXE, "CRenderer::ReleaseCacheSurfaces");
void CRenderer::ReleaseCacheSurfaces(void) // line 531
{
	return (this->*_ReleaseCacheSurfaces)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_UnloadRarelyUsedCaches(SAKEXE, "CRenderer::UnloadRarelyUsedCaches");
void CRenderer::UnloadRarelyUsedCaches(void) // line 576
{
	return (this->*_UnloadRarelyUsedCaches)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_DestroyAllRPList(SAKEXE, "CRenderer::DestroyAllRPList");
void CRenderer::DestroyAllRPList(void) // line 747-773
{
	return (this->*_DestroyAllRPList)();

	//TODO
}


hook_method<void (CRenderer::*)(vector3d& from, vector3d& at, vector3d& up)> CRenderer::_SetLookAt(SAKEXE, "CRenderer::SetLookAt");
void CRenderer::SetLookAt(vector3d& from, vector3d& at, vector3d& up) // line 777
{
	return (this->*_SetLookAt)(from, at, up);

	;
}


hook_method<void (CRenderer::*)(vector3d& lightDir, vector3d& diffuseCol, vector3d& ambientCol)> CRenderer::_SetLight(SAKEXE, "CRenderer::SetLight");
void CRenderer::SetLight(vector3d& lightDir, vector3d& diffuseCol, vector3d& ambientCol) // line 780
{
	return (this->*_SetLight)(lightDir, diffuseCol, ambientCol);

	//TODO
}


hook_method<void (CRenderer::*)(int clearScreen)> CRenderer::_Clear(SAKEXE, "CRenderer::Clear");
void CRenderer::Clear(int clearScreen) // line 477
{
	return (this->*_Clear)(clearScreen);

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_ClearBackground(SAKEXE, "CRenderer::ClearBackground");
void CRenderer::ClearBackground(void) // line 486
{
	return (this->*_ClearBackground)();

	//TODO
}


//hook_method<void (CRenderer::*)(unsigned long color)> CRenderer::_SetBackgroundColor(SAKEXE, "CRenderer::SetBackgroundColor");
void CRenderer::SetBackgroundColor(unsigned long color) // line ???
{
//	return (this->*_SetBackgroundColor)(color);

	m_nClearColor = color;
}


hook_method<bool (CRenderer::*)(void)> CRenderer::_DrawScene(SAKEXE, "CRenderer::DrawScene");
bool CRenderer::DrawScene(void) // line 490-510
{
	return (this->*_DrawScene)();

	m_dwScreenWidth = g_3dDevice.C3dDevice::GetWidth(); //inlined
	m_dwScreenHeight = g_3dDevice.C3dDevice::GetHeight(); //inlined

	if( FAILED(m_device->BeginScene()) )
	{
		this->CRenderer::DestroyAllRPList();
		return false;
	}

	this->CRenderer::FlushRenderList();
	this->CRenderer::DestroyAllRPList();
	m_device->EndScene();
	return true;
}


hook_method<int (CRenderer::*)(void)> CRenderer::_Lock(SAKEXE, "CRenderer::Lock");
int CRenderer::Lock(void) // line 513
{
	return (this->*_Lock)();

	DDSURFACEDESC2 desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.dwSize = sizeof(desc);
	
	if( FAILED(g_3dDevice.C3dDevice::GetRenderSurface()->Lock(NULL, &desc, DDLOCK_WAIT, NULL)) )
		return 0;

	m_lpSurfacePtr = desc.lpSurface;
	m_bRGBBitCount = desc.ddpfPixelFormat.dwRGBBitCount;
	m_lPitch = desc.lPitch;
	return 1;
}


hook_method<void (CRenderer::*)(void)> CRenderer::_Unlock(SAKEXE, "CRenderer::Unlock");
void CRenderer::Unlock(void) // line 527
{
	return (this->*_Unlock)();

	g_3dDevice.C3dDevice::GetRenderSurface()->Unlock(NULL);
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushRenderList(SAKEXE, "CRenderer::FlushRenderList");
void CRenderer::FlushRenderList(void) // line 803-928
{
	return (this->*_FlushRenderList)();

	m_device->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTFP_LINEAR);
	this->CRenderer::DoFog();
	m_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	m_device->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_device->SetRenderState(D3DRENDERSTATE_FOGENABLE, m_isFoggy);
	m_device->SetRenderState(D3DRENDERSTATE_ALPHAREF, 207);
	m_device->SetRenderState(D3DRENDERSTATE_ALPHATESTENABLE, TRUE);
	m_device->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	m_device->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_TRUE);
	m_device->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE);

	mystd::sort(m_rpFaceList.begin(), m_rpFaceList.end(), CRenderer::RPFaceTexPrtLess());
	for( mystd::vector<RPFace*>::iterator it = m_rpFaceList.begin(); it != m_rpFaceList.end(); ++it )
	{
		RPFace* rp = *it;

		if( m_oldTexture != rp->tex )
		{
			if( rp->tex != NULL )
				m_device->SetTexture(0, rp->tex->CSurface::GetDDSurface());
			else
				m_device->SetTexture(0, NULL);

			m_oldTexture = rp->tex;
		}

		rp->RPFace::DrawPri(m_device);
	}

	this->CRenderer::SetLmapTexture(NULL);

	mystd::sort(m_rpRawList.begin(), m_rpRawList.end(), CRenderer::RPRawTexPrtLess());
	for( mystd::vector<RPRaw*>::iterator it = m_rpRawList.begin(); it != m_rpRawList.end(); ++it )
	{
		RPRaw* rp = *it;

		if( m_oldTexture != rp->tex )
		{
			if( rp->tex != NULL )
				m_device->SetTexture(0, rp->tex->CSurface::GetDDSurface());
			else
				m_device->SetTexture(0, NULL);

			m_oldTexture = rp->tex;
		}

		rp->RPRaw::DrawPri(m_device);
	}

	m_device->SetRenderState(D3DRENDERSTATE_AMBIENT, -1);
	m_device->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_CW);

	if( !g_isLightMap )
	{
		mystd::sort(m_rpLMGroundList.begin(), m_rpLMGroundList.end(), CRenderer::RPFaceTexPrtLess());
		for( mystd::vector<RPFace*>::iterator it = m_rpLMGroundList.begin(); it != m_rpLMGroundList.end(); ++it )
		{
			RPFace* rp = *it;

			this->CRenderer::SetTexture(rp->tex);
			rp->RPFace::DrawPri(m_device);
		}
	}
	else
	if( !g_isSupportLMTex )
	{
		mystd::sort(m_rpLMGroundList.begin(), m_rpLMGroundList.end(), CRenderer::RPFaceTexPrtLess());
		for( mystd::vector<RPFace*>::iterator it = m_rpLMGroundList.begin(); it != m_rpLMGroundList.end(); ++it )
		{
			RPFace* rp = *it;

			if( m_oldTexture != rp->tex )
			{
				if( rp->tex != NULL )
					m_device->SetTexture(0, rp->tex->CSurface::GetDDSurface());
				else
					m_device->SetTexture(0, NULL);

				m_oldTexture = rp->tex;
			}

			rp->RPFace::DrawPri(m_device);
		}

		m_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTSS_COLORARG1);
		m_device->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
		m_device->SetRenderState(D3DRENDERSTATE_ALPHAREF, 1);
		m_device->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
		m_device->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_SRCALPHA);

		mystd::sort(m_rpLMLightList.begin(), m_rpLMLightList.end(), CRenderer::RPFaceTexPrtLess());
		for( mystd::vector<RPFace*>::iterator it = m_rpLMLightList.begin(); it != m_rpLMLightList.end(); ++it )
		{
			RPFace* rp = *it;

			this->CRenderer::SetTexture(rp->tex);
			rp->RPFace::DrawPri(m_device);
		}

		m_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		m_device->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
		m_device->SetRenderState(D3DRENDERSTATE_ALPHAREF, 207);
	}
	else
	{
		m_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATEALPHA_ADDCOLOR);

		mystd::sort(m_rpLmList.begin(), m_rpLmList.end(), CRenderer::RPLmFaceTexPrtLess());
		for( mystd::vector<RPLmFace*>::iterator it = m_rpLmList.begin(); it != m_rpLmList.end(); ++it )
		{
			RPLmFace* rp = *it;

			if( m_oldTexture != rp->tex )
			{
				if( rp->tex )
					m_device->SetTexture(0, rp->tex->CSurface::GetDDSurface());
				else
					m_device->SetTexture(0, NULL);

				m_oldTexture = rp->tex;
			}

			this->CRenderer::SetLmapTexture(rp->tex2);
			rp->RPLmFace::DrawPri(m_device);
		}

		m_device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	}

	m_device->SetRenderState(D3DRENDERSTATE_AMBIENT, 0);
	m_device->SetRenderState(D3DRENDERSTATE_CULLMODE, D3DCULL_NONE);
	m_device->SetRenderState(D3DRENDERSTATE_ALPHAREF, 1);
	m_device->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, TRUE);
	m_device->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	m_device->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

	mystd::sort(m_rpAlphaDepthList.begin(), m_rpAlphaDepthList.end());
	for( mystd::vector<mystd::pair<float,RPFace*>>::iterator it = m_rpAlphaDepthList.begin(); it != m_rpAlphaDepthList.end(); ++it )
	{
		RPFace* rp = it->second;

		this->CRenderer::SetTexture(rp->tex);
		rp->RPFace::DrawPri(m_device);
	}

	m_device->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
	m_device->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

	mystd::sort(m_rpEmissiveDepthList.begin(), m_rpEmissiveDepthList.end());
	for( mystd::vector<mystd::pair<float,RPFace*>>::iterator it = m_rpEmissiveDepthList.begin(); it != m_rpEmissiveDepthList.end(); ++it )
	{
		RPFace* rp = it->second;

		this->CRenderer::SetTexture(rp->tex);
		rp->RPFace::DrawPri(m_device);
	}

	m_device->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE);
	m_device->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	m_device->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);

	mystd::sort(m_rpAlphaList.begin(), m_rpAlphaList.end());
	for( mystd::vector<mystd::pair<float,RPFace*>>::iterator it = m_rpAlphaList.begin(); it != m_rpAlphaList.end(); ++it )
	{
		RPFace* rp = it->second;

		this->CRenderer::SetTexture(rp->tex);
		rp->RPFace::DrawPri(m_device);
	}

	mystd::sort(m_rpRawAlphaList.begin(), m_rpRawAlphaList.end(), CRenderer::RPRawTexPrtLess());
	for( mystd::vector<RPRaw*>::iterator it = m_rpRawAlphaList.begin(); it != m_rpRawAlphaList.end(); ++it )
	{
		RPRaw* rp = *it;

		this->CRenderer::SetTexture(rp->tex);
		rp->RPRaw::DrawPri(m_device);
	}

	m_device->SetRenderState(D3DRENDERSTATE_FOGENABLE, FALSE);
	m_device->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
	m_device->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);

	mystd::sort(m_rpEmissiveList.begin(), m_rpEmissiveList.end());
	for( mystd::vector<mystd::pair<float,RPFace*>>::iterator it = m_rpEmissiveList.begin(); it != m_rpEmissiveList.end(); ++it )
	{
		RPFace* rp = it->second;

		this->CRenderer::SetTexture(rp->tex);
		rp->RPFace::DrawPri(m_device);
	}

	for( mystd::vector<RPFace*>::iterator it = m_rpAlphaOPList.begin(); it != m_rpAlphaOPList.end(); ++it )
	{
		RPFace* rp = *it;

		this->CRenderer::SetTexture(rp->tex);
		this->CRenderer::SetMultiTextureMode(rp->mtPreset);
		m_device->SetRenderState(D3DRENDERSTATE_SRCBLEND, rp->srcAlphaMode);
		m_device->SetRenderState(D3DRENDERSTATE_DESTBLEND, rp->destAlphaMode);
		rp->RPFace::DrawPri(m_device);
	}

	m_device->SetRenderState(D3DRENDERSTATE_ZENABLE, D3DZB_FALSE);
	m_device->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	m_device->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	this->CRenderer::FlushAlphaNoDepthList();
	m_device->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE);
	m_device->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE);
	this->CRenderer::FlushEmissiveNoDepthList();
	m_device->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	m_device->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_device->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTFP_NONE);
}


hook_method<CTexture* (CRenderer::*)(SprImg& img, unsigned long* pal, CacheInfo* info)> CRenderer::_AddSpriteIndex(SERVER, "CRenderer::AddSpriteIndex");
CTexture* CRenderer::AddSpriteIndex(SprImg& img, unsigned long* pal, CacheInfo* info) // line 605
{
	return (this->*_AddSpriteIndex)(img, pal, info);

	//TODO
}


hook_method<CTexture* (CRenderer::*)(SprImg& img, unsigned long palID, CacheInfo* info)> CRenderer::_GetSpriteIndex(SERVER, "CRenderer::GetSpriteIndex");
CTexture* CRenderer::GetSpriteIndex(SprImg& img, unsigned long palID, CacheInfo* info) // line 695
{
	return (this->*_GetSpriteIndex)(img, palID, info);

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_DoFog(SAKEXE, "CRenderer::DoFog");
void CRenderer::DoFog(void) // line 1206-1283
{
	return (this->*_DoFog)();

	//TODO
}


hook_method<void (CRenderer::*)(bool vertSync)> CRenderer::_Flip(SAKEXE, "CRenderer::Flip");
void CRenderer::Flip(bool vertSync) // line 1113
{
	return (this->*_Flip)(vertSync);

	++m_curFrame;
	++m_fpsFrameCount;

	if( this->CRenderer::Lock() ) //inlined
		this->CRenderer::Unlock(); //inlined

	g_3dDevice.C3dDevice::ShowFrame(vertSync);
}


hook_method<void (CRenderer::*)(void)> CRenderer::_BackupFrame(SAKEXE, "CRenderer::BackupFrame");
void CRenderer::BackupFrame(void) // line 1972
{
	return (this->*_BackupFrame)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_RestoreFrame(SAKEXE, "CRenderer::RestoreFrame");
void CRenderer::RestoreFrame(void) // line 1977
{
	return (this->*_RestoreFrame)();

	//TODO
}


hook_method<int (CRenderer::*)(const char* fName, CBitmapRes* bitmap)> CRenderer::_SaveBmp(SAKEXE, "CRenderer::SaveBmp");
int CRenderer::SaveBmp(const char* fName, CBitmapRes* bitmap) // line 1589
{
	return (this->*_SaveBmp)(fName, bitmap);

	//TODO
}


hook_method<int (CRenderer::*)(const char* fName, CBitmapRes* bitmap)> CRenderer::_SaveJPG(SAKEXE, "CRenderer::SaveJPG");
int CRenderer::SaveJPG(const char* fName, CBitmapRes* bitmap) // line 1694
{
	return (this->*_SaveJPG)(fName, bitmap);

	//TODO
}


hook_method<void (CRenderer::*)(const vector3d& src, const matrix& vtm, float* x, float* y, float* oow)> CRenderer::_ProjectVertex(SAKEXE, "?ProjectVertex@CRenderer@@QAEXABUvector3d@@ABUmatrix@@PAM22@Z");
void CRenderer::ProjectVertex(const vector3d& src, const matrix& vtm, float* x, float* y, float* oow) // line 2007
{
	return (this->*_ProjectVertex)(src, vtm, x, y, oow);

	//TODO
}


hook_method<void (CRenderer::*)(const vector3d& src, const matrix& vtm, tlvertex3d* vert)> CRenderer::_ProjectVertex2(SAKEXE, "?ProjectVertex@CRenderer@@QAEXABUvector3d@@ABUmatrix@@PAUtlvertex3d@@@Z");
void CRenderer::ProjectVertex(const vector3d& src, const matrix& vtm, tlvertex3d* vert) // line 2014
{
	return (this->*_ProjectVertex2)(src, vtm, vert);

	//TODO
}


hook_method<float (CRenderer::*)(float oow)> CRenderer::_GetPixelRatio(SERVER, "CRenderer::GetPixelRatio");
float CRenderer::GetPixelRatio(float oow) // line 2023
{
	return (this->*_GetPixelRatio)(oow);

	return oow * m_hpc * (1/7.0f);
}


hook_method<float (CRenderer::*)(void)> CRenderer::_GetScreenXFactor(SERVER, "CRenderer::GetScreenXFactor");
float CRenderer::GetScreenXFactor(void) // line 2028
{
	return (this->*_GetScreenXFactor)();

	return m_screenXFactor;
}


hook_method<void (CRenderer::*)(int sx, int sy, const vector3d& from, const matrix& invViewMatrix, ray3d* ray)> CRenderer::_BuildRay(SAKEXE, "CRenderer::BuildRay");
void CRenderer::BuildRay(int sx, int sy, const vector3d& from, const matrix& invViewMatrix, ray3d* ray) // line 1574-1586
{
	return (this->*_BuildRay)(sx, sy, from, invViewMatrix, ray);

	matrix ivtm;
	memcpy(&ivtm, &invViewMatrix, sizeof(ivtm));

	double ratex = (double)sx / (double)m_halfWidth;
	double ratey = (double)sy / (double)m_halfHeight;
	ray->org.x = from.x;
	ray->org.y = from.y;
	ray->org.z = from.z;

	vector3d dirView;
	dirView.x = float((double)m_halfWidth / m_hpc * (ratex - 1.0));
	double vy = -1.0 / m_vpc * (double)m_halfHeight * (1.0 - ratey);
	ray->dir.x = float(ivtm.v11 * dirView.x + ivtm.v21 * vy + ivtm.v31);
	ray->dir.y = float(ivtm.v12 * dirView.x + ivtm.v22 * vy + ivtm.v32);
	ray->dir.z = float(ivtm.v13 * dirView.x + ivtm.v23 * vy + ivtm.v33);
	ray->dir.vector3d::Normalize(); // inlined
}


hook_method<RPQuadFace& (CRenderer::*)(void)> CRenderer::_BorrowQuadRP(SAKEXE, "CRenderer::BorrowQuadRP");
RPQuadFace& CRenderer::BorrowQuadRP(void) // line 1903
{
	return (this->*_BorrowQuadRP)();

	if( m_rpQuadFaceListIter == m_rpQuadFaceList.end() )
	{
		m_rpQuadFaceListIter = m_rpQuadFaceList.insert(m_rpQuadFaceListIter);
		return *m_rpQuadFaceListIter;
	}
	else
	{
		return *m_rpQuadFaceListIter++;
	}
}


hook_method<void (CRenderer::*)(RPFace* rp, int renderFlag)> CRenderer::_AddRP(SAKEXE, "?AddRP@CRenderer@@QAEXPAURPFace@@H@Z");
void CRenderer::AddRP(RPFace* rp, int renderFlag) // line 1793
{
	return (this->*_AddRP)(rp, renderFlag);

	//TODO
}


hook_method<void (CRenderer::*)(RPTriFace* rp, int renderFlag)> CRenderer::_AddRP2(SAKEXE, "?AddRP@CRenderer@@QAEXPAURPTriFace@@H@Z");
void CRenderer::AddRP(RPTriFace* rp, int renderFlag) // line 1836
{
	return (this->*_AddRP2)(rp, renderFlag);

	//TODO
}


hook_method<void (CRenderer::*)(int nMode)> CRenderer::_SetMultiTextureMode(SAKEXE, "CRenderer::SetMultiTextureMode");
void CRenderer::SetMultiTextureMode(int nMode)
{
	return (this->*_SetMultiTextureMode)(nMode);

	//TODO
}


hook_method<int (CRenderer::*)(int x, int y, const char* text, unsigned long colorRef)> CRenderer::_TextOutScreen(SAKEXE, "CRenderer::TextOutScreen");
int CRenderer::TextOutScreen(int x, int y, const char* text, unsigned long colorRef) // line 1164
{
	return (this->*_TextOutScreen)(x, y, text, colorRef);

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushFaceList(SAKEXE, "CRenderer::FlushFaceList");
void CRenderer::FlushFaceList(void) // line 931-942
{
	return (this->*_FlushFaceList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushLMGroundList(SAKEXE, "CRenderer::FlushLMGroundList");
void CRenderer::FlushLMGroundList(void) // line 982-992
{
	return (this->*_FlushLMGroundList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushLMLightList(SAKEXE, "CRenderer::FlushLMLightList");
void CRenderer::FlushLMLightList(void) // line 995-1004
{
	return (this->*_FlushLMLightList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushAlphaDepthList(SAKEXE, "CRenderer::FlushAlphaDepthList");
void CRenderer::FlushAlphaDepthList(void) // line 1020-1029
{
	return (this->*_FlushAlphaDepthList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushAlphaList(SAKEXE, "CRenderer::FlushAlphaList");
void CRenderer::FlushAlphaList(void) // line 1044-1053
{
	return (this->*_FlushAlphaList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushAlphaNoDepthList(SAKEXE, "CRenderer::FlushAlphaNoDepthList");
void CRenderer::FlushAlphaNoDepthList(void) // line 1008-1017
{
	return (this->*_FlushAlphaNoDepthList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushEmissiveDepthList(SAKEXE, "CRenderer::FlushEmissiveDepthList");
void CRenderer::FlushEmissiveDepthList(void) // line 1032-1041
{
	return (this->*_FlushEmissiveDepthList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushEmissiveList(SAKEXE, "CRenderer::FlushEmissiveList");
void CRenderer::FlushEmissiveList(void) // line 1056-1065
{
	return (this->*_FlushEmissiveList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushEmissiveNoDepthList(SAKEXE, "CRenderer::FlushEmissiveNoDepthList");
void CRenderer::FlushEmissiveNoDepthList(void) // line 1068-1077
{
	return (this->*_FlushEmissiveNoDepthList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushRawList(SAKEXE, "CRenderer::FlushRawList");
void CRenderer::FlushRawList(void) // line 945-955
{
	return (this->*_FlushRawList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushAlphaRawList(SAKEXE, "CRenderer::FlushAlphaRawList");
void CRenderer::FlushAlphaRawList(void) // line 958-967
{
	return (this->*_FlushAlphaRawList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushEmissiveRawList(SAKEXE, "CRenderer::FlushEmissiveRawList");
void CRenderer::FlushEmissiveRawList(void) // line 970-979
{
	return (this->*_FlushEmissiveRawList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushEffectList(SAKEXE, "CRenderer::FlushEffectList");
void CRenderer::FlushEffectList(void) // line 1080-1090
{
	return (this->*_FlushEffectList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushBumpList(SAKEXE, "CRenderer::FlushBumpList");
void CRenderer::FlushBumpList(void) // line 1095-1097
{
	return (this->*_FlushBumpList)();

	//TODO
}


hook_method<void (CRenderer::*)(void)> CRenderer::_FlushLmList(SAKEXE, "CRenderer::FlushLmList");
void CRenderer::FlushLmList(void) // line 1100-1110
{
	return (this->*_FlushLmList)();

	//TODO
}


////////////////////////////////////////


hook_method<CTexture* (CTexMgr::*)(unsigned long w, unsigned long h, PixelFormat pf, LPDIRECTDRAWSURFACE7 surface)> CTexMgr::_CreateTexture(SAKEXE, "?CreateTexture@CTexMgr@@QAEPAVCTexture@@KKW4PixelFormat@@PAUIDirectDrawSurface7@@@Z");
CTexture* CTexMgr::CreateTexture(unsigned long w, unsigned long h, PixelFormat pf, LPDIRECTDRAWSURFACE7 surface)
{
	return (this->*_CreateTexture)(w, h, pf, surface);

	//TODO
}


hook_method<CTexture* (CTexMgr::*)(int w, int h, unsigned long* imgData, PixelFormat pf, bool blackkey)> CTexMgr::_CreateTexture2(SAKEXE, "?CreateTexture@CTexMgr@@QAEPAVCTexture@@HHPAKW4PixelFormat@@_N@Z");
CTexture* CTexMgr::CreateTexture(int w, int h, unsigned long* imgData, PixelFormat pf, bool blackkey)
{
	return (this->*_CreateTexture2)(w, h, imgData, pf, blackkey);

	//TODO
}


hook_method<CTexture* (CTexMgr::*)(const char* fName, bool blackkey)> CTexMgr::_GetTexture(SAKEXE, "CTexMgr::GetTexture");
CTexture* CTexMgr::GetTexture(const char* fName, bool blackkey) // line 247
{
	return (this->*_GetTexture)(fName, blackkey);

	//TODO
}


hook_method<void (CTexMgr::*)(CTexture* t)> CTexMgr::_DestroyTexture(SAKEXE, "CTexMgr::DestroyTexture");
void CTexMgr::DestroyTexture(CTexture* t) // line 274
{
	return (this->*_DestroyTexture)(t);

	//TODO
}


hook_method<void (CTexMgr::*)(void)> CTexMgr::_DestroyAllTexture(SAKEXE, "CTexMgr::DestroyAllTexture");
void CTexMgr::DestroyAllTexture(void) // line 288
{
	return (this->*_DestroyAllTexture)();

	//TODO
}


hook_method<void (CTexMgr::*)(void)> CTexMgr::_UnloadRarelyUsedTexture(SAKEXE, "CTexMgr::UnloadRarelyUsedTexture");
void CTexMgr::UnloadRarelyUsedTexture(void) // line 320-342
{
	return (this->*_UnloadRarelyUsedTexture)();

	//TODO
}


//hook_method<CTexture* (CTexMgr::*)(void)> CTexMgr::_GetDummyTexture(SAKEXE, "CTexMgr::GetDummyTexture");
CTexture* CTexMgr::GetDummyTexture(void) // line ???
{
//	return (this->*_GetDummyTexture)();

	return &CTexMgr::s_dummy_texture;
}


////////////////////////////////////////


hook_func<unsigned long (__cdecl *)(float oow)> _GetSpecularFromOow(SAKEXE, "GetSpecularFromOow");
unsigned long __cdecl GetSpecularFromOow(float oow) // line 2038
{
	return (_GetSpecularFromOow)(oow);

	// TODO
}


hook_func<float (__cdecl *)(float oow)> _GetZFromOow(SAKEXE, "GetZFromOow");
float __cdecl GetZFromOow(float oow) // line 2047
{
	return (_GetZFromOow)(oow);

	// TODO
}


hook_func<float (__cdecl *)(float z)> _GetOowFromZ(SAKEXE, "GetOowFromZ");
float __cdecl GetOowFromZ(float z) // line 2052
{
	return (_GetOowFromZ)(z);

	// TODO
}


