#include "PrecompiledHeader.h"
#include "TEngine.h"

#include "TGameBody.h"
#include "../../Platform/Window/Abstract/AbstractWindowEventHandler.h"
#include "../../Platform/Application/TApplication.h"

#include "../../Engine/Module/InputModule.h"
#include "../../Engine/Module/TimeModule.h"
#include "../Object/TCoreEvents.h"

std::shared_ptr<tgon::TGameApplication> GenerateGameApplication( );

class EngineWindowEventHandler :
	public tgon::AbstractWindowEventHandler
{
public:
	virtual bool OnDestroy( )
	{
		return MessageBox( NULL, L"Are you sure you want to quit?", L"WARNING!", MB_YESNO ) == IDYES;
	}


	/*
		Cons/Destructor
	*/
public:
	//
	// Constructor
	//	
	EngineWindowEventHandler( ) = default;

	//
	// Destructor
	//
	virtual ~EngineWindowEventHandler( ) = default;
};


tgon::TEngine::TEngine( ) :
	m_gameApp( GenerateGameApplication( ))
{
	//this->SubscribeEvent<E_DESTROY>( &TEngine::WowCPAR );
}

void tgon::TEngine::AddModule( const std::shared_ptr<IModule>& module )
{
	auto iter = m_modules.find( module->GetHashCode( ));
	
	// Check duplication of module
	if ( iter == m_modules.end( ))
	{
		m_modules.insert({ module->GetHashCode( ), module });
		m_modulesForUpdate.push_back( module );
	}
	else
	{
		assert( false && "m_modules already has module you added!" );
	}
}


void tgon::TEngine::SetupModules( )
{
	//AddModule( std::make_shared<TInputModule>( this->GetWindow( ), 
	//	TInputModule::kMouse | TInputModule::kKeyboard )
	//);
}


int32_t tgon::TEngine::Execute( int argc, char** argv )
{
	//auto window = std::make_shared<TWindow>( WindowStyle::DefaultStyle );
	//window->SetEventHandler( std::make_shared<EngineWindowEventHandler>() );
	//
	//// Register event handler.
	//while ( !window->IsDestroyed( ))
	//{
	//	if ( m_gameApp->IsPaused( ))
	//	{
	//		continue;
	//	}
	//
	//	// Idle time
	//	if ( !window->PumpEvent( ))
	//	{
	//		//this->NotifyEvent( TEvent::OnUpdateBegin );
	//		m_gameApp->Update( );
	//		//this->NotifyEvent( TEvent::OnUpdateEnd );
	//	}
	//
	//}
	//
	this->NotifyEvent<E_DESTROY>( );

	return int32_t( );
}