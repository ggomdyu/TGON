#import "PrecompiledHeader.h"

#import <GL/glew.h>
#import <AppKit/NSOpenGL.h>
#import <AppKit/NSOpenGLView.h>
#import <AppKit/NSWindow.h>

#import "Core/Platform/Window.h"

#import "OpenGLContext.h"

namespace tgon
{
namespace
{

void ConvertVideoModeToNative(const VideoMode& videoMode, NSOpenGLPixelFormatAttribute* attributes, std::size_t attributesBufferSize)
{
    int attributeIndex = 0;

    if (videoMode.enableHardwareAccelerate)
    {
        attributes[attributeIndex++] = NSOpenGLPFAAccelerated;
    }

    attributes[attributeIndex++] = NSOpenGLPFADoubleBuffer;

    if (videoMode.enableMultiSampling)
    {
        attributes[attributeIndex++] = NSOpenGLPFASampleBuffers;
        attributes[attributeIndex++] = 1;
        
        attributes[attributeIndex++] = NSOpenGLPFASamples;
        attributes[attributeIndex++] = videoMode.sampleCount;
    }

    attributes[attributeIndex++] = NSOpenGLPFAColorSize;
    attributes[attributeIndex++] = 32;

    attributes[attributeIndex++] = NSOpenGLPFADepthSize;
    attributes[attributeIndex++] = 24;

    attributes[attributeIndex++] = NSOpenGLPFAAlphaSize;
    attributes[attributeIndex++] = 8;

    attributes[attributeIndex++] = NSOpenGLPFAOpenGLProfile;
    attributes[attributeIndex++] = NSOpenGLProfileVersion3_2Core;

    // Mark end of attribute.
    attributes[attributeIndex++] = 0;
}

} /* namespace */

OpenGLContext::OpenGLContext(const VideoMode& videoMode, std::shared_ptr<Window> window)
{
    // Find a suitable pixel format.
    {
        NSOpenGLPixelFormatAttribute pixelFormatAttributes[64];
        {
            ConvertVideoModeToNative(videoMode, pixelFormatAttributes, std::extent<decltype(pixelFormatAttributes)>::value);
        }

        pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
        if (pixelFormat == nullptr)
        {
            NSLog(@"No OpenGL pixel format.");
            return;
        }
    }

    // Create a GL context through the selected pixel format.
    {
        context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
    }

    // Create a GL View and attach it to thes target window.
    NSWindow* nativeWindow = (__bridge NSWindow*)window->GetNativeWindow();
    {
        NSOpenGLView* openGLView = [[NSOpenGLView alloc] init];
        [openGLView setOpenGLContext:context];

        // Now, we will use this context.
        [[openGLView openGLContext] makeCurrentContext];

        [nativeWindow setContentView:openGLView];
    }

    glewInit();
}

OpenGLContext::OpenGLContext(OpenGLContext&& rhs) :
    pixelFormat(rhs.pixelFormat),
    context(rhs.context)
{
    rhs.pixelFormat = nil;
    rhs.context = nil;
}

OpenGLContext::~OpenGLContext() = default;

OpenGLContext& OpenGLContext::operator=(OpenGLContext&& rhs)
{
    if (this != &rhs)
    {
        pixelFormat = rhs.pixelFormat;
        context = rhs.context;
        
        rhs.pixelFormat = nil;
        rhs.context = nil;
    }

    return *this;
}

void OpenGLContext::MakeCurrent()
{
    [context makeCurrentContext];
}

void OpenGLContext::SwapBuffer()
{
    [context flushBuffer];
}

} /* namespace tgon */
