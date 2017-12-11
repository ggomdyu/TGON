/**
 * @filename    MacOSAppDelegate.h
 * @author      ggomdyu
 * @since       09/05/2017
 */

#import <AppKit/NSApplication.h>
#import <objc/NSObject.h>

@interface AppDelegate : NSObject<NSApplicationDelegate>
{
@private
    struct __CVDisplayLink* _displayLink;
}
@end
