#pragma once
#include "Window/UIWindow.h"
#include "Struct.h" // NamePair, BOXINFO
#include "std/string"
#include "std/vector"


class UIBalloonText : public UIWindow
{
	/* this+  0 */ public: //UIWindow baseclass_0;
	/* this+ 72 */ protected: bool m_isBold;
	/* this+ 76 */ protected: int m_fontSize;
	/* this+ 80 */ protected: mystd::vector<mystd::string> m_strings;
	/* this+ 96 */ protected: COLORREF m_fontColor;
	/* this+100 */ protected: COLORREF m_bgColor;
	/* this+104 */ protected: bool m_isBack;
	/* this+106 */ protected: short m_charfont;

	public: UIBalloonText::UIBalloonText(void);
	public: virtual UIBalloonText::~UIBalloonText(void);
	public: virtual bool UIBalloonText::ShouldDoHitTest(void);
	public: virtual void UIBalloonText::OnProcess(void);
	public: virtual void UIBalloonText::OnDraw(void);
	public: void UIBalloonText::SetText(const char* msg, const int maxNumCharLine);
	public: void UIBalloonText::AddText(const char* msg);
	public: void UIBalloonText::SetFntColor(COLORREF fontColor, COLORREF bgColor);
	public: void UIBalloonText::SetFntSize(int fontSize);
	public: void UIBalloonText::SetBackTrans(bool isBack);
	protected: void UIBalloonText::AdjustSizeByText(void);
};
C_ASSERT( sizeof UIBalloonText == 108 );


class UINameBalloonText : public UIBalloonText
{
	/* this+  0 */ public: //UIBalloonText baseclass_0;
	/* this+108 */ mystd::string m_ebmResName;
	/* this+124 */ int m_textWidth;

	virtual UINameBalloonText::~UINameBalloonText(void);
	public: virtual void UINameBalloonText::SetNameText(const char* cName);
	public: virtual void UINameBalloonText::SetNameText(const NamePair& namePair, bool cutSharp);

private:
	static hook_func<void (UINameBalloonText::*)(const char* cName)> UINameBalloonText::_SetNameText2;
	static hook_func<void (UINameBalloonText::*)(const NamePair& namePair, bool cutSharp)> UINameBalloonText::_SetNameText;
};
C_ASSERT( sizeof UINameBalloonText == 128 );


class UITransBalloonText : public UIBalloonText
{
	/* this+  0 */ public: //UIBalloonText baseclass_0;
	/* this+108 */ private: BOXINFO m_transBoxInfo;
	/* this+136 */ private: mystd::vector<COLORREF> m_stringsColors;
	/* this+152 */ private: COLORREF m_borderLineColor;

	public: UITransBalloonText::UITransBalloonText(void);
	public: virtual UITransBalloonText::~UITransBalloonText(void);
	public: virtual void UITransBalloonText::Resize(int cx, int cy);
	public: virtual void UITransBalloonText::Move(int x, int y);
	public: virtual bool UITransBalloonText::GetTransBoxInfo(BOXINFO* boxInfo);
	public: virtual void UITransBalloonText::OnCreate(int cx, int cy);
	public: virtual void UITransBalloonText::OnDraw(void);
	public: void UITransBalloonText::SetTransBoxColor(COLORREF transboxColor);
	public: void UITransBalloonText::SetBorderLineColor(COLORREF borderLineColor);

	public: mystd::string UITransBalloonText::GetText(size_t index);
	public: void UITransBalloonText::ChangeText(const char* text, size_t index);
	public: void UITransBalloonText::SetText(const char* text, COLORREF color);
	public: void UITransBalloonText::AddText(const char* text, COLORREF color);
};
C_ASSERT( sizeof UITransBalloonText == 156 );
