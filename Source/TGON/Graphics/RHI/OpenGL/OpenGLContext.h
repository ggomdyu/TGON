/**
 * @filename    OpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include <memory>
#include <boost/predef/os.h>

#ifdef _MSC_VER
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#       include <Windows.h>
#   endif
#endif

#if BOOST_OS_WINDOWS
#elif BOOST_OS_MACOS
@class NSOpenGLPixelFormat;
@class NSOpenGLContext;
#elif BOOST_OS_ANDROID
#elif BOOST_OS_IOS
#endif

namespace tgon
{
namespace platform
{

class Window;

} /* namespace platform */

namespace rhi
{

struct OpenGLContext
{
public:
    OpenGLContext(const std::shared_ptr<class platform::Window>& window, const struct VideoMode& videoMode);
    ~OpenGLContext();

/* @section Public variable */
public:
    std::shared_ptr<class platform::Window> window;

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