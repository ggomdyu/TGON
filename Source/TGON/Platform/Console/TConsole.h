/*
* Author : Cha Junho
* Date : 03/22/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Slate/PlatformConsole.h"


namespace tgon
{


class TGON_API TConsole :
	public ConsoleImpl
{
public:
	/*
		Cons/Destructor
	*/
	TConsole( ) = delete;

	virtual ~TConsole( ) = delete;
	

public:
	/*
		Commands
	*/
	// Write
	template <typename _Ty, typename... _Args>
	static void Write( _Ty&& arg, const _Args&... args )
	{
		ConsoleImpl::Write( std::forward<_Ty>( arg ));
		Write( args... );
	}

	static void Write( )
	{
	}


	// WriteLine
	template <typename _Ty, typename... _Args>
	static void WriteLine( _Ty&& arg, const _Args&... args )
	{
		ConsoleImpl::Write( std::forward<_Ty>( arg ));
		WriteLine( args... );
	}

	static void WriteLine( )
	{
		ConsoleImpl::Write( L"\n" );
	}

};


}
