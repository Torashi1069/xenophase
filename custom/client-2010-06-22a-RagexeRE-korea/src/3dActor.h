#pragma once
#include "3dLib/Prim.h"


struct C3dOBB // oBoundingBox
{
	/* this+ 0 */ vector3d halfSize;
	/* this+12 */ vector3d center;
	/* this+24 */ vector3d u;
	/* this+36 */ vector3d v;
	/* this+48 */ vector3d w;
	/* this+60 */ vector3d vertices[8];
};


struct C3dAABB // aaBoundingBox
{
	/* this+ 0 */ vector3d min;
	/* this+12 */ vector3d max;
};
