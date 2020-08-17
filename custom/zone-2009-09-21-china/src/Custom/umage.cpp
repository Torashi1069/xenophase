#include "globals.hpp"
#include "CharacterMgr.h"
#include "CItem.hpp"
#include "ItemLog.h"
#include "CITP.hpp"
#include "CITPMgr.hpp"
#include "PC.h"
#include "Common/Packet.h"
#include "Custom/umage.hpp"


/// Constrains the value to the specified min/max range.
/// Assumes minval < maxval.
template<typename T> T cap_value(T val, T minval, T maxval)
{
	return( (val < minval) ? minval : (val > maxval) ? maxval : val );
}
///


/// Autoloot system.
/// If all criteria are met, the specified player will obtain the specified floor item.
/// @param pc Player who gets the item.
/// @param item Ground item to obtain.
/// @return true if the item was autolooted, otherwise false.
bool Autoloot(CPC* pc, CItem* item, int droprate)
{
	if( pc == NULL )
		return false; // player not online? wth.

	droprate = cap_value(droprate, 0, 10000);

	// check if user has autoloot enabled
	if( droprate > pc->CPC::GetItem(ITID_AUTOLOOT) )
		return false;

	// check if the user isn't dead
	if( pc->IsDeadState() )
		return false;

	// check if user isn't idle
	time_t diff = DIFF_TIME(timeGetTime(), pc->m_pathInfo.m_moveInfo.LastTime); //TODO: use GetParameterValue(VAR_MOVEREQTIME,0)
	if( diff > AUTOLOOT_IDLE_TIME )
		return false;

	// (ripped out from CPCItemInventoryMgr::OnPickUpItem())

	int myXpos;
	int myYpos;
	int otherXPos;
	int otherYPos;
	int mapID;
	item->GetParameterValue(VAR_CURXPOS, otherXPos);
	item->GetParameterValue(VAR_CURYPOS, otherYPos);
	pc->GetParameterValue(VAR_CURXPOS, myXpos);
	pc->GetParameterValue(VAR_CURYPOS, myYpos);
	item->GetParameterValue(VAR_MAPID, mapID);

	// distance check goes first
	if( !(mapID == pc->m_characterInfo.mapID && abs(otherXPos - myXpos) <= AUTOLOOT_DISTANCE && abs(otherYPos - myYpos) <= AUTOLOOT_DISTANCE) )
		return false; // out of range

	// if in a party with item sharing, switch context to one of the eligible members
	CPC* tmp = NULL;
	if( pc->m_characterInfo.PartyItemDivisionRule && pc->m_groupMember.size() > 1 )
		tmp = pc->m_pcitemInventoryMgr.RandomDivision(item);
	pc = ( tmp != NULL ) ? tmp : pc;

	if( !g_itpMgr->CITPMgr::GetITP(item->GetITID()) )
		return false;

	IVItItem* ivit = pc->m_pcitemInventoryMgr.AllocInventoryItem(item->GetITID(), item->m_itemInfo.count);
	if( !ivit )
		return false;

	int identifyflag;
	int slot1;
	int slot2;
	int slot3;
	int slot4;
	item->GetParameterValue(VAR_ISIDENTIFIED, identifyflag);
	ivit->m_isIdentified = ( identifyflag != 0 );
	item->GetParameterValue(VAR_ITEM_SLOT1, slot1);
	item->GetParameterValue(VAR_ITEM_SLOT2, slot2);
	item->GetParameterValue(VAR_ITEM_SLOT3, slot3);
	item->GetParameterValue(VAR_ITEM_SLOT4, slot4);
	ivit->m_slotInfo.info[0] = slot1;
	ivit->m_slotInfo.info[1] = slot2;
	ivit->m_slotInfo.info[2] = slot3;
	ivit->m_slotInfo.info[3] = slot4;
	ivit->IVItItem::SetUniqueIdentityNumV2(item->m_itemInfo.unique_identity_numberV2);
	ivit->IVItItem::SetHireExpireDate(item->m_itemInfo.hire_expire_date);

	if( ivit->GetType() == INVENTORYITEMTYPE_EQUIPITEM )
	{
		int isdamaged;
		int refininglevel;
		item->GetParameterValue(VAR_ISDAMAGED, isdamaged);
		item->GetParameterValue(VAR_REFININGLEVEL, refininglevel);
		((IVItEquipItem*)ivit)->m_isDamaged = ( isdamaged != 0 );
		((IVItEquipItem*)ivit)->m_refiningLevel = refininglevel;
	}

	if( !pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::Add(ivit, 0, 0, 1, 0) )
	{// failed, roll back
		pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::FreeInventoryItem((InventoryItem *)ivit);
		return false;
	}

	pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::NotifyPickUpToParty(ivit);
	g_itemLog->CItemLog::AddItemLog(1, pc, NULL, ivit, 0, ivit->m_count, NULL);
	pc->m_pcitemInventoryMgr.CPCItemInventoryMgr::RefreshItemWeight();

	g_characterMgr->CCharacterMgr::RemoveCharacter(item);
	return true;
}
///


/// Returns the amount of data remaining in the player's input queue.
unsigned int RFIFOREST(const CPC* sd)
{
	return sd->m_packetHandler.m_recvQueue->GetSize();
}
///


#define BUFP(p,pos) (((BYTE*)(p)) + (pos))
#define BUFW(p,pos) (*(WORD*)BUFP((p),(pos)))


/// Validates one global/guild/party/whisper message packet and tries to recognize its components.
/// Returns true if the packet was parsed successfully.
/// Formats: 0 - <packet id>.w <packet len>.w (<name> : <message>).?B 00
///          1 - <packet id>.w <packet len>.w <name>.24B <message>.?B 00
bool clif_process_message(CPC* sd, const char* buf, int format, char** name_, int* namelen_, char** message_, int* messagelen_)
{
	char *text, *name, *message;
	unsigned int packetlen, textlen, namelen, messagelen;

	*name_ = NULL;
	*namelen_ = 0;
	*message_ = NULL;
	*messagelen_ = 0;

	packetlen = BUFW(buf,2);
	// basic structure checks
	if( packetlen > RFIFOREST(sd) )
	{	// there has to be enough data to read
//		ShowWarning("clif_process_message: Received malformed packet from player '%s' (packet length is incorrect)!\n", sd->status.name);
		return false;
	}
	if( packetlen < 4 + 1 )
	{	// 4-byte header and at least an empty string is expected
//		ShowWarning("clif_process_message: Received malformed packet from player '%s' (no message data)!\n", sd->status.name);
		return false;
	}

	text = (char*)BUFP(buf,4);
	textlen = packetlen - 4;

	// process <name> part of the packet
	if( format == 0 )
	{// name and message are separated by ' : '
		// validate name
		name = text;
		namelen = strnlen(sd->m_characterInfo.characterName, NAME_LENGTH-1); // name length (w/o zero byte)

		if( strncmp(name, sd->m_characterInfo.characterName, namelen) || // the text must start with the speaker's name
			name[namelen] != ' ' || name[namelen+1] != ':' || name[namelen+2] != ' ' ) // followed by ' : '
		{
			//Hacked message, or infamous "client desynch" issue where they pick one char while loading another.
//			ShowWarning("clif_process_message: Player '%s' sent a message using an incorrect name! Forcing a relog...\n", sd->status.name);
			g_characterMgr->OnDisconnect(sd); // Just kick them out to correct it.
			return false;
		}

		message = name + namelen + 3;
		messagelen = textlen - namelen - 3; // this should be the message length (w/ zero byte included)
	}
	else
	{// name has fixed width
		if( textlen < NAME_LENGTH + 1 )
		{
//			ShowWarning("clif_process_message: Received malformed packet from player '%s' (packet length is incorrect)!\n", sd->status.name);
			return false;
		}

		// validate name
		name = text;
		namelen = strnlen(name, NAME_LENGTH-1); // name length (w/o zero byte)

		if( name[namelen] != '\0' )
		{	// only restriction is that the name must be zero-terminated
//			ShowWarning("clif_process_message: Player '%s' sent an unterminated name!\n", sd->status.name);
			return false;
		}

		message = name + NAME_LENGTH;
		messagelen = textlen - NAME_LENGTH; // this should be the message length (w/ zero byte included)
	}

	if( messagelen != strnlen(message, messagelen)+1 )
	{	// the declared length must match real length
//		ShowWarning("clif_process_message: Received malformed packet from player '%s' (length is incorrect)!\n", sd->status.name);
		return false;		
	}
	// verify <message> part of the packet
	if( message[messagelen-1] != '\0' )
	{	// message must be zero-terminated
//		ShowWarning("clif_process_message: Player '%s' sent an unterminated message string!\n", sd->status.name);
		return false;		
	}
	if( messagelen > CHAT_SIZE_MAX-1 )
	{	// messages mustn't be too long
		// Normally you can only enter CHATBOX_SIZE-1 letters into the chat box, but Frost Joke / Dazzler's text can be longer.
		// Also, the physical size of strings that use multibyte encoding can go multiple times over the chatbox capacity.
		// Neither the official client nor server place any restriction on the length of the data in the packet,
		// but we'll only allow reasonably long strings here. This also makes sure that they fit into the `chatlog` table.
//		ShowWarning("clif_process_message: Player '%s' sent a message too long ('%.*s')!\n", sd->status.name, CHAT_SIZE_MAX-1, message);
		return false;
	}

	*name_ = name;
	*namelen_ = namelen;
	*message_ = message;
	*messagelen_ = messagelen;
	return true;
}
///


/// Displays a message to the target.
void clif_displaymessage(CPC* sd, const char* mes, ...)
{
	char buf[256];

	va_list args;
	va_start(args, mes);

	BUFW(buf,0) = 0x8e;
	BUFW(buf,2) = 4 + vsnprintf((char*)BUFP(buf,4), sizeof(buf)-4, mes, args) + 1;

	va_end(args);

	sd->Send(BUFW(buf,2), buf);
}
///


/// Applies custom damage reduction equation.
int ModifyDamage_Emperium(int damage)
{
	if( damage >  660 )
		damage =  660 + (damage -  660) * 80 / 100;
	if( damage > 1330 )
		damage = 1330 + (damage - 1330) * 65 / 100;
	if( damage > 2220 )
		damage = 2220 + (damage - 2220) * 50 / 100;

	return damage;
}
///
