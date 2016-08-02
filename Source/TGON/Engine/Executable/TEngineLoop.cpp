#include "PrecompiledHeader.h"
#include "TEngineLoop.h"

#include "TGameBody.h"
#include "../../Platform/Window/Abstract/AbstractWindowEventHandler.h"
#include "../../Platform/Application/TApplication.h"


std::shared_ptr<tgon::TGameBody> GenerateGameBody( );


namespace tgon
{
	class EngineWindowEventHandler :
		public AbstractWindowEventHandler,
		public TEventSubject
	{
	public:
		TGON_OBJECT( EngineWindowEventHandler, TEventSubject )

		/*
			Cons/Destructor
		*/
		EngineWindowEventHandler( ) {}

		virtual ~EngineWindowEventHandler( ) {}

		/*
			Event handler
		*/
		virtual bool OnDestroy( )
		{ 
			this->NotifyEvent( TEvent::OnDestroy );
			return true;
		}
	};
}

tgon::TEngineLoop::TEngineLoop( ) :
	m_gameBody( GenerateGameBody( )),
	m_isGameDone( false )
{
	this->SubscribeEvent( TEvent::OnDestroy, &TEngineLoop::OnDestroy );
}

int32_t tgon::TEngineLoop::Execute( int argc, char** argv )
{
	// Make custom event handler.
	auto customEventHandler = std::make_shared<EngineWindowEventHandler>( );

	// Register event handler.
	SpTWindow window = m_gameBody->GetWindow( );
	window->SetEventHandler( customEventHandler );


	while ( !m_isGameDone )
	{
		// Idle time
		if ( !window->PumpEvent( ))
		{
			NotifyEvent( TEvent::OnUpdateBegin );
			m_gameBody->Update( );
			NotifyEvent( TEvent::OnUpdateEnd );

			NotifyEvent( TEvent::OnRenderBegin );
			m_gameBody->Render( );
			NotifyEvent( TEvent::OnRenderEnd );
		}
	}


	
	return int32_t( );
}