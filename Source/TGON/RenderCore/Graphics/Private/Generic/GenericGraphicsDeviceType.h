/**
 * @filename    GenericGraphicsDeviceType.h
 * @author      ggomdyu
 * @since       05/14/2017
 */

#pragma once
#include <cstdint>

#include "Core/Platform/TConfig.h"

#ifdef TGON_GRAPHICS_DIRECT3D11
#	include <dxgi.h>
#	include <d3dcommon.h>
#	include <d3d11.h>
#	include <d3dx10math.h>
#elif defined TGON_GRAPHICS_DIRECT3D12
#elif TGON_GRAPHICS_OPENGL
#	include <gl/GL.h>
#	include <gl/GLU.h>
#elif defined TGON_GRAPHICS_VULKAN
#elif defined TGON_GRAPHICS_OPENGL
#endif

namespace tgon {
namespace graphics {

struct TGraphicsDeviceProperty
{
    std::size_t bufferWidth;
    std::size_t bufferHeight;
    bool fullscreen;
    bool enableVerticalSync;
};

struct TRendererProperty
{
    float fovy;
    float aspectRatio;
    float nearZ;
    float farZ;
};

struct TRefreshRate
{
    constexpr TRefreshRate() noexcept :
		numerator(0), denominator(0)
	{
	}
    constexpr TRefreshRate(int32_t numerator, int32_t denominator) noexcept :
		numerator(numerator), denominator(denominator)
	{
	}

    int32_t numerator;
    int32_t denominator;
};

enum class TPrimitiveType
{
#if TGON_GRAPHICS_DIRECT3D9
	kPointList = D3DPRIMITIVETYPE::D3DPT_POINTLIST,
	kLineList = D3DPRIMITIVETYPE::D3DPT_LINELIST,
	kLineStrip = D3DPRIMITIVETYPE::D3DPT_LINESTRIP,
	kTriangleList = D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST,
	kTriangleStrip = D3DPRIMITIVETYPE::D3DPT_TRIANGLESTRIP,
	kTriangleFan = D3DPRIMITIVETYPE::D3DPT_TRIANGLEFAN,
#elif TGON_GRAPHICS_OPENGL
	kPointList = GL_POINTS,
	kLineList = GL_LINES,
	kLineStrip = GL_LINE_STRIP,
	kTriangleList = GL_TRIANGLES,
	kTriangleStrip = GL_TRIANGLE_STRIP,
	kTriangleFan = GL_TRIANGLE_FAN,
#endif
};

enum class TLightType
{
#if TGON_GRAPHICS_DIRECT3D9
	kPoint = D3DLIGHTTYPE::D3DLIGHT_POINT,
	kDirectional = D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL,
	kSpot = D3DLIGHTTYPE::D3DLIGHT_SPOT,
#endif
};

enum class TFillMode
{
#if TGON_GRAPHICS_DIRECT3D9
	kPoint = D3DFILLMODE::D3DFILL_POINT,
	kWireFrame = D3DFILLMODE::D3DFILL_WIREFRAME,
	kSolid = D3DFILLMODE::D3DFILL_SOLID,
#endif
};

enum class TCullMode
{
#if TGON_GRAPHICS_DIRECT3D9
	kNone = D3DCULL::D3DCULL_NONE,
	kCW = D3DCULL::D3DCULL_CW,
	kCCW = D3DCULL::D3DCULL_CCW,
#else TGON_GRAPHICS_OPENGL
	kNone,
	kCW,
	kCCW,
#endif
};

enum class TFormat
{
#ifdef TGON_GRAPHICS_DIRECT3D11
	R8G8B8A8_UNORM = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM,
#elif defined(TGON_GRAPHICS_VULKAN)
	R8G8B8A8_UNORM = VkSurfaceFormatKHR::VK_FORMAT_B8G8R8A8_UNORM,
#endif
};

} /* namespace graphics */
} /* namespace tgon */