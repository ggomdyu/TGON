/**
 * @filename    OpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include <memory>

#include "OpenGLContextFwd.h"

namespace tgon
{

struct OpenGLContext
{
/* @section Public constructor */
public:
    OpenGLContext(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& window);
    ~OpenGLContext();

/* @section Public method */
public:
    void MakeCurrent();
    void SwapBuffer();

/* @section Public variable */
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