#pragma once


class CGVar
{
public:
	bool isOK() const;
	int GetAsyncDBThreadNum();
	void SetGlobalDBPwd(const std::string in_GlobalDBPwd);
	void SetCharacterDBPwd(const std::string in_CharacterDBPwd);
	std::string GetGlobalDBPwd();
	std::string GetCharacterDBPwd();

private:
	bool Create();
	void Destroy();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CGVar* GetObj(); /// @custom

private:
	CGVar();
	~CGVar();

private:
	/* static  */ static CGVar*& m_cpSelf; //TODO
	/* this+ 0 */ bool m_bOK;
	/* this+ 4 */ int m_AsyncDBThreadNum;
	/* this+ 8 */ std::string m_GlobalDBPwd;
	/* this+36 */ std::string m_CharacterDBPwd;
};
