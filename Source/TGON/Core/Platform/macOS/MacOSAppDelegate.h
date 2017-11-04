/**
 * @filename    MacOSAppDelegate.h
 * @author      ggomdyu
 * @since       09/05/2017
 */

#import <AppKit/NSApplication.h>
#import <objc/NSObject.h>

#import "MacOSAppDelegateFwd.h"

@interface MacOSAppDelegate : NSObject<NSApplicationDelegate>
{
@private
    __CVDisplayLink* _displayLink;
}
@end
