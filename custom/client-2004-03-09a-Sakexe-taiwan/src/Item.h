#pragma once
#include "GameActor.h" // CRenderObject


class CItem : public CRenderObject
{
	struct vtable_t
	{
		void* (CItem::* scalar_deleting_destructor)(unsigned int flags);
		bool (CItem::* OnProcess)(void);
		void (CItem::* SendMsg)(CGameObject* sender, int message, int arg1, int arg2, int arg3);
		void (CItem::* Render)(matrix& vtm);
		int (CGameObject::* Get8Dir)(float rot);
		void (CItem::* SetRenderInfo)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
		void (CRenderObject::* SetTlvert)(float tlvertX, float tlvertY);
		void (CRenderObject::* SetAction)(int action, int speed, int type);
		void (CRenderObject::* ProcessMotion)(void);
	};

	/* this+  0 */ public: //CRenderObject baseclass_0;
	/* this+204 */ public: mystd::string m_itemName;
	/* this+220 */ protected: unsigned long m_aid;
	/* this+224 */ protected: int m_isJumping;
	/* this+228 */ protected: float m_sfallingSpeed;
	/* this+232 */ protected: float m_sPosY;

	public: CItem::CItem(void);
	public: virtual CItem::~CItem(void);
	public: void CItem::OnInit(void);
	public: void CItem::OnExit(void);
	public: virtual bool CItem::OnProcess(void);
	public: virtual void CItem::Render(matrix& vtm);
	public: virtual void CItem::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);
	public: virtual void CItem::SetRenderInfo(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY);
	public: unsigned long CItem::GetAID(void);

private:
	static hook_method<void (CItem::*)(void)> CItem::_OnInit;
	static hook_method<void (CItem::*)(void)> CItem::_OnExit;
	static hook_method<bool (CItem::*)(void)> CItem::_OnProcess;
	static hook_method<void (CItem::*)(matrix& vtm)> CItem::_Render;
	static hook_method<void (CItem::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CItem::_SendMsg;
	static hook_method<void (CItem::*)(RENDER_INFO_RECT& info, const float tlvertX, const float tlvertY)> CItem::_SetRenderInfo;
	static hook_method<unsigned long (CItem::*)(void)> CItem::_GetAID;
};
