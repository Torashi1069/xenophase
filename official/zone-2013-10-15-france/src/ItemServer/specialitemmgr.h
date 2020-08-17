#pragma once
#include "ItemServer/CItemScriptEventHandler.h"
#include "ItemServer/specialitem.h"
#include "ItemServer/specialitemdef.h"
#include "NetLib/MemoryMgr.h"
#include "ScriptLib/BinBuf.h"


enum SITMNG_EVENT_ENUM
{
	EVENT_START_HOLDING   = 1,
	EVENT_START_EQUIP     = 2,
	EVENT_FINISH_HOLDING  = 3,
	EVENT_FINISH_EQUIP    = 4,
	EVENT_USE_ITEM        = 5,
	EVENT_ATTACKED        = 6,
	EVENT_CONSUME         = 7,
	EVENT_ATTACK          = 8,
	EVENT_ACTIVEWEAPON    = 9,
	EVENT_DEACTIVEWEAPON  = 10,
	EVENT_ACTIVEMWEAPON   = 11,
	EVENT_DEACTIVEMWEAPON = 12,
	EVENT_ACTIVEARMOR     = 13,
	EVENT_DEACTIVEARMOR   = 14,
	EVENT_ACTIVEMARMOR    = 15,
	EVENT_DEACTIVEMARMOR  = 16,
	EVENT_ACTIVESKILL     = 17,
	EVENT_DEACTIVESKILL   = 18,
};


class CSpecialItemMgr
{
public:
	CSpecialItemMgr();
	virtual ~CSpecialItemMgr();

public:
	bool Init();
	bool Run(int itemCode, int count, int eventCode, int charID, const unsigned int in_Identity);
	void SendMsg(unsigned long in_ITID, unsigned long in_EventID, unsigned long in_senderAID, short in_Index);
	bool GetItemSpecialStatus(CSendSpecialItemInfoMsg* pITZMsg, CReceiveSpecialItemInfoMsg* pZITMsg, const unsigned int in_Identity);
	void SetScanItem(char* ); //TODO
	void SetScanEvent(int ); //TODO
	void SetItemParam(int* , int ); //TODO
	void SetRetItemFunc(int , int ); //TODO
	void SetRetItemParam(int* , int ); //TODO
	int GetItemFuncIdx(); //TODO
	void AddItemFuncIdx(); //TODO

private:
	bool GetItem(int itemCode, CSpecialItem*& item);
	CSpecialItem* CreateItem(int in_ITID);
	bool AddEvent(int charID, int itemCode, int beginPos);
	bool RunEvent(int charID, int itemCode, int beginPos, const unsigned int in_Identity);

private:
	/* this+  0 */ //const CSpecialItemMgr::`vftable';
	/* this+  4 */ CBinBuf m_binBuf;
	/* this+ 12 */ std::map<int,CSpecialItem*> m_itemMap;
	/* this+ 28 */ char* m_strScanItem;
	/* this+ 32 */ int m_nScanItem;
	/* this+ 36 */ int m_nScanEvent;
	/* this+ 40 */ int m_nItemParam[10];
	/* this+ 80 */ int m_nItemFuncIdx;
	/* this+ 84 */ int m_nRetItemFunc[10];
	/* this+124 */ int m_nRetItemFuncParam[10][10];
	/* this+524 */ int m_nIndex;

	friend class CSpecialItemScanner;
};


extern CMemoryMgr<CItemScriptEventHandler>& g_itemHandlerPool;
extern int& w_index;
extern int& w_cardItem;
