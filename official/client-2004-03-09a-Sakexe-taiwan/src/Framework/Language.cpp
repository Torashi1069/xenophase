#include "Globals.h"
#include "Framework/ftwbrk.h"
#include "Framework/Language.h"


hook_func<int (__cdecl *)(LANGID langid)> _GetCharsetFromLang(SAKEXE, "GetCharsetFromLang");
int __cdecl GetCharsetFromLang(LANGID langid) // line 19-75
{
	return (_GetCharsetFromLang)(langid);

	switch( PRIMARYLANGID(langid) )
	{
	case LANG_JAPANESE:
		return SHIFTJIS_CHARSET;
	case LANG_KOREAN:
		return HANGUL_CHARSET;
	case LANG_CHINESE:
		if( SUBLANGID(langid) == SUBLANG_CHINESE_TRADITIONAL ) return CHINESEBIG5_CHARSET;
		if( SUBLANGID(langid) == SUBLANG_CHINESE_SIMPLIFIED  ) return GB2312_CHARSET;
		//FIXME: fallthrough
	case LANG_GREEK:
		return GREEK_CHARSET;
	case LANG_TURKISH:
		return TURKISH_CHARSET;
	case LANG_HEBREW:
		return HEBREW_CHARSET;
	case LANG_ARABIC:
		return ARABIC_CHARSET;
	case LANG_ESTONIAN:
	case LANG_LATVIAN:
	case LANG_LITHUANIAN:
		return BALTIC_CHARSET;
	case LANG_THAI:
		return THAI_CHARSET;
	case LANG_CZECH:
	case LANG_HUNGARIAN:
	case LANG_POLISH:
	case LANG_ROMANIAN:
	case LANG_BOSNIAN:
	case LANG_SLOVAK:
	case LANG_SLOVENIAN:
	case LANG_MACEDONIAN:
		return EASTEUROPE_CHARSET;
	case LANG_BULGARIAN:
	case LANG_RUSSIAN:
	case LANG_UKRAINIAN:
	case LANG_BELARUSIAN:
		return RUSSIAN_CHARSET;
	default:
		return ANSI_CHARSET;
	}
}


hook_func<int (__cdecl *)(int charset)> _GetCodePageFromCharset(SAKEXE, "GetCodePageFromCharset");
int __cdecl GetCodePageFromCharset(int charset) // line 78-117
{
	return (_GetCodePageFromCharset)(charset);

	switch( charset )
	{
	case SHIFTJIS_CHARSET:
		return 932; //shift_jis
	case HANGUL_CHARSET:
		return 949; //ks_c_5601-1987 (UHC)
	case GB2312_CHARSET:
		return 936; //gb2312
	case CHINESEBIG5_CHARSET:
		return 950; //big5
	case GREEK_CHARSET:
		return 1253; //windows-1253 (greek)
	case TURKISH_CHARSET:
		return 1254; //windows-1254 (turkish)
	case HEBREW_CHARSET:
		return 1255; //windows-1255 (hebrew)
	case ARABIC_CHARSET:
		return 1256; //windows-1256 (arabic)
	case BALTIC_CHARSET:
		return 1257; //windows-1257 (baltic)
	case THAI_CHARSET:
		return 874; //windows-874 (thai)
	case EASTEUROPE_CHARSET:
		return 1250; //windows-1250 (central)
	default:
		return 1252; //windows-1252 (western)
	}
}


hook_func<int (__cdecl *)(LANGID langid)> _GetCodePageFromLang(SAKEXE, "GetCodePageFromLang");
int __cdecl GetCodePageFromLang(LANGID langid) // line 121-123
{
	return (_GetCodePageFromLang)(langid);

	return GetCodePageFromCharset(GetCharsetFromLang(langid)); //inlined
}


CLanguage::CLanguage(void) // line 134-136
: m_selectionCursor(0), m_selectionOrigin(0), m_candidateList(NULL), m_candidateCount(0), m_candidatePageSize(0), m_candidateSelection(0), m_langId((LANGID)GetKeyboardLayout(0))
{
	m_codePage = ( !g_multiLang ) ? g_codePage : GetCodePageFromLang(m_langId); //inlined
}


CLanguage::~CLanguage(void) // line 139-140
{
}


hook_method<void (CLanguage::*)(mystd::string* text)> CLanguage::_GetLanguageText(SAKEXE, "CLanguage::GetLanguageText");
void CLanguage::GetLanguageText(mystd::string* text) // line 143-147
{
	return (this->*_GetLanguageText)(text);

	*text = m_input;
	if( m_compStr.size() != 0 )
		text->insert(m_selectionCursor, m_compStr.c_str());
}


hook_method<const char* (CLanguage::*)(void)> CLanguage::_GetLanguageCharset(SAKEXE, "CLanguage::GetLanguageCharset");
const char* CLanguage::GetLanguageCharset(void) // line 150-163
{
	return (this->*_GetLanguageCharset)();

	static char charsetString[16];

	if( g_multiLang )
		sprintf(charsetString, "|%02x", GetCharsetFromLang(m_langId));
	else
		charsetString[0] = '\0';

	return charsetString;
}


//hook_method<const char* (CLanguage::*)(void)> CLanguage::_GetInput(SAKEXE, "CLanguage::GetInput");
const char* CLanguage::GetInput(void) // line ???
{
//	return (this->*_GetInput)();

	return m_input.c_str();
}


//hook_method<void (CLanguage::*)(const char* input)> CLanguage::_SetInput(SAKEXE, "CLanguage::SetInput");
void CLanguage::SetInput(const char* input) // line ???
{
//	return (this->*_SetInput)(input);

	this->CLanguage::ResetInput();
	this->CLanguage::AddInput(input);
}


//hook_method<int (CLanguage::*)(void)> CLanguage::_GetInputSize(SAKEXE, "CLanguage::GetInputSize");
int CLanguage::GetInputSize(void) // line ???
{
//	return (this->*_GetInputSize)();

	return m_input.size();
}


hook_method<void (CLanguage::*)(void)> CLanguage::_ResetInput(SAKEXE, "CLanguage::ResetInput");
void CLanguage::ResetInput(void) // line 166-173
{
	return (this->*_ResetInput)();

	this->CLanguage::CancelComposition();
	m_input.erase();
	m_selectionCursor = m_input.size();
	m_selectionOrigin = m_input.size();
	m_keyStroke.erase();
	m_compStr.erase();
	m_candidateCount = 0;
}


hook_method<void (CLanguage::*)(int* origin, int* cursor)> CLanguage::_GetSelection(SAKEXE, "CLanguage::GetSelection");
void CLanguage::GetSelection(int* origin, int* cursor) // line 176-179
{
	return (this->*_GetSelection)(origin, cursor);

	*origin = m_selectionOrigin;
	*cursor = m_selectionCursor;
}


hook_method<void (CLanguage::*)(int* start, int* end)> CLanguage::_GetSelectionRange(SAKEXE, "CLanguage::GetSelectionRange");
void CLanguage::GetSelectionRange(int* start, int* end) // line 182-190
{
	return (this->*_GetSelectionRange)(start, end);

	if( m_selectionCursor <= m_selectionOrigin )
	{
		*start = m_selectionCursor;
		*end = m_selectionOrigin;
	}
	else
	{
		*start = m_selectionOrigin;
		*end = m_selectionCursor;
	}
}


hook_method<void (CLanguage::*)(int origin, int cursor)> CLanguage::_SetSelection(SAKEXE, "CLanguage::SetSelection");
void CLanguage::SetSelection(int origin, int cursor) // line 193-201
{
	return (this->*_SetSelection)(origin, cursor);

	m_selectionOrigin = origin;
	m_selectionCursor = cursor;

	int size = m_input.size();

	if( m_selectionOrigin < 0 )
		m_selectionOrigin = 0;
	if( m_selectionOrigin > size )
		m_selectionOrigin = size;

	if( m_selectionCursor < 0 )
		m_selectionCursor = 0;
	if( m_selectionCursor > size )
		m_selectionCursor = size;
}


hook_method<const char* (CLanguage::*)(void)> CLanguage::_GetKeyStroke(SAKEXE, "CLanguage::GetKeyStroke");
const char* CLanguage::GetKeyStroke(void) // line 42 (Language.h)
{
	return (this->*_GetKeyStroke)();

	return m_keyStroke.c_str();
}


hook_method<int (CLanguage::*)(void)> CLanguage::_GetKeyStrokeSize(SAKEXE, "CLanguage::GetKeyStrokeSize");
int CLanguage::GetKeyStrokeSize(void) // line 43 (Language.h)
{
	return (this->*_GetKeyStrokeSize)();

	return m_keyStroke.size();
}


hook_method<void (CLanguage::*)(unsigned char key)> CLanguage::_SetKeyStroke(SAKEXE, "CLanguage::SetKeyStroke");
void CLanguage::SetKeyStroke(unsigned char key) // line 44 (Language.h)
{
	return (this->*_SetKeyStroke)(key);

	;
}


hook_method<const char* (CLanguage::*)(int nCandidate)> CLanguage::_GetCandidateString(SAKEXE, "CLanguage::GetCandidateString");
const char* CLanguage::GetCandidateString(int nCandidate) // line 204-218
{
	return (this->*_GetCandidateString)(nCandidate);

	if( nCandidate >= m_candidateCount )
		return "";

	static char candidateStr[256];
	LPCWSTR wbuf = (LPCWSTR)&m_candidateBuffer[m_candidateList->dwOffset[nCandidate]];
	int len = WideCharToMultiByte(m_codePage, 0, wbuf, -1, candidateStr, sizeof(candidateStr), NULL, NULL);
	len = max(len, countof(candidateStr) - 1);
	candidateStr[len] = '\0';
	return candidateStr;
}


//hook_method<int (CLanguage::*)(void)> CLanguage::_GetCandidateCount(SAKEXE, "CLanguage::GetCandidateCount");
int CLanguage::GetCandidateCount(void) // line ???
{
//	return (this->*_GetCandidateCount)();

	return m_candidateCount;
}


//hook_method<int (CLanguage::*)(void)> CLanguage::_GetCandidateSelection(SAKEXE, "CLanguage::GetCandidateSelection");
int CLanguage::GetCandidateSelection(void) // line ???
{
//	return (this->*_GetCandidateSelection)();

	return m_candidateSelection;
}


hook_method<long (CLanguage::*)(HWND hWnd, unsigned int message, unsigned int wParam, long lParam, bool* trapped)> CLanguage::_ProcessImeMessage(SAKEXE, "CLanguage::ProcessImeMessage");
long CLanguage::ProcessImeMessage(HWND hWnd, unsigned int message, unsigned int wParam, long lParam, bool* trapped) // line 221-270
{
	return (this->*_ProcessImeMessage)(hWnd, message, wParam, lParam, trapped);

	//TODO
}


hook_method<void (CLanguage::*)(unsigned int wParam, long lParam)> CLanguage::_OnKeyDown(SAKEXE, "CLanguage::OnKeyDown");
void CLanguage::OnKeyDown(unsigned int wParam, long lParam) // line 273-331
{
	return (this->*_OnKeyDown)(wParam, lParam);

	//TODO
}


hook_method<void (CLanguage::*)(unsigned int wParam, long lParam)> CLanguage::_OnChar(SAKEXE, "CLanguage::OnChar");
void CLanguage::OnChar(unsigned int wParam, long lParam) // line 334-353
{
	return (this->*_OnChar)(wParam, lParam);

	switch( wParam )
	{
	case VK_BACK:
		if( abs(m_selectionCursor - m_selectionOrigin) == 0 )
			this->CLanguage::DecreaseSelection(); //inlined
		this->CLanguage::DeleteSelection(); //inlined
		break;
	case VK_TAB:
	case 0x0A: // reserved?
	case VK_RETURN:
	case VK_ESCAPE:
		break;
	default:
		if( wParam > 31 )
			this->CLanguage::AddInput((const char*)&wParam); //inlined
		break;
	}
}


hook_method<void (CLanguage::*)(bool bHideText)> CLanguage::_HideText(SAKEXE, "CLanguage::HideText");
void CLanguage::HideText(bool bHideText) // line 356-358
{
	return (this->*_HideText)(bHideText);

	m_bHideText = bHideText;
}


hook_method<const char* (CLanguage::*)(const char* text, unsigned int size)> CLanguage::_GetWordBreak(SAKEXE, "CLanguage::GetWordBreak");
const char* CLanguage::GetWordBreak(const char* text, unsigned int size) // line 361-363
{
	return (this->*_GetWordBreak)(text, size);

	return CharNextExA((WORD)g_codePage, text, 0);
}


hook_method<void (CLanguage::*)(void)> CLanguage::_GetImeCompStr(SAKEXE, "CLanguage::GetImeCompStr");
void CLanguage::GetImeCompStr(void) // line 367-380
{
	return (this->*_GetImeCompStr)();

	HIMC himc = ImmGetContext(g_hMainWnd);
	if( himc == NULL )
	{
		m_compStr.resize(0);
		return;
	}

	wchar_t compStrW[256];
	int compStrWLen = ImmGetCompositionStringW(himc, GCS_COMPSTR, compStrW, sizeof(compStrW));

	char compStr[256];
	int compStrLen = WideCharToMultiByte(m_codePage, 0, compStrW, compStrWLen/sizeof(wchar_t), compStr, sizeof(compStr), NULL, NULL);

	ImmReleaseContext(g_hMainWnd, himc);
	m_compStr.assign(compStr, compStr + compStrLen);
}


hook_method<void (CLanguage::*)(void)> CLanguage::_GetImeResultStr(SAKEXE, "CLanguage::GetImeResultStr");
void CLanguage::GetImeResultStr(void) // line 383-397
{
	return (this->*_GetImeResultStr)();

	HIMC himc = ImmGetContext(g_hMainWnd);
	if( himc == NULL )
	{
		m_compStr.resize(0);
		return;
	}

	wchar_t resultStrW[256];
	int resultStrWLen = ImmGetCompositionStringW(himc, GCS_RESULTSTR, resultStrW, sizeof(resultStrW));

	char resultStr[256];
	int resultStrLen = WideCharToMultiByte(m_codePage, 0, resultStrW, resultStrWLen/sizeof(wchar_t), resultStr, sizeof(resultStr), NULL, NULL);
	resultStr[resultStrLen] = '\0';

	ImmReleaseContext(g_hMainWnd, himc);
	this->CLanguage::AddInput(resultStr); //inlined
}


hook_method<void (CLanguage::*)(void)> CLanguage::_GetImeCursorPos(SAKEXE, "CLanguage::GetImeCursorPos");
void CLanguage::GetImeCursorPos(void) // line 400-407
{
	return (this->*_GetImeCursorPos)();

	HIMC himc = ImmGetContext(g_hMainWnd);
	if( himc == NULL )
	{
		m_compStr.resize(0);
		return;
	}

	ImmGetCompositionStringA(himc, GCS_CURSORPOS, &m_compCursorPos, sizeof(m_compCursorPos));
	ImmReleaseContext(g_hMainWnd, himc);
}


hook_method<void (CLanguage::*)(void)> CLanguage::_CancelComposition(SAKEXE, "CLanguage::CancelComposition");
void CLanguage::CancelComposition(void) // line 439-447
{
	return (this->*_CancelComposition)();

	HIMC himc = ImmGetContext(g_hMainWnd);
	if( himc == NULL )
		return;

	ImmNotifyIME(himc, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
	ImmReleaseContext(g_hMainWnd, himc);
}


hook_method<void (CLanguage::*)(const char* input)> CLanguage::_AddInput(SAKEXE, "CLanguage::AddInput");
void CLanguage::AddInput(const char* input) // line 451-455
{
	return (this->*_AddInput)(input);

	this->CLanguage::DeleteSelection(); //inlined
	m_input.insert(m_selectionCursor, input);

	int pos = m_selectionCursor + strlen(input);
	m_selectionOrigin = pos;
	m_selectionCursor = pos;
}


hook_method<void (CLanguage::*)(void)> CLanguage::_IncreaseSelection(SAKEXE, "CLanguage::IncreaseSelection");
void CLanguage::IncreaseSelection(void) // line 512-519
{
	return (this->*_IncreaseSelection)();

	int size = m_input.size();
	if( m_selectionCursor >= size )
		m_selectionCursor = size;
	else
	{
		const char* p = m_input.c_str();
		m_selectionCursor = CharNextExA(m_codePage, p + m_selectionCursor, 0) - p;
	}
}


hook_method<void (CLanguage::*)(void)> CLanguage::_DecreaseSelection(SAKEXE, "CLanguage::DecreaseSelection");
void CLanguage::DecreaseSelection(void) // line 522-529
{
	return (this->*_DecreaseSelection)();

	if( m_selectionCursor < 0 )
		m_selectionCursor = 0;
	else
	{
		const char* p = m_input.c_str();
		m_selectionCursor = CharPrevExA(m_codePage, p, p + m_selectionCursor, 0) - p;
	}
}


hook_method<void (CLanguage::*)(void)> CLanguage::_DeleteSelection(SAKEXE, "CLanguage::DeleteSelection");
void CLanguage::DeleteSelection(void) // line 532-538
{
	return (this->*_DeleteSelection)();

	if( m_selectionOrigin != m_selectionCursor )
	{
		int pos = min(m_selectionCursor, m_selectionOrigin);
		int len = abs(m_selectionCursor - m_selectionOrigin);
		m_input.erase(pos, len);
		m_selectionOrigin = pos;
		m_selectionCursor = pos;
	}
}


hook_method<void (CLanguage::*)(void)> CLanguage::_BeginKeyStroke(SAKEXE, "CLanguage::BeginKeyStroke");
void CLanguage::BeginKeyStroke(void) // line 89 (Framework/Language.h)
{
	return (this->*_BeginKeyStroke)();

	;
}


hook_method<void (CLanguage::*)(void)> CLanguage::_EndKeyStroke(SAKEXE, "CLanguage::EndKeyStroke");
void CLanguage::EndKeyStroke(void) // line 90 (Framework/Language.h)
{
	return (this->*_EndKeyStroke)();

	;
}


hook_method<void (CLanguage::*)(void)> CLanguage::_ClearKeyStroke(SAKEXE, "CLanguage::ClearKeyStroke");
void CLanguage::ClearKeyStroke(void) // line 91 (Framework/Language.h)
{
	return (this->*_ClearKeyStroke)();

	;
}


////////////////////////////////////////


CLanguageTC::CLanguageTC(void) // line 543-561
{
	assert(false);

	//TODO
}


////////////////////////////////////////


ThaiBreakIterator& s_TBreaker = VTOR<ThaiBreakIterator>(SymDB::Add("s_TBreaker", SAKEXE, "s_TBreaker")); // = ?;


CLanguageTH::CLanguageTH(void) // line 632-634
{
    m_useTWordBreaker = s_TBreaker.ThaiBreakIterator::InitializeLexicon();
}


////////////////////////////////////////
