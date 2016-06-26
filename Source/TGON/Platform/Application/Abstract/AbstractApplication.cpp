#include "PrecompiledHeader.h"
#include "AbstractApplication.h"


tgon::AbstractApplication::AbstractApplication( 
	const WindowStyle& rootWndStyle ) :
	
	m_rootWndStyle( rootWndStyle )
{
}


tgon::AbstractApplication::~AbstractApplication( )
{
}

void tgon::AbstractApplication::SetupWindowComponents( )
{
	m_window = TWindow::Make( m_rootWndStyle, this );
}
