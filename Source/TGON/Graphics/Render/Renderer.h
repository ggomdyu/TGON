/**
 * @filename    Renderer.h
 * @author      ggomdyu
 * @since       12/31/2017
 */

#pragma once
#include <memory>

#include "RendererFwd.h"

#include "Material.h"
#include "Texture.h"

namespace tgon
{
namespace render
{

class Renderer
{
/* @section Public constructor */
public:
    Renderer(const std::shared_ptr<platform::Window>& window, const rhi::VideoMode& videoMode);

/* @section Public method */
public:
    void SetMaterial(const Material& material);

    const std::unique_ptr<rhi::IDynamicRHI>& GetRHI() const noexcept;

/* @section Private method */
private:
    std::unique_ptr<rhi::IDynamicRHI> MakeRHI(const std::shared_ptr<platform::Window>& window, const rhi::VideoMode& videoMode);

/* @section Private variable */
public:
    std::unique_ptr<rhi::IDynamicRHI> m_rhi;
};

} /* namespace render */
} /* namespace tgon */