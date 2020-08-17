#pragma once


class CLanguage
{
	/* this+  0 */ public: //const CLanguage::`vftable';
	/* this+  4 */ BYTE dummy[176];
	/* this+180 */ LANGID m_scriptLangId;

	struct vtable_t
	{
		void* (CLanguage::* scalar_deleting_destructor)(unsigned int __flags);
		const char* (CLanguage::* GetKeyStroke)(void);
		int (CLanguage::* GetKeyStrokeSize)(void);
		void (CLanguage::* SetKeyStroke)(unsigned char key);
		long (CLanguage::* ProcessImeMessage)(HWND hWnd, unsigned int message, unsigned int wParam, long lParam, bool* trapped);
		const char* (CLanguage::* GetWordBreak)(const char* text, unsigned int size);
		void (CLanguage::* GetImeCompStr)(void);
		void (CLanguage::* BeginKeyStroke)(void);
		void (CLanguage::* EndKeyStroke)(void);
		void (CLanguage::* ClearKeyStroke)(void);
	};

	public: CLanguage::CLanguage(void);
	public: virtual CLanguage::~CLanguage(void);
	public: virtual const char* CLanguage::GetKeyStroke(void);
	public: virtual int CLanguage::GetKeyStrokeSize(void);
	public: virtual void CLanguage::SetKeyStroke(unsigned char key);
	public: virtual long CLanguage::ProcessImeMessage(HWND hWnd, unsigned int message, unsigned int wParam, long lParam, bool* trapped);
	public: virtual const char* CLanguage::GetWordBreak(const char* text, unsigned int size);
	public: virtual void CLanguage::GetImeCompStr(void);
	public: virtual void CLanguage::BeginKeyStroke(void);
	public: virtual void CLanguage::EndKeyStroke(void);
	public: virtual void CLanguage::ClearKeyStroke(void);
	const char* LanguageFile(const char* fName);
	const char* GetLanguageCharset(bool bScript);

public:
	static hook_func<CLanguage* (CLanguage::*)(void)> CLanguage::_cCLanguage;
	static hook_func<void (CLanguage::*)(void)> CLanguage::_dCLanguage;
	static hook_func<const char* (CLanguage::*)(void)> CLanguage::_GetKeyStroke;
	static hook_func<int (CLanguage::*)(void)> CLanguage::_GetKeyStrokeSize;
	static hook_func<void (CLanguage::*)(unsigned char key)> CLanguage::_SetKeyStroke;
	static hook_func<long (CLanguage::*)(HWND hWnd, unsigned int message, unsigned int wParam, long lParam, bool* trapped)> CLanguage::_ProcessImeMessage;
	static hook_func<const char* (CLanguage::*)(const char* text, unsigned int size)> CLanguage::_GetWordBreak;
	static hook_func<void (CLanguage::*)(void)> CLanguage::_GetImeCompStr;
	static hook_func<void (CLanguage::*)(void)> CLanguage::_BeginKeyStroke;
	static hook_func<void (CLanguage::*)(void)> CLanguage::_EndKeyStroke;
	static hook_func<void (CLanguage::*)(void)> CLanguage::_ClearKeyStroke;
	static hook_func<const char* (CLanguage::*)(const char* fName)> CLanguage::_LanguageFile;
	static hook_func<const char* (CLanguage::*)(bool bScript)> CLanguage::_GetLanguageCharset;
};
C_ASSERT( sizeof CLanguage == 184 );


extern CLanguage*& g_language;
