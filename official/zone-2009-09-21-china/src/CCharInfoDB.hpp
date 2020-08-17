#pragma once
#include "MannerPointInfo.hpp"
#include "ODBC.h"
#include "struct.hpp"
#include "std/list"


class CCharInfoDB : public CODBC
{
public:
	public: CCharInfoDB::CCharInfoDB(void);
	public: virtual CCharInfoDB::~CCharInfoDB(void);
	public: void CCharInfoDB::UpdateItemStoreMoney(int AID, int money);
	public: void CCharInfoDB::DeleteItem(int GID);
	public: void CCharInfoDB::InsertWarpInfo(int GID);
	public: void CCharInfoDB::UpdateWarpInfo(int GID, WARPPORTAL_INFO* warpInfo);
	public: int CCharInfoDB::GetWarpInfo(int GID, WARPPORTAL_INFO* warpInfo);
	public: void CCharInfoDB::GetCharacterName(int GID, char* charname);
	public: int CCharInfoDB::LoadMPInfo(unsigned long AID, mystd::list<MannerPointData>* info, int& LastDate);
	public: void CCharInfoDB::DeleteMP(unsigned long AID, unsigned long otherGID);
	public: int CCharInfoDB::InsertNewMP(unsigned long AID, unsigned long otherGID, int type);
	public: int CCharInfoDB::GetCharacterID(char* Name, unsigned long& AID, unsigned long& GID);
	public: int CCharInfoDB::UpdatePVPEvent(char* GID, char* Name);
	public: int CCharInfoDB::GetPVPEvent(char* GID, char* Name);
	public: void CCharInfoDB::GetErrorString(void* hStmt, char* lpszError);
	public: int CCharInfoDB::GetShortCutKey(unsigned long GID, unsigned char* pShortCutKey);
	public: int CCharInfoDB::UpdateShortCutKey(unsigned long GID, unsigned char* pShortCutKey);
	private: int CCharInfoDB::InsertHuntingList(int GID);
	private: int CCharInfoDB::InsertTimeList(int GID);
	public: int CCharInfoDB::SelectHuntingList(unsigned long GID, unsigned char* buf);
	public: int CCharInfoDB::UpdateHuntingList(unsigned long GID, unsigned char* buf, int size);
	public: int CCharInfoDB::SelectTimeList(unsigned long GID, unsigned char* buf);
	public: int CCharInfoDB::UpdateTimeList(unsigned long GID, unsigned char* buf, int size);

private:
	static hook_method<void (CCharInfoDB::*)(int AID, int money)> CCharInfoDB::_UpdateItemStoreMoney;
	static hook_method<void (CCharInfoDB::*)(int GID)> CCharInfoDB::_DeleteItem;
	static hook_method<void (CCharInfoDB::*)(int GID)> CCharInfoDB::_InsertWarpInfo;
	static hook_method<void (CCharInfoDB::*)(int GID, WARPPORTAL_INFO* warpInfo)> CCharInfoDB::_UpdateWarpInfo;
	static hook_method<int (CCharInfoDB::*)(int GID, WARPPORTAL_INFO* warpInfo)> CCharInfoDB::_GetWarpInfo;
	static hook_method<void (CCharInfoDB::*)(int GID, char* charname)> CCharInfoDB::_GetCharacterName;
	static hook_method<int (CCharInfoDB::*)(unsigned long AID, mystd::list<MannerPointData>* info, int& LastDate)> CCharInfoDB::_LoadMPInfo;
	static hook_method<void (CCharInfoDB::*)(unsigned long AID, unsigned long otherGID)> CCharInfoDB::_DeleteMP;
	static hook_method<int (CCharInfoDB::*)(unsigned long AID, unsigned long otherGID, int type)> CCharInfoDB::_InsertNewMP;
	static hook_method<int (CCharInfoDB::*)(char* Name, unsigned long& AID, unsigned long& GID)> CCharInfoDB::_GetCharacterID;
	static hook_method<int (CCharInfoDB::*)(char* GID, char* Name)> CCharInfoDB::_UpdatePVPEvent;
	static hook_method<int (CCharInfoDB::*)(char* GID, char* Name)> CCharInfoDB::_GetPVPEvent;
	static hook_method<void (CCharInfoDB::*)(void* hStmt, char* lpszError)> CCharInfoDB::_GetErrorString;
	static hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* pShortCutKey)> CCharInfoDB::_GetShortCutKey;
	static hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* pShortCutKey)> CCharInfoDB::_UpdateShortCutKey;
	static hook_method<int (CCharInfoDB::*)(int GID)> CCharInfoDB::_InsertHuntingList;
	static hook_method<int (CCharInfoDB::*)(int GID)> CCharInfoDB::_InsertTimeList;
	static hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* buf)> CCharInfoDB::_SelectHuntingList;
	static hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* buf, int size)> CCharInfoDB::_UpdateHuntingList;
	static hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* buf)> CCharInfoDB::_SelectTimeList;
	static hook_method<int (CCharInfoDB::*)(unsigned long GID, unsigned char* buf, int size)> CCharInfoDB::_UpdateTimeList;
};
