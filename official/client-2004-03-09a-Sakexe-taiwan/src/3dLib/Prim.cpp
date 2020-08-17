#include "Globals.h"
#include "Prim.h"
#define _USE_MATH_DEFINES
#include <math.h>
const float epsilon = 0.00001f;
////////////////////////////////////////


hook_func<float (__cdecl *)(float input)> __sqrt(SAKEXE, "_sqrt");
float __cdecl _sqrt(float input) // line 11-18
{
	return (__sqrt)(input);

	__asm
	{
	fld input
	fsqrt
	fstp input
	}

	return input;
}


hook_func<float (__cdecl *)(float input)> __sin(SAKEXE, "_sin");
float __cdecl _sin(float input) // line 20-27
{
	return (__sin)(input);

	__asm
	{
	fld input
	fsin
	fstp input
	}

	return input;
}


hook_func<float (__cdecl *)(float input)> __cos(SAKEXE, "_cos");
float __cdecl _cos(float input) // line 29-36
{
	return (__cos)(input);

	__asm
	{
	fld input
	fcos
	fstp input
	}

	return input;
}


////////////////////////////////////////


//hook_method<void (matrix::*)(void)> matrix::_MakeIdentity(SAKEXE, "matrix::MakeIdentity");
void matrix::MakeIdentity(void) // line ??-??
{
//	return (this->*_MakeIdentity)();

	memcpy(this, &_IdentityMatrix, sizeof(*this));
}


hook_method<void (matrix::*)(const matrix& src)> matrix::_MakeInverse(SAKEXE, "matrix::MakeInverse");
void matrix::MakeInverse(const matrix& src) // line 253-273
{
	return (this->*_MakeInverse)(src);

	//TODO
}


//hook_method<void (matrix::*)(const vector3d& v)> matrix::_MakeTranslate(SAKEXE, "?MakeTranslate@matrix@@QAEXABUvector3d@@@Z");
void matrix::MakeTranslate(const vector3d& v) // line ??-??
{
//	return (this->*_MakeTranslate)(v);

	this->matrix::MakeTranslate(v.x, v.y, v.z);
}


hook_method<void (matrix::*)(float x, float y, float z)> matrix::_MakeTranslate2(SAKEXE, "?MakeTranslate@matrix@@QAEXMMM@Z");
void matrix::MakeTranslate(float x, float y, float z) // line 46-51
{
	return (this->*_MakeTranslate2)(x, y, z);

	this->matrix::MakeIdentity(); // inlined
	this->v41 = x;
	this->v42 = y;
	this->v43 = z;
}


hook_method<void (matrix::*)(float angle)> matrix::_MakeXRotation(SAKEXE, "matrix::MakeXRotation");
void matrix::MakeXRotation(float angle) // line 54-61
{
	return (this->*_MakeXRotation)(angle);

	this->matrix::MakeIdentity(); // inlined
	float sin_angle = _sin(angle);
	float cos_angle = _cos(angle);
	this->v22 = cos_angle;
	this->v33 = cos_angle;
	this->v32 = -sin_angle;
	this->v23 = sin_angle;
}


hook_method<void (matrix::*)(float angle)> matrix::_MakeYRotation(SAKEXE, "matrix::MakeYRotation");
void matrix::MakeYRotation(float angle) // line 64-71
{
	return (this->*_MakeYRotation)(angle);

	this->matrix::MakeIdentity(); // inlined
	float sin_angle = _sin(angle);
	float cos_angle = _cos(angle);
	this->v11 = cos_angle;
	this->v33 = cos_angle;
	this->v13 = -sin_angle;
	this->v31 = sin_angle;
}


hook_method<void (matrix::*)(float angle)> matrix::_MakeZRotation(SAKEXE, "matrix::MakeZRotation");
void matrix::MakeZRotation(float angle) // line 74-81
{
	return (this->*_MakeZRotation)(angle);

	this->matrix::MakeIdentity(); // inlined
	float sin_angle = _sin(angle);
	float cos_angle = _cos(angle);
	this->v11 = cos_angle;
	this->v22 = cos_angle;
	this->v21 = -sin_angle;
	this->v12 = sin_angle;
}


hook_method<void (matrix::*)(float x, float y, float z)> matrix::_MakeScale(SAKEXE, "matrix::MakeScale");
void matrix::MakeScale(float x, float y, float z) // line 84-89
{
	return (this->*_MakeScale)(x, y, z);

	this->matrix::MakeIdentity(); // inlined
	this->v11 = x;
	this->v22 = y;
	this->v33 = z;
}


hook_method<void (matrix::*)(const vector3d& v)> matrix::_AppendTranslate(SAKEXE, "matrix::AppendTranslate");
void matrix::AppendTranslate(const vector3d& v) // line 92-98
{
	return (this->*_AppendTranslate)(v);

	matrix TM;
	TM.matrix::MakeTranslate(v); // inlined

	matrix temp;
	temp.matrix::MultMatrix(*this, TM);

	memcpy(this, &temp, sizeof(*this));
}


hook_method<void (matrix::*)(float angle)> matrix::_AppendXRotation(SAKEXE, "matrix::AppendXRotation");
void matrix::AppendXRotation(float angle) // line 101-107
{
	return (this->*_AppendXRotation)(angle);

	matrix TM;
	TM.matrix::MakeXRotation(angle); // inlined

	matrix temp;
	temp.matrix::MultMatrix(*this, TM);

	memcpy(this, &temp, sizeof(*this));
}


hook_method<void (matrix::*)(float angle)> matrix::_AppendYRotation(SAKEXE, "matrix::AppendYRotation");
void matrix::AppendYRotation(float angle) // line 110-116
{
	return (this->*_AppendYRotation)(angle);

	matrix TM;
	TM.matrix::MakeYRotation(angle); // inlined

	matrix temp;
	temp.matrix::MultMatrix(*this, TM);

	memcpy(this, &temp, sizeof(*this));
}


hook_method<void (matrix::*)(float angle)> matrix::_AppendZRotation(SAKEXE, "matrix::AppendZRotation");
void matrix::AppendZRotation(float angle) // line 119-125
{
	return (this->*_AppendZRotation)(angle);

	matrix TM;
	TM.matrix::MakeZRotation(angle); // inlined

	matrix temp;
	temp.matrix::MultMatrix(*this, TM);

	memcpy(this, &temp, sizeof(*this));
}


hook_method<void (matrix::*)(float x, float y, float z)> matrix::_AppendScale(SAKEXE, "matrix::AppendScale");
void matrix::AppendScale(float x, float y, float z) // line 128-134
{
	return (this->*_AppendScale)(x, y, z);

	matrix TM;
	TM.matrix::MakeScale(x, y, z); // inlined

	matrix temp;
	temp.matrix::MultMatrix(*this, TM);

	memcpy(this, &temp, sizeof(*this));
}


hook_method<void (matrix::*)(const matrix& a, const matrix& b)> matrix::_MultMatrix(SAKEXE, "matrix::MultMatrix");
void matrix::MultMatrix(const matrix& a, const matrix& b) // line 237-250
{
	return (this->*_MultMatrix)(a, b);

	this->v11 = a.v11 * b.v11 + a.v12 * b.v21 + a.v13 * b.v31;
	this->v21 = a.v21 * b.v11 + a.v22 * b.v21 + a.v23 * b.v31;
	this->v31 = a.v31 * b.v11 + a.v32 * b.v21 + a.v33 * b.v31;
	this->v41 = a.v41 * b.v11 + a.v42 * b.v21 + a.v43 * b.v31 + b.v41;
	this->v12 = a.v11 * b.v12 + a.v12 * b.v22 + a.v13 * b.v32;
	this->v22 = a.v21 * b.v12 + a.v22 * b.v22 + a.v23 * b.v32;
	this->v32 = a.v31 * b.v12 + a.v32 * b.v22 + a.v33 * b.v32;
	this->v42 = a.v41 * b.v12 + a.v42 * b.v22 + a.v43 * b.v32 + b.v42;
	this->v13 = a.v11 * b.v13 + a.v12 * b.v23 + a.v13 * b.v33;
	this->v23 = a.v21 * b.v13 + a.v22 * b.v23 + a.v23 * b.v33;
	this->v33 = a.v31 * b.v13 + a.v32 * b.v23 + a.v33 * b.v33;
	this->v43 = a.v41 * b.v13 + a.v42 * b.v23 + a.v43 * b.v33 + b.v43;
}


hook_method<int (matrix::*)(void)> matrix::_IsIdentity(SAKEXE, "matrix::IsIdentity");
int matrix::IsIdentity(void) // line 276-302
{
	return (this->*_IsIdentity)();

	//FIXME: broken by integer arithmetic (fixed between 2010-06-22aRagexeRE and 2012-02-07bRagexeRE)
    return abs(long(this->v11 - 1.0)) <= epsilon
        && abs(long(this->v22 - 1.0)) <= epsilon
        && abs(long(this->v33 - 1.0)) <= epsilon
        && abs(long(this->v12)) <= epsilon
        && abs(long(this->v13)) <= epsilon
        && abs(long(this->v21)) <= epsilon
        && abs(long(this->v23)) <= epsilon
        && abs(long(this->v31)) <= epsilon
        && abs(long(this->v32)) <= epsilon
        && abs(long(this->v41)) <= epsilon
        && abs(long(this->v42)) <= epsilon
        && abs(long(this->v43)) <= epsilon;

}


////////////////////////////////////////


vector2d::vector2d(void) // line ??
{
}


vector2d::vector2d(float nx, float ny) // line ??
{
	this->vector2d::Set(nx, ny);
}


void vector2d::Set(float nx, float ny) // line ??
{
	this->x = nx;
	this->y = ny;
}


////////////////////////////////////////


vector3d::vector3d(void) // line 47 (Prim.h)
{
}


vector3d::vector3d(float nx, float ny, float nz) // line 48 (Prim.h)
{
	this->vector3d::Set(nx, ny, nz);
}


void vector3d::Set(float nx, float ny, float nz) // line ??
{
	this->x = nx;
	this->y = ny;
	this->z = nz;
}


void vector3d::Normalize(void) // line ??
{
	double div = 1.0 / _sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	this->x = float(div * this->x);
	this->y = float(div * this->y);
	this->z = float(div * this->z);
}


void vector3d::MATRIX_TO_VECTOR(matrix& dir) // line 449
{
	this->x = dir.v13;
	this->y = dir.v23;
	this->z = dir.v33;
}


vector3d& vector3d::operator=(const vector3d& rhs) // line 67 (Prim.h)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}


////////////////////////////////////////


vector4d::vector4d(void) // line ???
{
}


vector4d::vector4d(float x, float y, float z, float oow) // line ???
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->oow = oow;
}


////////////////////////////////////////


tlvertex3d::tlvertex3d(void) // line 423 (3dLib/Prim.h)
{
	this->specular = 0xFF000000;
}


tlvertex3d::tlvertex3d(float x, float y, float z, float oow, unsigned long color, unsigned long specular, float tu, float tv) // line ???
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->oow = oow;
	this->color = color;
	this->specular = specular;
	this->tu = tu;
	this->tv = tv;
}


////////////////////////////////////////


hook_func<void (__cdecl *)(w3d_quaternion& q, vector3d& v, float& fTheta)> _ROTATION_TO_QUATERNION(SAKEXE, "ROTATION_TO_QUATERNION");
void __cdecl ROTATION_TO_QUATERNION(w3d_quaternion& q, vector3d& v, float& fTheta) // line 549-564
{
	return (_ROTATION_TO_QUATERNION)(q, v, fTheta);

	//TODO
}


hook_func<void (__cdecl *)(vector3d& v, float& fTheta, w3d_quaternion& q)> _QUATERNION_TO_ROTATION(SAKEXE, "QUATERNION_TO_ROTATION");
void __cdecl QUATERNION_TO_ROTATION(vector3d& v, float& fTheta, w3d_quaternion& q) // line 568-582
{
	return (_QUATERNION_TO_ROTATION)(v, fTheta, q);

	//TODO
}


hook_func<void (__cdecl *)(w3d_quaternion& q, float fYaw, float fPitch, float fRoll)> _ANGLES_TO_QUATERNION(SAKEXE, "ANGLES_TO_QUATERNION");
void __cdecl ANGLES_TO_QUATERNION(w3d_quaternion& q, float fYaw, float fPitch, float fRoll) // line 586-598
{
	return (_ANGLES_TO_QUATERNION)(q, fYaw, fPitch, fRoll);

	//TODO
}


hook_func<void (__cdecl *)(matrix& mat, w3d_quaternion& trans)> _QUATERNION_TO_MATRIX(SAKEXE, "QUATERNION_TO_MATRIX");
void __cdecl QUATERNION_TO_MATRIX(matrix& mat, w3d_quaternion& trans) // line 604-622
{
	return (_QUATERNION_TO_MATRIX)(mat, trans);

	//TODO
}


hook_func<void (__cdecl *)(w3d_quaternion& trans, matrix& mat)> _MATRIX_TO_QUATERNION(SAKEXE, "MATRIX_TO_QUATERNION");
void __cdecl MATRIX_TO_QUATERNION(w3d_quaternion& trans, matrix& mat) // line 626-662
{
	return (_MATRIX_TO_QUATERNION)(trans, mat);

	//TODO
}


hook_func<float (__cdecl *)(w3d_quaternion& p, w3d_quaternion& q)> _QUATERNION_DOT_PRODUCT(SAKEXE, "QUATERNION_DOT_PRODUCT");
float __cdecl QUATERNION_DOT_PRODUCT(w3d_quaternion& p, w3d_quaternion& q) // line 676-678
{
	return (_QUATERNION_DOT_PRODUCT)(p, q);

	//TODO
}


hook_func<void (__cdecl *)(w3d_quaternion& q, w3d_quaternion& a, w3d_quaternion& b)> _QUATERNION_MULTIPLY(SAKEXE, "QUATERNION_MULTIPLY");
void __cdecl QUATERNION_MULTIPLY(w3d_quaternion& q, w3d_quaternion& a, w3d_quaternion& b) // line 682-687
{
	return (_QUATERNION_MULTIPLY)(q, a, b);

	//TODO
}


hook_func<w3d_quaternion (__cdecl *)(double t, w3d_quaternion& p, w3d_quaternion& q)> _INTERPOLATE_QUATERNION(SAKEXE, "INTERPOLATE_QUATERNION");
w3d_quaternion __cdecl INTERPOLATE_QUATERNION(double t, w3d_quaternion& p, w3d_quaternion& q) // line 692-725
{
	return (_INTERPOLATE_QUATERNION)(t, p, q);

	//TODO
}


hook_func<void (__cdecl *)(void)> _CreateTrigonometricTable(SAKEXE, "CreateTrigonometricTable");
void __cdecl CreateTrigonometricTable(void) // line 729-739
{
	return (_CreateTrigonometricTable)();

	for( int i = 0; i <= 360; ++i )
	{
		g_radTable[i] = float(i * M_PI / 180);
		g_sinTable[i] = _sin(g_radTable[i]);
		g_cosTable[i] = _cos(g_radTable[i]);
		g_radTable[i + 361] = -g_radTable[i];
		g_sinTable[i + 361] = -g_sinTable[i];
		g_cosTable[i + 361] = -g_cosTable[i];
	}
}


hook_func<float (__cdecl *)(int degree)> _GetRadian(SAKEXE, "GetRadian");
float __cdecl GetRadian(int degree) // line 742-750
{
	return (_GetRadian)(degree);

	if( degree > 360 || degree < -360 )
		degree = degree % 360;

	if( degree < 0 )
		degree = degree + 361;

	return g_radTable[degree];
}


hook_func<float (__cdecl *)(int degree)> _GetSin(SAKEXE, "GetSin");
float __cdecl GetSin(int degree) // line 753-761
{
	return (_GetSin)(degree);

	if( degree > 360 || degree < -360 )
		degree = degree % 360;

	if( degree < 0 )
		degree = degree + 361;

	return g_sinTable[degree];
}


hook_func<float (__cdecl *)(int degree)> _GetCos(SAKEXE, "GetCos");
float __cdecl GetCos(int degree) // line 764-772
{
	return (_GetCos)(degree);

	if( degree > 360 || degree < -360 )
		degree = degree % 360;

	if( degree < 0 )
		degree = degree + 361;

	return g_cosTable[degree];
}


hook_func<int (__cdecl *)(const ray3d& ray, const C3dOBB& obb)> _CheckRayOBBIntersect(SAKEXE, "CheckRayOBBIntersect");
int __cdecl CheckRayOBBIntersect(const ray3d& ray, const C3dOBB& obb) // line 776-841
{
	return (_CheckRayOBBIntersect)(ray, obb);

	//TODO
}


BOOL __cdecl CheckRayTriIntersect(const ray3d& ray, const vector3d& v0, const vector3d& v1, const vector3d& v2, float* u, float* v, float* t) // line 844-865
{
	vector3d e1;
	e1.x = v1.x - v0.x;
	e1.y = v1.y - v0.y;
	e1.z = v1.z - v0.z;

	vector3d e2;
	e2.x = v2.x - v0.x;
	e2.y = v2.y - v0.y;
	e2.z = v2.z - v0.z;

	double detx = e2.y * ray.dir.x - e2.x * ray.dir.y;
	double dety = e2.z * ray.dir.y - e2.y * ray.dir.z;
	double detz = e2.x * ray.dir.z - e2.z * ray.dir.x;

	double det = detx * e1.z + detz * e1.y + dety * e1.x;
	if( det > -epsilon && det < epsilon )
		return FALSE;

	float inv_det = float(1.0 / det);

	vector3d s;
	s.x = ray.org.x - v0.x;
	s.y = ray.org.y - v0.y;
	s.z = ray.org.z - v0.z;

	*u = float((s.z * detx + s.y * detz + s.x * dety) * inv_det);
	if( *u < 0.0 || *u > 1.0 )
		return FALSE;

	vector3d q;
	q.x = s.y * e1.z - s.z * e1.y;
	q.y = s.z * e1.x - s.x * e1.z;
	q.z = s.x * e1.y - s.y * e1.x;

	*v = float((q.z * ray.dir.z + q.y * ray.dir.y + q.x * ray.dir.x) * inv_det);
	if( *v < 0.0 || *v + *u > 1.0 )
		return FALSE;

	*t = float((q.z * e2.z + q.y * e2.y + q.x * e2.x) * inv_det);
	return TRUE;
}


hook_func<int (__cdecl *)(const lineSegment3d& ray, const C3dOBB& obb)> _CheckLineSegmentOBBIntersect(SAKEXE, "CheckLineSegmentOBBIntersect");
int __cdecl CheckLineSegmentOBBIntersect(const lineSegment3d& ray, const C3dOBB& obb) // line 869-942
{
	return (_CheckLineSegmentOBBIntersect)(ray, obb);

	//TODO
}


hook_func<int (__cdecl *)(const lineSegment3d& ray, const vector3d& v0, const vector3d& v1, const vector3d& v2, float* u, float* v, float* t)> _CheckLineSegmentTriIntersect(SAKEXE, "CheckLineSegmentTriIntersect");
int __cdecl CheckLineSegmentTriIntersect(const lineSegment3d& ray, const vector3d& v0, const vector3d& v1, const vector3d& v2, float* u, float* v, float* t) // line 945-970
{
	return (_CheckLineSegmentTriIntersect)(ray, v0, v1, v2, u, v, t);

	//TODO
}


hook_func<float (__cdecl *)(const ray3d& ray, const vector3d& Vert)> _SquaredVertRayDist(SAKEXE, "SquaredVertRayDist");
float __cdecl SquaredVertRayDist(const ray3d& ray, const vector3d& Vert) // line 973-981
{
	return (_SquaredVertRayDist)(ray, Vert);

	//TODO
}


////////////////////////////////////////
