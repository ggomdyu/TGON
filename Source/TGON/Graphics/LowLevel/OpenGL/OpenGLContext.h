/**
 * @filename    OpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>

#include "Graphics/LowLevel/Generic/GenericGraphicsType.h"

#include "OpenGLContextFwd.h"

namespace tgon
{

struct TGON_API OpenGLContext final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    OpenGLContext(const VideoMode& videoMode, const std::shared_ptr<Window>& displayTarget);
    OpenGLContext(OpenGLContext&& rhs);

/* @section Public destructor */
public:
    ~OpenGLContext();

/* @section Public operator */
public:
    OpenGLContext& operator=(OpenGLContext&& rhs);

/* @section Public method */
public:
    void MakeCurrent();
    
    /* @brief   Displays the rendered image to the screen. */
    void SwapBuffer();

/* @section Public variable */
public:
#if TGON_PLATFORM_WINDOWS
    HWND wndHandle;
    HGLRC context;
    HDC dcHandle;
    int pixelFormat;
#elif TGON_PLATFORM_MACOS
    NSOpenGLPixelFormat* pixelFormat;
    NSOpenGLContext* context;
#elif TGON_PLATFORM_ANDROID
#elif TGON_PLATFORM_IOS
#endif
};

} /* namespace tgon */
