/**
 * @filename    WindowFwd.h
 * @author      ggomdyu
 * @since       12/29/2017
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   include <Windows.h>
#endif

#if BOOST_OS_MACOS
@class NSWindow;
@class WindowDelegate;
#endif

namespace tgon
{
namespace core
{

struct Color4f;

} /* namespace core */

namespace core
{

struct WindowStyle;


} /* namespace core */
} /* namespace tgon */