#pragma once


struct ITEM_DESC
{
	/* this+ 0 */ const char* identifiedDisplayName;
	/* this+ 4 */ const char* identifiedResourceName;
	/* this+ 8 */ mystd::vector<const char*> identifiedDescriptionName;
	/* this+24 */ const char* unidentifiedDisplayName;
	/* this+28 */ const char* unidentifiedResourceName;
	/* this+32 */ mystd::vector<const char*> unidentifiedDescriptionName;
	/* this+48 */ unsigned long slot;
	/* this+52 */ int slotCount;
	/* this+56 */ mystd::vector<const char*> parameter;
};


struct ITEM_INFO
{
	/* this+ 0 */ int m_itemType;
	/* this+ 4 */ int m_location;
	/* this+ 8 */ unsigned long m_itemIndex;
	/* this+12 */ int m_wearLocation;
	/* this+16 */ int m_num;
	/* this+20 */ int m_price;
	/* this+24 */ int m_realPrice;
	/* this+28 */ int m_slot[4];
	/* this+44 */ mystd::string m_itemName;
	/* this+60 */ mystd::string m_field_3C_str;
	/* this+76 */ bool m_isIdentified;
	/* this+77 */ bool m_isDamaged;
	/* this+80 */ int m_refiningLevel;
	/* this+84 */ unsigned short m_isYours;
	/* this+88 */ int m_deleteTime;

	ITEM_INFO();
	void SetItemId(int itemId);
	static const ITEM_DESC& __cdecl GetItemDesc(int itemName);
	static const ITEM_DESC& __cdecl GetItemDesc(const char* itemName);

private:
	static hook_func<const ITEM_DESC& (__cdecl *)(int itemName)> _GetItemDesc;
};
