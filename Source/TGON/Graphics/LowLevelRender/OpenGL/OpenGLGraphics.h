/**
 * @filename    OpenGLGraphics.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include <memory>
#include <GL/glew.h>

#include "../Generic/GenericGraphics.h"

#include "OpenGLContext.h"

namespace tgon
{

class OpenGLGraphics :
    public GenericGraphics
{
public:
    TGON_RUNTIME_OBJECT(OpenGLGraphics)

/* @section Public constructor */
public:
    OpenGLGraphics(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& displayTargetWindow);
    
/* @section Public destructor */
public:
    virtual ~OpenGLGraphics() override;

/* @section Public method */
public:
    virtual void SetClearColor(const Color4f& color) final override;
    virtual void SetFillMode(FillMode fillMode) final override;
    virtual void SetCullMode(CullMode cullMode) final override;
    virtual void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height) final override;
    virtual void EnableBlend() final override;
    virtual void EnableDepthTest() final override;
    virtual void DisableBlend() final override;
    virtual void DisableDepthTest() final override;
    virtual void ClearColorBuffer() final override;
    virtual void ClearColorDepthBuffer() final override;
    virtual void SwapBuffer() final override;
//    virtual void DrawPrimitives(PrimitiveType primitiveType, int32_t startVertex, int32_t primitiveCount) final override;
//    virtual void DrawIndexedPrimitives(int32_t primitiveCount) final override;

/* @section Private variable */
private:
    OpenGLContext m_context;
    GLuint m_vertexArrayHandle;
};

} /* namespace tgon */
