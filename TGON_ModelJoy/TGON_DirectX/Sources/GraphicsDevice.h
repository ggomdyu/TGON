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
	Declare_Static_Singleton( GraphicsDevice )


	bool		Setup( GraphicsDeviceCreateParam gdp )		{ return device.Setup( gdp ); }
	void		Display( )					{ device.Display( ); }

private:
				GraphicsDevice( );
	virtual		~GraphicsDevice( );

	void		operator delete ( void* arg )		{ std::free( arg ); }


private:
	GraphicsDeviceImpl device;
};


}