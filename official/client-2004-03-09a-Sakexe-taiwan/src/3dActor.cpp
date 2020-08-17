#include "3dActor.h"
#include "GameWorld.h" // CRayPicker
#include "Resource/Model.h" // CVolumeBox
const float pi = 3.141592f;


C3dNode::C3dNode(void) // line 22-29
: m_parent(NULL),
  m_master(NULL),
  m_numTexture(0),
  m_mesh(NULL),
  m_isAlphaForPlayer(0)
{
	m_opacity = 1.0;
}


C3dNode::~C3dNode(void) // line 32-34
{
	for( mystd::list<C3dNode*>::iterator it = m_child.begin(); it != m_child.end(); ++it )
		delete *it;
}


hook_method<void (C3dNode::*)(void)> C3dNode::_Reset(SAKEXE, "C3dNode::Reset");
void C3dNode::Reset(void) // line 37-48
{
	return (this->*_Reset)();

	for( mystd::list<C3dNode*>::iterator it = m_child.begin(); it != m_child.end(); ++it )
		delete *it;

	m_child.clear();
	m_texture.clear();
	m_colorInfo.clear();
	m_destVertCol.clear();
}


hook_method<void (C3dNode::*)(int framepos)> C3dNode::_SetFrame(SAKEXE, "C3dNode::SetFrame");
void C3dNode::SetFrame(int framepos) // line 51-67
{
	return (this->*_SetFrame)(framepos);

	matrix posTM, rotTM, scaleTM;
	m_posAnim.C3dPosAnim::GetMatrix(framepos, posTM);
	m_rotAnim.C3dRotAnim::GetMatrix(framepos, rotTM);
	m_scaleAnim.C3dScaleAnim::GetMatrix(framepos, scaleTM);
	
	matrix tmp;
	tmp.matrix::MultMatrix(scaleTM, rotTM);
	m_ltm.matrix::MultMatrix(tmp, posTM);

	for( mystd::list<C3dNode*>::iterator it = m_child.begin(); it != m_child.end(); ++it )
		(*it)->C3dNode::SetFrame(framepos);
}


hook_method<void (C3dNode::*)(const matrix& ptm, int flipNormal, bool clip)> C3dNode::_Render(SAKEXE, "C3dNode::Render");
void C3dNode::Render(const matrix& ptm, int flipNormal, bool clip) // line 71-232
{
	return (this->*_Render)(ptm, flipNormal, clip);

	//TODO
}


hook_method<void (C3dNode::*)(C3dNodeRes* modelNode)> C3dNode::_AssignModel(SAKEXE, "C3dNode::AssignModel");
void C3dNode::AssignModel(C3dNodeRes* modelNode) // line 235-274
{
	return (this->*_AssignModel)(modelNode);

	//TODO
}


hook_method<void (C3dNode::*)(const matrix& ptm, const vector3d& light, const vector3d& diffuseCol, const vector3d& ambientCol, int shadeType)> C3dNode::_UpdateVertexColor(SAKEXE, "C3dNode::UpdateVertexColor");
void C3dNode::UpdateVertexColor(const matrix& ptm, const vector3d& light, const vector3d& diffuseCol, const vector3d& ambientCol, int shadeType) // line 392-486
{
	return (this->*_UpdateVertexColor)(ptm, light, diffuseCol, ambientCol, shadeType);

	//TODO
}


hook_method<void (C3dNode::*)(C3dAABB* box, const matrix& ptm)> C3dNode::_UpdateBound(SAKEXE, "C3dNode::UpdateBound");
void C3dNode::UpdateBound(C3dAABB* box, const matrix& ptm) // line 277-306
{
	return (this->*_UpdateBound)(box, ptm);

	//TODO
}


hook_method<void (C3dNode::*)(const matrix& ptm, const matrix& wtm)> C3dNode::_UpdateAABB(SAKEXE, "C3dNode::UpdateAABB");
void C3dNode::UpdateAABB(const matrix& ptm, const matrix& wtm) // line 309-367
{
	return (this->*_UpdateAABB)(ptm, wtm);

	//TODO
}


hook_method<void (C3dNode::*)(const CRayPicker& rayPicker)> C3dNode::_CheckAABB(SAKEXE, "C3dNode::CheckAABB");
void C3dNode::CheckAABB(const CRayPicker& rayPicker) // line 380-387
{
	return (this->*_CheckAABB)(rayPicker);

	m_isAlphaForPlayer = rayPicker.CRayPicker::CheckAABBIntersect(m_aabb);
	for( mystd::list<C3dNode*>::iterator it = m_child.begin(); it != m_child.end(); ++it )
		(*it)->C3dNode::CheckAABB(rayPicker);
}


hook_method<void (C3dNode::*)(CRenderer* renderer, const matrix& nodeTM, C3dGround15* pGround)> C3dNode::_UpdateDestVertColor(SAKEXE, "C3dNode::UpdateDestVertColor");
void C3dNode::UpdateDestVertColor(CRenderer* renderer, const matrix& nodeTM, C3dGround15* pGround) // line 519-555
{
	return (this->*_UpdateDestVertColor)(renderer, nodeTM, pGround);

	//TODO
}


hook_method<C3dNode* (C3dNode::*)(const char* name)> C3dNode::_FindNode(SAKEXE, "C3dNode::FindNode");
C3dNode* C3dNode::FindNode(const char* name) // line 558-570
{
	return (this->*_FindNode)(name);

	if( strcmp(m_name, name) == 0 )
		return this; // match.

	for( mystd::list<C3dNode*>::iterator it = m_child.begin(); it != m_child.end(); ++it )
	{
		C3dNode* node = (*it)->C3dNode::FindNode(name);
		if( node != NULL )
			return node; // found.
	}

	return NULL; // not found.
}


hook_method<void (C3dNode::*)(void)> C3dNode::_SetToAlpha(SAKEXE, "C3dNode::SetToAlpha");
void C3dNode::SetToAlpha(void) // line 370-377
{
	return (this->*_SetToAlpha)();

	m_isAlphaForPlayer = 1;
	for( mystd::list<C3dNode*>::iterator it = m_child.begin(); it != m_child.end(); ++it )
		(*it)->C3dNode::SetToAlpha();
}


////////////////////////////////////////


C3dActor::C3dActor(void) // line 575-593
: m_pos(0., 0., 0.),
  m_rot(0., 0., 0.),
  m_scale(1., 1., 1.),
  m_shadeType(0),
  m_node(0),
  m_curMotion(0),
  m_animType(2),
  m_animSpeed(0.),
  m_animLen(0),
  m_renderSignature(0),
  m_isMatrixNeedUpdate(1),
  m_isBbNeedUpdate(1),
  m_posOffset(0., 0., 0.),
  m_isHalfAlpha(0),
  m_fadeAlphaCnt(-1)
{
}


C3dActor::~C3dActor(void) // line 596-598
{
	this->C3dActor::Reset();
}


hook_method<void (C3dActor::*)(void)> C3dActor::_Reset(SAKEXE, "C3dActor::Reset");
void C3dActor::Reset(void) // line 601-612
{
	return (this->*_Reset)();

	if( m_node != NULL )
	{
		delete m_node;
		m_node = NULL;
	}

	for( mystd::list<CVolumeBox*>::iterator it = m_volumeBoxList.begin(); it != m_volumeBoxList.end(); ++it )
		delete *it;

	m_volumeBoxList.clear();
}


hook_method<void (C3dActor::*)(int framepos)> C3dActor::_SetFrame(SAKEXE, "C3dActor::SetFrame");
void C3dActor::SetFrame(int framepos) // line 615-619
{
	return (this->*_SetFrame)(framepos);

	m_node->C3dNode::SetFrame(framepos); // inlined
	m_isMatrixNeedUpdate = 1;
}


//hook_method<void (C3dActor::*)(const vector3d& pos)> C3dActor::_SetPos(SAKEXE, "C3dActor::SetPos");
void C3dActor::SetPos(const vector3d& pos) // line ???
{
//	return (this->*_SetPos)(pos);

	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_pos.z = pos.z;
	m_isMatrixNeedUpdate = 1;
}


//hook_method<void (C3dActor::*)(const vector3d& rot)> C3dActor::_SetRot(SAKEXE, "C3dActor::SetRot");
void C3dActor::SetRot(const vector3d& rot) // line ???
{
//	return (this->*_SetRot)(rot);

	m_rot.x = rot.x;
	m_rot.y = rot.y;
	m_rot.z = rot.z;
	m_isMatrixNeedUpdate = 1;
}


//hook_method<void (C3dActor::*)(const vector3d& scale)> C3dActor::_SetScale(SAKEXE, "C3dActor::SetScale");
void C3dActor::SetScale(const vector3d& scale) // line ???
{
//	return (this->*_SetScale)(scale);

	m_scale.x = scale.x;
	m_scale.y = scale.y;
	m_scale.z = scale.z;
	m_isMatrixNeedUpdate = 1;
}


hook_method<void (C3dActor::*)(float opacity)> C3dActor::_SetOpacity(SAKEXE, "C3dActor::SetOpacity");
void C3dActor::SetOpacity(float opacity) // line 622-623
{
	return (this->*_SetOpacity)(opacity);

	;
}


//hook_method<void (C3dActor::*)(int animType)> C3dActor::_SetAnimType(SAKEXE, "C3dActor::SetAnimType");
void C3dActor::SetAnimType(int animType) // line ???-???
{
//	return (this->*_SetAnimType)(animType);

	m_animType = animType;
}


hook_method<void (C3dActor::*)(void)> C3dActor::_OnProcess(SAKEXE, "C3dActor::OnProcess");
void C3dActor::OnProcess(void) // line 651-675
{
	return (this->*_OnProcess)();

	if( m_animType == 1 )
	{
		m_node->C3dNode::SetFrame(m_curMotion); // inlined
		m_isMatrixNeedUpdate = 1;

		int oldMotion = m_curMotion;
		m_curMotion += int(m_animSpeed * 100.0);
		if( m_curMotion >= m_animLen )
			m_curMotion = oldMotion;
	}
	else
	if( m_animType == 2 )
	{
		m_node->C3dNode::SetFrame(m_curMotion); // inlined
		m_isMatrixNeedUpdate = 1;

		if( m_animLen == 0 )
			m_animLen = 1;

		m_curMotion += int(m_animSpeed * 100.0);
		if( m_curMotion >= m_animLen )
			m_curMotion = m_curMotion % m_animLen;
	}
}


hook_method<void (C3dActor::*)(matrix& ctm, bool clip, int flagRF)> C3dActor::_Render(SAKEXE, "C3dActor::Render");
void C3dActor::Render(matrix& ctm, bool clip, int flagRF) // line 680-697
{
	return (this->*_Render)(ctm, clip, flagRF);

	bool flip = false;
	if( m_scale.x < 0.0 )
		flip = !flip;
	if( m_scale.y < 0.0 )
		flip = !flip;
	if( m_scale.z < 0.0 )
		flip = !flip;

	if( m_isMatrixNeedUpdate )
		this->C3dActor::UpdateMatrix();

	matrix objectTM;
	objectTM.matrix::MultMatrix(m_wtm, ctm);
	m_node->Render(objectTM, flip, clip);

	C3dActor* master = m_node->m_master;
	if( master->m_isHalfAlpha == 1 )
	{
		if( master->m_fadeAlphaCnt > 90 )
			master->m_fadeAlphaCnt -= 5;
	}
	else
	{
		if( master->m_fadeAlphaCnt < 255 )
			master->m_fadeAlphaCnt += 5;
	}

	master->m_isHalfAlpha = 0;
}


hook_method<void (C3dActor::*)(C3dModelRes* model)> C3dActor::_AssignModel(SAKEXE, "C3dActor::AssignModel");
void C3dActor::AssignModel(C3dModelRes* model) // line 700-712
{
	return (this->*_AssignModel)(model);

	m_node = new C3dNode();
	m_node->m_master = this;
	m_shadeType = model->m_shadeType;
	m_animLen = model->m_animLen;
	m_node->AssignModel(model->C3dModelRes::GetFirstNode()); // inlined
	m_node->C3dNode::SetFrame(0); // inlined
	m_isMatrixNeedUpdate = 1;
	this->C3dActor::UpdateBound();
}


hook_method<void (C3dActor::*)(const vector3d& lightDir, const vector3d& diffuseCol, const vector3d& ambientCol)> C3dActor::_UpdateVertexColor(SAKEXE, "C3dActor::UpdateVertexColor");
void C3dActor::UpdateVertexColor(const vector3d& lightDir, const vector3d& diffuseCol, const vector3d& ambientCol) // line 840-844
{
	return (this->*_UpdateVertexColor)(lightDir, diffuseCol, ambientCol);

	if( m_isMatrixNeedUpdate )
		this->C3dActor::UpdateMatrix(); // inlined

	m_node->UpdateVertexColor(m_wtm, lightDir, diffuseCol, ambientCol, m_shadeType);
}


//hook_method<C3dNode* (C3dActor::*)(const char* name)> C3dActor::_FindNode(SAKEXE, "C3dActor::FindNode");
C3dNode* C3dActor::FindNode(const char* name) // line ???-???
{
//	return (this->*_FindNode)(name);

	return m_node->C3dNode::FindNode(name);
}


hook_method<void (C3dActor::*)(mystd::list<CVolumeBox*>* volBoxList)> C3dActor::_SetVolumeBoxInfo(SAKEXE, "C3dActor::SetVolumeBoxInfo");
void C3dActor::SetVolumeBoxInfo(mystd::list<CVolumeBox*>* volBoxList) // line 626
{
	return (this->*_SetVolumeBoxInfo)(volBoxList);

	for( mystd::list<CVolumeBox*>::iterator i = volBoxList->begin(); i != volBoxList->end(); ++i )
		m_volumeBoxList.push_back(*i);
}


//hook_method<char* (C3dActor::*)(void)> C3dActor::_GetName(SAKEXE, "C3dActor::GetName");
char* C3dActor::GetName(void) // line ???
{
//	return (this->*_GetName)();

	return m_name;
}


//hook_method<float (C3dActor::*)(void)> C3dActor::_GetAnimSpeed(SAKEXE, "C3dActor::GetAnimSpeed");
float C3dActor::GetAnimSpeed(void) // line ???
{
//	return (this->*_GetAnimSpeed)();

	return m_animSpeed;
}


//hook_method<int (C3dActor::*)(void)> C3dActor::_GetBlockType(SAKEXE, "C3dActor::GetBlockType");
int C3dActor::GetBlockType(void) // line ???
{
//	return (this->*_GetBlockType)();

	return m_blockType;
}


//hook_method<int (C3dActor::*)(void)> C3dActor::_GetIsHideCheck(SAKEXE, "C3dActor::GetIsHideCheck");
int C3dActor::GetIsHideCheck(void) // line ???
{
//	return (this->*_GetIsHideCheck)();

	return m_isHideCheck;
}


//hook_method<void (C3dActor::*)(char* name)> C3dActor::_SetName(SAKEXE, "C3dActor::SetName");
void C3dActor::SetName(char* name) // line ???
{
//	return (this->*_SetName)(name);

	strcpy(m_name, name);
}


//hook_method<void (C3dActor::*)(float speed)> C3dActor::_SetAnimSpeed(SAKEXE, "C3dActor::SetAnimSpeed");
void C3dActor::SetAnimSpeed(float speed) // line ???
{
//	return (this->*_SetAnimSpeed)(speed);

	m_animSpeed = speed;
}


//hook_method<void (C3dActor::*)(int blockType)> C3dActor::_SetBlockType(SAKEXE, "C3dActor::SetBlockType");
void C3dActor::SetBlockType(int blockType) // line ???
{
//	return (this->*_SetBlockType)(blockType);

	m_blockType = blockType;
}


//hook_method<void (C3dActor::*)(int isHideCheck)> C3dActor::_SetIsHideCheck(SAKEXE, "C3dActor::SetIsHideCheck");
void C3dActor::SetIsHideCheck(int isHideCheck) // line ???
{
//	return (this->*_SetIsHideCheck)(isHideCheck);

	m_isHideCheck = isHideCheck;
}


//hook_method<bool (C3dActor::*)(void)> C3dActor::_IsHalfAlpha(SAKEXE, "C3dActor::IsHalfAlpha");
bool C3dActor::IsHalfAlpha(void) // line ???
{
//	return (this->*_IsHalfAlpha)();

	return m_isHalfAlpha;
}


//hook_method<unsigned char (C3dActor::*)(void)> C3dActor::_GetFadeAlphaCnt(SAKEXE, "C3dActor::GetFadeAlphaCnt");
unsigned char C3dActor::GetFadeAlphaCnt(void) // line ???
{
//	return (this->*_GetFadeAlphaCnt)();

	return m_fadeAlphaCnt;
}


hook_method<void (C3dActor::*)(void)> C3dActor::_UpdateMatrix(SAKEXE, "C3dActor::UpdateMatrix");
void C3dActor::UpdateMatrix(void) // line 637-648
{
	return (this->*_UpdateMatrix)();

	m_wtm.matrix::MakeTranslate(m_posOffset.x, m_posOffset.y, m_posOffset.z);
	m_wtm.matrix::AppendScale(m_scale.x, m_scale.y, m_scale.z);
	m_wtm.matrix::AppendYRotation(m_rot.y * pi / 180);
	m_wtm.matrix::AppendXRotation(m_rot.x * pi / 180);
	m_wtm.matrix::AppendZRotation(m_rot.z * pi / 180);
	m_wtm.matrix::AppendTranslate(m_pos);
	m_iwtm.matrix::MakeInverse(m_wtm);
	m_isMatrixNeedUpdate = 0;
}


hook_method<void (C3dActor::*)(void)> C3dActor::_UpdateBound(SAKEXE, "C3dActor::UpdateBound");
void C3dActor::UpdateBound(void) // line 720-837
{
	return (this->*_UpdateBound)();

	//TODO
}
