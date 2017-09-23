/**
 * @filename    MacOSConfig.h
 * @author      ggomdyu
 * @since       09/05/2017
 */

#import <AppKit/NSApplication.h>
#import <objc/NSObject.h>

@class NSOpenGLContext;

@interface MacOSAppDelegate : NSObject<NSApplicationDelegate>
{
@private
    struct __CVDisplayLink* _displayLink;
}
@end
