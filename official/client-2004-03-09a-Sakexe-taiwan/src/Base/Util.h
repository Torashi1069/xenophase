#pragma once


class CTokenizer
{
public:
//	CTokenizer();
	CTokenizer(const mystd::string& a);

public:
	void SetString(const mystd::string& a);
	void MakeLower();
	void MakeUpper();
//	void operator<<(const mystd::string& );
	mystd::string& operator[](int a);
	int NumTokens();
//	int GetInt(int );
//	int GetFloat(int );
//	void GetLine(mystd::istrstream& stream); //TODO

private:
	/* this+0 */ mystd::vector<mystd::string> m_token;
};


void MakeStringLower(mystd::string& s);
char* GetNumberText(int number, char* buf);
const char* StrChrBackward(const char* strName, char c);
DWORD aToDW_HEX(const char* hexNumber);
void GetFileNames(mystd::list<mystd::string>& fileNameList, const char* path, const char* szFileName_wildcard);
void DeleteDirectory(const char* dirName);
