#include "PrecompiledHeader.pch"

#include <Windows.h>

#include "Core/Platform/Window.h"

#include "../../OpenGLContext.h"
#include "../../../RHIType.h"

namespace tgon
{
namespace rhi
{

OpenGLContext::OpenGLContext(const std::shared_ptr<platform::Window>& window, const rhi::VideoMode& videoMode) :
    window(window)
{
    ::PIXELFORMATDESCRIPTOR pixelFormatDesc {};
    {
        pixelFormatDesc.nSize = sizeof(decltype(pixelFormatDesc));
        pixelFormatDesc.nVersion = 1;
        pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
        if (videoMode.enableDoubleBuffer)
        {
            pixelFormatDesc.dwFlags |= PFD_DOUBLEBUFFER;
        }

        pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
        pixelFormatDesc.cColorBits = 32;
        pixelFormatDesc.cDepthBits = 24;
        pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;
    }

    dcHandle = ::GetDC(reinterpret_cast<HWND>(window->GetNativeWindow()));
        
    // Find a suitable pixel format, and make DC select it.
    pixelFormat = ::ChoosePixelFormat(dcHandle, &pixelFormatDesc);
    ::SetPixelFormat(dcHandle, pixelFormat, &pixelFormatDesc);

    // Create Platform-specfic GL context.
    context = ::wglCreateContext(dcHandle);

    // Activates current context.
    // We can draw something after this code.
    ::wglMakeCurrent(dcHandle, context);
}

OpenGLContext::~OpenGLContext()
{
    ::wglMakeCurrent(dcHandle, nullptr);
    ::wglDeleteContext(context);
    ::ReleaseDC(reinterpret_cast<HWND>(window->GetNativeWindow()), dcHandle);
}

} /* namespace rhi */
} /* namespace tgon */