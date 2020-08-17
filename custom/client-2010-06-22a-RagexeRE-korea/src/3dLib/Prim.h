#pragma once


struct matrix
{
	/* this+ 0 */ float v11;
	/* this+ 4 */ float v12;
	/* this+ 8 */ float v13;
	/* this+12 */ float v21;
	/* this+16 */ float v22;
	/* this+20 */ float v23;
	/* this+24 */ float v31;
	/* this+28 */ float v32;
	/* this+32 */ float v33;
	/* this+36 */ float v41;
	/* this+40 */ float v42;
	/* this+44 */ float v43;
};


struct vector2d
{
	/* this+0 */ float x;
	/* this+4 */ float y;
};


struct vector3d
{
	/* this+0 */ float x;
	/* this+4 */ float y;
	/* this+8 */ float z;

	public: vector3d::vector3d(void)
	{
	}

	public: vector3d::vector3d(float nx, float ny, float nz)
	{
		this->x = nx;
		this->y = ny;
		this->z = nz;
	}
};


struct ray3d
{
	/* this+ 0 */ vector3d org;
	/* this+12 */ vector3d dir;
};


struct lineSegment3d
{
	/* this+ 0 */ vector3d org;
	/* this+12 */ vector3d dir;
	/* this+24 */ float limit;
};


struct UVRECT
{
	/* this+ 0 */ float u1;
	/* this+ 4 */ float v1;
	/* this+ 8 */ float u2;
	/* this+12 */ float v2;
};


void __cdecl CreateTrigonometricTable(void);
