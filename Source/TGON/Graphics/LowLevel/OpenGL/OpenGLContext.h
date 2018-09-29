/**
 * @file    OpenGLContext.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once
#include <boost/noncopyable.hpp>
#if TGON_PLATFORM_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN 1
#   endif
#   include <Windows.h>
#elif TGON_PLATFORM_MACOS
#   import <AppKit/NSOpenGL.h>
#   import <OpenGL/OpenGL.h>
#endif

#include "Core/Platform/Window.h"

#include "../GraphicsType.h"

namespace tgon
{

struct TGON_API OpenGLContext final :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(OpenGLContext);

/**@section Public constructor */
public:
    OpenGLContext(const VideoMode& videoMode, const Window& displayTarget);
    OpenGLContext(OpenGLContext&& rhs);

/**@section Public destructor */
public:
    ~OpenGLContext();

/**@section Public operator */
public:
    OpenGLContext& operator=(OpenGLContext&& rhs);

/**@section Public method */
public:
    /**@brief   Makes this context to main. */
    void MakeCurrent();
    
    /**@brief   Displays a back buffer image to screen. */
    void SwapBuffer();

/**@section Public variable */
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
