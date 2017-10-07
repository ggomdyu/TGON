#import "PrecompiledHeader.pch"
#import "OpenGLContext.h"

#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>
#import <AppKit/NSOpenGL.h>

namespace tgon
{
namespace graphics
{
namespace
{

NSOpenGLPixelFormatAttribute* ConvertVideoModeToNative(const VideoMode& videoMode)
{
    static NSOpenGLPixelFormatAttribute attributes[64] {};

    int attributeCount = 0;

    if (videoMode.enableHardwareAccelerate)
    {
        attributes[attributeCount++] = NSOpenGLPFAAccelerated;
    }

    if (videoMode.enableDoubleBuffer)
    {
        attributes[attributeCount++] = NSOpenGLPFADoubleBuffer;
    }

    if (videoMode.enableMultiSampling)
    {
        attributes[attributeCount++] = NSOpenGLPFASampleBuffers;
        attributes[attributeCount++] = 1;
        attributes[attributeCount++] = NSOpenGLPFASamples;
        attributes[attributeCount++] = videoMode.sampleCount;
    }

    attributes[attributeCount++] = NSOpenGLPFAColorSize;
    attributes[attributeCount++] = 32;

    attributes[attributeCount++] = NSOpenGLPFADepthSize;
    attributes[attributeCount++] = 24;

    attributes[attributeCount++] = NSOpenGLPFAAlphaSize;
    attributes[attributeCount++] = 8;

#if CGL_VERSION_1_3
    attributes[attributeCount++] = NSOpenGLPFAOpenGLProfile;
    attributes[attributeCount++] = NSOpenGLProfileVersion3_2Core;
#endif
    
    // Mark end of attribute.
    attributes[attributeCount++] = 0;

    return attributes;
}

}

OpenGLContext::OpenGLContext(const VideoMode& videoMode)
{
    NSOpenGLPixelFormatAttribute* pixelFormatAttributes = ConvertVideoModeToNative(videoMode);

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

void OpenGLContext::Lock()
{
    ::CGLLockContext([m_context CGLContextObj]);
}

void OpenGLContext::Unlock()
{
    ::CGLUnlockContext([m_context CGLContextObj]);
}

} /* namespace graphics */
} /* namespace tgon */
