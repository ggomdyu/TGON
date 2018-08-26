/**
 * @file    MacOSWindowUtility.h
 * @author  ggomdyu
 * @since   07/21/2017
 */

#pragma once
#import <AppKit/NSWindow.h>

#include "Core/Platform/Config.h"

#include "../WindowType.h"

namespace tgon
{

class TGON_API MacOSWindowUtility final
{
/* @section Public method */
public:
    /**
     * @brief                       Creates a window via given WindowStyle.
     * @param [in] windowStyle      Window style information
     */
    static NSWindow* CreateNativeWindow(const WindowStyle& windowStyle);
    
/* @section Private method */
private:
    /* @brief                       Converts a WindowStyle to NSWindowStyleMask. */
    static NSWindowStyleMask ConvertWindowStyleToMask(const WindowStyle& windowStyle);
};

} /* namespace tgon */
