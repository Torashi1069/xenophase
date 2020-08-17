#include "3dLib/Renderer.h"


hook_func<void (CRenderer::*)(int sx, int sy, const vector3d& from, const matrix& invViewMatrix, ray3d* ray)> CRenderer::_BuildRay("CRenderer::BuildRay");
void CRenderer::BuildRay(int sx, int sy, const vector3d& from, const matrix& invViewMatrix, ray3d* ray)
{
	return (this->*_BuildRay)(sx, sy, from, invViewMatrix, ray);
}


hook_func<void (CRenderer::*)(const vector3d& src, const matrix& vtm, float* x, float* y, float* oow)> CRenderer::_ProjectVertex("CRenderer::ProjectVertex(float)");
void CRenderer::ProjectVertex(const vector3d& src, const matrix& vtm, float* x, float* y, float* oow)
{
	return (this->*_ProjectVertex)(src, vtm, x, y, oow);
}


hook_func<void (CRenderer::*)(const vector3d& src, const matrix& vtm, tlvertex3d* vert)> CRenderer::_ProjectVertex2("CRenderer::ProjectVertex(vert)");
void CRenderer::ProjectVertex(const vector3d& src, const matrix& vtm, tlvertex3d* vert)
{
	return (this->*_ProjectVertex2)(src, vtm, vert);
}


hook_func<float (CRenderer::*)(float oow)> CRenderer::_GetPixelRatio("CRenderer::GetPixelRatio");
float CRenderer::GetPixelRatio(float oow)
{
	return (this->*_GetPixelRatio)(oow);
}


hook_func<float (CRenderer::*)(void)> CRenderer::_GetScreenXFactor("CRenderer::GetScreenXFactor");
float CRenderer::GetScreenXFactor(void)
{
	return (this->*_GetScreenXFactor)();
}


hook_func<float (CRenderer::*)(void)> CRenderer::_GetScreenYFactor("CRenderer::GetScreenYFactor");
float CRenderer::GetScreenYFactor(void)
{
	return (this->*_GetScreenYFactor)();
}


CRenderer*& g_renderer = VTOR<CRenderer*>(SymDB::Find("g_renderer"));
