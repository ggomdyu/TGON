#include "PrecompiledHeader.h"
#include "TConsole.h"


tgon::TConsole::TConsole( )
{
	this->WriteLine( "[CREATED] tgon::TConsole" );
}

tgon::TConsole::~TConsole( )
{
#if defined( DEBUG ) | defined( _DEBUG )
	this->WriteLine( "The console will be closed within a second." );
	
	uint64_t bigLoopIndex = 0;
	while ( ++bigLoopIndex != 1000000000 ) {}

#endif
	this->WriteLine( "[DESTROYED] tgon::TConsole" );
}