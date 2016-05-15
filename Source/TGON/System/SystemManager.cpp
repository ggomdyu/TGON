#include "PrecompiledHeader.h"
#include "SceneSystem.h"
#include "SystemManager.h"

#include "../Console/TConsole.h"


tgon::SystemManager::SystemManager( )
{
	TLOG( "[CREATED] tgon::SystemManager" );
}

tgon::SystemManager::~SystemManager( )
{
	TLOG( "[DESTROYED] tgon::SystemManager" );
}
