#pragma once


#define DYN_MINIMUM_AID 1
#define DYN_MAXIMUM_AID 50000
#define NPC_MINIMUM_AID 50001
#define PC_MINIMUM_AID  100000
#define PC_MINIMUM_GID  100000


int GetServerRandom(int nMin, int nMax);
bool __cdecl ScriptCompile(void);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);


struct MS_MAPMOVE
{
	/* this+0 */ unsigned long AID;
	/* this+4 */ short xPos;
	/* this+6 */ short yPos;
	/* this+8 */ char mapName[16];

	public: void MS_MAPMOVE::Set(const char* map, short x, short y, unsigned long npcAID) // line 570
	{
		strcpy(this->mapName, map);
		this->xPos = x;
		this->yPos = y;
		this->AID = npcAID;
	}
};
