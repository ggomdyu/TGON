/*
* Author : Cha Junho
* Date : 01/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Abstract/APlatformConsole.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>


namespace tgon
{


class TGON_API WindowsPlatformConsole : 
	public APlatformConsole<WindowsPlatformConsole>
{
	friend APlatformConsole<WindowsPlatformConsole>;

	// 
	// Internal works
	// 
private:
	/*
	 * @note			Write string to console.
	 * @param	str		String which you want to write to console
	*/
	static void WriteImpl( /*In*/ const char* str ) /*override*/;
	static void WriteImpl( /*In*/ const wchar_t* str ) /*override*/;

	// 
	// Ctor/Dtor
	// 
public:
	WindowsPlatformConsole( ) = delete;
	virtual ~WindowsPlatformConsole( ) = delete;
};


using TPlatformConsole = WindowsPlatformConsole;


} /*namespace tgon*/