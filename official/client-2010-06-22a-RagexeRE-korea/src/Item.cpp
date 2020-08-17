#include "Item.h"


CItem::CItem()
{
	this->CItem::OnInit();
}


CItem::~CItem()
{
	this->CItem::OnExit();
}


void CItem::OnInit()
{
	m_zoom = 1.0f;
	m_shouldAddPickInfo = true;
	m_shadowOn = true;
	m_colorOfSingleColor = 0xFFFFFF00;
}


void CItem::OnExit()
{
}


hook_func<bool (CItem::*)()> CItem::_OnProcess("CItem::OnProcess");
bool CItem::OnProcess()
{
	return (this->*_OnProcess)();

	//TODO
}


void CItem::Render(matrix& vtm)
{
	if( !m_isVisible )
		return;

	this->CRenderObject::RenderShadow(vtm, m_zoom * 0.4f);
	this->CRenderObject::RenderBody(vtm, 0);
}


hook_func<void (CItem::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CItem::_SendMsg("CItem::SendMsg");
void CItem::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3)
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);

	//TODO
}


hook_func<void (CItem::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CItem::_SetRenderInfo("CItem::SetRenderInfo");
void CItem::SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)
{
	return (this->*_SetRenderInfo)(info, tlvertX, tlvertY);

	//TODO
}


unsigned long CItem::GetAID()
{
	return m_aid;
}
