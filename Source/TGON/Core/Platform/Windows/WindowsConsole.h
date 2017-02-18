/*
 * author   ggomdyu
 * since    01/24/2016


*/

#pragma once
#include "../Generic/GenericConsole.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>


namespace tgon
{


class TGON_API WindowsConsole : 
	public GenericConsole<WindowsConsole>
{
	friend GenericConsole<WindowsConsole>;

	/* 
	 * Ctor/Dtor
	*/ 
public:
	WindowsConsole( ) = delete;
	~WindowsConsole( ) = delete;
	
	/* 
	 * Internal works
	*/ 
private:
	/*
	 * @note			Write string to console.
	 * @param	str		String which you want to write to console
	*/
	static void WriteImpl( /*In*/ const char* str ) /*override*/;
	static void WriteImpl( /*In*/ const wchar_t* str ) /*override*/;
};


using Console = WindowsConsole;


} /*namespace tgon*/