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

class OpenGLRHI :
    public BaseRHI
{
/* @section Public constructor */
public:
    explicit OpenGLRHI(const std::shared_ptr<platform::Window>& window, const rhi::VideoMode& videoMode);
    virtual ~OpenGLRHI() = default;

/* @section Public method */
public:
    virtual void SetClearColor(const math::Color4f& color) override;
    virtual void SetFillMode(enum class FillMode fillMode) override;
    virtual void SetCullMode(enum class CullMode cullMode) override;
    virtual void EnalbleDepthTest() override;
    virtual void DisableDepthTest() override;

    virtual void BeginScene(enum class PrimitiveType primitiveType) override;
    virtual void EndScene() override;
    virtual void ClearColorBuffer() override;
    virtual void ClearColorDepthBuffer() override;
    virtual void SwapBuffer() override;

/* @section Private variable */
private:
    OpenGLContext m_context;
};

} /* namespace rhi */
} /* namespace tgon */
