/**
 * @filename    ApplicationFwd.h
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
@class NSEvent;
#endif

namespace tgon
{
namespace core
{

class Application;
struct WindowStyle;
enum class MessageBoxIconType;
class Window;
struct BatteryState;

} /* namespace core */
} /* namespace tgon */