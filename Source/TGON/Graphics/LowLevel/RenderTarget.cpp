#include "PrecompiledHeader.h"

#include <GL/glew.h>

#include "RenderTarget.h"
#include "Core/Platform/Config.h"
#if (TGON_PLATFORM_WINDOWS || TGON_PLATFORM_MACOS)
#   include "OpenGL/OpenGLRenderTarget.h"
#endif

namespace tgon
{

RenderTarget::RenderTarget(int32_t width, int32_t height, int32_t multisampleLevel) :
    m_renderTargetImpl(std::make_unique<RenderTargetImpl>(width, height, multisampleLevel))
{
}

void RenderTarget::Use()
{
    m_renderTargetImpl->Use();
}

void RenderTarget::Unuse()
{
    m_renderTargetImpl->Unuse();
}

} /* namespace tgon */
