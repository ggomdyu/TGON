/*
* Author : Junho-Cha
* Date : 03/22/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Platform/Slate/PlatformConsole.h"


namespace tgon
{


using TConsole = ConsoleImpl;

template <typename Arg, typename ...Args>
void TLog( 
	/*IN*/ const Arg& arg, 
	/*IN*/ const Args&... args )
{
#if defined( DEBUG ) || defined( _DEBUG )
	TConsole::Write( arg );
	TLog( args... );
#endif
}

inline void TLog( )
{
}


}