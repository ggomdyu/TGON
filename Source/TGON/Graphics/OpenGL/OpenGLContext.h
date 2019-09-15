/**
 * @file    OpenGLContext.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include "Platform/Config.h"
#if TGON_PLATFORM_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN 1
#   endif
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   include <Windows.h>
#elif TGON_PLATFORM_MACOS
#   import <AppKit/NSOpenGL.h>
#   import <OpenGL/OpenGL.h>
#endif

#include "Core/NonCopyable.h"

#include "../GraphicsType.h"

namespace tgon
{

class Window;

struct TGON_API OpenGLContext final :
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
    /**@brief   Makes this context to main. */
    void MakeCurrent();
    
    /**@brief   Displays a back buffer image to screen. */
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
