#pragma once
class XMLElement;


void InitClientInfo(const char* clientInfo);
void SetOption(XMLElement* clientinfo);
void InitDefaultClientInfo();
void InitDefaultServiceType();
void SelectClientInfo(int number);
void SelectClientInfo2(int number, int number2);
void InitLanguage();
void SelectKoreaClientInfo();
void InitDefaultLoadingScreen(int count);
const char* GetLicenceText();
XMLElement* GetClientInfo();
bool IsNameYellow(unsigned long aid);
bool IsGravityAid(unsigned long aid);
int IsNameSpecific(unsigned long aid);
