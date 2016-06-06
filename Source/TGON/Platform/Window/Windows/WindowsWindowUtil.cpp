#include "PrecompiledHeader.h"
#include "WindowsWindowUtil.h"


#include "../WindowStyle.h"
#include "../Windows/WindowsWindow.h"


void tgon::Convert_wndstyle_to_dword(
	const WindowStyle& wndStyle,
	_Out_ DWORD* exWndStyle,
	_Out_ DWORD* normalWndStyle )
{
	*exWndStyle = 0;
	*normalWndStyle = 0;


	/*
		Extended style
	*/
	if ( wndStyle.TopMost )
	{
		*exWndStyle |= WS_EX_TOPMOST;
	}
	else if ( wndStyle.ShowTopOnCreated )
	{
		*exWndStyle |= WS_EX_APPWINDOW;
	}
	if ( wndStyle.SupportPerPixelTransparency )
	{
		*exWndStyle |= WS_EX_LAYERED;
	}


	/*
		Normal style
	*/
	if ( wndStyle.Maximized )
	{
		*normalWndStyle |= WS_MAXIMIZE;
		assert( !wndStyle.Minimized &&
				"Can't be selected both Maximized and Minimized." );
	}
	else if ( wndStyle.Minimized )
	{
		*normalWndStyle |= WS_MINIMIZE;
	}

	if ( wndStyle.Resizeable )
	{
		*normalWndStyle |= WS_THICKFRAME;
		assert( !wndStyle.Popup &&
				"Can't be selected both Resizeable and Popup." );
	}
	else if ( wndStyle.Popup )
	{
		*normalWndStyle |= WS_POPUP;
	}

	// Single member
	if ( wndStyle.ShowImmediately )
	{
		*normalWndStyle |= WS_VISIBLE;
	}
	if ( wndStyle.SupportWindowTransparency )
	{
		*normalWndStyle |= WS_EX_LAYERED;
	}
}


void tgon::ReshapeWindowForm(
	const WindowsWindow& from,
	const WindowsWindow& to )
{
	DWORD normalStyle =
		GetWindowLongPtrW( to.GetWindowHandle(), GWL_STYLE );
	SetWindowLongPtrW( from.GetWindowHandle(),
		GWL_STYLE, normalStyle );

	DWORD exStyle = GetWindowLongPtrW( to.GetWindowHandle(), 
		GWL_EXSTYLE );
	SetWindowLongPtrW( from.GetWindowHandle(),
					   GWL_EXSTYLE,
					   exStyle );

	WINDOWPLACEMENT wp;
	GetWindowPlacement( to.GetWindowHandle(), &wp );
	SetWindowPlacement( from.GetWindowHandle(), &wp );

	/*
		If you have changed window data using SetWindowLong, you must call
		SetWindowPos for the changes to take effect.
		Use the following combination for uFlags: SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED. 
		
		cf. https://msdn.microsoft.com/ko-kr/library/windows/desktop/ms633545(v=vs.85).aspx
	*/
	SetWindowPos( from.GetWindowHandle(), nullptr, 0, 0, 0, 0,
				  SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
}