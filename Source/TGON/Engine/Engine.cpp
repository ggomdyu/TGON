#include "PrecompiledHeader.h"
#include "Engine.h"

#include "GameApplication.h"
#include "../Core/Platform/Abstract/APlatformWindowEventHandler.h"
#include "../Core/Platform/TApplication.h"
#include "Module/InputModule.h"
#include "CoreEvents.h"


namespace tgon
{

std::shared_ptr<GameApplication> GenerateGameApplication( );

Engine::Engine( ) :
	m_gameApplication( GenerateGameApplication( ))
{
	//this->SubscribeEvent<E_MODULEADDED>( &This::OnModuleAdded );

	this->AddDefaultModulesToRepo( );
}


void Engine::AddDefaultModulesToRepo( )
{
	//AddModule( std::make_shared<TInputModule>( this->GetWindow( ), 
	//	TInputModule::kMouse | TInputModule::kKeyboard )
	//);
}


int32_t Engine::Execute( int argc, char** argv )
{
	// Register event handler to window.
	const std::shared_ptr<TPlatformWindow>& window = m_gameApplication->GetRootWindow( );
	

	// Loop for window event( =messsage )
	while ( !window->IsClosed( ))
	{
		// If engine was paused, then ignore update.
		if ( m_gameApplication->IsPaused( ))
		{
			continue;
		}
	
		if ( !window->PumpEvent( ))
		{
			this->FrameMoveModules( );

			m_gameApplication->Update( );
		}
	}
	

	this->NotifyEvent<E_DESTROY>( );
	return 0;
}

void tgon::Engine::OnModuleAdded( IModule* module )
{
	m_modulesForFastIter.push_back( module );
}


} /*namespace tgon*/