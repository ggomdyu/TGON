/**
 * @file    OpenGLIndexBuffer.h
 * @author  ggomdyu
 * @since   01/05/2018
 */

#pragma once
#include <GL/glew.h>

#include "Platform/Config.h"
#include "Core/NonCopyable.h"

namespace tgon
{

class TGON_API OpenGLIndexBuffer :
    private NonCopyable
{
/**@section Constructor */
protected:
    explicit OpenGLIndexBuffer(GLuint indexBufferHandle) noexcept;
    OpenGLIndexBuffer(OpenGLIndexBuffer&& rhs) noexcept;

/**@section Method */
protected:
    void Destroy();
    
/**@section Operator */
protected:
    OpenGLIndexBuffer& operator=(OpenGLIndexBuffer&& rhs);

/**@section Variable */
protected:
    GLuint m_indexBufferHandle;
};
    
using PlatformIndexBuffer = OpenGLIndexBuffer;

} /* namespace tgon */
