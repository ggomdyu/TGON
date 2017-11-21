/**
 * @filename    OpenGLContext.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#include "OpenGLContextFwd.h"

namespace tgon
{
namespace rhi
{

struct TGON_API OpenGLContext
{
/* @section Public type */
public:
    using OnDrawCallback = void(*)(const std::shared_ptr<OpenGLContext>&);

/* @section Public variable */
public:
#if BOOST_OS_WINDOWS
#elif BOOST_OS_MACOS
    NSOpenGLPixelFormat* pixelFormat;
    NSOpenGLContext* context;
#elif BOOST_OS_ANDROID
#elif BOOST_OS_IOS
#endif

    OnDrawCallback onDrawCallback;
};

} /* namespace rhi */
} /* namespace tgon */

