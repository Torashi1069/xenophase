#pragma once
#include "GameActor.h" // CRenderObject
#include "3dLib/Prim.h" // matrix
#include "std/string"


class CItem : public CRenderObject
{
public:
	CItem();
	virtual ~CItem();
	void OnInit();
	void OnExit();
	virtual bool OnProcess();
	virtual void Render(matrix& vtm);
	virtual void SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	virtual void SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
	unsigned long GetAID();

public:
	/* this+  0 */ //CRenderObject baseclass_0;
	/* this+248 */ mystd::string m_itemName;
protected:
	/* this+264 */ unsigned long m_aid;
	/* this+268 */ BOOL m_isJumping;
	/* this+272 */ float m_sfallingSpeed;
	/* this+276 */ float m_sPosY;

private:
	static hook_func<bool (CItem::*)()> CItem::_OnProcess;
	static hook_func<void (CItem::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CItem::_SendMsg;
	static hook_func<void (CItem::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CItem::_SetRenderInfo;
};
