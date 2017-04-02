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


#pragma once
#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <windows.h>


namespace tgon
{


/*
 * @note					Convert WindowStyle to DWORD.
 * @param	normalWndStyle	Normal window style ( e.g. WS_... )
 * @param	exWndStyle		Extended window style ( e.g. WS_EX_... )
*/
void ConvertWindowStyleToDword( _In_ const struct WindowStyle& wndStyle, 
								_Out_ DWORD* exWndStyle, 
								_Out_ DWORD* normalWndStyle );

/*
 * @note					Create window by forwarded arguments
 * @param	wndStyle		Window style which described about form
 * @param	className		Window class name which registered via RegisterClass ( You can forward defaultly WindowsPlatformApplication::AppClassName )
 * @param	instanceHandle	Process identifier ( You can forward defaultly WindowsPlatformApplication::InstanceHandle )
 * @param	extraParam		Extra data for window
*/
HWND CreateWindowForm( _In_ const struct WindowStyle& wndStyle,
					   _In_ const wchar_t* className,
					   _In_ HINSTANCE instanceHandle,
					   _In_opt_ void* extraParam = nullptr );

/*
 * @note			Copy and paste window placement information ( e.g. Position, Size, Window style )
 * @param	from	Paste target
 * @param	to		Destination of copied target
*/
void ReshapeWindowForm( _In_ const class WindowsWindowFrame& from, 
						_In_ const class WindowsWindowFrame& to );

/*
 * @return	Return true if the window has system menu.
*/
bool HasSystemMenu( const class WindowsWindowFrame& window );

/*
 * @return	Return true if the window is sizeable.
*/
bool IsWindowSizable( const class WindowsWindowFrame& window );


} /* namespace tgon */
