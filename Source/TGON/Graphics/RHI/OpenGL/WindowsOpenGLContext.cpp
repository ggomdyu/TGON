#include "PrecompiledHeader.pch"
#include "OpenGLContext.h"

#include <Windows.h>

#include "Core/Platform/Base/BaseWindow.h"
#include "Graphics/RHI/Base/BaseRHIType.h"

namespace tgon
{
namespace rhi
{
namespace gl
{

OpenGLContext::OpenGLContext(const std::shared_ptr<platform::BaseWindow>& window, const rhi::VideoMode& videoMode)
{
    ::PIXELFORMATDESCRIPTOR pixelFormatDesc {};
    {
        pixelFormatDesc.nSize = sizeof(decltype(pixelFormatDesc));
        pixelFormatDesc.nVersion = 1;
        pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
        pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
        pixelFormatDesc.cColorBits = 32;
        pixelFormatDesc.cDepthBits = 24;
        pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;
    }

    windowHandle = reinterpret_cast<::HWND>(window->GetNativeWindow());
    {
        HDC dcHandle = ::GetDC(windowHandle);
        
        // Find a suitable pixel format, and make DC select it.
        pixelFormat = ::ChoosePixelFormat(dcHandle, &pixelFormatDesc);
        ::SetPixelFormat(dcHandle, pixelFormat, &pixelFormatDesc);

        // Create Platform-specfic GL context.
        context = ::wglCreateContext(dcHandle);

        // Activates current context.
        // We can draw something after this code.
        ::wglMakeCurrent(dcHandle, context);
    }
}

OpenGLContext::~OpenGLContext()
{
    ::wglMakeCurrent(dcHandle, nullptr);
    ::wglDeleteContext(context);
    ::ReleaseDC(windowHandle, dcHandle);
}

} /* namespace gl */
} /* namespace rhi */
} /* namespace tgon */
