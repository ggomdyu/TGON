#include "PrecompiledHeader.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

#include "Core/Platform/Window.h"
#include "Core/Debug/Log.h"
#include "Graphics/LowLevel/Generic/GenericGraphicsType.h"

#include "OpenGLContext.h"

namespace tgon
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
        Log(LogLevel::Warning, "Failed to invoke ChoosePixelFormat. (Code: %d)", GetLastError());
        return nullptr;
    }

    // Sets the pixel format of the specified device context to the format specified by the pixelFormat index.
    if (::SetPixelFormat(dcHandle, pixelFormat, &pixelFormatDesc) == FALSE)
    {
        Log(LogLevel::Warning, "Failed to invoke SetPixelFormat. (Code: %d)", GetLastError());
        return nullptr;
    }

    // Creates a OpenGL 2.1 rendering context.
    HGLRC context = ::wglCreateContext(dcHandle);
    if (context == nullptr)
    {
        Log(LogLevel::Warning, "Failed to invoke wglCreateContext. (Code: %d)", GetLastError());
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
    UINT formatCount = 0;
    if (wglChoosePixelFormatARB(dcHandle, pixelFormatAttributes, nullptr, 1, &pixelFormat, &formatCount) == FALSE)
    {
        Log(LogLevel::Warning, "Failed to invoke wglChoosePixelFormatARB. (Code: %d)", GetLastError());
    }

    // Sets the pixel format of the specified device context to the format specified by the pixelFormat index.
    PIXELFORMATDESCRIPTOR pfd;
    if (::SetPixelFormat(dcHandle, pixelFormat, &pfd) == FALSE)
    {
        Log(LogLevel::Warning, "Failed to invoke SetPixelFormat. (Code: %d)", GetLastError());
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
        Log(LogLevel::Warning, "Failed to invoke wglCreateContextAttribsARB. (Code: %d)", GetLastError());
        return nullptr;
    }

    return context;
}

} /* namespace */

OpenGLContext::OpenGLContext(const VideoMode& videoMode, Window& window) :
    wndHandle(reinterpret_cast<HWND>(window.GetNativeWindow())),
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
            Log(LogLevel::Warning, "Failed to invoke wglMakeCurrent. (Code: %d)", GetLastError());
            return;
        }
    }
    else
    {
        return;
    }

    if (glewInit() != GLEW_OK)
    {
        Log(LogLevel::Warning, "Failed to invoke glewInit. (Code: %d)", GetLastError());
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
            Log(LogLevel::Warning, "Failed to invoke wglMakeCurrent. (Code: %d)", GetLastError());
            return;
        }
    }
    else
    {
        return;
    }
}

OpenGLContext::OpenGLContext(OpenGLContext&& rhs) :
    wndHandle(rhs.wndHandle),
    context(rhs.context),
    dcHandle(rhs.dcHandle),
    pixelFormat(rhs.pixelFormat)
{
    rhs.wndHandle = nullptr;
    rhs.context = nullptr;
    rhs.dcHandle = nullptr;
    rhs.pixelFormat = 0;
}

OpenGLContext::~OpenGLContext()
{
    if (context != nullptr)
    {
        ::wglMakeCurrent(nullptr, nullptr);
        ::wglDeleteContext(context);
    }
        
    if (wndHandle != nullptr && dcHandle != nullptr)
    {
        ::ReleaseDC(wndHandle, dcHandle);

        context = nullptr;
        dcHandle = nullptr;
    }
}

OpenGLContext& OpenGLContext::operator=(OpenGLContext&& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    wndHandle = rhs.wndHandle;
    context = rhs.context;
    dcHandle = rhs.dcHandle;
    pixelFormat = rhs.pixelFormat;
    
    rhs.wndHandle = nullptr;
    rhs.context = nullptr;
    rhs.dcHandle = nullptr;
    rhs.pixelFormat = 0;

    return *this;
}

void OpenGLContext::MakeCurrent()
{
    ::wglMakeCurrent(dcHandle, context);
}

void OpenGLContext::SwapBuffer()
{
    ::SwapBuffers(dcHandle);
}

} /* namespace tgon */