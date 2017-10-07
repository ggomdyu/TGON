/**
 * @filename    MacOSOpenGLView.h
 * @author      ggomdyu
 * @since       09/18/2017
 * @brief
 */

#pragma once
#import <AppKit/NSOpenGLView.h>

@class NSOpenGLPixelFormat;
@class NSOpenGLContext;

namespace tgon
{
namespace graphics
{

struct VideoMode final
{
/* @section Public variable */
public:
    /* @brief   If false, the application will perform software rendering. */
    bool enableHardwareAccelerate;
    bool enableDoubleBuffer;
    bool enableMultiSampling;
    uint16_t sampleCount;
    uint32_t colorBits;
    uint32_t depthBits;
    uint32_t stencilBits;
};

//class OpenGLContextLockGuard
//{
//
//};

class OpenGLContext
{
/* @section Public constructor */
public:
    explicit OpenGLContext(const VideoMode& videoMode);

public:
    void Lock();
    void Unlock();

private:
    NSOpenGLPixelFormat* m_pixelFormat;
    NSOpenGLContext* m_context;
};

} /* namespace graphics */
} /* namespace tgon */
