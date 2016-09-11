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
	// Gets
	// 
public:
	/*
	 * @note	Singleton interface for this class
	 * @return	Return instance reference of this class
	*/
	static WindowsPlatformConsole& Get( )
	{
		static WindowsPlatformConsole instance;
		return instance;
	}

	// 
	// Internal works
	// 
private:
	/*
	 * @note			Write string to console.
	 * @param	str		String which you want to write to console
	*/
	void WriteImpl( /*In*/ const char* str );
	void WriteImpl( /*In*/ const wchar_t* str );

	// 
	// Ctor/Dtor
	// 
protected:
	WindowsPlatformConsole( );
	virtual ~WindowsPlatformConsole( );

	// 
	// Operators
	// 
	WindowsPlatformConsole& operator=( /*In*/ const WindowsPlatformConsole& ) = delete;

	// 
	// Internal works
	// 
private:
	void SetupConsole( );

	// 
	// Private variables
	// 
private:
	HANDLE m_outputHandle;
};


using TPlatformConsole = WindowsPlatformConsole;


} /*namespace tgon*/