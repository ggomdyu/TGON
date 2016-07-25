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
	template <typename Ty, typename... _Args>
	static void Write( Ty&& arg, const _Args&... args )
	{
		ConsoleImpl::Write( std::forward<Ty>( arg ));
		Write( args... );
	}

	static void Write( )
	{
	}


	// WriteLine
	template <typename Ty, typename... _Args>
	static void WriteLine( Ty&& arg, const _Args&... args )
	{
		ConsoleImpl::Write( std::forward<Ty>( arg ));
		WriteLine( args... );
	}

	static void WriteLine( )
	{
		ConsoleImpl::Write( L"\n" );
	}

};


}
