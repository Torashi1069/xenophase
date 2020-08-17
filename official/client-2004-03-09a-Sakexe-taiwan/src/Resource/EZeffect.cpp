#include "Globals.h"
#include "3dLib/Renderer.h" // CTexMgr
#include "Base/ResMgr.h"
#include "Resource/EZeffect.h"
////////////////////////////////////////



KAC_LAYER::KAC_LAYER(void) // line 13-14
{
}


KAC_LAYER::~KAC_LAYER(void) // line 17-21
{
	for( int i = 0; i < countof(m_tex); ++i )
		if( m_tex[i] != NULL )
			m_tex[i]->CTexture::Unlock();
}


CTexture* KAC_LAYER::GetTexture(int iTex) // line 25-42
{
	if( iTex >= cTex )
		return g_texMgr.CTexMgr::GetDummyTexture();

	if( m_tex[iTex] == NULL )
	{
		char texName[256] = "effect\\";
		strcat(texName, m_texName[iTex]); //inlined
		if( strchr(texName, '.') == NULL )
			strcat(texName, ".bmp"); //inlined

		CTexture* pTex = g_texMgr.CTexMgr::GetTexture(texName, true);
		m_tex[iTex] = pTex;
		pTex->CTexture::Lock();
	}

	return m_tex[iTex];
}


////////////////////////////////////////


CEZeffectRes::CEZeffectRes(Exemplar __formal, const char* resid, const char* baseDir) // line 89 (Resource/EZeffect.h)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


CEZeffectRes::CEZeffectRes(void) // line 48-51
{
	m_nMaxLayer = 0;
	this->CEZeffectRes::Reset(); // inlined
}


hook_method<CRes* (CEZeffectRes::*)(void) const> CEZeffectRes::_Clone(SERVER, "CEZeffectRes::Clone");
CRes* CEZeffectRes::Clone(void) const // line 89 (Resource/EZeffect.h)
{
	return (this->*_Clone)();

	return new CEZeffectRes();
}


hook_method<bool (CEZeffectRes::*)(const char* fName)> CEZeffectRes::_Load(SAKEXE, "CEZeffectRes::Load");
bool CEZeffectRes::Load(const char* fName) // line 60-109
{
	return (this->*_Load)(fName);

	if( !m_fp.CFile::Open(fName, 0) )
	{
		mystd::string msg = mystd::string("Str::Cannot find File : ") + fName;
		ErrorMsg(msg.c_str());
		this->Reset();
		return false;
	}

	int dwSig;
	int dwVer;
	m_fp.CFile::Read(&dwSig, 4);
	m_fp.CFile::Read(&dwVer, 4);
	m_fp.CFile::Read(&m_aniClips.cFrame, 4);
	m_fp.CFile::Read(&m_aniClips, 4);
	m_fp.CFile::Read(&m_aniClips.cLayer, 4);
	m_fp.CFile::Seek(16, CFile::current);

	if( dwVer != 148 )
	{
		ErrorMsg("LoadAniClip: Version is incorrect");
		this->Reset();
		return false;
	}

	for( int iLayer = 0; iLayer < m_aniClips.cLayer; ++iLayer )
	{
		KAC_LAYER& layer = m_aniClips.aLayer[iLayer];

		m_fp.CFile::Read(&layer.cTex, 4);

		int i;
		for( i = 0; i < layer.cTex; ++i )
		{
			layer.m_texName[i] = (const char*)m_fp.GetBuf();
			m_fp.Seek(128, CFile::current);
		}

		for( i = layer.cTex; i < sizeof(layer.m_texName)/sizeof(layer.m_texName[0]); ++i )
			layer.m_texName[i] = "1.bmp";

		m_fp.CFile::Read(&layer.cAniKey, 4);

		if( layer.cAniKey > 0 )
		{
			layer.aAniKey = (KAC_KEYFRAME*)m_fp.GetBuf();
			m_fp.Seek(sizeof(KAC_KEYFRAME) * layer.cAniKey, CFile::current);
			
		}
	}

	return true;
}


hook_method<void (CEZeffectRes::*)(void)> CEZeffectRes::_Reset(SERVER, "CEZeffectRes::Reset");
void CEZeffectRes::Reset(void) // line 54-56
{
	return (this->*_Reset)();

	memset(&m_aniClips, 0, sizeof(m_aniClips));
	m_fp.CFile::Close();
}
