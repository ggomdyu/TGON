#include "stdafx.h"
#include "GenericWindow.h"


tgon::GenericWindow::GenericWindow( const WindowStyle& wndStyle ) :
		m_wndStyle( wndStyle )
{
}


tgon::GenericWindow::~GenericWindow( )
{
}


void tgon::GenericWindow::AddWindowEventCallback( const uint32_t evType, const EventProc& evProc )
{
	m_evMap.insert( std::make_pair( evType, evProc ));
}

const tgon::GenericWindow::EventProcMap& tgon::GenericWindow::GetEventMap( )
{
	return m_evMap;
}

void tgon::GenericWindow::CallWindowEventProc( const uint32_t evType )
{
	const auto evProc = this->GetEventMap( ).find( evType );

	if ( evProc != this->GetEventMap( ).end( ))
	{
		evProc->second( );
	}
}

