#pragma once


class CMonsterParameterTable
{
public:
	CMonsterParameterTable();
	virtual ~CMonsterParameterTable();

public:
	std::pair<bool,std::string> SetTable(const int in_Job, const std::string in_SpriteName, const std::string in_Name);
	void SetTable();
	void Clear();
	void SaveToFileMobName(const char* fName);
	void SaveToFileNpcSpr(const char* fName);

protected:
	/* this+ 0 */ //const CMonsterParameterTable::`vftable';
	/* this+ 4 */ std::map<std::string,unsigned long> m_spriteName;
	/* this+20 */ std::map<std::string,unsigned long> m_mobName;
};
