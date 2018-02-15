/**
 * @filename    OpenGLContextFwd.h
 * @author      ggomdyu
 * @since       12/29/2017
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#       include <Windows.h>
#   endif
#endif

#if BOOST_OS_MACOS
@class NSOpenGLPixelFormat;
@class NSOpenGLContext;
#endif

namespace tgon
{
namespace core
{

class GenericWindow;

} /* namespace core */

namespace graphics
{

struct VideoMode;

} /* namespace graphics */
} /* namespace tgon */
