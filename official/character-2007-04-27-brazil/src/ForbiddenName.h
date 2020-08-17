#pragma once
#include "Common/Singleton.h"


class CForbiddenName : public CSingleton<CForbiddenName>
{
public:
	CForbiddenName();
	~CForbiddenName();
	bool isForbidden(const char* name);
	bool readForbiddenWordFile(const char* file);
	bool readAsciiTableFile(const char* file);

private:
//	void setForbiddenASCII(const unsigned char);
//	void setIgnoredASCII(const unsigned char);
//	void setAllowedASCII(const unsigned char);
//	bool isAllowedASCII(const unsigned char);
//	bool isIgnoredASCII(const unsigned char);
//	bool isForbiddenASCII(const unsigned char);
	void setForbiddenWord(const char* word);
	bool isIncludedForbiddenWord(const char* word);
	void sortForbiddenWordBySize();

private:
	enum { ALLOWED = 1, IGNORED = 2, FORBIDDEN = 3 };
	enum { ASCIINUM = 256 };

private:
	/* this+  0 */ //CSingleton<CForbiddenName> baseclass_0;
	/* this+  0 */ char m_asciiTable[ASCIINUM];
	/* this+256 */ std::vector<char*> m_forbiddenWords;
	/* this+272 */ bool m_useAscii;
};
