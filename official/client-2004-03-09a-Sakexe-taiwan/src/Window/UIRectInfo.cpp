#include "Globals.h"
#include "Window/UIRectInfo.h"


////////////////////////////////////////


hook_method<void (BasicInfoWndInfo::*)(void)> BasicInfoWndInfo::_MakeDefault(SAKEXE, "BasicInfoWndInfo::MakeDefault");
void BasicInfoWndInfo::MakeDefault(void) // line 62
{
	return (this->*_MakeDefault)();

	//TODO
}


hook_method<int (BasicInfoWndInfo::*)(void)> BasicInfoWndInfo::_IsValidInfo(SAKEXE, "BasicInfoWndInfo::IsValidInfo");
int BasicInfoWndInfo::IsValidInfo(void) // line 49
{
	return (this->*_IsValidInfo)();

	//TODO
}


////////////////////////////////////////


hook_method<void (GuildWndInfo::*)(void)> GuildWndInfo::_MakeDefault(SAKEXE, "GuildWndInfo::MakeDefault");
void GuildWndInfo::MakeDefault(void) // line 193
{
	return (this->*_MakeDefault)();

	this->x = 0;
	this->y = 34;
	this->w = guildWndWidth;
	this->h = guildWndHeight;
	this->curTab = 0;
}


hook_method<int (GuildWndInfo::*)(void)> GuildWndInfo::_IsValidInfo(SAKEXE, "GuildWndInfo::IsValidInfo");
int GuildWndInfo::IsValidInfo(void) // line 202
{
	return (this->*_IsValidInfo)();

	return this->w == guildWndWidth
	    && this->h == guildWndHeight
	    && this->x >= 0
		&& this->x <= g_renderer->CRenderer::GetWidth() - this->w
	    && this->y >= 0
		&& this->y <= g_renderer->CRenderer::GetHeight() - this->h
	    && this->curTab >= 0
	    && this->curTab < 7;
}


////////////////////////////////////////


BOOL EquipWndInfo::IsValidInfo() // 264-276
{
	return this->w == 280
	    && ( this->h == 147 || this->h == 17 )
	    && this->orgHeight == 147
	    && this->x >= 0
	    && this->x <= g_renderer->CRenderer::GetWidth() - this->w
	    && this->y >= 0
	    && this->y <= g_renderer->CRenderer::GetHeight() - this->h;
}


void EquipWndInfo::MakeDefault() // 279-286
{
	this->x = 185;
	this->y = 300;
	this->w = 280;
	this->h = 147;
	this->orgHeight = 147;
	this->show = 0;
}


////////////////////////////////////////


hook_method<void (MessengerGroupWndInfo::*)(void)> MessengerGroupWndInfo::_MakeDefault(SAKEXE, "MessengerGroupWndInfo::MakeDefault");
void MessengerGroupWndInfo::MakeDefault(void) // line 380
{
	return (this->*_MakeDefault)();

	//TODO
}


hook_method<int (MessengerGroupWndInfo::*)(void)> MessengerGroupWndInfo::_IsValidInfo(SAKEXE, "MessengerGroupWndInfo::IsValidInfo");
int MessengerGroupWndInfo::IsValidInfo(void) // line 389
{
	return (this->*_IsValidInfo)();

	//TODO
}


////////////////////////////////////////


BOOL WhisperWndInfo::IsValidInfo() // line 449-459
{
    return ( this->w >= 280 && this->h >= 120
	      && this->x >= 0 && this->x <= g_renderer->CRenderer::GetWidth() - this->w
	      && this->y >= 0 && this->y <= g_renderer->CRenderer::GetHeight() - this->h );
}


void WhisperWndInfo::MakeDefault() // line 462-467
{
	this->w = 280;
	this->h = 120;
	this->x = 0;
	this->y = 347;
}


////////////////////////////////////////


hook_method<void (ShortCutWndInfo::*)(void)> ShortCutWndInfo::_MakeDefault(SAKEXE, "ShortCutWndInfo::MakeDefault");
void ShortCutWndInfo::MakeDefault(void) // line 535
{
	return (this->*_MakeDefault)();

	this->x = 185;
	this->y = 300;
	this->w = 280;
	this->h = 34;
	this->show = 0;
}


hook_method<int (ShortCutWndInfo::*)(void)> ShortCutWndInfo::_IsValidInfo(SAKEXE, "ShortCutWndInfo::IsValidInfo");
int ShortCutWndInfo::IsValidInfo(void) // line 522
{
	return (this->*_IsValidInfo)();

	return ( this->w == 280 && this->h == 34
	      && this->x >= 0 && this->x <= g_renderer->CRenderer::GetWidth() - 280
	      && this->y >= 0 && this->y <= g_renderer->CRenderer::GetHeight() - 34 );
}


////////////////////////////////////////


hook_method<void (MerchantItemShopWndInfo::*)(void)> MerchantItemShopWndInfo::_MakeDefault(SAKEXE, "MerchantItemShopWndInfo::MakeDefault");
void MerchantItemShopWndInfo::MakeDefault(void) // line 654
{
	return (this->*_MakeDefault)();

	//TODO
}


hook_method<int (MerchantItemShopWndInfo::*)(void)> MerchantItemShopWndInfo::_IsValidInfo(SAKEXE, "MerchantItemShopWndInfo::IsValidInfo");
int MerchantItemShopWndInfo::IsValidInfo(void) // line 661
{
	return (this->*_IsValidInfo)();

	//TODO
}


////////////////////////////////////////


void FriendOptionWndInfo::MakeDefault() // line 719-724
{
	this->x = 200;
	this->y = 120;
	this->w = 280;
	this->h = 120;
}


BOOL FriendOptionWndInfo::IsValidInfo() // line 727-737
{
	return ( this->w == 280 && this->h == 120
	      && this->x >= 0 && this->x <= g_renderer->CRenderer::GetWidth() - 280
	      && this->y >= 0 && this->y <= g_renderer->CRenderer::GetHeight() - 120 );
}


////////////////////////////////////////
