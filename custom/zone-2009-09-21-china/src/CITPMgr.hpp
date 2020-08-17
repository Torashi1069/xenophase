#pragma once
#include "CITP.hpp"
#include "ODBC.h"
#include "std/map"
#include "std/string"
#include "std/vector"


class CITPMgr : public CODBC
{
	/* this+0x0  */ public: //CODBC baseclass_0;
	/* this+0x14 */ private: mystd::map<unsigned short,CITP *> m_itp;
	/* this+0x20 */ private: mystd::map<mystd::string,unsigned short> m_itemName;
	/* this+0x2C */ private: mystd::map<mystd::string,unsigned long> m_effect;
	/* this+0x38 */ private: mystd::map<unsigned short,mystd::vector<unsigned short> > m_combiItem;
	/* this+0x44 */ private: mystd::map<unsigned short,unsigned short> m_scrollItem;

	typedef mystd::map<unsigned short,CITP*> ITEMPROTOTYPEMAP;
	typedef ITEMPROTOTYPEMAP::const_iterator ITEMPROTOTYPEMAP_ITER;
	typedef mystd::map<mystd::string,unsigned short> ITEMNAMEIDXMAP;
	typedef ITEMNAMEIDXMAP::const_iterator ITEMNAMEIDXMAP_ITER;

	public: CITPMgr::CITPMgr(void);
	public: virtual CITPMgr::~CITPMgr(void);
	public: bool CITPMgr::Save(const char* fName);
	public: void CITPMgr::Init(const char* Script);
	public: void CITPMgr::LoadITP(void);
	public: mystd::map<mystd::string,unsigned short>& CITPMgr::GetNameMap(void);
	public: mystd::map<unsigned short,mystd::vector<unsigned short> >& CITPMgr::GetCombiItemList(void);
	public: void CITPMgr::InsertITP(void);
	public: CITP* CITPMgr::GetITP(unsigned short ITID);
	public: enum enumInventoryItemType CITPMgr::GetInventoryItemType(const unsigned short in_ITID);
	public: unsigned long CITPMgr::GetEffectID(const char* effectName);
	public: unsigned short CITPMgr::GetITID(const char* itemName);
	public: int CITPMgr::FindITID(const char* itemName, unsigned long* pItemIDList);
	public: short CITPMgr::GetItemWeight(unsigned short ITID);
	public: int CITPMgr::IsApparel(unsigned short ITID);
	public: int CITPMgr::IsCashPointItem(unsigned short ITID);
	public: char* CITPMgr::GetItemName(unsigned short ITID);
	public: void CITPMgr::DBClose(void);
	public: bool CITPMgr::IsScrollItem(unsigned short ITID);
	private: void CITPMgr::GetQuest(void);
	private: void CITPMgr::GetArmor(unsigned long type);
	private: void CITPMgr::GetCannonball(void);
	private: void CITPMgr::GetArrow(void);
	private: void CITPMgr::GetAmmo(void);
	private: void CITPMgr::GetGun(void);
	private: void CITPMgr::GetWeapon(void);
	private: void CITPMgr::GetBothhand(void);
	private: void CITPMgr::GetBow(void);
	private: void CITPMgr::GetEvent(void);
	private: void CITPMgr::GetSpecial(void);
	private: void CITPMgr::GetHeal(void);
	private: void CITPMgr::GetCard(void);
	private: void CITPMgr::GetCashPointItem(void);
	private: void CITPMgr::GetThrowWeapon(void);
	private: void CITPMgr::LoadItemMoveInfo(void);
	private: bool CITPMgr::LoadCashItemList(void);
	private: int CITPMgr::LoadCombiItemList(const char* fileName);
	private: void CITPMgr::LoadScrollItemList(void);
	private: void CITPMgr::LoadItemBindOnEquip(void);
	private: int CITPMgr::AddITP(CITP* itp);

private:
	static hook_method<bool (CITPMgr::*)(const char* fName)> CITPMgr::_Save;
	static hook_method<void (CITPMgr::*)(const char* Script)> CITPMgr::_Init;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_LoadITP;
	static hook_method<mystd::map<mystd::string,unsigned short>& (CITPMgr::*)(void)> CITPMgr::_GetNameMap;
	static hook_method<mystd::map<unsigned short,mystd::vector<unsigned short> >& (CITPMgr::*)(void)> CITPMgr::_GetCombiItemList;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_InsertITP;
	static hook_method<CITP* (CITPMgr::*)(unsigned short ITID)> CITPMgr::_GetITP;
	static hook_method<enum enumInventoryItemType (CITPMgr::*)(const unsigned short in_ITID)> CITPMgr::_GetInventoryItemType;
	static hook_method<unsigned long (CITPMgr::*)(const char* effectName)> CITPMgr::_GetEffectID;
	static hook_method<unsigned short (CITPMgr::*)(const char* itemName)> CITPMgr::_GetITID;
	static hook_method<int (CITPMgr::*)(const char* itemName, unsigned long* pItemIDList)> CITPMgr::_FindITID;
	static hook_method<short (CITPMgr::*)(unsigned short ITID)> CITPMgr::_GetItemWeight;
	static hook_method<int (CITPMgr::*)(unsigned short ITID)> CITPMgr::_IsApparel;
	static hook_method<int (CITPMgr::*)(unsigned short ITID)> CITPMgr::_IsCashPointItem;
	static hook_method<char* (CITPMgr::*)(unsigned short ITID)> CITPMgr::_GetItemName;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_DBClose;
	static hook_method<bool (CITPMgr::*)(unsigned short ITID)> CITPMgr::_IsScrollItem;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetQuest;
	static hook_method<void (CITPMgr::*)(unsigned long type)> CITPMgr::_GetArmor;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetCannonball;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetArrow;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetAmmo;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetGun;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetWeapon;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetBothhand;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetBow;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetEvent;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetSpecial;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetHeal;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetCard;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetCashPointItem;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_GetThrowWeapon;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_LoadItemMoveInfo;
	static hook_method<bool (CITPMgr::*)(void)> CITPMgr::_LoadCashItemList;
	static hook_method<int (CITPMgr::*)(const char* fileName)> CITPMgr::_LoadCombiItemList;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_LoadScrollItemList;
	static hook_method<void (CITPMgr::*)(void)> CITPMgr::_LoadItemBindOnEquip;
	static hook_method<int (CITPMgr::*)(CITP* itp)> CITPMgr::_AddITP;
};
