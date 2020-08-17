#pragma once
#include "Guild.h"
#include "std/map"


class CGuildMgr
{
	struct vtable_t
	{
		void* (CGuildMgr::* vector_deleting_destructor)(unsigned int);
		void (CGuildMgr::* Init)(void);
	};

	/* this+0x0 */ //const CGuildMgr::`vftable'
	/* this+0x4 */ protected: mystd::map<unsigned long,CGuild*> m_guildInfo;

	public: CGuild* CGuildMgr::SearchGuild(unsigned long GDID);
	public: CGuildMgr::CGuildMgr(void);
	public: virtual CGuildMgr::~CGuildMgr(void);
	public: virtual void CGuildMgr::Init(void);
	public: void CGuildMgr::ClearGuildInfo(void);
	//public: int CGuildMgr::AddGuild(class CGuild *);
	public: unsigned long CGuildMgr::GetGuildSize(void);

private:
	static hook_method<CGuild* (CGuildMgr::*)(unsigned long GDID)> CGuildMgr::_SearchGuild;
	static hook_method<void (CGuildMgr::*)(void)> CGuildMgr::_Init;
	static hook_method<void (CGuildMgr::*)(void)> CGuildMgr::_ClearGuildInfo;
	static hook_method<unsigned long (CGuildMgr::*)(void)> CGuildMgr::_GetGuildSize;
};
