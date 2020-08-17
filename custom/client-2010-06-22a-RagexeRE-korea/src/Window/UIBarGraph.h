#pragma once
#include "Window/UIWindow.h"


class UIBarGraph : public UIWindow
{
	/* this+ 0 */ public: //UIWindow baseclass_0;
	/* this+72 */ public: float m_percent;
};
C_ASSERT( sizeof UIBarGraph == 76 );


class UIBarGraph2 : public UIBarGraph
{
	/* this+  0 */ public: //UIBarGraph baseclass_0;
	/* this+ 76 */ public: int m_isVertical;
	/* this+ 80 */ public: int m_backR;
	/* this+ 84 */ public: int m_backG;
	/* this+ 88 */ public: int m_backB;
	/* this+ 92 */ public: int m_r;
	/* this+ 96 */ public: int m_g;
	/* this+100 */ public: int m_b;
};
C_ASSERT( sizeof UIBarGraph2 == 104 );


class UIBarGraph3 : public UIWindow
{
	/* this+ 0 */ public: //UIWindow baseclass_0;
	/* this+72 */ public: const int* m_pAmount;
	/* this+76 */ public: const int* m_pTotalAmount;
};
C_ASSERT( sizeof UIBarGraph3 == 80 );


class UIBarGraph4 : public UIBarGraph3
{
	/* this+ 0 */ public: //UIBarGraph3 baseclass_0;
	/* this+80 */ public: bool m_bType;
};
C_ASSERT( sizeof UIBarGraph4 == 84 );
