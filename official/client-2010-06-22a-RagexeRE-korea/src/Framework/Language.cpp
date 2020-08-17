#include "Framework/Language.h"


// globals
CLanguage*& g_language = VTOR<CLanguage*>(SymDB::Find("g_language"));


hook_func<CLanguage* (CLanguage::*)(void)> CLanguage::_cCLanguage("CLanguage::CLanguage");
CLanguage::CLanguage(void)
{
	(this->*_cCLanguage)(); return;
}


hook_func<void (CLanguage::*)(void)> CLanguage::_dCLanguage("CLanguage::~CLanguage");
CLanguage::~CLanguage(void)
{
	(this->*_dCLanguage)(); return;
}


hook_func<const char* (CLanguage::*)(void)> CLanguage::_GetKeyStroke("CLanguage::GetKeyStroke");
const char* CLanguage::GetKeyStroke(void)
{
	return (this->*_GetKeyStroke)();
}


hook_func<int (CLanguage::*)(void)> CLanguage::_GetKeyStrokeSize("CLanguage::GetKeyStrokeSize");
int CLanguage::GetKeyStrokeSize(void)
{
	return (this->*_GetKeyStrokeSize)();
}


hook_func<void (CLanguage::*)(unsigned char key)> CLanguage::_SetKeyStroke("CLanguage::SetKeyStroke");
void CLanguage::SetKeyStroke(unsigned char key)
{
	return (this->*_SetKeyStroke)(key);
}


hook_func<long (CLanguage::*)(HWND hWnd, unsigned int message, unsigned int wParam, long lParam, bool* trapped)> CLanguage::_ProcessImeMessage("CLanguage::ProcessImeMessage");
long CLanguage::ProcessImeMessage(HWND hWnd, unsigned int message, unsigned int wParam, long lParam, bool* trapped)
{
	return (this->*_ProcessImeMessage)(hWnd, message, wParam, lParam, trapped);
}


hook_func<const char* (CLanguage::*)(const char* text, unsigned int size)> CLanguage::_GetWordBreak("CLanguage::GetWordBreak");
const char* CLanguage::GetWordBreak(const char* text, unsigned int size)
{
	return (this->*_GetWordBreak)(text, size);
}


hook_func<void (CLanguage::*)(void)> CLanguage::_GetImeCompStr("CLanguage::GetImeCompStr");
void CLanguage::GetImeCompStr(void)
{
	return (this->*_GetImeCompStr)();
}


hook_func<void (CLanguage::*)(void)> CLanguage::_BeginKeyStroke("CLanguage::BeginKeyStroke");
void CLanguage::BeginKeyStroke(void)
{
	return (this->*_BeginKeyStroke)();
}


hook_func<void (CLanguage::*)(void)> CLanguage::_EndKeyStroke("CLanguage::EndKeyStroke");
void CLanguage::EndKeyStroke(void)
{
	return (this->*_EndKeyStroke)();
}


hook_func<void (CLanguage::*)(void)> CLanguage::_ClearKeyStroke("CLanguage::ClearKeyStroke");
void CLanguage::ClearKeyStroke(void)
{
	return (this->*_ClearKeyStroke)();
}


hook_func<const char* (CLanguage::*)(const char* fName)> CLanguage::_LanguageFile("CLanguage::LanguageFile");
const char* CLanguage::LanguageFile(const char* fName)
{
	return (this->*_LanguageFile)(fName);
}


hook_func<const char* (CLanguage::*)(bool bScript)> CLanguage::_GetLanguageCharset("CLanguage::GetLanguageCharset");
const char* CLanguage::GetLanguageCharset(bool bScript)
{
	return (this->*_GetLanguageCharset)(bScript);
}
