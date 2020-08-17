#pragma once


struct TRIE
{
	unsigned char ch; // char
	bool wrap;        // can break word?
	void* next;       // pointer to next node in save level
	void* child;      // pointer to next level
};


struct DICTVERSION
{
	unsigned char fv; // version of 'Find Thai Word Break' routine.
	unsigned char dv; // version of 'Dictionary'.
};


struct DICTHEADER
{
	char szDesc[256];    // readable description of file
	char chEOF;          // end of file flag
	DICTVERSION version; // version number
	unsigned int cWord;  // number of word in dictionary
	unsigned int cNode;  // number of all char node
	long code;           // code for data validation
	long nSize;          // dict's size
	bool fValid;         // status of dict
};


class ThaiFunc
{
public:
	ThaiFunc();
	~ThaiFunc();

public:
	void InitializeTable();
	bool IsThaiChar(unsigned short ch);
	unsigned int ThaiCharType(unsigned short ch);

protected:
	/* this+0 */ unsigned int tblCharType[96];
};


class ThaiLexicon
{
public:
	ThaiLexicon();
	~ThaiLexicon();

public:
	//unsigned char ThaiLexicon::AddWord(unsigned char *, unsigned int);
	//void ThaiLexicon::RefreshTrie();
	//unsigned char ThaiLexicon::fSaveLexicon(const char *);
	bool fLoadLexicon(const char* lpFileName);
	//unsigned int uiGetCountWord();
	//long lGetCountNode();
	//long lGetCountSize();
	//TRIE* lpGetTriePacked();
	//unsigned char * pGetMemDict();
	//unsigned char ThaiLexicon::SearchMemDict(unsigned char *);
	//unsigned int GetTotalWord();
	//unsigned int GetTotalNode();

protected:
	//int ThaiLexicon::Trie2Mem(TRIE*, int, unsigned char);
	//int ThaiLexicon::EnumNode(TRIE*);
	//unsigned char ThaiLexicon::CountUniqueStr(TRIE*);
	//int ThaiLexicon::InsertSubWord(TRIE*, unsigned char, int);

	void DestroyTrie(TRIE* pTrie);

protected:
	/* this+ 0 */ TRIE* m_trie;
	/* this+ 4 */ unsigned int m_cWord;
	/* this+ 8 */ long m_cNode;
	/* this+12 */ long m_nSize;
	/* this+16 */ unsigned char* m_MemDict;
	/* this+20 */ DICTHEADER m_DictHeader;
};


class ThaiBreakIterator
{
public:
	ThaiBreakIterator();
	~ThaiBreakIterator();

public:
	bool InitializeLexicon();
	//int FindThaiWordBreak(const char *, unsigned int, unsigned char *, unsigned int, unsigned int);

protected:
	//unsigned char HaveType(char, unsigned long);
	//unsigned long XCharType(char);
	//int GetWeight(unsigned char *, unsigned char *, unsigned char *, unsigned char *, unsigned long);
	//unsigned char fCanCat(unsigned char, unsigned char, unsigned int);

	/* this+0 */ ThaiLexicon* m_pLexicon;
	/* this+4 */ unsigned long m_rgThaiCharTypeTable[256];
};
