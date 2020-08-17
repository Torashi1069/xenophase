#pragma once
#include "FTToken.h"
#include "ITP.h"
#include "Player/Inventory/CInventoryItem.h"
#include "shared/ODBC.h"


enum EFFECT
{
	EFFECT01 = 1,
	EFFECT02 = 2,
	EFFECT03 = 3,
	EFFECT04 = 4,
	EFFECT05 = 5,
	EFFECT06 = 6,
	EFFECT07 = 7,
	EFFECT08 = 8,
	EFFECT09 = 9,
	EFFECT10 = 10,
	EFFECT11 = 11,
	EFFECT12 = 12,
	EFFECT13 = 13,
	EFFECT14 = 14,
	EFFECT15 = 15,
	EFFECT16 = 16,
	EFFECT17 = 17,
	EFFECT18 = 18,
	EFFECT19 = 19,
	EFFECT20 = 20,
	EFFECT21 = 21,
	EFFECT22 = 22,
	EFFECT23 = 23,
	EFFECT24 = 24,
	EFFECT25 = 25,
	EFFECT26 = 26,
	EFFECT27 = 27,
	EFFECT28 = 28,
	EFFECT29 = 29,
	EFFECT30 = 30,
};


class CITPMgr : public CODBC
{
public:
	CITPMgr();
	virtual ~CITPMgr();

public:
	bool Save(const char* fName);
	void Init(const char* Script);
	void LoadITP();
	std::map<std::string,unsigned short>& GetNameMap();
	std::map<unsigned short,std::vector<unsigned short>>& GetCombiItemList();
	void InsertITP(); // not implemented
	CITP* GetITP(unsigned short ITID);
	enumInventoryItemType GetInventoryItemType(const unsigned short in_ITID);
	unsigned long GetEffectID(const char* effectName);
	unsigned short GetITID(const char* itemName);
	int FindITID(const char* itemName, unsigned long* pItemIDList);
	short GetItemWeight(unsigned short ITID);
	int IsApparel(unsigned short ITID);
	BOOL IsCashPointItem(unsigned short ITID);
	char* GetItemName(unsigned short ITID);
	void DBClose();
	bool IsScrollItem(unsigned short ITID);
	const bool IsCostumeItem(const unsigned long loc) const;

private:
	void GetQuest();
	void GetArmor(unsigned long type);
	void GetCannonball();
	void GetArrow();
	void GetAmmo();
	void GetGun();
	void GetWeapon();
	void GetBothhand();
	void GetBow();
	void GetEvent();
	void GetSpecial();
	void GetHeal();
	void GetCard();
	void GetCashPointItem();
	bool GetThrow();
	void LoadItemMoveInfo();
	bool LoadCashItemList();
	BOOL LoadCombiItemList(const char* fileName);
	void LoadScrollItemList();
	void LoadItemBindOnEquip();
	BOOL AddITP(CITP* itp);

private:
	typedef std::map<unsigned short,CITP*> ITEMPROTOTYPEMAP;
	typedef std::map<unsigned short,CITP*>::iterator ITEMPROTOTYPEMAP_ITER;
	typedef std::map<std::string,unsigned short> ITEMNAMEIDXMAP;
	typedef std::map<std::string,unsigned short>::iterator ITEMNAMEIDXMAP_ITER;

private:
	/* this+ 0 */ //CODBC baseclass_0;
	/* this+20 */ std::map<unsigned short,CITP*> m_itp;
	/* this+36 */ std::map<std::string,unsigned short> m_itemName;
	/* this+52 */ std::map<std::string,unsigned long> m_effect;
	/* this+68 */ std::map<unsigned short,std::vector<unsigned short>> m_combiItem;
	/* this+84 */ std::map<unsigned short,unsigned short> m_scrollItem;
};


class CItemList
{
public:
	CItemList();
	~CItemList();

private:
	enum { MAX_ITEM = 1000 };

public:
	void LoadFromFile(const char* fileName, int verDate);
	int GetNth(int n);

private:
	/* this+0 */ int m_itemNum;
	/* this+4 */ int m_itemArray[MAX_ITEM];
};


class CItemListV2
{
public:
	CItemListV2();
	~CItemListV2();

public:
	bool Load(const char* in_FileName);
	bool IsPartOfItemList(const unsigned short in_ITID);

private:
	/* this+0 */ std::set<unsigned short> m_ItemList;
};


class CBuyingStoreItemList
{
public:
	bool OpenFileBuyingStoreItemList();
	bool IsPossibleTradeItem(const unsigned short wITID);

private:
	/* this+0 */ std::set<unsigned short> m_BuyingStoreItemList;
};


class CCashItemList
{
private:
	class ANAYSISRET
	{
	public:
		enum enumCode
		{
			CODE_SUCCESS                          = 0,
			CODE_ERROR                            = 1,
			CODE_ERROR_LEXICALANALYSIS_INITIALIZE = 2,
			CODE_ERROR_GET_TOKEN                  = 3,
			CODE_ERROR_SYNTAX                     = 4,
			CODE_ERROR_UNKNOWN                    = 5,
			CODE_ERROR_UNKNOWN_ITEMID             = 6,
		};

	public:
		/* this+ 0 */ CFTToken Token;
		/* this+44 */ enumCode Code;

	public:
		ANAYSISRET(const enumCode in_Code) : Code(in_Code) { }
		ANAYSISRET(const enumCode in_Code, CFTToken& in_Token) : Code(in_Code), Token(in_Token) { }
	};

private:
	ANAYSISRET Anaysis(const std::string in_strFileName);

public:
	bool Load();

public:
	CCashItemList();
	virtual ~CCashItemList();
};
