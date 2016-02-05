/*
* 작성자 : 차준호
* 작성일 : 2016-01-08
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-10
*/

#pragma once
#ifdef PLATFORM_WINDOWS_OS
	#include "..\..\TGON_DirectX\Sources\D3d9Device.h"
#endif
#include <memory>

namespace tgon
{


typedef GraphicsDeviceImpl TGraphicsDevice;

/* Smart pointer type */
typedef std::shared_ptr<TGraphicsDevice>	SpGraphicsDevice;
typedef std::unique_ptr<TGraphicsDevice>	UpGraphicsDevice;


}