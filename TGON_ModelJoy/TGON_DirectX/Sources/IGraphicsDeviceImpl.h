#pragma once
#include "GraphicsDeviceMisc.h"

namespace tgon
{


class IGraphicsDeviceImpl
{
public:
	IGraphicsDeviceImpl( ) {};
	virtual				~IGraphicsDeviceImpl( ) = 0 {};

	virtual bool		Setup( GraphicsDeviceCreateParam gd ) = 0;
	virtual void		Display( ) = 0;
};


}