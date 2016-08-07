#include "PrecompiledHeader.h"
#include "TEngine.h"

#include "TGameBody.h"
#include "../../Platform/Window/Abstract/AbstractWindowEventHandler.h"
#include "../../Platform/Application/TApplication.h"


std::shared_ptr<tgon::TGameBody> GenerateGameBody( );

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
	m_mainGameBody( GenerateGameBody( ))
{
}

int32_t tgon::TEngine::Execute( int argc, char** argv )
{
	TWindow* window = m_mainGameBody->GetWindow( );
	window->SetEventHandler( std::make_shared<EngineWindowEventHandler>() );

	// Register event handler.
	while ( !window->IsDestroyed( ))
	{
		if ( m_mainGameBody->IsPaused( ))
		{
			continue;
		}

		// Idle time
		if ( !window->PumpEvent( ))
		{
			//this->NotifyEvent( TEvent::OnUpdateBegin );
			m_mainGameBody->FrameUpdate( );
			//this->NotifyEvent( TEvent::OnUpdateEnd );
		}

	}

	this->NotifyEvent( TEventType( "OnDestroy" ) );


	return int32_t( );
}