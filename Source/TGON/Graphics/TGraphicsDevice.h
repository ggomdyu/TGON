/*
* Author : 차준호
* Date : 2016-01-08
* 최종 수정 :
* 최종 수정일 : 
* Description : Polymorphic graphics type
*/

#pragma once
#include "../Config/Platform/Platform.h"
#include "Window/TWindow.h"

#ifdef TGON_PLATFORM_WINDOWS
	#include "D3d9Device.h"
#elif
#endif
#include <memory>


namespace tgon
{


class TGraphicsDevice;
typedef std::shared_ptr<TGraphicsDevice> SpTGraphicsDevice;


class TGraphicsDevice : public GraphicsDeviceImpl
{
private:
	explicit TGraphicsDevice( const SpTWindow& window,
							  const struct GraphicsDeviceProp& gdcp ) :
		GraphicsDeviceImpl( window, gdcp ) {}

public:
	static SpTGraphicsDevice Create( const SpTWindow& window,
									 const struct GraphicsDeviceProp& gdcp )
	{
		SpTGraphicsDevice device( new TGraphicsDevice( window, gdcp ));
		return device;
	}

};


}