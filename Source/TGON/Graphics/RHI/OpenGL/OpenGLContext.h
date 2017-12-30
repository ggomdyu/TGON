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
namespace rhi
{

struct OpenGLContext
{
/* @section Public constructor */
public:
    OpenGLContext(const std::shared_ptr<platform::Window>& window, const VideoMode& videoMode);
    ~OpenGLContext();

/* @section Public variable */
public:
    std::shared_ptr<platform::Window> window;

#if BOOST_OS_WINDOWS
    HGLRC context;
    HDC dcHandle;
    int pixelFormat;
#elif BOOST_OS_MACOS
    NSOpenGLPixelFormat* pixelFormat;
    NSOpenGLContext* context;
#elif BOOST_OS_ANDROID
#elif BOOST_OS_IOS
#endif
};

} /* namespace rhi */
} /* namespace tgon */