#pragma once


class CTipOfTheDay
{
	/* this+0 */ protected: bool m_bTryLoading;
	/* this+4 */ protected: mystd::vector<mystd::vector<mystd::string>> m_tipList;

	public: CTipOfTheDay::CTipOfTheDay();
	public: CTipOfTheDay::~CTipOfTheDay();
	public: int CTipOfTheDay::Load();
	public: int CTipOfTheDay::Size();
	public: mystd::vector<mystd::string>& CTipOfTheDay::GetTip(int index);

private:
	static hook_func<int (CTipOfTheDay::*)()> CTipOfTheDay::_Load;
	static hook_func<int (CTipOfTheDay::*)()> CTipOfTheDay::_Size;
	static hook_func<mystd::vector<mystd::string>& (CTipOfTheDay::*)(int index)> CTipOfTheDay::_GetTip;
};
C_ASSERT( sizeof CTipOfTheDay == 20 );
