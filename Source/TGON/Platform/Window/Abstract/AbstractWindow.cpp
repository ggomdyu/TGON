#include "PrecompiledHeader.h"
#include "AbstractWindow.h"


tgon::AbstractWindow::AbstractWindow( 
	const WindowStyle& wndStyle,
	AbstractWindowDelegate* wndDelegate ) :

	m_wndStyle( wndStyle ),
	m_wndDelegate( wndDelegate )
{
}

tgon::AbstractWindow::~AbstractWindow( )
{
}
