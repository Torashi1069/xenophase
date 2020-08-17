#pragma once


class CInstantMapConfiguration
{
private:
	/* static  */ static CInstantMapConfiguration*& m_cpSelf; //TODO
	/* this+ 0 */ //const CInstantMapConfiguration::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 8 */ int m_DestroyWaitSecond;
	/* this+12 */ int m_CreateResponseWaitSecond_fromZSVR;
	/* this+16 */ bool m_bOpen;

private:
	bool Create();
	void Destroy();

public:
	bool isOK() const;
	int GetDestroyWiatSecond();
	int GetCreateResponseWaitSecond_fromZSVR();
	bool IsOpen();

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CInstantMapConfiguration* GetObj(); /// @custom

private:
	CInstantMapConfiguration();
	virtual ~CInstantMapConfiguration();
};
