#include "stdafx.h"
#include "GenericWindow.h"

NSBEGIN( tgon );
GenericWindow::GenericWindow( const WindowStyle& ws ) :
		m_ws( ws ), m_nMsgType( 0 )
{
}

GenericWindow::~GenericWindow( )
{
}

const WindowStyle& GenericWindow::GetWindowStyle( ) const
{
	return m_ws;
}

void GenericWindow::SetCurrentMessage( const uint32_t uMsg )
{
	m_nMsgType = uMsg;
}

uint32_t GenericWindow::GetCurrentMessage( ) const
{
	return m_nMsgType;
}
NSEND( );