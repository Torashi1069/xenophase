#pragma once


class Config
{
public:
	/// Various configuration options.
	struct cfg
	{
		unsigned int crash_handler; // 0=unhandled, 1=gravity stacktrace, 2=minidump, 3=basic dump, 4=extended dump, 9=full dump
	};

	/// Returns a singleton instance of the config object.
	static Config& Obj(void);

	/// Returns the config data.
	const cfg* Get(void);
	const cfg* operator ->(void);

private:
	/// Initializes the object.
	Config(void);

	/// Cleans up the object.
	~Config(void);

	/// Reads the ini file.
	void Load(const char* szIniFile);

	/// The config data itself.
	cfg m_cfg;
};


/// Configuration.
const Config::cfg* config(void);
