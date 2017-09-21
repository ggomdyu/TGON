/**
 * @filename    MacOSWindowUtility.h
 * @author      ggomdyu
 * @since       07/21/2017
 * @brief
 */

#pragma once

@class NSWindow;

namespace tgon
{
namespace platform
{

struct WindowStyle;

namespace macos
{

/**
 * @brief                       Create window via given arguments.
 * @param [in] windowStyle      Window style information
 */
NSWindow* CreateNativeWindow(const WindowStyle& windowStyle);

} /* namespace macos */
} /* namespace platform */
} /* namespace tgon */
