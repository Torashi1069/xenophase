#pragma once
#include "granny.h"
#include "Struct.h"
#include "3dLib/Anim.h"
#include "3dLib/Mesh.h"
#include "3dLib/Prim.h"
#include "3dLib/Texture.h"
#include "Base/Res.h"
class C3dGrannyBoneRes;
class C3dGrannyModelRes;


struct MaterialInfo
{
	/* this+  0 */ char name[128];
	/* this+128 */ int numSubMtls;
	/* this+132 */ mystd::string* subMaterials;

	//MaterialInfo(void);
	MaterialInfo::~MaterialInfo(void) { delete[] this->subMaterials; } // line 58
};


struct CVolumeBox
{
	/* this+  0 */ vector3d m_size;
	/* this+ 12 */ vector3d m_pos;
	/* this+ 24 */ vector3d m_rot;
	/* this+ 36 */ vector3d m_worldVert[8];
	/* this+132 */ matrix m_vtm;
	/* this+180 */ matrix m_ivtm;
	/* this+228 */ int flag;
};


struct C3dNodeRes
{
	/* this+  0 */ char name[128];
	/* this+128 */ char parentname[128];
	/* this+256 */ class C3dModelRes* scene;
	/* this+260 */ C3dNodeRes* parent;
	/* this+264 */ mystd::list<C3dNodeRes*> child;
	/* this+276 */ C3dMesh* mesh;
	/* this+280 */ int numTexture;
	/* this+284 */ CTexture** texture;
	/* this+288 */ float pos[3];
	/* this+300 */ float rotaxis[3];
	/* this+312 */ float rotangle;
	/* this+316 */ float scale[3];
	/* this+328 */ unsigned char alpha;
	/* this+332 */ C3dPosAnim posanim;
	/* this+348 */ C3dRotAnim rotanim;

	public: C3dNodeRes::C3dNodeRes(void);
	public: C3dNodeRes::~C3dNodeRes(void);
	public: void C3dNodeRes::Release(void);

private:
	static hook_method<void (C3dNodeRes::*)(void)> C3dNodeRes::_Release;
};


class C3dModelRes : public CRes
{
	struct vtable_t
	{
		void* (C3dModelRes::* scalar_deleting_destructor)(unsigned int flags);
		bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (C3dModelRes::* Clone)(void) const;
		bool (C3dModelRes::* Load)(const char* fName);
		void (C3dModelRes::* Reset)(void);
		void (CRes::* OnLoadError)(const char* fName);
	};

	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ private: int m_numMaterials;
	/* this+276 */ private: MaterialInfo* m_material;
	/* this+280 */ private: mystd::list<C3dNodeRes*> m_objectList;
	/* this+292 */ private: mystd::list<mystd::string> m_rootObjList;
	/* this+304 */ private: mystd::map<mystd::string,C3dMesh*> m_meshList;
	/* this+320 */ public: char name[80];
	/* this+400 */ public: int m_shadeType;
	/* this+404 */ public: int m_animLen;
	/* this+408 */ public: mystd::list<CVolumeBox*> m_volumeBoxList;
	/* this+420 */ public: unsigned char m_alpha;

	public: C3dModelRes::C3dModelRes(Exemplar __formal, const char* resid, const char* baseDir);
	public: C3dModelRes::C3dModelRes(void);
	public: virtual CRes* C3dModelRes::Clone(void) const;
	public: virtual bool C3dModelRes::Load(const char* fName);
	public: virtual void C3dModelRes::Reset(void);
	public: C3dNodeRes* C3dModelRes::FindNode(const char* name);
	public: C3dNodeRes* C3dModelRes::GetFirstNode(void);
	//public: const char* GetMaterialName(int, int);
	//public: const char* GetMaterialName(int);
	//public: int GetSubMtlCount(int);
	//public: C3dMesh* GetMesh(const mystd::string&);

private:
	static hook_method<CRes* (C3dModelRes::*)(void) const> C3dModelRes::_Clone;
	static hook_method<bool (C3dModelRes::*)(const char* fName)> C3dModelRes::_Load;
	static hook_method<void (C3dModelRes::*)(void)> C3dModelRes::_Reset;
	static hook_method<C3dNodeRes* (C3dModelRes::*)(const char* name)> C3dModelRes::_FindNode;
	static hook_method<C3dNodeRes* (C3dModelRes::*)(void)> C3dModelRes::_GetFirstNode;
};


class C3dGrannyModelRes : public CRes
{
public:
	//C3dGrannyModelRes(class Exemplar, const char *, const char *);
	//C3dGrannyModelRes();
	//~C3dGrannyModelRes();
	//class CRes * Clone();
	//void Release();
	//void Reset();
	//unsigned char Load(const char *);
	granny_control* ActAnimation(int idx, granny_model_instance* instance, granny_control* control, int nLoop);
	void DeActAnimation(granny_control* control);
	granny_world_pose* UpdateAni(float GameClock, struct granny_model_instance* instance);
	//void * RenderMesh(int, int *, int *, int *, struct matrix *, struct granny_world_pose *);
	//void * GetRigidMesh(int);
	//unsigned char CalculateHitArea(struct RENDER_INFO_RECT &, struct matrix &, struct matrix &, struct vector3d &);
	int GetMeshNo();
	//struct granny_mesh_binding * GetMeshBinding(int);
	int GetMeshIndexCount(int nMeshNo);
	//void SetHairInfo(struct HairInfo *);
	//unsigned char SetHairAndHeadMesh();
	void SetHitRad(float HitRadx, float HitRady);
	//unsigned char IsAnimationFinished(struct granny_control *);
	granny_model* GetModel(); // @custom
	//granny_model_instance* GetModelInstance();
	//void SetMatVer(struct granny_pnt332_vertex *);
	//void * GetWorldMatrix(struct matrix *, struct granny_world_pose *);
	//void BindMeshToSkeleton(class C3dGrannyModelRes *);
	//struct granny_skeleton * GetSkeleton();

protected:
	//void GrannyError(enum granny_log_message_type, enum granny_log_message_origin, const char *, void *);
	//void CreateTexture(struct GrannyTexture *, struct granny_texture *);
	//class CTexture * CreateRGBATexture(struct granny_texture *, int);
	//void CreateModel(struct GrannyModel *, struct granny_model *);
	//void CreateMesh(struct GrannyMesh *, struct granny_mesh *, struct granny_model_instance *);
	//void * RenderModel(struct GrannyModel *, int, int *, int *, int *, struct matrix *, struct granny_world_pose *);
	//void SetProjectZ(float);
	//struct GrannyTexture * FindTexture(struct granny_material *);
	//struct granny_file * LoadFile(const char *, const char *);

protected:
	/* this+  0 */ //CRes baseclass_0;
	/* this+272 */ float m_ProjectZ;
	/* this+276 */ GrannyScene m_Scene;
	/* this+912 */ granny_model* m_pModel;
	/* this+916 */ vector3d m_HitareaPos;
	/* this+928 */ float m_HitRadx;
	/* this+932 */ float m_HitRady;
	/* this+936 */ C3dGrannyBoneRes* m_pBoneRes;
	/* this+940 */ int m_nBoneType;
private:
	/* this+944 */ struct HairInfo* m_hair;
	/* this+948 */ granny_skeleton* m_pSkeleton;

private:
	static hook_func<granny_control* (C3dGrannyModelRes::*)(int idx, granny_model_instance* instance, granny_control* control, int nLoop)> C3dGrannyModelRes::_ActAnimation;
};


class C3dGrannyBoneRes
{
	/* this+  0 */ protected: float m_ProjectZ;
	/* this+  4 */ protected: GrannyScene m_Scene;
	/* this+640 */ protected: granny_animation* m_Animation[100][20];

	//public: void C3dGrannyBoneRes::C3dGrannyBoneRes();
	//public: void C3dGrannyBoneRes::~C3dGrannyBoneRes();
	public: void C3dGrannyBoneRes::Init(void);
	//public: void C3dGrannyBoneRes::FreeModel();
	//public: void C3dGrannyBoneRes::Release();
	//public: void Reset();
	//public: unsigned char C3dGrannyBoneRes::AddBone(const char *, int, int);
	//public: struct granny_animation * C3dGrannyBoneRes::GetAnimation(int, int);
	//public: void UpdateAni(float);
	//public: int GetMeshNo();
	//protected: void GrannyError(enum granny_log_message_type, enum granny_log_message_origin, const char *, void *);
	//protected: void C3dGrannyBoneRes::CreateModel(struct GrannyModel *, struct granny_model *);
	//protected: void C3dGrannyBoneRes::CreateMesh(struct GrannyMesh *, struct granny_mesh *, struct granny_model_instance *);
	//protected: void C3dGrannyBoneRes::SetProjectZ(float);
	//protected: struct granny_animation * C3dGrannyBoneRes::LoadAnimation(struct GrannyModel *, const char *, const char *);
	//protected: struct granny_file * C3dGrannyBoneRes::LoadFile(const char *, const char *);

private:
	static hook_method<void (C3dGrannyBoneRes::*)(void)> C3dGrannyBoneRes::_Init;
};
