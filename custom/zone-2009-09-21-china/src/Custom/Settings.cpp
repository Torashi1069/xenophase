#include "Custom/Settings.h"
#include "globals.hpp"


CSettings* CSettings::GetObj(void)
{
	static CSettings s;
	return &s;
}


CSettings::CSettings(void)
{
	this->CSettings::Load();
}


void CSettings::Load(void)
{
	max_character_count = GetPrivateProfileIntA("ETC", "MAX_CHARACTER_COUNT", 1500, g_infFile);
	stream_pool_size = GetPrivateProfileIntA("ETC", "STREAM_POOL_SIZE", 1500, g_infFile);
	auction_pool_size = GetPrivateProfileIntA("ETC", "AUCTION_POOL_SIZE", 1500, g_infFile);
	max_stream_buffer = GetPrivateProfileIntA("ETC", "MAX_STREAMBUFFER", 1024*1024, g_infFile);
	m_bDisableGuildAllyRequest = GetPrivateProfileIntA("GUILD", "disable ally request", 0, g_infFile);
	m_bDisableGuildHostileRequest = GetPrivateProfileIntA("GUILD", "disable hostile request", 0, g_infFile);
	m_bIsOutputDisconnectLog = GetPrivateProfileIntA("ETC", "output disconnect log", 0, g_infFile) != 0;
	killer_expire_time_loser = 600000000ui64 * GetPrivateProfileIntA("KILLER_SYSTEM", "EXPIRE_TIME_LOSER", 10, g_infFile);
	killer_expire_time_winner = 60000ui64 * GetPrivateProfileIntA("KILLER_SYSTEM", "EXPIRE_TIME_WINNER", 5, g_infFile);
	killer_manner_point = GetPrivateProfileIntA("KILLER_SYSTEM", "MANNER_POINT", 0, g_infFile);
	base_treasurebox_count = GetPrivateProfileIntA("GUILD", "BASE_TREASUREBOX_COUNT", 4, g_infFile);
}
