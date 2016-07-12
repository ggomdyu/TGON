#include "TGraphics.h"
#include "PrecompiledHeader.h"
#include "TGraphics.h"


tgon::TGraphics::TGraphics( const TWindow& owner ) :
	GraphicsImpl( owner )
{
}

tgon::TGraphics::TGraphics( const SpTWindow& owner ) :
	GraphicsImpl( *owner.get( ))
{
}
