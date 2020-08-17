#pragma once


class CInstantMapConfiguration
{
private:
	/* static */ static CInstantMapConfiguration*& m_cpSelf; //TODO
	/* this+ 0 */ //const CInstantMapConfiguration::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ int m_FirstScriptEventRunSecond;
	/* this+12 */ bool m_Allow;
	/* this+16 */ int m_expect_maximum_life_minute;

private:
	bool Create();
	void Destroy();

public:
	bool isOK() const;
	int GetFirstScriptEventRunSecond();
	bool IsAllow();
	int GetExpectMaximumLifeMinute();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CInstantMapConfiguration* GetObj(); /// @custom

private:
	CInstantMapConfiguration();
	virtual ~CInstantMapConfiguration();
};
