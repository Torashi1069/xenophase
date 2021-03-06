#include "Common/Packet.h"
#include "globals.hpp"


hook_func<bool (__cdecl *)(int packetType)> _IsFixedPacket(SERVER, "IsFixedPacket");
bool __cdecl IsFixedPacket(int packetType) // line 35
{
	return (_IsFixedPacket)(packetType);

	return ( g_packetLenMap[packetType] != -1 );
}


hook_func<int (__cdecl *)(int packetType)> _GetPacketSize(SERVER, "GetPacketSize");
int __cdecl GetPacketSize(int packetType) // line 49
{
	return (_GetPacketSize)(packetType);

	if( packetType == 0x2BF )
		return 12;

	if( packetType == 0x2C0 )
		return 4;

	return g_packetLenMap[packetType];
}


hook_func<void (__cdecl *)(void)> _InitPacketLen(SERVER, "InitPacketLen");
void __cdecl InitPacketLen(void) // line 63
{
	return (_InitPacketLen)();

	InitPacketLenWithClient();

	g_packetLenMap[10500] = 6;
	g_packetLenMap[10501] = 23;
	g_packetLenMap[10733] = 39;
	g_packetLenMap[10732] = 6;
	g_packetLenMap[10502] = 98;
	g_packetLenMap[10678] = 151;
	g_packetLenMap[10682] = 204;
	g_packetLenMap[10726] = 20;
	g_packetLenMap[10503] = 98;
	g_packetLenMap[10505] = 42;
	g_packetLenMap[10506] = 42;
	g_packetLenMap[10504] = 19;
	g_packetLenMap[10507] = 7;
	g_packetLenMap[10508] = 11;
	g_packetLenMap[10509] = 7;
	g_packetLenMap[10510] = 7;
	g_packetLenMap[10612] = 7;
	g_packetLenMap[10611] = 7;
	g_packetLenMap[10677] = 54;
	g_packetLenMap[10679] = 6;
	g_packetLenMap[10680] = 6;
	g_packetLenMap[10681] = 10;
	g_packetLenMap[143] = 6;
	g_packetLenMap[10513] = 4;
	g_packetLenMap[10000] = -1;
	g_packetLenMap[10001] = 5;
	g_packetLenMap[10002] = -1;
	g_packetLenMap[10003] = 28;
	g_packetLenMap[10515] = 14;
	g_packetLenMap[10006] = 24;
	g_packetLenMap[10007] = -1;
	g_packetLenMap[10516] = 15;
	g_packetLenMap[10517] = 10;
	g_packetLenMap[10004] = -1;
	g_packetLenMap[10009] = 13;
	g_packetLenMap[10021] = 8;
	g_packetLenMap[10022] = 8;
	g_packetLenMap[10028] = 16;
	g_packetLenMap[10023] = 8;
	g_packetLenMap[10024] = 8;
	g_packetLenMap[10025] = 18;
	g_packetLenMap[10026] = 8;
	g_packetLenMap[10027] = 25;
	g_packetLenMap[10546] = 6;
	g_packetLenMap[10010] = 12;
	g_packetLenMap[10011] = 12;
	g_packetLenMap[10012] = 12;
	g_packetLenMap[10019] = 16;
	g_packetLenMap[10013] = 10;
	g_packetLenMap[10014] = 12;
	g_packetLenMap[10015] = 8;
	g_packetLenMap[10016] = 8;
	g_packetLenMap[10017] = -1;
	g_packetLenMap[10018] = 11;
	g_packetLenMap[10514] = 10;
	g_packetLenMap[10511] = 6;
	g_packetLenMap[10512] = 6;
	g_packetLenMap[10008] = 7;
	g_packetLenMap[10020] = 28;
	g_packetLenMap[10518] = 86;
	g_packetLenMap[10519] = 34;
	g_packetLenMap[10520] = -1;
	g_packetLenMap[10521] = -1;
	g_packetLenMap[10522] = 7;
	g_packetLenMap[10523] = 31;
	g_packetLenMap[10524] = 6;
	g_packetLenMap[10525] = 10;
	g_packetLenMap[10526] = -1;
	g_packetLenMap[10527] = -1;
	g_packetLenMap[10528] = 34;
	g_packetLenMap[10638] = 36;
	g_packetLenMap[10529] = 35;
	g_packetLenMap[10530] = -1;
	g_packetLenMap[10531] = 14;
	g_packetLenMap[10532] = 31;
	g_packetLenMap[10533] = 34;
	g_packetLenMap[10534] = 14;
	g_packetLenMap[10545] = 14;
	g_packetLenMap[10643] = 14;
	g_packetLenMap[10535] = 10;
	g_packetLenMap[10536] = 34;
	g_packetLenMap[10537] = 79;
	g_packetLenMap[10639] = 81;
	g_packetLenMap[10538] = 35;
	g_packetLenMap[10539] = 22;
	g_packetLenMap[10540] = 14;
	g_packetLenMap[10541] = -1;
	g_packetLenMap[10542] = -1;
	g_packetLenMap[10543] = 2;
	g_packetLenMap[10544] = 2;
	g_packetLenMap[10527] = -1;
	g_packetLenMap[10547] = 10;
	g_packetLenMap[10548] = 2;
	g_packetLenMap[10549] = 22;
	g_packetLenMap[11000] = 50;
	g_packetLenMap[11001] = 10;
	g_packetLenMap[11002] = -1;
	g_packetLenMap[11003] = 30;
	g_packetLenMap[10673] = 6;
	g_packetLenMap[11009] = 6;
	g_packetLenMap[11011] = 6;
	g_packetLenMap[11013] = 6;
	g_packetLenMap[10550] = 14;
	g_packetLenMap[10552] = 38;
	g_packetLenMap[10553] = 14;
	g_packetLenMap[10554] = -1;
	g_packetLenMap[10555] = -1;
	g_packetLenMap[10556] = -1;
	g_packetLenMap[10557] = -1;
	g_packetLenMap[10558] = -1;
	g_packetLenMap[10559] = -1;
	g_packetLenMap[10560] = 14;
	g_packetLenMap[10561] = -1;
	g_packetLenMap[10562] = -1;
	g_packetLenMap[10563] = -1;
	g_packetLenMap[10564] = 14;
	g_packetLenMap[10565] = -1;
	g_packetLenMap[10566] = 54;
	g_packetLenMap[10567] = 78;
	g_packetLenMap[10568] = 82;
	g_packetLenMap[10569] = 102;
	g_packetLenMap[10570] = 54;
	g_packetLenMap[10571] = 18;
	g_packetLenMap[10572] = -1;
	g_packetLenMap[10573] = -1;
	g_packetLenMap[10574] = -1;
	g_packetLenMap[10575] = -1;
	g_packetLenMap[10576] = -1;
	g_packetLenMap[10551] = 86;
	g_packetLenMap[10577] = 18;
	g_packetLenMap[10579] = 66;
	g_packetLenMap[10580] = 15;
	g_packetLenMap[10578] = 34;
	g_packetLenMap[10581] = -1;
	g_packetLenMap[10582] = 222;
	g_packetLenMap[10583] = -1;
	g_packetLenMap[10584] = -1;
	g_packetLenMap[10585] = -1;
	g_packetLenMap[10586] = -1;
	g_packetLenMap[10587] = -1;
	g_packetLenMap[10588] = 11;
	g_packetLenMap[10589] = 52;
	g_packetLenMap[10590] = 30;
	g_packetLenMap[10591] = 186;
	g_packetLenMap[10592] = 186;
	g_packetLenMap[10593] = 30;
	g_packetLenMap[10594] = 7;
	g_packetLenMap[10595] = 47;
	g_packetLenMap[10596] = 14;
	g_packetLenMap[10597] = 15;
	g_packetLenMap[10598] = 47;
	g_packetLenMap[10599] = 146;
	g_packetLenMap[10601] = 14;
	g_packetLenMap[10600] = 14;
	g_packetLenMap[10602] = 10;
	g_packetLenMap[10603] = -1;
	g_packetLenMap[10604] = -1;
	g_packetLenMap[10605] = 14;
	g_packetLenMap[10606] = 18;
	g_packetLenMap[10607] = 18;
	g_packetLenMap[10608] = 150;
	g_packetLenMap[10609] = 14;
	g_packetLenMap[10610] = 16;
	g_packetLenMap[10613] = 12;
	g_packetLenMap[10614] = 35;
	g_packetLenMap[10615] = 36;
	g_packetLenMap[10617] = 10;
	g_packetLenMap[10616] = 10;
	g_packetLenMap[10618] = -1;
	g_packetLenMap[10619] = 26;
	g_packetLenMap[10637] = 26;
	g_packetLenMap[10641] = 26;
	g_packetLenMap[10642] = 6;
	g_packetLenMap[10670] = 10;
	g_packetLenMap[10620] = 2;
	g_packetLenMap[10621] = 82;
	g_packetLenMap[10622] = 6;
	g_packetLenMap[10623] = 6;
	g_packetLenMap[10624] = 18;
	g_packetLenMap[10625] = 18;
	g_packetLenMap[10626] = 14;
	g_packetLenMap[10627] = 14;
	g_packetLenMap[10628] = -1;
	g_packetLenMap[10629] = -1;
	g_packetLenMap[10632] = 42;
	g_packetLenMap[10640] = 46;
	g_packetLenMap[10633] = 62;
	g_packetLenMap[10634] = 10;
	g_packetLenMap[10635] = 10;
	g_packetLenMap[10636] = 6;
	g_packetLenMap[10630] = 10;
	g_packetLenMap[10631] = 2;
	g_packetLenMap[10647] = 30;
	g_packetLenMap[10648] = 30;
	g_packetLenMap[10649] = -1;
	g_packetLenMap[10650] = 15;
	g_packetLenMap[10651] = 18;
	g_packetLenMap[10652] = 40;
	g_packetLenMap[10653] = 14;
	g_packetLenMap[10654] = 14;
	g_packetLenMap[10655] = 34;
	g_packetLenMap[10657] = 324;
	g_packetLenMap[10658] = 36;
	g_packetLenMap[529] = 6;
	g_packetLenMap[10659] = 10;
	g_packetLenMap[10660] = -1;
	g_packetLenMap[10661] = 14;
	g_packetLenMap[10662] = -1;
	g_packetLenMap[10663] = 14;
	g_packetLenMap[10664] = 16;
	g_packetLenMap[10665] = 14;
	g_packetLenMap[10666] = 79;
	g_packetLenMap[10667] = -1;
	g_packetLenMap[10668] = 7;
	g_packetLenMap[10669] = 74;
	g_packetLenMap[10671] = 6;
	g_packetLenMap[10672] = 10;
	g_packetLenMap[10674] = 14;
	g_packetLenMap[10675] = 46;
	g_packetLenMap[10676] = 85;
	g_packetLenMap[10683] = 2;
	g_packetLenMap[10684] = 136;
	g_packetLenMap[10698] = 75;
	g_packetLenMap[10705] = 73;
	g_packetLenMap[10706] = 12;
	g_packetLenMap[10707] = 79;
	g_packetLenMap[10708] = 18;
	g_packetLenMap[10709] = 38;
	g_packetLenMap[10710] = 107;
	g_packetLenMap[10711] = 10;
	g_packetLenMap[10712] = 38;
	g_packetLenMap[10713] = 14;
	g_packetLenMap[10686] = 30;
	g_packetLenMap[10687] = 27;
	g_packetLenMap[10691] = 35;
	g_packetLenMap[10692] = 14;
	g_packetLenMap[10693] = 22;
	g_packetLenMap[10695] = 7;
	g_packetLenMap[10694] = 10;
	g_packetLenMap[10696] = 2;
	g_packetLenMap[10697] = 2;
	g_packetLenMap[11015] = 22;
	g_packetLenMap[10688] = 10;
	g_packetLenMap[10689] = 26;
	g_packetLenMap[10690] = 10;
	g_packetLenMap[10700] = 34;
	g_packetLenMap[10701] = 34;
	g_packetLenMap[10702] = 34;
	g_packetLenMap[10703] = 14;
	g_packetLenMap[10704] = 100;
	g_packetLenMap[10714] = 10;
	g_packetLenMap[10715] = 10;
	g_packetLenMap[10716] = 14;
	g_packetLenMap[10717] = 11;
	g_packetLenMap[10727] = 6;
	g_packetLenMap[10728] = 20;
	g_packetLenMap[10729] = 16;
	g_packetLenMap[10730] = 14;
	g_packetLenMap[10734] = 54;
	g_packetLenMap[10735] = 54;
	g_packetLenMap[10736] = 54;
	g_packetLenMap[10737] = 54;
	g_packetLenMap[10731] = 6;
	g_packetLenMap[10738] = 2;
	g_packetLenMap[10739] = 22;
	g_packetLenMap[10740] = 24;
	g_packetLenMap[10741] = 24;
	g_packetLenMap[10742] = 6;
	g_packetLenMap[10743] = -1;
	g_packetLenMap[10744] = 14;
	g_packetLenMap[10745] = 10;
	g_packetLenMap[10746] = 12;
	g_packetLenMap[10747] = 10;
	g_packetLenMap[10748] = 12;
	g_packetLenMap[10749] = 10;
	g_packetLenMap[10750] = 31;
	g_packetLenMap[10751] = 62;
	g_packetLenMap[10752] = 18;
	g_packetLenMap[10753] = 7;
	g_packetLenMap[10754] = 6;
	g_packetLenMap[10755] = 7;
	g_packetLenMap[10756] = 6;
}


hook_func<void (__cdecl *)(void)> _InitPacketLenWithClient(SERVER, "InitPacketLenWithClient");
void __cdecl InitPacketLenWithClient(void) // line 432
{
	return (_InitPacketLenWithClient)();

	g_packetLenMap[391] = 6;
	g_packetLenMap[129] = 3;
	g_packetLenMap[454] = 4;
	g_packetLenMap[455] = 2;
	g_packetLenMap[100] = 55;
	g_packetLenMap[105] = -1;
	g_packetLenMap[106] = 23;
	g_packetLenMap[475] = 2;
	g_packetLenMap[476] = -1;
	g_packetLenMap[477] = 47;
	g_packetLenMap[506] = 48;
	g_packetLenMap[516] = 18;
	g_packetLenMap[497] = -1;
	g_packetLenMap[512] = 26;
	g_packetLenMap[446] = 2;
	g_packetLenMap[447] = 3;
	g_packetLenMap[101] = 17;
	g_packetLenMap[102] = 3;
	g_packetLenMap[103] = 37;
	g_packetLenMap[525] = -1;
	g_packetLenMap[107] = -1;
	g_packetLenMap[108] = 3;
	g_packetLenMap[109] = 108;
	g_packetLenMap[110] = 3;
	g_packetLenMap[113] = 28;
	g_packetLenMap[104] = 46;
	g_packetLenMap[507] = 56;
	g_packetLenMap[111] = 2;
	g_packetLenMap[112] = 3;
	g_packetLenMap[714] = 3;
	g_packetLenMap[114] = 19;
	g_packetLenMap[130] = 2;
	g_packetLenMap[133] = 5;
	g_packetLenMap[137] = 7;
	g_packetLenMap[140] = -1;
	g_packetLenMap[126] = 6;
	g_packetLenMap[125] = 2;
	g_packetLenMap[144] = 7;
	g_packetLenMap[153] = -1;
	g_packetLenMap[412] = -1;
	g_packetLenMap[155] = 5;
	g_packetLenMap[204] = 6;
	g_packetLenMap[206] = 2;
	g_packetLenMap[159] = 6;
	g_packetLenMap[162] = 6;
	g_packetLenMap[167] = 8;
	g_packetLenMap[169] = 6;
	g_packetLenMap[171] = 4;
	g_packetLenMap[184] = 7;
	g_packetLenMap[185] = 6;
	g_packetLenMap[178] = 3;
	g_packetLenMap[186] = 2;
	g_packetLenMap[187] = 5;
	g_packetLenMap[191] = 3;
	g_packetLenMap[193] = 2;
	g_packetLenMap[197] = 7;
	g_packetLenMap[200] = -1;
	g_packetLenMap[201] = -1;
	g_packetLenMap[150] = -1;
	g_packetLenMap[207] = 27;
	g_packetLenMap[208] = 3;
	g_packetLenMap[211] = 2;
	g_packetLenMap[213] = -1;
	g_packetLenMap[217] = 14;
	g_packetLenMap[222] = -1;
	g_packetLenMap[224] = 30;
	g_packetLenMap[226] = 26;
	g_packetLenMap[227] = 2;
	g_packetLenMap[228] = 6;
	g_packetLenMap[230] = 3;
	g_packetLenMap[232] = 8;
	g_packetLenMap[235] = 2;
	g_packetLenMap[237] = 2;
	g_packetLenMap[239] = 2;
	g_packetLenMap[243] = 8;
	g_packetLenMap[245] = 8;
	g_packetLenMap[247] = 2;
	g_packetLenMap[249] = 26;
	g_packetLenMap[488] = 28;
	g_packetLenMap[252] = 6;
	g_packetLenMap[255] = 10;
	g_packetLenMap[258] = 6;
	g_packetLenMap[256] = 2;
	g_packetLenMap[259] = 30;
	g_packetLenMap[264] = -1;
	g_packetLenMap[274] = 4;
	g_packetLenMap[275] = 10;
	g_packetLenMap[278] = 10;
	g_packetLenMap[280] = 2;
	g_packetLenMap[283] = 20;
	g_packetLenMap[285] = 2;
	g_packetLenMap[294] = 8;
	g_packetLenMap[295] = 8;
	g_packetLenMap[296] = 8;
	g_packetLenMap[297] = 8;
	g_packetLenMap[298] = 2;
	g_packetLenMap[302] = 2;
	g_packetLenMap[303] = -1;
	g_packetLenMap[434] = -1;
	g_packetLenMap[308] = -1;
	g_packetLenMap[304] = 6;
	g_packetLenMap[312] = 3;
	g_packetLenMap[319] = 26;
	g_packetLenMap[320] = 22;
	g_packetLenMap[323] = 10;
	g_packetLenMap[326] = 6;
	g_packetLenMap[376] = 4;
	g_packetLenMap[378] = 4;
	g_packetLenMap[380] = 6;
	g_packetLenMap[509] = 15;
	g_packetLenMap[394] = 4;
	g_packetLenMap[398] = 10;
	g_packetLenMap[400] = 90;
	g_packetLenMap[407] = 4;
	g_packetLenMap[408] = 8;
	g_packetLenMap[430] = 4;
	g_packetLenMap[603] = 6;
	g_packetLenMap[431] = 4;
	g_packetLenMap[441] = 6;
	g_packetLenMap[461] = 30;
	g_packetLenMap[1090] = 8;
	g_packetLenMap[462] = 6;
	g_packetLenMap[1091] = 8;
	g_packetLenMap[463] = 28;
	g_packetLenMap[464] = 8;
	g_packetLenMap[481] = 8;
	g_packetLenMap[465] = 14;
	g_packetLenMap[466] = 10;
	g_packetLenMap[148] = 6;
	g_packetLenMap[149] = 30;
	g_packetLenMap[405] = 102;
	g_packetLenMap[403] = 6;
	g_packetLenMap[373] = 6;
	g_packetLenMap[374] = 106;
	g_packetLenMap[121] = 53;
	g_packetLenMap[413] = 6;
	g_packetLenMap[332] = -1;
	g_packetLenMap[333] = 2;
	g_packetLenMap[334] = 6;
	g_packetLenMap[335] = 6;
	g_packetLenMap[336] = 110;
	g_packetLenMap[438] = 114;
	g_packetLenMap[337] = 6;
	g_packetLenMap[338] = -1;
	g_packetLenMap[339] = -1;
	g_packetLenMap[340] = -1;
	g_packetLenMap[358] = -1;
	g_packetLenMap[341] = -1;
	g_packetLenMap[342] = -1;
	g_packetLenMap[343] = 6;
	g_packetLenMap[344] = -1;
	g_packetLenMap[345] = 54;
	g_packetLenMap[346] = 66;
	g_packetLenMap[347] = 54;
	g_packetLenMap[348] = 90;
	g_packetLenMap[349] = 42;
	g_packetLenMap[350] = 6;
	g_packetLenMap[351] = 42;
	g_packetLenMap[352] = -1;
	g_packetLenMap[353] = -1;
	g_packetLenMap[354] = -1;
	g_packetLenMap[355] = -1;
	g_packetLenMap[356] = -1;
	g_packetLenMap[357] = 30;
	g_packetLenMap[359] = 3;
	g_packetLenMap[360] = 14;
	g_packetLenMap[361] = 3;
	g_packetLenMap[362] = 30;
	g_packetLenMap[363] = 10;
	g_packetLenMap[329] = 9;
	g_packetLenMap[330] = 6;
	g_packetLenMap[331] = 27;
	g_packetLenMap[366] = 186;
	g_packetLenMap[367] = 182;
	g_packetLenMap[382] = -1;
	g_packetLenMap[383] = -1;
	g_packetLenMap[357] = 30;
	g_packetLenMap[358] = -1;
	g_packetLenMap[359] = 3;
	g_packetLenMap[360] = 14;
	g_packetLenMap[361] = 3;
	g_packetLenMap[362] = 30;
	g_packetLenMap[363] = 10;
	g_packetLenMap[364] = 43;
	g_packetLenMap[364] = 43;
	g_packetLenMap[365] = 14;
	g_packetLenMap[498] = 20;
	g_packetLenMap[368] = 14;
	g_packetLenMap[369] = 30;
	g_packetLenMap[370] = 10;
	g_packetLenMap[371] = 3;
	g_packetLenMap[372] = -1;
	g_packetLenMap[384] = 6;
	g_packetLenMap[385] = 3;
	g_packetLenMap[386] = 106;
	g_packetLenMap[387] = 10;
	g_packetLenMap[388] = 10;
	g_packetLenMap[389] = 34;
	g_packetLenMap[414] = 2;
	g_packetLenMap[415] = 6;
	g_packetLenMap[416] = 3;
	g_packetLenMap[417] = 3;
	g_packetLenMap[418] = 37;
	g_packetLenMap[419] = 5;
	g_packetLenMap[420] = 11;
	g_packetLenMap[421] = 26;
	g_packetLenMap[422] = -1;
	g_packetLenMap[423] = 4;
	g_packetLenMap[424] = 4;
	g_packetLenMap[425] = 6;
	g_packetLenMap[426] = 10;
	g_packetLenMap[458] = 3;
	g_packetLenMap[432] = 11;
	g_packetLenMap[433] = 7;
	g_packetLenMap[442] = 26;
	g_packetLenMap[443] = 26;
	g_packetLenMap[444] = 26;
	g_packetLenMap[445] = 26;
	g_packetLenMap[448] = 2;
	g_packetLenMap[449] = 14;
	g_packetLenMap[450] = 10;
	g_packetLenMap[467] = 35;
	g_packetLenMap[469] = -1;
	g_packetLenMap[468] = 6;
	g_packetLenMap[479] = 6;
	g_packetLenMap[499] = 10;
	g_packetLenMap[644] = 14;
	g_packetLenMap[511] = 10;
	g_packetLenMap[493] = 2;
	g_packetLenMap[487] = 2;
	g_packetLenMap[439] = 6;
	g_packetLenMap[503] = 14;
	g_packetLenMap[483] = 14;
	g_packetLenMap[459] = 9;
	g_packetLenMap[505] = 6;
	g_packetLenMap[485] = 6;
	g_packetLenMap[513] = -1;
	g_packetLenMap[514] = 26;
	g_packetLenMap[515] = 10;
	g_packetLenMap[517] = 26;
	g_packetLenMap[518] = 11;
	g_packetLenMap[519] = 34;
	g_packetLenMap[520] = 14;
	g_packetLenMap[521] = 36;
	g_packetLenMap[522] = 10;
	g_packetLenMap[526] = 32;
	g_packetLenMap[530] = 26;
	g_packetLenMap[531] = 26;
	g_packetLenMap[532] = 42;
	g_packetLenMap[533] = 6;
	g_packetLenMap[534] = 6;
	g_packetLenMap[535] = 2;
	g_packetLenMap[536] = 2;
	g_packetLenMap[549] = 2;
	g_packetLenMap[641] = 4;
	g_packetLenMap[537] = 282;
	g_packetLenMap[538] = 282;
	g_packetLenMap[550] = 282;
	g_packetLenMap[642] = 284;
	g_packetLenMap[539] = 10;
	g_packetLenMap[540] = 10;
	g_packetLenMap[548] = 10;
	g_packetLenMap[640] = 12;
	g_packetLenMap[645] = 6;
	g_packetLenMap[646] = 4;
	g_packetLenMap[541] = 6;
	g_packetLenMap[542] = 6;
	g_packetLenMap[543] = 66;
	g_packetLenMap[546] = 6;
	g_packetLenMap[545] = -1;
	g_packetLenMap[544] = 10;
	g_packetLenMap[547] = 8;
	g_packetLenMap[115] = 11;
	g_packetLenMap[116] = 3;
	g_packetLenMap[117] = -1;
	g_packetLenMap[118] = 9;
	g_packetLenMap[119] = 5;
	g_packetLenMap[120] = 55;
	g_packetLenMap[122] = 58;
	g_packetLenMap[123] = 60;
	g_packetLenMap[124] = 42;
	g_packetLenMap[127] = 6;
	g_packetLenMap[128] = 7;
	g_packetLenMap[131] = 2;
	g_packetLenMap[132] = 2;
	g_packetLenMap[134] = 16;
	g_packetLenMap[135] = 12;
	g_packetLenMap[136] = 10;
	g_packetLenMap[138] = 29;
	g_packetLenMap[139] = 23;
	g_packetLenMap[141] = -1;
	g_packetLenMap[142] = -1;
	g_packetLenMap[145] = 22;
	g_packetLenMap[146] = 28;
	g_packetLenMap[147] = 2;
	g_packetLenMap[151] = -1;
	g_packetLenMap[152] = 3;
	g_packetLenMap[154] = -1;
	g_packetLenMap[156] = 9;
	g_packetLenMap[157] = 17;
	g_packetLenMap[158] = 17;
	g_packetLenMap[160] = 23;
	g_packetLenMap[161] = 6;
	g_packetLenMap[163] = -1;
	g_packetLenMap[164] = -1;
	g_packetLenMap[165] = -1;
	g_packetLenMap[166] = -1;
	g_packetLenMap[168] = 7;
	g_packetLenMap[170] = 7;
	g_packetLenMap[172] = 7;
	g_packetLenMap[174] = -1;
	g_packetLenMap[175] = 6;
	g_packetLenMap[176] = 8;
	g_packetLenMap[177] = 8;
	g_packetLenMap[179] = 3;
	g_packetLenMap[180] = -1;
	g_packetLenMap[181] = 6;
	g_packetLenMap[182] = 6;
	g_packetLenMap[183] = -1;
	g_packetLenMap[188] = 6;
	g_packetLenMap[189] = 44;
	g_packetLenMap[190] = 5;
	g_packetLenMap[192] = 7;
	g_packetLenMap[194] = 6;
	g_packetLenMap[195] = 8;
	g_packetLenMap[196] = 6;
	g_packetLenMap[198] = -1;
	g_packetLenMap[199] = -1;
	g_packetLenMap[202] = 3;
	g_packetLenMap[203] = 3;
	g_packetLenMap[205] = 3;
	g_packetLenMap[209] = 4;
	g_packetLenMap[210] = 4;
	g_packetLenMap[212] = -1;
	g_packetLenMap[214] = 3;
	g_packetLenMap[215] = -1;
	g_packetLenMap[216] = 6;
	g_packetLenMap[218] = 3;
	g_packetLenMap[219] = -1;
	g_packetLenMap[220] = 28;
	g_packetLenMap[221] = 29;
	g_packetLenMap[223] = -1;
	g_packetLenMap[225] = 30;
	g_packetLenMap[229] = 26;
	g_packetLenMap[231] = 3;
	g_packetLenMap[233] = 19;
	g_packetLenMap[234] = 5;
	g_packetLenMap[236] = 3;
	g_packetLenMap[238] = 2;
	g_packetLenMap[240] = 3;
	g_packetLenMap[241] = 2;
	g_packetLenMap[242] = 6;
	g_packetLenMap[244] = 21;
	g_packetLenMap[246] = 8;
	g_packetLenMap[248] = 2;
	g_packetLenMap[250] = 3;
	g_packetLenMap[251] = -1;
	g_packetLenMap[253] = 27;
	g_packetLenMap[254] = 30;
	g_packetLenMap[257] = 6;
	g_packetLenMap[260] = 79;
	g_packetLenMap[261] = 31;
	g_packetLenMap[262] = 10;
	g_packetLenMap[263] = 10;
	g_packetLenMap[265] = -1;
	g_packetLenMap[266] = 4;
	g_packetLenMap[267] = 6;
	g_packetLenMap[268] = 6;
	g_packetLenMap[269] = 2;
	g_packetLenMap[270] = 11;
	g_packetLenMap[271] = -1;
	g_packetLenMap[689] = -1;
	g_packetLenMap[690] = -1;
	g_packetLenMap[693] = -1;
	g_packetLenMap[272] = 10;
	g_packetLenMap[273] = 39;
	g_packetLenMap[276] = 31;
	g_packetLenMap[277] = 35;
	g_packetLenMap[279] = 18;
	g_packetLenMap[281] = 13;
	g_packetLenMap[553] = 15;
	g_packetLenMap[282] = 15;
	g_packetLenMap[284] = 68;
	g_packetLenMap[286] = 3;
	g_packetLenMap[287] = 16;
	g_packetLenMap[288] = 6;
	g_packetLenMap[289] = 14;
	g_packetLenMap[290] = -1;
	g_packetLenMap[291] = -1;
	g_packetLenMap[292] = 21;
	g_packetLenMap[293] = 8;
	g_packetLenMap[299] = 2;
	g_packetLenMap[300] = 3;
	g_packetLenMap[301] = 4;
	g_packetLenMap[305] = 86;
	g_packetLenMap[306] = 6;
	g_packetLenMap[307] = -1;
	g_packetLenMap[309] = 7;
	g_packetLenMap[310] = -1;
	g_packetLenMap[311] = 6;
	g_packetLenMap[313] = 16;
	g_packetLenMap[314] = 4;
	g_packetLenMap[315] = 4;
	g_packetLenMap[316] = 4;
	g_packetLenMap[317] = 6;
	g_packetLenMap[318] = 24;
	g_packetLenMap[321] = 14;
	g_packetLenMap[322] = 6;
	g_packetLenMap[324] = 23;
	g_packetLenMap[325] = 19;
	g_packetLenMap[327] = 39;
	g_packetLenMap[328] = 8;
	g_packetLenMap[375] = -1;
	g_packetLenMap[377] = 5;
	g_packetLenMap[379] = -1;
	g_packetLenMap[381] = 7;
	g_packetLenMap[392] = 8;
	g_packetLenMap[393] = 4;
	g_packetLenMap[395] = 4;
	g_packetLenMap[396] = 29;
	g_packetLenMap[397] = -1;
	g_packetLenMap[399] = 6;
	g_packetLenMap[401] = 86;
	g_packetLenMap[402] = 24;
	g_packetLenMap[404] = 30;
	g_packetLenMap[406] = 9;
	g_packetLenMap[650] = 18;
	g_packetLenMap[409] = 4;
	g_packetLenMap[410] = 14;
	g_packetLenMap[411] = 10;
	g_packetLenMap[427] = 12;
	g_packetLenMap[428] = 6;
	g_packetLenMap[429] = -1;
	g_packetLenMap[602] = -1;
	g_packetLenMap[435] = 67;
	g_packetLenMap[436] = 12;
	g_packetLenMap[437] = 18;
	g_packetLenMap[440] = 3;
	g_packetLenMap[451] = -1;
	g_packetLenMap[452] = 22;
	g_packetLenMap[453] = 22;
	g_packetLenMap[456] = 13;
	g_packetLenMap[457] = 97;
	g_packetLenMap[460] = 9;
	g_packetLenMap[470] = 4;
	g_packetLenMap[471] = 11;
	g_packetLenMap[472] = 54;
	g_packetLenMap[554] = 58;
	g_packetLenMap[473] = 53;
	g_packetLenMap[555] = 57;
	g_packetLenMap[474] = 60;
	g_packetLenMap[556] = 65;
	g_packetLenMap[478] = 33;
	g_packetLenMap[480] = 30;
	g_packetLenMap[482] = 34;
	g_packetLenMap[484] = 2;
	g_packetLenMap[486] = 26;
	g_packetLenMap[489] = 81;
	g_packetLenMap[490] = 6;
	g_packetLenMap[491] = 10;
	g_packetLenMap[492] = 26;
	g_packetLenMap[494] = -1;
	g_packetLenMap[495] = -1;
	g_packetLenMap[496] = -1;
	g_packetLenMap[500] = 32;
	g_packetLenMap[501] = 9;
	g_packetLenMap[502] = 34;
	g_packetLenMap[595] = 3;
	g_packetLenMap[596] = 3;
	g_packetLenMap[504] = 2;
	g_packetLenMap[508] = -1;
	g_packetLenMap[510] = 5;
	g_packetLenMap[551] = 18;
	g_packetLenMap[552] = 18;
	g_packetLenMap[557] = 5;
	g_packetLenMap[562] = 9;
	g_packetLenMap[563] = 11;
	g_packetLenMap[564] = 6;
	g_packetLenMap[560] = 12;
	g_packetLenMap[558] = 71;
	g_packetLenMap[637] = 62;
	g_packetLenMap[565] = -1;
	g_packetLenMap[569] = 11;
	g_packetLenMap[559] = 5;
	g_packetLenMap[561] = 26;
	g_packetLenMap[567] = 2;
	g_packetLenMap[568] = 282;
	g_packetLenMap[566] = 10;
	g_packetLenMap[570] = 4;
	g_packetLenMap[571] = 36;
	g_packetLenMap[572] = 6;
	g_packetLenMap[573] = 6;
	g_packetLenMap[574] = 8;
	g_packetLenMap[575] = 2;
	g_packetLenMap[576] = -1;
	g_packetLenMap[577] = 6;
	g_packetLenMap[578] = -1;
	g_packetLenMap[579] = 6;
	g_packetLenMap[599] = 8;
	g_packetLenMap[580] = 6;
	g_packetLenMap[581] = 3;
	g_packetLenMap[582] = 4;
	g_packetLenMap[583] = 8;
	g_packetLenMap[584] = -1;
	g_packetLenMap[585] = 3;
	g_packetLenMap[586] = 70;
	g_packetLenMap[587] = 4;
	g_packetLenMap[588] = 8;
	g_packetLenMap[589] = 12;
	g_packetLenMap[590] = 6;
	g_packetLenMap[591] = 10;
	g_packetLenMap[592] = 3;
	g_packetLenMap[593] = 34;
	g_packetLenMap[594] = -1;
	g_packetLenMap[597] = 5;
	g_packetLenMap[598] = 5;
	g_packetLenMap[600] = 2;
	g_packetLenMap[601] = 3;
	g_packetLenMap[604] = 4;
	g_packetLenMap[605] = 6;
	g_packetLenMap[606] = 4;
	g_packetLenMap[607] = 6;
	g_packetLenMap[608] = 6;
	g_packetLenMap[609] = 11;
	g_packetLenMap[610] = 11;
	g_packetLenMap[611] = 11;
	g_packetLenMap[612] = 20;
	g_packetLenMap[613] = 20;
	g_packetLenMap[614] = 30;
	g_packetLenMap[615] = 4;
	g_packetLenMap[616] = 4;
	g_packetLenMap[617] = 4;
	g_packetLenMap[618] = 4;
	g_packetLenMap[619] = 4;
	g_packetLenMap[620] = 4;
	g_packetLenMap[621] = 4;
	g_packetLenMap[623] = 2;
	g_packetLenMap[624] = 2;
	g_packetLenMap[625] = 40;
	g_packetLenMap[626] = 44;
	g_packetLenMap[627] = 30;
	g_packetLenMap[628] = 8;
	g_packetLenMap[629] = 37;
	g_packetLenMap[630] = -1;
	g_packetLenMap[631] = 84;
	g_packetLenMap[632] = 2;
	g_packetLenMap[633] = 2;
	g_packetLenMap[634] = -1;
	g_packetLenMap[635] = 14;
	g_packetLenMap[636] = 60;
	g_packetLenMap[638] = -1;
	g_packetLenMap[639] = 8;
	g_packetLenMap[643] = 6;
	g_packetLenMap[647] = -1;
	g_packetLenMap[648] = 6;
	g_packetLenMap[649] = 8;
	g_packetLenMap[1092] = -1;
	g_packetLenMap[1093] = 6;
	g_packetLenMap[651] = -1;
	g_packetLenMap[652] = 46;
	g_packetLenMap[653] = 34;
	g_packetLenMap[654] = 4;
	g_packetLenMap[655] = 6;
	g_packetLenMap[656] = 4;
	g_packetLenMap[657] = 4;
	g_packetLenMap[658] = 2;
	g_packetLenMap[659] = 70;
	g_packetLenMap[660] = 10;
	g_packetLenMap[661] = -1;
	g_packetLenMap[662] = -1;
	g_packetLenMap[663] = -1;
	g_packetLenMap[664] = 8;
	g_packetLenMap[665] = 6;
	g_packetLenMap[666] = 27;
	g_packetLenMap[667] = 80;
	g_packetLenMap[668] = 66;
	g_packetLenMap[669] = -1;
	g_packetLenMap[670] = 11;
	g_packetLenMap[671] = 3;
	g_packetLenMap[674] = 8;
	g_packetLenMap[677] = 8;
	g_packetLenMap[682] = 4;
	g_packetLenMap[683] = 36;
	g_packetLenMap[684] = 6;
	g_packetLenMap[685] = 8;
	g_packetLenMap[688] = 85;
	g_packetLenMap[696] = 22;
	g_packetLenMap[699] = 8;
	g_packetLenMap[697] = 191;
	g_packetLenMap[698] = 11;
	g_packetLenMap[700] = 6;
	g_packetLenMap[691] = 107;
	g_packetLenMap[692] = 6;
	g_packetLenMap[694] = 7;
	g_packetLenMap[695] = 7;
	g_packetLenMap[705] = -1;
	g_packetLenMap[706] = -1;
	g_packetLenMap[708] = 26;
	g_packetLenMap[709] = 30;
	g_packetLenMap[712] = 3;
	g_packetLenMap[713] = 3;
	g_packetLenMap[710] = 30;
	g_packetLenMap[711] = 7;
	g_packetLenMap[715] = 65;
	g_packetLenMap[716] = 4;
	g_packetLenMap[717] = 71;
	g_packetLenMap[718] = 10;
	g_packetLenMap[719] = 6;
	g_packetLenMap[725] = 2;
	g_packetLenMap[720] = -1;
	g_packetLenMap[721] = -1;
	g_packetLenMap[722] = -1;
	g_packetLenMap[723] = 4;
	g_packetLenMap[724] = 29;
	g_packetLenMap[726] = 6;
	g_packetLenMap[727] = -1;
	g_packetLenMap[728] = 10;
	g_packetLenMap[729] = 10;
	g_packetLenMap[730] = 3;
	g_packetLenMap[731] = -1;
	g_packetLenMap[732] = -1;
	g_packetLenMap[733] = 32;
	g_packetLenMap[734] = 6;
	g_packetLenMap[735] = 36;
	g_packetLenMap[736] = 34;
	g_packetLenMap[737] = 33;
	g_packetLenMap[738] = 8;
	g_packetLenMap[739] = 10;
	g_packetLenMap[740] = 6;
	g_packetLenMap[741] = 5;
	g_packetLenMap[742] = 6;
	g_packetLenMap[743] = -1;
	g_packetLenMap[744] = -1;
	g_packetLenMap[745] = -1;
	g_packetLenMap[746] = -1;
	g_packetLenMap[747] = 13;
	g_packetLenMap[748] = 67;
	g_packetLenMap[749] = 59;
	g_packetLenMap[750] = 60;
	g_packetLenMap[751] = 8;
	g_packetLenMap[752] = 10;
	g_packetLenMap[753] = 2;
	g_packetLenMap[754] = 2;
	g_packetLenMap[755] = -1;
	g_packetLenMap[756] = -1;
	g_packetLenMap[757] = -1;
	g_packetLenMap[758] = -1;
	g_packetLenMap[759] = -1;
	g_packetLenMap[760] = -1;
	g_packetLenMap[761] = -1;
	g_packetLenMap[762] = -1;
	g_packetLenMap[763] = -1;
	g_packetLenMap[764] = -1;
	g_packetLenMap[765] = -1;
	g_packetLenMap[766] = -1;
	g_packetLenMap[767] = -1;
	g_packetLenMap[768] = -1;
	g_packetLenMap[769] = -1;
	g_packetLenMap[770] = -1;
	g_packetLenMap[771] = -1;
	g_packetLenMap[772] = -1;
	g_packetLenMap[773] = -1;
	g_packetLenMap[774] = -1;
	g_packetLenMap[775] = -1;
	g_packetLenMap[776] = -1;
	g_packetLenMap[777] = -1;
	g_packetLenMap[778] = -1;
	g_packetLenMap[779] = -1;
	g_packetLenMap[780] = -1;
	g_packetLenMap[781] = -1;
	g_packetLenMap[782] = -1;
	g_packetLenMap[783] = -1;
	g_packetLenMap[784] = -1;
	g_packetLenMap[785] = -1;
	g_packetLenMap[786] = -1;
	g_packetLenMap[787] = -1;
	g_packetLenMap[788] = -1;
	g_packetLenMap[789] = -1;
	g_packetLenMap[790] = -1;
	g_packetLenMap[791] = -1;
	g_packetLenMap[792] = -1;
	g_packetLenMap[793] = -1;
	g_packetLenMap[794] = -1;
	g_packetLenMap[795] = -1;
	g_packetLenMap[796] = -1;
	g_packetLenMap[797] = -1;
	g_packetLenMap[798] = -1;
	g_packetLenMap[799] = -1;
	g_packetLenMap[800] = -1;
	g_packetLenMap[801] = -1;
	g_packetLenMap[802] = -1;
	g_packetLenMap[803] = -1;
	g_packetLenMap[804] = -1;
	g_packetLenMap[805] = -1;
	g_packetLenMap[806] = -1;
	g_packetLenMap[807] = -1;
	g_packetLenMap[808] = -1;
	g_packetLenMap[809] = -1;
	g_packetLenMap[810] = -1;
	g_packetLenMap[811] = -1;
	g_packetLenMap[812] = -1;
	g_packetLenMap[813] = -1;
	g_packetLenMap[814] = -1;
	g_packetLenMap[815] = -1;
	g_packetLenMap[816] = -1;
	g_packetLenMap[817] = -1;
	g_packetLenMap[818] = -1;
	g_packetLenMap[819] = -1;
	g_packetLenMap[820] = -1;
	g_packetLenMap[821] = -1;
	g_packetLenMap[822] = -1;
	g_packetLenMap[823] = -1;
	g_packetLenMap[824] = -1;
	g_packetLenMap[825] = -1;
	g_packetLenMap[826] = -1;
	g_packetLenMap[827] = -1;
	g_packetLenMap[828] = -1;
	g_packetLenMap[829] = -1;
	g_packetLenMap[830] = -1;
	g_packetLenMap[831] = -1;
	g_packetLenMap[832] = -1;
	g_packetLenMap[833] = -1;
	g_packetLenMap[834] = -1;
	g_packetLenMap[835] = -1;
	g_packetLenMap[836] = -1;
	g_packetLenMap[837] = -1;
	g_packetLenMap[838] = -1;
	g_packetLenMap[839] = -1;
	g_packetLenMap[840] = -1;
	g_packetLenMap[841] = -1;
	g_packetLenMap[842] = -1;
	g_packetLenMap[843] = -1;
	g_packetLenMap[844] = -1;
	g_packetLenMap[845] = -1;
	g_packetLenMap[846] = -1;
	g_packetLenMap[847] = -1;
	g_packetLenMap[848] = -1;
	g_packetLenMap[849] = -1;
	g_packetLenMap[850] = -1;
	g_packetLenMap[851] = -1;
	g_packetLenMap[852] = -1;
	g_packetLenMap[853] = -1;
	g_packetLenMap[854] = -1;
	g_packetLenMap[855] = -1;
	g_packetLenMap[856] = -1;
	g_packetLenMap[857] = -1;
	g_packetLenMap[858] = -1;
	g_packetLenMap[859] = -1;
	g_packetLenMap[860] = 2;
	g_packetLenMap[861] = -1;
	g_packetLenMap[862] = 2;
	g_packetLenMap[863] = -1;
	g_packetLenMap[864] = -1;
	g_packetLenMap[865] = -1;
	g_packetLenMap[866] = -1;
	g_packetLenMap[867] = -1;
	g_packetLenMap[868] = -1;
	g_packetLenMap[869] = -1;
	g_packetLenMap[870] = -1;
	g_packetLenMap[871] = -1;
	g_packetLenMap[872] = -1;
	g_packetLenMap[873] = -1;
	g_packetLenMap[874] = -1;
	g_packetLenMap[875] = -1;
	g_packetLenMap[876] = -1;
	g_packetLenMap[877] = -1;
	g_packetLenMap[878] = -1;
	g_packetLenMap[879] = -1;
	g_packetLenMap[880] = -1;
	g_packetLenMap[881] = -1;
	g_packetLenMap[882] = -1;
	g_packetLenMap[883] = -1;
	g_packetLenMap[884] = -1;
	g_packetLenMap[885] = -1;
	g_packetLenMap[886] = -1;
	g_packetLenMap[887] = -1;
	g_packetLenMap[888] = -1;
	g_packetLenMap[889] = -1;
	g_packetLenMap[890] = -1;
	g_packetLenMap[891] = -1;
	g_packetLenMap[892] = -1;
	g_packetLenMap[893] = -1;
	g_packetLenMap[894] = -1;
	g_packetLenMap[895] = -1;
	g_packetLenMap[896] = -1;
	g_packetLenMap[897] = -1;
	g_packetLenMap[898] = -1;
	g_packetLenMap[899] = -1;
	g_packetLenMap[900] = -1;
	g_packetLenMap[901] = -1;
	g_packetLenMap[902] = -1;
	g_packetLenMap[903] = -1;
	g_packetLenMap[904] = -1;
	g_packetLenMap[905] = -1;
	g_packetLenMap[906] = -1;
	g_packetLenMap[907] = -1;
	g_packetLenMap[908] = -1;
	g_packetLenMap[909] = -1;
	g_packetLenMap[910] = -1;
	g_packetLenMap[911] = -1;
	g_packetLenMap[912] = -1;
	g_packetLenMap[913] = -1;
	g_packetLenMap[914] = -1;
	g_packetLenMap[915] = -1;
	g_packetLenMap[916] = -1;
	g_packetLenMap[917] = -1;
	g_packetLenMap[918] = -1;
	g_packetLenMap[919] = -1;
	g_packetLenMap[920] = -1;
	g_packetLenMap[921] = -1;
	g_packetLenMap[922] = -1;
	g_packetLenMap[923] = -1;
	g_packetLenMap[924] = -1;
	g_packetLenMap[925] = -1;
	g_packetLenMap[926] = -1;
	g_packetLenMap[927] = -1;
	g_packetLenMap[928] = -1;
	g_packetLenMap[929] = -1;
	g_packetLenMap[930] = -1;
	g_packetLenMap[931] = -1;
	g_packetLenMap[932] = -1;
	g_packetLenMap[933] = -1;
	g_packetLenMap[934] = -1;
	g_packetLenMap[935] = -1;
	g_packetLenMap[936] = -1;
	g_packetLenMap[937] = -1;
	g_packetLenMap[938] = -1;
	g_packetLenMap[939] = -1;
	g_packetLenMap[940] = -1;
	g_packetLenMap[941] = -1;
	g_packetLenMap[942] = -1;
	g_packetLenMap[943] = -1;
	g_packetLenMap[944] = -1;
	g_packetLenMap[945] = -1;
	g_packetLenMap[946] = -1;
	g_packetLenMap[947] = -1;
	g_packetLenMap[948] = -1;
	g_packetLenMap[949] = -1;
	g_packetLenMap[950] = -1;
	g_packetLenMap[951] = -1;
	g_packetLenMap[952] = -1;
	g_packetLenMap[953] = -1;
	g_packetLenMap[954] = -1;
	g_packetLenMap[955] = -1;
	g_packetLenMap[956] = -1;
	g_packetLenMap[957] = -1;
	g_packetLenMap[958] = -1;
	g_packetLenMap[959] = -1;
	g_packetLenMap[960] = -1;
	g_packetLenMap[961] = -1;
	g_packetLenMap[962] = -1;
	g_packetLenMap[963] = -1;
	g_packetLenMap[964] = -1;
	g_packetLenMap[965] = -1;
	g_packetLenMap[966] = -1;
	g_packetLenMap[967] = -1;
	g_packetLenMap[968] = -1;
	g_packetLenMap[969] = -1;
	g_packetLenMap[970] = -1;
	g_packetLenMap[971] = -1;
	g_packetLenMap[972] = -1;
	g_packetLenMap[973] = -1;
	g_packetLenMap[974] = -1;
	g_packetLenMap[975] = -1;
	g_packetLenMap[976] = -1;
	g_packetLenMap[977] = -1;
	g_packetLenMap[978] = -1;
	g_packetLenMap[979] = -1;
	g_packetLenMap[980] = -1;
	g_packetLenMap[981] = -1;
	g_packetLenMap[982] = -1;
	g_packetLenMap[983] = -1;
	g_packetLenMap[984] = -1;
	g_packetLenMap[985] = -1;
	g_packetLenMap[986] = -1;
	g_packetLenMap[987] = -1;
	g_packetLenMap[988] = -1;
	g_packetLenMap[989] = 18;
	g_packetLenMap[990] = 18;
	g_packetLenMap[994] = -1;
	g_packetLenMap[995] = -1;
	g_packetLenMap[996] = -1;
	g_packetLenMap[997] = -1;
	g_packetLenMap[998] = -1;
	g_packetLenMap[999] = -1;
	g_packetLenMap[1000] = -1;
	g_packetLenMap[1001] = -1;
	g_packetLenMap[1002] = -1;
	g_packetLenMap[1003] = -1;
	g_packetLenMap[1004] = -1;
	g_packetLenMap[1005] = -1;
	g_packetLenMap[1006] = -1;
	g_packetLenMap[1007] = -1;
	g_packetLenMap[1008] = -1;
	g_packetLenMap[1009] = -1;
	g_packetLenMap[1010] = -1;
	g_packetLenMap[1011] = -1;
	g_packetLenMap[1012] = -1;
	g_packetLenMap[1013] = -1;
	g_packetLenMap[1014] = -1;
	g_packetLenMap[1015] = -1;
	g_packetLenMap[1016] = -1;
	g_packetLenMap[1017] = -1;
	g_packetLenMap[1018] = -1;
	g_packetLenMap[1019] = -1;
	g_packetLenMap[1020] = -1;
	g_packetLenMap[1021] = -1;
	g_packetLenMap[1022] = -1;
	g_packetLenMap[1023] = -1;
	g_packetLenMap[1024] = -1;
	g_packetLenMap[1025] = -1;
	g_packetLenMap[1026] = -1;
	g_packetLenMap[1027] = -1;
	g_packetLenMap[1028] = -1;
	g_packetLenMap[1029] = -1;
	g_packetLenMap[1030] = -1;
	g_packetLenMap[1031] = -1;
	g_packetLenMap[1032] = -1;
	g_packetLenMap[1033] = -1;
	g_packetLenMap[1034] = -1;
	g_packetLenMap[1035] = -1;
	g_packetLenMap[1036] = -1;
	g_packetLenMap[1037] = -1;
	g_packetLenMap[1038] = -1;
	g_packetLenMap[1039] = -1;
	g_packetLenMap[1040] = -1;
	g_packetLenMap[1041] = -1;
	g_packetLenMap[1042] = -1;
	g_packetLenMap[1043] = -1;
	g_packetLenMap[1044] = -1;
	g_packetLenMap[1045] = -1;
	g_packetLenMap[1046] = -1;
	g_packetLenMap[1047] = -1;
	g_packetLenMap[1048] = -1;
	g_packetLenMap[1049] = -1;
	g_packetLenMap[1050] = -1;
	g_packetLenMap[1051] = -1;
	g_packetLenMap[1052] = -1;
	g_packetLenMap[1053] = -1;
	g_packetLenMap[1054] = -1;
	g_packetLenMap[1055] = -1;
	g_packetLenMap[1056] = -1;
	g_packetLenMap[1057] = -1;
	g_packetLenMap[1058] = -1;
	g_packetLenMap[1059] = -1;
	g_packetLenMap[1060] = -1;
	g_packetLenMap[1061] = -1;
	g_packetLenMap[1062] = -1;
	g_packetLenMap[1063] = -1;
	g_packetLenMap[1064] = -1;
	g_packetLenMap[1065] = -1;
	g_packetLenMap[1066] = -1;
	g_packetLenMap[1067] = -1;
	g_packetLenMap[1068] = -1;
	g_packetLenMap[1069] = -1;
	g_packetLenMap[1070] = -1;
	g_packetLenMap[1071] = -1;
	g_packetLenMap[1072] = -1;
	g_packetLenMap[1073] = -1;
	g_packetLenMap[1074] = -1;
	g_packetLenMap[1075] = -1;
	g_packetLenMap[1076] = -1;
	g_packetLenMap[1077] = -1;
	g_packetLenMap[1078] = 19;
	g_packetLenMap[1079] = 7;
	g_packetLenMap[1080] = 10;
	g_packetLenMap[1081] = 8;
	g_packetLenMap[1085] = 8;
	g_packetLenMap[1086] = -1;
	g_packetLenMap[1087] = 25;
	g_packetLenMap[1088] = 10;
	g_packetLenMap[1089] = 4;
	g_packetLenMap[1090] = -1;
	g_packetLenMap[1091] = 8;
	g_packetLenMap[1094] = 14;
	g_packetLenMap[1096] = -1;
	g_packetLenMap[1098] = 6;
	g_packetLenMap[1099] = 2;
	g_packetLenMap[2000] = 6;
	g_packetLenMap[2001] = 2;
	g_packetLenMap[2002] = -1;
	g_packetLenMap[2003] = 4;
	g_packetLenMap[2004] = 4;
	g_packetLenMap[2005] = 4;
	g_packetLenMap[2006] = 4;
	g_packetLenMap[1095] = 2;
	g_packetLenMap[2007] = 8;
	g_packetLenMap[2008] = 8;
	g_packetLenMap[2009] = 268;
	g_packetLenMap[2010] = 6;
	g_packetLenMap[2011] = 8;
	g_packetLenMap[2012] = 6;
	g_packetLenMap[2013] = 54;
	g_packetLenMap[2014] = 30;
	g_packetLenMap[2015] = 54;
	g_packetLenMap[2016] = 58;
	g_packetLenMap[2017] = 15;
	g_packetLenMap[2018] = 8;
	g_packetLenMap[2019] = 6;
	g_packetLenMap[2020] = -1;
	g_packetLenMap[2022] = 8;
	g_packetLenMap[2021] = 8;
	g_packetLenMap[2024] = -1;
	g_packetLenMap[2023] = 32;
	g_packetLenMap[2025] = 5;
	g_packetLenMap[2026] = 2;
	g_packetLenMap[2027] = -1;
	g_packetLenMap[2028] = 8;
	g_packetLenMap[2029] = 10;
	g_packetLenMap[2030] = 6;
	g_packetLenMap[2031] = 8;
	g_packetLenMap[2032] = 8;
	g_packetLenMap[2033] = 15;
	g_packetLenMap[2034] = 6;
	g_packetLenMap[2035] = 4;
	g_packetLenMap[2036] = 3;
}
