/**
 * @file    OpenGLGraphics.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <GL/glew.h>
#include <memory>

#include "OpenGLContext.h"

#include "../GraphicsType.h"

namespace tgon
{
    
class GraphicsImpl final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    GraphicsImpl(const Window& displayTarget, const VideoMode& videoMode);
    
/* @section Public destructor */
public:
    ~GraphicsImpl();

/* @section Public method */
public:
    void SetClearColor(const Color4f& color);
    void SetFillMode(FillMode fillMode);
    void SetCullMode(CullMode cullMode);
    void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);
    void SetBlendMode(BlendMode blendMode);
    void EnableCullFace();
    void EnableBlend();
    void EnableDepthTest();
    void DisableCullFace();
    void DisableBlend();
    void DisableDepthTest();
    void ClearColorBuffer();
    void ClearColorDepthBuffer();
    void SwapBuffer();
    void DrawPrimitives(PrimitiveType primitiveType, int32_t vertexCount);
    void DrawIndexedPrimitives(PrimitiveType primitiveType, int32_t indexCount);

/* @section Private method */
private:
    void SetDefaultGLRenderState();
    
/* @section Private variable */
private:
    OpenGLContext m_context;
    
    GLuint m_vertexArrayHandle;
};

} /* namespace tgon */
