#include "ItemInfo.h"


ITEM_INFO::ITEM_INFO()
{
	memset(this, 0, sizeof(*this)); //FIXME: destroys m_itemName and m_field_3C_str
}


void ITEM_INFO::SetItemId(int itemId)
{
	char buf[16];
	m_itemName = itoa(itemId, buf, 10);
}


hook_func<const ITEM_DESC& (__cdecl *)(int itemName)> ITEM_INFO::_GetItemDesc("ITEM_INFO::GetItemDesc");
const ITEM_DESC& __cdecl ITEM_INFO::GetItemDesc(int itemName)
{
	return ITEM_INFO::_GetItemDesc(itemName);

	//TODO
}


const ITEM_DESC& __cdecl ITEM_INFO::GetItemDesc(const char* itemName)
{
	return ITEM_INFO::GetItemDesc(atoi(itemName));
}
