#pragma once

#if TGON_GRAPHICS_OPENGL
#if TGON_PLATFORM_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN 1
#   endif
#   include "Platform/Windows/Windows.h"
#elif TGON_PLATFORM_MACOS
#   include <AppKit/NSOpenGL.h>
#   include <OpenGL/OpenGL.h>
#endif

#include "Core/RuntimeObject.h"

#include "../VideoMode.h"

namespace tg
{

class OpenGLContext final :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(OpenGLContext)

/**@section Constructor */
public:
    OpenGLContext() noexcept = default;
    OpenGLContext(const std::shared_ptr<class Window>& displayWindow, const VideoMode& videoMode);
    OpenGLContext(OpenGLContext&& rhs) noexcept;

/**@section Destructor */
public:
    ~OpenGLContext() override;

/**@section Operator */
public:
    OpenGLContext& operator=(OpenGLContext&& rhs) noexcept;

/**@section Method */
public:
    void MakeCurrent();
    void SwapBuffer();

private:
    void Destroy();

/**@section Variable */
public:
#if TGON_PLATFORM_WINDOWS
    HWND wndHandle = nullptr;
    HGLRC context = nullptr;
    HDC dcHandle = nullptr;
#elif TGON_PLATFORM_MACOS
    NSOpenGLPixelFormat* pixelFormat = nil;
    NSOpenGLContext* context = nil;
#elif TGON_PLATFORM_ANDROID
#elif TGON_PLATFORM_IOS
#endif
};

}
#endif
