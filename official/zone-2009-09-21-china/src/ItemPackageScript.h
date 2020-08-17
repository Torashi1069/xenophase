#pragma once
#include "CFTToken.hpp"
#include "std/map"
#include "std/vector"


class CItemPackageScript
{
	class PackageItem
	{
		/* this+0x0 */ public: int ITID;
		/* this+0x4 */ public: int Count;
		/* this+0x8 */ public: int HireHour;

		//public: void PackageItem();
	};

	class IPBox
	{
		enum enumType
		{
			UNKNOWN = 0,
			MUST    = 1,
			RANDOM  = 2,
		};

		class Item : public CItemPackageScript::PackageItem
		{
			/* this+ 0 */ public: //CItemPackageScript::PackageItem baseclass_0;
			/* this+12 */ public: int gift_number;
			/* this+16 */ public: int random_factor;

			//public: void Item();
		};

		/* this+ 0 */ public: mystd::vector<CItemPackageScript::IPBox::Item> ItemList;
		/* this+16 */ public: int gift_total_number;
		/* this+20 */ public: enum CItemPackageScript::IPBox::enumType Type;

		//public: bool Insert(class CItemPackageScript::IPBox::Item &);
		//public: void Clear();
		//public: int GetNumber();
		//public: void CItemPackageScript::IPBox::IPBox();
		//public: void CItemPackageScript::IPBox::~IPBox();
	};

	class IPPackage
	{
		/* this+0 */ public: mystd::vector<CItemPackageScript::IPBox> m_BoxList;

		//public: void Clear();
		//public: int GetNumber();
		//public: bool Insert(class CItemPackageScript::IPBox &);
		//public: void IPPackage();
		//public: void CItemPackageScript::IPPackage::~IPPackage();
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
			CODE_ERROR_INSERT_PACKAGE             = 6,
			CODE_ERROR_INSERT_BOX                 = 7,
			CODE_ERROR_UNKNOWN_ITEMID             = 8,
			CODE_ERROR_EQUIPTITEM_COUNT           = 9,
		};

		/* this+ 0 */ public: CFTToken Token;
		/* this+44 */ public: enum CItemPackageScript::ANAYSISRET::enumCode Code;

		//public: void CItemPackageScript::ANAYSISRET::ANAYSISRET(const enum CItemPackageScript::ANAYSISRET::enumCode, class CFTToken &);
		//public: void CItemPackageScript::ANAYSISRET::ANAYSISRET(const enum CItemPackageScript::ANAYSISRET::enumCode);
		//public: void CItemPackageScript::ANAYSISRET::~ANAYSISRET();
	};

	/* this+ 0 */ public: //const CItemPackageScript::`vftable';
	/* this+ 4 */ private: mystd::map<int,CItemPackageScript::IPPackage> m_PackageContainer;
	/* this+16 */ private: bool m_bOK;
	/* static  */ private: static CItemPackageScript*& m_cpSelf;

	typedef mystd::map<int,CItemPackageScript::IPPackage> PACKAGECONTAINERITOR;

	//private: bool Anaysis_InsertPackage(const int, class CItemPackageScript::IPPackage &);
	//private: class CItemPackageScript::ANAYSISRET CItemPackageScript::Anaysis(const class std::basic_string<char,std::char_traits<char>,std::allocator<char> >);
	//private: class CItemPackageScript::ANAYSISRET CItemPackageScript::Anaysis_Package(const int, class CFTLexicalAnaysis &);
	//private: class CItemPackageScript::ANAYSISRET CItemPackageScript::Anaysis_Box_Must(class CItemPackageScript::IPPackage &, class CFTLexicalAnaysis &);
	//private: class CItemPackageScript::ANAYSISRET CItemPackageScript::Anaysis_Box_Random(class CItemPackageScript::IPPackage &, class CFTLexicalAnaysis &);
	//private: void CItemPackageScript::UnpackItemPackage_RandomBox(class CItemPackageScript::IPBox * const, class std::vector<CItemPackageScript::PackageItem,std::allocator<CItemPackageScript::PackageItem> > &);
	//public: bool isOK();
	public: bool CItemPackageScript::Init(void);
	//public: class std::vector<CItemPackageScript::PackageItem,std::allocator<CItemPackageScript::PackageItem> > CItemPackageScript::UnpackItemPackage(const int);
	public: static CItemPackageScript* CItemPackageScript::GetObj(void);
	private: CItemPackageScript::CItemPackageScript(void);
	private: virtual CItemPackageScript::~CItemPackageScript(void);

private:
	static hook_method<bool (CItemPackageScript::*)(void)> CItemPackageScript::_Init;
	static hook_method<static CItemPackageScript* (__cdecl*)(void)> CItemPackageScript::_GetObj;
};
