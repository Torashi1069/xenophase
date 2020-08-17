#include "3dLib/Anim.h"
#include "3dLib/Prim.h"
#include <math.h>
const float pi = 3.141592f;
const float EPSILON = 0.000001f;
////////////////////////////////////////


posKeyframe::posKeyframe(int frame, float px, float py, float pz) // line ?
{
	this->frame = frame;
	this->px = px;
	this->py = py;
	this->pz = pz;
}


void posKeyframe::Slerp(float t, posKeyframe& start, posKeyframe& end) // line 8-13
{
    double s = 1.0 - t;
    this->px = float(s * start.px + t * end.px);
    this->py = float(s * start.py + t * end.py);
    this->pz = float(s * start.pz + t * end.pz);
}


////////////////////////////////////////


rotKeyframe::rotKeyframe(int frame, float qx, float qy, float qz, float qw) // line ??
{
	this->frame = frame;
	this->qx = qx;
	this->qy = qy;
	this->qz = qz;
	this->qw = qw;
}


void rotKeyframe::Slerp(float t, rotKeyframe& start, rotKeyframe& end, int spin) // line 16-46
{
	float theta = start.qx * end.qx + start.qy * end.qy + start.qz * end.qz + end.qw * start.qw;
	bool bflip = false;
	if( theta < 0.0 )
	{
		theta = -theta;
		bflip = true;
	}

	double m, n;
	if( 1.0f - theta >= EPSILON )
	{
		float phi = acos(theta);
		float beta = (spin * pi + phi) * t;
		m = _sin(phi - beta) / _sin(phi);
		n = _sin(beta) / _sin(phi);
	}
	else
	{
		m = 1.0 - t;
		n = t;
	}

	if( bflip )
		n = -n;

	this->qx = float(m * start.qx + n * end.qx);
	this->qy = float(m * start.qy + n * end.qy);
	this->qz = float(m * start.qz + n * end.qz);
	this->qw = float(m * start.qw + n * end.qw);
}


////////////////////////////////////////


scaleKeyframe::scaleKeyframe(int frame, float sx, float sy, float sz, float qx, float qy, float qz, float qw)
{
	this->frame = frame;
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
	this->qx = qx;
	this->qy = qy;
	this->qz = qz;
	this->qw = qw;
}


void scaleKeyframe::Slerp(float t, scaleKeyframe& start, scaleKeyframe& end, int spin) // line 49-83
{
	double s = 1.0 - t;
	this->sx = float(s * start.sx + t * end.sx);
	this->sy = float(s * start.sy + t * end.sy);
	this->sz = float(s * start.sz + t * end.sz);

	float theta = start.qz * end.qz + start.qy * end.qy + start.qx * end.qx + end.qw * start.qw;
	bool bflip = false;
	if( theta < 0.0 )
	{
		theta = -theta;
		bflip = true;
	}

	double m, n;
	if( 1.0f - theta >= EPSILON )
	{
		float phi = acos(theta);
		float beta = (spin * pi + phi) * t;
		m = _sin(phi - beta) / _sin(phi);
		n = _sin(beta) / _sin(phi);
	}
	else
	{
		m = 1.0 - t;
		n = t;
	}

	if( bflip )
		n = -n;

	this->qx = float(m * start.qx + n * end.qx);
	this->qy = float(m * start.qy + n * end.qy);
	this->qz = float(m * start.qz + n * end.qz);
	this->qw = float(m * start.qw + n * end.qw);
}


////////////////////////////////////////


hook_method<void (C3dPosAnim::*)(int frame, matrix& result)> C3dPosAnim::_GetMatrix(SAKEXE, "C3dPosAnim::GetMatrix");
void C3dPosAnim::GetMatrix(int frame, matrix& result) // line 96-118
{
	return (this->*_GetMatrix)(frame, result);

	//TODO
}


////////////////////////////////////////


hook_method<void (C3dRotAnim::*)(int frame, matrix& result)> C3dRotAnim::_GetMatrix(SAKEXE, "C3dRotAnim::GetMatrix");
void C3dRotAnim::GetMatrix(int frame, matrix& result)
{
	return (this->*_GetMatrix)(frame, result);

	//TODO
}


////////////////////////////////////////


hook_method<void (C3dScaleAnim::*)(int frame, matrix& result)> C3dScaleAnim::_GetMatrix(SAKEXE, "C3dScaleAnim::GetMatrix");
void C3dScaleAnim::GetMatrix(int frame, matrix& result)
{
	return (this->*_GetMatrix)(frame, result);

	//TODO
}


////////////////////////////////////////
