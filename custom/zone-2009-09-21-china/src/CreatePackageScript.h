#pragma once
#include "CFTToken.hpp"
#include "std/map"
#include "std/vector"


class CCreatePackageScript
{
	class PackageItem
	{
		/* this+0 */ public: int ITID;
		/* this+4 */ public: int Count;
		/* this+8 */ public: int HireHour;

		//public: void PackageItem();
	};

	class IPBox
	{
		class Item : public CCreatePackageScript::PackageItem
		{
			/* this+ 0 */ public: //CCreatePackageScript::PackageItem baseclass_0;
			/* this+12 */ public: int gift_number;
			/* this+16 */ public: int random_factor;

			//public: void Item();
		};

		enum enumType
		{
			UNKNOWN = 0,
			MUST    = 1,
			RANDOM  = 2,
		};

		/* this+ 0 */ public: mystd::vector<CCreatePackageScript::IPBox::Item> ItemList;
		/* this+16 */ public: int gift_total_number;
		/* this+20 */ public: enum CCreatePackageScript::IPBox::enumType Type;

		//public: bool Insert(class CCreatePackageScript::IPBox::Item &);
		//public: void Clear();
		//public: int GetNumber();
		//public: void CCreatePackageScript::IPBox::IPBox();
		//public: void CCreatePackageScript::IPBox::~IPBox();
	};

	class IPPackage
	{
		/* this+0 */ public: mystd::vector<CCreatePackageScript::IPBox> m_BoxList;

		//public: void Clear();
		//public: int GetNumber();
		//public: bool Insert(class CCreatePackageScript::IPBox &);
		//public: void IPPackage();
		//public: void CCreatePackageScript::IPPackage::~IPPackage();
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
			CODE_ERROR_NO_FILE                    = 9,
			CODE_ERROR_EQUIPTITEM_COUNT           = 10,
		};

		/* this+ 0 */ public: CFTToken Token;
		/* this+44 */ public: enum CCreatePackageScript::ANAYSISRET::enumCode Code;

		//public: void CCreatePackageScript::ANAYSISRET::ANAYSISRET(const enum CCreatePackageScript::ANAYSISRET::enumCode, class CFTToken &);
		//public: void CCreatePackageScript::ANAYSISRET::ANAYSISRET(const enum CCreatePackageScript::ANAYSISRET::enumCode);
		//public: void CCreatePackageScript::ANAYSISRET::~ANAYSISRET();
	};

	/* this+ 0 */ public: //const CCreatePackageScript::`vftable';
	/* this+ 4 */ private: mystd::map<int,CCreatePackageScript::IPPackage> m_PackageContainer;
	/* this+16 */ private: bool m_bOK;
	/* static  */ private: static CCreatePackageScript*& m_cpSelf;

	typedef mystd::map<int,CCreatePackageScript::IPPackage> PACKAGECONTAINERITOR;

	//private: bool Anaysis_InsertPackage(const int, class CCreatePackageScript::IPPackage &);
	private: CCreatePackageScript::ANAYSISRET CCreatePackageScript::Anaysis(const mystd::string in_strFileName);
	//private: CCreatePackageScript::ANAYSISRET CCreatePackageScript::Anaysis_Package(const int in_ITID, CFTLexicalAnaysis& in_LexicalAnaysis);
	//private: CCreatePackageScript::ANAYSISRET CCreatePackageScript::Anaysis_Box_Must(CCreatePackageScript::IPPackage& in_Package, CFTLexicalAnaysis& in_LexicalAnaysis);
	//private: CCreatePackageScript::ANAYSISRET CCreatePackageScript::Anaysis_Box_Random(CCreatePackageScript::IPPackage& in_Package, CFTLexicalAnaysis& in_LexicalAnaysis);
	//private: void CCreatePackageScript::UnpackItemPackage_RandomBox(CCreatePackageScript::IPBox* const in_pBox, mystd::vector<CCreatePackageScript::PackageItem>& out_ItemList);
	public: bool CCreatePackageScript::isOK(void);
	public: bool CCreatePackageScript::Init(void);
	//public: mystd::vector<CCreatePackageScript::PackageItem> CCreatePackageScript::UnpackItemPackage(const int in_ITID);
	public: static CCreatePackageScript* CCreatePackageScript::GetObj(void);
	private: CCreatePackageScript::CCreatePackageScript(void);
	private: virtual CCreatePackageScript::~CCreatePackageScript(void);

private:
	static hook_method<CCreatePackageScript::ANAYSISRET (CCreatePackageScript::*)(const mystd::string in_strFileName)> CCreatePackageScript::_Anaysis;
	static hook_method<bool (CCreatePackageScript::*)(void)> CCreatePackageScript::_isOK;
	static hook_method<bool (CCreatePackageScript::*)(void)> CCreatePackageScript::_Init;
	static hook_method<static CCreatePackageScript* (__cdecl *)(void)> CCreatePackageScript::_GetObj;
};
