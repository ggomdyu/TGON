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
    OpenGLGraphics(OpenGLContext&& context);
    
/**@section Variable */
protected:
    OpenGLContext m_context;
    GLuint m_vertexArrayHandle = 0;
};

using PlatformGraphics = OpenGLGraphics;

} /* namespace tgon */
