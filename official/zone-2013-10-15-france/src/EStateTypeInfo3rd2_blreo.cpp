#include "Character.h"
#include "Enum.h"
#include "EStateTypeInfo3rd2_blreo.h"


bool IsAgitTrigerNPC(int in_Job) // 75-86
{
	return ( in_Job == JT_EMPELIUM
	      || in_Job == JT_BARRICADE
	      || in_Job == JT_BARRICADE_
	      || in_Job == JT_S_EMPEL_1
	      || in_Job == JT_S_EMPEL_2
	      );
}


bool IsAgitTrigerNPC(CCharacter* in_cpCH) // 89-93
{
	int Job = -1;
	in_cpCH->GetParameterValue(VAR_JOB, Job);

	return IsAgitTrigerNPC(Job);
}
