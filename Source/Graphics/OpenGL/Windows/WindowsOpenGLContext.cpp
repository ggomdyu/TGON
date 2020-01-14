#include "PrecompiledHeader.h"

#include <GL/glew.h>
#include <GL/wglew.h>
#include <cassert>

#include "Platform/Window.h"
#include "Platform/Windows/Windows.h"
#include "Diagnostics/Debug.h"

#include "../OpenGLContext.h"

namespace tgon
{
namespace
{

HGLRC MakeOldGLRC(HDC dcHandle, int colorBits, int depthBits, int stencilBits)
{
    PIXELFORMATDESCRIPTOR pixelFormatDesc{};
    {
        pixelFormatDesc.nSize = sizeof(decltype(pixelFormatDesc));
        pixelFormatDesc.nVersion = 1;
        pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
        pixelFormatDesc.cColorBits = colorBits;
        pixelFormatDesc.cDepthBits = depthBits;
        pixelFormatDesc.cStencilBits = stencilBits;
        pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;
    }

    int pixelFormat = ChoosePixelFormat(dcHandle, &pixelFormatDesc);
    if (pixelFormat == 0)
    {
        return nullptr;
    }

    if (SetPixelFormat(dcHandle, pixelFormat, &pixelFormatDesc) == FALSE)
    {
        return nullptr;
    }

    return wglCreateContext(dcHandle);
}

HGLRC MakeNewGLRC(HDC dcHandle, int colorBits, int depthBits, int stencilBits, int majorVersion, int minorVersion)
{
    int pixelFormatAttributes[] =
    {
        WGL_DRAW_TO_WINDOW_ARB, /*=*/ GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,  /*=*/ GL_TRUE,
        WGL_PIXEL_TYPE_ARB,     /*=*/ WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,     /*=*/ colorBits,
        WGL_DEPTH_BITS_ARB,     /*=*/ depthBits,
        WGL_STENCIL_BITS_ARB,   /*=*/ stencilBits,
        0
    };
    int pixelFormat = 0;
    UINT formatCount = 0;
    if (wglChoosePixelFormatARB(dcHandle, pixelFormatAttributes, nullptr, 1, &pixelFormat, &formatCount) == FALSE)
    {
        return nullptr;
    }

    PIXELFORMATDESCRIPTOR pfd;
    if (SetPixelFormat(dcHandle, pixelFormat, &pfd) == FALSE)
    {
        return nullptr;
    }

    int contextAttributes[64] =
    {
        WGL_CONTEXT_MAJOR_VERSION_ARB,  /*=*/ majorVersion,
        WGL_CONTEXT_MINOR_VERSION_ARB,  /*=*/ minorVersion,
        WGL_CONTEXT_PROFILE_MASK_ARB,   /*=*/ WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };
    return wglCreateContextAttribsARB(dcHandle, nullptr, contextAttributes);
}

} /* namespace */

OpenGLContext::OpenGLContext(const Window& displayWindow, const VideoMode& videoMode) :
    wndHandle(reinterpret_cast<HWND>(displayWindow.GetNativeWindow())),
    dcHandle(GetDC(wndHandle))
{
    HGLRC oldGLRC = MakeOldGLRC(dcHandle, videoMode.colorBits, videoMode.depthBits,videoMode.stencilBits);
    if (oldGLRC == nullptr)
    {
        return;
    }

    if (wglMakeCurrent(dcHandle, oldGLRC) == FALSE)
    {
        return;
    }
 
    if (glewInit() != GLEW_OK)
    {
        return;
    }

    // Create the new version of GLRC.
    context = MakeNewGLRC(dcHandle, videoMode.colorBits, videoMode.depthBits, videoMode.stencilBits, 4, 1);
    if (context == nullptr)
    {
        return;
    }

    // The old OpenGL context is attached to the new GLRC. thus, release it.
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(oldGLRC);
    if (::wglMakeCurrent(dcHandle, context) == FALSE)
    {
        return;
    }
}

OpenGLContext::OpenGLContext(OpenGLContext&& rhs) noexcept :
    wndHandle(rhs.wndHandle),
    context(rhs.context),
    dcHandle(rhs.dcHandle)
{
    rhs.wndHandle = nullptr;
    rhs.context = nullptr;
    rhs.dcHandle = nullptr;
}

OpenGLContext::~OpenGLContext()
{
    this->Destroy();
}

OpenGLContext& OpenGLContext::operator=(OpenGLContext&& rhs) noexcept
{
    std::swap(wndHandle, rhs.wndHandle);
    std::swap(context, rhs.context);
    std::swap(dcHandle, rhs.dcHandle);

    return *this;
}

void OpenGLContext::MakeCurrent()
{
    wglMakeCurrent(dcHandle, context);
}

void OpenGLContext::SwapBuffer()
{
    SwapBuffers(dcHandle);
}

void OpenGLContext::Destroy()
{
    if (context != nullptr)
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(context);
    }

    if (wndHandle != nullptr && dcHandle != nullptr)
    {
        ReleaseDC(wndHandle, dcHandle);

        context = nullptr;
        dcHandle = nullptr;
    }
}

} /* namespace tgon */