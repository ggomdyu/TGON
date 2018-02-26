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
namespace core
{

/**
 * @brief                       Creates a window via given WindowStyle.
 * @param [in] windowStyle      Window style information
 */
NSWindow* MakeNativeWindow(const struct WindowStyle& windowStyle);

} /* namespace core */
} /* namespace tgon */
