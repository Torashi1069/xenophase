#pragma once
class CPC;
namespace Effect3rd {


struct tagEffect3rdDBFmt
{
	/* this+ 0 */ int ID;
	/* this+ 4 */ int TimeMS;
	/* this+ 8 */ int Data1;
	/* this+12 */ int Data2;
	/* this+16 */ int Data3;

	tagEffect3rdDBFmt() { }
	tagEffect3rdDBFmt(int in_ID, int in_TimeMS, int in_Data1, int in_Data2, int in_Data3) : ID(in_ID), TimeMS(in_TimeMS), Data1(in_Data1), Data2(in_Data2), Data3(in_Data3) { }
};


void Delete(const int in_AID, const int in_GID, const int in_EffectID);
void UpdateAll(CPC* in_cpPlayer);


}; // namespace
