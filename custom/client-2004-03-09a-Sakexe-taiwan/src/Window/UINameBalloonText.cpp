#include "Globals.h"
#include "ModeMgr.h"
#include "Base/ResMgr.h"
#include "Resource/Emblem.h"
#include "Window/UINameBalloonText.h"


UINameBalloonText::UINameBalloonText() // line 934-947 (UIControl.cpp)
{
	m_bgColor = 0;
	m_textWidth = 0;
	m_isBack = false;
}


UINameBalloonText::~UINameBalloonText() // line 950-954 (UIControl.cpp)
{
}


void UINameBalloonText::OnDraw() // line 1065-1087 (UIControl.cpp)
{
	this->UIWindow::ClearDC(0xFFFF00FF);

	int x = 4;
	int y = 4;

	if( m_ebmResName.size() != 0 && g_resMgr().CResMgr::IsExist(m_ebmResName.c_str()) )
	{
		CEmblemRes* emblem = (CEmblemRes*)g_resMgr().CResMgr::Get(m_ebmResName.c_str());
		if( emblem != NULL )
		{
			g_modeMgr.CModeMgr::GetGameMode();
			this->UIWindow::DrawBitmap(4, (m_h - 24) / 2, emblem->CEmblemRes::GetBitmap(), true);
			x = 32;
		}
	}

	for( mystd::vector<mystd::string>::iterator it = m_strings.begin(); it != m_strings.end(); ++it )
	{
		this->UIWindow::TextOutWithOutline(x, y, it->c_str(), it->size(), m_fontColor, m_bgColor, 0, NameBalloonfontSize, NameBalloonfontBold);
		y += NameBalloonfontSize + 2;
	}
}


void UINameBalloonText::SetEmblemResName(const char* EmblemResName) // line 1090-1100 (UIControl.cpp)
{
	if( EmblemResName == NULL )
		return;

	m_ebmResName = EmblemResName;

	if( m_ebmResName.size() != 0 )
	{
		int y = m_h;
		if( y <= 24 )
			y = 24;

		this->Resize(m_textWidth + 25, y);
	}

	this->Invalidate();
}


void UINameBalloonText::SetNameText(const char* cName) // line 966-991 (UIControl.cpp)
{
	if( m_strings.size() != 0 && m_strings.front() == cName )
		return; // already holds something, assume no change needed

	m_strings.clear();
	m_strings.push_back(cName);

	m_textWidth = max(32, 8 + this->UIWindow::GetTextWidth(m_strings.back().c_str(), m_strings.back().size(), 0, NameBalloonfontSize, NameBalloonfontBold));

	this->Resize(m_textWidth, 8 + NameBalloonfontSize);
	this->Invalidate();
}


void UINameBalloonText::SetNameText(const NamePair& namePair, bool cutSharp) // line 994-1060 (UIControl.cpp)
{
	m_strings.clear();

	mystd::string cName = namePair.cName;

	if( cutSharp )
	{
		size_t pos = cName.find('#');
		if( pos != cName.npos )
			cName.resize(pos);
	}

	if( NameBalloonShorten )
	{
		m_textWidth = 0;

		if( namePair.rName[0] != '\0' )
		{
			m_strings.push_back(namePair.rName.c_str());
			m_textWidth = max(32, 8 + this->UIWindow::GetTextWidth(m_strings.back().c_str(), m_strings.back().size(), 0, NameBalloonfontSize, NameBalloonfontBold));
		}

		m_strings.push_back(cName.c_str());
		m_textWidth = max(m_textWidth, 8 + this->UIWindow::GetTextWidth(m_strings.back().c_str(), 0, 0, NameBalloonfontSize, NameBalloonfontBold));
	}
	else
	{
		char Dest[256];

		if( namePair.pName[0] != '\0' )
		{
			const char* format = ( g_serviceType != ServiceKorea ) ? "%s [%s]" : "%s『%s』";
			sprintf(Dest, format, cName.c_str(), namePair.pName.c_str());
			m_strings.push_back(Dest);
		}
		else
		{
			m_strings.push_back(cName.c_str());
		}

		m_textWidth = max(32, 8 + this->UIWindow::GetTextWidth(m_strings.back().c_str(), m_strings.back().size(), 0, NameBalloonfontSize, NameBalloonfontBold));

		if( namePair.gName[0] != '\0' )
		{
			const char* format = ( g_serviceType != ServiceKorea ) ? "%s [%s]" : "%s『%s』";
			sprintf(Dest, format, namePair.gName.c_str(), namePair.rName.c_str());
			m_strings.push_back(Dest);

			m_textWidth = max(m_textWidth, 8 + this->UIWindow::GetTextWidth(m_strings.back().c_str(), 0, 0, NameBalloonfontSize, NameBalloonfontBold));
		}
	}

	this->Resize(m_textWidth, 6 + (2 + NameBalloonfontSize) * m_strings.size());
	this->Invalidate();
}
