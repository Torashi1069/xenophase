#pragma once
#include "Struct.h"


class CLanguage
{
public:
	struct vtable_t
	{
		void* (CLanguage::* scalar_deleting_destructor)(unsigned int flags);
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

	/* this+  0 */ public: //const CLanguage::`vftable';
	/* this+  4 */ protected: mystd::deque<unsigned long> m_fakeInput;
	/* this+ 52 */ protected: mystd::string m_input;
	/* this+ 68 */ protected: int m_inputCursor;
	/* this+ 72 */ protected: int m_selectionCursor;
	/* this+ 76 */ protected: int m_selectionOrigin;
	/* this+ 80 */ protected: mystd::string m_keyStroke;
	/* this+ 96 */ protected: mystd::string m_compStr;
	/* this+112 */ protected: int m_compCursorPos;
	/* this+116 */ protected: CANDIDATELIST* m_candidateList;
	/* this+120 */ protected: int m_candidateCount;
	/* this+124 */ protected: int m_candidatePageSize;
	/* this+128 */ protected: int m_candidateSelection;
	/* this+132 */ protected: mystd::vector<unsigned char> m_candidateBuffer;
	/* this+148 */ protected: bool m_bHideText;
	/* this+150 */ protected: LANGID m_langId;
	/* this+152 */ protected: unsigned int m_codePage;

	public: CLanguage::CLanguage(void);
	public: virtual CLanguage::~CLanguage(void);
	//public: void SetHWnd(struct HWND__ *);
	public: void CLanguage::GetLanguageText(mystd::string* text);
	public: const char* CLanguage::GetLanguageCharset(void);
	public: const char* CLanguage::GetInput(void);
	public: void CLanguage::SetInput(const char* input);
	public: int CLanguage::GetInputSize(void);
	public: void CLanguage::ResetInput(void);
	public: void CLanguage::GetSelection(int* origin, int* cursor);
	public: void CLanguage::GetSelectionRange(int* start, int* end);
	public: void CLanguage::SetSelection(int origin, int cursor);
	//public: int GetSelectionCursor();
	//public: int GetSelectionSize();
	public: virtual const char* CLanguage::GetKeyStroke(void); // line 42
	public: virtual int CLanguage::GetKeyStrokeSize(void); // line 43
	public: virtual void CLanguage::SetKeyStroke(unsigned char key); // line 44
	//public: const char* GetCompositionString();
	//public: int GetCompositionStringSize();
	//public: int GetCompositionCursorPos();
	public: const char* CLanguage::GetCandidateString(int nCandidate);
	public: int CLanguage::GetCandidateCount(void);
	public: int CLanguage::GetCandidateSelection(void);
	//public: int GetCandidatePageSize();
	public: virtual long CLanguage::ProcessImeMessage(HWND hWnd, unsigned int message, unsigned int wParam, long lParam, bool* trapped);
	public: void CLanguage::OnKeyDown(unsigned int wParam, long lParam);
	public: void CLanguage::OnChar(unsigned int wParam, long lParam);
	public: void CLanguage::HideText(bool bHideText);
	public: virtual const char* CLanguage::GetWordBreak(const char* text, unsigned int size);
	protected: virtual void CLanguage::GetImeCompStr(void);
	protected: void CLanguage::GetImeResultStr(void);
	protected: void CLanguage::GetImeCursorPos(void);
	//protected: void CLanguage::GetImeCandidateList();
	protected: void CLanguage::CancelComposition(void);
	protected: void CLanguage::AddInput(const char* input);
	//protected: void CLanguage::CopyTextToClipBoard();
	//protected: void CLanguage::CopyTextFromClipBoard();
	//protected: void CLanguage::CutTextToClipBoard();
	protected: void CLanguage::IncreaseSelection(void);
	protected: void CLanguage::DecreaseSelection(void);
	protected: void CLanguage::DeleteSelection(void);
	//protected: void ClearSelection();
	//protected: void CancelSelection();
	//protected: void ClearComposition();
	//protected: void ReadCandidate();
	//protected: void ClearCandidate();
	protected: virtual void CLanguage::BeginKeyStroke(void); // line 89
	protected: virtual void CLanguage::EndKeyStroke(void); // line 90
	protected: virtual void CLanguage::ClearKeyStroke(void); // line 91

private:
	static hook_method<void (CLanguage::*)(mystd::string* text)> CLanguage::_GetLanguageText;
	static hook_method<const char* (CLanguage::*)(void)> CLanguage::_GetLanguageCharset;
	static hook_method<const char* (CLanguage::*)(void)> CLanguage::_GetInput;
	static hook_method<void (CLanguage::*)(const char* input)> CLanguage::_SetInput;
	static hook_method<int (CLanguage::*)(void)> CLanguage::_GetInputSize;
	static hook_method<void (CLanguage::*)(void)> CLanguage::_ResetInput;
	static hook_method<void (CLanguage::*)(int* origin, int* cursor)> CLanguage::_GetSelection;
	static hook_method<void (CLanguage::*)(int* start, int* end)> CLanguage::_GetSelectionRange;
	static hook_method<void (CLanguage::*)(int origin, int cursor)> CLanguage::_SetSelection;
	static hook_method<const char* (CLanguage::*)(void)> CLanguage::_GetKeyStroke;
	static hook_method<int (CLanguage::*)(void)> CLanguage::_GetKeyStrokeSize;
	static hook_method<void (CLanguage::*)(unsigned char key)> CLanguage::_SetKeyStroke;
	static hook_method<const char* (CLanguage::*)(int nCandidate)> CLanguage::_GetCandidateString;
	static hook_method<int (CLanguage::*)(void)> CLanguage::_GetCandidateCount;
	static hook_method<int (CLanguage::*)(void)> CLanguage::_GetCandidateSelection;
	static hook_method<long (CLanguage::*)(HWND hWnd, unsigned int message, unsigned int wParam, long lParam, bool* trapped)> CLanguage::_ProcessImeMessage;
	static hook_method<void (CLanguage::*)(unsigned int wParam, long lParam)> CLanguage::_OnKeyDown;
	static hook_method<void (CLanguage::*)(unsigned int wParam, long lParam)> CLanguage::_OnChar;
	static hook_method<void (CLanguage::*)(bool bHideText)> CLanguage::_HideText;
	static hook_method<const char* (CLanguage::*)(const char* text, unsigned int size)> CLanguage::_GetWordBreak;
	static hook_method<void (CLanguage::*)(void)> CLanguage::_GetImeCompStr;
	static hook_method<void (CLanguage::*)(void)> CLanguage::_GetImeResultStr;
	static hook_method<void (CLanguage::*)(void)> CLanguage::_GetImeCursorPos;
	static hook_method<void (CLanguage::*)(void)> CLanguage::_CancelComposition;
	static hook_method<void (CLanguage::*)(const char* input)> CLanguage::_AddInput;
	static hook_method<void (CLanguage::*)(void)> CLanguage::_IncreaseSelection;
	static hook_method<void (CLanguage::*)(void)> CLanguage::_DecreaseSelection;
	static hook_method<void (CLanguage::*)(void)> CLanguage::_DeleteSelection;
	static hook_method<void (CLanguage::*)(void)> CLanguage::_BeginKeyStroke;
	static hook_method<void (CLanguage::*)(void)> CLanguage::_EndKeyStroke;
	static hook_method<void (CLanguage::*)(void)> CLanguage::_ClearKeyStroke;
};


struct TCINPUTKEY
{
	/* this+0 */ unsigned char offset;
	/* this+1 */ char text[3];
};


class CLanguageTC : public CLanguage
{
public:
	struct vtable_t // const CLanguageTC::`vftable'
	{
		void (CLanguageTC::* scalar_deleting_destructor)(unsigned int);
		const char* (CLanguageTC::* GetKeyStroke)(void);
		int (CLanguageTC::* GetKeyStrokeSize)(void);
		void (CLanguageTC::* SetKeyStroke)(unsigned char);
		long (CLanguage::* ProcessImeMessage)(HWND hWnd, unsigned int message, unsigned int wParam, long lParam, bool* trapped);
		const char* (CLanguage::* GetWordBreak)(const char* text, unsigned int size);
		void (CLanguageTC::* GetImeCompStr)(void);
		void (CLanguage::* BeginKeyStroke)(void);
		void (CLanguageTC::* EndKeyStroke)(void);
		void (CLanguageTC::* ClearKeyStroke)(void);
	};

	/* this+  0 */ public: //CLanguage baseclass_0;
	/* this+156 */ protected: unsigned char m_tcKeyStrokeEnabled;
	/* this+157 */ protected: unsigned char m_tcKeyStroke;
	/* this+160 */ protected: mystd::list<unsigned char> m_tcKeyStrokeList;
	/* this+172 */ protected: TCINPUTKEY m_tcKeyStrokeTable[256];

	public: CLanguageTC::CLanguageTC(void);
	//public: virtual CLanguageTC::~CLanguageTC(void);
	//public: const char* CLanguageTC::GetKeyStroke();
	//public: int CLanguageTC::GetKeyStrokeSize();
	//public: void CLanguageTC::SetKeyStroke(unsigned char);
	//protected: void CLanguageTC::EndKeyStroke();
	//protected: void CLanguageTC::ClearKeyStroke();
	//protected: void FormatInputKey();
	//protected: void CLanguageTC::GetImeCompStr();
};


class CLanguageTH : public CLanguage
{
	/* this+  0 */ public: //CLanguage baseclass_0;
	/* this+156 */ private: bool m_useTWordBreaker;

	public: CLanguageTH::CLanguageTH(void);
	//public: virtual CLanguageTH::~CLanguageTH(void);
	//public: const char* CLanguageTH::GetWordBreak(const char* text, unsigned int size);
};
