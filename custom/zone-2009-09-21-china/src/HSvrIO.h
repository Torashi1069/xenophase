#pragma once
#include "SvrIO.h"
#include "HSvrIOPacketHandler.h"


class CHSvrIO : public CSvrIO
{
	struct vtable_t
	{
		void* (CHSvrIO::* scalar_deleting_destructor)(unsigned int flags);
		int (CSvrIO::* OnProcess)(void);
		void (CSvrIO::* OnCustomInit)(void);
	};

	/* this+0 */ public: //CSvrIO baseclass_0;

	public: CHSvrIO::CHSvrIO(void);
	public: virtual CHSvrIO::~CHSvrIO(void);
	public: CHSvrIOPacketHandler* CHSvrIO::GetPacketHandlerPtr(void);

private:
	static hook_method<CHSvrIOPacketHandler* (CHSvrIO::*)(void)> CHSvrIO::_GetPacketHandlerPtr;
};
