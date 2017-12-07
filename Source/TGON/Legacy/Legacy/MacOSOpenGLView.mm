#import "PrecompiledHeader.pch"
#import "MacOSOpenGLView.h"

#import <AppKit/NSOpenGL.h>
#import <OpenGL/OpenGL.h>
#import <QuartzCore/CVDisplayLink.h>

// OpenGL 3.2 is only supported on MacOS X Lion and later
// CGL_VERSION_1_3 is defined as 1 on MacOS X Lion and later
#if CGL_VERSION_1_3
#   import <OpenGL/gl3.h>
#else
#   import <OpenGL/gl.h>
#endif

#include <AppKit/NSOpenGL.h>

@implementation MacOSOpenGLView


@end
