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

HGLRC MakeOldGLRC(HDC dcHandle)
{
    PIXELFORMATDESCRIPTOR pixelFormatDesc{};
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

HGLRC MakeNewGLRC(HDC dcHandle, int majorVersion, int minorVersion)
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

OpenGLContext::OpenGLContext(const Window& displayTarget, const VideoMode& videoMode) :
    wndHandle(reinterpret_cast<HWND>(displayTarget.GetNativeWindow())),
    dcHandle(GetDC(wndHandle))
{
    HGLRC oldGLRC = MakeOldGLRC(dcHandle);
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
    context = MakeNewGLRC(dcHandle, 4, 1);
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
    this->Destroy();
}

OpenGLContext& OpenGLContext::operator=(OpenGLContext&& rhs)
{
    this->Destroy();

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