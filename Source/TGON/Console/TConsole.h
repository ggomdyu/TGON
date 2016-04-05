/*
* Author : 차준호
* Date : 2016-03-22
* 최종 수정 :
* 최종 수정일 :
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