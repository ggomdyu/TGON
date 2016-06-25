#pragma once
#include <windows.h>

namespace tgon
{


class WindowsCursor;
typedef WindowsCursor CursorImpl;


class WindowsCursor
{
public:
	static void SetPosition( const int32_t x, const int32_t y )
	{
		SetCursorPos( x, y );
	}

	static void GetPosition( _Out_ int32_t* x, _Out_ int32_t* y )
	{
		POINT pt;
		GetCursorPos( &pt );

		*x = pt.x;
		*y = pt.y;
	}
};


}
