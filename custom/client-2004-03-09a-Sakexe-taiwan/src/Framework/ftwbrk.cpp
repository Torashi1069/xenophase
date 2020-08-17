#include "Base/File.h"
#include "Framework/ftwbrk.h"
////////////////////////////////////////


unsigned int TBL_CHTYPE_WITHLEADING[96] = {
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0111, 0x0111,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0011, 0x0091,
    0x0011, 0x0091, 0x0011, 0x0091,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0111, 0x0011, 0x0111, 0x0011,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0011, 0x1010,
    0x0010, 0x0290, 0x0010, 0x0210,
    0x0290, 0x0290, 0x0290, 0x0290,
    0x0310, 0x0310, 0x0310, 0x1000,
    0x1000, 0x0000, 0x0000, 0x0010,
    0x4010, 0x4010, 0x4010, 0x4010,
    0x4010, 0x0010, 0x0010, 0x2010,
    0x0410, 0x0410, 0x0410, 0x0410,
    0x0410, 0x0010, 0x0010, 0x0010,
    0x0012, 0x0012, 0x0012, 0x0012,
    0x0012, 0x0012, 0x0012, 0x0012,
    0x0012, 0x0012, 0x1010, 0x1010,
    0x0310, 0x0310, 0x0310, 0x0020,
};


unsigned int TBL_CHTYPE[96] = {
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0111, 0x0111,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0011, 0x0091,
    0x0011, 0x0091, 0x0011, 0x0091,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0111, 0x0011, 0x0111, 0x0011,
    0x0011, 0x0011, 0x0011, 0x0011,
    0x0011, 0x0011, 0x0011, 0x1010,
    0x0010, 0x0290, 0x0010, 0x0010,
    0x0290, 0x0290, 0x0290, 0x0290,
    0x0310, 0x0310, 0x0310, 0x1000,
    0x1000, 0x0000, 0x0000, 0x0010,
    0x0010, 0x0010, 0x0010, 0x0010,
    0x0010, 0x0010, 0x0010, 0x2010,
    0x0410, 0x0410, 0x0410, 0x0410,
    0x0410, 0x2010, 0x0010, 0x0010,
    0x0012, 0x0012, 0x0012, 0x0012,
    0x0012, 0x0012, 0x0012, 0x0012,
    0x0012, 0x0012, 0x1010, 0x1010,
    0x0310, 0x0310, 0x0310, 0x0020,
};


unsigned long THAICHARTYPETABLE[256] = {
    0,   0,   0,   0,
    0,   0,   0,   0,
    0,   0,   0,   0,
    0,   0,   0,   0,
    0,   0,   0,   0,
    0,   0,   0,   0,
    0,   0,   0,   0,
    0,   0,   0,   0,
    1000000,400,400,400,
    400,400,400,400,
    10, 20,400,400,
    400,400,404,400,
    10002,10002,10002,10002,
    10002,10002,10002,10002,
    10002,10002,400,400,
    10,400, 20, 40,
    400,100002,100002,100002,
    100002,100002,100002,100002,
    100002,100002,100002,100002,
    100002,100002,100002,100002,
    100002,100002,100002,100002,
    100002,100002,100002,100002,
    100002,100002,100002, 10,
    400, 20,400,400,
    400,200002,200002,200002,
    200002,200002,200002,200002,
    200002,200002,200002,200002,
    200002,200002,200002,200002,
    200002,200002,200002,200002,
    200002,200002,200002,200002,
    200002,200002,200002, 10,
    400, 20,400,   0,
    20001,101,101,101,
    101,400,8101,8101,
    8101,8101,4101,8101,
    8101,8101,8101,4101,
    20001,414,424,414,
    424,400,400,400,
    4101,4101,4101,8101,
    8101,8101,8101,4101,
    1000000,20001,20001,20001,
    20001,20001,20001,20001,
    20001,20001,20001,20001,
    20001,20001,20001,20001,
    20001,20001,20001,20001,
    20001,20001,20001,20001,
    20001,20001,20001,20001,
    20001,20001,20001,20001,
    20001,20001,20001,20001,
    20001,20001,20001,20001,
    20001,20001,20001,20001,
    20001,20001,20001,201,
    2001,4101,2001,2001,
    101,101,101,101,
    101,101,4101,2000000,
    400,   0,   0,400,
    1001,1001,1001,1001,
    1001,2001,   1,4101,
    8101,8101,8101,8101,
    4101,4101,4101,400,
    10001,10001,10001,10001,
    10001,10001,10001,10001,
    10001,400,400,101,
    101,101,   0,   0,
};


////////////////////////////////////////


ThaiFunc::ThaiFunc() // line 315-316
{
}


ThaiFunc::~ThaiFunc() // line 319-320
{
}


bool ThaiFunc::IsThaiChar(unsigned short ch) // line 323-325
{
	return ( (ch & 0xFF00) == 0x0E00 );
}


unsigned int ThaiFunc::ThaiCharType(unsigned short ch) // line 328-330
{
	return TBL_CHTYPE[(unsigned char)ch];
}


void ThaiFunc::InitializeTable() // line 333-335
{
	memcpy(tblCharType, TBL_CHTYPE, sizeof(TBL_CHTYPE));
}


////////////////////////////////////////


ThaiLexicon::ThaiLexicon() // line 341-348
{
	m_trie = NULL;
	m_cWord = 0;
	m_cNode = 0;
	m_nSize = 0;
	m_MemDict = NULL;
	memset(&m_DictHeader, 0, sizeof(m_DictHeader));
}


ThaiLexicon::~ThaiLexicon() // line 351-355
{
	if( m_MemDict )
		delete m_MemDict;
	DestroyTrie(m_trie); // inlined
}


void ThaiLexicon::DestroyTrie(TRIE* pTrie) // line 358-365
{
	if( pTrie )
	{
		DestroyTrie((TRIE*)(pTrie->child));
		DestroyTrie((TRIE*)(pTrie->next));
		delete pTrie;
	}
}


////////////////////////////////////////


ThaiBreakIterator::ThaiBreakIterator() // line 703-704
{
	m_pLexicon = NULL;
}


ThaiBreakIterator::~ThaiBreakIterator() // line 707-710
{
	if( m_pLexicon )
		delete m_pLexicon;
}


bool ThaiBreakIterator::InitializeLexicon() // line 713-722
{
	if( m_pLexicon )
		delete m_pLexicon;
	m_pLexicon = new ThaiLexicon;
	m_pLexicon->ThaiLexicon::fLoadLexicon("..\\ftwrk.lex");
	memcpy(m_rgThaiCharTypeTable, THAICHARTYPETABLE, sizeof(m_rgThaiCharTypeTable));
	if( !m_pLexicon )
		return false;

	return true;
}


bool ThaiLexicon::fLoadLexicon(const char* lpFileName) // line 651-697
{
	bool fSuccess = false;
	CFile file;

	if( !file.CFile::Open(lpFileName, 0) )
		return false;

	if( !file.CFile::Read(&m_DictHeader, sizeof(m_DictHeader)) )
		;
	else
	if( m_DictHeader.code != (m_DictHeader.cWord << 1) + m_DictHeader.cNode )
		;
	else
	if( !(m_MemDict = new unsigned char[m_DictHeader.nSize]) )
		;
	else
	if( !file.CFile::Read(m_MemDict, m_DictHeader.nSize) )
		;
	else
	{
		m_cWord = m_DictHeader.cWord;
		m_cNode = m_DictHeader.cNode;
		m_nSize = m_DictHeader.nSize;
		fSuccess = 1;
	}

	if( !fSuccess && m_MemDict )
	{
		delete m_MemDict;
		m_MemDict = NULL;
	}

	m_DictHeader.fValid = fSuccess;
	return fSuccess;
}


////////////////////////////////////////
