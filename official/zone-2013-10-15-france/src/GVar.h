#pragma once


class CGVar
{
private:
	/* static  */ static CGVar*& m_cpSelf; //TODO
	/* this+ 0 */ //const CGVar::`vftable';
	/* this+ 4 */ int m_DBColumnSizeBodyItem;
	/* this+ 8 */ int m_DBColumnSizeStoreItem;
	/* this+12 */ int m_DBColumnSizeCartItem;
	/* this+16 */ unsigned int m_valid_client_file_length;
	/* this+20 */ int m_character_data_save_interval_minute;
	/* this+24 */ bool m_bIsMaskPlayerNameBSI;
	/* this+25 */ bool m_bFreeServer_Always_PK_in_Agit_Map;
	/* this+26 */ bool m_bAgainstServerSiegeWarfare;
	/* this+   */ struct {
	/* this+28 */ int when_reassembly_time_out;
	/* this+32 */ int when_reassembly_invalid;
	/* this+36 */ int when_reassembly_modifyIMT_winsock;
	/* this+40 */ int when_reassembly_modifyIMT_gdi32;
	/* this+44 */ int when_reassembly_hackshield;
	/* this+48 */ int when_found_unknown_packet;
	/* this+   */ } m_UserBlock;
	/* this+52 */ int m_AsyncDBThreadNum;
	/* this+56 */ bool m_bOK;

private:
	bool Create();
	void Destory();
	const bool isOK() const;

public:
	int GetDBColumnSizeBodyItem();
	int GetDBColumnSizeStoreItem();
	int GetDBColumnSizeCartItem();
	int GetUserBlockSecond_when_reassembly_time_out();
	int GetUserBlockSecond_when_reassembly_invalid();
	int GetUserBlockSecond_when_reassembly_modifyIMT_winsock();
	int GetUserBlockSecond_when_reassembly_modifyIMT_gdi32();
	int GetUserBlockSecond_when_reassembly_hackshield();
	int GetUserBlockSecond_when_found_unknown_packet();
	int GetCharacterDataSaveIntervalMinute();
	int GetAsyncDBThreadNum();
	unsigned int get_valid_client_file_length();
	unsigned int GetUsedMemoryBytes();
	bool IsMaskPlayerNameBSI();
	bool IsFreeServerAlwaysPKinAgitMap();
	bool IsAgainstServerSiegeWarfare();
	int GetHSID();
	void SetHSID(const int in_HSID);
	int GetIrMailExpireDay();
	int GetMIN_ZENY_ITEMLOG_EXECEXCHANGEITEM();

public:
	static bool CreateInstance();
	static void DestoryInstance();
	static CGVar* GetObj(); /// @custom

private:
	CGVar();
	virtual ~CGVar();
	CGVar(CGVar&); // = delete;
	CGVar& operator=(CGVar&); // = delete;

private:
	/* this+60 */ int m_HSID;
	/* this+64 */ int m_IrMailExpireDay;
	/* this+68 */ int m_MIN_ZENY_ITEMLOG_EXECEXCHANGEITEM;
	/* this+72 */ float m_DenominatorData;

public:
	void SetMaxCharacterCount(const int ); //TODO
	int GetMaxCharacterCount() const;
	float GetDenominatorData();
};
