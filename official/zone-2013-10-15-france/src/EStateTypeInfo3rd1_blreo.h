#pragma once
#include "Enum.h"
#include "EStateTypeInfo.h"
class CCharacter;


class ESTATE_FROSTMISTY : public ESTATE
{
public:
	virtual bool SetCheckup(CActor* in_cpActor, int& io_Time, int& io_Val1, int& io_Val2, int& io_val3);
	virtual void SetComplete(CActor* in_cpActor, const int in_Time, const int in_Val1, const int in_Val2, const int in_Val3);
	virtual void ResetComplete(CActor* in_cpActor, const int in_Val1, const int in_Val2, const int in_Val3);
	static int GetDefaultLifeTM(CCharacter* in_cpTarget);

public:
	ESTATE_FROSTMISTY() : ESTATE(EFST_FROSTMISTY, "EFST_FROSTMISTY") { }
//	virtual ~ESTATE_FROSTMISTY();
};
