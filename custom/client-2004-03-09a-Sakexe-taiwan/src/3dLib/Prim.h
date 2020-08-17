#pragma once
#include "Struct.h" // struct COLOR
struct matrix;
struct vector2d;
struct vector3d;
struct C3dOBB; // 3dActor.h


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

	//public: void SetRow1(float, float, float);
	//public: void SetRow2(float, float, float);
	//public: void SetRow3(float, float, float);
	//public: void SetRow4(float, float, float);
	public: void matrix::MakeIdentity(void);
	public: void matrix::MakeInverse(const matrix& src);
	public: void matrix::MakeTranslate(const vector3d& v);
	public: void matrix::MakeTranslate(float x, float y, float z);
	public: void matrix::MakeXRotation(float angle);
	public: void matrix::MakeYRotation(float angle);
	public: void matrix::MakeZRotation(float angle);
	public: void matrix::MakeScale(float x, float y, float z);
	public: void matrix::AppendTranslate(const vector3d& v);
	public: void matrix::AppendXRotation(float angle);
	public: void matrix::AppendYRotation(float angle);
	public: void matrix::AppendZRotation(float angle);
	public: void matrix::AppendScale(float x, float y, float z);
	//public: void matrix::PrependTranslate(const vector3d &);
	//public: void PrependScale(float *);
	//public: void matrix::PrependScale(float, float, float);
	//public: void matrix::MakeTransform(rotKeyframe &);
	//public: void matrix::MakeTransform(float *, float);
	//public: void matrix::MakeTransform(const vector3d &, float *, float);
	//public: void matrix::MakeView(const vector3d &, const vector3d &, const vector3d &);
	public: void matrix::MultMatrix(const matrix& a, const matrix& b);
	public: int matrix::IsIdentity(void);
	//public: void matrix::VECTOR_TO_VIEW(vector3d &, vector3d &, vector3d &, vector3d &);
	//public: void matrix::VIEW_MATRIX(vector3d &, vector3d &, int);
	//public: void matrix::VECTOR_TO_REV_VIEW(vector3d &, vector3d &, vector3d &, vector3d &);
	//public: void matrix::REV_VIEW_MATRIX(vector3d &, vector3d &, int);
	//public: void matrix::VECTOR_TO_MATRIX(vector3d &);
	//public: void matrix::NORMALIZE_SCALE(matrix &);
	//public: void matrix::REVERSE_MATRIX(matrix &);
	//public: void matrix::UPVECTOR_TO_MATRIX(vector3d);

private:
	static hook_method<void (matrix::*)(void)> matrix::_MakeIdentity;
	static hook_method<void (matrix::*)(const matrix& src)> matrix::_MakeInverse;
	static hook_method<void (matrix::*)(const vector3d& v)> matrix::_MakeTranslate;
	static hook_method<void (matrix::*)(float x, float y, float z)> matrix::_MakeTranslate2;
	static hook_method<void (matrix::*)(float angle)> matrix::_MakeXRotation;
	static hook_method<void (matrix::*)(float angle)> matrix::_MakeYRotation;
	static hook_method<void (matrix::*)(float angle)> matrix::_MakeZRotation;
	static hook_method<void (matrix::*)(float x, float y, float z)> matrix::_MakeScale;
	static hook_method<void (matrix::*)(const vector3d& v)> matrix::_AppendTranslate;
	static hook_method<void (matrix::*)(float angle)> matrix::_AppendXRotation;
	static hook_method<void (matrix::*)(float angle)> matrix::_AppendYRotation;
	static hook_method<void (matrix::*)(float angle)> matrix::_AppendZRotation;
	static hook_method<void (matrix::*)(float x, float y, float z)> matrix::_AppendScale;
	static hook_method<void (matrix::*)(const matrix& a, const matrix& b)> matrix::_MultMatrix;
	static hook_method<int (matrix::*)(void)> matrix::_IsIdentity;
};


struct plane3d
{
	/* this+ 0 */ float x;
	/* this+ 4 */ float y;
	/* this+ 8 */ float z;
	/* this+12 */ float w;

	//public: void plane3d(float, float, float, float);
	//public: void plane3d();
	//public: void Set(float, float, float, float);
	//public: void MatrixMult(const struct matrix &, const struct plane3d &);
};


struct vector2d
{
	/* this+0 */ float x;
	/* this+4 */ float y;

	public: vector2d::vector2d(void);
	public: vector2d::vector2d(float nx, float ny);
	public: void vector2d::Set(float nx, float ny);
	//public: void Normalize();
};


struct vector3d
{
	/* this+0 */ float x;
	/* this+4 */ float y;
	/* this+8 */ float z;

	public: vector3d::vector3d(void); // line 47
	public: vector3d::vector3d(float nx, float ny, float nz); // line 48
	public: void vector3d::Set(float nx, float ny, float nz);
	//public: void MatrixMult(const vector3d&, const matrix&);
	//public: void CrossProduct(const vector3d&, const vector3d&);
	public: void vector3d::Normalize(void);
	//public: float Magnitude();
	//public: float Angle(const vector3d&);
	//public: float DotProduct(const vector3d&);
	public: void vector3d::MATRIX_TO_VECTOR(matrix& dir);
	public: vector3d& vector3d::operator=(const vector3d& rhs); // line 67
	//public: vector3d& vector3d::operator+=(const vector3d& rhs);
	//public: vector3d& vector3d::operator-=(const vector3d& rhs);
	//public: vector3d& operator*=(const float&);
	//public: vector3d operator*(const float&);
};


struct vector4d
{
	/* this+ 0 */ float x;
	/* this+ 4 */ float y;
	/* this+ 8 */ float z;
	/* this+12 */ float oow;

	public: vector4d::vector4d(void);
	public: vector4d::vector4d(float x, float y, float z, float oow);
};


struct tvertex3d
{
	/* this+0 */ unsigned long color;
	/* this+4 */ float u;
	/* this+8 */ float v;

	//public: void Set(float, float);
};


struct face3d
{
	/* this+ 0 */ unsigned short vertindex[3];
	/* this+ 6 */ unsigned short tvertindex[3];
	/* this+12 */ unsigned short meshMtlId;
	/* this+16 */ int twoSide;
	/* this+20 */ int smoothGroup;

	//public: void Set(int, int, int, int);
	//public: void Set(int, int, int);
	//public: void SetT(int, int, int);
	//public: face3d& operator=(const face3d_v11&);
	//public: face3d& face3d::operator=(const face3d&); // line 218
	//public: bool operator<(const face3d&);
};


struct ray3d
{
	/* this+ 0 */ vector3d org;
	/* this+12 */ vector3d dir;
};


struct lmvertex3d
{
	/* this+ 0 */ vector3d wvert;
	/* this+12 */ COLOR argbs;
	/* this+16 */ vector2d uv;
	/* this+24 */ vector2d uv2;
};


struct tlvertex3d
{
	/* this+ 0 */ float x;
	/* this+ 4 */ float y;
	/* this+ 8 */ float z;
	/* this+12 */ float oow;
	union {
	/* this+16 */ unsigned long color;
	/* this+16 */ COLOR argb;
	};
	/* this+20 */ unsigned long specular;
	union {
	struct {
	/* this+24 */ float tu;
	/* this+28 */ float tv;
	};
	/* this+24 */ texCoor coord;
	};

	public: tlvertex3d::tlvertex3d(void); // line 423
	public: tlvertex3d::tlvertex3d(float x, float y, float z, float oow, unsigned long color, unsigned long specular, float tu, float tv);
};


struct lmtlvertex3d
{
	/* this+ 0 */ tlvertex3d vert;
	/* this+32 */ texCoor lmcoord;
};


struct lineSegment3d
{
	/* this+ 0 */ vector3d org;
	/* this+12 */ vector3d dir;
	/* this+24 */ float limit;
};


struct w3d_quaternion
{
	/* this+ 0 */ float qw;
	/* this+ 4 */ float qx;
	/* this+ 8 */ float qy;
	/* this+12 */ float qz;

	//w3d_quaternion();
	//w3d_quaternion(float, float, float, float);
	//w3d_quaternion operator+(struct w3d_quaternion &);
	//w3d_quaternion operator*(float &);
};


float __cdecl _sqrt(float input);
float __cdecl _sin(float input);
float __cdecl _cos(float input);
void __cdecl CreateTrigonometricTable(void);
float __cdecl GetSin(int degree);
float __cdecl GetCos(int degree);
void __cdecl ROTATION_TO_QUATERNION(w3d_quaternion& q, vector3d& v, float& fTheta);
void __cdecl QUATERNION_TO_ROTATION(vector3d& v, float& fTheta, w3d_quaternion& q);
void __cdecl ANGLES_TO_QUATERNION(w3d_quaternion& q, float fYaw, float fPitch, float fRoll);
void __cdecl QUATERNION_TO_MATRIX(matrix& mat, w3d_quaternion& trans);
void __cdecl MATRIX_TO_QUATERNION(w3d_quaternion& trans, matrix& mat);
float __cdecl QUATERNION_DOT_PRODUCT(w3d_quaternion& p, w3d_quaternion& q);
void __cdecl QUATERNION_MULTIPLY(w3d_quaternion& q, w3d_quaternion& a, w3d_quaternion& b);
w3d_quaternion __cdecl INTERPOLATE_QUATERNION(double t, w3d_quaternion& p, w3d_quaternion& q);
int __cdecl CheckRayOBBIntersect(const ray3d& ray, const C3dOBB& obb);
BOOL __cdecl CheckRayTriIntersect(const ray3d& ray, const vector3d& v0, const vector3d& v1, const vector3d& v2, float* u, float* v, float* t);
int __cdecl CheckLineSegmentOBBIntersect(const lineSegment3d& ray, const C3dOBB& obb);
int __cdecl CheckLineSegmentTriIntersect(const lineSegment3d& ray, const vector3d& v0, const vector3d& v1, const vector3d& v2, float* u, float* v, float* t);
float __cdecl SquaredVertRayDist(const ray3d& ray, const vector3d& Vert);
