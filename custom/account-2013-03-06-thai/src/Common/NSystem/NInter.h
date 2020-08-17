#pragma once


class NInter
{
public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam) = 0;

public:
	NInter() { };
	virtual ~NInter() { };
};
