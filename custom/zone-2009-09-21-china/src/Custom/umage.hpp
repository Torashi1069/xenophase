#pragma once
class CPC;
class CItem;


const int NAME_LENGTH = 23 + 1;
const int CHAT_SIZE_MAX = 255 + 1; //Max allowed chat text length
const int AREA_SIZE = 14;
const int PARTY_ITEM_SHARE_DISTANCE = AREA_SIZE;
const int AUTOLOOT_DISTANCE = AREA_SIZE;
const int AUTOLOOT_IDLE_TIME = 80*1000;
const int ITID_GLOBALCHAT = 3996;
const int ITID_AUTOTRADE = 3998; // 'guest' item id
const int ITID_AUTOLOOT = 3999; // 'guest' item id
const int NPC_PROCESS_INTERVAL = 50;
const int MAX_EATINGITEM = 10; // looter mob capacity 


#define DIFF_TIME(a,b) ((int)((a)-(b)))
template<typename T> T cap_value(T val, T minval, T maxval);


bool Autoloot(CPC* pc, CItem* item, int droprate);
bool clif_process_message(CPC* sd, const char* buf, int format, char** name_, int* namelen_, char** message_, int* messagelen_);
void clif_displaymessage(CPC* sd, const char* mes, ...);
int ModifyDamage_Emperium(int damage);
