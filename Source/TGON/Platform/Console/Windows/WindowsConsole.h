/*
* Author : Junho-Cha
* Date : 01/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Interface/IConsole.h"
#include "../Core/TSingleton.h"

#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace tgon
{


class WindowsConsole;
using ConsoleImpl = WindowsConsole;

class TGON_API WindowsConsole : 
	private IConsole,
	public TSingleton<WindowsConsole>
{
public:
	/*
		Commands
	*/
	virtual void Write( const wchar_t* str ) override;
	virtual void Write( const char* str ) override;


protected:
	WindowsConsole( );
	virtual ~WindowsConsole( );

private:
	HANDLE m_outputHandle;
};



}