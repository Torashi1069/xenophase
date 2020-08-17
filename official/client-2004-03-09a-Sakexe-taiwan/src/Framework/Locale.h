#pragma once
class XMLElement;


void __cdecl InitClientInfo(const char* clientInfo);
void __cdecl InitDefaultServiceType(void);
void __cdecl InitDefaultClientInfo(void);
void __cdecl SelectKoreaClientInfo(void);
void __cdecl SelectClientInfo(int number);
void __cdecl InitDefaultLoadingScreen(void);
void __cdecl InitLanguage(void);
XMLElement* __cdecl GetClientInfo(void);
const char* __cdecl GetLicenceText(void);
bool __cdecl IsNameYellow(unsigned long aid);
bool __cdecl IsGravityAid(unsigned long aid);
