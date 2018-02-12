#include "PrecompiledHeader.pch"

#include "OpenGLContext.h"

#include "Core/Platform/Window.h"
#include "Core/Debug/Log.h"
#include "Graphics/Abstract/GraphicsType.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

namespace tgon
{
namespace graphics
{
namespace
{

HGLRC MakeOldGLRC(HDC dcHandle)
{
    ::PIXELFORMATDESCRIPTOR pixelFormatDesc{};
    {
        pixelFormatDesc.nSize = sizeof(decltype(pixelFormatDesc));
        pixelFormatDesc.nVersion = 1;
        pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
        pixelFormatDesc.cColorBits = 32;
        pixelFormatDesc.cDepthBits = 24;
        pixelFormatDesc.cStencilBits = 8;
        pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;
    }

    // Attempts to match an appropriate pixel format supported by a device context to a given pixel format specification.
    // If the function fails, the return value is zero.
    int pixelFormat = ::ChoosePixelFormat(dcHandle, &pixelFormatDesc);
    if (pixelFormat == -1)
    {
        core::Log("Failed to invoke ChoosePixelFormat. (%d)", GetLastError());
        return nullptr;
    }

    // Sets the pixel format of the specified device context to the format specified by the pixelFormat index.
    if (::SetPixelFormat(dcHandle, pixelFormat, &pixelFormatDesc) == FALSE)
    {
        core::Log("Failed to invoke SetPixelFormat. (%d)", GetLastError());
        return nullptr;
    }

    // Creates a OpenGL 2.1 rendering context.
    HGLRC context = ::wglCreateContext(dcHandle);
    if (context == nullptr)
    {
        core::Log("Failed to invoke wglCreateContext. (%d)", GetLastError());
        return nullptr;
    }

    return context;
}

HGLRC MakeNewGLRC(HDC dcHandle)
{
    int pixelFormatAttributes[] =
    {
        WGL_DRAW_TO_WINDOW_ARB, /*=*/ GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,  /*=*/ GL_TRUE,
        WGL_PIXEL_TYPE_ARB,     /*=*/ WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,     /*=*/ 32,
        WGL_DEPTH_BITS_ARB,     /*=*/ 24,
        WGL_STENCIL_BITS_ARB,   /*=*/ 8,
        0
    };

    int pixelFormat = 0;
    UINT formatNumber = 0;
    if (wglChoosePixelFormatARB(dcHandle, pixelFormatAttributes, nullptr, 1, &pixelFormat, &formatNumber) == FALSE)
    {
        core::Log("Failed to invoke wglChoosePixelFormatARB. (%d)", GetLastError());
    }

    // Sets the pixel format of the specified device context to the format specified by the pixelFormat index.
    PIXELFORMATDESCRIPTOR pfd;
    if (::SetPixelFormat(dcHandle, pixelFormat, &pfd) == FALSE)
    {
        core::Log("Failed to invoke SetPixelFormat. (%d)", GetLastError());
    }

    int contextAttributes[64] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB,  /*=*/ 4,
        WGL_CONTEXT_MINOR_VERSION_ARB,  /*=*/ 1,
        WGL_CONTEXT_PROFILE_MASK_ARB,   /*=*/ WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    // Creates a new OpenGL rendering context, which is suitable for drawing on the device referenced by hdc. The rendering context has the same pixel format as the device context.
    HGLRC context = wglCreateContextAttribsARB(dcHandle, nullptr, contextAttributes);
    if (context == nullptr)
    {
        core::Log("Failed to invoke wglCreateContextAttribsARB. (%d)", GetLastError());
        return nullptr;
    }

    return context;
}


} /* namespace */

OpenGLContext::OpenGLContext(const std::shared_ptr<core::Window>& window) :
    wndHandle(reinterpret_cast<HWND>(window->GetNativeWindow())),
    dcHandle(GetDC(wndHandle))
{
    assert(wndHandle != nullptr);
    assert(dcHandle != nullptr);

    // Makes a old OpenGL rendering context that used temporary to make newer version of context.
    HGLRC oldGLRC = MakeOldGLRC(dcHandle);
    if (oldGLRC != nullptr)
    {
        if (::wglMakeCurrent(dcHandle, oldGLRC) == FALSE)
        {
            core::Log("Failed to invoke wglMakeCurrent. (%d)", GetLastError());
            return;
        }
    }
    else
    {
        return;
    }

    if (glewInit() != GLEW_OK)
    {
        core::Log("Failed to invoke glewInit. (%d)", GetLastError());
        return;
    }

    // Create the new version of OpenGL Context.
    context = MakeNewGLRC(dcHandle);
    if (context != nullptr)
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(oldGLRC);

        // Makes a old OpenGL rendering context that used temporary to make newer version of context.
        if (::wglMakeCurrent(dcHandle, context) == FALSE)
        {
            core::Log("Failed to invoke wglMakeCurrent. (%d)", GetLastError());
            return;
        }
    }
    else
    {
        return;
    }
}

OpenGLContext::~OpenGLContext()
{
    assert(context != nullptr);
    assert(dcHandle != nullptr);

    ::wglMakeCurrent(nullptr, nullptr);
    ::wglDeleteContext(context);
    
    ::ReleaseDC(wndHandle, dcHandle);

    context = nullptr;
    dcHandle = nullptr;
}

void OpenGLContext::MakeCurrent()
{
    ::wglMakeCurrent(dcHandle, context);
}
    
} /* namespace graphics */
} /* namespace tgon */