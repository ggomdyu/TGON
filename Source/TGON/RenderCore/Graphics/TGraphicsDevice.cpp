#include "PrecompiledHeader.h"
#include "TGraphicsDevice.h"

#include "../../Platform/Window/TWindow.h"


tgon::TGraphicsDevice::TGraphicsDevice( TWindow* deviceWindow, const GraphicsProperty& grpProp ) :
	GraphicsDeviceImpl( deviceWindow, grpProp )
{
}