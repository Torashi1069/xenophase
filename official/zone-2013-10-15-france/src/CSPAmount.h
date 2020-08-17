#pragma once


class CSPAmount
{
public:
	operator int();
	CSPAmount& operator+=(const int in_Amount);
	CSPAmount& operator=(const int in_Amount);

public:
	void Init();
	void RecoveryProhibitionSet();
	void RecoveryProhibitionReset();
	void SetForceAmout(const int in_Amount);

public:
	CSPAmount();
	virtual ~CSPAmount();

private:
	/* this+0 */ //const CSPAmount::`vftable';
	/* this+4 */ int m_Amount;
	/* this+8 */ int m_RecoveryProhibitionRefCnt;
};
