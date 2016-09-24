#include "PrecompiledHeader.h"
#include "Engine.h"

#include "GameApplication.h"
#include "../Core/Platform/PlatformApplication.h"
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
	const std::shared_ptr<TPlatformWindow>& window = m_gameApplication->GetRootWindow( );
	if ( window.get( ) )
	{
		// Loop for window event( =messsage )
		while ( !window->IsClosed( ))
		{
			// If engine was paused, then ignore update. -> Needs optimization
			//if ( m_gameApplication->IsPaused( ))
			//{
			//	continue;
			//}

			if ( !window->PumpEvent( ))
			{
				this->UpdateModules( );
				m_gameApplication->OnUpdate( );
			}
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