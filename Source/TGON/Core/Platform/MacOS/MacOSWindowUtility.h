/**
 * @file    MacOSWindowUtility.h
 * @author  ggomdyu
 * @since   07/21/2017
 */

#pragma once

@class NSWindow;

namespace tgon
{
    
struct WindowStyle;

/**
 * @brief                       Creates a window via given WindowStyle.
 * @param [in] windowStyle      Window style information
 */
NSWindow* MakeNativeWindow(const WindowStyle& windowStyle);

} /* namespace tgon */
