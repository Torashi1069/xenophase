#include "Window/UIWindow.h"


class UIGage : public UIWindow
{
public:
	UIGage();
	virtual ~UIGage();
	virtual bool ShouldDoHitTest();

public:
	/* this+  0 */ //UIWindow baseclass_0;
	/* this+ 72 */ int m_edgeR;
	/* this+ 76 */ int m_edgeG;
	/* this+ 80 */ int m_edgeB;
	/* this+ 84 */ int m_backR;
	/* this+ 88 */ int m_backG;
	/* this+ 92 */ int m_backB;
	/* this+ 96 */ int m_r;
	/* this+100 */ int m_g;
	/* this+104 */ int m_b;
	/* this+108 */ int m_backR2;
	/* this+112 */ int m_backG2;
	/* this+116 */ int m_backB2;
	/* this+120 */ int m_r2;
	/* this+124 */ int m_g2;
	/* this+128 */ int m_b2;
};


class UIRechargeGage : public UIGage
{
public:
	UIRechargeGage();
	virtual ~UIRechargeGage();
	virtual void OnDraw();
	void SetAmount(int amount, int totalAmount);

public:
	/* this+  0 */ //UIGage baseclass_0;
	/* this+132 */ int m_amount;
	/* this+136 */ int m_totalAmount;
};


class UIPcGage : public UIGage
{
public:
	UIPcGage();
	virtual ~UIPcGage();
	virtual void OnDraw();
	void SetHp(int amount, int totalAmount);
	void SetSp(int amount, int totalAmount);
	void SetMode(int mode);

public:
	/* this+  0 */ //UIGage baseclass_0;
	/* this+132 */ int m_dangerR;
	/* this+136 */ int m_dangerG;
	/* this+140 */ int m_dangerB;
	/* this+144 */ int m_mode; // 0:hp only, !0:hp and sp
	/* this+148 */ int m_hpAmount;
	/* this+152 */ int m_hpTotalAmount;
	/* this+156 */ int m_spAmount;
	/* this+160 */ int m_spTotalAmount;
};


class UIPlayerGage : public UIGage
{
public:
	UIPlayerGage();
	virtual ~UIPlayerGage();
	virtual bool IsUpdateNeed();
	virtual void OnDraw();

public:
	/* this+  0 */ //UIGage baseclass_0;
	/* this+132 */ int m_dangerR;
	/* this+136 */ int m_dangerG;
	/* this+140 */ int m_dangerB;
};


