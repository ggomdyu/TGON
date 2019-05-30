/**
 * @file    RenderTargetType.h
 * @author  ggomdyu
 * @since   05/29/2019
 */

#pragma once
#include "Math/Extent.h"

namespace tgon
{

struct RenderTargetProperty
{
/**@section Constructor */
public:
    constexpr RenderTargetProperty(const FExtent2D& extent, bool hasColorBuffer, bool hasDepthBuffer, bool hasStencilBuffer) noexcept :
        RenderTargetProperty(extent.width, extent.height, hasColorBuffer, hasDepthBuffer, hasStencilBuffer)
    {
    }
    
    constexpr RenderTargetProperty(float width, float height, bool hasColorBuffer, bool hasDepthBuffer, bool hasStencilBuffer) noexcept :
        width(width),
        height(height),
        hasColorBuffer(hasColorBuffer),
        hasDepthBuffer(hasDepthBuffer),
        hasStencilBuffer(hasStencilBuffer)
    {
    }

/**@section Variable */
public:
    float width;
    float height;
    bool hasColorBuffer;
    bool hasDepthBuffer;
    bool hasStencilBuffer;
};

} /* namespace tgon */
