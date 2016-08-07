#include "PrecompiledHeader.h"
#include "WindowsScreen.h"

#include <Windows.h>


int32_t tgon::WindowsScreen::GetMonitorCount( )
{
	return GetSystemMetrics( SM_CMONITORS );
}

int32_t tgon::WindowsScreen::GetMainWidth( )
{
	return GetSystemMetrics( SM_CXSCREEN );
}

int32_t tgon::WindowsScreen::GetMainHeight( )
{
	return GetSystemMetrics( SM_CYSCREEN );
}