#include "CBink.h"


CBink::CBink(void) // line 15
{
	m_Bink = NULL;
	m_BinkBuffer = NULL;
	m_IsBinkPlaying = false;
}


hook_method<int (CBink::*)(BINK* bink, HWND window)> CBink::_BinkShowNextFrame(SAKEXE, "CBink::BinkShowNextFrame");
int CBink::BinkShowNextFrame(BINK* bink, HWND window) // line 22
{
	return (this->*_BinkShowNextFrame)(bink, window);

	//TODO
}


hook_method<void (CBink::*)(long microseconds)> CBink::_BinkGoodSleepUs(SAKEXE, "CBink::BinkGoodSleepUs");
void CBink::BinkGoodSleepUs(long microseconds) // line 64
{
	return (this->*_BinkGoodSleepUs)(microseconds);

	//TODO
}


hook_method<int (CBink::*)(void)> CBink::_InitOpenning(SAKEXE, "CBink::InitOpenning");
int CBink::InitOpenning(void) // line 121
{
	return (this->*_InitOpenning)();

	//TODO
}


hook_method<int (CBink::*)(void)> CBink::_CloseOpenning(SAKEXE, "CBink::CloseOpenning");
int CBink::CloseOpenning(void) // line 137
{
	return (this->*_CloseOpenning)();

	//TODO
}


hook_method<int (CBink::*)(void)> CBink::_ReadBinkModeRegistry(SAKEXE, "CBink::ReadBinkModeRegistry");
int CBink::ReadBinkModeRegistry(void) // line 176
{
	return (this->*_ReadBinkModeRegistry)();

	//TODO
}


hook_method<int (CBink::*)(void)> CBink::_WriteBinkModeRegistry(SAKEXE, "CBink::WriteBinkModeRegistry");
int CBink::WriteBinkModeRegistry(void) // line 193
{
	return (this->*_WriteBinkModeRegistry)();

	//TODO
}


hook_method<int (CBink::*)(unsigned short param)> CBink::_Break(SAKEXE, "CBink::Break");
int CBink::Break(unsigned short param) // line 159
{
	return (this->*_Break)(param);

	//TODO
}


hook_method<void (CBink::*)(int flag)> CBink::_Pause(SAKEXE, "CBink::Pause");
void CBink::Pause(int flag) // line 171
{
	return (this->*_Pause)(flag);

	//TODO
}


//hook_method<bool (CBink::*)(void)> CBink::_IsBinkPlaying(SAKEXE, "CBink::IsBinkPlaying");
bool CBink::IsBinkPlaying(void)
{
//	return (this->*_IsBinkPlaying)();

	return m_IsBinkPlaying;
}


hook_method<void (CBink::*)(int flag)> CBink::_OpenningMain(SAKEXE, "CBink::OpenningMain");
void CBink::OpenningMain(int flag) // line 209
{
	return (this->*_OpenningMain)(flag);

	//TODO
}
