#include "Globals.h"
#include "Base/ResMgr.h"
#include "Resource/Model.h"
////////////////////////////////////////


C3dNodeRes::C3dNodeRes(void) // line 12
{
	memset(this->parentname, 0, sizeof(this->parentname));
	this->parent = NULL;
	this->texture = NULL;
	this->mesh = NULL;
	this->numTexture = 0;
}


C3dNodeRes::~C3dNodeRes(void) // line 21
{
	this->C3dNodeRes::Release();
}


hook_method<void (C3dNodeRes::*)(void)> C3dNodeRes::_Release(SAKEXE, "C3dNodeRes::Release");
void C3dNodeRes::Release(void) // line 26
{
	return (this->*_Release)();

	if( this->texture != NULL )
	{
		for( int i = 0; i < this->numTexture; ++i )
		{
			this->texture[i]->CTexture::Unlock();
			g_texMgr.CTexMgr::DestroyTexture(this->texture[i]);
		}

		delete this->texture;
		this->texture = NULL;
	}

	if( this->mesh != NULL )
	{
		delete this->mesh;
		this->mesh = NULL;
	}

	this->child.clear();
}


////////////////////////////////////////


C3dModelRes::C3dModelRes(Exemplar __formal, const char* resid, const char* baseDir) // line 67 (Resource/Model.h)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


C3dModelRes::C3dModelRes(void) // line 46
{
	m_numMaterials = 0;
	m_material = NULL;
}


hook_method<CRes* (C3dModelRes::*)(void) const> C3dModelRes::_Clone(SAKEXE, "C3dModelRes::Clone");
CRes* C3dModelRes::Clone(void) const // line 64 (Resource/Model.h)
{
	return (this->*_Clone)();

	return new C3dModelRes();
}


hook_method<void (C3dModelRes::*)(void)> C3dModelRes::_Reset(SAKEXE, "C3dModelRes::Reset");
void C3dModelRes::Reset(void) // line 52
{
	return (this->*_Reset)();

	if( m_material != NULL )
	{
		delete[] m_material;
		m_material = NULL;
		m_numMaterials = 0;
	}

	for( mystd::list<C3dNodeRes*>::iterator it = m_objectList.begin(); it != m_objectList.end(); ++it )
		delete *it;

	m_objectList.clear();

	m_rootObjList.clear();

	m_meshList.clear();

	for( mystd::list<CVolumeBox*>::iterator it = m_volumeBoxList.begin(); it != m_volumeBoxList.end(); ++it )
		delete *it;

	m_volumeBoxList.clear();
}


hook_method<bool (C3dModelRes::*)(const char* fName)> C3dModelRes::_Load(SAKEXE, "C3dModelRes::Load");
bool C3dModelRes::Load(const char* fName) // line 76
{
	return (this->*_Load)(fName);

	//TODO
}


hook_method<C3dNodeRes* (C3dModelRes::*)(const char* name)> C3dModelRes::_FindNode(SAKEXE, "C3dModelRes::FindNode");
C3dNodeRes* C3dModelRes::FindNode(const char* name) // line 296
{
	return (this->*_FindNode)(name);

	for( mystd::list<C3dNodeRes*>::iterator it = m_objectList.begin(); it != m_objectList.end(); ++it )
		if( strcmp((*it)->name, name) == 0 )
			return *it;

	return NULL;
}


//hook_method<C3dNodeRes* (C3dModelRes::*)(void)> C3dModelRes::_GetFirstNode(SAKEXE, "C3dModelRes::GetFirstNode");
C3dNodeRes* C3dModelRes::GetFirstNode(void) // line ???
{
//	return (this->*_GetFirstNode)();

	return m_objectList.front();
}


class hook_ptr<struct mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,class C3dMesh *>,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,class C3dMesh *,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class C3dMesh *> >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class C3dMesh *> >::_Node *> mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,class C3dMesh *>,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,class C3dMesh *,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class C3dMesh *> >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class C3dMesh *> >::_Nil(SAKEXE, "?_Nil@?$_Tree@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAVC3dMesh@@@2@U_Kfn@?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAVC3dMe50b2dfff");
class hook_val<unsigned int> mystd::_Tree<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::pair<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > const ,class C3dMesh *>,struct mystd::map<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,class C3dMesh *,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class C3dMesh *> >::_Kfn,struct mystd::less<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,class mystd::allocator<class C3dMesh *> >::_Nilrefs(SAKEXE, "?_Nilrefs@?$_Tree@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$pair@$$CBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAVC3dMesh@@@2@U_Kfn@?$map@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PAVC5aefcb9a");


////////////////////////////////////////


hook_method<void (C3dGrannyBoneRes::*)(void)> C3dGrannyBoneRes::_Init(SAKEXE, "C3dGrannyBoneRes::Init");
void C3dGrannyBoneRes::Init(void) // line 1346
{
	return (this->*_Init)();

	;
}


////////////////////////////////////////


hook_func<granny_control* (C3dGrannyModelRes::*)(int idx, granny_model_instance* instance, granny_control* control, int nLoop)> C3dGrannyModelRes::_ActAnimation(SAKEXE, "C3dGrannyModelRes::ActAnimation");
granny_control* C3dGrannyModelRes::ActAnimation(int idx, granny_model_instance* instance, granny_control* control, int nLoop) // line 873-886
{
	return (this->*_ActAnimation)(idx, instance, control, nLoop);

	//TODO
}


void C3dGrannyModelRes::DeActAnimation(granny_control* control)
{
	if( control != NULL )
	{
		GrannySetControlActive(control, 0);
		GrannyFreeControl(control);
	}
}


granny_world_pose* C3dGrannyModelRes::UpdateAni(float GameClock, struct granny_model_instance* instance) // line 1109-1125
{
	GrannyModel* Model = m_Scene.Model;
	if( Model == NULL )
		return NULL;

	granny_skeleton* skeleton = GrannyGetSourceSkeleton(instance);
	GrannySetModelClock(instance, GameClock);
	GrannySampleModelAnimations(instance, 0, skeleton->BoneCount, m_Scene.SharedLocalPose);
	GrannyBuildWorldPose(skeleton, 0, skeleton->BoneCount, m_Scene.SharedLocalPose, 0, Model->WorldPose);
	GrannyFreeCompletedModelControls(instance);

	return Model->WorldPose;
}


int C3dGrannyModelRes::GetMeshNo() // @guessed
{
	return m_Scene.Model->MeshCount;
}


int C3dGrannyModelRes::GetMeshIndexCount(int nMeshNo) // line 1309-1311
{
	return GrannyGetMeshIndexCount(m_Scene.Model->Meshes[nMeshNo].Mesh) / 3;
}


void C3dGrannyModelRes::SetHitRad(float HitRadx, float HitRady)
{
	m_HitRadx = HitRadx;
	m_HitRady = HitRady;
}


granny_model* C3dGrannyModelRes::GetModel() // @guessed
{
	return m_pModel;
}


////////////////////////////////////////
