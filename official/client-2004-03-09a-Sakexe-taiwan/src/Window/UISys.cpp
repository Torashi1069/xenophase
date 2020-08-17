#include "Globals.h"
#include "3dLib/DrawUtil.h"
#include "Window/UISys.h"


int __cdecl UIX(int x) // line 1771-1773 (UISys.h)
{
	return x + (g_renderer->CRenderer::GetWidth() - 640) / 2;
}


int __cdecl UIY(int y) // line ????-????
{
	return y + (g_renderer->CRenderer::GetHeight() - 480) / 2;
}


int __cdecl UICY(int y) // line 1786-1788 (UISys.h)
{
	return y * g_renderer->CRenderer::GetHeight() / 480;
}


hook_func<void (__cdecl *)(const char* msg, mystd::vector<mystd::string>& strings, int maxNumCharLine)> _CutString(SAKEXE, "CutString");
void __cdecl CutString(const char* msg, mystd::vector<mystd::string>& strings, int maxNumCharLine) // line 12-43
{
	return (_CutString)(msg, strings, maxNumCharLine);

	const char* const msg_end = &msg[strlen(msg)];
	const char* const msg_charset = &msg[FindCharSet(msg, msg_end - msg)];

	const char* pLine = msg;
	const char* pWord = msg;
	const char* pChar = msg;

	while( pChar < msg_end )
	{
		pChar = g_language->GetWordBreak(pChar, msg_end - pChar);

		while( *pChar++ == ' ' )
			pWord = pChar;

		if( pChar >= pLine + maxNumCharLine )
		{
			if( pLine < pWord )
			{
				strings.push_back(mystd::string(pLine, pWord));
				pLine = pWord;
			}
			else
			{
				strings.push_back(mystd::string(pLine, pChar));
				pLine = pChar;
			}
		}
	}

	if( pLine < pChar )
		strings.push_back(mystd::string(pLine, pChar));

	if( msg_charset < msg_end )
	{
		for( size_t i = 1; i < strings.size(); ++i )
		{
			mystd::string& p = strings[i];
			p.insert(p.begin(), msg_charset, msg_charset+3); //inlined
		}
	}
}


hook_func<void (__cdecl *)(const char* msg, mystd::vector<mystd::string>& strings, int maxNumCharLine, bool readCR)> _CutStringWithColor(SAKEXE, "CutStringWithColor");
void __cdecl CutStringWithColor(const char* msg, mystd::vector<mystd::string>& strings, int maxNumCharLine, bool readCR) // line 46-83
{
	return (_CutStringWithColor)(msg, strings, maxNumCharLine, readCR);

	//TODO
}


////////////////////////////////////////


CSnapInfo::CSnapInfo() // line ???-???
{
}


void CSnapInfo::SetInfo(int x, int y, int w, int h) // line 766-782
{
	m_info[0].points[0] = x;     m_info[0].points[1] = y; m_info[0].points[2] = y + h;
	m_info[1].points[0] = x + w; m_info[1].points[1] = y; m_info[1].points[2] = y + h;
	m_info[2].points[0] = y;     m_info[2].points[1] = x; m_info[2].points[2] = x + w;
	m_info[3].points[0] = y + h; m_info[3].points[1] = x; m_info[3].points[2] = x + w;
}


void CSnapInfo::Reverse() // line 785-794
{
	#define swap(a,b) { int tmp = a; a = b; b = tmp; }
	swap(m_info[0].points[0], m_info[1].points[0]);
	swap(m_info[0].points[1], m_info[1].points[1]);
	swap(m_info[0].points[2], m_info[1].points[2]);
	swap(m_info[2].points[0], m_info[3].points[0]);
	swap(m_info[2].points[1], m_info[3].points[1]);
	swap(m_info[2].points[2], m_info[3].points[2]);
	#undef swap
}


bool CSnapInfo::IsOverLapped(int s1, int d1, int s2, int d2) // line 797-807
{
	return ( s2 >= s1 && s2 <= d1
	      || d2 >= s1 && d2 <= d1
	      || s1 >= s2 && s1 <= d2
	      || d1 >= s2 && d1 <= d2 );
}


hook_func<void (CSnapInfo::*)(CSnapInfo* snapInfo, int& dx, int& dy)> CSnapInfo::_GetDeltaSnap(SAKEXE, "CSnapInfo::GetDeltaSnap");
void CSnapInfo::GetDeltaSnap(CSnapInfo* snapInfo, int& dx, int& dy) // line 810-878
{
	return (this->*_GetDeltaSnap)(snapInfo, dx, dy);

	//TODO
}
