#pragma once


class CSendSpecialItemInfoMsg
{
public:
	CSendSpecialItemInfoMsg();
	~CSendSpecialItemInfoMsg();

public:
	void SetCharId(int nCharId);
	void SetItemId(int nItemId);
	void SetEvent(int nEvent);
	int GetCharId();
	int GetItemId();
	int GetEvent();

private:
	/* this+0 */ int m_nCharId;
	/* this+4 */ int m_nItemId;
	/* this+8 */ int m_nEvent;
};


class CReceiveSpecialItemInfoMsg
{
public:
	CReceiveSpecialItemInfoMsg();
	~CReceiveSpecialItemInfoMsg();

public:
	void SetFunc(int nFunc, int nIdx);
	void SetParam(int* pParamArr, int nIdx);
	void GetFunc(int* pFuncArr);
	void GetParam(void* pParamArr);

private:
	/* this+ 0 */ int m_nFunc[10];
	/* this+40 */ int m_nParamArr[10][10];
};
