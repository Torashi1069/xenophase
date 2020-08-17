#include "3dActor.h"
#include "Globals.h"
#include "Base/ResMgr.h"
#include "Resource/SkyBox.h"
#include "Resource/Model.h" // C3dModelRes


hook_method<void (CFlare::*)(matrix& view, vector3d vFrom, vector3d vAt)> CFlare::_Render(SAKEXE, "CFlare::Render");
void CFlare::Render(matrix& view, vector3d vFrom, vector3d vAt) // line 75
{
	return (this->*_Render)(view, vFrom, vAt);

	//TODO
}


hook_method<Flare (CFlare::*)(int wType, float fLoc, float fScale, float r, float g, float b)> CFlare::_SetFlare(SAKEXE, "CFlare::SetFlare");
Flare CFlare::SetFlare(int wType, float fLoc, float fScale, float r, float g, float b) // line 27
{
	return (this->*_SetFlare)(wType, fLoc, fScale, r, g, b);

	Flare ret;
	ret.wType = wType;
	ret.fLoc = fLoc;
	ret.r = r;
	ret.g = g;
	ret.b = b;

	return ret;
}


hook_method<void (CFlare::*)(float fTimeKey, vector3d vFrom, vector3d vAt)> CFlare::_Process(SAKEXE, "CFlare::Process");
void CFlare::Process(float fTimeKey, vector3d vFrom, vector3d vAt) // line 39
{
	return (this->*_Process)(fTimeKey, vFrom, vAt);

	//TODO
}


hook_method<void (CFlare::*)(void)> CFlare::_Init(SAKEXE, "CFlare::Init");
void CFlare::Init(void) // line 6
{
	return (this->*_Init)();

	//TODO
}


////////////////////////////////////////


CSkyBox::CSkyBox(void) // line 145
{
	//TODO
}


CSkyBox::~CSkyBox(void) // line 172
{
}


hook_method<void (CSkyBox::*)(matrix& view, vector3d* vPos, float roty, float fLatitude, vector3d vFrom, vector3d vAt)> CSkyBox::_Render(SAKEXE, "CSkyBox::Render");
void CSkyBox::Render(matrix& view, vector3d* vPos, float roty, float fLatitude, vector3d vFrom, vector3d vAt) // line 226
{
	return (this->*_Render)(view, vPos, roty, fLatitude, vFrom, vAt);

	//TODO
}


hook_method<bool (CSkyBox::*)(float hratio, float vratio, vector3d vPos, matrix& view, tlvertex3d vert)> CSkyBox::_ChkVisible(SAKEXE, "CSkyBox::ChkVisible");
bool CSkyBox::ChkVisible(float hratio, float vratio, vector3d vPos, matrix& view, tlvertex3d vert) // line 175
{
	return (this->*_ChkVisible)(hratio, vratio, vPos, view, vert);

	//TODO
}


////////////////////////////////////////


CSkyBoxEllipse::CSkyBoxEllipse(void) // line 436
{
	m_res = (C3dModelRes*)g_resMgr().CResMgr::Get("skybox.rsm");
	m_sky = new C3dActor();

	m_sky->C3dActor::SetScale(vector3d(30.0, 30.0, 30.0));
	m_sky->C3dActor::SetRot(vector3d(0.0, 0.0, 0.0));
	m_fLoopRotX = 0.0;
	m_sky->C3dActor::SetAnimSpeed(1.f/30.f);
	m_sky->C3dActor::AssignModel(m_res);
	m_sky->C3dActor::UpdateVertexColor(vector3d(0.0, 1.0, 0.0), vector3d(1.0, 1.0, 1.0), vector3d(1.0, 1.0, 1.0));
	m_sky->C3dActor::SetFrame(0);
	m_flare.CFlare::Init();
}


CSkyBoxEllipse::~CSkyBoxEllipse(void) // line 451
{
	if( m_sky != NULL )
	{
		delete m_sky;
		m_sky = NULL;
	}
}


hook_method<void (CSkyBoxEllipse::*)(matrix& view, vector3d* vPos, float roty, float fLatitude, vector3d vFrom, vector3d vAt)> CSkyBoxEllipse::_Render(SAKEXE, "CSkyBoxEllipse::Render");
void CSkyBoxEllipse::Render(matrix& view, vector3d* vPos, float roty, float fLatitude, vector3d vFrom, vector3d vAt) // line 459
{
	return (this->*_Render)(view, vPos, roty, fLatitude, vFrom, vAt);

	//TODO
}
