#pragma once


class CMsg
{
	/* this+ 0 */ public: int par1;
	/* this+ 4 */ public: int par2;
	/* this+ 8 */ public: int par3;
	/* this+12 */ public: int par4;
	/* this+16 */ public: int par5;
	/* this+20 */ protected: unsigned long m_MID;

	public: unsigned long CMsg::GetMsgID(void)
	{
		return m_MID;
	}

	public: void CMsg::SetMsgID(unsigned long msgID)
	{
		m_MID = msgID;
	}
};


class CNPC2ZMsg : public CMsg
{
	/* this+0 */ public: //CMsg baseclass_0;
};


class CZNPC2Msg : public CMsg
{
	/* this+0 */ //public: CMsg baseclass_0;
};
