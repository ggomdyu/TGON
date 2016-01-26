#pragma once
#include "tgGraphicsDevice.h"


namespace tgon {


class IQuad
{
public:
	explicit	IQuad( tgGraphicsDevice& gd ) : m_gd( gd )	{}
	virtual		~IQuad( )		{}

	virtual void		Draw( ) = 0;

protected:
	tgGraphicsDevice&	GetGraphicsDevice( )	{ return m_gd; }

private:
	tgGraphicsDevice&	m_gd;
};


}