/*
* Author : Cha Junho
* Date : 01/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Interface/InterfaceConsole.h"

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
	public InterfaceConsole
{
/*
	Commands
*/
public:
	//
	// Write char* string to console.
	//
	// @param str String that you want to write to console
	//
	virtual void Write( /*In*/ const char* str ) override;

	//
	// Write wchar_t* string to console.
	//
	// @param str String that you want to write to console
	//
	virtual void Write( /*In*/ const wchar_t* str ) override;


/*
	Cons/Destructor
*/
protected:
	//
	// Constructor
	//
	WindowsConsole( );

	//
	// Destructor
	//
	virtual ~WindowsConsole( );


public:
	//
	// Copy constructor
	//
	WindowsConsole( /*In*/ const WindowsConsole& ) = delete;


/*
	Operators
*/
	//
	// Copy assignment operator
	//
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


}