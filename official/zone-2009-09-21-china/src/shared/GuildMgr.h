#pragma once
#include "Guild.h"
#include "std/map"


class CGuildMgr
{
public:
	struct vtable_t // const CGuildMgr::`vftable'
	{
		void* (CGuildMgr::* vector_deleting_destructor)(unsigned int flags);
		void (CGuildMgr::* Init)(void);
	};

	/* this+0 */ public: //const CGuildMgr::`vftable';
	/* this+4 */ protected: mystd::map<unsigned long,CGuild*> m_guildInfo;

	public: CGuildMgr::CGuildMgr(void);
	public: virtual CGuildMgr::~CGuildMgr(void);
	public: virtual void CGuildMgr::Init(void);
	public: CGuild* CGuildMgr::SearchGuild(unsigned long GDID);
	public: void CGuildMgr::ClearGuildInfo(void);
	public: int CGuildMgr::AddGuild(CGuild* guild);
	public: unsigned long CGuildMgr::GetGuildSize(void);

private:
	static hook_method<void (CGuildMgr::*)(void)> CGuildMgr::_Init;
	static hook_method<CGuild* (CGuildMgr::*)(unsigned long GDID)> CGuildMgr::_SearchGuild;
	static hook_method<void (CGuildMgr::*)(void)> CGuildMgr::_ClearGuildInfo;
	static hook_method<int (CGuildMgr::*)(CGuild* guild)> CGuildMgr::_AddGuild;
	static hook_method<unsigned long (CGuildMgr::*)(void)> CGuildMgr::_GetGuildSize;
};
