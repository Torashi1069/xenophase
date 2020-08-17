#pragma once
#include "EStateTypeInfo.h"
class CPC;


class ESTATE_CIRCLE_OF_FIRE_OPTION : public ESTATE
{
public:
	virtual bool SetCheckup(CActor* in_cpActor, int& io_Time, int& io_Val1, int& io_Val2, int& io_val3);
	virtual void SetComplete(CActor* in_cpActor, const int in_Time, const int in_Val1, const int in_Val2, const int in_Val3);
	virtual void ResetComplete(CActor* in_cpActor, const int in_Val1, const int in_Val2, const int in_Val3);
	static void Operation(CPC* in_cpPlayer, const int in_ATKpercent);

public:
	ESTATE_CIRCLE_OF_FIRE_OPTION();
	virtual ~ESTATE_CIRCLE_OF_FIRE_OPTION();
};
