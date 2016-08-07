#include "PrecompiledHeader.h"
#include "AbstractWindow.h"


#include "AbstractWindowEventHandler.h"


tgon::AbstractWindow::AbstractWindow( ) :
	m_eventListener( new AbstractWindowEventHandler ),
	m_destroyed( false )
{
}

tgon::AbstractWindow::~AbstractWindow( )
{
	m_destroyed = true;
}