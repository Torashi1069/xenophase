#pragma once


class CHPAmount
{
public:
	operator int();
	CHPAmount& operator+=(const int in_Amount);
	CHPAmount& operator=(const int in_Amount);

public:
	void Init();
	void RecoveryProhibitionSet();
	void RecoveryProhibitionReset();
	void SetForceAmout(const int in_Amount);

public:
	CHPAmount();
	virtual ~CHPAmount();

private:
	/* this+0 */ //const CHPAmount::`vftable';
	/* this+4 */ int m_Amount;
	/* this+8 */ int m_RecoveryProhibitionRefCnt;
};
