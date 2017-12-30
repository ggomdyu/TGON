/**
 * @filename    OpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include <memory>

#include "../OpenGLContext.h"

#include "IDynamicRHI.h"

namespace tgon
{
namespace rhi
{

class OpenGLRHI :
    public IDynamicRHI
{
/* @section Public constructor */
public:
    explicit OpenGLRHI(const std::shared_ptr<platform::Window>& window, const rhi::VideoMode& videoMode);
    virtual ~OpenGLRHI() = default;

/* @section Public method */
public:
    virtual void SetClearColor(const math::Color4f& color) override;
    virtual void SetFillMode(FillMode fillMode) override;
    virtual void SetCullMode(CullMode cullMode) override;
    virtual void EnalbleDepthTest() override;
    virtual void DisableDepthTest() override;

    virtual Shader CreateShader(const char* shaderCode);
    virtual VideoBuffer CreateVideoBuffer(VideoBufferType videoBufferType, std::size_t bufferSize);

    virtual void BeginScene(PrimitiveType primitiveType) override;
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
