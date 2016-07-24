#include "PrecompiledHeader.h"
#include "AbstractWindow.h"


#include "AbstractWindowEventHandler.h"


tgon::AbstractWindow::AbstractWindow( ) :
	m_eventListener( new AbstractWindowEventHandler )
{
}

tgon::AbstractWindow::~AbstractWindow( )
{
}
