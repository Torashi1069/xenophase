#include "globals.hpp"
#include "CharacterMgr.h"
#include "CITPMgr.hpp"
#include "MonParameterMgr.h"
#include "CMVPInfo.hpp"
#include "PC.h"
#include "ZoneScript.h"
#include "Common/Packet.h"
#include "Custom/AtCommand.h"
#include "Custom/GlobalChat.h"
#include "Custom/umage.hpp"


/// Prototype for all atcommands.
typedef bool (ATCOMMANDFUNC)(CPC* sd, const char* command, const char* params);


bool atcommand_setitem(CPC* sd, const char* command, const char* params)
{
	// sets a 'quest item'
	int itid, num;
	if( sscanf(params, "%d %d", &itid, &num) != 2 )
		return false;

	sd->CPC::SetItem(itid, num);
	clif_displaymessage(sd, "v[%d] := %d", itid, num);
	return true;
}


bool atcommand_getvar(CPC* sd, const char* command, const char* params)
{
	int itid;
	if( sscanf(params, "%d", &itid) != 1 )
		return false;

	clif_displaymessage(sd, "v[%d] == %d", itid, sd->CPC::GetItem(itid));
	return true;
}


bool atcommand_mobinfo(CPC* sd, const char* command, const char* params)
{
	unsigned char msize[3][7] = {"Small", "Medium", "Large"};
	unsigned char mrace[12][11] = {"Formless", "Undead", "Beast", "Plant", "Insect", "Fish", "Demon", "Demi-Human", "Angel", "Dragon", "Boss", "Non-Boss"};
	unsigned char melement[10][8] = {"Neutral", "Water", "Earth", "Fire", "Wind", "Poison", "Holy", "Dark", "Ghost", "Undead"};
	char atcmd_output[256], atcmd_output2[256];
	int i, j;

	if( *params == '\0' )
	{
		clif_displaymessage(sd, "Please, enter a Monster ID (usage: @mobinfo <monster_name_or_monster_ID>).");
		return true;
	}

	int mob_id = atoi(params);
	MONPARAMETER* mob = g_monParameter->CMonParameterMgr::GetMonParameter(mob_id);
	if( mob == NULL )
	{
		char mob_name[256];
		strncpy(mob_name, params, 256); mob_name[255] = '\0';
		_strupr(mob_name);

		mob_id = g_monParameter->CMonParameterMgr::SearchKeyword(params);
		mob = g_monParameter->CMonParameterMgr::GetMonParameter(mob_id);
		if( mob == NULL )
		{
			clif_displaymessage(sd, "Invalid monster ID or name.");
			return false;
		}
	}

	// stats
	if( g_mvpInfo->GetInfo(mob_id) )
		clif_displaymessage(sd, "MVP Monster: '%s'/'%s'/'%s' (%d)", mob->name,  mob->name,  mob->name, mob_id);
	else
		clif_displaymessage(sd, "Monster: '%s'/'%s'/'%s' (%d)", mob->name,  mob->name,  mob->name, mob_id);

	clif_displaymessage(sd, " Level:%d  HP:%d  SP:%d  Base EXP:%u  Job EXP:%u", mob->LV, mob->HP, mob->SP, mob->exp, mob->jexp);
	clif_displaymessage(sd, " DEF:%d  MDEF:%d  STR:%d  AGI:%d  VIT:%d  INT:%d  DEX:%d  LUK:%d", mob->def, mob->mdef, mob->str, mob->agi, mob->vit, mob->Int, mob->dex, mob->luk);
	clif_displaymessage(sd, " ATK:%d~%d  Range:%d~%d~%d  Size:%s  Race: %s  Element: %s (Lv:%d)", mob->atk1, mob->atk1 + mob->atk2, mob->aRan, mob->as, mob->es, msize[mob->scale], mrace[mob->race], melement[mob->property % 20], mob->property / 20);

	// drops
	clif_displaymessage(sd, " Drops:");

	strcpy(atcmd_output, " ");
	j = 0;
	for( i = 0; i < 8; ++i )
	{
		CITP* item;
		if( mob->itemInfo[i].ITID <= 0 || mob->itemInfo[i].percent < 1 || (item = g_itpMgr->CITPMgr::GetITP(mob->itemInfo[i].ITID)) == NULL )
			continue;

		int slots = item->GetMaxSlot();
		if( slots > 0)
			sprintf(atcmd_output2, " - %s[%d]  %02.02f%%", item->m_name, slots, (float)mob->itemInfo[i].percent / 100);
		else
			sprintf(atcmd_output2, " - %s  %02.02f%%", item->m_name, (float)mob->itemInfo[i].percent / 100);

		strcat(atcmd_output, atcmd_output2);

		if (++j % 3 == 0) {
			clif_displaymessage(sd, "%s", atcmd_output);
			strcpy(atcmd_output, " ");
		}
	}
	if (j == 0)
		clif_displaymessage(sd, "This monster has no drops.");
	else if (j % 3 != 0)
		clif_displaymessage(sd, "%s", atcmd_output);

	// mvp
	MVPINFO* mvpinfo = g_mvpInfo->GetInfo(mob_id);
	if( mvpinfo )
	{
		clif_displaymessage(sd, " MVP Bonus EXP:%llu  %02.02f%%", (unsigned long long)mvpinfo->expPercent * mob->exp / 10000, (float)mvpinfo->expPercent / 100);
		strcpy(atcmd_output, " MVP Items:");
		j = 0;
		for (i = 0; i < 3; i++)
		{
			if (mvpinfo->itemPercent[i] == 0 )
				continue;
			
			j++;
			if (j == 1)
				sprintf(atcmd_output2, " %s  %02.02f%%", mvpinfo->itemName[i], (float)mvpinfo->itemPercent[i] / 100);
			else
				sprintf(atcmd_output2, " - %s  %02.02f%%", mvpinfo->itemName[i], (float)mvpinfo->itemPercent[i] / 100);

			strcat(atcmd_output, atcmd_output2);
		}
		if (j == 0)
			clif_displaymessage(sd, "This monster has no MVP prizes.");
		else
			clif_displaymessage(sd, "%s", atcmd_output);
	}

	return true;
}


bool atcommand_speed(CPC* sd, const char* command, const char* params)
{
	int speed;
	if( sscanf(params, "%d", &speed) != 1 )
	{
		clif_displaymessage(sd, "Please, enter a speed value (usage: @speed <value>).");
		return true;
	}

	int old_speed;
	sd->GetParameterValue(VAR_SPEED, old_speed);
	sd->UpdateParameterValue(VAR_SPEED, -old_speed + speed);

	clif_displaymessage(sd, "Speed changed.");
	return true;
}


bool atcommand_heal(CPC* sd, const char* command, const char* params)
{
	// only basic full-heal functionality for now
	int oldhp, oldsp, maxhp, maxsp;
	sd->GetParameterValue(VAR_HP, oldhp);
	sd->GetParameterValue(VAR_SP, oldsp);
	sd->GetParameterValue(VAR_MAXHP, maxhp);
	sd->GetParameterValue(VAR_MAXSP, maxsp);
	sd->UpdateParameterValue(VAR_HP, -oldhp + maxhp);
	sd->UpdateParameterValue(VAR_SP, -oldsp + maxsp);

	clif_displaymessage(sd, "HP, SP recovered.");
	return true;
}


bool atcommand_save(CPC* sd, const char* command, const char* params)
{
	strncpy(sd->m_characterInfo.restartMapName, sd->m_characterInfo.mapName, sizeof(sd->m_characterInfo.restartMapName));
	sd->m_characterInfo.sxPos = sd->m_pathInfo.m_moveInfo.xPos;
	sd->m_characterInfo.syPos = sd->m_pathInfo.m_moveInfo.yPos;

	clif_displaymessage(sd, "Your save point has been changed.");
	return true;
}


bool atcommand_cart(CPC* sd, const char* command, const char* params)
{
	if( !sd->m_pcitemInventoryMgr.IsCartOn() )
		g_characterMgr->CCharacterMgr::SendMsg(sd, sd, CM_CARTON, 0, 0, 0, 0);
	else
		g_characterMgr->CCharacterMgr::SendMsg(sd, sd, CM_CARTOFF, 0, 0, 0, 0);

	clif_displaymessage(sd, "Your cart was changed.");
	return true;
}


bool atcommand_storage(CPC* sd, const char* command, const char* params)
{
	g_characterMgr->CCharacterMgr::SendMsg(NULL, sd, CM_NOTIFY_STOREDITEM, 0, 0, 0, 0);
	clif_displaymessage(sd, "Storage opened.");
	return true;
}


bool atcommand_item(CPC* sd, const char* command, const char* params)
{
	// currently just triggers /item, TODO: eathena-like 'count' parameter
	PACKET_CZ_ITEM_CREATE cz_item_create;
	cz_item_create.PacketType = HEADER_CZ_ITEM_CREATE;
	strncpy(cz_item_create.itemName, params, sizeof(cz_item_create.itemName));
	sd->CClient::Recv(sizeof(cz_item_create), (char*)&cz_item_create);
	return true;
}


bool atcommand_monster(CPC* sd, const char* command, const char* params)
{
	// currently just triggers /item, TODO: eathena-like 'count' parameter
	PACKET_CZ_ITEM_CREATE cz_item_create;
	cz_item_create.PacketType = HEADER_CZ_ITEM_CREATE;
	strncpy(cz_item_create.itemName, params, sizeof(cz_item_create.itemName));
	sd->CClient::Recv(sizeof(cz_item_create), (char*)&cz_item_create);
	return true;
}


bool atcommand_autoloot(CPC* sd, const char* command, const char* params)
{
	int rate;

	if( *params == '\0' )
	{// autoloot command without value
		if( sd->CPC::GetItem(ITID_AUTOLOOT) != 0 )
			rate = 0;
		else
			rate = 10000;
	}
	else
	{
		rate = (int)(atof(params)*100);
	}

	rate = cap_value(rate, 0, 10000);

	// set new value
	sd->CPC::SetItem(ITID_AUTOLOOT, rate);

	if( rate > 0 )
		clif_displaymessage(sd, "Autolooting items with drop rates of %0.02f%% and below.",((double)rate)/100.);
	else
		clif_displaymessage(sd, "Autoloot is now off.");

	return true;
}


bool atcommand_autotrade(CPC* sd, const char* command, const char* params)
{
	// check if player's alive
	if( sd->CPC::IsDeadState() )
	{
		clif_displaymessage(sd, "Cannot autotrade if you are dead.");
		return false;
	}

	// check for allowed map type
	if( sd->CCharacter::GetMapRes()&& !sd->CCharacter::GetMapRes()->IsVillage() )
	{
		clif_displaymessage(sd, "Autotrade is not allowed on this map.");
		return false;
	}

	// check for open shop
	if( !sd->m_pcitemInventoryMgr.CPCItemInventoryMgr::IsMCStoreOpen() )
	{
		clif_displaymessage(sd, "You must be vending to use autotrade.");
		return false;
	}

	// set autotrade var
	sd->CPC::SetItem(ITID_AUTOTRADE, 1);

	// disconnect client
	PACKET_SC_NOTIFY_BAN sc_notify_ban;
	sc_notify_ban.PacketType = HEADER_SC_NOTIFY_BAN;
	sc_notify_ban.ErrorCode = 15;
	sd->Send(sizeof(sc_notify_ban), (char*)&sc_notify_ban);
	sd->CClient::Detach();

	return true;
}


bool atcommand_uptime(CPC* sd, const char* command, const char* params)
{
	FILETIME f, dummy;
	GetProcessTimes(GetCurrentProcess(), &f, &dummy, &dummy, &dummy);
	LONGLONG then = f.dwLowDateTime + ((LONGLONG)f.dwHighDateTime << 32);
	LONGLONG now = Int32x32To64(time(NULL), 10000000) + 116444736000000000;

	unsigned long seconds = (unsigned long)((now - then) / 10000000);
	unsigned long day = 24*60*60, hour = 60*60, minute = 60;
	unsigned long days = 0, hours = 0, minutes = 0;
	days = seconds/day;
	seconds -= (seconds/day>0)?(seconds/day)*day:0;
	hours = seconds/hour;
	seconds -= (seconds/hour>0)?(seconds/hour)*hour:0;
	minutes = seconds/minute;
	seconds -= (seconds/minute>0)?(seconds/minute)*minute:0;

	clif_displaymessage(sd, "Server uptime: %ld days, %ld hours, %ld minutes, %ld seconds.", days, hours, minutes, seconds);
	return true;
}


bool atcommand_servertime(CPC* sd, const char* command, const char* params)
{
	char temp[256];
	struct tm *datetime;
	time_t t;

	time(&t);
	datetime = localtime(&t);
	strftime(temp, sizeof(temp)-1, "Server time: %A, %B %d %Y %X.", datetime);

	clif_displaymessage(sd, temp);
	return true;
}
///


struct {
	const char* name;
	ATCOMMANDFUNC* func;
	bool admin_only;
} AtCommands[] = {
	// admin-only commands
	{ "setitem",    &atcommand_setitem,    true },
	{ "getvar",     &atcommand_getvar,     true },
	{ "mobinfo",    &atcommand_mobinfo,    true },
	{ "mi",         &atcommand_mobinfo,    true },
	{ "speed",      &atcommand_speed,      true },
	{ "heal",       &atcommand_heal,       true },
	{ "save",       &atcommand_save,       true },
	{ "cart",       &atcommand_cart,       true },
	{ "storage",    &atcommand_storage,    true },
	{ "item",       &atcommand_item,       true },
	{ "monster",    &atcommand_monster,    true },
	// normal player commands
	{ "autoloot",   &atcommand_autoloot,   false },
	{ "autotrade",  &atcommand_autotrade,  false },
	{ "uptime",     &atcommand_uptime,     false },
	{ "servertime", &atcommand_servertime, false },
	{ "date",       &atcommand_servertime, false },
	{ "time",       &atcommand_servertime, false },
	{ "channels",   &atcommand_globalchat_channels, false },
	{ "join",       &atcommand_globalchat_join,     false },
	{ "part",       &atcommand_globalchat_part,     false },
	{ "exit",       &atcommand_globalchat_part,     false },
	{ "leave",      &atcommand_globalchat_part,     false },
};


/// Executes a command.
/// Returns true if the text was processed and should not be echoed.
/// @param sd Player to run the command on
/// @param text Command and parameters in unparsed form (format: '@' <command> <whitespace> <parameters>)
bool AtCommand(CPC* sd, const char* text)
{
	if( *text++ != '@' )
		return false; // just normal text

	char command[256] = "";
	char params[256] = "";

	if( sscanf(text, "%255s %255[^\0]", command, params) == 0 )
		return false; // wut.

	return AtCommand(sd, command, params);
}
///


/// Executes a command.
/// Returns true if the text was processed and should not be echoed.
/// @param sd The player to run the command on
/// @param command Command to execute (without the command symbol)
/// @param params Parameter string
bool AtCommand(CPC* sd, const char* command, const char* params)
{
	// poor man's privilege table
	bool isAdminGM = ( g_zoneScript->CZoneScript::SearchID(sd->m_characterInfo.accountName, CHECK_ADMINISTRATOR) == 1 );

	// find the command
	int i;
	for( i = 0; i < ARRAYSIZE(AtCommands); ++i )
		if( stricmp(command, AtCommands[i].name) == 0 )
			break;

	if( i == ARRAYSIZE(AtCommands) )
	{// not a command.
		//clif_displaymessage(sd, "'%s' is an unknown command.", command);
		return false;
	}

	if( AtCommands[i].admin_only && !isAdminGM )
	{// not permitted.
		return false;
	}

	assert( AtCommands[i].func != NULL );
	if( AtCommands[i].func(sd, command, params) == false )
	{// command failed.
		clif_displaymessage(sd, "%s failed.", command);
		return true;
	}

	return true;
}
///
