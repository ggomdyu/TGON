/**
 * @file    MacOSWindowDelegate.h
 * @author  ggomdyu
 * @since   08/31/2017
 */

#pragma once
#import <Cocoa/Cocoa.h>

namespace tgon
{
 
class MacOSWindow;
    
} /* namespace tgon */

@interface WindowDelegate : NSObject<NSWindowDelegate>
{
}

@property (readonly, assign) tgon::MacOSWindow* window;

- (id)initWithWindow:(tgon::MacOSWindow*)window;

@end
