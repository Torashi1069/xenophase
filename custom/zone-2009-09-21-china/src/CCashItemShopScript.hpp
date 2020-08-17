#pragma once
#include "CFTToken.hpp"
#include "std/map"


class CCashItemShopScript
{
public:
	class CProduct
	{
		/* this+0x0 */ unsigned short m_ITID;
		/* this+0x4 */ int m_Price;

		//public: bool operator==(const class CCashItemShopScript::CProduct &);
		//public: void CProduct(void);
		//public: void CProduct(const unsigned short, const int);
		//public: void ~CProduct(void);
	};

	class ANAYSISRET
	{
		enum enumCode
		{
			CODE_SUCCESS                          = 0,
			CODE_ERROR                            = 1,
			CODE_ERROR_LEXICALANALYSIS_INITIALIZE = 2,
			CODE_ERROR_GET_TOKEN                  = 3,
			CODE_ERROR_SYNTAX                     = 4,
			CODE_ERROR_UNKNOWN                    = 5,
			CODE_ERROR_UNKNOWN_ITEMID             = 6,
			CODE_ERROR_VERSION                    = 7,
			CODE_ERROR_INSERT_ITEMSTAND           = 8,
			CODE_ERROR_INSERT_ITEMSTANDCONTAINER  = 9,
		};

		/* this+0x0  */ CFTToken Token;
		/* this+0x2C */ enum CCashItemShopScript::ANAYSISRET::enumCode Code;

		//public: void CCashItemShopScript::ANAYSISRET::ANAYSISRET(const enum CCashItemShopScript::ANAYSISRET::enumCode in_Code, class CFTToken& in_Token);
		//public: void CCashItemShopScript::ANAYSISRET::ANAYSISRET(const enum CCashItemShopScript::ANAYSISRET::enumCode in_Code);
		//public: void CCashItemShopScript::ANAYSISRET::~ANAYSISRET(void);
	};

	/* this+0x0 */ //const CCashItemShopScript::`vftable'
	/* this+0x4 */ mystd::map< mystd::string, mystd::vector<CCashItemShopScript::CProduct> > m_ItemStandContainer;
	/* static   */ static hook_ptr<CCashItemShopScript*> m_cpSelf;

	typedef mystd::map< mystd::string, mystd::vector<CCashItemShopScript::CProduct> >::const_iterator ITEMSTANDCONTAINERITOR;

	//private: class CCashItemShopScript::ANAYSISRET CCashItemShopScript::Anaysis(const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >, const int);
	public: static CCashItemShopScript* __cdecl CCashItemShopScript::GetObj(void);
	//public: void WriteFile(const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >);
	public: mystd::vector<CCashItemShopScript::CProduct>* CCashItemShopScript::GetStandMapPtr(const mystd::string in_strStandName);
	//public: int CCashItemShopScript::GetItemPrice(const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >, const unsigned short);
	public: bool CCashItemShopScript::Init(void);
	private: CCashItemShopScript::CCashItemShopScript(void);
	private: virtual CCashItemShopScript::~CCashItemShopScript(void);

private:
	static hook_method<static CCashItemShopScript* (__cdecl *)(void)> CCashItemShopScript::_GetObj;
	static hook_method<mystd::vector<CCashItemShopScript::CProduct>* (CCashItemShopScript::*)(const mystd::string in_strStandName)> CCashItemShopScript::_GetStandMapPtr;
	static hook_method<bool (CCashItemShopScript::*)(void)> CCashItemShopScript::_Init;
};
