/**
 * @filename    MacOSWindowUtility.h
 * @author      ggomdyu
 * @since       07/21/2017
 * @brief
 */

#pragma once
#include "MacOSWindowFwd.h"

namespace tgon
{

/**
 * @brief                       Creates a window via given WindowStyle.
 * @param [in] windowStyle      Window style information
 */
NSWindow* MakeNativeWindow(const WindowStyle& windowStyle);

} /* namespace tgon */
