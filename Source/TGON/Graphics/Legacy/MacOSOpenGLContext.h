/**
 * @filename    MacOSOpenGLView.h
 * @author      ggomdyu
 * @since       09/18/2017
 * @brief
 */

#pragma once
#import <AppKit/NSOpenGL.h>

#include "Graphics/API/OpenGL/Base/BaseOpenGLContext.h"
#include "Graphics/Platform/GraphicsWindowType.h"

@class NSOpenGLPixelFormat;
@class NSOpenGLContext;

namespace tgon
{
namespace opengl
{
namespace macos
{

class TGON_API MacOSOpenGLContext :
    public BaseOpenGLContext
{
/* @section Public constructor */
public:
    explicit MacOSOpenGLContext(const platform::VideoMode& videoMode);

/* @section Public method */
public:
    virtual void Lock() override;
    virtual void Unlock() override;

    NSOpenGLPixelFormat* GetPixelFormat() noexcept;
    NSOpenGLContext* GetContext() noexcept;

/* @section Public constructor */
private:
    NSOpenGLPixelFormat* m_pixelFormat;
    NSOpenGLContext* m_context;
};

} /* namespace macos */

using OpenGLContext = macos::MacOSOpenGLContext;

} /* namespace opengl */
} /* namespace tgon */
