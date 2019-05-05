#include "PrecompiledHeader.h"

#include <Windows.h>
#include <GL/glew.h>
#include <GL/wglew.h>

#include "Core/Debug/Log.h"

#include "../OpenGLContext.h"

#include "WindowsOpenGLContextUtility.h"

namespace tgon
{

OpenGLContext::OpenGLContext(const std::shared_ptr<Window>& displayTarget, const VideoMode& videoMode) :
    wndHandle(reinterpret_cast<HWND>(displayTarget->GetNativeWindow())),
    dcHandle(GetDC(wndHandle))
{
    assert(wndHandle != nullptr);
    assert(dcHandle != nullptr);

    // Makes a old OpenGL rendering context that used temporary to make newer version of context.
    HGLRC oldGLRC = MakeOldGLRC(dcHandle);
    if (oldGLRC == nullptr)
    {
        throw std::runtime_error("Failed to invoke MakeOldGLRC.");
    }

    if (::wglMakeCurrent(dcHandle, oldGLRC) == FALSE)
    {
        throw std::runtime_error("Failed to invoke wglMakeCurrent.");
    }
 
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to invoke glewInit.");
    }

    // Create the new version of OpenGL Context.
    context = MakeNewGLRC(dcHandle);
    if (context == nullptr)
    {
        return;
    }

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(oldGLRC);

    // Makes a old OpenGL rendering context that used temporary to make newer version of context.
    if (::wglMakeCurrent(dcHandle, context) == FALSE)
    {
        throw std::runtime_error("Failed to invoke wglMakeCurrent.");
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