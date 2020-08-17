#pragma once
#include "ScriptLib/BinBuf.h"
#include "CBuffInfo.hpp"
#include "std/map"
#include "std/string"


class CBuffInfoMgr
{
public:
	/* this+0x0  */ mystd::map<int,CBuffInfo *> m_buffInfoMap;
	/* this+0xC  */ mystd::map<mystd::string,int> m_buffInfoNames;
	/* this+0x18 */ CBinBuf m_binBuf;

	public: CBuffInfoMgr::CBuffInfoMgr(void);
	public: CBuffInfoMgr::~CBuffInfoMgr(void);
	public: bool CBuffInfoMgr::Create(void);
	public: bool CBuffInfoMgr::InitBuffScript(void);
	public: CBuffInfo* CBuffInfoMgr::GetBuffInfo(const char* buffName);
	public: CBuffInfo* CBuffInfoMgr::GetBuffInfo(int buffType);
	public: bool CBuffInfoMgr::IsSendPacket(int buffType);
	public: bool CBuffInfoMgr::RunBuffScript(unsigned long aid, int eventType, int buffType);
	public: int CBuffInfoMgr::GetBuffType(const char* buffName);
	private: CBuffInfo* CBuffInfoMgr::AddBuffInfo(int buffType, const char* buffName);
	private: CBuffInfo* CBuffInfoMgr::AddBuffInfoWithScript(int buffTYpe, const char* buffName);
	private: void CBuffInfoMgr::Reset(void);

private:
	static hook_method<bool (CBuffInfoMgr::*)(void)> CBuffInfoMgr::_Create;
	static hook_method<bool (CBuffInfoMgr::*)(void)> CBuffInfoMgr::_InitBuffScript;
	static hook_method<CBuffInfo* (CBuffInfoMgr::*)(const char* buffName)> CBuffInfoMgr::_GetBuffInfo;
	static hook_method<CBuffInfo* (CBuffInfoMgr::*)(int buffType)> CBuffInfoMgr::_GetBuffInfo2;
	static hook_method<bool (CBuffInfoMgr::*)(int buffType)> CBuffInfoMgr::_IsSendPacket;
	static hook_method<bool (CBuffInfoMgr::*)(unsigned long aid, int eventType, int buffType)> CBuffInfoMgr::_RunBuffScript;
	static hook_method<int (CBuffInfoMgr::*)(const char* buffName)> CBuffInfoMgr::_GetBuffType;
	static hook_method<CBuffInfo* (CBuffInfoMgr::*)(int buffType, const char* buffName)> CBuffInfoMgr::_AddBuffInfo;
	static hook_method<CBuffInfo* (CBuffInfoMgr::*)(int buffTYpe, const char* buffName)> CBuffInfoMgr::_AddBuffInfoWithScript;
	static hook_method<void (CBuffInfoMgr::*)(void)> CBuffInfoMgr::_Reset;
};
