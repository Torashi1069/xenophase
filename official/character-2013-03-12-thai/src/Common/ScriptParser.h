#pragma once


class CScriptParser
{
private:
	/* this+0 */ std::map<std::string,std::vector<std::string>> m_data;

public:
	CScriptParser();
	~CScriptParser();
	size_t size();
	void clear();
	bool LoadFile(const char* szFileName);
	const char* GetItem(const char* szKey, DWORD dwColumn);
	const char* GetItem(DWORD dwRow, DWORD dwColumn);
};
