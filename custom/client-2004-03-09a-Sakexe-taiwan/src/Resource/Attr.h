#pragma once
#include "Base/Res.h"
#include "3dLib/Prim.h"


struct CAttrCell
{
	/* this+ 0 */ float h1;
	/* this+ 4 */ float h2;
	/* this+ 8 */ float h3;
	/* this+12 */ float h4;
	/* this+16 */ int flag;

	public: CAttrCell::CAttrCell(void);
};


class C3dAttr : public CRes
{
	struct vtable_t
	{
		void* (C3dAttr::* scalar_deleting_destructor)(unsigned int flags);
		bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (C3dAttr::* Clone)(void) const;
		bool (C3dAttr::* Load)(const char* fName);
		void (C3dAttr::* Reset)(void);
		void (CRes::* OnLoadError)(const char* fName);
	};

	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ public: int m_width;
	/* this+276 */ public: int m_height;
	/* this+280 */ public: int m_zoom;
	/* this+284 */ public: mystd::vector<CAttrCell> m_cells;

	public: C3dAttr::C3dAttr(Exemplar __formal, const char* resid, const char* baseDir); // line 26
	public: C3dAttr::C3dAttr(void);
	public: virtual CRes* C3dAttr::Clone(void) const; // line 26
	public: void C3dAttr::Create(int w, int h);
	public: virtual bool C3dAttr::Load(const char* fName);
	public: virtual void C3dAttr::Reset(void);
	public: float C3dAttr::GetHeight(float x, float z);
	//public: int C3dAttr::GetAttr(float, float);
	public: CAttrCell* C3dAttr::GetCell(int Cellx, int Celly);
	public: float C3dAttr::RayTest(const ray3d& ray, int x, int y);
	public: void C3dAttr::SetCellInfo(int Type, int Cellx, int Celly); // line 54
	//public: void C3dAttr::GetWorldPos(float, float, vector2d&);
	//public: void ConvertToCellCoor(float, float, long&, long&);
	//public: void C3dAttr::GetHeightMinMax(const RECT&, float&, float&);

private:
	static hook_method<CRes* (C3dAttr::*)(void) const> C3dAttr::_Clone;
	static hook_method<void (C3dAttr::*)(int w, int h)> C3dAttr::_Create;
	static hook_method<bool (C3dAttr::*)(const char* fName)> C3dAttr::_Load;
	static hook_method<void (C3dAttr::*)(void)> C3dAttr::_Reset;
	static hook_method<float (C3dAttr::*)(float x, float z)> C3dAttr::_GetHeight;
	static hook_method<CAttrCell* (C3dAttr::*)(int Cellx, int Celly)> C3dAttr::_GetCell;
	static hook_method<float (C3dAttr::*)(const ray3d& ray, int x, int y)> C3dAttr::_RayTest;
	static hook_method<void (C3dAttr::*)(int Type, int Cellx, int Celly)> C3dAttr::_SetCellInfo;
};
