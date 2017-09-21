/**
 * @filename    MacOSConfig.h
 * @author      ggomdyu
 * @since       09/05/2017
 */

#import <AppKit/NSApplication.h>
#import <objc/NSObject.h>

@class CVDisplayLink;
@class NSTimer;

@interface MacOSAppDelegate : NSObject<NSApplicationDelegate>
{
@private
    NSTimer* _updateTimer;
}
@end
