#include "..\OpenGLContext.h"
#include "PrecompiledHeader.h"

#include <cassert>
#include <stdexcept>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

#include "Platform/Window.h"
#include "Diagnostics/Log.h"

#include "../OpenGLContext.h"

#include "WindowsOpenGLContextUtility.h"

namespace tgon
{

OpenGLContext::OpenGLContext(const Window& displayTarget, const VideoMode& videoMode) :
    wndHandle(reinterpret_cast<HWND>(displayTarget.GetNativeWindow())),
    dcHandle(GetDC(wndHandle))
{
    assert(wndHandle != nullptr);
    assert(dcHandle != nullptr);

    // Makes a old OpenGL rendering context that used temporary to make newer version of context.
    HGLRC oldGLRC = MakeOldGLRC(dcHandle);
    if (oldGLRC == nullptr)
    {
        throw std::runtime_error("Failed to create old version of OpenGL rendering context.");
    }

    if (::wglMakeCurrent(dcHandle, oldGLRC) == FALSE)
    {
        throw std::runtime_error("Failed to invoke wglMakeCurrent.");
    }
 
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize glew.");
    }

    // Create the new version of OpenGL Context.
    context = MakeNewGLRC(dcHandle);
    if (context == nullptr)
    {
        throw std::runtime_error("Failed to create latest version of OpenGL rendering context.");
    }

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(oldGLRC);

    // Makes a old OpenGL rendering context that used temporary to make newer version of context.
    if (::wglMakeCurrent(dcHandle, context) == FALSE)
    {
        throw std::runtime_error("Failed to invoke wglMakeCurrent.");
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
    ::wglMakeCurrent(dcHandle, context);
}

void OpenGLContext::SwapBuffer()
{
    ::SwapBuffers(dcHandle);
}

void OpenGLContext::Destroy()
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

} /* namespace tgon */