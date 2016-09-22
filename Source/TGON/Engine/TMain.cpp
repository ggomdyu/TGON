#include "PrecompiledHeader.h"
#include "../Core/Platform/TMain.h"

#include "../Core/Platform/OSAL/PlatformApplication.h"
#include "../Engine/Engine.h"


namespace tgon
{


int32_t TMain( int32_t argc, char** argv )
{
	// Singleton on demand
	{
		tgon::TApplication::Get( );
		//tgon::TPlatformConsole::Get( );
	}

	// Start loop engine
	{
		Engine engineLoop;
		
		const int32_t errCode = engineLoop.Execute( argc, argv );
	}
	return 0;
}


} /*namespace tgon*/