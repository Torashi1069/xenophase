#pragma once
class XMLElement;


void __cdecl InitClientInfo(const char* clientInfo);
void __cdecl InitDefaultServiceType();
void __cdecl SetOption(XMLElement* clientinfo);
void __cdecl InitDefaultLoadingScreen(int count);
bool __cdecl IsNameYellow(unsigned long aid);
bool __cdecl IsGravityAid(unsigned long aid);
