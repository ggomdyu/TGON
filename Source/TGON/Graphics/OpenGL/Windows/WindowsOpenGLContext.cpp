#include "PrecompiledHeader.h"

#include <Windows.h>
#include <GL/glew.h>
#include <cassert>

#include "Platform/Window.h"
#include "Diagnostics/Debug.h"

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

    // Create the old version of GLRC(GL rendering context).
    // It will be used to create the latest version of GLRC.
    HGLRC oldGLRC = MakeOldGLRC(dcHandle);
    if (oldGLRC == nullptr)
    {
        Debug::WriteLine("Failed to create the old version of GLRC.");
        return;
    }

    if (::wglMakeCurrent(dcHandle, oldGLRC) == FALSE)
    {
        Debug::WriteLine("Failed to invoke wglMakeCurrent.");
        return;
    }
 
    if (glewInit() != GLEW_OK)
    {
        Debug::WriteLine("Failed to initialize glew.");
        return;
    }

    // Create the new version of GLRC.
    context = MakeNewGLRC(dcHandle);
    if (context == nullptr)
    {
        Debug::WriteLine("Failed to create the latest version of GLRC.");
        return;
    }

    // The old OpenGL context is attached to the new GLRC. thus, release it.
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(oldGLRC);

    if (::wglMakeCurrent(dcHandle, context) == FALSE)
    {
        Debug::WriteLine("Failed to invoke wglMakeCurrent.");
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