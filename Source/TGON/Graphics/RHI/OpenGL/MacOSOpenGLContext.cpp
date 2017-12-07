#import "PrecompiledHeader.pch"
#import "../OpenGLRHIUtility.h"

namespace tgon
{
namespace rhi
{
namespace gl
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

std::shared_ptr<OpenGLContext> MakeContext(const rhi::VideoMode& videoMode)
{
    auto context = std::make_shared<OpenGLContext>();
    {
        NSOpenGLPixelFormatAttribute pixelFormatAttributes[64];
        {
            ConvertVideoModeToNative(videoMode, pixelFormatAttributes, std::extent<decltype(pixelFormatAttributes)>::value);
        }

        context->pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
        if (context->pixelFormat == nullptr)
        {
            NSLog(@"No OpenGL pixel format.");
        }

        context->context = [[NSOpenGLContext alloc] initWithFormat:context->pixelFormat shareContext:nil];
    }
    return context;
}

} /* namespace gl */
} /* namespace rhi */
} /* namespace tgon */
