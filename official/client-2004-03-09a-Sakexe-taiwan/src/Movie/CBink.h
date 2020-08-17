#pragma once
#include "bink.h"


class CBink
{
	/* this+ 0 */ protected: BINK* m_Bink;
	/* this+ 4 */ protected: BINKBUFFER* m_BinkBuffer;
	/* this+ 8 */ protected: bool m_IsBinkPlaying;
	/* this+12 */ protected: int m_BinkMode;

	public: CBink::CBink(void);
	protected: int CBink::BinkShowNextFrame(BINK* bink, HWND window);
	protected: void CBink::BinkGoodSleepUs(long microseconds);
	protected: int CBink::InitOpenning(void);
	protected: int CBink::CloseOpenning(void);
	protected: int CBink::ReadBinkModeRegistry(void);
	protected: int CBink::WriteBinkModeRegistry(void);
	public: int CBink::Break(unsigned short param);
	public: void CBink::Pause(int flag);
	public: bool CBink::IsBinkPlaying(void);
	public: void CBink::OpenningMain(int flag);

private:
	static hook_method<int (CBink::*)(BINK* bink, HWND window)> CBink::_BinkShowNextFrame;
	static hook_method<void (CBink::*)(long microseconds)> CBink::_BinkGoodSleepUs;
	static hook_method<int (CBink::*)(void)> CBink::_InitOpenning;
	static hook_method<int (CBink::*)(void)> CBink::_CloseOpenning;
	static hook_method<int (CBink::*)(void)> CBink::_ReadBinkModeRegistry;
	static hook_method<int (CBink::*)(void)> CBink::_WriteBinkModeRegistry;
	static hook_method<int (CBink::*)(unsigned short param)> CBink::_Break;
	static hook_method<void (CBink::*)(int flag)> CBink::_Pause;
	static hook_method<bool (CBink::*)(void)> CBink::_IsBinkPlaying;
	static hook_method<void (CBink::*)(int flag)> CBink::_OpenningMain;
};
