#import "PrecompiledHeader.pch"
#import "MacOSOpenGLContext.h"

#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>
#import <AppKit/NSOpenGL.h>

#import "MacOSOpenGLUtility.h"

namespace tgon
{
namespace opengl
{

MacOSOpenGLContext::MacOSOpenGLContext(const VideoMode& videoMode)
{
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[64];
    ConvertVideoModeToNative(videoMode, pixelFormatAttributes);

    // Choose a supported pixel format.
    m_pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
    if (m_pixelFormat == nil)
    {
        NSLog(@"No OpenGL pixel format selected.");
        return;
    }

    m_context = [[NSOpenGLContext alloc] initWithFormat:m_pixelFormat shareContext:nil];
    if (m_pixelFormat == nil)
    {
        NSLog(@"No OpenGL pixel format selected.");
        return;
    }

#if CGL_VERSION_1_3 && defined(DEBUG)
    // When we're using a CoreProfile context, crash if we call a legacy OpenGL function
    // This will make it much more obvious where and when such a function call is made so
    // that we can remove such calls.
    // Without this we'd simply get GL_INVALID_OPERATION error for calling legacy functions
    // but it would be more difficult to see where that function was called.
    CGLEnable([m_context CGLContextObj], kCGLCECrashOnRemovedFunctions);
#endif
}

void MacOSOpenGLContext::Lock()
{
    ::CGLLockContext([m_context CGLContextObj]);
}

void MacOSOpenGLContext::Unlock()
{
    ::CGLUnlockContext([m_context CGLContextObj]);
}

NSOpenGLPixelFormat* GetPixelFormat() noexcept
{
    return m_pixelFormat;
}

NSOpenGLContext* GetContext() noexcept
{
    return m_context;
}

} /* namespace opengl */
} /* namespace tgon */
