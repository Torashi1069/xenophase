#pragma once


class CRuneItemInfo
{
public:
	enum { RUNEITEM_ERROR = -1 };

public:
	CRuneItemInfo();
	virtual ~CRuneItemInfo();
	bool Init();

private:
	struct RUNE_MATERIAL
	{
		/* this+0 */ int itemID;
		/* this+4 */ short count;
	};

	typedef std::list<RUNE_MATERIAL> RUNE_MATERIAL_LIST;

public:
	RUNE_MATERIAL_LIST* GetRuneMaterial(int runeID);
	int GetRawRuneSuccessPercent(int rawID);
	int GetRuneRankSuccessPercent(int runeID);
	int GetMakableRuneItemByLevel(int skLevel);
	int GetMakeSuccessPercentByLevel(int skLevel);
	int GetUseSuccessPercentByLevel(int skLevel);
	int GetRuneItemMaxCount(int itemID);
	int GetMakableRuneItemRandomCount(int skLevel);

private:
	struct RUNE_ITEM
	{
		/* this+0 */ int itemID;
		/* this+4 */ std::string itemName;
	};

private:
	/* this+  0 */ //const CRuneItemInfo::`vftable';
	/* this+  4 */ std::map<std::string,short> m_ranktype;
	/* this+ 20 */ std::map<int,short> m_runeRankList;
	/* this+ 36 */ std::map<short,short> m_rankSuccessPercent;
	/* this+ 52 */ std::map<int,short> m_rawRuneSuccessPercent;
	/* this+ 68 */ std::vector<short> m_runeMastery_MakeSuccessPercent;
	/* this+ 84 */ std::vector<short> m_runeMastery_MakeMinCount;
	/* this+100 */ std::vector<short> m_runeMastery_MakeMaxCount;
	/* this+116 */ std::vector<short> m_runeMastery_UseSuccessPercent;
	/* this+132 */ std::map<int,RUNE_ITEM> m_runeMasteryLevel_MakableItem;
	/* this+148 */ std::map<int,short> m_runeItem_MaxCount;
	/* this+164 */ std::map<int,RUNE_MATERIAL_LIST> m_runeMaterials;

private:
	bool Load_RankType(lua_State* L);
	bool Load_RuneRankList(lua_State* L);
	bool Load_RankSuccessPercent(lua_State* L);
	bool Load_RawRundSuccessPercent(lua_State* L);
	bool Load_RuneMastery_MakeSuccessPercent(lua_State* L);
	bool Load_RuneMastery_MakeMinCount(lua_State* L);
	bool Load_RuneMastery_MakeMaxCount(lua_State* L);
	bool Load_RuneMastery_UseSuccessPercent(lua_State* L);
	bool Load_RuneMasteryLevel_MakableItem(lua_State* L);
	bool Load_RuneItem_MaxCount(lua_State* L);
	bool Load_RuneMaterial(lua_State* L);
	bool Load_KeyValue(lua_State* L, const char* table, std::map<int,short>* _list);
	bool Load_KeyValue(lua_State* L, const char* table, std::map<std::string,short>* _list);
	bool Load_KeyValue(lua_State* L, const char* table, std::vector<short>* _list);
	bool Load_KeyValue(lua_State* L, const char* table, std::list<RUNE_MATERIAL>* _list);
};


extern CRuneItemInfo& g_runeItemInfo;
