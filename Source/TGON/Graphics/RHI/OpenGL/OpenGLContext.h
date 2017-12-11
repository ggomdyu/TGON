/**
 * @filename    OpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include <memory>

#ifdef _MSC_VER
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#       include <Windows.h>
#   endif
#endif

#include "OpenGLContextFwd.h"

namespace tgon
{
namespace rhi
{
namespace gl
{

struct OpenGLContext
{
public:
    OpenGLContext(const std::shared_ptr<platform::BaseWindow>& window, const rhi::VideoMode& videoMode);
    ~OpenGLContext();

/* @section Public variable */
public:
    std::shared_ptr<platform::BaseWindow> window;

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

} /* namespace gl */
} /* namespace rhi */
} /* namespace tgon */