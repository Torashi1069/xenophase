#pragma once


class N2Inter
{
public:
	virtual void PostInterMessage(const unsigned int in_FromInter, const int in_Msg, const int in_wParam, const int in_lParam) = 0;
	virtual bool PeekInterMessage(unsigned int& out_FromInter, int& out_Msg, int& out_wParam, int& out_lParam, const bool in_bRemove) = 0;

public:
	N2Inter() { }
	virtual ~N2Inter() { }
};
