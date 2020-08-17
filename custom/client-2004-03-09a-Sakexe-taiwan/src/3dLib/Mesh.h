#pragma once
#include "3dLib/Device.h"
#include "3dLib/Prim.h"


class C3dMesh
{
	/* this+  0 */ private: int m_numVert;
	/* this+  4 */ private: int m_numFace;
	/* this+  8 */ private: int m_numTVert;
	/* this+ 12 */ private: vector3d* m_vert;
	/* this+ 16 */ private: vector3d* m_faceNormal;
	/* this+ 20 */ private: vector3d* m_vertNormal;
	/* this+ 24 */ private: tvertex3d* m_tvert;
	/* this+ 28 */ private: face3d* m_face;
	/* this+ 32 */ private: C3dMesh* m_parent;
	/* this+ 36 */ private: mystd::vector<int> m_shadeGroup[32];
	/* this+548 */ private: CDynamicVB m_vb;

	//public: void C3dMesh::C3dMesh();
	//public: void C3dMesh::~C3dMesh();
	//public: void SetParent(class C3dMesh *);
	//public: void C3dMesh::UpdateNormal();
	//public: void C3dMesh::Release();
	//public: void SortFace();
};
