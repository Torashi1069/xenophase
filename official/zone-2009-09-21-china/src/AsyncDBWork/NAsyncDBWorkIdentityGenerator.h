#pragma once


class CNAsyncDBWorkIdentityGenerator
{
	enum
	{
		MINIMUM_IDENTITY = 100
	};

	/* this+0x0 */ private: int m_IdentityCnt;

	public: int CNAsyncDBWorkIdentityGenerator::operator()(void);
	public: CNAsyncDBWorkIdentityGenerator::CNAsyncDBWorkIdentityGenerator(void);
	public: CNAsyncDBWorkIdentityGenerator::~CNAsyncDBWorkIdentityGenerator(void);
};
