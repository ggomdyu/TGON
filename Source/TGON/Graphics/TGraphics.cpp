#include "TGraphics.h"
#include "PrecompiledHeader.h"
#include "TGraphics.h"


tgon::TGraphics::TGraphics(
	const SpTWindow& window,
	const GraphicsStyle& gdcp ) : 
	GraphicsImpl( window, gdcp )
{
}

tgon::TGraphics::~TGraphics( )
{
}