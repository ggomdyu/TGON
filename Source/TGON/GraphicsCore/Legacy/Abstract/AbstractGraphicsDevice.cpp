#include "PrecompiledHeader.h"
#include "AbstractGraphicsDevice.h"

#include "../../../Core/Platform/OSAL/PlatformWindow.h"



namespace tgon {


AbstractGraphicsDevice::AbstractGraphicsDevice( TPlatformWindow* deviceWindow ) :
	m_deviceWindow( deviceWindow ),
//	m_currMode( TCullMode::kNone ),
	m_clearColor( 0x000000 )
{
}


}
