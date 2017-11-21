/**
 * @filename    MacOSWindowUtility.h
 * @author      ggomdyu
 * @since       07/21/2017
 * @brief
 */

#pragma once
#import "MacOSWindowUtilityFwd.h"

namespace tgon
{
namespace platform
{
namespace macos
{

/**
 * @brief                       Create window through given arguments.
 * @param [in] windowStyle      Window style information
 */
NSWindow* MakeNativeWindow(const WindowStyle& windowStyle);

} /* namespace macos */
} /* namespace platform */
} /* namespace tgon */
