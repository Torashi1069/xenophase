#include "mss.h"


hook_func<DXDEC void (AILCALL *)(HSTREAM stream,S32 volume)> _AIL_set_stream_volume("mss32.dll", "_AIL_set_sample_volume@8");
DXDEC void AILCALL AIL_set_stream_volume(HSTREAM stream,S32 volume)
{
	return (_AIL_set_stream_volume)(stream, volume);

	//TODO
}
