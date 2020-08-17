#include "PC.h"
#include "CharacterMgr.h"
#include "globals.hpp"
#include "Common/Packet.h"
#include "custom/GlobalChat.h"
#include "Custom/umage.hpp"


/// Resolve channel name to channel id.
/// Only compares the first letter of the name (quick&dirty shorthand support).
/// @return If successful, returns the channel id, otherwise returns a value of CHANNEL_COUNT or greater.
enumGlobalChannel globalchat_name2id(const char* channel)
{
	for( int i = 0; i < CHANNEL_COUNT; ++i )
		if( strnicmp(channel, Channels[i].name, 2) == 0 )
			return (enumGlobalChannel)i;

	return CHANNEL_DUMMY;
}
///

/// Returns (or sets default) quest variable for GlobalChat.
/// @return Return the value (count) of ITID_GLOBALCHAT for character.
int globalchat_getitem(CPC* sd)
{
	int value = sd->CPC::GetItem(ITID_GLOBALCHAT);
	if( value == 0 )
	{
		value |= 1 << CHANNEL_DUMMY; // set highest (dummy) bit to make value nonzero
		value = (1 << CHANNEL_MAIN) | (1 << CHANNEL_TRADE) | (1 << CHANNEL_RECRUIT); // the default
		sd->CPC::SetItem(ITID_GLOBALCHAT, value);
	}

	return value;
}
///

/// Join global channel.
bool atcommand_globalchat_join(CPC* sd, const char* command, const char* params)
{
	if( *params == '\0' )
	{// usage
		clif_displaymessage(sd, "Usage: @join #<channel>");
		clif_displaymessage(sd, "For information about available channels, use @channels.");
		return false;
	}

	// get current global chat value
	int value = globalchat_getitem(sd);

	// determine channel id
	int id = globalchat_name2id(params);
	if( id >= CHANNEL_COUNT )
	{
		clif_displaymessage(sd, "Channel '%s' does not exist.", params);
		clif_displaymessage(sd, "For information about available channels, use @channels.");
		return false;
	}

	bool joined = ( (value & (1 << id)) != 0 );
	if( joined )
	{
		clif_displaymessage(sd, "You are in %s already.", Channels[id].name);
		return false;
	}

	// join the channel
	value |= 1 << CHANNEL_DUMMY; // set highest (dummy) bit to make value nonzero
	value |= 1 << id;
	sd->CPC::SetItem(ITID_GLOBALCHAT, value);

	// display join message
	if( *Channels[id].notice != '\0' )
		clif_displaymessage(sd, "%s", Channels[id].notice);

	// display instructions
	clif_displaymessage(sd, "You have joined %s. Whisper to %s to talk in the channel.", Channels[id].name, Channels[id].name);

	return true;
}
///


/// Leave global channel.
bool atcommand_globalchat_part(CPC* sd, const char* command, const char* params)
{
	if( *params == '\0' )
	{// usage
		clif_displaymessage(sd, "Usage: @part #<channel>");
		clif_displaymessage(sd, "For information about available channels, use @channels.");
		return false;
	}

	// get current global chat value
	int value = globalchat_getitem(sd);

	// determine channel id
	int id = globalchat_name2id(params);
	if( id >= CHANNEL_COUNT )
	{
		clif_displaymessage(sd, "Channel '%s' does not exist.", params);
		clif_displaymessage(sd, "For information about available channels, use @channels.");
		return false;
	}

	bool joined = ( (value & (1 << id)) != 0 );
	if( !joined )
	{
		clif_displaymessage(sd, "You are not in %s.", Channels[id].name);
		return false;
	}

	// leave the channel
	value |= 1 << CHANNEL_DUMMY; // set highest (dummy) bit to make value nonzero
	value &= ~(1 << id);
	sd->CPC::SetItem(ITID_GLOBALCHAT, value);

	// display notice
	clif_displaymessage(sd, "You left %s.", Channels[id].name);

	return false;
}
///

/// Display info about global channels.
bool atcommand_globalchat_channels(CPC* sd, const char* command, const char* params)
{
	// get current global chat value
	int value = globalchat_getitem(sd);

	clif_displaymessage(sd, "Global channels list:");

	for( int i = 0; i < CHANNEL_COUNT; ++i )
	{
		bool joined = ( (value & (1 << i)) != 0 );
		clif_displaymessage(sd, "%s%-12s %s", (joined)?"¤":"  ", Channels[i].name, Channels[i].description);
	}

	return true;
}
///


/// Process a global chat message from the client.
void clif_parse_globalchat(CPC* sd, const char* channel, const char* message)
{
	if( sd->CPC::IsBadGuy() )
	{
		//clif_displaymessage(sd, "You cannot talk while muted.");
		return;
	}

	// check if channel exists
	int id = globalchat_name2id(channel);
	if( id >= CHANNEL_COUNT )
	{
		clif_displaymessage(sd, "Channel '%s' does not exist.", channel);
		clif_displaymessage(sd, "For information about available channels, use @channels.");
		return;
	}

	// get current global chat value
	int value = globalchat_getitem(sd);

	// check if not joined
	bool joined = ( (value & (1 << id)) != 0 );
	if( !joined )
	{
		clif_displaymessage(sd, "You are not in %s.", Channels[id].name);
		return;
	}

	// pre-processing:
	char msg[256];
	strcpy(msg, message);

	// replace control characters with spaces
	for( size_t i = 0; i < strlen(msg); ++i )
		if( iscntrl((unsigned char)msg[i]) )
			msg[i] = ' ';

	intif_globalchat("%s : [%s] %s", Channels[id].name, sd->CPC::GetCharacterName(), msg);
}
///


/// Process a global chat message from inter.
void intif_parse_globalchat(const char* mes)
{
	enumGlobalChannel id = globalchat_name2id(mes);
	if( id >= CHANNEL_COUNT )
		return; // should not happen

	g_characterMgr->CCharacterMgr::GlobalChat(id, mes);
}
///


/// Send a global chat message to inter.
void intif_globalchat(const char* mes, ...)
{
	char buf[sizeof(PACKET_ZI_BROADCAST)+CHAT_SIZE_MAX];
	PACKET_ZI_BROADCAST& zi_broadcast = *(PACKET_ZI_BROADCAST*)buf;

	va_list args;
	va_start(args, mes);

	zi_broadcast.PacketType = HEADER_ZI_BROADCAST;
	vsnprintf(zi_broadcast.Text, CHAT_SIZE_MAX, mes, args);
	zi_broadcast.PacketLength = 4 + strlen(zi_broadcast.Text) + 1;

	va_end(args);

	g_characterMgr->CCharacterMgr::SendToIServer(zi_broadcast.PacketLength, (char*)&zi_broadcast);
}
///
