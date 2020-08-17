#include "Globals.h"
#include "Window/UIGage.h"
////////////////////////////////////////


UIGage::UIGage() // line 292-310 (UIControl2.cpp)
{
	m_backR = 68;
	m_backG = 68;
	m_backB = 68;
	m_backR2 = 68;
	m_backG2 = 68;
	m_backB2 = 68;
	m_edgeR = 20;
	m_edgeG = 25;
	m_edgeB = 155;
	m_r = 22;
	m_g = 234;
	m_b = 37;
	m_r2 = 29;
	m_g2 = 101;
	m_b2 = 219;
}


UIGage::~UIGage() // line 313-314 (UIControl2.cpp)
{
}


bool UIGage::ShouldDoHitTest() // line 305 (Window/UISys.h)
{
	return false;
}


///////////////////////////////////////


UIRechargeGage::UIRechargeGage() // line 318-321 (UIControl2.cpp)
{
	m_amount = 0;
	m_totalAmount = 100;
}


UIRechargeGage::~UIRechargeGage() // line 324-325 (UIControl2.cpp)
{
}


void UIRechargeGage::OnDraw() // line 328-338 (UIControl2.cpp)
{
	this->UIWindow::ClearDC(RGB(m_edgeR, m_edgeG, m_edgeB));
	this->UIWindow::DrawBox(1, 1, m_w - 2, m_h - 2, RGB(m_backR, m_backG, m_backB));

	if( m_totalAmount != 0 )
	{
		float percent = float(100 * m_amount / m_totalAmount);
		if( percent != 0 )
		{
			this->UIWindow::DrawBox(1, 1, (int)(m_w * percent / 100 - 2), m_h - 2, RGB(m_r, m_g, m_b));
		}
	}
}


void UIRechargeGage::SetAmount(int amount, int totalAmount) // line 341-345 (UIControl2.cpp)
{
	m_amount = amount;
	m_totalAmount = totalAmount;
	this->Invalidate();
}


///////////////////////////////////////


UIPcGage::UIPcGage() // line 349-358 (UIControl2.cpp)
{
	m_hpAmount = 0;
	m_hpTotalAmount = 0;
	m_spAmount = 0;
	m_spTotalAmount = 0;
	m_mode = 0;
	m_dangerR = 234;
	m_dangerG = 22;
	m_dangerB = 22;
}


UIPcGage::~UIPcGage() // line 361-362 (UIControl2.cpp)
{
}


void UIPcGage::OnDraw() // line 370-407 (UIControl2.cpp)
{
	this->UIWindow::ClearDC(RGB(m_edgeR, m_edgeG, m_edgeB));

	if( m_mode )
	{
		this->UIWindow::DrawBox(1, 1, m_w - 2, (m_h - 3) / 2, RGB(m_backR, m_backG, m_backB));
		this->UIWindow::DrawBox(1, m_h / 2 + 1, m_w - 2, (m_h - 3) / 2, RGB(m_backR2, m_backG2, m_backB2));

		if( m_hpTotalAmount != 0 && m_spTotalAmount != 0 )
		{
			float percent = float(100 * m_hpAmount / m_hpTotalAmount);
			if( percent != 0 )
			{
				if( percent >= 25 )
				{
					this->UIWindow::DrawBox(1, 1, (int)(m_w * percent / 100 - 2), (m_h - 3) / 2, RGB(m_r, m_g, m_b));
				}
				else
				{
					this->UIWindow::DrawBox(1, 1, (int)(m_w * percent / 100 - 2), (m_h - 3) / 2, RGB(m_dangerR, m_dangerG, m_dangerB));
				}
			}

			float percent2 = float(100 * m_spAmount / m_spTotalAmount);
			if( percent2 != 0 )
			{
				this->UIWindow::DrawBox(1, m_h / 2 + 1, (int)(m_w * percent2 / 100 - 2), (m_h - 3) / 2, RGB(m_r2, m_g2, m_b2));
			}
		}
	}
	else
	{
		this->UIWindow::DrawBox(1, 1, m_w - 2, m_h - 2, RGB(m_backR, m_backG, m_backB));

		if( m_hpTotalAmount != 0 )
		{
			float percent = float(100 * m_hpAmount / m_hpTotalAmount);
			if( percent != 0 )
			{
				if( percent >= 25 )
				{
					this->UIWindow::DrawBox(1, 1, (int)(m_w * percent / 100 - 2), m_h - 2, RGB(m_r, m_g, m_b));
				}
				else
				{
					this->UIWindow::DrawBox(1, 1, (int)(m_w * percent / 100 - 2), m_h - 2, RGB(m_dangerR, m_dangerG, m_dangerB));
				}
			}
		}
	}
}


void UIPcGage::SetHp(int amount, int totalAmount) // line 410-414 (UIControl2.cpp)
{
	m_hpAmount = amount;
	m_hpTotalAmount = totalAmount;
	this->Invalidate();
}


void UIPcGage::SetSp(int amount, int totalAmount) // line 417-421 (UIControl2.cpp)
{
	m_spAmount = amount;
	m_spTotalAmount = totalAmount;
	this->Invalidate();
}


void UIPcGage::SetMode(int mode) // line 365-367 (UIControl2.cpp)
{
	m_mode = mode;
}


///////////////////////////////////////


UIPlayerGage::UIPlayerGage() // line 426-430 (UIControl2.cpp)
{
	m_dangerR = 234;
	m_dangerG = 22;
	m_dangerB = 22;
}


UIPlayerGage::~UIPlayerGage() // line 433-434 (UIControl2.cpp)
{
}


bool UIPlayerGage::IsUpdateNeed() // line 347 (Window/UISys.h)
{
	return true;
}


void UIPlayerGage::OnDraw() // line 437-463 (UIControl2.cpp)
{
	int hp = g_session.CSession::GetHp();
	int maxhp = g_session.CSession::GetMaxhp();
	int sp = g_session.CSession::GetSp();
	int maxsp = g_session.CSession::GetMaxsp();

	this->UIWindow::ClearDC(RGB(m_edgeR, m_edgeG, m_edgeB));
	this->UIWindow::DrawBox(1, 1, m_w - 2, (m_h - 3) / 2, RGB(m_backR, m_backG, m_backB));
	this->UIWindow::DrawBox(1, m_h / 2 + 1, m_w - 2, (m_h - 3) / 2, RGB(m_backR2, m_backG2, m_backB2));

	float percent1 = float(100 * hp / maxhp);
	if( percent1 != 0 )
	{
		if( percent1 >= 25 )
		{
			this->UIWindow::DrawBox(1, 1, (int)(m_w * percent1 / 100 - 2), (m_h - 3) / 2, RGB(m_r, m_g, m_b));
		}
		else
		{
			this->UIWindow::DrawBox(1, 1, (int)(m_w * percent1 / 100 - 2), (m_h - 3) / 2, RGB(m_dangerR, m_dangerG, m_dangerB));
		}
	}

	float percent2 = float(100 * sp / maxsp);
	if( percent2 != 0 )
	{
		this->UIWindow::DrawBox(1, m_h / 2 + 1, (int)(m_w * percent2 / 100 - 2), (m_h - 3) / 2, RGB(m_r2, m_g2, m_b2));
	}
}


///////////////////////////////////////
