#include "stdafx.h"
#include "WindowsApplication.h"

#include "WindowsWindow.h"

HINSTANCE tgon::WindowsApplication::m_hInstance( GetModuleHandle( NULL ));

bool tgon::WindowsApplication::ResponseMessage( )
{
	MSG msg = { 0 };
	BOOL bExistMsg = PeekMessage( &msg, NULL, 0, 0, PM_REMOVE );

	if ( bExistMsg )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return bExistMsg != 0;
}