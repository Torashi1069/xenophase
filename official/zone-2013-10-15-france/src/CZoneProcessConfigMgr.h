#pragma once


class CZoneProcessConfigMgr
{
public:
	bool isOK() const;

private:
	std::pair<bool,std::string> Create();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CZoneProcessConfigMgr* GetObj(); /// @custom

private:
	CZoneProcessConfigMgr();
	virtual ~CZoneProcessConfigMgr();
	CZoneProcessConfigMgr(CZoneProcessConfigMgr&); // = delete;
	CZoneProcessConfigMgr& operator=(CZoneProcessConfigMgr&); // = delete;

private:
	/* static */ static CZoneProcessConfigMgr*& m_cpSelf; //TODO
	/* this+0 */ //const CZoneProcessConfigMgr::`vftable';
	/* this+4 */ bool m_bOK;
};
