/*
* Author : Junho-Cha
* Date : 03/22/2016
* Latest author :
* Latest date :
* Description : Polymorphic console type
*/

#pragma once
#include "../Platform/PlatformConsole.h"
#include "../Core/TSingleton.h"


namespace tgon
{

class TGON_API TConsole : public ConsoleImpl
{
public:
	TGON_OBJECT( TConsole, ConsoleImpl )
	TGON_SINGLETON( TConsole )

private:
	TConsole( );
	virtual ~TConsole( );
};

template <typename ...Args>
inline void TLOG( const Args& ...args ) 
{
#if defined( DEBUG ) || defined( _DEBUG )
	TConsole::Get( )->WriteLine( args... );
#endif
}


}