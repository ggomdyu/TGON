#include "PrecompiledHeader.h"
#include "TGameBody.h"


tgon::TGameBody::TGameBody( const WindowStyle& wndStyle ) :
	m_isGameDone( false ),
	m_window( TWindow::Make( wndStyle ))
{
}

tgon::TGameBody::~TGameBody( )
{
}

void tgon::TGameBody::Update( )
{
	NotifyEvent( TEvent::OnUpdateBegin );


	NotifyEvent( TEvent::OnUpdateEnd );

}

void tgon::TGameBody::Render( )
{
	m_graphics->Clear( );
	m_graphics->BeginScene( );
	NotifyEvent( TEvent::OnRenderBegin );


	m_graphics->EndScene( );
	m_graphics->Present( );
	NotifyEvent( TEvent::OnRenderEnd );
}

void tgon::TGameBody::InitializeModule( )
{
	//TimeModule;
	//InputModule;
}