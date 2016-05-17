/*
* Author : Junho-Cha
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace tgon
{
	// Transform WindowStyle struct to DWORD type. 
	// Find out what cannot be selected both flags, and invoke assert.
	void Convert_wndstyle_to_dword(
		const struct WindowStyle&,
		_Out_ DWORD* exWndStyle,
		_Out_ DWORD* normalWndStyle
	);

	// This function changes these states : Position, Size, Window style
	void ReshapeWindowForm(
		const class WindowsWindow& from,
		const class WindowsWindow& to 
	);
}