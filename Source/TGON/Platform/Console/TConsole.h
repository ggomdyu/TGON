/*
* Author : Junho-Cha
* Date : 03/22/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Platform/Slate/PlatformConsole.h"
#include "../../Core/TSingleton.h"


namespace tgon
{


using TConsole = ConsoleImpl;


inline void TLog( )
{
}

template <typename Arg, typename ...Args>
void TLog( const Arg& arg, 
		   const Args&... args )
{
#if defined( DEBUG ) || defined( _DEBUG )
	TConsole::Get( )->Write( arg );
	TLog( args... );
#endif
}


}