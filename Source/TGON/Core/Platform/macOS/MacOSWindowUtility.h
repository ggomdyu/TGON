/**
 * @filename    MacOSWindowUtility.h
 * @author      ggomdyu
 * @since       07/21/2017
 * @brief
 */

#include <Cocoa/Cocoa.h>

namespace tgon
{
namespace platform
{

struct WindowStyle;

namespace macos
{

/**
 * @brief                               Converts WindowStyle to Native-window-style.
 * @param [in] windowStyle              Window style information
 * @param [out] destWindowPosition      Destination of window position
 * @param [out] destWindowStyleMask     Destination of NSWindowStyleMask
 */
void ConvertToNativeWindowStyle(const WindowStyle& windowStyle, NSPoint* destWindowPosition, NSWindowStyleMask* destWindowStyleMask);

/**
 * @brief                       Create window via given arguments.
 * @param [in] windowStyle      Window style information
 */
NSWindow* CreateNativeWindow(const WindowStyle& windowStyle);

} /* namespace macos */
} /* namespace platform */
} /* namespace tgon */
