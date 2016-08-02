/*
* Author : Cha Junho
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once
#include <windows.h>


namespace tgon
{


struct WindowStyle;
class WindowsWindow;
	
// Convert WindowStyle to DWORD.
void ConvertWindowStyleToDword( IN const WindowStyle&, OUT DWORD* exWndStyle, OUT DWORD* normalWndStyle );

// This function changes window states : Position, Size, Window style
void ReshapeWindowForm( const WindowsWindow& from, const WindowsWindow& to );


}