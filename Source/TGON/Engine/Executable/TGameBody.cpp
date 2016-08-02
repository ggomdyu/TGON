#include "PrecompiledHeader.h"
#include "TGameBody.h"


tgon::TGameBody::TGameBody( const WindowStyle& wndStyle ) :
	m_isGameDone( false ),
	m_window( std::make_shared<TWindow>( wndStyle )),
	m_graphics( TGraphics::Make( m_window.get(), true ))
{
}

tgon::TGameBody::~TGameBody( )
{
}

void tgon::TGameBody::Update( )
{



}

void tgon::TGameBody::Render( )
{
	m_graphics->Clear( );
	m_graphics->BeginScene( );


	m_graphics->EndScene( );
	m_graphics->Present( );
}

void tgon::TGameBody::InitializeModule( )
{
	//TimeModule;
	//InputModule;
}