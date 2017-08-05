#include "PrecompiledHeader.pch"
#include "Engine.h"

#include "GameApplication.h"

#include "Module/InputModule.h"
#include "Module/TimeModule.h"

namespace tgon
{

std::shared_ptr<GameApplication> MakeGameApplication( );

Engine::Engine( ) :
	m_gameApplication( MakeGameApplication( ))
{
	this->AddEssentialModules( );
}

void Engine::AddEssentialModules( )
{
    This::AddModule<TimeModule>( );

	//This::AddModule( std::make_shared<TInputModule>( this->GetWindow( ), 
	//	TInputModule::kMouse | TInputModule::kKeyboard )
	//);
}

int32_t Engine::Execute( int argc, char** argv )
{
	const std::shared_ptr<platform::Window>& window = m_gameApplication->GetRootWindow( );
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

            ModuleContext::GetModule<TimeModule>( )->Update( );

			if ( !window->PumpEvent( ))
			{
				this->UpdateModules( );
				m_gameApplication->OnUpdate( );
			}
		}
	}

	return 0;
}

void Engine::UpdateModules( )
{
    for ( auto module : m_modulesForFastIter )
    {
        module->Update( );
    }
}

} /* namespace tgon */
