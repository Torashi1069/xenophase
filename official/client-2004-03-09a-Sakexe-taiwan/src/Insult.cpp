#include "Globals.h"
#include "Insult.h"
////////////////////////////////////////


Insult::Insult(char* word) // line 35
{
	this->Insult::Set(word);
}


void Insult::Set(char* word) // line ??
{
	for( char* p = word; p < word + strlen(word); p = CharNextExA((WORD)g_codePage, p, 0) )
		if( *p > 0 && isupper(*p) )
			*p = toupper(*p);

	this->word = word;
}


////////////////////////////////////////


CInsultFilter::CInsultFilter(void) // line 94
{
	//TODO
}


CInsultFilter::~CInsultFilter(void) // line 98
{
	//TODO
}


hook_method<bool (CInsultFilter::*)(const char* fName)> CInsultFilter::_Load(SERVER, "CInsultFilter::Load");
bool CInsultFilter::Load(const char* fName) // line 84
{
	return (this->*_Load)(fName);

	//TODO
}


hook_method<bool (CInsultFilter::*)(const char* str)> CInsultFilter::_IsGoodSentence(SERVER, "CInsultFilter::IsGoodSentence");
bool CInsultFilter::IsGoodSentence(const char* str) // line 45
{
	return (this->*_IsGoodSentence)(str);

	//TODO
}


hook_method<bool (CInsultFilter::*)(const char* str)> CInsultFilter::_IsBadSentence(SERVER, "CInsultFilter::IsBadSentence");
bool CInsultFilter::IsBadSentence(const char* str) // line 40
{
	return (this->*_IsBadSentence)(str);

	//TODO
}


////////////////////////////////////////
