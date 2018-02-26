/**
 * @filename    Renderer.h
 * @author      ggomdyu
 * @since       12/31/2017
 */

#pragma once
#include <memory>

#include "RendererFwd.h"

#include "Material.h"

namespace tgon
{
namespace graphics
{

class Renderer
{
/* @section Public constructor */
public:
    Renderer(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode);

/* @section Public method */
public:
    void SetMaterial(const Material& material);

    const std::unique_ptr<IDynamicRHI>& GetRHI() const noexcept;

/* @section Private method */
private:
    std::unique_ptr<IDynamicRHI> MakeRHI(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode);

/* @section Private variable */
public:
    std::unique_ptr<IDynamicRHI> m_rhi;
};

} /* namespace graphics */
} /* namespace tgon */
