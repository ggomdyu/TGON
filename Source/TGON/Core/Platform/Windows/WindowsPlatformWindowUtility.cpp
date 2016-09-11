// 
// Copyright (c) 2015 ggomdyu
// 
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
// 

#include "PrecompiledHeader.h"
#include "WindowsPlatformWindowUtility.h"

#include "WindowsPlatformWindow.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>
#include <cassert>
#include <codecvt>


/*
namespace tgon {


bool UTF8ToUTF16( const char* utf16Src, wchar_t* utf16Dest )
{
	enum BinaryTable
	{
		_1000_0000 = 0x80,
		_1100_0000 = 0xC0,
		_1110_0000 = 0xE0,
		_0001_1111 = 0x1F,
		_0011_1111 = 0x3F,
	};

	int32_t destIndex = 0;
	for ( int32_t i = 0; utf16Src[i] != '\0'; ++i )
	{
		// 000000-00007F : American character field
		if (( utf16Src[i] & _1000_0000 ) == 0 )
		{
			utf16Dest[destIndex++] = utf16Src[i];
		}

		// 000080-0007FF : European character field
		else if (( utf16Src[i] & _1110_0000 ) == _1100_0000 &&
				 ( utf16Src[i+1] & _1100_0000 ) == _1000_0000 )
		{
			wchar_t ch = (( utf16Src[i] & _0001_1111 ) << 6 ) +
						 ( utf16Src[i] & _0011_1111 );

			utf16Dest[destIndex++] = ch;
			i += 1;
		}
		// 000800-00FFFF : Asian character field
		else if (( utf16Src[i] & _1110_0000 ) == _1110_0000 &&
				 ( utf16Src[i+1] & _1100_0000 ) == _1000_0000 &&
				 ( utf16Src[i+2] & _1100_0000 ) == _1000_0000 )
		{
			wchar_t ch = ( utf16Src[i] << 12 ) +
						 (( utf16Src[i+1] & _0011_1111 ) << 6 ) +
						 ( utf16Src[i+2] & _0011_1111 );

			utf16Dest[destIndex++] = ch;
			i += 2;
		}
		else
		{
			// Error: The forwarded string is not UTF-8 encoded
			return false;
		}
	}

	return true;
}
*/

namespace tgon
{


void ConvertWindowStyleToDword( /*IN*/ const WindowStyle& wndStyle,
								/*OUT*/ DWORD* exWndStyle, 
								/*OUT*/ DWORD* normalWndStyle )
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

HWND CreateWindowForm( /*IN*/ const struct WindowStyle& wndStyle,
					   /*IN*/ const wchar_t* className,
					   /*IN*/ HINSTANCE instanceHandle,
					   /*IN_OPT*/ void* extraParam )
{
	// Set coordinates of window
	int32_t x = wndStyle.x;
	int32_t y = wndStyle.y;

	if ( wndStyle.showMiddle )
	{
		x = static_cast<int32_t>( GetSystemMetrics( SM_CXSCREEN )*0.5 - 
								  wndStyle.width*0.5 );
		y = static_cast<int32_t>( GetSystemMetrics( SM_CYSCREEN )*0.5 - 
								  wndStyle.height*0.5 );
	}

	// Convert WindowStyle to platform dependent style.
	DWORD normalStyle, exStyle;
	ConvertWindowStyleToDword( wndStyle, &exStyle, &normalStyle );
	
	// Convert title, which utf-8 encoded, to utf-16.
	// This string encoding converter shows too bad performance!
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> utfConverter;
	std::wstring utf16Title( utfConverter.from_bytes( wndStyle.title.c_str( )));

	// Create a Window
	HWND wndHandle = CreateWindowExW(
		exStyle,
		className,
		utf16Title.c_str( ),
		// WS_CLIPSIBLINGS, WS_CLIPCHILDREN prevent other windows from drawing over or into our window.
		normalStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		x,
		y, 
		wndStyle.width, 
		wndStyle.height,
		nullptr,
		nullptr,
		instanceHandle,
		extraParam	// Extra parameter( pass this pointer when need to handling WM_CREATE )
	);

	return wndHandle;
}

void ReshapeWindowForm( /*IN*/ const WindowsPlatformWindow& from, 
						/*IN*/ const WindowsPlatformWindow& to )
{
	// Get destination window's placement information
	WINDOWPLACEMENT wndPlacementInfo;
	GetWindowPlacement( to.GetWindowHandle(), &wndPlacementInfo );
	
	// And assign to 'from' window
	SetWindowPlacement( from.GetWindowHandle(), &wndPlacementInfo );

	// Also Change window style 
	DWORD dwStyle = GetWindowLongPtrW( to.GetWindowHandle( ), GWL_STYLE );
	SetWindowLongPtrW( from.GetWindowHandle( ), GWL_STYLE, dwStyle );

	DWORD dwExStyle = GetWindowLongPtrW( to.GetWindowHandle( ), GWL_EXSTYLE );
	SetWindowLongPtrW( from.GetWindowHandle( ), GWL_EXSTYLE, dwExStyle );

	// If you have changed window data using SetWindowLong, you must call
	// SetWindowPos for the changes to take effect.
	// Use the following combination for uFlags: SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED. 
	SetWindowPos( from.GetWindowHandle(), nullptr, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
}

bool HasSystemMenu( /*IN*/ const WindowsPlatformWindow& window )
{
	DWORD dwStyle = ::GetWindowLongPtrW( window.GetWindowHandle(), GWL_STYLE );
	return ( dwStyle & WS_CAPTION ) != 0 && ( dwStyle & WS_SYSMENU ) != 0;
}

bool IsWindowSizable( /*IN*/ const WindowsPlatformWindow& window )
{
	DWORD dwStyle = ::GetWindowLongPtrW( window.GetWindowHandle(), GWL_STYLE );
	DWORD dwExStyle = ::GetWindowLongPtrW( window.GetWindowHandle( ), GWL_EXSTYLE );

	return (( dwStyle & WS_THICKFRAME ) != 0 ) && !(( dwExStyle & WS_EX_DLGMODALFRAME ) != 0 );
}


} /*namespace tgon*/