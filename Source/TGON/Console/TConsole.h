/*
* Author : Junho-Cha
* Date : 2016-03-22
* Latest author :
* Latest date :
* Description : Polymorphic console type
*/

#pragma once
#include "../Config/Platform/PlatformConsole.h"
#include <string>


namespace tgon
{


class TConsole : public ConsoleImpl
{
public:
	// Singleton
	static TConsole* Get( ) 
	{
		static TConsole consInst;
		return &consInst;
	}

private:
	TConsole( ) {}
	virtual ~TConsole( ) {}
};


template <typename ...Args>
TGON_FORCEINLINE void TLOG( const Args& ...args ) 
{
	TConsole::Get( )->WriteLine( args... );
}


}