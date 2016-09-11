/*
* Author : Cha Junho
* Date : 01/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Abstract/APlatformConsole.h"

#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	undef WIN32_LEAN_AND_MEAN
#endif


namespace tgon
{


class WindowsConsole;
using ConsoleImpl = WindowsConsole;

class TGON_API WindowsConsole : 
	public IConsole
{
	/*
		Commands
	*/
public:
	//
	// @note Write char* string to console.
	// @param str String that you want to write to console
	//
	virtual void Write( /*In*/ const char* str ) override;

	//
	// @note Write wchar_t* string to console.
	// @param str String that you want to write to console
	//
	virtual void Write( /*In*/ const wchar_t* str ) override;


	/*
		Ctor/Dtor
	*/
protected:
	WindowsConsole( );

	WindowsConsole( /*In*/ const WindowsConsole& ) = delete;

	virtual ~WindowsConsole( );


	/*
		Operators
	*/
	WindowsConsole& operator=( /*In*/ const WindowsConsole& ) = delete;


	/*
		Internal works
	*/
private:
	void SetupConsole( );


	/*
		Private variables
	*/
private:
	HANDLE m_outputHandle;
};


} /*namespace tgon*/