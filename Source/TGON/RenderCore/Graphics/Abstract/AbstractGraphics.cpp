#include "PrecompiledHeader.h"
#include "AbstractGraphics.h"

#include "../../../Platform/Window/TWindow.h"


tgon::AbstractGraphics::AbstractGraphics( TWindow* deviceWindow, bool isWindowed ) :
	m_deviceWindow( deviceWindow ),
	m_isWindowed( isWindowed ),
//	m_currMode( TCullMode::kNone ),
	m_clearColor( 0x000000 )
{
}
