#include "PrecompiledHeader.h"
#include "AbstractGraphics.h"

#include "../../../Platform/Window/TWindow.h"


tgon::AbstractGraphics::AbstractGraphics( TWindow* deviceWindow ) :
	m_deviceWindow( deviceWindow ),
//	m_currMode( TCullMode::kNone ),
	m_clearColor( 0x000000 )
{
}
