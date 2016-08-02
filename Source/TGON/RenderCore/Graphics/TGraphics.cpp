#include "PrecompiledHeader.h"
#include "TGraphics.h"

#include "../../Platform/Window/TWindow.h"


tgon::TGraphics::TGraphics( TWindow* owner, bool isWindowed ) :
	GraphicsImpl( owner, isWindowed )
{
}