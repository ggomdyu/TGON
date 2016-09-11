#include "PrecompiledHeader.h"
#include "TGraphicsDevice.h"

#include "../../Core/Platform/OSAL/PlatformWindow.h"



namespace tgon {


TGraphicsDevice::TGraphicsDevice( TPlatformWindow* deviceWindow, const GraphicsProperty& grpProp ) :
	GraphicsDeviceImpl( deviceWindow, grpProp )
{
}

}