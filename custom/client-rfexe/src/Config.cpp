#include "Config.h"
static Config* s_pConfig = NULL;


/// Returns a singleton instance of the config object.
Config& Config::Obj(void)
{
	static Config* singleton = new Config();
	return *singleton;
}


/// Initializes the object.
Config::Config(void)
{
	::s_pConfig = this;
	Load("./rfexe.ini");
}


/// Cleans up the object.
Config::~Config(void)
{
	::s_pConfig = NULL;
}


/// Returns the config data.
const Config::cfg* Config::Get(void)
{
	return &m_cfg;
}


/// Returns the config data.
const Config::cfg* Config::operator ->(void)
{
	return &m_cfg;
}


/// Reads the ini file.
void Config::Load(const char* szIniFile)
{
	memset(&m_cfg, 0, sizeof(m_cfg));
	m_cfg.crash_handler = GetPrivateProfileIntA("Debug", "crash handler", 1, szIniFile);
}


/// Configuration.
const Config::cfg* config(void)
{
	return Config::Obj().Get();
}
