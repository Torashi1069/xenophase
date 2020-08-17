#pragma once


class NXInter
{
public:
	enum
	{
		NINTERMSG_REQ_THREAD_QUIT             = 0,
		NINTERMSG_REQ_CONNECT                 = 1,
		NINTERMSG_RES_CONNECT_FAIL            = 2,
		NINTERMSG_RES_CONNECT_SUCCESS         = 3,
		NINTERMSG_NOTIFY_DISCONNECT           = 4,
		NINTERMSG_NOTIFY_ERROR_RESQUEUE_WRITE = 5,
		NINTERMSG_INSTANTMAP_CONTROLLER       = 6,
		NINTERMSG_INSTANTMAP_WORKTHREAD_WORK  = 7,
	};

public:
	virtual void PostInterMessage(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam) = 0;
	virtual bool PeekInterMessage(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Msg, int& out_wParam, int& out_lParam, const bool in_bRemove) = 0;

public:
	NXInter();
	virtual ~NXInter();
};
