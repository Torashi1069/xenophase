#pragma once
#include "Struct.h"
#include "3dLib/Prim.h" // vector3d
#include "Base/Res.h"
struct SceneGraphNode;


class C3dWorldRes : public CRes
{
public:
	struct vtable_t
	{
		void* (C3dWorldRes::* scalar_deleting_destructor)(unsigned int flags);
		bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (C3dWorldRes::* Clone)(void) const;
		bool (C3dWorldRes::* Load)(const char* fName);
		void (C3dWorldRes::* Reset)(void);
		void (CRes::* OnLoadError)(const char* fName);
	};

	struct actorInfo
	{
		/* this+  0 */ char name[40];
		/* this+ 40 */ char modelName[80];
		/* this+120 */ char nodeName[80];
		/* this+200 */ vector3d pos;
		/* this+212 */ vector3d rot;
		/* this+224 */ vector3d scale;
		/* this+236 */ int animType;
		/* this+240 */ int blockType;
		/* this+244 */ float animSpeed;
		/* this+248 */ float posx;
		/* this+252 */ float posy;
		/* this+256 */ float posz;
	};

	struct lightSrcInfo
	{
		/* this+  0 */ char name[80];
		/* this+ 80 */ vector3d pos;
		/* this+ 92 */ int red;
		/* this+ 96 */ int green;
		/* this+100 */ int blue;
		/* this+104 */ float range;
	};

	struct effectSrcInfo
	{
		/* this+  0 */ char name[80];
		/* this+ 80 */ vector3d pos;
		/* this+ 92 */ int type;
		/* this+ 96 */ float emitSpeed;
		/* this+100 */ float param[4];
	};

	struct soundSrcInfo_V19
	{
		/* this + 0 */ char name[80];
		/* this+ 80 */ char waveName[80];
		/* this+160 */ vector3d pos;
		/* this+172 */ float vol;
		/* this+176 */ int width;
		/* this+180 */ int height;
		/* this+184 */ float range;
	};

	struct soundSrcInfo
	{
		/* this+  0 */ char name[80];
		/* this+ 80 */ char waveName[80];
		/* this+160 */ vector3d pos;
		/* this+172 */ float vol;
		/* this+176 */ int width;
		/* this+180 */ int height;
		/* this+184 */ float range;
		/* this+188 */ float cycle;
	};

	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ public: mystd::list<C3dWorldRes::actorInfo*> m_3dActors;
	/* this+284 */ public: mystd::list<C3dWorldRes::effectSrcInfo*> m_particles;
	/* this+296 */ public: mystd::list<C3dWorldRes::soundSrcInfo*> m_sounds;
	/* this+308 */ public: SceneGraphNode* m_CalculatedNode;
	/* this+312 */ public: mystd::string m_gndFile;
	/* this+328 */ public: mystd::string m_attrFile;
	/* this+344 */ public: mystd::string m_scrFile;
	/* this+360 */ public: float m_waterLevel;
	/* this+364 */ public: int m_waterType;
	/* this+368 */ public: float m_waveHeight;
	/* this+372 */ public: float m_waveSpeed;
	/* this+376 */ public: float m_wavePitch;
	/* this+380 */ public: int m_waterAnimSpeed;
	/* this+384 */ public: int m_lightLongitude;
	/* this+388 */ public: int m_lightLatitude;
	/* this+392 */ public: vector3d m_lightDir;
	/* this+404 */ public: vector3d m_diffuseCol;
	/* this+416 */ public: vector3d m_ambientCol;
	/* this+428 */ public: unsigned char m_verMajor;
	/* this+429 */ public: unsigned char m_verMinor;
	/* this+432 */ public: int m_groundTop;
	/* this+436 */ public: int m_groundBottom;
	/* this+440 */ public: int m_groundLeft;
	/* this+444 */ public: int m_groundRight;

	public: C3dWorldRes::C3dWorldRes(Exemplar __formal, const char* resid, const char* baseDir);
	public: C3dWorldRes::C3dWorldRes(void);
	public: virtual CRes* C3dWorldRes::Clone(void) const;
	public: virtual void C3dWorldRes::Reset(void);
	public: virtual bool C3dWorldRes::Load(const char* fName);

private:
	static hook_method<CRes* (C3dWorldRes::*)(void) const> C3dWorldRes::_Clone;
	static hook_method<void (C3dWorldRes::*)(void)> C3dWorldRes::_Reset;
	static hook_method<bool (C3dWorldRes::*)(const char* fName)> C3dWorldRes::_Load;
};
