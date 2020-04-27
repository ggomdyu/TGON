#include "PrecompiledHeader.h"

#if TGON_GRAPHICS_OPENGL
#include <GL/glew.h>
#include <AppKit/NSOpenGLView.h>
#include <AppKit/NSWindow.h>

#include "Platform/Window.h"

#include "../OpenGLContext.h"

namespace tg
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

NSOpenGLPixelFormat* FindSuitablePixelFormat(const VideoMode& videoMode)
{
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[64];
    ConvertVideoModeToNative(videoMode, pixelFormatAttributes, std::extent_v<decltype(pixelFormatAttributes)>);

    return [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
}

} /* namespace */

OpenGLContext::OpenGLContext(const std::shared_ptr<Window>& displayWindow, const VideoMode& videoMode) :
    context([[NSOpenGLContext alloc] initWithFormat:FindSuitablePixelFormat(videoMode) shareContext:nil])
{
    NSWindow* nativeWindow = (__bridge NSWindow*)displayWindow->GetNativeWindow();
    
    // Create a NSOpenGLView and attach it to the target window.
    NSOpenGLView* openGLView = [[NSOpenGLView alloc] init];
    [openGLView setOpenGLContext: context];
    [[openGLView openGLContext] makeCurrentContext];
    [nativeWindow setContentView:openGLView];
    
    glewInit();
}

OpenGLContext::OpenGLContext(OpenGLContext&& rhs) noexcept :
    pixelFormat(rhs.pixelFormat),
    context(rhs.context)
{
    rhs.pixelFormat = nil;
    rhs.context = nil;
}

OpenGLContext::~OpenGLContext()
{
	this->Destroy();
}

OpenGLContext& OpenGLContext::operator=(OpenGLContext&& rhs) noexcept
{
    std::swap(pixelFormat, rhs.pixelFormat);
    std::swap(context, rhs.context);
    
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

void OpenGLContext::Destroy()
{
	pixelFormat = nil;
    context = nil;
}

}
#endif
