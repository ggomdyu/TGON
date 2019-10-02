/**
 * @file    OpenGLGraphics.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <GL/glew.h>

#include "Core/NonCopyable.h"

#include "OpenGLContext.h"

namespace tgon
{
    
class TGON_API OpenGLGraphics :
    private NonCopyable
{
/**@section Constructor */
protected:
    OpenGLGraphics(const Window& displayTarget, const VideoMode& videoMode) noexcept(false);
    
/**@section Destructor */
protected:
    ~OpenGLGraphics();

/**@section Method */
protected:
    void SetDefaultGLRenderState();
    
/**@section Variable */
protected:
    OpenGLContext m_context;
    GLuint m_vertexArrayHandle;
};

using PlatformGraphics = OpenGLGraphics;

} /* namespace tgon */
