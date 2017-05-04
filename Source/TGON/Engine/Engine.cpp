#include "PrecompiledHeader.h"
#include "Engine.h"

#include "GameApplication.h"

#include "Module/InputModule.h"
#include "Module/TimeModule.h"

namespace tgon
{

std::shared_ptr<GameApplication> MakeGameApplication( );

TEngine::TEngine( ) :
	m_gameApplication( MakeGameApplication( ))
{
	this->AddEssentialModules( );
}

void TEngine::AddEssentialModules( )
{
    This::AddModule<TimeModule>( );

	//This::AddModule( std::make_shared<TInputModule>( this->GetWindow( ), 
	//	TInputModule::kMouse | TInputModule::kKeyboard )
	//);
}

int32_t TEngine::Execute( int argc, char** argv )
{
	const std::shared_ptr<window::TWindow>& window = m_gameApplication->GetRootWindow( );
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
	

//	this->NotifyEvent<E_DESTROY>( );
	return 0;
}

void TEngine::UpdateModules( )
{
    for ( auto module : m_modulesForFastIter )
    {
        module->Update( );
    }
}

} /* namespace tgon */
