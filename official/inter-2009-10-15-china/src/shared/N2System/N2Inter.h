#pragma once


class N2Inter
{
	struct vtable_t
	{
		void (N2Inter::* PostInterMessage)(const unsigned int, const int, const int, const int); //__purecall
		bool (N2Inter::* PeekInterMessage)(unsigned int&, int&, int&, int&, const bool); //__purecall
		void* (N2Inter::* vector_deleting_destructor)(unsigned int);
	};

	/* this+0x0 */ //const N2Inter::`vftable'

	public: virtual void PostInterMessage(const unsigned int, const int, const int, const int) = 0;
	public: virtual bool PeekInterMessage(unsigned int&, int&, int&, int&, const bool) = 0;
	public: N2Inter::N2Inter(void);
	public: virtual N2Inter::~N2Inter(void);
};
