/**
 * @file    OpenGLGraphics.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <GL/glew.h>
#include <memory>

#include "Math/Rect.h"
#include "Math/Color.h"

#include "OpenGLContext.h"

#include "../GraphicsType.h"

namespace tgon
{
    
class TGON_API OpenGLGraphics
{
/**@section Constructor */
public:
    OpenGLGraphics(const Window& displayTarget, const VideoMode& videoMode) noexcept(false);
    
/**@section Destructor */
public:
    ~OpenGLGraphics();

/**@section Method */
public:
    void SetScissorRect(const FRect& scissorRect);
    void SetClearColor(const Color4f& color);
    void SetFillMode(FillMode fillMode);
    void SetCullMode(CullMode cullMode);
    void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);
    void SetBlendMode(BlendMode blendMode);
    void EnableCullFace();
    void EnableBlend();
    void EnableDepthTest();
    void EnableScissorTest();
    void DisableCullFace();
    void DisableBlend();
    void DisableDepthTest();
    void DisableScissorTest();
    void ClearColorBuffer();
    void ClearColorDepthBuffer();
    void SwapBuffer();
    void DrawPrimitives(PrimitiveType primitiveType, int32_t vertexStartOffset, int32_t vertexCount);
    void DrawIndexedPrimitives(PrimitiveType primitiveType, int32_t indexCount);

private:
    void SetDefaultGLRenderState();
    
/**@section Variable */
private:
    OpenGLContext m_context;
    GLuint m_vertexArrayHandle;
};

using PlatformGraphics = OpenGLGraphics;

} /* namespace tgon */
