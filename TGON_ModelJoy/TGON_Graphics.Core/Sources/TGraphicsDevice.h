/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-08
* ���� ���� : ����ȣ
* ���� ������ : 2016-01-10
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