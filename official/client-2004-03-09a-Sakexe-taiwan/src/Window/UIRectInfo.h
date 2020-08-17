#pragma once


struct SayDialogWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void SayDialogWndInfo::MakeDefault(void); // 20
	//public: int SayDialogWndInfo::IsValidInfo(void);
};


struct ChooseWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ChooseWndInfo::MakeDefault(void); // 41
	//public: int ChooseWndInfo::IsValidInfo(void);
};


struct BasicInfoWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	public: void BasicInfoWndInfo::MakeDefault(void); // 62
	public: int BasicInfoWndInfo::IsValidInfo(void);

private:
	static hook_method<void (BasicInfoWndInfo::*)(void)> BasicInfoWndInfo::_MakeDefault;
	static hook_method<int (BasicInfoWndInfo::*)(void)> BasicInfoWndInfo::_IsValidInfo;
};


struct ItemWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
	/* this+16 */ int orgHeight;
	/* this+20 */ int curTab;
	/* this+24 */ int curRadio1;
	/* this+28 */ int curRadio2;
	/* this+32 */ int curRadio3;
	/* this+36 */ int show;

	//public: void ItemWndInfo::MakeDefault(void); // 88
	//public: int ItemWndInfo::IsValidInfo(void);
};


struct PartySettingWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void PartySettingWndInfo::MakeDefault(void); // 102
	//public: int PartySettingWndInfo::IsValidInfo(void);
};


struct ItemParamChangeDisplayWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ItemParamChangeDisplayWndInfo::MakeDefault(void); // 125
	//public: int ItemParamChangeDisplayWndInfo::IsValidInfo(void);
};


struct ItemCollectionWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ItemCollectionWndInfo::MakeDefault(void); // 147
	//public: int ItemCollectionWndInfo::IsValidInfo(void);
};


struct CombinedCardItemCollectionWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void CombinedCardItemCollectionWndInfo::MakeDefault(void); // 169
	//public: int CombinedCardItemCollectionWndInfo::IsValidInfo(void);
};


struct GuildWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
	/* this+16 */ int curTab;

	public: void GuildWndInfo::MakeDefault(void); // 193
	public: int GuildWndInfo::IsValidInfo(void);

private:
	static hook_method<void (GuildWndInfo::*)(void)> GuildWndInfo::_MakeDefault;
	static hook_method<int (GuildWndInfo::*)(void)> GuildWndInfo::_IsValidInfo;
};


struct DetailLevelWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void DetailLevelWndInfo::MakeDefault(void); // 219
	//public: int DetailLevelWndInfo::IsValidInfo(void);
};


struct ExchangeAcceptWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ExchangeAcceptWndInfo::MakeDefault(void); // 241
	//public: int ExchangeAcceptWndInfo::IsValidInfo(void);
};


struct EquipWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
	/* this+16 */ int orgHeight;
	/* this+20 */ int show;

	void MakeDefault(); // 279-286
	BOOL IsValidInfo(); // 264-276
};


struct SkillListWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
	/* this+16 */ int show;

	//public: void SkillListWndInfo::MakeDefault(void); // 291
	//public: int SkillListWndInfo::IsValidInfo(void);
};


struct ItemStoreWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ItemStoreWndInfo::MakeDefault(void); // 314
	//public: int ItemStoreWndInfo::IsValidInfo(void);
};


struct ItemShopWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ItemShopWndInfo::MakeDefault(void); // 336
	//public: int ItemShopWndInfo::IsValidInfo(void);
};


struct ItemSellWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ItemSellWndInfo::MakeDefault(void); // 358
	//public: int ItemSellWndInfo::IsValidInfo(void);
};


struct MessengerGroupWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
	/* this+16 */ int show;
	/* this+20 */ int radio;

	public: void MessengerGroupWndInfo::MakeDefault(void); // 380
	public: int MessengerGroupWndInfo::IsValidInfo(void);

private:
	static hook_method<void (MessengerGroupWndInfo::*)(void)> MessengerGroupWndInfo::_MakeDefault;
	static hook_method<int (MessengerGroupWndInfo::*)(void)> MessengerGroupWndInfo::_IsValidInfo;
};


struct ItemPurchaseWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ItemPurchaseWndInfo::MakeDefault(void); // 406
	//public: int ItemPurchaseWndInfo::IsValidInfo(void);
};


struct ChatRoomWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ChatRoomWndInfo::MakeDefault(void); // 441
	//public: int ChatRoomWndInfo::IsValidInfo(void);
};


struct WhisperWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	void MakeDefault(); // 463
	BOOL IsValidInfo();
};


struct StatusWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
	/* this+16 */ int orgHeight;
	/* this+20 */ int show;

	//public: void StatusWndInfo::MakeDefault(void); // 490
	//public: int StatusWndInfo::IsValidInfo(void);
};


struct OptionWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
	/* this+16 */ int orgHeight;
	/* this+20 */ int show;

	//public: void OptionWndInfo::MakeDefault(void); // 515
	//public: int OptionWndInfo::IsValidInfo(void);
};


struct ShortCutWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
	/* this+16 */ int show;

	public: void ShortCutWndInfo::MakeDefault(void); // 535
	public: int ShortCutWndInfo::IsValidInfo(void);

private:
	static hook_method<void (ShortCutWndInfo::*)(void)> ShortCutWndInfo::_MakeDefault;
	static hook_method<int (ShortCutWndInfo::*)(void)> ShortCutWndInfo::_IsValidInfo;
};


struct ShortenItemWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
	/* this+16 */ int show;

	//public: void ShortenItemWndInfo::MakeDefault(void); // 557
	//public: int ShortenItemWndInfo::IsValidInfo(void);
};


struct ShortenSkillWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ShortenSkillWndInfo::MakeDefault(void); // 579
	//public: int ShortenSkillWndInfo::IsValidInfo(void);
};


struct MerchantItemWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
	/* this+16 */ int show;

	//public: void MerchantItemWndInfo::MakeDefault(void); // 589
	//public: int MerchantItemWndInfo::IsValidInfo(void);
};


struct MerchantMirrorItemWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void MerchantMirrorItemWndInfo::MakeDefault(void); // 611
	//public: int MerchantMirrorItemWndInfo::IsValidInfo(void);
};


struct MerchantShopMakeWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void MerchantShopMakeWndInfo::MakeDefault(void); // 632
	//public: int MerchantShopMakeWndInfo::IsValidInfo(void);
};


struct MerchantItemShopWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	public: void MerchantItemShopWndInfo::MakeDefault(void); // 654
	public: int MerchantItemShopWndInfo::IsValidInfo(void);

private:
	static hook_method<void (MerchantItemShopWndInfo::*)(void)> MerchantItemShopWndInfo::_MakeDefault;
	static hook_method<int (MerchantItemShopWndInfo::*)(void)> MerchantItemShopWndInfo::_IsValidInfo;
};


struct MerchantItemMyShopWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void MerchantItemMyShopWndInfo::MakeDefault(void); // 677
	//public: int MerchantItemMyShopWndInfo::IsValidInfo(void);
};


struct MerchantItemPurchaseWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void MerchantItemPurchaseWndInfo::MakeDefault(void); // 698
	//public: int MerchantItemPurchaseWndInfo::IsValidInfo(void);
};


struct FriendOptionWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	void MakeDefault(); // 719
	int IsValidInfo();
};


struct ItemIdentifyWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ItemIdentifyWndInfo::MakeDefault(void); // 742
	//public: int ItemIdentifyWndInfo::IsValidInfo(void);
};


struct ItemCompositionWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void ItemCompositionWndInfo::MakeDefault(void); // 764
	//public: int ItemCompositionWndInfo::IsValidInfo(void);
};


struct EmotionWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void EmotionWndInfo::MakeDefault(void); // 799
	//public: int EmotionWndInfo::IsValidInfo(void);
};


struct EmotionListWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void EmotionListWndInfo::MakeDefault(void); // 823
	//public: int EmotionListWndInfo::IsValidInfo(void);
};


struct PetInfoWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;

	//public: void PetInfoWndInfo::MakeDefault(void); // 843
	//public: int PetInfoWndInfo::IsValidInfo(void);
};


struct WhisperListWndInfo
{
	/* this+ 0 */ int x;
	/* this+ 4 */ int y;
	/* this+ 8 */ int w;
	/* this+12 */ int h;
	/* this+16 */ int show;

	//public: void WhisperListWndInfo::MakeDefault(void); // ???
	//public: int WhisperListWndInfo::IsValidInfo(void);
};
