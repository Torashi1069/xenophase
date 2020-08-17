#pragma once
#pragma pack(push,1)


struct EQUIPSLOTINFO
{
	/* this+0 */ unsigned short info[4];
};


struct REPAIRITEM_INFO
{
	/* this+0 */ short index;
	/* this+2 */ unsigned short ITID;
	/* this+4 */ unsigned char refiningLevel;
	/* this+5 */ EQUIPSLOTINFO slot;
};


/// @see PACKET_ZC_PC_PURCHASE_ITEMLIST
struct PURCHASE_ITEM
{
	/* this+0 */ int price;
	/* this+4 */ int discountprice;
	/* this+8 */ unsigned char type;
	/* this+9 */ unsigned short ITID;
};


/// @see PACKET_ZC_PC_SELL_ITEMLIST
struct SELL_ITEM
{
	/* this+0 */ short index;
	/* this+2 */ int price;
	/* this+6 */ int overchargeprice;
};


/// @see PACKET_CZ_PC_PURCHASE_ITEMLIST
struct CZ_PURCHASE_ITEM
{
	/* this+0 */ short count;
	/* this+2 */ unsigned short ITID;
};


/// @see PACKET_CZ_PC_SELL_ITEMLIST
struct CZ_SELL_ITEM
{
	/* this+0 */ short index;
	/* this+2 */ short count;
};


/// @see PACKET_ZC_ENTER_ROOM
struct ROOM_MEMBER_DATA
{
	/* this+0 */ unsigned long role;
	/* this+4 */ char name[24];
};


#pragma pack(pop)
