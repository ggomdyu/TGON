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

class GenericWindow;

} /*　namespace core */
} /*　namespace tgon */

@interface WindowDelegate : NSObject<NSWindowDelegate>
{
}

@property (readonly, assign) tgon::core::GenericWindow* window;

- (id)initWithWindow:(tgon::core::GenericWindow*)window;

@end
