/**
 * @file    RenderTarget.h
 * @author  ggomdyu
 * @since   01/06/2018
 */

#pragma once
#if TGON_GRAPHICS_OPENGL
#   include "OpenGL/OpenGLRenderTarget.h"
#endif

#include "Texture.h"

namespace tgon
{

class RenderTarget final :
    private PlatformRenderTarget
{
/**@section Constructor */
public:
    explicit RenderTarget(const FExtent2D& extent, int32_t depthBits = 0, int32_t stencilBits = 0);

/**@section Method */
public:
    void Use();
    void Unuse();
    std::shared_ptr<Texture> GetTexture() noexcept;
    std::shared_ptr<const Texture> GetTexture() const noexcept;

private:
    std::shared_ptr<Texture> m_texture;
};

} /* namespace tgon */
