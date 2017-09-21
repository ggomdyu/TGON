/**
 * @filename    MacOSWindowDelegate.h
 * @author      ggomdyu
 * @since       08/31/2017
 * @brief
 */

#pragma once
#include <Cocoa/Cocoa.h>

namespace tgon
{
namespace platform
{
namespace macos
{

class MacOSWindow;

} /* namespace macos */
} /* namespace platform */
} /* namespace tgon */

@interface MacOSWindowDelegate : NSObject<NSWindowDelegate>
{
}

@property (readonly, assign) tgon::platform::macos::MacOSWindow* window;

- (id)initWithWindow:(tgon::platform::macos::MacOSWindow*)window;

@end
