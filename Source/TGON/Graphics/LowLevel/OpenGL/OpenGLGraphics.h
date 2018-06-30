/**
 * @file    OpenGLGraphics.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>
#include <GL/glew.h>

#include "OpenGLContext.h"

namespace tgon
{

struct VideoMode;
struct Color4f;
enum class PrimitiveType;
enum class FillMode;
enum class CullMode;

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
    void EnableBlend();
    void EnableDepthTest();
    void DisableBlend();
    void DisableDepthTest();
    void ClearColorBuffer();
    void ClearColorDepthBuffer();
    void SwapBuffer();
    void DrawPrimitives(PrimitiveType primitiveType, int32_t startVertex, int32_t primitiveCount);
    void DrawIndexedPrimitives(int32_t primitiveCount);

/* @section Private variable */
private:
    OpenGLContext m_context;
    GLuint m_vertexArrayHandle;
};

} /* namespace tgon */
