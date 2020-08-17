#pragma once


class N3Inter
{
public:
	virtual void Receive(const unsigned int in_Msg, const unsigned int in_wParam, const unsigned int in_lParam) = 0;

public:
	N3Inter() { }
	virtual ~N3Inter() { }
};
