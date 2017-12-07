/**
 * @filename    OpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include <boost/predef/os.h>
#include <memory>

#include "OpenGLContextFwd.h"

#if BOOST_OS_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#       include <Windows.h>
#   endif
#elif BOOST_OS_MACOS
    @class NSOpenGLPixelFormat;
    @class NSOpenGLContext;
#elif BOOST_OS_ANDROID
#elif BOOST_OS_IOS
#endif

namespace tgon
{
namespace rhi
{
namespace gl
{

class OpenGLContext
{
public:
    OpenGLContext(const std::shared_ptr<platform::BaseWindow>& window, const rhi::VideoMode& videoMode);
    ~OpenGLContext();

/* @section Public variable */
public:
    HGLRC context;
#if BOOST_OS_WINDOWS
    //HDC dcHandle;
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