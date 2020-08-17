#pragma once
struct vector3d;
struct matrix;
struct ray3d;
struct tlvertex3d;


class CRenderer
{
	/* this+ 0 */ private: BYTE dummy_0[36];
	/* this+36 */ private: int m_width;
	/* this+40 */ private: int m_height;
	/* this+44 */ private: int m_halfWidth;
	/* this+48 */ private: int m_halfHeight;
	/* this+52 */ //TODO

	public: void CRenderer::BuildRay(int sx, int sy, const vector3d& from, const matrix& invViewMatrix, ray3d* ray);
	public: void CRenderer::ProjectVertex(const vector3d& src, const matrix& vtm, float* x, float* y, float* oow);
	public: void CRenderer::ProjectVertex(const vector3d& src, const matrix& vtm, tlvertex3d* vert);
	public: float CRenderer::GetPixelRatio(float oow);
	public: float CRenderer::GetScreenXFactor(void);
	public: float CRenderer::GetScreenYFactor(void);

	/// @custom
	public: int CRenderer::GetWidth(void) { return m_width; }
	public: int CRenderer::GetHeight(void) { return m_height; }

public:
	static hook_func<void (CRenderer::*)(int sx, int sy, const vector3d& from, const matrix& invViewMatrix, ray3d* ray)> CRenderer::_BuildRay;
	static hook_func<void (CRenderer::*)(const vector3d& src, const matrix& vtm, float* x, float* y, float* oow)> CRenderer::_ProjectVertex;
	static hook_func<void (CRenderer::*)(const vector3d& src, const matrix& vtm, tlvertex3d* vert)> CRenderer::_ProjectVertex2;
	static hook_func<float (CRenderer::*)(float oow)> CRenderer::_GetPixelRatio;
	static hook_func<float (CRenderer::*)(void)> CRenderer::_GetScreenXFactor;
	static hook_func<float (CRenderer::*)(void)> CRenderer::_GetScreenYFactor;
};


extern CRenderer*& g_renderer;
