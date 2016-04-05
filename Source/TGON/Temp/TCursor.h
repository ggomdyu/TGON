#pragma once
#include <Platform/Platform.hpp>

#ifdef TGON_PLATFORM_WINDOWS
	#include "WindowsCursor.h"
#elif TGON_PLATFORM_LINUX
#elif TGON_PLATFORM_MAC
#endif


namespace tgon
{


class TCursor : public CursorImpl
{
public:
	static void SetPosition( const int32_t x, const int32_t y ) {
		CursorImpl::SetPosition( x, y );
	}

	static void GetPosition( int32_t* x, int32_t* y ) {
		CursorImpl::GetPosition( x, y );
	}
};


}
