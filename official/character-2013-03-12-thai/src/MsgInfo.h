#pragma once


struct sMsgInfo
{
	/* this+  0 */ char m_szMsg[100];
	/* this+100 */ int col; // color
};


class CMsgInfo
{
private:
	/* this+    0 */ sMsgInfo m_MsgInfo[100];
	/* this+10400 */ int nCurPos;

public:
//	CMsgInfo();
//	~CMsgInfo();
	void AddString(int col, const char* Msg, ...);
//	void Print(HDC hDC);
};
