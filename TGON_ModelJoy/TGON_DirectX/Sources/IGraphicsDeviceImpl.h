#pragma once
#include "GraphicsDeviceMisc.h"

namespace tgon
{


class IGraphicsDeviceImpl
{
public:
	IGraphicsDeviceImpl( ) {};
	virtual				~IGraphicsDeviceImpl( ) = 0 {};

	virtual bool		Setup( const GraphicsDeviceCreateParam& ) = 0;
	virtual void		Display( ) = 0;
};


}