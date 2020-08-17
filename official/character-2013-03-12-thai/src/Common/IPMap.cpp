#include "Common/IPMap.h"
////////////////////////////////////////


/// statics
IPBean IPBean::Null("0.0.0.0");


IPBean::IPBean(const char* ip)
{
	mIP = ntohl(inet_addr(ip));
}


////////////////////////////////////////


IPMap::IPMap()
{
	memset(mBClassIPMap, 0, sizeof(mBClassIPMap));
}


IPMap::~IPMap()
{
	for( int i = 0; i < UINT16_MAX; ++i )
	{
		if( mBClassIPMap[i] != NULL )
		{
			delete mBClassIPMap[i];
			mBClassIPMap[i] = NULL;
		}
	}
}


////////////////////////////////////////
