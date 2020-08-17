#pragma once


struct Insult
{
	/* this+0 */ const char* word;

	public: Insult::Insult(char* word);
	//public: void Insult();
	public: void Insult::Set(char* word);
	//public: bool Check(const char *);
};


class CInsultFilter
{
	/* this+0 */ private: mystd::vector<Insult> m_insult;

	public: CInsultFilter::CInsultFilter(void);
	public: CInsultFilter::~CInsultFilter(void);
	public: bool CInsultFilter::Load(const char* fName);
	public: bool CInsultFilter::IsGoodSentence(const char* str);
	public: bool CInsultFilter::IsBadSentence(const char* str);

private:
	static hook_method<bool (CInsultFilter::*)(const char* fName)> CInsultFilter::_Load;
	static hook_method<bool (CInsultFilter::*)(const char* str)> CInsultFilter::_IsGoodSentence;
	static hook_method<bool (CInsultFilter::*)(const char* str)> CInsultFilter::_IsBadSentence;
};
