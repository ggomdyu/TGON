/**
 * @filename    OpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include <memory>

#include "Graphics/RHI/Base/BaseRHI.h"

#include "OpenGLContext.h"

namespace tgon
{
namespace rhi
{
namespace gl
{

class OpenGLRHI :
    public BaseRHI
{
/* @section Public constructor */
public:
    explicit OpenGLRHI(const std::shared_ptr<platform::BaseWindow>& window, const rhi::VideoMode& videoMode);

/* @section Public method */
public:
    virtual void SetClearColor(const math::Color4f& color) override;
    virtual void SetFillMode(FillMode fillMode) override;
    virtual void SetCullMode(CullMode cullMode) override;

    virtual void BeginScene(PrimitiveType primitiveType) override;
    virtual void EndScene() override;
    virtual void Flush() override;

/* @section Private variable */
private:
    OpenGLContext m_context;
};

} /* namespace gl */
} /* namespace rhi */
} /* namespace tgon */