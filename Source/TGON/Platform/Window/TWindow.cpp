#include "PrecompiledHeader.h"
#include "TWindow.h"

#include "WindowStyle.h"


tgon::TWindow::TWindow( const WindowStyle& wndStyle ) :
	WindowsWindow( wndStyle )
{
	this->LazyInitialization( );
}

tgon::TWindow::~TWindow( )
{
}