/**
 * @filename    MacOSWindowDelegate.h
 * @author      ggomdyu
 * @since       08/31/2017
 * @brief
 */

#pragma once
#import <Cocoa/Cocoa.h>

namespace tgon
{
namespace platform
{

class Window;

} /*　namespace platform */
} /*　namespace tgon */

@interface WindowDelegate : NSObject<NSWindowDelegate>
{
}

@property (readonly, assign) tgon::platform::Window* window;

- (id)initWithWindow:(tgon::platform::Window*)window;

@end
