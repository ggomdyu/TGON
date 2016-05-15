/*
* Author : Junho-Cha
* Date : 01/24/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Interface/IConsole.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace tgon
{


class WindowsConsole;
typedef WindowsConsole ConsoleImpl;
	
class TGON_API WindowsConsole : private IConsole
{
public:
	TGON_OBJECT( WindowsConsole, IConsole )

	/*
		@ Commands
	*/
	template <typename T, typename ...Args>
	void Write( const T& arg, const Args& ...args );
	
	template <typename T, typename ...Args>
	void WriteLine( const T& arg, const Args& ...args );

	/*
		@ Internal works
	*/
private:
	virtual void Write( ) override;
	virtual void WriteLine( ) override;

	/*
		@ Cons/Destructor
	*/
protected:
	WindowsConsole( );
	virtual ~WindowsConsole( );


private:
	HANDLE m_outputHandle;
};


template <typename T, typename ...Args>
void tgon::WindowsConsole::WriteLine(
	const T& arg,
	const Args& ...args ) 
{
	this->FillBuffer( arg );
	this->WriteLine( args... );
}


template<typename T, typename ...Args>
inline void WindowsConsole::Write(
	const T& arg,
	const Args& ...args )
{
	this->FillBuffer( arg );
	this->Write( args... );
}



}