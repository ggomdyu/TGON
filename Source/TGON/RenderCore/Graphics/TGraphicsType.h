/*
* Author : Cha Junho
* Date : 05/27/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Config/Graphics.h"

#if TGON_GRAPHICS_DIRECTX9
#	include <d3d9types.h>
#endif


namespace tgon
{


enum class TPrimitiveType
{
#if TGON_GRAPHICS_DIRECTX9
	kPointList = D3DPRIMITIVETYPE::D3DPT_POINTLIST,
	kLineList = D3DPRIMITIVETYPE::D3DPT_LINELIST,
	kLineStrip = D3DPRIMITIVETYPE::D3DPT_LINESTRIP,
	kTriangleList = D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST,
	kTriangleStrip = D3DPRIMITIVETYPE::D3DPT_TRIANGLESTRIP,
	kTriangleFan = D3DPRIMITIVETYPE::D3DPT_TRIANGLEFAN,
#endif
};

enum class TLightType
{
#if TGON_GRAPHICS_DIRECTX9
	kPoint = D3DLIGHTTYPE::D3DLIGHT_POINT,
	kDirectional = D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL,
	kSpot = D3DLIGHTTYPE::D3DLIGHT_SPOT,
#endif
};

enum class TFillMode
{
#if TGON_GRAPHICS_DIRECTX9
	kPoint = D3DFILLMODE::D3DFILL_POINT,
	kWireFrame = D3DFILLMODE::D3DFILL_WIREFRAME,
	kSolid = D3DFILLMODE::D3DFILL_SOLID,
#endif
};

enum class TCullMode
{
#if TGON_GRAPHICS_DIRECTX9
	kNone = D3DCULL::D3DCULL_NONE,
	kCW = D3DCULL::D3DCULL_CW,
	kCCW = D3DCULL::D3DCULL_CCW,
#endif
};


}