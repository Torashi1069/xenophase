#pragma once


class NInter
{
	enum
	{
		NINTERMSG_REQ_THREAD_QUIT             = 0x0,
		NINTERMSG_REQ_CONNECT                 = 0x1,
		NINTERMSG_RES_CONNECT_FAIL            = 0x2,
		NINTERMSG_RES_CONNECT_SUCCESS         = 0x3,
		NINTERMSG_NOTIFY_DISCONNECT           = 0x4,
		NINTERMSG_NOTIFY_ERROR_RESQUEUE_WRITE = 0x5,
		NINTERMSG_INSTANTMAP_CONTROLLER       = 0x6,
		NINTERMSG_INSTANTMAP_WORKTHREAD_WORK  = 0x7,
	};

	struct vtable_t
	{
		void (NInter::* PostInterMessage)(const unsigned int, const unsigned long, const int, const int, const int); //__purecall
		bool (NInter::* PeekInterMessage)(const unsigned long, unsigned int&, int&, int&, int&, const bool); //__purecall
		void* (NInter::* vector_deleting_destructor)(unsigned int);
	};

	/* this+0x0 */ //const NInter::`vftable'

	public: virtual void NInter::PostInterMessage(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam) = 0;
	public: virtual bool NInter::PeekInterMessage(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Msg, int& out_wParam, int& out_lParam, const bool in_bRemove) = 0;
	public: NInter::NInter(void);
	public: virtual NInter::~NInter(void);
};
