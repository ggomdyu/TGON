/**
 * @file    MacOSWindowDelegate.h
 * @author  ggomdyu
 * @since   08/31/2017
 */

#pragma once
#import <Cocoa/Cocoa.h>

namespace tgon
{
 
class WindowImpl;
    
} /* namespace tgon */

@interface WindowDelegate : NSObject<NSWindowDelegate>
{
}

@property (readonly, assign) tgon::WindowImpl* window;

- (id)initWithWindow:(tgon::WindowImpl*)window;

@end
