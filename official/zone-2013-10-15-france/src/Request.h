#pragma once


enum enumREQUESTTYPE
{
	RT_BODYITEM_PARSING           = 0,
	RT_STOREITEM_PARSING          = 1,
	RT_CARTITEM_PARSING           = 2,
	RT_BODYITEM_SAVE_ASYNC        = 3,
	RT_STOREITEM_SAVE_ASYNC       = 4,
	RT_CARTITEM_SAVE_ASYNC        = 5,
	RT_REQ_PCVAR                  = 6,
	RT_NOTIFY_VARCHANGE           = 7,
	RT_NOTIFY_ARROWEQUIPED        = 8,
	RT_SEND_PACKET                = 9,
	RT_UPDATE_PARAMETER           = 10,
	RT_NOTIFY_ATTACKRANGE         = 11,
	RT_REQ_TAKEOFFEQUIP           = 12,
	RT_REQ_PICKUPITEM             = 13,
	RT_REQ_THROWITEM              = 14,
	RT_REQ_USEITEM                = 15,
	RT_REQ_WEAREQUIP              = 16,
	RT_RESET_EXCHANGEITEM         = 17,
	RT_RESET_MCSTORE              = 18,
	RT_HIREITEM_RETURN            = 19,
	RT_REQ_INVENTORY_TAB          = 20,
	RT_GUILD_STOREITEM_SAVE_ASYNC = 21,
};


struct Request
{
public:
	void SetID(int ID) { m_requestID = ID; }
	int GetID() { return m_requestID; }

public:
	/* this+ 0 */ int par1;
	/* this+ 4 */ int par2;
	/* this+ 8 */ int par3;
protected:
	/* this+12 */ int m_requestID;
};
