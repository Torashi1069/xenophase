#include "GameActor.h"
#include "GameWorld.h"
#include "Item.h"
////////////////////////////////////////


hook_func<CRayPicker* (CRayPicker::*)(void)> CRayPicker::_cCRayPicker("CRayPicker::CRayPicker");
CRayPicker::CRayPicker(void)
{
	(this->*_cCRayPicker)(); return;

	;
}


hook_func<void (CRayPicker::*)(const ray3d& ray, SceneGraphNode* rootNode)> CRayPicker::_Build("CRayPicker::Build");
void CRayPicker::Build(const ray3d& ray, SceneGraphNode* rootNode)
{
	return (this->*_Build)(ray, rootNode);
}


////////////////////////////////////////


hook_func<CWorld* (CWorld::*)(void)> CWorld::_cCWorld("CWorld::CWorld");
CWorld::CWorld(void)
{
	(this->*_cCWorld)(); return;
}


hook_func<void (CWorld::*)(void)> CWorld::_dCWorld("CWorld::~CWorld");
CWorld::~CWorld(void)
{
	(this->*_dCWorld)(); return;
}


CGameActor* CWorld::GetGameActorByAID(unsigned long GID)
{
	for( mystd::list<CGameActor*>::iterator it = m_actorList.begin(); it != m_actorList.end(); ++it )
		if( (*it)->CGameActor::GetGID() == GID )
			return *it;

	return NULL;
}


CItem* CWorld::GetItemByAID(unsigned long AID)
{
	for( mystd::list<CItem*>::iterator it = m_itemList.begin(); it != m_itemList.end(); ++it )
        if( (*it)->CItem::GetAID() == AID )
			return *it;

    return NULL;
}


SceneGraphNode* CWorld::GetRootNode(void)
{
	return &m_rootNode;
}


BOOL CWorld::IsPKZone()
{
	return m_isPKZone;
}


BOOL CWorld::IsSiegeMode()
{
	return m_isSiegeMode;
}


////////////////////////////////////////
