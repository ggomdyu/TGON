/*
* Author : Junho-Cha
* Date : 2016-01-24
* Latest author :
* Latest date :
*/

#pragma once
#include "../Layered/LayeredConsole.h"
#include "../../Config/Compiler/SyntaxCompatible.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace tgon
{


class WindowsConsole;
typedef WindowsConsole ConsoleImpl;
	
class WindowsConsole : private LayeredConsole
{
protected:
	WindowsConsole( );
	virtual ~WindowsConsole( );

public:
	template <typename T, typename ...Args>
	void WriteLine( const T& arg, const Args& ...args );

	using LayeredConsole::SetFlashOnLogging;
	using LayeredConsole::IsFlashOnLogging;
	HANDLE GetOutputHandle( ) const;

private:
	virtual void WriteLine( ) override;

private:
	HANDLE m_outputHandle;
};


}


template <typename T, typename ...Args>
void tgon::WindowsConsole::WriteLine( const T& arg, const Args& ...args ) 
{
	this->FillBuffer( arg );
	this->WriteLine( args... );
}

TGON_FORCEINLINE HANDLE tgon::WindowsConsole::GetOutputHandle( ) const
{
	return m_outputHandle;
}