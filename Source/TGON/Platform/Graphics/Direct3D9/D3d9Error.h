/*
* Author : Junho-Cha
* Date : 05/08/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <d3d9.h>

namespace tgon
{


enum class D3d9ErrorCode
{
	kSuccess =				S_OK,
	kFailed =				S_FALSE,
	kOutOfVideoMemory =		D3DERR_OUTOFVIDEOMEMORY,
	kWrongTextureFormat =	D3DERR_WRONGTEXTUREFORMAT,
	kNotFound =				D3DERR_NOTFOUND,
	kInvalidCall =			D3DERR_INVALIDCALL,
	kInvalidDevice =		D3DERR_INVALIDDEVICE,
	kDeviceLost =			D3DERR_DEVICELOST,
	kDeviceRemoved =		D3DERR_DEVICEREMOVED,
};


}