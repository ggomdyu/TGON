/**
 * @file    MacOSWindowUtility.h
 * @author  ggomdyu
 * @since   07/21/2017
 */

#pragma once
#import <AppKit/NSWindow.h>

#include "Platform/Config.h"

namespace tgon
{
    
struct WindowStyle;

/**
 * @brief                   Creates a window via given WindowStyle.
 * @param [in] windowStyle  Window style information
 */
TGON_API NSWindow* CreateNativeWindow(const WindowStyle& windowStyle);

} /* namespace tgon */
