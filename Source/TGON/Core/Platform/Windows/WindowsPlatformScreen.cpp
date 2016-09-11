#include "PrecompiledHeader.h"
#include "WindowsPlatformScreen.h"

#include <Windows.h>



namespace tgon
{


int32_t WindowsScreen::GetMonitorCount( )
{
	return GetSystemMetrics( SM_CMONITORS );
}

int32_t WindowsScreen::GetMainWidth( )
{
	return GetSystemMetrics( SM_CXSCREEN );
}

int32_t WindowsScreen::GetMainHeight( )
{
	return GetSystemMetrics( SM_CYSCREEN );
}


} /*namespace tgon*/