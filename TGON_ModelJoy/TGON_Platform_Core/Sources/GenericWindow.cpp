#include "stdafx.h"
#include "GenericWindow.h"


tgon::GenericWindow::GenericWindow( const WindowStyle& wndStyle ) :
		m_wndStyle( wndStyle )
{
}


tgon::GenericWindow::~GenericWindow( )
{
}


void tgon::GenericWindow::RegisterEventCallback( const uint32_t targetEvent, const WorkProc& doWork )
{
	m_eventWorkList.insert( std::make_pair( targetEvent, doWork ));
}