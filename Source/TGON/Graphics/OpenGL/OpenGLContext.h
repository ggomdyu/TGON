/**
 * @file    OpenGLContext.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

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

#include "Core/NonCopyable.h"
#include "Platform/Window.h"

#include "../VideoMode.h"

namespace tgon
{

class TGON_API OpenGLContext final :
    private NonCopyable
{
/**@section Constructor */
public:
    OpenGLContext(const Window& displayTarget, const VideoMode& videoMode);
    OpenGLContext(OpenGLContext&& rhs) noexcept;

/**@section Destructor */
public:
    ~OpenGLContext();

/**@section Operator */
public:
    OpenGLContext& operator=(OpenGLContext&& rhs);

/**@section Method */
public:
    void MakeCurrent();
    void SwapBuffer();

private:
    void Destroy();

/**@section Variable */
public:
#if TGON_PLATFORM_WINDOWS
    HWND wndHandle;
    HGLRC context;
    HDC dcHandle;
    int pixelFormat;
#elif TGON_PLATFORM_MACOS
    NSOpenGLPixelFormat* pixelFormat;
    NSOpenGLContext* context;
#elif TGON_PLATFORM_ANDROID
#elif TGON_PLATFORM_IOS
#endif
};

} /* namespace tgon */
#endif
