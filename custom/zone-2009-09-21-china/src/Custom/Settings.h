#pragma once


class CSettings
{
public:
	int max_character_count;
	int stream_pool_size;
	int auction_pool_size;
	int max_stream_buffer;
	int m_bDisableGuildAllyRequest;
	int m_bDisableGuildHostileRequest;
	int m_bIsOutputDisconnectLog;
	unsigned __int64 killer_expire_time_loser;
	unsigned __int64 killer_expire_time_winner;
	int killer_manner_point;
	int base_treasurebox_count;

	static CSettings* CSettings::GetObj(void);

private:
	CSettings::CSettings(void);
	void CSettings::Load(void);
};
