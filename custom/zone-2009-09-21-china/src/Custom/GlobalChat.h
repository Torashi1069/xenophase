#pragma once
class CPC;


enum enumGlobalChannel
{
	CHANNEL_MAIN    = 0,
	CHANNEL_TRADE   = 1,
	CHANNEL_RECRUIT = 2,
	CHANNEL_COUNT      ,
	CHANNEL_DUMMY   = 14,
};


const struct GlobalChannel
{
	int id; // not used; must be sequential
	const char* name;
	unsigned int color; // AABBGGRR
	const char* description;
	const char* notice;

} Channels[CHANNEL_COUNT] = {

	{ CHANNEL_MAIN   , "#main"   , 0x00BBBBBB, "General conversation", "" },
	{ CHANNEL_TRADE  , "#trade"  , 0x0066CCFF, "Trading: buy, sell, trade and price checks", "" },
	{ CHANNEL_RECRUIT, "#recruit", 0x0050EECA, "Recruiting: party, guild, battlegrounds", "" },
};


enumGlobalChannel globalchat_name2id(const char* channel);
int globalchat_getitem(CPC* sd);
bool atcommand_globalchat_join(CPC* sd, const char* command, const char* message);
bool atcommand_globalchat_part(CPC* sd, const char* command, const char* message);
bool atcommand_globalchat_channels(CPC* sd, const char* command, const char* message);
void clif_parse_globalchat(CPC* sd, const char* channel, const char* message);
void intif_parse_globalchat(const char* mes);
void intif_globalchat(const char* mes, ...);
