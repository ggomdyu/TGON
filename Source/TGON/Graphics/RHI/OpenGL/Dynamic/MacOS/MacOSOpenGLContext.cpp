#import "PrecompiledHeader.pch"
#import "OpenGLContext.h"

#import <AppKit/NSOpenGL.h>
#import <AppKit/NSOpenGLView.h>
#import <AppKit/NSWindow.h>

#import "Core/Platform/Window.h"
#import "Graphics/RHI/Base/BaseRHIType.h"

namespace tgon
{
namespace rhi
{
namespace
{

void ConvertVideoModeToNative(const VideoMode& videoMode, NSOpenGLPixelFormatAttribute* attributes, std::size_t attributesBufferSize)
{
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
}

} /* namespace */

OpenGLContext::OpenGLContext(const std::shared_ptr<platform::Window>& window, const VideoMode& videoMode)
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
        }
    }

    // Create a GL context through the selected pixel format.
    {
        context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
    }

    // Create a GL View and attach it to target window.
    NSWindow* nativeWindow = (__bridge NSWindow*)window->GetNativeWindow();
    {
        NSOpenGLView *openGLView = [[NSOpenGLView alloc] init];
        [nativeWindow setContentView:openGLView];

        [[openGLView openGLContext] makeCurrentContext];
    }
}

OpenGLContext::~OpenGLContext() = default;

} /* namespace rhi */
} /* namespace tgon */
