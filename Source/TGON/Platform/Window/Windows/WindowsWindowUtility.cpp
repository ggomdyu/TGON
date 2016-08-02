#include "PrecompiledHeader.h"
#include "WindowsWindowUtility.h"

#include <Windows.h>
#include <cassert>

#include "../WindowStyle.h"
#include "../Windows/WindowsWindow.h"


void tgon::ConvertWindowStyleToDword( 
	IN const WindowStyle& wndStyle, 
	OUT DWORD* exWndStyle, 
	OUT DWORD* normalWndStyle )
{
	*exWndStyle = 0;
	*normalWndStyle = 0;

	/* Extended style */
	if ( wndStyle.topMost )
	{
		*exWndStyle |= WS_EX_TOPMOST;
	}
	else if ( wndStyle.showTopOnCreated )
	{
		*exWndStyle |= WS_EX_APPWINDOW;
	}

	if ( wndStyle.supportPerPixelTransparency )
	{
		*exWndStyle |= WS_EX_LAYERED;
	}


	/* Normal style */
	if ( wndStyle.maximized )
	{
		*normalWndStyle |= WS_MAXIMIZE;
		assert( !wndStyle.minimized && "Can't be selected both Maximized and Minimized." );
	}
	else if ( wndStyle.minimized )
	{
		*normalWndStyle |= WS_MINIMIZE;
	}

	if ( wndStyle.resizeable )
	{
		*normalWndStyle |= WS_THICKFRAME;
		assert( !wndStyle.popup && "Can't be selected both Resizeable and Popup." );
	}
	else if ( wndStyle.popup )
	{
		*normalWndStyle |= WS_POPUP;
	}

	if ( wndStyle.showImmediately )
	{
		*normalWndStyle |= WS_VISIBLE;
	}
	if ( wndStyle.supportWindowTransparency )
	{
		*normalWndStyle |= WS_EX_LAYERED;
	}
}


void tgon::ReshapeWindowForm(
	const WindowsWindow& from,
	const WindowsWindow& to )
{
	// Get destination window's placement information
	WINDOWPLACEMENT wndPlacementInfo;
	GetWindowPlacement( to.GetWindowHandle(), &wndPlacementInfo );
	
	// And move source window as described
	SetWindowPlacement( from.GetWindowHandle(), &wndPlacementInfo );

	// Also Change window style 
	const DWORD normalWndStyle = GetWindowLongPtrW( to.GetWindowHandle( ), GWL_STYLE );
	const DWORD extendedWndStyle = GetWindowLongPtrW( to.GetWindowHandle( ), GWL_EXSTYLE );
	
	SetWindowLongPtrW( from.GetWindowHandle( ), GWL_STYLE, normalWndStyle );
	SetWindowLongPtrW( from.GetWindowHandle( ), GWL_EXSTYLE, extendedWndStyle );

	// If you have changed window data using SetWindowLong, you must call
	// SetWindowPos for the changes to take effect.
	// Use the following combination for uFlags: SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED. 
	SetWindowPos( from.GetWindowHandle(), nullptr, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
}