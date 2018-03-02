/**
 * @filename    OpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include "OpenGLContextFwd.h"

#include <memory>

namespace tgon
{
namespace graphics
{

struct OpenGLContext
{
/* @section Public constructor */
public:
    OpenGLContext(const VideoMode& videoMode, const std::shared_ptr<core::GenericWindow>& window);
    ~OpenGLContext();

/* @section Public method */
public:
    void MakeCurrent();

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

} /* namespace graphics */
} /* namespace tgon */