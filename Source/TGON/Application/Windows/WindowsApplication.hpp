#pragma once
#include "WindowsApplication.h"


inline HINSTANCE tgon::WindowsApplication::GetInstanceHandle( ) const
{
	return m_instanceHandle;
}


inline void tgon::WindowsApplication::GetScreenSize(
		int32_t* const width,
		int32_t* const height )
{
	*width = GetSystemMetrics( SM_CXSCREEN );
	*height = GetSystemMetrics( SM_CYSCREEN );
}


inline void tgon::WindowsApplication::GetCursorPosition(
		int32_t* const x,
		int32_t* const y )
{
	POINT pt;
	GetCursorPos( &pt );

	*x = pt.x;
	*y = pt.y;
}