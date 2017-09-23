#import "PrecompiledHeader.pch"
#import "MacOSOpenGLView.h"


#import <OpenGL/OpenGL.h>

// OpenGL 3.2 is only supported on MacOS X Lion and later
// CGL_VERSION_1_3 is defined as 1 on MacOS X Lion and later
#import <OpenGL/gl.h>

//#if CGL_VERSION_1_3
//#   import <OpenGL/gl3.h>
//#else
//#   import <OpenGL/gl.h>
//#endif

@implementation MacOSOpenGLView

- (id)initWithDisplayLink
{
    self = [super init];
    if (self)
    {
        NSOpenGLContext* context = [self openGLContext];

        // Set the display link for the current renderer
//        CGLContextObj cglContext = [openGLContext CGLContextObj];
//        CGLPixelFormatObj cglPixelFormat = [pixelFormat CGLPixelFormatObj];
//        CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
    }

    return self;
}

-(void)drawRect
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(0.5f, -0.5f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
    }
    glEnd();

    glFlush();
}

@end
