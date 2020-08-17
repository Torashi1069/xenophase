#include "Globals.h"
#include "Skin.h"
#include "Window/UISys.h"
#include "Window/UIScrollBar.h"
#include "Window/UITextViewer.h"


UITextViewer::UITextViewer() // line 1335-1343 (UIControl2.cpp)
{
	m_itemSpacing = 18;
	m_noColor = false;

	unsigned long rr, gg, bb;
	g_skinMgr.CSkinMgr::GetColorChipColor(18, 2, rr, gg, bb);
	m_bgR = rr;
	m_bgG = gg;
	m_bgB = bb;
}


UITextViewer::~UITextViewer() // line 1346-1347 (UIControl2.cpp)
{
}


void UITextViewer::Create2(int x, int y, int cx, int cy, bool trans) // line 1350-1352 (UIControl2.cpp)
{
	this->UIListBox::Create2(x, y, cx, cy, trans); // inlined
}


void UITextViewer::OnCreate(int cx, int cy) // line 1355-1357 (UIControl2.cpp)
{
	this->UIListBox::OnCreate(cx, cy);
}


void UITextViewer::OnLBtnDown(int x, int y) // line 920 (Window/UISys.h)
{
}


void UITextViewer::OnLBtnDblClk(int x, int y) // line 921 (Window/UISys.h)
{
}


void UITextViewer::OnLBtnUp(int x, int y) // line 922 (Window/UISys.h)
{
}


void UITextViewer::OnDraw() // line 1360-1388 (UIControl2.cpp)
{
	COLORREF clearColor = BYTE(m_bgR) << 0 | BYTE(m_bgG) << 8 | BYTE(m_bgB) << 16;
	this->UIWindow::ClearDC(clearColor);

	int lastItem = min(m_h / m_itemSpacing - m_horzScrEnabled + m_vertViewOffset, (int)m_items.size());

	COLORREF colorRef = 0;
	for( int i = 0; i < m_vertViewOffset; ++i )
	{
		const char* textptr = m_items[i].c_str();
		const char* textend = textptr + m_items[i].size();
		const char* colorptr;

		while( textptr < textend )
		{
			colorptr = this->UIWindow::FindColorMark(textptr, textend);
			textptr = this->UIWindow::InterpretColor(colorptr, &colorRef);
		}
	}

	if( m_noColor )
	{
		for( int i = m_vertViewOffset; i < lastItem; ++i )
		{
			this->UIWindow::TextOutWithOutline(3, (i - m_vertViewOffset) * m_itemSpacing + 4, m_items[i].c_str(), m_items[i].size(), 0, 0xFFFFFF, 0, 12, false);
		}
	}
	else
	{
		for( int i = m_vertViewOffset; i < lastItem; ++i )
		{
			this->UIWindow::TextOutWithDecoration(3, (i - m_vertViewOffset) * m_itemSpacing + 4, m_items[i].c_str(), m_items[i].size(), &colorRef, 0, 12);
		}
	}
}


int UITextViewer::SendMsg(UIWindow* sender, int message, int val1, int val2, int val3) // line 1391-1439 (UIControl2.cpp)
{
	switch( message )
	{
	case UM_UPPUSH:
	{
		if( m_vertScrEnabled )
			this->SendMsg(m_vertScrollBar, UM_SCROLLVERT, -1, 0, 0);
	}
	break;
	case UM_DOWNPUSH:
	{
		if( m_vertScrEnabled )
			this->SendMsg(m_vertScrollBar, UM_SCROLLVERT, 1, 0, 0);
	}
	break;
	case UM_SETTEXT:
	{
		const char* msg = (const char*)val1;
		int maxNumCharLine = (int)val2;
		bool readCR = (bool)!!val3;

		if( maxNumCharLine == 0 )
			maxNumCharLine = 35;

		if( val2 == 138 )
		{
			mystd::vector<mystd::string> strings;
			CutString(msg, strings, 38);

			for( size_t i = 0; i < strings.size(); ++i )
				this->AddItem(strings[i].c_str());

			m_noColor = true;
		}
		else
		{
			mystd::vector<mystd::string> strings;
			CutStringWithColor(msg, strings, maxNumCharLine, readCR);

			for( size_t i = 0; i < strings.size(); ++i )
				this->AddItem(strings[i].c_str());

			m_noColor = false;
		}

		this->Invalidate();
	}
	break;
	default:
	{
		return this->UIListBox::SendMsg(sender, message, val1, val2, val3);
	}
	break;
	};

	return 0;
}
