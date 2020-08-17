#pragma once


class CGVar
{
public:
	/* this+0x0  */ //const CGVar::`vftable'
	/* static    */ private: static hook_ptr<CGVar *> m_cpSelf;
	/* this+0x4  */ public:  int m_DBColumnSizeBodyItem;
	/* this+0x8  */ public:  int m_DBColumnSizeStoreItem;
	/* this+0xC  */ public:  int m_DBColumnSizeCartItem;
	/* this+0x10 */ public:  unsigned int m_valid_client_file_length;
	/* this+0x14 */ public:  int m_character_data_save_interval_minute;
	/* this+0x18 */ public:  int m_AsyncDBThreadNum;
	/* this+0x1C */ public:  bool m_bOK;

	private: CGVar::CGVar(void);
	private: virtual CGVar::~CGVar(void);
	private: bool CGVar::Create(void);
	private: void CGVar::Destroy(void);
	private: const bool CGVar::isOK(void);
	public: int CGVar::GetDBColumnSizeBodyItem(void);
	public: int CGVar::GetDBColumnSizeStoreItem(void);
	public: int CGVar::GetDBColumnSizeCartItem(void);
	public: int CGVar::GetCharacterDataSaveIntervalMinute(void);
	public: int CGVar::GetAsyncDBThreadNum(void);
	public: unsigned int CGVar::get_valid_client_file_length(void);
	public: unsigned int CGVar::GetUsedMemoryBytes(void);
	public: static CGVar* CGVar::GetObj(void);
	public: static bool CGVar::CreateInstance(void);
	public: static void CGVar::DestroyInstance(void);

private:
	static hook_method<bool (CGVar::*)(void)> CGVar::_Create;
	static hook_method<void (CGVar::*)(void)> CGVar::_Destroy;
	static hook_method<const bool (CGVar::*)(void)> CGVar::_isOK;
	static hook_method<int (CGVar::*)(void)> CGVar::_GetDBColumnSizeBodyItem;
	static hook_method<int (CGVar::*)(void)> CGVar::_GetDBColumnSizeStoreItem;
	static hook_method<int (CGVar::*)(void)> CGVar::_GetDBColumnSizeCartItem;
	static hook_method<int (CGVar::*)(void)> CGVar::_GetCharacterDataSaveIntervalMinute;
	static hook_method<int (CGVar::*)(void)> CGVar::_GetAsyncDBThreadNum;
	static hook_method<unsigned int (CGVar::*)(void)> CGVar::_get_valid_client_file_length;
	static hook_method<unsigned int (CGVar::*)(void)> CGVar::_GetUsedMemoryBytes;
	static hook_method<CGVar* (__cdecl *)(void)> CGVar::_GetObj;
	static hook_method<static bool (__cdecl *)(void)> CGVar::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CGVar::_DestroyInstance;
};
