#pragma once


class CZoneProcessLocalConfigMgr
{
public:
	bool isOK() const;
	bool Init();
	int GetZSID();
	void SetZSID(const int ZSID);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CZoneProcessLocalConfigMgr* GetObj(); /// @custom

private:
	CZoneProcessLocalConfigMgr();
	virtual ~CZoneProcessLocalConfigMgr();
	CZoneProcessLocalConfigMgr(const CZoneProcessLocalConfigMgr&); // = delete;
	CZoneProcessLocalConfigMgr& operator=(const CZoneProcessLocalConfigMgr&); // = delete;

private:
	/* static */ static CZoneProcessLocalConfigMgr*& m_cpSelf; //TODO
	/* this+0 */ //const CZoneProcessLocalConfigMgr::`vftable';
	/* this+4 */ bool m_bOK;
	/* this+8 */ int m_ZSID;
};
