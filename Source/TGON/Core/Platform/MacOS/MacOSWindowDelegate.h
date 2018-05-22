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

class GenericWindow;

} /*　namespace tgon */

@interface WindowDelegate : NSObject<NSWindowDelegate>
{
}

@property (readonly, assign) tgon::GenericWindow* window;

- (id)initWithWindow:(tgon::GenericWindow*)window;

@end
