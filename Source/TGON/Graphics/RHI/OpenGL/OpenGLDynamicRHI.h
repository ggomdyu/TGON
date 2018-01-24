/**
 * @filename    OpenGLDynamicRHI.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include "OpenGLDynamicRHIFwd.h"

#include "../IDynamicRHI.h"

#include <memory>
#include <GL/glew.h>

namespace tgon
{
namespace graphics
{

class OpenGLDynamicRHI :
    public IDynamicRHI
{
/* @section Public constructor */
public:
    OpenGLDynamicRHI(const std::shared_ptr<core::Window>& window, const VideoMode& videoMode);
    virtual ~OpenGLDynamicRHI() override;

/* @section Public method */
public:
    virtual void SetClearColor(const core::Color4f& color) override;
    virtual void SetFillMode(FillMode fillMode) override;
    virtual void SetCullMode(CullMode cullMode) override;
    virtual void EnableBlend() override;
    virtual void EnableDepthTest() override;
    virtual void DisableBlend() override;
    virtual void DisableDepthTest() override;

    virtual void BeginScene(PrimitiveType primitiveType) override;
    virtual void EndScene() override;
    virtual void ClearColorBuffer() override;
    virtual void ClearColorDepthBuffer() override;
    virtual void SwapBuffer() override;

/* @section Private variable */
private:
    std::unique_ptr<OpenGLContext> m_context;

    GLuint m_vertexArray;
};

} /* namespace graphics */
} /* namespace tgon */