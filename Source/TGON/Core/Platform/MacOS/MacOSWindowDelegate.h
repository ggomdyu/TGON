/**
 * @file    MacOSWindowDelegate.h
 * @author  ggomdyu
 * @since   08/31/2017
 */

#pragma once
#import <Cocoa/Cocoa.h>

#import "../Window.h"

@interface WindowDelegate : NSObject<NSWindowDelegate>
{
}

@property (readonly, assign) tgon::Window* window;

- (id)initWithWindow:(tgon::Window*)window;

@end
