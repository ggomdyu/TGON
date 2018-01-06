#include "PrecompiledHeader.pch"

#include "../OpenGLContext.h"

#include "Core/Platform/Window.h"
#include "Core/Debug/Log.h"
#include "Graphics/RHI/RHIType.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

namespace tgon
{
namespace graphics
{

OpenGLContext::OpenGLContext(const std::shared_ptr<core::Window>& window, const graphics::VideoMode& videoMode) :
    window(window),
    dcHandle(GetDC(reinterpret_cast<HWND>(window->GetNativeWindow())))
{
    assert(window != nullptr);
    assert(window->GetNativeWindow() != nullptr);
    assert(dcHandle != nullptr);

    // Initializes Pixel Format.
    {
        ::PIXELFORMATDESCRIPTOR pixelFormatDesc{};
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

        // Attempts to match an appropriate pixel format supported by a device context to a given pixel format specification.
        // If the function fails, the return value is zero.
        pixelFormat = ::ChoosePixelFormat(dcHandle, &pixelFormatDesc);
        if (pixelFormat == -1)
        {
            core::Log("Failed to invoke ChoosePixelFormat. (%d)", GetLastError());
            return;
        }

        // Sets the pixel format of the specified device context to the format specified by the pixelFormat index.
        if (::SetPixelFormat(dcHandle, pixelFormat, &pixelFormatDesc) == FALSE)
        {
            core::Log("Failed to invoke SetPixelFormat. (%d)", GetLastError());
            return;
        }
    }

    // Initializes OpenGL Context.
    {
        // Creates a OpenGL 2.1 rendering context.
        HGLRC oldGLContext = ::wglCreateContext(dcHandle);
        if (oldGLContext == nullptr)
        {
            core::Log("Failed to invoke wglCreateContext. (%d)", GetLastError());
            return;
        }

        // Makes a old OpenGL rendering context that used temporary to make newer version of context.
        if (::wglMakeCurrent(dcHandle, oldGLContext) == FALSE)
        {
            core::Log("Failed to invoke wglMakeCurrent. (%d)", GetLastError());
            return;
        }

        if (glewInit() != GLEW_OK)
        {
            core::Log("Failed to invoke glewInit. (%d)", GetLastError());
            return;
        }

        int attributeIndex = 0;

        int attributes[64] {};
        attributes[attributeIndex++] = WGL_CONTEXT_MAJOR_VERSION_ARB;
        attributes[attributeIndex++] = 4;
        attributes[attributeIndex++] = WGL_CONTEXT_MINOR_VERSION_ARB;
        attributes[attributeIndex++] = 0;
        attributes[attributeIndex++] = 0;

        // Creates a new OpenGL rendering context, which is suitable for drawing on the device referenced by hdc. The rendering context has the same pixel format as the device context.
        context = wglCreateContextAttribsARB(dcHandle, nullptr, attributes);
        if (context == nullptr)
        {
            core::Log("Failed to invoke wglCreateContextAttribsARB. (%d)", GetLastError());
            return;
        }

        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(oldGLContext);

        wglMakeCurrent(dcHandle, context);
        if (context == nullptr)
        {
            core::Log("Failed to invoke wglMakeCurrent. (%d)", GetLastError());
            return;
        }
    }
}

OpenGLContext::~OpenGLContext()
{
    assert(context != nullptr);
    assert(dcHandle != nullptr);

    ::wglMakeCurrent(nullptr, nullptr);
    ::wglDeleteContext(context);
    
    ::ReleaseDC(reinterpret_cast<HWND>(window->GetNativeWindow()), dcHandle);

    context = nullptr;
    dcHandle = nullptr;
}
    
} /* namespace graphics */
} /* namespace tgon */