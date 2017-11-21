#include "PrecompiledHeader.pch"
#include "OpenGLRHI.h"

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>

#include "OpenGLContext.h"
#include "OpenGLRHIUtility.h"

namespace tgon
{
namespace rhi
{
namespace gl
{

OpenGLRHI::OpenGLRHI(const rhi::VideoMode& videoMode) :
    m_context(this->MakeContext(videoMode))
{
}

void OpenGLRHI::BeginScene(PrimitiveType primitiveType)
{
    glBegin(ConvertPrimitiveTypeToNative(primitiveType));
}

void OpenGLRHI::EndScene()
{
    glEnd();
}

void OpenGLRHI::Flush()
{
    glFlush();
}

} /* namespace gl */
} /* namespace rhi */
} /* namespace tgon */
