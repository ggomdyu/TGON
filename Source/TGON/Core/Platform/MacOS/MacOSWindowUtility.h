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

/**
 * @brief                       Create window through given arguments.
 * @param [in] windowStyle      Window style information
 */
NSWindow* MakeNativeWindow(const struct WindowStyle& windowStyle);

} /* namespace platform */
} /* namespace tgon */
