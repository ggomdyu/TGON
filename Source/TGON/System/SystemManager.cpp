#include "PrecompiledHeader.h"
#include "SystemManager.h"

#include "../Platform/Console/TConsole.h"


tgon::SystemManager::SystemManager( )
{
	TLog( L"[CREATED] tgon::SystemManager" );
}

tgon::SystemManager::~SystemManager( )
{
	TLog( L"[DESTROYED] tgon::SystemManager" );
}
