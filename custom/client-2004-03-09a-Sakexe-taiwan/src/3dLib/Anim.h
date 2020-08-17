#pragma once
struct matrix; // 3dLib/Prim.h


struct posKeyframe
{
	/* this+ 0 */ int frame;
	/* this+ 4 */ float px;
	/* this+ 8 */ float py;
	/* this+12 */ float pz;

	//public: void posKeyframe();
	public: posKeyframe::posKeyframe(int frame, float px, float py, float pz);
	public: void posKeyframe::Slerp(float t, posKeyframe& start, posKeyframe& end);
};


struct rotKeyframe
{
	/* this+ 0 */ int frame;
	/* this+ 4 */ float qx;
	/* this+ 8 */ float qy;
	/* this+12 */ float qz;
	/* this+16 */ float qw;

	//public: void rotKeyframe();
	public: rotKeyframe::rotKeyframe(int frame, float qx, float qy, float qz, float qw);
	public: void rotKeyframe::Slerp(float t, rotKeyframe& start, rotKeyframe& end, int spin);
};


struct scaleKeyframe
{
	/* this+ 0 */ int frame;
	/* this+ 4 */ float sx;
	/* this+ 8 */ float sy;
	/* this+12 */ float sz;
	/* this+16 */ float qx;
	/* this+20 */ float qy;
	/* this+24 */ float qz;
	/* this+28 */ float qw;

	//public: void scaleKeyframe();
	public: scaleKeyframe::scaleKeyframe(int frame, float sx, float sy, float sz, float qx, float qy, float qz, float qw);
	public: void scaleKeyframe::Slerp(float t, scaleKeyframe& start, scaleKeyframe& end, int spin);
};


class C3dPosAnim
{
	/* this+0 */ private: mystd::vector<posKeyframe> m_animdata;

	//public: void C3dPosAnim::AddKey(int, float, float, float); // line 86 (Anim.cpp)
	//public: void C3dPosAnim::ReleaseAllKeys();
	public: void C3dPosAnim::GetMatrix(int frame, matrix& result);
	//public: void C3dPosAnim::Load(class CFile *);
	//public: int Size();

private:
	static hook_method<void (C3dPosAnim::*)(int frame, matrix& result)> C3dPosAnim::_GetMatrix;
};


class C3dRotAnim
{
	/* this+0 */ private: mystd::vector<rotKeyframe> m_animdata;

	//public: void C3dRotAnim::AddKey(int, float, float, float, float); // line 142 (Anim.cpp)
	//public: void C3dRotAnim::ReleaseAllKeys();
	public: void C3dRotAnim::GetMatrix(int frame, matrix& result);
	//public: void C3dRotAnim::Load(class CFile *);
	//public: int Size();

private:
	static hook_method<void (C3dRotAnim::*)(int frame, matrix& result)> C3dRotAnim::_GetMatrix;
};


class C3dScaleAnim
{
	/* this+0 */ private: mystd::vector<scaleKeyframe> m_animdata;

	//public: void C3dScaleAnim::AddKey(int, float, float, float, float, float, float, float); // line 193 (Anim.cpp)
	//public: void C3dScaleAnim::ReleaseAllKeys();
	public: void C3dScaleAnim::GetMatrix(int frame, matrix& result);
	//public: void C3dScaleAnim::Load(class CFile *);
	//public: int Size();

private:
	static hook_method<void (C3dScaleAnim::*)(int frame, matrix& result)> C3dScaleAnim::_GetMatrix;
};
