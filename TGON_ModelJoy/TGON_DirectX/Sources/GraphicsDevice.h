/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-08
* ���� ���� : ����ȣ
* ���� ������ : 2016-01-10
*/

// Happy new year 2016!!

#pragma once
#include "PlatformGraphicsDevice.h"

#include <memory>
#include <Pattern\Singleton.h>


namespace tgon
{


class GraphicsDevice
{

public:
	GraphicsDevice( );
	~GraphicsDevice( );

	bool		Setup( const GraphicsDeviceCreateParam& gdp )		{ return device.Setup( gdp ); }
	void		Display( )					{ device.Display( ); }

private:
	GraphicsDeviceImpl device;
};


}