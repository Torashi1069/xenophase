#include "GameMode.h"
#include "Globals.h" // Trace()
#include "ItemInfo.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Base/File.h"
////////////////////////////////////////


mystd::map<int,ITEM_DESC>& ITEM_INFO::s_itemDescMap = VTOR<mystd::map<int,ITEM_DESC>>(SymDB::Add("ITEM_INFO::s_itemDescMap", SAKEXE, "ITEM_INFO::s_itemDescMap"));
mystd::map<int,CARD_DESC>& ITEM_INFO::s_cardDescMap = VTOR<mystd::map<int,CARD_DESC>>(SymDB::Add("ITEM_INFO::s_cardDescMap", SAKEXE, "ITEM_INFO::s_cardDescMap"));
mystd::map<int,mystd::vector<const char*>>& ITEM_INFO::s_maketargetdesc = VTOR<mystd::map<int,mystd::vector<const char*>>>(SymDB::Add("ITEM_INFO::s_maketargetdesc", SAKEXE, "ITEM_INFO::s_maketargetdesc"));
CommonObject& ITEM_INFO::s_obj = VTOR<CommonObject>(SymDB::Add("ITEM_INFO::s_obj", SAKEXE, "ITEM_INFO::s_obj"));


////////////////////////////////////////


CommonObject::CommonObject(void) // line 20 (ItemInfo.h)
{
	this->CommonObject::Clear();
}


CommonObject::~CommonObject(void) // line 21 (ItemInfo.h)
{
	this->CommonObject::Clear();
}


hook_method<void (CommonObject::*)(void)> CommonObject::_Clear(SAKEXE, "CommonObject::Clear");
void CommonObject::Clear(void) // line 15-24
{
	return (this->*_Clear)();

	for( mystd::vector<char*>::iterator i = m_deleteList.begin(); i != m_deleteList.end(); ++i )
	{
		if( *i )
			delete *i;
		*i = NULL;
	}

	m_deleteList.clear();
}


hook_method<bool (CommonObject::*)(mystd::vector<const char*>& pCharList, const char* fName, bool desc)> CommonObject::_TokenFileToPCharList(SAKEXE, "CommonObject::TokenFileToPCharList");
bool CommonObject::TokenFileToPCharList(mystd::vector<const char*>& pCharList, const char* fName, bool desc) // line 27-68
{
	return (this->*_TokenFileToPCharList)(pCharList, fName, desc);

	pCharList.clear();
	pCharList.reserve(0x1000);

	CFile fp;
	if( !fp.CFile::Open(fName, CFile::modeRead) )
		return false;

	size_t len = fp.GetLength();
	char* buf = new char[len + 1];
	fp.CFile::Read(buf, len);
	buf[len] = '\0';

	fp.CFile::Close();

	char* base = &buf[0];
	for( size_t i = 0; i < len; ++i )
	{
		switch( buf[i] )
		{
		case '\n':
			base = &buf[i + 1];
			break;
		case '\r':
			buf[i] = '\0';
			if( desc )
				pCharList.push_back(base);
			base = &buf[i + 1];
			break;
		case '#':
			buf[i] = '\0';
			pCharList.push_back(base);
			base = &buf[i + 1];
			break;
		}
	}

	Trace("%s size = %d capacity = %d", fName, pCharList.size(), pCharList.capacity());
	m_deleteList.push_back(buf);

	return true;
}


////////////////////////////////////////


bool __cdecl IsNumberString(const char* str) // line 71-95
{
	static const bool number[256] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
								      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

	for( size_t i = 0; i < strlen(str); ++i )
		if( !number[BYTE(str[i])] )
			return false;

	return true;
}


////////////////////////////////////////


ITEM_INFO::ITEM_INFO(void) // line 73 (ItemInfo.h)
{
	memset(this, 0, sizeof(*this)); //FIXME: destroys m_itemName
}


ITEM_INFO::ITEM_INFO(int) // line 74 (ItemInfo.h)
{//inlined
	memset(this, 0, sizeof(*this)); //FIXME: destroys m_itemName
}


hook_method<void (ITEM_INFO::*)(int itemId)> ITEM_INFO::_SetItemId(SAKEXE, "ITEM_INFO::SetItemId");
void ITEM_INFO::SetItemId(int itemId) // line 99-102
{
	return (this->*_SetItemId)(itemId);

	char buf[16];
	m_itemName = itoa(itemId, buf, 10);
}


hook_method<int (ITEM_INFO::*)(void) const> ITEM_INFO::_GetItemId(SAKEXE, "ITEM_INFO::GetItemId");
int ITEM_INFO::GetItemId(void) const // line 76 (ItemInfo.h)
{
	return (this->*_GetItemId)();

	return atoi(m_itemName.c_str());
}


hook_method<int (ITEM_INFO::*)(char* refining) const> ITEM_INFO::_GetRefining(SAKEXE, "ITEM_INFO::GetRefining");
int ITEM_INFO::GetRefining(char* refining) const // line 105-107
{
	return (this->*_GetRefining)(refining);

	return sprintf(refining, "+%d ", m_refiningLevel);
}


hook_method<int (ITEM_INFO::*)(char* named) const> ITEM_INFO::_GetNamed(SAKEXE, "ITEM_INFO::GetNamed");
int ITEM_INFO::GetNamed(char* named) const // line 110-112
{
	return (this->*_GetNamed)(named);

	return sprintf(named, MsgStr(MSI_NAMED_PET)); //FIXME: uncontrolled format string vulnerability
}


hook_method<int (ITEM_INFO::*)(char* prefix) const> ITEM_INFO::_GetPrefix(SAKEXE, "ITEM_INFO::GetPrefix");
int ITEM_INFO::GetPrefix(char* prefix) const // line 116-145
{
	return (this->*_GetPrefix)(prefix);

	char* p = prefix;
	int slot[4] = { m_slot[0], m_slot[1], m_slot[2], m_slot[3] };

	for( int i = 0; i < countof(slot); ++i )
	{
		int cardId = slot[i];
		if( cardId == 0 )
			continue;

		const char* cardPrefix = ITEM_INFO::GetCardDesc(cardId).prefix;
		if( cardPrefix == NULL || *cardPrefix == '\0' )
			continue;

		int count = 1;
		for( int j = i + 1; j < countof(slot); ++j )
		{
			if( slot[j] == cardId )
			{
				slot[j] = 0;
				++count;
			}
		}

		if( count == 2 )
			p += sprintf(p, "%s ", MsgStr(MSI_DOUBLE));
		else
		if( count == 3 )
			p += sprintf(p, "%s ", MsgStr(MSI_TRIPLE));
		else
		if( count == 4 )
			p += sprintf(p, "%s ", MsgStr(MSI_QUADROPLE));

		p += sprintf(p, "%s ", cardPrefix);
	}

	return int(p - prefix);
}


hook_method<int (ITEM_INFO::*)(char* postfix) const> ITEM_INFO::_GetPostfix(SAKEXE, "ITEM_INFO::GetPostfix");
int ITEM_INFO::GetPostfix(char* postfix) const // line 148-178
{
	return (this->*_GetPostfix)(postfix);

	char* p = postfix;
	int slot[4] = { m_slot[0], m_slot[1], m_slot[2], m_slot[3] };

	for( int i = 0; i < countof(slot); ++i )
	{
		int cardId = slot[i];
		if( cardId == '\0' )
			continue;

		const char* cardPostfix = ITEM_INFO::GetCardDesc(cardId).postfix;
		if( cardPostfix == NULL || *cardPostfix == '\0' )
			continue;

		int count = 1;
		for( int j = i + 1; j < countof(slot); ++j )
		{
			if( slot[j] == cardId )
			{
				slot[j] = 0;
				++count;
			}
		}

		p += sprintf(p, " %s", cardPostfix);

		if( count == 2 )
			p += sprintf(p, " %s", MsgStr(MSI_DOUBLE));
		else
		if( count == 3 )
			p += sprintf(p, " %s", MsgStr(MSI_TRIPLE));
		else
		if( count == 4 )
			p += sprintf(p, " %s", MsgStr(MSI_QUADROPLE));
	}

	return int(p - postfix);
}


hook_method<int (ITEM_INFO::*)(char* text) const> ITEM_INFO::_GetManufacturedItemPrefix(SAKEXE, "ITEM_INFO::GetManufacturedItemPrefix");
int ITEM_INFO::GetManufacturedItemPrefix(char* text) const // line 181-200
{
	return (this->*_GetManufacturedItemPrefix)(text);

	int result;

	switch( BYTE(m_slot[1] >> 8) )
	{
	case 5:
		strcpy(text, MsgStr(MSI_ONE_STARPIECE));
		result = strlen(text);
	break;
	case 10:
		strcpy(text, MsgStr(MSI_TWO_STARPIECE));
		result = strlen(text);
	break;
	case 15:
		strcpy(text, MsgStr(MSI_THREE_STARPIECE));
		result = strlen(text);
	break;
	default:
		result = 0;
	break;
	}

	return result;
}


hook_method<int (ITEM_INFO::*)(char* text) const> ITEM_INFO::_GetManufacturedItemProducer(SAKEXE, "ITEM_INFO::GetManufacturedItemProducer");
int ITEM_INFO::GetManufacturedItemProducer(char* text) const // line 203-211
{
	return (this->*_GetManufacturedItemProducer)(text);

	unsigned long GID = (m_slot[2] << 0) + (m_slot[3] << 16);
	strcpy(text, g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetActorNameByGID(GID).cName.c_str());
	return strlen(text);
}


hook_method<int (ITEM_INFO::*)(char* text) const> ITEM_INFO::_GetManufacturedItemPostfix(SAKEXE, "ITEM_INFO::GetManufacturedItemPostfix");
int ITEM_INFO::GetManufacturedItemPostfix(char* text) const // line 214-239
{
	return (this->*_GetManufacturedItemPostfix)(text);

	int result;

	switch( BYTE(m_slot[1] >> 0) )
	{
	case 0:
		strcpy(text, MsgStr(MSI_MANUFACTURED_NORMAL_ITEM));
		result = strlen(text);
	break;
	case 1:
		strcpy(text, MsgStr(MSI_MANUFACTURED_ICE_ITEM));
		result = strlen(text);
	break;
	case 2:
		strcpy(text, MsgStr(MSI_MANUFACTURED_EARTH_ITEM));
		result = strlen(text);
	break;
	case 3:
		strcpy(text, MsgStr(MSI_MANUFACTURED_FIRE_ITEM));
		result = strlen(text);
	break;
	case 4:
		strcpy(text, MsgStr(MSI_MANUFACTURED_WIND_ITEM));
		result = strlen(text);
	break;
	default:
		result = 0;
	break;
	}

	return result;
}


hook_method<int (ITEM_INFO::*)(char* name) const> ITEM_INFO::_GetIdDisplayName(SAKEXE, "ITEM_INFO::GetIdDisplayName");
int ITEM_INFO::GetIdDisplayName(char* name) const // line 242-247
{
	return (this->*_GetIdDisplayName)(name);

	const ITEM_DESC& item = ITEM_INFO::GetItemDesc(m_itemName.c_str()); //inlined
	strcpy(name, item.identifiedDisplayName); //FIXME: crashes if nullDesc
	return strlen(name);
}


hook_method<int (ITEM_INFO::*)(char* name) const> ITEM_INFO::_GetUnidDisplayName(SAKEXE, "ITEM_INFO::GetUnidDisplayName");
int ITEM_INFO::GetUnidDisplayName(char* name) const // line 250-255
{
	return (this->*_GetUnidDisplayName)(name);

	const ITEM_DESC& item = ITEM_INFO::GetItemDesc(m_itemName.c_str()); //inlined
	strcpy(name, item.unidentifiedDisplayName); //FIXME: crashes if nullDesc
	return strlen(name);
}


hook_method<char* (ITEM_INFO::*)(char* itemName)> ITEM_INFO::_GetItemName(SAKEXE, "ITEM_INFO::GetItemName");
char* ITEM_INFO::GetItemName(char* itemName) // line 258-302
{
	return (this->*_GetItemName)(itemName);

	if( !m_isIdentified )
	{
		this->ITEM_INFO::GetUnidDisplayName(itemName);
		return itemName;
	}

	if( m_slot[0] == 0 && m_slot[1] == 0 && m_slot[2] == 0 && m_slot[3] == 1 )
	{
		int pos = 0;
		pos += this->ITEM_INFO::GetNamed(&itemName[pos]); //inlined
		pos += this->ITEM_INFO::GetIdDisplayName(&itemName[pos]); //inlined
		return itemName;
	}

	if( m_slot[0] == 254 && m_slot[1] == 0 )
	{
		int pos = 0;
		pos += this->ITEM_INFO::GetManufacturedItemProducer(&itemName[pos]); //inlined
		pos += this->ITEM_INFO::GetManufacturedItemPostfix(&itemName[pos]); //inlined
		pos += this->ITEM_INFO::GetIdDisplayName(&itemName[pos]); //inlined
		return itemName;
	}

	if( !this->ITEM_INFO::IsAttachableItem() ) //inlined
	{
		this->ITEM_INFO::GetIdDisplayName(itemName);
		return itemName;
	}

	char* itemName2 = itemName;
	if( m_refiningLevel != 0 )
		itemName2 += ITEM_INFO::GetRefining(itemName); //inlined

	if( this->ITEM_INFO::IsCardItem(m_slot[0]) )
	{
		int pos = 0;
		pos += this->ITEM_INFO::GetPrefix(&itemName2[pos]); //inlined
		pos += this->ITEM_INFO::GetIdDisplayName(&itemName2[pos]); //inlined
		pos += this->ITEM_INFO::GetPostfix(&itemName2[pos]); //inlined
		return itemName;
	}

	if( this->ITEM_INFO::IsManufacturedItem() ) //inlined
	{
		int pos = 0;
		pos += this->ITEM_INFO::GetManufacturedItemPrefix(&itemName2[pos]); //inlined
		pos += this->ITEM_INFO::GetManufacturedItemProducer(&itemName2[pos]); //inlined
		pos += this->ITEM_INFO::GetManufacturedItemPostfix(&itemName2[pos]); //inlined
		pos += this->ITEM_INFO::GetIdDisplayName(&itemName2[pos]); //inlined
		return itemName;
	}

	this->ITEM_INFO::GetIdDisplayName(itemName2); //inlined
	return itemName;
}


hook_method<bool (ITEM_INFO::*)(void)> ITEM_INFO::_IsValid(SAKEXE, "ITEM_INFO::IsValid");
bool ITEM_INFO::IsValid(void) // line 89 (ItemInfo.h)
{
	return (this->*_IsValid)();

	return ( m_itemIndex != 0 );
}


hook_method<const char* (ITEM_INFO::*)(void)> ITEM_INFO::_GetResName(SAKEXE, "ITEM_INFO::GetResName");
const char* ITEM_INFO::GetResName(void) // line 336-341
{
	return (this->*_GetResName)();

	if( m_isIdentified )
		return ITEM_INFO::GetItemDesc(m_itemName.c_str()).identifiedResourceName;
	else
		return ITEM_INFO::GetItemDesc(m_itemName.c_str()).unidentifiedResourceName;
}


hook_method<const mystd::vector<const char*>& (ITEM_INFO::*)(void)> ITEM_INFO::_GetDescription(SAKEXE, "ITEM_INFO::GetDescription");
const mystd::vector<const char*>& ITEM_INFO::GetDescription(void) // line 344-349
{
	return (this->*_GetDescription)();

	if( m_isIdentified )
		return ITEM_INFO::GetItemDesc(m_itemName.c_str()).identifiedDescriptionName;
	else
		return ITEM_INFO::GetItemDesc(m_itemName.c_str()).unidentifiedDescriptionName;
}


hook_method<int (ITEM_INFO::*)(void)> ITEM_INFO::_GetSlotCount(SAKEXE, "ITEM_INFO::GetSlotCount");
int ITEM_INFO::GetSlotCount(void) // line 352-354
{
	return (this->*_GetSlotCount)();

	return ITEM_INFO::GetItemDesc(m_itemName.c_str()).slotCount; //inlined
}


hook_method<void (ITEM_INFO::*)(const DRAG_INFO* dragInfo)> ITEM_INFO::_CopyItemInfo(SAKEXE, "ITEM_INFO::CopyItemInfo");
void ITEM_INFO::CopyItemInfo(const DRAG_INFO* dragInfo) // line 413-426
{
	return (this->*_CopyItemInfo)(dragInfo);

	m_price = dragInfo->m_dragItemPrice;
	m_realPrice = dragInfo->m_dragItemRealPrice;
	m_num = dragInfo->m_numDragItem;
	m_itemName = dragInfo->m_dragItemName;
	m_itemIndex = dragInfo->m_dragItemIndex;
	m_itemType = dragInfo->m_dragItemType;
	m_isIdentified = dragInfo->m_isIdentified;
	m_refiningLevel = dragInfo->m_refiningLevel;
	m_slot[0] = dragInfo->m_slot[0];
	m_slot[1] = dragInfo->m_slot[1];
	m_slot[2] = dragInfo->m_slot[2];
	m_slot[3] = dragInfo->m_slot[3];
}


//hook_method<static bool (__cdecl *)(const char* itemName)> ITEM_INFO::_IsCardItem(SAKEXE, "?IsCardItem@ITEM_INFO@@SA_NPBD@Z");
bool __cdecl ITEM_INFO::IsCardItem(const char* itemName) // line ???
{
//	return ITEM_INFO::_IsCardItem(itemName);

	return ITEM_INFO::IsCardItem(atoi(itemName));
}


hook_method<static bool (__cdecl *)(int itemName)> ITEM_INFO::_IsCardItem2(SAKEXE, "?IsCardItem@ITEM_INFO@@SA_NH@Z");
bool __cdecl ITEM_INFO::IsCardItem(int itemName) // line 610-612
{
	return ITEM_INFO::_IsCardItem2(itemName);

	return ( ITEM_INFO::s_cardDescMap.find(itemName) != ITEM_INFO::s_cardDescMap.end() );
}


//hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsCardItem3(SAKEXE, "???");
bool ITEM_INFO::IsCardItem(void) const // line ???
{
//	return (this->*_IsCardItem3)();

	return ITEM_INFO::IsCardItem(m_itemName.c_str());
}


hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsManufacturedItem(SAKEXE, "ITEM_INFO::IsManufacturedItem");
bool ITEM_INFO::IsManufacturedItem(void) const // line 357-361
{
	return (this->*_IsManufacturedItem)();

	return ( m_slot[0] == 255 );
}


hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsRecoveryItem(SAKEXE, "ITEM_INFO::IsRecoveryItem");
bool ITEM_INFO::IsRecoveryItem(void) const // line 364-368
{
	return (this->*_IsRecoveryItem)();

	int ITID = this->ITEM_INFO::GetItemId();
	return ( ITID > ITEM_RECOVERY_START && ITID < ITEM_RECOVERY_END );
}


hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsAttachableItem(SAKEXE, "ITEM_INFO::IsAttachableItem");
bool ITEM_INFO::IsAttachableItem(void) const // line 371-387
{
	return (this->*_IsAttachableItem)();

	switch( m_itemType )
	{
	case TYPE_ARMOR:
	case TYPE_WEAPON:
	case TYPE_BOW:
	case TYPE_BOTHHAND:
	case TYPE_ARMORTM:
	case TYPE_ARMORTB:
	case TYPE_ARMORMB:
	case TYPE_ARMORTMB:
	case TYPE_GUN:
		return true;
	break;
	default:
		return false;
	break;
	}
}


hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsPropertyItem(SAKEXE, "ITEM_INFO::IsPropertyItem");
bool ITEM_INFO::IsPropertyItem(void) const // line 390-400
{
	return (this->*_IsPropertyItem)();

	int ITID = this->ITEM_INFO::GetItemId();
	return ( ITID >= ITEM_FLAME_HEART && ITID <= ITEM_GREAT_NATURE );
}


hook_method<bool (ITEM_INFO::*)(void) const> ITEM_INFO::_IsMaterialItem(SAKEXE, "ITEM_INFO::IsMaterialItem");
bool ITEM_INFO::IsMaterialItem(void) const // line 403-410
{
	return (this->*_IsMaterialItem)();

	int ITID = this->ITEM_INFO::GetItemId();
	return ( ITID == ITEM_STAR_CRUMB || this->ITEM_INFO::IsPropertyItem() );
}


hook_method<ITEM_INFO& (ITEM_INFO::*)(const ITEM_INFO& iteminfo)> ITEM_INFO::_operator_eq2(SAKEXE, "??4ITEM_INFO@@QAEAAU0@ABU0@@Z");
ITEM_INFO& ITEM_INFO::operator=(const ITEM_INFO& iteminfo) // line 305-320
{
	return (this->*_operator_eq2)(iteminfo);

	m_itemType = iteminfo.m_itemType;
	m_location = iteminfo.m_location;
	m_itemIndex = iteminfo.m_itemIndex;
	m_wearLocation = iteminfo.m_wearLocation;
	m_num = iteminfo.m_num;
	m_price = iteminfo.m_price;
	m_realPrice = iteminfo.m_realPrice;
	m_slot[0] = iteminfo.m_slot[0];
	m_slot[1] = iteminfo.m_slot[1];
	m_slot[2] = iteminfo.m_slot[2];
	m_slot[3] = iteminfo.m_slot[3];
	m_itemName = iteminfo.m_itemName;
	m_isIdentified = iteminfo.m_isIdentified;
	m_isDamaged = iteminfo.m_isDamaged;
	m_refiningLevel = iteminfo.m_refiningLevel;
	return *this;
}


hook_method<ITEM_INFO& (ITEM_INFO::*)(const SHOP_ITEM& shopitem)> ITEM_INFO::_operator_eq(SAKEXE, "??4ITEM_INFO@@QAEAAU0@ABUSHOP_ITEM@@@Z");
ITEM_INFO& ITEM_INFO::operator=(const SHOP_ITEM& shopitem) // line 323-333
{
	return (this->*_operator_eq)(shopitem);

	m_itemName = shopitem.itemName;
	m_price = shopitem.price;
	m_realPrice = shopitem.price;
	m_itemIndex = shopitem.index;
	m_itemType = shopitem.type;
	m_realPrice = shopitem.realPrice;
	m_isIdentified = shopitem.isIdentified;
	return *this;
}


hook_method<void (__cdecl *)(void)> ITEM_INFO::_InitItemInfoTables(SAKEXE, "ITEM_INFO::InitItemInfoTables");
void __cdecl ITEM_INFO::InitItemInfoTables(void) // line 435-602
{
	return ITEM_INFO::_InitItemInfoTables();

	static const char* strNull = "";
	static const char* strUnknown = "Unknown Item";
	static const char* strApple = "사과";
	static const char* strSorry = "sorry";

	ITEM_INFO::s_itemDescMap.clear();
	ITEM_INFO::s_cardDescMap.clear();
	ITEM_INFO::s_maketargetdesc.clear();
	ITEM_INFO::s_obj.Clear();

	//NOTE: this function has a lot of memleaks due to misuse of TokenFileToPCharList/table
	mystd::vector<const char*> table;
	table.resize(20000);

	ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "Num2ItemDisplayNameTable.txt", false); // line 449
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 2 )
	{
		int itemId = atoi(*(i + 0));
		const char* itemName = *(i + 1);

		mystd::map<int,ITEM_DESC>::iterator desc = ITEM_INFO::s_itemDescMap.find(itemId);
		if( desc == ITEM_INFO::s_itemDescMap.end() )
			desc = ITEM_INFO::s_itemDescMap.insert(mystd::pair<const int,ITEM_DESC>(itemId, ITEM_DESC())).first;

		g_session.CSession::RemoveUnderbar(itemName, const_cast<char*>(itemName));
		desc->second.unidentifiedDisplayName = itemName;
	}

	ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "Num2ItemResNameTable.txt", false); // line 458
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 2 )
	{
		int itemId = atoi(*(i + 0));
		const char* resName = *(i + 1);

		mystd::map<int,ITEM_DESC>::iterator desc = ITEM_INFO::s_itemDescMap.find(itemId);
		if( desc == ITEM_INFO::s_itemDescMap.end() )
			desc = ITEM_INFO::s_itemDescMap.insert(mystd::pair<const int,ITEM_DESC>(itemId, ITEM_DESC())).first;

		desc->second.unidentifiedResourceName = resName;
	}

	int itemName = 0;
	ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "Num2itemDescTable.txt", true); // line 467
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 1 )
	{
		const char* line = *i;

		if( line == NULL || *line == '\0' )
			continue;

		if( IsNumberString(line) )
		{
			itemName = atoi(line); // remember and use in next loop iteration
		}
		else
		{
			DataTxtDecode(const_cast<char*>(line));

			mystd::map<int,ITEM_DESC>::iterator desc = ITEM_INFO::s_itemDescMap.find(itemName);
			if( desc == ITEM_INFO::s_itemDescMap.end() )
				desc = ITEM_INFO::s_itemDescMap.insert(mystd::pair<const int,ITEM_DESC>(itemName, ITEM_DESC())).first;

			desc->second.unidentifiedDescriptionName.push_back(line);
		}
	}

	ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "IdNum2ItemDisplayNameTable.txt", false); // line 482
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 2 )
	{
		int itemId = atoi(*(i + 0));
		const char* itemName = *(i + 1);

		mystd::map<int,ITEM_DESC>::iterator desc = ITEM_INFO::s_itemDescMap.find(itemId);
		if( desc == ITEM_INFO::s_itemDescMap.end() )
			desc = ITEM_INFO::s_itemDescMap.insert(mystd::pair<const int,ITEM_DESC>(itemId, ITEM_DESC())).first;

		g_session.CSession::RemoveUnderbar(itemName, const_cast<char*>(itemName));
		desc->second.identifiedDisplayName = itemName;
	}

	ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "IdNum2ItemResNameTable.txt", false); // line 491
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 2 )
	{
		int itemId = atoi(*(i + 0));
		const char* resName = *(i + 1);

		mystd::map<int,ITEM_DESC>::iterator desc = ITEM_INFO::s_itemDescMap.find(itemId);
		if( desc == ITEM_INFO::s_itemDescMap.end() )
			desc = ITEM_INFO::s_itemDescMap.insert(mystd::pair<const int,ITEM_DESC>(itemId, ITEM_DESC())).first;

		desc->second.identifiedResourceName = resName;
	}

	int itemName_ = 0;
    ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "IdNum2itemDescTable.txt", true); // line 500
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 1 )
    {
		const char* line = *i;

        if( line == NULL || *line == '\0' )
			continue;

		if( IsNumberString(line) )
		{
			itemName_ = atoi(line); // remember and use in next loop iteration
		}
		else
		{
			DataTxtDecode(const_cast<char*>(line));

			mystd::map<int,ITEM_DESC>::iterator desc = ITEM_INFO::s_itemDescMap.find(itemName_);
			if( desc == ITEM_INFO::s_itemDescMap.end() )
				desc = ITEM_INFO::s_itemDescMap.insert(mystd::pair<const int,ITEM_DESC>(itemName_, ITEM_DESC())).first;

			desc->second.identifiedDescriptionName.push_back(line);
		}
    }

	ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "itemSlotTable.txt", false); // line 515
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 2 )
	{
		int itemId = atoi(*(i + 0));
		int slotMask = atoi(*(i + 1));

		mystd::map<int,ITEM_DESC>::iterator desc = ITEM_INFO::s_itemDescMap.find(itemId);
		if( desc == ITEM_INFO::s_itemDescMap.end() )
			desc = ITEM_INFO::s_itemDescMap.insert(mystd::pair<const int,ITEM_DESC>(itemId, ITEM_DESC())).first;

		desc->second.slot = slotMask;
	}

	ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "itemParamTable.txt", false); // line 523
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 3 )
	{
		int itemId = atoi(*(i + 0));
		int param1 = atoi(*(i + 1));
		int param2 = atoi(*(i + 2));

		mystd::map<int,ITEM_DESC>::iterator desc = ITEM_INFO::s_itemDescMap.find(itemId);
		if( desc == ITEM_INFO::s_itemDescMap.end() )
			desc = ITEM_INFO::s_itemDescMap.insert(mystd::pair<const int,ITEM_DESC>(itemId, ITEM_DESC())).first;

		desc->second.parameter.push_back(param1);
		desc->second.parameter.push_back(param2);
	}

    ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "itemSlotCountTable.txt", false); // line 533
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 2 )
    {
        int itemId = atoi(*(i + 0));
		int slotCount = atoi(*(i + 1));

		mystd::map<int,ITEM_DESC>::iterator desc = ITEM_INFO::s_itemDescMap.find(itemId);
		if( desc == ITEM_INFO::s_itemDescMap.end() )
			desc = ITEM_INFO::s_itemDescMap.insert(mystd::pair<const int,ITEM_DESC>(itemId, ITEM_DESC())).first;

        desc->second.slotCount = slotCount;
    }

	ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "CardItemNameTable.txt", false); // line 541
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 1 )
	{
		int itemId = atoi(*i);

		mystd::map<int,CARD_DESC>::iterator desc = ITEM_INFO::s_cardDescMap.find(itemId);
		if( desc == ITEM_INFO::s_cardDescMap.end() )
			desc = ITEM_INFO::s_cardDescMap.insert(mystd::pair<const int,CARD_DESC>(itemId, CARD_DESC())).first;
	}

	ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "Num2CardIllustNameTable.txt", false); // line 547
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 2 )
	{
		int itemId = atoi(*(i + 0));
		const char* illustName = *(i + 1);

		mystd::map<int,CARD_DESC>::iterator desc = ITEM_INFO::s_cardDescMap.find(itemId);
		if( desc == ITEM_INFO::s_cardDescMap.end() )
			desc = ITEM_INFO::s_cardDescMap.insert(mystd::pair<const int,CARD_DESC>(itemId, CARD_DESC())).first;

		desc->second.illustName = illustName;
	}

	ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "CardPrefixNameTable.txt", false); // line 555
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 2 )
	{
		int itemId = atoi(*(i + 0));
		const char* cardPrefix = *(i + 1);

		mystd::map<int,CARD_DESC>::iterator desc = ITEM_INFO::s_cardDescMap.find(itemId);
		if( desc == ITEM_INFO::s_cardDescMap.end() )
			desc = ITEM_INFO::s_cardDescMap.insert(mystd::pair<const int,CARD_DESC>(itemId, CARD_DESC())).first;

		desc->second.prefix = cardPrefix;
	}

	ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "CardPostfixNameTable.txt", false); // line 563
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 1 )
	{
		int itemId = atoi(*i);

		mystd::map<int,CARD_DESC>::iterator desc = ITEM_INFO::s_cardDescMap.find(itemId);
		if( desc == ITEM_INFO::s_cardDescMap.end() )
			desc = ITEM_INFO::s_cardDescMap.insert(mystd::pair<const int,CARD_DESC>(itemId, CARD_DESC())).first;

		// wow, what a weird way to implement this...
		desc->second.postfix = desc->second.prefix;
		desc->second.prefix = strNull;
	}

	int itemName__ = 0;
    ITEM_INFO::s_obj.CommonObject::TokenFileToPCharList(table, "MetalProcessItemList.txt", true); // line 572
	for( mystd::vector<const char*>::iterator i = table.begin(); i != table.end(); i += 1 )
    {
		const char* line = *i;

		if( line == NULL || *line == '\0' )
			continue;

		if( IsNumberString(line) )
		{
			itemName__ = atoi(line); // remember and use in next loop iteration
		}
		else
		if( strlen(line) != 0 )
		{
			mystd::map<int,mystd::vector<const char*>>::iterator desc = ITEM_INFO::s_maketargetdesc.find(itemName__);
			if( desc == ITEM_INFO::s_maketargetdesc.end() )
				desc = ITEM_INFO::s_maketargetdesc.insert(mystd::pair<const int,mystd::vector<const char*>>(itemName__, mystd::vector<const char*>())).first;

			desc->second.push_back(line);
		}
    }

	ITEM_DESC& idNone = GetDesc<ITEM_DESC>(ITEM_NONE, ITEM_INFO::s_itemDescMap);
	idNone.identifiedDisplayName = strUnknown;
	idNone.identifiedResourceName = strApple;
	idNone.identifiedDescriptionName.push_back(strUnknown);
	idNone.unidentifiedDisplayName = strUnknown;
	idNone.unidentifiedResourceName = strApple;
	idNone.unidentifiedDescriptionName.push_back(strUnknown);

	ITEM_DESC& idInvalid = GetDesc<ITEM_DESC>(ITEM_INVALID, ITEM_INFO::s_itemDescMap);
	idInvalid = idNone;

	CARD_DESC& cdNone = GetDesc<CARD_DESC>(ITEM_NONE, ITEM_INFO::s_cardDescMap);
	cdNone.illustName = strSorry;
	cdNone.prefix = strNull;
	cdNone.postfix = strNull;

	CARD_DESC& cdInvalid = GetDesc<CARD_DESC>(ITEM_INVALID, ITEM_INFO::s_cardDescMap);
	cdInvalid = cdNone;
}


//hook_method<const ITEM_DESC& (__cdecl *)(const char* itemName)> ITEM_INFO::_GetItemDesc(SAKEXE, "?GetItemDesc@ITEM_INFO@@SAABUITEM_DESC@@PBD@Z");
const ITEM_DESC& __cdecl ITEM_INFO::GetItemDesc(const char* itemName) // line ???
{
//	return ITEM_INFO::_GetItemDesc(itemName);

	return ITEM_INFO::GetItemDesc(atoi(itemName));
}


hook_method<const ITEM_DESC& (__cdecl *)(int itemName)> ITEM_INFO::_GetItemDesc2(SAKEXE, "?GetItemDesc@ITEM_INFO@@SAABUITEM_DESC@@H@Z");
const ITEM_DESC& __cdecl ITEM_INFO::GetItemDesc(int itemName) // line 605-607
{
	return ITEM_INFO::_GetItemDesc2(itemName);

	return GetDesc<ITEM_DESC>(itemName, ITEM_INFO::s_itemDescMap); //inlined
}


//hook_method<const CARD_DESC& (__cdecl *)(const char* itemName)> ITEM_INFO::_GetCardDesc(SAKEXE, "?GetCardDesc@ITEM_INFO@@SAABUCARD_DESC@@PBD@Z");
const CARD_DESC& __cdecl ITEM_INFO::GetCardDesc(const char* itemName) // line ???
{
//	return ITEM_INFO::_GetCardDesc(itemName);

	return ITEM_INFO::GetCardDesc(atoi(itemName));
}


hook_method<const CARD_DESC& (__cdecl *)(int itemName)> ITEM_INFO::_GetCardDesc2(SAKEXE, "?GetCardDesc@ITEM_INFO@@SAABUCARD_DESC@@H@Z");
const CARD_DESC& __cdecl ITEM_INFO::GetCardDesc(int itemName) // line 615-617
{
	return ITEM_INFO::_GetCardDesc2(itemName);

	return GetDesc<CARD_DESC>(itemName, ITEM_INFO::s_cardDescMap); //inlined
}


//hook_method<const mystd::vector<const char*>& (__cdecl *)(const char* itemName)> ITEM_INFO::_GetMakeTargetDesc(SAKEXE, "?GetMakeTargetDesc@ITEM_INFO@@SAABV?$vector@PBDV?$allocator@PBD@std@@@std@@PBD@Z");
const mystd::vector<const char*>& __cdecl ITEM_INFO::GetMakeTargetDesc(const char* itemName) // line ???
{
//	return ITEM_INFO::_GetMakeTargetDesc(itemName);

	return ITEM_INFO::GetMakeTargetDesc(atoi(itemName));
}


hook_method<const mystd::vector<const char*>& (__cdecl *)(int itemName)> ITEM_INFO::_GetMakeTargetDesc2(SAKEXE, "?GetMakeTargetDesc@ITEM_INFO@@SAABV?$vector@PBDV?$allocator@PBD@std@@@std@@H@Z");
const mystd::vector<const char*>& __cdecl ITEM_INFO::GetMakeTargetDesc(int itemName) // line 620-622
{
	return ITEM_INFO::_GetMakeTargetDesc2(itemName);

	return GetDesc<mystd::vector<const char*>>(itemName, ITEM_INFO::s_maketargetdesc); //inlined
}


////////////////////////////////////////


class hook_ptr<struct mystd::_Tree<int,struct mystd::pair<int const ,struct ITEM_DESC>,struct mystd::map<int,struct ITEM_DESC,struct mystd::less<int>,class mystd::allocator<struct ITEM_DESC> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct ITEM_DESC> >::_Node *> mystd::_Tree<int,struct mystd::pair<int const ,struct ITEM_DESC>,struct mystd::map<int,struct ITEM_DESC,struct mystd::less<int>,class mystd::allocator<struct ITEM_DESC> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct ITEM_DESC> >::_Nil(SAKEXE, "?_Nil@?$_Tree@HU?$pair@$$CBHUITEM_DESC@@@std@@U_Kfn@?$map@HUITEM_DESC@@U?$less@H@std@@V?$allocator@UITEM_DESC@@@3@@2@U?$less@H@2@V?$allocator@UITEM_DESC@@@2@@std@@1PAU_Node@12@A");
class hook_ptr<struct mystd::_Tree<int,struct mystd::pair<int const ,struct CARD_DESC>,struct mystd::map<int,struct CARD_DESC,struct mystd::less<int>,class mystd::allocator<struct CARD_DESC> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct CARD_DESC> >::_Node *> mystd::_Tree<int,struct mystd::pair<int const ,struct CARD_DESC>,struct mystd::map<int,struct CARD_DESC,struct mystd::less<int>,class mystd::allocator<struct CARD_DESC> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct CARD_DESC> >::_Nil(SAKEXE, "?_Nil@?$_Tree@HU?$pair@$$CBHUCARD_DESC@@@std@@U_Kfn@?$map@HUCARD_DESC@@U?$less@H@std@@V?$allocator@UCARD_DESC@@@3@@2@U?$less@H@2@V?$allocator@UCARD_DESC@@@2@@std@@1PAU_Node@12@A");
class hook_ptr<struct mystd::_Tree<int,struct mystd::pair<int const ,class mystd::vector<char const *,class mystd::allocator<char const *> > >,struct mystd::map<int,class mystd::vector<char const *,class mystd::allocator<char const *> >,struct mystd::less<int>,class mystd::allocator<class mystd::vector<char const *,class mystd::allocator<char const *> > > >::_Kfn,struct mystd::less<int>,class mystd::allocator<class mystd::vector<char const *,class mystd::allocator<char const *> > > >::_Node *> mystd::_Tree<int,struct mystd::pair<int const ,class mystd::vector<char const *,class mystd::allocator<char const *> > >,struct mystd::map<int,class mystd::vector<char const *,class mystd::allocator<char const *> >,struct mystd::less<int>,class mystd::allocator<class mystd::vector<char const *,class mystd::allocator<char const *> > > >::_Kfn,struct mystd::less<int>,class mystd::allocator<class mystd::vector<char const *,class mystd::allocator<char const *> > > >::_Nil(SAKEXE, "?_Nil@?$_Tree@HU?$pair@$$CBHV?$vector@PBDV?$allocator@PBD@std@@@std@@@std@@U_Kfn@?$map@HV?$vector@PBDV?$allocator@PBD@std@@@std@@U?$less@H@2@V?$allocator@V?$vector@PBDV?$allocator@PBD@std@@@std@@@2@@2@U?$less@H@2@V?$allocator@V?$vector@PBDV?$alloc7872b7af");
