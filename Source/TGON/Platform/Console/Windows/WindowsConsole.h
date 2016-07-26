/*
* Author : Cha Junho
* Date : 01/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Interface/IConsole.h"


#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	undef WIN32_LEAN_AND_MEAN
#endif


namespace tgon
{


using ConsoleImpl = class WindowsConsole;

class TGON_API WindowsConsole : 
	public IConsole
{
public:
	/*
		Commands
	*/
	virtual void Write( _In_ const char* str ) override;

	virtual void Write( _In_ const wchar_t* str ) override;


protected:
	/*
		Cons/Destructor
	*/
	WindowsConsole( );

	virtual ~WindowsConsole( );
	
private:
	HANDLE m_outputHandle;
};


}