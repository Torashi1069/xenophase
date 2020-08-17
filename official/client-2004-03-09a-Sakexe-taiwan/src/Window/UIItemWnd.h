#pragma once
#include "ItemInfo.h"
#include "SkillInfo.h"
#include "Struct.h"
#include "Window/UIFrameWnd.h"
class UIBitmapButton;
class UIEditCtrl;
class UIResizer;
class UIScrollBar;
class UIStaticText;
class UITab;


class UIItemDropCntWnd : public UIFrameWnd
{
	struct vtable_t // const UIItemDropCntWnd::`vftable'
	{
		void* (UIItemDropCntWnd::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIFrameWnd::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIFrameWnd::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIWindow::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIWindow::* StoreInfo)(void);
		void (UIFrameWnd::* SaveOriginalPos)(void);
		void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIItemDropCntWnd::* SetShow)(int visible);
		void (UIItemDropCntWnd::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIItemDropCntWnd::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIFrameWnd::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIFrameWnd::* OnMouseMove)(int x, int y);
		void (UIFrameWnd::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIFrameWnd::* OnLBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIWindow::* OnWheel)(int wheel);
		void (UIFrameWnd::* RefreshSnap)(void);
		int (UIItemDropCntWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: UIEditCtrl* m_editCtrl;
	/* this+100 */ protected: UIStaticText* m_newText;

	public: UIItemDropCntWnd::UIItemDropCntWnd(void);
	public: virtual UIItemDropCntWnd::~UIItemDropCntWnd(void);
	public: virtual void UIItemDropCntWnd::OnCreate(int cx, int cy);
	public: virtual void UIItemDropCntWnd::OnDraw(void);
	public: virtual int UIItemDropCntWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UIItemDropCntWnd::SetShow(int visible);

private:
	static hook_method<void (UIItemDropCntWnd::*)(int cx, int cy)> UIItemDropCntWnd::_OnCreate;
	static hook_method<void (UIItemDropCntWnd::*)(void)> UIItemDropCntWnd::_OnDraw;
	static hook_method<int (UIItemDropCntWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIItemDropCntWnd::_SendMsg;
	static hook_method<void (UIItemDropCntWnd::*)(int visible)> UIItemDropCntWnd::_SetShow;
};


class UIItemBaseWnd : public UIFrameWnd
{
	struct vtable_t // const UIItemBaseWnd::`vftable'
	{
		void* (UIItemBaseWnd::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIFrameWnd::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIFrameWnd::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIItemBaseWnd::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIItemBaseWnd::* StoreInfo)(void);
		void (UIFrameWnd::* SaveOriginalPos)(void);
		void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int);
		void (UIItemBaseWnd::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIItemBaseWnd::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIFrameWnd::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIFrameWnd::* OnMouseMove)(int x, int y);
		void (UIFrameWnd::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIFrameWnd::* OnLBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIItemBaseWnd::* OnWheel)(int wheel);
		void (UIFrameWnd::* RefreshSnap)(void);
		int (UIItemBaseWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: int m_drawNumItem;
	/* this+100 */ protected: int m_isBasket;
	/* this+104 */ protected: UIResizer* m_resizer;
	/* this+108 */ protected: UIScrollBar* m_scrollBar;
	/* this+112 */ protected: UIBitmapButton* m_button[2];
	/* this+120 */ protected: int m_viewOffset;
	/* this+124 */ protected: int m_itemHorzNum;
	/* this+128 */ protected: int m_itemVertNum;
	/* this+132 */ protected: int m_vertScrEnabled;
	/* this+136 */ protected: mystd::list<ITEM_INFO> m_itemList;

	public: UIItemBaseWnd::UIItemBaseWnd(void);
	public: virtual UIItemBaseWnd::~UIItemBaseWnd(void);
	public: virtual void UIItemBaseWnd::OnCreate(int cx, int cy);
	public: virtual void UIItemBaseWnd::OnDraw(void);
	//public: virtual int UIItemBaseWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	//public: virtual void UIItemBaseWnd::OnWheel(int wheel);
	public: virtual void UIItemBaseWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo);
	//public: virtual void UIItemBaseWnd::StoreInfo(void);
	public: void UIItemBaseWnd::RecalcScrbarPos(void);
	//protected: int UIItemBaseWnd::GetCurItem(int x, int y);
	//protected: ITEM_INFO UIItemBaseWnd::GetItemInfo(int);
	//protected: ITEM_INFO UIItemBaseWnd::GetItemInfo(int, int);

private:
	static hook_method<void (UIItemBaseWnd::*)(int cx, int cy)> UIItemBaseWnd::_OnCreate;
	static hook_method<void (UIItemBaseWnd::*)(void)> UIItemBaseWnd::_OnDraw;
	static hook_method<void (UIItemBaseWnd::*)(int x, int y, const DRAG_INFO* const dragInfo)> UIItemBaseWnd::_DragAndDrop;
	static hook_method<void (UIItemBaseWnd::*)(void)> UIItemBaseWnd::_RecalcScrbarPos;
};


class UIMerchantItemShopWnd : public UIItemBaseWnd
{
	struct vtable_t // const UIMerchantItemShopWnd::`vftable'
	{
		void* (UIMerchantItemShopWnd::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIFrameWnd::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIFrameWnd::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIMerchantItemShopWnd::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIMerchantItemShopWnd::* StoreInfo)(void);
		void (UIFrameWnd::* SaveOriginalPos)(void);
		void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int);
		void (UIMerchantItemShopWnd::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIMerchantItemShopWnd::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIMerchantItemShopWnd::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIFrameWnd::* OnMouseMove)(int x, int y);
		void (UIMerchantItemShopWnd::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIFrameWnd::* OnLBtnUp)(int x, int y);
		void (UIMerchantItemShopWnd::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIItemBaseWnd::* OnWheel)(int wheel);
		void (UIFrameWnd::* RefreshSnap)(void);
		int (UIMerchantItemShopWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIItemBaseWnd baseclass_0;
	/* this+148 */ protected: UIStaticText* m_titleText;
	/* this+152 */ protected: MerchantItemShopWndInfo* m_info;
	/* this+156 */ protected: int m_curItem;
	/* this+160 */ protected: int m_aid;

	public: UIMerchantItemShopWnd::UIMerchantItemShopWnd(void);
	public: virtual UIMerchantItemShopWnd::~UIMerchantItemShopWnd(void);
	public: virtual void UIMerchantItemShopWnd::OnCreate(int cx, int cy);
	public: virtual void UIMerchantItemShopWnd::OnLBtnDown(int x, int y);
	public: virtual void UIMerchantItemShopWnd::OnRBtnDown(int x, int y);
	public: virtual void UIMerchantItemShopWnd::OnMouseHover(int x, int y);
	public: virtual void UIMerchantItemShopWnd::OnDraw(void);
	public: virtual void UIMerchantItemShopWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo);
	public: virtual int UIMerchantItemShopWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UIMerchantItemShopWnd::StoreInfo(void);

private:
	static hook_method<void (UIMerchantItemShopWnd::*)(int cx, int cy)> UIMerchantItemShopWnd::_OnCreate;
	static hook_method<void (UIMerchantItemShopWnd::*)(int x, int y)> UIMerchantItemShopWnd::_OnLBtnDown;
	static hook_method<void (UIMerchantItemShopWnd::*)(int x, int y)> UIMerchantItemShopWnd::_OnRBtnDown;
	static hook_method<void (UIMerchantItemShopWnd::*)(int x, int y)> UIMerchantItemShopWnd::_OnMouseHover;
	static hook_method<void (UIMerchantItemShopWnd::*)(void)> UIMerchantItemShopWnd::_OnDraw;
	static hook_method<void (UIMerchantItemShopWnd::*)(int x, int y, const DRAG_INFO* const dragInfo)> UIMerchantItemShopWnd::_DragAndDrop;
	static hook_method<int (UIMerchantItemShopWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMerchantItemShopWnd::_SendMsg;
	static hook_method<void (UIMerchantItemShopWnd::*)(void)> UIMerchantItemShopWnd::_StoreInfo;
};


class UIMerchantItemPurchaseWnd : public UIItemBaseWnd
{
	struct vtable_t // const UIMerchantItemPurchaseWnd::`vftable'
	{
		void* (UIMerchantItemPurchaseWnd::* scalar_deleting_destructor)(unsigned int flags);
		void (UIWindow::* Invalidate)(void);
		void (UIWindow::* InvalidateWallPaper)(void);
		void (UIWindow::* Resize)(int cx, int cy);
		bool (UIFrameWnd::* IsFrameWnd)(void);
		bool (UIWindow::* IsUpdateNeed)(void);
		void (UIFrameWnd::* Move)(int x, int y);
		bool (UIWindow::* CanGetFocus)(void);
		bool (UIWindow::* GetTransBoxInfo)(BOXINFO* boxInfo);
		bool (UIWindow::* IsTransmitMouseInput)(void);

		bool (UIWindow::* ShouldDoHitTest)(void);
		void (UIMerchantItemPurchaseWnd::* DragAndDrop)(int x, int y, const DRAG_INFO* const dragInfo);
		void (UIMerchantItemPurchaseWnd::* StoreInfo)(void);
		void (UIFrameWnd::* SaveOriginalPos)(void);
		void (UIFrameWnd::* MoveDelta)(int deltaDragX, int deltaDragY);
		unsigned long (UIWindow::* GetColor)(void);
		void (UIWindow::* SetShow)(int);
		void (UIMerchantItemPurchaseWnd::* OnCreate)(int cx, int cy);
		void (UIWindow::* OnDestroy)(void);
		void (UIWindow::* OnProcess)(void);

		void (UIMerchantItemPurchaseWnd::* OnDraw)(void);
		void (UIWindow::* OnDraw2)(void);
		void (UIWindow::* OnRun)(void);
		void (UIWindow::* OnSize)(int cx, int cy);
		void (UIWindow::* OnBeginEdit)(void);
		void (UIWindow::* OnFinishEdit)(void);
		void (UIMerchantItemPurchaseWnd::* OnLBtnDown)(int x, int y);
		void (UIWindow::* OnLBtnDblClk)(int x, int y);
		void (UIFrameWnd::* OnMouseMove)(int x, int y);
		void (UIMerchantItemPurchaseWnd::* OnMouseHover)(int x, int y);

		void (UIWindow::* OnMouseShape)(int x, int y);
		void (UIFrameWnd::* OnLBtnUp)(int x, int y);
		void (UIMerchantItemPurchaseWnd::* OnRBtnDown)(int x, int y);
		void (UIWindow::* OnRBtnUp)(int x, int y);
		void (UIWindow::* OnRBtnDblClk)(int x, int y);
		void (UIItemBaseWnd::* OnWheel)(int wheel);
		void (UIFrameWnd::* RefreshSnap)(void);
		int (UIMerchantItemPurchaseWnd::* SendMsg)(UIWindow* sender, int message, int val1, int val2, int val3);
	};

	/* this+  0 */ public: //UIItemBaseWnd baseclass_0;
	/* this+148 */ protected: UIStaticText* m_priceText;
	/* this+152 */ protected: unsigned long m_aid;
	/* this+156 */ protected: MerchantItemPurchaseWndInfo* m_info;
	/* this+160 */ protected: int m_curItem;

	public: UIMerchantItemPurchaseWnd::UIMerchantItemPurchaseWnd(void);
	public: virtual UIMerchantItemPurchaseWnd::~UIMerchantItemPurchaseWnd(void);
	public: virtual void UIMerchantItemPurchaseWnd::OnCreate(int cx, int cy);
	public: virtual void UIMerchantItemPurchaseWnd::OnLBtnDown(int x, int y);
	public: virtual void UIMerchantItemPurchaseWnd::OnRBtnDown(int x, int y);
	public: virtual void UIMerchantItemPurchaseWnd::OnMouseHover(int x, int y);
	public: virtual void UIMerchantItemPurchaseWnd::OnDraw(void);
	public: virtual void UIMerchantItemPurchaseWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo);
	public: virtual int UIMerchantItemPurchaseWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: void UIMerchantItemPurchaseWnd::StoreInfo(void);

private:
	static hook_method<void (UIMerchantItemPurchaseWnd::*)(int cx, int cy)> UIMerchantItemPurchaseWnd::_OnCreate;
	static hook_method<void (UIMerchantItemPurchaseWnd::*)(int x, int y)> UIMerchantItemPurchaseWnd::_OnLBtnDown;
	static hook_method<void (UIMerchantItemPurchaseWnd::*)(int x, int y)> UIMerchantItemPurchaseWnd::_OnRBtnDown;
	static hook_method<void (UIMerchantItemPurchaseWnd::*)(int x, int y)> UIMerchantItemPurchaseWnd::_OnMouseHover;
	static hook_method<void (UIMerchantItemPurchaseWnd::*)(void)> UIMerchantItemPurchaseWnd::_OnDraw;
	static hook_method<void (UIMerchantItemPurchaseWnd::*)(int x, int y, const DRAG_INFO* const dragInfo)> UIMerchantItemPurchaseWnd::_DragAndDrop;
	static hook_method<int (UIMerchantItemPurchaseWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIMerchantItemPurchaseWnd::_SendMsg;
	static hook_method<void (UIMerchantItemPurchaseWnd::*)(void)> UIMerchantItemPurchaseWnd::_StoreInfo;
};


class UIMerchantItemWnd : public UIItemBaseWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIItemBaseWnd baseclass_0;
	/* this+148 */ protected: MerchantItemWndInfo* m_info;
	/* this+152 */ protected: UIBitmapButton* m_sysButtons[1];
	/* this+156 */ protected: UIStaticText* m_supplyText;

	public: UIMerchantItemWnd::UIMerchantItemWnd(void);
	public: virtual UIMerchantItemWnd::~UIMerchantItemWnd(void);
	//public: void UIMerchantItemWnd::OnCreate(int cx, int cy);
	//public: void UIMerchantItemWnd::OnLBtnDown(int x, int y);
	//public: void UIMerchantItemWnd::OnRBtnDown(int x, int y);
	//public: void UIMerchantItemWnd::OnMouseHover(int x, int y);
	//public: void UIMerchantItemWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo);
	//public: int UIMerchantItemWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	//public: void UIMerchantItemWnd::StoreInfo();
};


class UIItemWnd : public UIItemBaseWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIItemBaseWnd baseclass_0;
	/* this+148 */ protected: ItemWndInfo* m_info;
	/* this+152 */ protected: UITab* m_tab;
	/* this+156 */ protected: UIBitmapButton* m_sysButtons[3];
	/* this+168 */ protected: int m_curRadioBtn[3];
	/* this+180 */ protected: int m_curTab;
	/* this+184 */ protected: int m_orgHeight;

	public: UIItemWnd::UIItemWnd(void);
	public: virtual UIItemWnd::~UIItemWnd(void);
	public: virtual bool UIItemWnd::IsUpdateNeed(void);
	public: virtual void UIItemWnd::OnCreate(int cx, int cy);
	public: virtual void UIItemWnd::OnDestroy(void);
	public: virtual void UIItemWnd::OnDraw(void);
	public: virtual void UIItemWnd::OnLBtnDblClk(int x, int y);
	public: virtual void UIItemWnd::OnLBtnDown(int x, int y);
	public: virtual void UIItemWnd::OnRBtnDown(int x, int y);
	public: virtual void UIItemWnd::OnMouseHover(int x, int y);
	public: virtual int UIItemWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UIItemWnd::DragAndDrop(int x, int y, const DRAG_INFO* const dragInfo);
	public: virtual void UIItemWnd::StoreInfo(void);
	public: bool UIItemWnd::Sort(const ITEM_INFO* const itemInfo);
	public: void UIItemWnd::RefreshRadioBtn(void);
	protected: ITEM_INFO UIItemWnd::GetItemInfo(int x, int y);

private:
	static hook_method<bool (UIItemWnd::*)(void)> UIItemWnd::_IsUpdateNeed;
	static hook_method<void (UIItemWnd::*)(int cx, int cy)> UIItemWnd::_OnCreate;
	static hook_method<void (UIItemWnd::*)(void)> UIItemWnd::_OnDestroy;
	static hook_method<void (UIItemWnd::*)(void)> UIItemWnd::_OnDraw;
	static hook_method<void (UIItemWnd::*)(int x, int y)> UIItemWnd::_OnLBtnDblClk;
	static hook_method<void (UIItemWnd::*)(int x, int y)> UIItemWnd::_OnLBtnDown;
	static hook_method<void (UIItemWnd::*)(int x, int y)> UIItemWnd::_OnRBtnDown;
	static hook_method<void (UIItemWnd::*)(int x, int y)> UIItemWnd::_OnMouseHover;
	static hook_method<int (UIItemWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UIItemWnd::_SendMsg;
	static hook_method<void (UIItemWnd::*)(int x, int y, const DRAG_INFO* const dragInfo)> UIItemWnd::_DragAndDrop;
	static hook_method<void (UIItemWnd::*)(void)> UIItemWnd::_StoreInfo;
	static hook_method<bool (UIItemWnd::*)(const ITEM_INFO* const itemInfo)> UIItemWnd::_Sort;
	static hook_method<void (UIItemWnd::*)(void)> UIItemWnd::_RefreshRadioBtn;
	static hook_method<ITEM_INFO (UIItemWnd::*)(int x, int y)> UIItemWnd::_GetItemInfo;
};


class UIItemStoreWnd : public UIItemBaseWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIItemBaseWnd baseclass_0;
	/* this+148 */ protected: mystd::string m_countInfoText;
	/* this+164 */ protected: UIStaticText* m_titleText;
	/* this+168 */ protected: ItemStoreWndInfo* m_info;
	/* this+172 */ protected: UITab* m_tab;
	/* this+176 */ protected: int m_curRadioBtn[3];
	/* this+188 */ protected: int m_curTab;

	public: UIItemStoreWnd::UIItemStoreWnd(void);
	//public: virtual UIItemStoreWnd::~UIItemStoreWnd(void);
	//public: void UIItemStoreWnd::OnCreate(int cx, int cy);
	//public: void UIItemStoreWnd::OnDraw();
	//public: void UIItemStoreWnd::OnLBtnDown(int x, int y);
	//public: void UIItemStoreWnd::OnRBtnDown(int x, int y);
	//public: void UIItemStoreWnd::OnMouseHover(int x, int y);
	//public: void UIItemStoreWnd::DragAndDrop(int, int, const struct DRAG_INFO * const);
	//public: int UIItemStoreWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	//public: void UIItemStoreWnd::StoreInfo();
	//protected: struct ITEM_INFO UIItemStoreWnd::GetItemInfo(int, int);
	//public: unsigned char UIItemStoreWnd::Sort(const struct ITEM_INFO * const);
	//public: void UIItemStoreWnd::RefreshRadioBtn();
};


class UISkillListWnd : public UIFrameWnd
{
	struct vtable_t
	{
		//TODO
	};

	/* this+  0 */ public: //UIFrameWnd baseclass_0;
	/* this+ 96 */ protected: UIResizer* m_resizer;
	/* this+100 */ protected: UIScrollBar* m_scrollBar;
	/* this+104 */ protected: UIBitmapButton* m_button[2];
	/* this+112 */ protected: UIBitmapButton* m_incArrowButton[7];
	/* this+140 */ protected: UIBitmapButton* m_lvlSelectDnButton[7];
	/* this+168 */ protected: UIBitmapButton* m_lvlSelectUpButton[7];
	/* this+196 */ protected: int m_curItem;
	/* this+200 */ protected: int m_viewOffset;
	/* this+204 */ protected: int m_itemHorzNum;
	/* this+208 */ protected: int m_itemVertNum;
	/* this+212 */ protected: int m_vertScrEnabled;
	/* this+216 */ protected: mystd::list<SKILL_INFO> m_itemList;
	/* this+228 */ protected: SkillListWndInfo* m_info;
	/* this+232 */ protected: mystd::vector<StringId> m_menuItems;

	public: UISkillListWnd::UISkillListWnd(void);
	public: virtual UISkillListWnd::~UISkillListWnd(void);
	public: virtual void UISkillListWnd::OnCreate(int cx, int cy);
	public: virtual void UISkillListWnd::OnDraw(void);
	public: virtual void UISkillListWnd::OnLBtnDown(int x, int y);
	public: virtual void UISkillListWnd::OnLBtnDblClk(int x, int y);
	public: virtual void UISkillListWnd::OnRBtnDown(int x, int y);
	public: virtual void UISkillListWnd::OnRBtnUp(int x, int y);
	public: virtual void UISkillListWnd::OnMouseHover(int x, int y);
	public: virtual int UISkillListWnd::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3);
	public: virtual void UISkillListWnd::StoreInfo(void);
	public: virtual void UISkillListWnd::OnWheel(int wheel);
	public: virtual bool UISkillListWnd::IsUpdateNeed(void);
	public: void UISkillListWnd::RecalcScrbarPos(void);
	public: void UISkillListWnd::RefreshButton(void);
	public: SKILL_INFO UISkillListWnd::GetSkillInfoByViewCnt(int viewCnt);
	protected: SKILL_INFO UISkillListWnd::GetSkillInfo(int curItem);
	protected: SKILL_INFO UISkillListWnd::GetSkillInfo(int x, int drawCount);
	protected: int UISkillListWnd::GetCurItem(int x, int y);

private:
	static hook_method<void (UISkillListWnd::*)(int cx, int cy)> UISkillListWnd::_OnCreate;
	static hook_method<void (UISkillListWnd::*)(void)> UISkillListWnd::_OnDraw;
	static hook_method<void (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_OnLBtnDown;
	static hook_method<void (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_OnLBtnDblClk;
	static hook_method<void (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_OnRBtnDown;
	static hook_method<void (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_OnRBtnUp;
	static hook_method<void (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_OnMouseHover;
	static hook_method<int (UISkillListWnd::*)(UIWindow* sender, int message, int val1, int val2, int val3)> UISkillListWnd::_SendMsg;
	static hook_method<void (UISkillListWnd::*)(void)> UISkillListWnd::_StoreInfo;
	static hook_method<void (UISkillListWnd::*)(int wheel)> UISkillListWnd::_OnWheel;
	static hook_method<bool (UISkillListWnd::*)(void)> UISkillListWnd::_IsUpdateNeed;
	static hook_method<void (UISkillListWnd::*)(void)> UISkillListWnd::_RecalcScrbarPos;
	static hook_method<void (UISkillListWnd::*)(void)> UISkillListWnd::_RefreshButton;
	static hook_method<SKILL_INFO (UISkillListWnd::*)(int viewCnt)> UISkillListWnd::_GetSkillInfoByViewCnt;
	static hook_method<SKILL_INFO (UISkillListWnd::*)(int curItem)> UISkillListWnd::_GetSkillInfo;
	static hook_method<SKILL_INFO (UISkillListWnd::*)(int x, int drawCount)> UISkillListWnd::_GetSkillInfo2;
	static hook_method<int (UISkillListWnd::*)(int x, int y)> UISkillListWnd::_GetCurItem;
};
