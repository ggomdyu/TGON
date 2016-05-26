#include "PrecompiledHeader.h"
#include "AbstractWindow.h"


tgon::AbstractWindow::AbstractWindow( 
	const WindowStyle& wndStyle,
	bool isEventHandleable ) :
	m_wndStyle( wndStyle ),
	m_isEventHandleable( isEventHandleable )
{
}

tgon::AbstractWindow::~AbstractWindow( )
{
}
