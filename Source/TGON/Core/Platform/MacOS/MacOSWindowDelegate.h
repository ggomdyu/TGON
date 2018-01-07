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
namespace core
{

class Window;

} /*　namespace core */
} /*　namespace tgon */

@interface WindowDelegate : NSObject<NSWindowDelegate>
{
}

@property (readonly, assign) tgon::core::Window* window;

- (id)initWithWindow:(tgon::core::Window*)window;

@end
