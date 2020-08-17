#pragma once


class CBink
{
	public: void CBink::OpenningMain(int flag);

public:
	static hook_func<void (CBink::*)(int flag)> CBink::_OpenningMain;
};


extern CBink& g_Bink;
