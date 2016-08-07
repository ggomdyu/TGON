#include "PrecompiledHeader.h"
#include "AbstractGraphicsDevice.h"

#include "../../../Platform/Window/TWindow.h"


tgon::AbstractGraphicsDevice::AbstractGraphicsDevice( TWindow* deviceWindow ) :
	m_deviceWindow( deviceWindow ),
//	m_currMode( TCullMode::kNone ),
	m_clearColor( 0x000000 )
{
}
