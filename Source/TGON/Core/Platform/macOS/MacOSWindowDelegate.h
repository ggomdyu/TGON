/**
 * @filename    MacOSWindowDelegate.h
 * @author      ggomdyu
 * @since       08/31/2017
 * @brief
 */

#pragma once
#import <Cocoa/Cocoa.h>

#import "MacOSWindowDelegateFwd.h"

@interface MacOSWindowDelegate : NSObject<NSWindowDelegate>
{
}

@property (readonly, assign) tgon::platform::macos::MacOSWindow* window;

- (id)initWithWindow:(tgon::platform::macos::MacOSWindow*)window;

@end
